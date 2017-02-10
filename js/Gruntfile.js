/*global module:false*/
module.exports = function(grunt) {

  // Project configuration.
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    // Task configuration.
    jsdoc: {
      src: ['README.md', 'lib/*'],
      options: {
        destination: 'doc',
        template: "node_modules/ink-docstrap/template",
        configure: "jsdoc-lib.conf.json"
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
  grunt.registerTask('doc-gen', ['jsdoc']);

  grunt.registerTask('clean-doc', ['shell:clean_doc']);
};
