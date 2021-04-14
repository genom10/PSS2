//
// Created by egord on 13.04.2021.
//

#ifndef DRIVER_CAR_H
#define DRIVER_CAR_H

#include <string>

class Car {
public:
    std::string carType;
    std::string getCarType();
    Car() = default;
    Car(std::string);
};


#endif //DRIVER_CAR_H
