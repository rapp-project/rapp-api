macro(SETUP_RAPP)

    include_directories(${RAPP_INCLUDE_DIRS} ${RAPP_ROBOTS_INCLUDE_DIRS})

    add_definitions("-std=c++11 -static-libstdc++ -m32")
    string(REPLACE ":" ";" LIBS_LIST $ENV{LD_LIBRARY_PATH})
    link_directories(${LIBS_LIST})

    find_package(Boost 1.49 COMPONENTS system thread random unit_test_framework program_options regex filesystem REQUIRED)
endmacro(SETUP_RAPP)

macro(CREATE_RAPP)
    
    include(CMakeParseArguments)

    cmake_parse_arguments(RAPP
        ""
        "NAME"
        "SRCS;LIBS;FILES"
        ${ARGN}
    )

#   MESSAGE("Default args: ${RAPP_UNPARSED_ARGUMENTS}")
#   MESSAGE("Arguments for ${RAPP_NAME}")
#   MESSAGE("Sources: ${RAPP_SRCS}")
#   MESSAGE("Libs: ${RAPP_LIBS}")

    add_executable(${RAPP_NAME} ${RAPP_SRCS})
    target_link_libraries(${RAPP_NAME} rapp rapp_robot_vision rapp_robot_navigation rapp_robot_communication rapp_robot_info rapp_robot_localization ${RAPP_LIBS} ${Boost_LIBRARIES})

    install(TARGETS ${RAPP_NAME} DESTINATION bin)
    
    if (EXISTS ${CMAKE_SOURCE_DIR}/run.sh)
        MESSAGE(WARNING "Run script found")
        install(FILES run.sh DESTINATION .)
    else()
        file(WRITE ${CMAKE_BINARY_DIR}/run.sh "#/bin/sh\n$1/bin/${RAPP_NAME} --base_path $1" )
        MESSAGE(WARNING "Run script is missing! Using default:\n\t#/bin/sh\n\tbin/${RAPP_NAME}")
        install(FILES ${CMAKE_BINARY_DIR}/run.sh DESTINATION .)
    endif()

    if (RAPP_FILES)
        install(FILES ${RAPP_FILES} DESTINATION share/${RAPP_NAME})
    endif()

endmacro(CREATE_RAPP)
