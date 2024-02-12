cmake_minimum_required(VERSION 3.27)
project(a1_starting_code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(a1_starting_code
        ingredient.cpp
        ingredient.h
        main.cpp
        noodle.cpp
        noodle.h
        pork.cpp
        pork.h
        ramenRestaurant.cpp
        ramenRestaurant.h
        soup.cpp
        soup.h)
