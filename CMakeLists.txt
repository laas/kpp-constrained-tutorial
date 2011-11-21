# Requires at least CMake 2.6 to configure the package.
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE(cmake/cpack.cmake)
INCLUDE(cmake/base.cmake)
INCLUDE(cmake/boost.cmake)
INCLUDE(cmake/kineo.cmake)

SET(PROJECT_NAME kpp-constrained-tutorial)
SET(PROJECT_VERSION 0.1)
SET(PROJECT_DESCRIPTION "Insert package description here...")
SET(PROJECT_URL "Insert package webpage here...")


SET(${PROJECT_NAME}_HEADERS
  ${CMAKE_SOURCE_DIR}/include/kpp/constrained-tutorial/tutorial.hh
)

SET(CXX_DISABLE_WERROR 1)

SETUP_PROJECT()

ADD_REQUIRED_DEPENDENCY("hpp-constrained-planner")
ADD_REQUIRED_DEPENDENCY(kppInterface)

# Search for Boost.
SET(BOOST_COMPONENTS
  filesystem system thread program_options unit_test_framework)
SEARCH_FOR_BOOST()

SET(PKG_CONFIG_LIBS "")

SET(KINEO_ADDON_SOURCES
  src/tutorial.cc
)

KINEO_ADDON(${PROJECT_NAME})

PKG_CONFIG_USE_DEPENDENCY(${PROJECT_NAME} hpp-constrained-planner)
PKG_CONFIG_USE_DEPENDENCY(${PROJECT_NAME} kppInterface)

# Documentation produced by doxygen
INCLUDE(FindDoxygen)
IF(DOXYGEN_FOUND)
  add_subdirectory(doc)
ENDIF(DOXYGEN_FOUND)

SETUP_PROJECT_FINALIZE()
SETUP_PROJECT_CPACK()