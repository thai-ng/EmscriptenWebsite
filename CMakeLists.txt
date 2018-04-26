# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.5)
cmake_policy(SET CMP0015 NEW)

project (CppWeb)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build.emscripten)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include sub-projects.
add_subdirectory ("src")
target_include_directories(CppWeb PUBLIC include)

set_target_properties(CppWeb PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 --bind")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/publics/ DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build.emscripten)