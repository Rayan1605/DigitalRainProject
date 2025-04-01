cmake_minimum_required(VERSION 3.20)  # Adjusted to a more common version
project(DigitalRainProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(DigitalRainProject
        main.cpp
        RainDrop.cpp
        RainDrop.h
)