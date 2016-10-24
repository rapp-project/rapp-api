# - Config file for the RAPP package
# It defines the following variables
#  RAPP_INCLUDE_DIRS - include directories for FooBar
#  RAPP_LIBRARIES    - libraries to link against
#  RAPP_EXECUTABLE   - the bar executable

# Compute paths
get_filename_component(RAPP_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(RAPP_CMAKE_DIR "${RAPP_CMAKE_DIR}/../../../")
get_filename_component(RAPP_CMAKE_DIR ${RAPP_CMAKE_DIR} ABSOLUTE)

if(EXISTS ${RAPP_CMAKE_DIR}/lib/librapp.a) 
  set(RAPP_STATIC_LIBRARIES
    ${RAPP_CMAKE_DIR}/lib/librapp.a
    CACHE INTERNAL "" FORCE
  )
endif()

if(EXISTS ${RAPP_CMAKE_DIR}/lib/librapp.so)
  set(RAPP_LIBRARIES
    ${RAPP_CMAKE_DIR}/lib/librapp.so
    CACHE INTERNAL "" FORCE
  )
endif()

set(RAPP_INCLUDE_DIRS
${RAPP_CMAKE_DIR}/include
CACHE INTERNAL "" FORCE
)
