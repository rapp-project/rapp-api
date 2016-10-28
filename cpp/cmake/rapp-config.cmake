# - Config file for the RAPP package
# It defines the following variables
#  RAPP_INCLUDE_DIRS - include directories for RAPP
#  RAPP_LIBRARIES    - libraries to link against
#  RAPP_STATIC_LIBRARIES - static libraries to link against

if(EXISTS ${CMAKE_INSTALL_PREFIX}/lib/librapp.a) 
  set(RAPP_STATIC_LIBRARIES
      ${CMAKE_INSTALL_PREFIX}/lib/librapp.a
      CACHE INTERNAL "" FORCE
  )
endif()

if(EXISTS ${CMAKE_INSTALL_PREFIX}/lib/librapp.so)
  set(RAPP_LIBRARIES
      ${CMAKE_INSTALL_PREFIX}/lib/librapp.so
      CACHE INTERNAL "" FORCE
  )
endif()

set(RAPP_INCLUDE_DIRS
    ${CMAKE_INSTALL_PREFIX}/include
    CACHE INTERNAL "" FORCE
)
