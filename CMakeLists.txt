cmake_minimum_required(VERSION 3.19)
project(UIGL)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(glfw)


add_executable(UIGL main.cpp)

target_sources(UIGL PUBLIC
        TimeTrigger.cpp
        app/App.cpp
        app/dispatcher/Dispatcher.cpp
        Runtime.cpp
)
target_link_libraries(UIGL ${OPENGL_LIBRARIES} glfw)
