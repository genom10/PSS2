cmake_minimum_required(VERSION 3.17)
project(Passenger)

set(CMAKE_CXX_STANDARD 17)

add_executable(Passenger main.cpp ../includes/sqlite_orm.h ../includes/sqlite3.c ../includes/sqlite3.h  ../includes/sqlite3ext.h Passenger.cpp Passenger.h PassengerGateway.cpp PassengerGateway.h PassengerStorage.h Driver.cpp Driver.h)