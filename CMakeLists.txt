cmake_minimum_required(VERSION 4.2)
project(NCIS)

set(CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "../bin/")

find_package( OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/glfw")




file(GLOB_RECURSE SRC "src/*.cpp")
file(GLOB_RECURSE HDR "src/include/*.hpp")


add_executable(core ${SRC} ${HDR} "vendor/glad/glad.c")


target_include_directories(core PRIVATE "vendor/glad/")
target_include_directories(core PRIVATE "vendor/glfw/include")

target_link_libraries(core glfw)
