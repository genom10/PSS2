cmake_minimum_required(VERSION 3.17)
project(Admin)

set(CMAKE_CXX_STANDARD 17)

add_executable(Admin main.cpp Admin.cpp Admin.h AdminGateway.cpp AdminGateway.h)