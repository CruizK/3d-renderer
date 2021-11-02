cmake_minimum_required(VERSION 3.1)

project(glad VERSION 1.0 LANGUAGES C)

set(SOURCE_LIST
  "src/glad.c"
  "include/glad/glad.h"
)

add_library(glad STATIC ${SOURCE_LIST})

target_include_directories(glad PUBLIC include)

# Mimic on Disk file structure to VS
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})