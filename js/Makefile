all:  doc deps

jshint:
	jshint includes

doc: doc-cloud doc-objects

doc-cloud:  deps
	rm -rf doc/cloud
	grunt doc-gen-cloud

doc-objects: deps
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
