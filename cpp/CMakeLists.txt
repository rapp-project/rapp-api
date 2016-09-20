# @date January 2016
# @author Alex Giokas <a.gkiokas@ortelio.co.uk>
# 
# Command line arguments you can use:
#       -DBUILD_RAPP_SHARED=ON		                    (Default: compile a shared librapp)
#       -DBUILD_RAPP_STATIC=ON		                    (Optional: compile a static librapp)
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
set(CMAKE_MACOSX_RPATH 1)

# include everything from "/includes"
include_directories("includes")

# Library-only Executables -
set (SOURCES ${SOURCES} 
                        ${INCLUDES}/cloud/asio/asio_handler/asio_handler.cpp
                        ${INCLUDES}/cloud/asio/asio_http/asio_http.cpp
                        ${INCLUDES}/cloud/asio/asio_https/asio_https.cpp
						${INCLUDES}/config/config.cpp)

# Find PThreads (needed by Boost)
find_package(Threads REQUIRED)

# Find Boost
find_package(Boost 1.49 COMPONENTS system thread random unit_test_framework program_options regex filesystem REQUIRED)
if (Boost_FOUND)
	if (${RAPP_STATIC})
		set(Boost_USE_STATIC_LIBS ON)
	else()
		set(Boost_USE_STATIC_LIBS OFF)
	endif()
    include_directories(${Boost_INCLUDE_DIR})
    message(STATUS "Using Boost Version: ${Boost_VERSION}")
    message(STATUS "Boost Headers: ${Boost_INCLUDE_DIRS}")
endif()

# Find libcrypt / libssl
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    message(STATUS "Using OpenSSL Version: ${OPENSSL_VERSION}")
	message(STATUS "OpenSSL Headers: ${OPENSSL_INCLUDE_DIR}")
endif()

# Set library sources
add_library(lrapp OBJECT ${SOURCES})

# user has set install location
if (CMAKE_INSTALL_PREFIX)
	message(STATUS "Installing library in: `${CMAKE_INSTALL_PREFIX}`")
# user did not set it - revert to "/usr/local"
else()
	set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} "/usr/local/")
    message(STATUS "Installing library in `${CMAKE_INSTALL_PREFIX}`")
endif()	

# Static Library - only if asked
if (${RAPP_STATIC})
	message(STATUS "Building Static library")
    add_library (rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static STATIC $<TARGET_OBJECTS:lrapp>)
    target_link_libraries(rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    set(LIBOBJ ${LIBOBJ} rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static)
	install(TARGETS rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static  DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/")
	install(CODE "EXECUTE_PROCESS(COMMAND ln -sf librapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static.a librapp.a WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)")
endif()

# Shared Library - By default or if asked
if ((${RAPP_SHARED}) OR (NOT (${RAPP_STATIC})))
	message(STATUS "Building Shared library, you can enable static lib with \"-DRAPP_STATIC=ON\"")
    add_library(rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} SHARED $<TARGET_OBJECTS:lrapp>)
    target_link_libraries(rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
    set(LIBOBJ ${LIBOBJ} rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
	install(TARGETS rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/")
	install(CODE "EXECUTE_PROCESS(COMMAND ln -sf librapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}.so librapp.so WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)")
endif()

if (CMAKE_INSTALL_PREFIX)
	message(STATUS "Installing Headers in: `${CMAKE_INSTALL_PREFIX}/include`")
endif()

# Header install dir
install (DIRECTORY ${INCLUDES}/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.hpp" PATTERN "*.ihh")

# Install Global header
install (FILES ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}) #copy global include header

if (${BUILD_EXAMPLES})
    set (EXAMPLES ${EXAMPLES} examples)
    add_executable(face_detect      ${EXAMPLES}/face_detect.cpp)
    add_executable(qr_detect        ${EXAMPLES}/qr_detect.cpp)
    add_executable(speech_recog     ${EXAMPLES}/speech_to_text.cpp)
    add_executable(ontology         ${EXAMPLES}/ontology_example.cpp)
    add_executable(set_denoise      ${EXAMPLES}/set_denoise_example.cpp)
    add_executable(picture          ${EXAMPLES}/picture_example.cpp)
    add_executable(asio_tls         ${EXAMPLES}/asio_tls.cpp)
    add_executable(text_to_speech   ${EXAMPLES}/text_to_speech.cpp)
    add_executable(service_example  ${EXAMPLES}/service_example1.cpp)
	add_executable(config_example	${EXAMPLES}/config.cpp)
	add_executable(available_services ${EXAMPLES}/available_services.cpp)
	add_executable(cognitive_example  ${EXAMPLES}/cognitive_example.cpp)
	add_executable(planner_example 	${EXAMPLES}/path_planner.cpp)

    target_link_libraries(face_detect       ${LIBOBJ} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
    target_link_libraries(qr_detect         ${LIBOBJ} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
    target_link_libraries(speech_recog      ${LIBOBJ} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
    target_link_libraries(ontology          ${LIBOBJ} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
    target_link_libraries(set_denoise       ${LIBOBJ} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
	target_link_libraries(asio_tls	        ${LIBOBJ} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
    target_link_libraries(text_to_speech    ${LIBOBJ} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
    target_link_libraries(service_example   ${LIBOBJ} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
	target_link_libraries(config_example	${LIBOBJ})
	target_link_libraries(available_services ${LIBOBJ})
	target_link_libraries(cognitive_example ${LIBOBJ})
	target_link_libraries(planner_example ${LIBOBJ})

    message(STATUS "Building examples, they will be placed in `${CMAKE_CURRENT_BINARY_DIR}`")
else()
    message(STATUS "Not Building examples - enable with `-DBUILD_EXAMPLES=ON`")
endif()

# build tests
if (${BUILD_TESTS})
    set (TESTS ${TESTS} tests)
    enable_testing ()
    add_executable(object_test           ${TESTS}/object_test.cpp)
    add_executable(service_test          ${TESTS}/service_test.cpp)
    add_executable(serialise_test        ${TESTS}/serialise.cpp)

    add_test(unit_object_test            object_test) 
    add_test(unit_service_test           service_test)
    add_test(json_serialise_test         serialise_test)

    target_link_libraries(object_test    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 
                                         rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
    target_link_libraries(service_test   ${CMAKE_THREAD_LIBS_INIT} 
                                         ${Boost_SYSTEM_LIBRARY}
                                         ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 
                                         rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
    target_link_libraries(serialise_test rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR})
    message(STATUS "Building tests, they will be placed in the `${CMAKE_CURRENT_BINARY_DIR}`")
else()
    message(STATUS "Not Building tests - enable with `-DBUILD_TESTS=ON`")
endif()

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 
set(CMAKE_COLOR_MAKEFILE on)
set(CMAKE_VERBOSE_MAKEFILE off)

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
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -fPIC -static-libstdc++")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -fPIC")
    endif()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

    # TODO: can somebody with a NAO test this?
    if (${OPEN_NAO})
        #set(CMAKE_EXE_LINKER_FLAGS "-lc++ -lcxxrt")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -fPIC -static-libstdc++ -m32")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mtune=atom -march=atom")
    else()
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mtune=native -march=narive")
    endif()
    set(BUILD_SHARED_LIBS OFF)
    message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
    message(STATUS "CXX Linker: " ${CMAKE_EXE_LINKER_FLAGS})

# OSX platform
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


# Prepare the CMake config files
configure_file(cmake/RappConfig.cmake.in "${PROJECT_BINARY_DIR}/RappConfig.cmake" @ONLY)
configure_file(cmake/RappConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/RappConfigVersion.cmake" @ONLY)
 
# Install the CMake config files
install(FILES
  "${PROJECT_BINARY_DIR}/RappConfig.cmake"
  "${PROJECT_BINARY_DIR}/RappConfigVersion.cmake"
  "cmake/RappMacros.cmake"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/Rapp"
)

