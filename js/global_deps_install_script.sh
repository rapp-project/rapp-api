#!/bin/bash -i

##

# Authors: Lazaros Penteridis
# Contact: lp@ortelio.co.uk
##

##
	#Install Rapp JS API global dependencies onto the system.
##

# Update apt-get repositories, Install NodeJS and npm and create a symbolic link for node
sudo apt-get update
sudo apt-get install curl

# Install Node.js v4

curl -sL https://deb.nodesource.com/setup_4.x | sudo -E bash -
sudo apt-get install -y nodejs

sudo apt-get install -y npm
sudo ln -s /usr/bin/nodejs /usr/bin/node

# global npm modules required
#for task management
sudo npm install -g grunt-cli
#for testing
sudo npm install -g mocha
