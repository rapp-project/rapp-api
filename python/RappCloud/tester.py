#!/usr/bin/env python
# -*- coding: utf-8 -*-

from RappPlatformApi import RappPlatformApi

ph = RappPlatformApi()

print ph.faceDetection('/home/manos/rapp_platform/rapp-platform-catkin-ws/src/rapp-platform/rapp_testing_tools/test_data/face_samples/etsardou_medium.jpg', False)
