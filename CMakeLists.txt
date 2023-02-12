cmake_minimum_required(VERSION 3.24)
project(COMP345_Assigment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(COMP345_Assigment1
        Cards.cpp
        Cards.h
        CardsDriver.cpp
        Continent.cpp
        Continent.h
        Coordinate.cpp
        Coordinate.h
        driver.cpp
        Maps.cpp
        Maps.h
        Orders.h
        Player.cpp
        Player.h
        PlayerDriver.cpp
        Territory.cpp
        Territory.h)
