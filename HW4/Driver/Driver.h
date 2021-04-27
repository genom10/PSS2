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
public:
    int id;
    std::string login;
    std::string password;
    std::string name;
    int rating;
    std::string orderHistory;
    std::vector<Car> cars;
    std::string carTypes;
    Driver(std::string login, std::string password, std::string name, std::string carTypes){
        id = -1;
        this->login = std::move(login);
        this->password = std::move(password);
        this->name = std::move(name);
        rating = 0;
        orderHistory = "";

        std::stringstream ss(carTypes);
        std::string token;
        while (std::getline(ss, token, ',')) {
            cars.push_back(Car(token));
        }

        this->carTypes = carTypes;
    }

public:
    Driver(std::tuple <int, std::string, std::string, std::string, int, std::string, std::string>);
    Driver() = default;

    std::vector<Car> getCars();
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
