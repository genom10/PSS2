//
// Created by egord on 4/14/2021.
//

#ifndef DRIVER_DRIVER_H
#define DRIVER_DRIVER_H

#include <iostream>
#include <utility>
#include "../includes/sqlite_orm.h"
#include "Car.h"

using namespace sqlite_orm;


class Driver{
protected:
    int id;
    std::string login;
    std::string password;
    std::string name;
    int rating;
    std::string orderHistory;
    Car car;
    std::string carType;
    Driver(std::string login, std::string password, std::string name, std::string carType){
        id = -1;
        this->login = std::move(login);
        this->password = std::move(password);
        this->name = std::move(name);
        rating = 0;
        orderHistory = "";
        car.carType = carType;
        this->carType = carType;
    }

public:
    Driver(std::tuple <int, std::string, std::string, std::string, int, std::string, std::string>);
    Driver() = default;

    Car getCar();
    static void ListAll();
    int getID() const;
    int getRating() const;
    static bool fetchLogin(std::string login);
    static Driver logIn(std::string login, std::string password);
    static Driver reg(std::string login, std::string password, std::string name, std::string carType);
    static void remove(Driver *passenger); //TODO remove from Order DB
    void addOrder(int i);
};
#endif //DRIVER_DRIVER_H
