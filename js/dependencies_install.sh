#!/bin/bash -i

##

# Authors: Lazaros Penteridis
# Contact: lp@ortelio.co.uk
##

##
	#Install Rapp API dependencies onto the system.
##

# Update apt-get repositories, Install NodeJS and npm and create a symbolic link for node
sudo apt-get update
sudo apt-get install -y nodejs
sudo apt-get install -y npm
sudo ln -s /usr/bin/nodejs /usr/bin/node


SCRIPT=$(readlink -f "$0")

JS_ROOT=$(dirname "$SCRIPT")

cd $JS_ROOT

# Install form-data and randomstring npm modules in the directory node_modules inside JS root directory
npm install form-data
npm install randomstring
