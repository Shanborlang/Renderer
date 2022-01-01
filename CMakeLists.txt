cmake_minimum_required(VERSION 3.17)
project(Renderer)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(third_party/glfw)
include_directories(third_party/glfw/include)

# glad
include_directories(third_party/glad/include)
set(GLAD_SOURCES "third_party/glad/src/glad.c")
add_library("glad" ${GLAD_SOURCES})

# CMAKE_DIR to find external dependecies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# GLM
include_directories("${CMAKE_SOURCE_DIR}/third_party/glm")

add_subdirectory(engine)

add_subdirectory(sandbox)