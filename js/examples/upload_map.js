#!/usr/bin/env node

// Import the path_planning_upload_map JS API Services & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.path_planning_upload_map = require('../includes/cloud/path_planning_upload_map.js');

var services = new RAPPCloud( );

services.path_planning_upload_map( '../../testdata/523_m.yaml', '../../testdata/523_mj.png', 'the map' );
