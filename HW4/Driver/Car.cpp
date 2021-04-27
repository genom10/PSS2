//
// Created by egord on 13.04.2021.
//

#include "Car.h"

Car::Car(std::string carType) {
    this->carType = carType;
}

std::string Car::getCarType() {
    return carType;
}
