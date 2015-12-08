#!/bin/bash -i

##

# Authors: Lazaros Penteridis
# Contact: lp@ortelio.co.uk
##

##
	#Install Rapp JS API dependencies onto the system.
##

# Update apt-get repositories, Install NodeJS and npm and create a symbolic link for node
sudo apt-get update
sudo apt-get install -y nodejs
sudo apt-get install -y npm
sudo ln -s /usr/bin/nodejs /usr/bin/node
