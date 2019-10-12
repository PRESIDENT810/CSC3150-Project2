cmake_minimum_required(VERSION 3.13)
project(CSC3150_Assignment_2)

set(CMAKE_CXX_STANDARD 14)
include_directories('source')

add_executable(CSC3150_Assignment_2
        source/hw2.cpp
        source/Log.h
        source/Frog.h source/util.h)