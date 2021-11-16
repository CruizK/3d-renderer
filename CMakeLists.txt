cmake_minimum_required(VERSION 3.16)

project(Sandbox VERSION 1.0 LANGUAGES CXX)

#GLFW Build Settings
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

add_subdirectory(deps/glfw-3.3.4)
add_subdirectory(deps/glad)
add_subdirectory(deps/spdlog-1.9.2)
add_subdirectory(deps/glm)
add_subdirectory(deps/stb_image)
add_subdirectory(deps/imgui)

file(GLOB_RECURSE SRC_FILES "src/*.h" "src/*.cpp")

set_target_properties(
  glfw
  glad
  spdlog
  stb_image
  imgui
  uninstall
  PROPERTIES
    FOLDER "deps"
)

add_executable(Sandbox ${SRC_FILES})

target_include_directories(Sandbox PRIVATE src)
target_compile_features(Sandbox PUBLIC cxx_std_11)
target_link_libraries(Sandbox PUBLIC glfw OpenGL::GL glad spdlog stb_image glm imgui)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
