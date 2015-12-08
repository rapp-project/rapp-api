/*global module:false*/
module.exports = function(grunt) {

  // Project configuration.
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    // Task configuration.
    jsdoc: {
      cloud: {
        src: ['includes/cloud/*/*.js'],
        options: {
          destination: 'doc/cloud',
          template: "node_modules/ink-docstrap/template",
          configure: "jsdoc-includes.conf.json"
        }
      },
      objects: {
        src: ['includes/objects/*/*.js'],
        options: {
          destination: 'doc/objects',
          template: "node_modules/ink-docstrap/template",
          configure: "jsdoc-includes.conf.json"
        }
      }
    },
    shell: {
      options: {
        stderr: true,
        stdout: true
      },
      clean_doc: {
        command: 'rm -rf doc/'
      }
    }
  });

  // Load jsdoc grunt task.
  grunt.loadNpmTasks('grunt-jsdoc');
  // Load shell grunt task
  grunt.loadNpmTasks('grunt-shell');

  // Generate documentation for all task.
  grunt.registerTask('doc-gen', ['jsdoc:cloud', 'jsdoc:objects']);

  // Generate documentation for the cloud services
  grunt.registerTask('doc-gen-cloud', ['jsdoc:cloud']);

  // Generate documentation for objects 
  grunt.registerTask('doc-gen-objects', ['jsdoc:objects']);

  grunt.registerTask('clean-doc', ['shell:clean_doc']);

};
