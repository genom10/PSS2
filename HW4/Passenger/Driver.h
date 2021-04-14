//
// Created by egord on 4/14/2021.
//

#ifndef PASSENGER_DRIVER_H
#define PASSENGER_DRIVER_H


#include <string>

class Driver {
public:
    int id;
    std::string login;
    std::string password;
    std::string name;
    int rating;
    std::string orderHistory;
    std::string carType;
};


#endif //PASSENGER_DRIVER_H
