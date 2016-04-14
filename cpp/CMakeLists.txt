# @date January 2016
# @author Alex Giokas <a.gkiokas@ortelio.co.uk>
# 
# Command line arguments you can use:
#       -DBUILD_RAPP_SHARED_LIBS=ON (Default: compile a shared librapp)
#       -DBUILD_RAPP_STATIC_LIBS=ON (Optional: compile a static librapp)
#       -DBUILD_TESTS=ON            (Optional: compile various tests - run with `make test`)
#       -DBUILD_EXAMPLES=ON         (Optional: compile various examples)
#       -DCMAKE_BUILD_TYPE=Debug    (Optional: enable debug symbols)
#       -DSTATIC_LIBSTD=ON          (Optional: compile statically against libstdc++)
#       -DOPEN_NAO=ON               (Optional: compiling on OpenNAO requires additional CXX flags)
#		-DCMAKE_INSTALL_PREFIX=/usr	(Optional: specify the install directory)  
#
# After succesfull compilation, run as su/sudo: `make install`
# 
PROJECT(rapp)
set (RAPP_VERSION_MAJOR 0)
set (RAPP_VERSION_MINOR 2)
cmake_minimum_required(VERSION 2.8)
set(LIBRARY_PATH ${LIBRARY_PATH}
		      /lib
		      /usr/lib
		      /usr/lib64
		      /usr/local/lib
		      /usr/local/lib64
		      /usr/lib/x86_64-linux-gnu)
set(INCLUDE_HEADERS ${INCLUDE_HEADERS} /usr/include/)
include_directories(SYSTEM ${INCLUDE_HEADERS})
set (INCLUDES ${INCLUDES} includes)
add_subdirectory(${INCLUDES})

# Library-only Executables -
set (SOURCES ${SOURCES} ${INCLUDES}/cloud/service_controller/service_controller.cpp)

# Find PThreads (needed by Boost)
find_package(Threads REQUIRED)

# Find Boost
find_package(Boost 1.49 COMPONENTS system thread random unit_test_framework program_options REQUIRED)

# Find libcrypt / libssl
find_package(OpenSSL REQUIRED)
if( OPENSSL_FOUND )
    include_directories(${OPENSSL_INCLUDE_DIRS})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
else()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif()

# Set library sources
add_library(lrapp OBJECT ${SOURCES})

# Static Library - only if asked
if (${RAPP_STATIC})
    message(STATUS "Building static library")
    add_library (rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static STATIC $<TARGET_OBJECTS:lrapp>)
    target_link_libraries(rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    set(LIBOBJ ${LIBOBJ} rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static)

	# TODO: check if param for install location has been passed
    install (TARGETS rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static  DESTINATION /usr/local/lib/)
    install(CODE "EXECUTE_PROCESS(COMMAND ln -sf librapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static.a librapp.a 
WORKING_DIRECTORY /usr/local/lib)")
endif()
# Shared Library - By default or if asked
if ((${RAPP_SHARED}) OR (NOT (${RAPP_STATIC})))
    message(STATUS "Building shared library, you can enable static lib with \"-DRAPP_STATIC=ON\"")
    add_library(rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} SHARED $<TARGET_OBJECTS:lrapp>)
    target_link_libraries(rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    set(LIBOBJ ${LIBOBJ} rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})

	# TODO: Check if param for install location has been passed
    install(TARGETS rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} DESTINATION /usr/local/lib/)
    install(CODE "EXECUTE_PROCESS(COMMAND ln -sf librapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}.so librapp.so 
WORKING_DIRECTORY /usr/local/lib)")
endif()

# TODO: check params for intall location of headers

# Header install dir
install (DIRECTORY ${INCLUDES}/ DESTINATION /usr/local/include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.hpp" PATTERN "*.ihh")
# Install Global header
install (FILES ${PROJECT_NAME} DESTINATION /usr/local/include/${PROJECT_NAME}) #copy global include header

if (${BUILD_EXAMPLES})
    set (EXAMPLES ${EXAMPLES} examples)
    add_executable(face_detect  ${EXAMPLES}/face_detect.cpp)
    add_executable(qr_detect    ${EXAMPLES}/qr_detect.cpp)
    add_executable(speech_recog ${EXAMPLES}/speech_to_text.cpp)
    add_executable(ontology     ${EXAMPLES}/ontology_example.cpp)
    add_executable(set_denoise  ${EXAMPLES}/set_denoise_example.cpp)
    add_executable(picture      ${EXAMPLES}/picture_example.cpp)
    add_executable(asio_tls     ${EXAMPLES}/asio_tls.cpp)

    target_link_libraries(face_detect  ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${LIBOBJ})
    target_link_libraries(qr_detect    ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${LIBOBJ})
    target_link_libraries(speech_recog ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${LIBOBJ})
    target_link_libraries(ontology     ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${LIBOBJ})
    target_link_libraries(set_denoise  ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${LIBOBJ})
	target_link_libraries(asio_tls	   ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${LIBOBJ})
    message(STATUS "Building examples, they will be placed in the `build` directory")
else()
    message(STATUS "Not Building examples - enable with `-DBUILD_EXAMPLES=ON`")
endif()


# build tests
if (${BUILD_TESTS})
    set (TESTS ${TESTS} tests)
    enable_testing ()
    add_executable(object_test          ${TESTS}/object_test.cpp)
    add_executable(cloud_test           ${TESTS}/cloud_test.cpp)
    add_executable(service_test         ${TESTS}/service_test.cpp)
    add_test(unit_object_test            object_test) 
    add_test(unit_cloud_test             cloud_test) 
    add_test(unit_service_test           service_test)
    target_link_libraries(object_test    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 
                                         rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
    target_link_libraries(service_test   ${CMAKE_THREAD_LIBS_INIT} 
                                         ${Boost_SYSTEM_LIBRARY}
                                         ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 
                                         rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
    target_link_libraries(cloud_test     ${CMAKE_THREAD_LIBS_INIT}
                                         ${Boost_SYSTEM_LIBRARY}
                                         ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 
                                         rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
    message(STATUS "Building tests, they will be placed in the `build` directory")
else()
    message(STATUS "Not Building tests - enable with `-DBUILD_TESTS=ON`")
endif()
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 
set(CMAKE_COLOR_MAKEFILE on)
set(CMAKE_VERBOSE_MAKEFILE on)
# Get from arguments if Debug is requested
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
    message(STATUS "Building: ${CMAKE_BUILD_TYPE} - ommit flag to change to `Release`")
else()
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "Building: ${CMAKE_BUILD_TYPE} - add `-DCMAKE_BUILD_TYPE=Debug` to switch to `Debug`")
endif()
# Linux should be the default OS/Platform for RAPP::API
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC/Linux
    message (STATUS "GCC/Linux" )
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
        message(STATUS "COMPILER: g++ version >= 4.7 using C++11")  
    elseif ()
        message (FATAL_ERROR "g++ version >= 4.7 is required")
    endif()
    if (${STATIC_LIBSTD})
        set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11 -Wall -fPIC -static-libstdc++")
    else()
        set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11 -Wall -fPIC")
    endif()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    # TODO: can somebody with a NAO test this?
    if (${OPEN_NAO})
        set(CMAKE_EXE_LINKER_FLAGS "-lc++ -lcxxrt")
        set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11 -Wall -fPIC -static-libstdc++ -m32")
    endif()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mtune=native -march=native")
    set(BUILD_SHARED_LIBS OFF)
    message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
    message(STATUS "CXX Linker: " ${CMAKE_EXE_LINKER_FLAGS})
# OSX ?!
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
    message (STATUS "Clang/OSX" )
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (CLANG_VERSION_MAJOR VERSION_GREATER 3 OR CLANG_VERSION_MAJOR VERSION_EQUAL 3)
        message(STATUS "Info: Clang >= 3.0 using C++11")
    elseif ()
        message(FATAL_ERROR "Clang version >= 3.0 is required")
    endif()
        set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -Wall")
        message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mtune=native -march=native")
        set(BUILD_SHARED_LIBS OFF)
        message(STATUS "CXX Linker: " ${CMAKE_EXE_LINKER_FLAGS})
# Intel Compiler May run on Linux - Maybe we should support it
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message (FATAL_ERROR "unsupported compiler")
# We cannot support Microsoft Visual Studio - We cannot support Win32 platforms
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message (FATAL_ERROR "unsupported compiler")
endif()

# TODO: install location
