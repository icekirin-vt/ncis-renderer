cmake_minimum_required(VERSION 4.2)
project(core)

set(C_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH "../bin/")

find_package( OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/glfw")
add_subdirectory("vendor/cglm")

# TODO: replace globs with individual filenames

add_executable(core)
target_sources(core PRIVATE 
		"src/main.c"
		"vendor/glad/glad.c"
)
target_include_directories(core PRIVATE "src/include")


target_include_directories(core PRIVATE "vendor/glad/" "vendor/glfw/include" "vendor/cglm/include")

target_link_libraries(core glfw cglm)
