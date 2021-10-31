cmake_minimum_required(VERSION 3.17)
project(engineLib CXX C)

include(../cmake/CommonMacros.txt)

include_directories(../third_party/glfw/include)
include_directories(../third_party/glad/include)
include_directories(../third_party/glm)

include_directories(include)

file(GLOB_RECURSE SRC_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c??)
file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h??)

add_library(engineLib ${SRC_FILES} ${HEADER_FILES})

set_property(TARGET engineLib PROPERTY CXX_STANDARD 17)
set_property(TARGET engineLib PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(engineLib PUBLIC glad glfw)