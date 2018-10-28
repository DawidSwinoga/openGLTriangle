cmake_minimum_required(VERSION 3.12)
project(Ex1)

set(CMAKE_CXX_STANDARD 14)

add_executable(triangle main.cpp)

target_link_libraries(triangle libopengl32.a libglu32.a libfreeglut.a)