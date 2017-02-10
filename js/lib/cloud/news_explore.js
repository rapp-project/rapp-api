#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class news_explore
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the news_explore RAPP platform service
 * @version 0.7.5
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param news_engine (String): The news search engine to use.
 * @param keywords (Array): Desired keywords.
 * @param exclude_titles (Array): Reject list of previously read articles, in 
 * order to avoid duplicates.
 * @param region (String): Language/Region.
 * @param topic (String): Main topics, i.e. sports, politics, etc.
 * @param num_news (Integer): Number of news stories.
 * @param callback is the function that will receive the result
 */    
RAPPCloud.prototype.news_explore = function(
                                             news_engine,
                                             keywords,
                                             exclude_titles,
                                             region,
                                             topic,
                                             num_news,
                                             callback
                                           )
{
    var cloud = this;
    var _delegate = callback;
    var request = cloud.determine_protocol();
    var body_obj = {};
    body_obj.news_engine = cloud.escape_string(news_engine);
    body_obj.keywords = [];
   	for (var i=0; i<keywords.length; i++)
       	body_obj.keywords[i] = cloud.escape_string(keywords[i]);
    body_obj.exclude_titles = [];
    for (i=0; i<exclude_titles.length; i++)
        body_obj.exclude_titles[i] = cloud.escape_string(exclude_titles[i]);
    body_obj.region = cloud.escape_string(region);
    body_obj.topic = cloud.escape_string(topic);
    body_obj.num_news = num_news;
    var body_json = JSON.stringify(body_obj);
    
    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/news_explore/ ',
        body: "json=" + body_json
    },
    function (error, response, json) 
    {
        if (!error && response.statusCode == 200)
            handle_reply(json);
        else if (error)
            error_handler (error);
        else if (response.statusCode != 200)
            console.log ('Error: ' + response.statusCode);
    });
    
    function handle_reply(json)
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			// JSON reply is: { news_stories: [{<story_1>}, ...,  {<story_n>}], error: '' }	
		    // news_stories (Array): Array of story objects.
    		// error (String): Error message, if one occures.
    		// where story object is:
			// { title: '', content: '', puplisher: '', publishedDate: '', url: '' }
    		// 		title (String): Article title.
    		// 		content (String): Article brief content.
    		// 		publisher (String): Article publisher.
    		// 		publishedDate (String): Article publication date.
    		// 		url (String): Article original url.
		
			if(json_obj.error)  // Check for Errors  
				console.log('news_explore JSON error: ' + json_obj.error);
	        else 
	        	_delegate(json_obj.news_stories);
		} catch (e) {
			console.log('news_explore::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler(error) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.news_explore;
