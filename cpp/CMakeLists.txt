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
set(INCLUDES ${INCLUDES} includes)

# set root at `/includes`
add_subdirectory(${INCLUDES})
set(CMAKE_MACOSX_RPATH 1)

message("Build directory: ${CMAKE_CURRENT_BINARY_DIR}")

# include everything from "/includes"
include_directories("includes")

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
            ${INCLUDES}/objects/time/time.cpp
            ${INCLUDES}/objects/quaternion/quaternion.cpp
            ${INCLUDES}/objects/point/point.cpp
            ${INCLUDES}/objects/pose/pose.cpp
            ${INCLUDES}/objects/msg_metadata/msg_metadata.cpp
            ${INCLUDES}/objects/pose_stamped/pose_stamped.cpp
            ${INCLUDES}/objects/planned_path/planned_path.cpp
            ${INCLUDES}/objects/human/human.cpp
            ${INCLUDES}/objects/face/face.cpp
            ${INCLUDES}/objects/picture/picture.cpp
            ${INCLUDES}/objects/audio/audio.cpp
            ${INCLUDES}/objects/qr_code/qr_code.cpp

            ${INCLUDES}/cloud/available_services/available_services.cpp
            ${INCLUDES}/cloud/cognitive_exercises/cognitive_exercises.cpp
            ${INCLUDES}/cloud/email/email.cpp
            ${INCLUDES}/cloud/geolocation/geolocation.cpp
            ${INCLUDES}/cloud/ontology/ontology.cpp
            ${INCLUDES}/cloud/vision/detection.cpp
            ${INCLUDES}/cloud/vision/recognition.cpp
            ${INCLUDES}/cloud/weather_report/weather_report.cpp
            ${INCLUDES}/cloud/navigation/path_planning/path_planning.cpp
            ${INCLUDES}/cloud/news/news.cpp
            ${INCLUDES}/cloud/speech/set_noise_profile.cpp
            ${INCLUDES}/cloud/speech/speech_detection_google.cpp
            ${INCLUDES}/cloud/speech/speech_detection_sphinx4.cpp
            )

# Begin searching for packgages we use in RAPP API
# Find PThreads (needed by Boost)
find_package(Threads REQUIRED)

###
# Find Boost - we use it for a variety of operations
#
find_package(Boost 1.49 COMPONENTS system thread random unit_test_framework program_options regex filesystem REQUIRED)
if (Boost_FOUND)
		
		set(Boost_USE_STATIC_LIBS OFF)
    include_directories(${Boost_INCLUDE_DIR})
    message(STATUS "Using Boost Version: ${Boost_VERSION}")
    message(STATUS "Boost Headers: ${Boost_INCLUDE_DIRS}")
endif()

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
if ((${RAPP_STATIC}) OR (${OPEN_NAO}))
    set(Boost_USE_STATIC_LIBS ON)
    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
    # static library - platform target (if this is running from Darwin/OSX it will fail without `i386-elf-gcc`)
    # for more info see: https://www.danirod.es/blog/i386-elf-gcc-on-mac.html
    # if the host platform is Linux/GCC then by default it will produce ELF 32bit binaries.
    if (${RAPP_STATIC})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fPIC")
    # static library - atom CPU - same as before, ELF targets need Linux/GCC host platform
    elseif (${OPEN_NAO})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fPIC -m32 -march=atom -mtune=atom")
    endif()
    # set target, add library - link with Boost and OpenSSL
    set(LIBTARGET ${LIBRARGET} rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static)
    add_library(${LIBTARGET} STATIC $<TARGET_OBJECTS:lrapp>)
    target_link_libraries(${LIBTARGET} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    message(STATUS "Building Static library: lib${LIBTARGET}")
    # install library
    install(TARGETS ${LIBTARGET}  DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/")
    # symbolic link library version to the generic name
    install(CODE "EXECUTE_PROCESS(COMMAND ln -sf lib${LIBTARGET} librapp.a WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)")
###
#   Shared Library - By default
###
else()
    # use shared boost - build shared libs - set correct flags
    set(Boost_USE_STATIC_LIBS OFF)
    set(BUILD_SHARED_LIBS ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fPIC")
    # build library first
    set(LIBTARGET ${LIBRARGET} rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
    add_library(${LIBTARGET} SHARED $<TARGET_OBJECTS:lrapp>)
    target_link_libraries(${LIBTARGET} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    message(STATUS "Building Shared library: lib${LIBTARGET}")
    # install library 
	install(TARGETS rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/")
    # symbolic link library version to the generic name
    install(CODE "EXECUTE_PROCESS(COMMAND ln -sf lib${LIBTARGET} librapp.so WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)")
endif()

###
#   Installation Directory - default or user defined
###
# user has set install location
if (CMAKE_INSTALL_PREFIX)
	message(STATUS "Installing library in: `${CMAKE_INSTALL_PREFIX}`")
# user did not set it - revert to "/usr/local"
else()
	set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} "/usr/local/")
    message(STATUS "Installing library in `${CMAKE_INSTALL_PREFIX}`")
endif()	

# Produce message
if (CMAKE_INSTALL_PREFIX)
	message(STATUS "Installing Headers in: `${CMAKE_INSTALL_PREFIX}/include`")
endif()

# Header install dir
install(DIRECTORY ${INCLUDES}/ DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME} FILES_MATCHING PATTERN "*.hpp" PATTERN "*.ihh")

# Install Global header
install(FILES ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}) #copy global include header

###
#   build tests - run with `make test`
###
if (${BUILD_TESTS})
    enable_testing()
    set(TESTS ${TESTS} tests)
    set(TESTFILES ${TESTFILES} asio_classes.cpp 
                               json_classes.cpp 
                               object_classes.cpp)
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
                  object_recognition.cpp
                  #speech_to_text.cpp
                  knowrob_ontology.cpp
                  picture_handling.cpp
                  #text_to_speech.cpp
                  config.cpp
                  cognitive_games.cpp
                  geolocation.cpp
                  weather.cpp
                  path_planning.cpp
                  email_handling.cpp
                  news.cpp
                  set_noise_profile.cpp
                  speech_detection_google.cpp
                  speech_detection_sphinx.cpp)
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
        target_link_libraries(${TARGET} ${LIBTARGET})
        add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TARGET} ${EXAMPLE_DIR}/.)
        add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E remove ${TARGET})
    endforeach(ITEM)

else()
    message(STATUS "Not Building examples. Enable them with `-DBUILD_EXAMPLES=ON`")
endif()


ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 
set(CMAKE_COLOR_MAKEFILE on)
set(CMAKE_VERBOSE_MAKEFILE off)

# Get from arguments if Debug is requested
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    message(STATUS "Building: ${CMAKE_BUILD_TYPE}. Ommit flag to change to `Release`")
else()
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mtune=native -march=native")
    message(STATUS "Building: ${CMAKE_BUILD_TYPE}. Add flag `-DCMAKE_BUILD_TYPE=Debug` to switch to `Debug`")
endif()

message (STATUS "Platform is `${CMAKE_SYSTEM_NAME}`" )

# Linux should be the default OS/Platform for RAPP::API
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # get compiler version
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    # Check GCC supports C++14
    if (GCC_VERSION VERSION_GREATER 4.9 OR GCC_VERSION VERSION_EQUAL 4.9)
        message(STATUS "COMPILER: g++ version >= 4.9 using C++14")  
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
