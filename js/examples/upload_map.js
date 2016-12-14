#!/usr/bin/env node

// Import the path_planning_upload_map JS API Services & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.path_planning_upload_map = require('../lib/cloud/path_planning_upload_map');

var services = new RAPPCloud();

services.path_planning_upload_map(
                                    '../testdata/maps/523_m3.png',
                                    '../testdata/maps/523_m.yaml', 
                                    'the_map'
                                 );
