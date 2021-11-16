cmake_minimum_required(VERSION 3.2)

project(imgui)

set(SOURCES 
    "src/imgui.cpp"
    "src/imgui_draw.cpp"
    "src/imgui_impl_opengl3.cpp"
    "src/imgui_impl_glfw.cpp"
    "src/imgui_widgets.cpp"
    "src/imgui_demo.cpp"
)

set(HEADERS
    "include/imgui/imconfig.h"
    "include/imgui/imgui.h"
    "include/imgui/imgui_impl_opengl3.h"
    "include/imgui/imgui_impl_glfw.h"
    "include/imgui/imgui_internal.h"
    "include/imgui/imstb_rectpack.h"
    "include/imgui/imstb_textedit.h"
    "include/imgui/imstb_truetype.h"
)


include_directories(include/imgui ../glad/include ../glfw-3.3.4/include)

add_library(imgui STATIC ${SOURCES} ${HEADERS})

target_include_directories(imgui PUBLIC include)

set_target_properties(imgui PROPERTIES
    COMPILE_DEFINITIONS IMGUI_IMPL_OPENGL_LOADER_GLAD
)