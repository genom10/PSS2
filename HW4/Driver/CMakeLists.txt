cmake_minimum_required(VERSION 3.17)
project(Driver)

set(CMAKE_CXX_STANDARD 17)

add_executable(Driver main.cpp Car.cpp Car.h ../includes/sqlite_orm.h ../includes/sqlite3.c ../includes/sqlite3.h  ../includes/sqlite3ext.h Driver.cpp Driver.h DriverGateway.cpp DriverGateway.h PassengerStorage.h)