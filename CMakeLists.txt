cmake_minimum_required(VERSION 3.20.2)
project(urban_logistics)

set(CMAKE_CXX_STANDARD 14)

add_executable(urban_logistics main.cpp Package.cpp Package.h Transport.cpp Transport.h Application.cpp Application.h Optimizer.cpp Optimizer.h FirstScenario.cpp FirstScenario.h SecondScenario.cpp SecondScenario.h ThirdScenario.cpp ThirdScenario.h FourthScenario.cpp FourthScenario.h FileReader.cpp FileReader.h)