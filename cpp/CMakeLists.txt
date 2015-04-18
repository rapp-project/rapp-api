PROJECT(RAPP)

set (RAPP_VERSION_MAJOR 0)
set (RAPP_VERSION_MINOR 1)

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

add_subdirectory(src)

# Face Detect Test
add_executable ( rapp_face_detect  tests/face_detect.cpp
                                   src/service/asio_service_raw/asio_service_raw.cpp
                                   src/service/service_controller/service_controller.cpp
                                   src/cloud/faceDetector/faceDetector.cpp
                                   src/objects/picture/picture.cpp)

# Qr Code Detect Test
add_executable ( rapp_qr_detect    tests/qr_detect.cpp
                                   src/service/asio_service_raw/asio_service_raw.cpp
                                   src/service/service_controller/service_controller.cpp
                                   src/cloud/qrDetector/qrDetector.cpp
                                   src/objects/picture/picture.cpp)

# Fetch Data Test
add_executable ( rapp_fetch_data   tests/fetch_data.cpp
                                   src/service/asio_service_http/asio_service_http.cpp
                                   src/service/service_controller/service_controller.cpp)
# Ontology Subclass Of Test
add_executable ( rapp_ontology_test tests/ontology_test.cpp
                                   src/service/asio_service_http/asio_service_http.cpp
                                   src/service/service_controller/service_controller.cpp)

# Find Libaries for which Cmake already has a meta-package
find_package( Threads REQUIRED )
find_package( Boost 1.49 COMPONENTS system thread REQUIRED )

# Build Libraries (both static and shared)
set (SOURCES ${SOURCES} src/service/asio_service_http/asio_service_http.cpp
                        src/service/asio_service_raw/asio_service_raw.cpp
                        src/service/service_controller/service_controller.cpp
                        src/cloud/faceDetector/faceDetector.cpp
                        src/cloud/qrDetector/qrDetector.cpp
                        src/objects/picture/picture.cpp)

# Set library sources
add_library (lrapp OBJECT ${SOURCES})

# Shared Library
add_library (rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} SHARED $<TARGET_OBJECTS:lrapp>)
target_link_libraries(rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} ${Boost_SYSTEM_LIBRARY})

# Static Library
add_library (rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static STATIC $<TARGET_OBJECTS:lrapp>)
target_link_libraries(rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static ${Boost_SYSTEM_LIBRARY})



# Link Tests/Examples
target_link_libraries( rapp_face_detect ${CMAKE_THREAD_LIBS_INIT} ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} )
target_link_libraries( rapp_qr_detect ${CMAKE_THREAD_LIBS_INIT} ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} )
target_link_libraries( rapp_fetch_data ${CMAKE_THREAD_LIBS_INIT} ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} )
target_link_libraries( rapp_ontology_test ${CMAKE_THREAD_LIBS_INIT} ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} )



set(CMAKE_COLOR_MAKEFILE on)
set(CMAKE_VERBOSE_MAKEFILE on)

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)



# Linux should be the default OS/Platform for RAPP::API
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  
  # using GCC/Linux
  message (STATUS "GCC/Linux" )
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  
  if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
    message(STATUS "Info: g++ version >= 4.7 using C++11")
  
  elseif ()
    message (FATAL_ERROR "g++ version >= 4.7 is required")
  endif()
  
  # Do I need this ?
  #add_definitions(-DBOOST_THREAD_USE_LIB)
  
  # NOTE: gnu++11 enables GNU's violating options, whereas c++11 is strictly only the new version
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11 -Wall -fPIC")
  message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mtune=native -march=native") # -s ?
  set(BUILD_SHARED_LIBS OFF)
  message(STATUS "CXX Linker: " ${CMAKE_EXE_LINKER_FLAGS})

# Intel Compiler May run on Linux - Maybe we should support it
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message (FATAL_ERROR "unsupported compiler")

# We cannot support Microsoft Visual Studio - We cannot support Win32 platforms
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message (FATAL_ERROR "unsupported compiler")
endif()

#set(MACOSX_RPATH ON)

# Install stuff
install (TARGETS rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR}-static  DESTINATION /usr/local/lib/)
install (TARGETS rapp.${RAPP_VERSION_MAJOR}.${RAPP_VERSION_MINOR} DESTINATION /usr/local/lib/)
install (DIRECTORY src/ DESTINATION /usr/local/include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.hpp" PATTERN "*.ihh")

#install (FILES includes/cgpp DESTINATION /usr/local/include/${PROJECT_NAME}) - TODO: Use to install a global include header
