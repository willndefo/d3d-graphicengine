cmake_minimum_required(VERSION 3.26)

# include 3rd party libraries
include("${CMAKE_SOURCE_DIR}/scripts/FetchLibraries.cmake")

# populate 3rd party libraries
FetchContent_MakeAvailable(glfw)

# create executable
file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/src/*.h" "${CMAKE_SOURCE_DIR}/src/*.cpp")
source_group("src" "${CMAKE_SOURCE_DIR}/src" ${SUBDIRECTORIES})
add_executable("src" main.cpp ${SUBDIRECTORIES})

# add directories and link libraries
target_include_directories("src" PRIVATE "${CMAKE_SOURCE_DIR}/src")

target_link_libraries("src" PRIVATE glfw)
target_link_libraries("src" PRIVATE d3d11.lib)
target_link_libraries("src" PRIVATE d3dcompiler.lib)
target_link_libraries("src" PRIVATE dxguid.lib)

# debug and release flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions("src" PUBLIC d3d-graphicengine-debug)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_definitions("src" PUBLIC d3d-graphicengine-release)
endif()

# macro definitions
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_definitions("src" PUBLIC RUNTIME_API=__delspec\(dllexport\))
	target_compile_definitions("src" PUBLIC FORCEINLINE=__forceinline)
else()
	message(FATAL_ERROR "Unsupported compiler")
endif()