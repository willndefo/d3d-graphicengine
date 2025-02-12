cmake_minimum_required (VERSION 3.8)

# Project name
project ("d3d-graphicengine")

# CMAKE options
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
endif()

set(CMAKE_CXX_STANDARD 20)

# compiler version check
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message (STATUS "Using MSVC Version, ${MSVC_VERSION}")
else()
	message(FATAL_ERROR "Compiler not supported")
endif()

# Output directories
add_subdirectory ("src")
