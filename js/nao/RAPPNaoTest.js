#!/usr/bin/env node

// An example of using the RAPPNao JS API.
// Note that all the service calls are asynchronous.

var rapp = require("./RAPPNao.js");
var services = new rapp.RAPPNao();

// The callback function that will handle the reply of the service.
function handler(result)
{ 
    console.log("Result from rosapi_get_time call:");
    console.log("time.secs = " + result.time.secs);
}

// Call rosapi_get_time.
services.rosapi_get_time(handler);

// Another callback function.
function handler_say(result)
{ 
    console.log("Result from rapp_say call:");
    console.log("response = " + result.response);
    // Stop the application.
    process.exit();
}

// Call rapp_say.
services.rapp_say("Hello, my name is NAO", "English", handler_say);
