cmake_minimum_required(VERSION 3.20.2)
project(urban_logistics)

set(CMAKE_CXX_STANDARD 14)

add_executable(urban_logistics main.cpp Packages.cpp Packages.h Transport.cpp Transport.h Application.cpp Application.h)