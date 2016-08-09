macro(SETUP_RAPP)

	include_directories(${RAPP_INCLUDE_DIRS} ${RAPP_ROBOTS_INCLUDE_DIRS})

	add_definitions("-std=c++11")
	string(REPLACE ":" ";" LIBS_LIST $ENV{LD_LIBRARY_PATH})
	link_directories(${LIBS_LIST})

endmacro(SETUP_RAPP)

macro(CREATE_RAPP)
	
	include(CMakeParseArguments)

	cmake_parse_arguments(RAPP
		""
		"NAME"
		"SRCS;LIBS"
		${ARGN}
	)

#	MESSAGE("Default args: ${RAPP_UNPARSED_ARGUMENTS}")
#	MESSAGE("Arguments for ${RAPP_NAME}")
#	MESSAGE("Sources: ${RAPP_SRCS}")
#	MESSAGE("Libs: ${RAPP_LIBS}")

	add_executable(${RAPP_NAME} ${RAPP_SRCS})
	target_link_libraries(${RAPP_NAME} rapp_robot_vision rapp_robot_navigation rapp_robot_communication ${RAPP_LIBS})

	install(TARGETS ${RAPP_NAME} DESTINATION bin)

endmacro(CREATE_RAPP)

