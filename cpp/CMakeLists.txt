# @date January 2016
# @author Alex Giokas <a.gkiokas@ortelio.co.uk>
# 
# Command line arguments you can use:
#       -DRAPP_SHARED=ON		                    (Default: compile a shared librapp)
#       -DRAPP_STATIC=ON		                    (Optional: compile a static librapp)
#       -DBUILD_TESTS=ON                                (Optional: compile various tests - run with `make test`)
#       -DBUILD_EXAMPLES=ON                             (Optional: compile various examples)
#       -DCMAKE_BUILD_TYPE=Debug                        (Optional: enable debug symbols)
#       -DSTATIC_LIBSTD=ON                              (Optional: compile statically against libstdc++)
#       -DOPEN_NAO=ON                                   (Optional: compiling on OpenNAO requires additional CXX flags)
#		-DCMAKE_INSTALL_PREFIX=/usr	                    (Optional: specify the library install directory
#       -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl       (Optional: specify OpenSSL root directory)
#       -DOPENSSL_LIBRARIES=/usr/local/opt/openssl/lib/ (Optional: specify OpenSSL library directory)
#
# After succesfull compilation, run as su/sudo: `make install`
# Warning: you cannot cross-compile across platforms without having setup both correct universal libraries (e.g., boost i386 on a amd64 system)
#          as well as the correct tools to compile an ELF from a Darwin/OSX platform.
#          It is outside the scope of RAPP to do that; if you need to compile for other platforms please make sure you have
#          setup your environment to do so and then modify this CMakeLists.txt for the correct target platform.
# 
PROJECT(rapp)
set (RAPP_VERSION_MAJOR 0)
set (RAPP_VERSION_MINOR 7)
cmake_minimum_required(VERSION 2.8)

# library paths
set(LIBRARY_PATH ${LIBRARY_PATH}
		      /lib
		      /usr/lib
		      /usr/lib64
		      /usr/local/lib
		      /usr/local/lib64
		      /usr/lib/x86_64-linux-gnu)

# header paths
set(INCLUDE_HEADERS ${INCLUDE_HEADERS} /usr/include/)
include_directories(SYSTEM ${INCLUDE_HEADERS})
set(INCLUDES ${INCLUDES} rapp)

# set root at `/includes`
add_subdirectory(${INCLUDES})
set(CMAKE_MACOSX_RPATH 1)

message("Build directory: ${CMAKE_CURRENT_BINARY_DIR}")

# include everything from "/includes"
include_directories(".")

# Library-only Executables -
set (SOURCES ${SOURCES} 
             ${INCLUDES}/cloud/asio/asio_timer.cpp
             ${INCLUDES}/cloud/asio/asio_http.cpp
             ${INCLUDES}/cloud/asio/asio_https.cpp
             ${INCLUDES}/cloud/asio/http_header.cpp
             ${INCLUDES}/cloud/asio/http_post.cpp
             ${INCLUDES}/cloud/asio/http_request.cpp
             ${INCLUDES}/cloud/asio/http_response.cpp
             ${INCLUDES}/config/config.cpp
             ${INCLUDES}/objects/time.cpp
             ${INCLUDES}/objects/quaternion.cpp
             ${INCLUDES}/objects/pose.cpp
             ${INCLUDES}/objects/point.cpp
             ${INCLUDES}/objects/msg_metadata.cpp
             ${INCLUDES}/objects/pose_stamped.cpp
             ${INCLUDES}/objects/planned_path.cpp
             ${INCLUDES}/objects/human.cpp
             ${INCLUDES}/objects/face.cpp
             ${INCLUDES}/objects/picture.cpp
             ${INCLUDES}/objects/audio.cpp
             ${INCLUDES}/objects/qr_code.cpp
             ${INCLUDES}/cloud/available_services.cpp
             ${INCLUDES}/cloud/cognitive_exercises.cpp
             ${INCLUDES}/cloud/email.cpp
             ${INCLUDES}/cloud/geolocation.cpp
             ${INCLUDES}/cloud/ontology.cpp
             ${INCLUDES}/cloud/vision_detection.cpp
             ${INCLUDES}/cloud/vision_recognition.cpp
             ${INCLUDES}/cloud/weather_report.cpp
             ${INCLUDES}/cloud/path_planning.cpp
             ${INCLUDES}/cloud/news.cpp
             ${INCLUDES}/cloud/set_noise_profile.cpp
             ${INCLUDES}/cloud/speech_recognition_google.cpp
             ${INCLUDES}/cloud/speech_recognition_sphinx4.cpp
             ${INCLUDES}/cloud/text_to_speech.cpp )

# Begin searching for packgages we use in RAPP API
# Find PThreads (needed by Boost)
find_package(Threads REQUIRED)

###
# Find libcrypt / libssl - we use it for TLS/SSL sockets
#
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    message(STATUS "Using OpenSSL Version: ${OPENSSL_VERSION}")
	message(STATUS "OpenSSL Headers: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")
endif()

###
# Set library sources
#
add_library(lrapp OBJECT ${SOURCES})

###
#   Static Library - only if asked - may be needed for NAO, Intel Atom, older ARM platforms
###
if (${RAPP_STATIC})
    # set target, add library - link with Boost and OpenSSL
    set(LIBTARGET ${LIBRARGET} rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
    add_library(${LIBTARGET} STATIC $<TARGET_OBJECTS:lrapp>)

    ###
    # Find Boost - we use it for a variety of operations
    #
    set_target_properties(${LIBTARGET} PROPERTIES LINK_SEARCH_START_STATIC 1)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    find_package(Boost 1.49 COMPONENTS system REQUIRED)
    if (Boost_FOUND)
        set(Boost_USE_STATIC_LIBS ON)
        set(BUILD_SHARED_LIBS OFF)
        include_directories(${Boost_INCLUDE_DIR})
        target_link_libraries(${LIBTARGET} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    endif()
    set_target_properties(${LIBTARGET} PROPERTIES LINK_SEARCH_END_STATIC 1)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -fPIC")

###
#  Open Nao requires special instructions for ATOM
###
elseif(${OPEN_NAO})
    ###
    # set target, add library - link with Boost and OpenSSL
    #
    set(LIBTARGET ${LIBRARGET} rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
    add_library(${LIBTARGET} SHARED $<TARGET_OBJECTS:lrapp>)

    ###
    # Find Boost - we use it for a variety of operations
    #
    find_package(Boost 1.55 COMPONENTS system REQUIRED)
    if (Boost_FOUND)
        set(Boost_USE_STATIC_LIBS OFF)
        set(BUILD_SHARED_LIBS ON)
        include_directories(${Boost_INCLUDE_DIR})
        target_link_libraries(${LIBTARGET} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    endif()

    ###
    #
    #
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -fPIC -O3 -ffast-math -march=atom -mtune=atom -mfpmath=sse -m32 -ffast-math")
    # -flto -funroll-loops -mfpmath=sse -fschedule-insns -fsched-pressure
    # ^^ more optimisations
###
#   Shared Library - By default
###
else()
    ###
    # Find Boost - we use it for a variety of operations
    #
    find_package(Boost 1.49 COMPONENTS system REQUIRED)
    if (Boost_FOUND)
        set(Boost_USE_STATIC_LIBS OFF)
        set(BUILD_SHARED_LIBS OFF)
        include_directories(${Boost_INCLUDE_DIR})
    endif()

    # use shared boost - build shared libs - set correct flags
    set(Boost_USE_STATIC_LIBS OFF)
    set(BUILD_SHARED_LIBS ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -fPIC")

    # build library first
    set(LIBTARGET ${LIBRARGET} rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
    add_library(${LIBTARGET} SHARED $<TARGET_OBJECTS:lrapp>)
    target_link_libraries(${LIBTARGET} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    #set_target_properties(${LIBTARGET} PROPERTIES INSTALL_oPATH "${CMAKE_INSTALL_PREFIX}/lib")

    message(STATUS "Building Shared library: lib${LIBTARGET}")

endif()


message(STATUS "Using Boost Version: ${Boost_VERSION}")
message(STATUS "Boost Headers: ${Boost_INCLUDE_DIRS}")

###
# RPATH
#
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

# install library 
install(TARGETS rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/")

# symbolic link library version to the generic name
install(CODE "EXECUTE_PROCESS(COMMAND ln -sf ${CMAKE_INSTALL_PREFIX}/lib/lib${LIBTARGET}.so ${CMAKE_INSTALL_PREFIX}/lib/librapp.so)")
message(STATUS "Installing library in: `${CMAKE_INSTALL_PREFIX}`")

# Headers go under /usr/loca/include
message(STATUS "Installing Headers in: `${CMAKE_INSTALL_PREFIX}/include`")
install(DIRECTORY ${INCLUDES}/ DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}" FILES_MATCHING PATTERN "*.hpp" PATTERN "*.ihh" PATTERN "*.impl")

###
#   build tests - run with `make test`
###
if (${BUILD_TESTS})
    find_package(Boost 1.49 COMPONENTS unit_test_framework REQUIRED)
    enable_testing()
    add_definitions(-DBOOST_TEST_DYN_LINK)
    set(TESTS ${TESTS} tests)
    set(TESTFILES ${TESTFILES} asio_classes.cpp 
                               json_classes.cpp 
                               object_classes.cpp
                               cloud_calls.cpp)
    set(TEST_DIR ${TEST_DIR} tests)
    message(STATUS "Building tests, they will be placed under directory `${CMAKE_CURRENT_BINARY_DIR}/${TEST_DIR}`")
    # create "/tests"
    add_custom_command(TARGET ${LIBTARGET} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_DIR})
    # symlink `/tests/data` instead of copying
    add_custom_command(TARGET ${LIBTARGET} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/${TESTS}/data ${TEST_DIR}/data)
    # iterate tests
    foreach(ITEM ${TESTFILES})
        string(REPLACE ".cpp" "" TARGET ${ITEM})
        add_executable(${TARGET} ${TESTS}/${ITEM})
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
        target_link_libraries(${TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${LIBTARGET})
        add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TARGET} ${TEST_DIR}/.)
        add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E remove ${TARGET})
        add_test(${TARGET} ${TEST_DIR}/${TARGET})
    endforeach(ITEM)
else()
    message(STATUS "Not Building tests. Enable them with `-DBUILD_TESTS=ON`")
endif()


###
#   build examples
###
if (${BUILD_EXAMPLES})
    set (EXAMPLES available_services.cpp
                  face_detect.cpp
                  human_detect.cpp
                  hazard_detect.cpp
                  qr_detect.cpp
                  light_detection.cpp
                  object_recognition.cpp
                  knowrob_ontology.cpp
                  picture_handling.cpp
                  text_to_speech.cpp
                  config.cpp
                  cognitive_games.cpp
                  geolocation.cpp
                  weather.cpp
                  path_planning.cpp
                  email_handling.cpp
                  news.cpp
                  set_noise_profile.cpp
                  speech_recognition_google.cpp
                  speech_recognition_sphinx4.cpp)
    set(EXAMPLE_DIR ${EXAMPLE_DIR} examples)
    message(STATUS "Building examples, they will be placed under `${CMAKE_CURRENT_BINARY_DIR}/${EXAMPLE_DIR}`")

    # create "/examples"
    add_custom_command(TARGET ${LIBTARGET} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E make_directory ${EXAMPLE_DIR})
    # symlink `/tests/data` instead of copying
    add_custom_command(TARGET ${LIBTARGET} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/tests/data ${EXAMPLE_DIR}/data)
    # iterate tests
    foreach(ITEM ${EXAMPLES})
        string(REPLACE ".cpp" "" TARGET ${ITEM})
        add_executable(${TARGET} ${EXAMPLE_DIR}/${ITEM})
        target_link_libraries(${TARGET} ${LIBTARGET} ${CMAKE_THREAD_LIBS_INIT})
        add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TARGET} ${EXAMPLE_DIR}/.)
        add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E remove ${TARGET})
    endforeach(ITEM)
else()
    message(STATUS "Not Building examples. Enable them with `-DBUILD_EXAMPLES=ON`")
endif()

####
set(CMAKE_COLOR_MAKEFILE on)
set(CMAKE_VERBOSE_MAKEFILE off)

####
# Get from arguments if Debug is requested
#
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    message(STATUS "Building: ${CMAKE_BUILD_TYPE}. Ommit flag to change to `Release`")
else()
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    message(STATUS "Building: ${CMAKE_BUILD_TYPE}. Add flag `-DCMAKE_BUILD_TYPE=Debug` to switch to `Debug`")
endif()

message (STATUS "Platform is `${CMAKE_SYSTEM_NAME}`" )

####
# Linux should be the default OS/Platform for RAPP::API 
# We need g++ 4.9 or higher, else json won't work
# We could support 4.8.4 using c++1y only if we change json library.
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # get compiler version
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    # Check GCC supports C++14
    if (GCC_VERSION VERSION_GREATER 4.9 OR GCC_VERSION VERSION_EQUAL 4.9)
        message(STATUS "Compiler: g++ version >= 4.9 using C++14")  
    elseif ()
        message (FATAL_ERROR "g++ version >= 4.9 is required")
    endif()
# OSX platform
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # get clang version
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (CLANG_VERSION_MAJOR VERSION_GREATER 3 OR CLANG_VERSION_MAJOR VERSION_EQUAL 3)
        message(STATUS "Info: Clang >= 3.0 using C++14")
    elseif ()
        message(FATAL_ERROR "Clang version >= 3.0 is required")
    endif()
# Intel Compiler May run on Linux - Maybe we should support it
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message (FATAL_ERROR "unsupported compiler")
# We cannot support Microsoft Visual Studio - We cannot support Win32 platforms
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message (FATAL_ERROR "unsupported compiler")
endif()

message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
message(STATUS "CXX Linker: " ${CMAKE_EXE_LINKER_FLAGS})
