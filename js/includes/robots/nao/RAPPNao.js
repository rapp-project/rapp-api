#!/usr/bin/env node

function RAPPNao()
{
    // As NAO core agent services are just ROS services, they
    // will be invoked from JavaScript code through the ROSbridge
    // server. The ROSbridge server MUST BE STARTED before any of
    // the service is called.
    this.rosbridge_url = "ws://localhost:9090";
}

RAPPNao.prototype =
{
    // An example wrapper function for one of the standard ROS services:
    // rosapi/get_time, where:
    //
    // callback - the function to be called with the result returned by
    //            the service.
    rosapi_get_time: function(callback)
    {
        var rapp = this;
        var WebSocket = require("ws");
        var ws = new WebSocket(rapp.rosbridge_url);
        ws.onopen = function ()
        {
            var msg =
            {
                op: "call_service",
                service: "/rosapi/get_time"
            };
            ws.send(JSON.stringify(msg));
        };
        ws.onmessage = function (event)
        {
            var eventValue = JSON.parse(event.data);
            if (eventValue.op == "service_response")
            {
                callback(eventValue.values);
            }
            ws.close();
            ws = undefined;
        };
    },
    //
    // NAO core agent services:
    //
    // rapp/say: Says the specified string of characters in the given language,
    // where:
    //
    // request - the string of characters;
    // language - the name of the language (e.g. "English"), or an empty string
    //            denoting the robot's default language;
    // callback - the function to be called with the result returned by
    //            the service.
    rapp_say: function(request, language, callback)
    {
        var rapp = this;
        var WebSocket = require("ws");
        var ws = new WebSocket(rapp.rosbridge_url);
        ws.onopen = function ()
        {
            var msg =
            {
                op: "call_service",
                service: "/rapp_say",
                args: { request: request,
                        language: language }
            };
            ws.send(JSON.stringify(msg));
        };
        ws.onmessage = function (event)
        {
            var eventValue = JSON.parse(event.data);
            if (eventValue.op == "service_response")
            {
                callback(eventValue.values);
            }
            ws.close();
            ws = undefined;
        };
    }
}

module.exports.RAPPNao = RAPPNao;
