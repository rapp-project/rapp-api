INSTALL_PATH?=/usr/local

all:  deps doc

install:
	mkdir -p $(INSTALL_PATH)/share/rapp-api-js/
	cp -rf includes/ $(INSTALL_PATH)/share/rapp-api-js/includes/
	cp -rf node_modules/ $(INSTALL_PATH)/share/rapp-api-js/node_modules/
	echo 'export NODE_PATH="'$(INSTALL_PATH)/share/rapp-api-js/includes/cloud:$(INSTALL_PATH)/share/rapp-api-js/includes/object'"' >> ~/.bashrc
	. ~/.bashrc
		
uninstall:
	rm -rf $(INSTALL_PATH)/share/rapp-api-js/
	awk '!/export NODE_PATH/' ~/.bashrc > ~/.temp1 && mv ~/.temp1 ~/.bashrc
	. ~/.bashrc
	
jshint:
	node_modules/jshint/bin/jshint includes
	
test:	   	deps
	@NODE_ENV=test ./node_modules/mocha/bin/mocha test/cloud_test.js test/object_test.js

doc: doc-cloud doc-objects

doc-cloud:	deps
	rm -rf doc/cloud
	grunt doc-gen-cloud

doc-objects:	deps
	rm -rf doc/objects
	grunt doc-gen-objects

deps:
	npm install

clean-doc:
	rm -rf doc/

clean-deps:
	rm -rf node_modules

clean:  clean-doc clean-deps

.PHONY: jshint
.PHONY: test
