cmake_minimum_required(VERSION 3.22.0)

set(CMAKE_CXX_STANDARD 14)

project(chain_Of_Responsibility)

add_executable(chain_Of_Responsibility main.cpp logMessage.h logMessage.cpp)