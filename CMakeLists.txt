cmake_minimum_required(VERSION 3.21)
project(HW3_clion)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW3_clion
        HealthPoints.cpp
        HealthPoints.h
        HealthPointsExampleTest.cpp
        Queue.h
        QueueExampleTests.cpp
        TestMain.cpp
        TestUtils.h)
