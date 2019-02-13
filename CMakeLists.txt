########## *_* Linux Keylogger Project *_* ########
cmake_minimum_required (VERSION 2.6)       ########
project (test)                             ########
###################################################

set(CMAKE_VERBOSE_MAKEFILE on)

message("Proj_src_dir is ${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}/src) 
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

add_executable(test key.cpp)

target_link_libraries(test keylog)
target_link_libraries(test pthread)
target_link_libraries(test X11)


