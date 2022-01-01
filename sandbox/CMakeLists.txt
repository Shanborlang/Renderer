cmake_minimum_required(VERSION 3.17)
project(Renderer)

include(../cmake/CommonMacros.txt)
include_directories(../engine/include)

SETUP_APP(Renderer "")

target_link_libraries(Renderer PRIVATE engineLib)