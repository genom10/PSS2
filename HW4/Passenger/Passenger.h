//
// Created by genom10 on 14.04.2021.
//

#ifndef PASSENGER_PASSENGER_H
#define PASSENGER_PASSENGER_H

#include <iostream>
#include <utility>
#include "../includes/sqlite_orm.h"

using namespace sqlite_orm;


class Passenger{
protected:
    int id;
    std::string login;
    std::string password;
    std::string name;
    int rating;
    std::string orderHistory;
    std::string paymentMethods;
    std::string pinnedAddresses;
    bool canOrder;
    Passenger(std::string login, std::string password, std::string name){
        id = -1;
        this->login = std::move(login);
        this->password = std::move(password);
        this->name = std::move(name);
        rating = 0;
        paymentMethods = "";
        pinnedAddresses = "";
        canOrder = true;
    }

public:
    Passenger(std::tuple <int, std::string, std::string, std::string, int, std::string, std::string, bool> data);
    Passenger() = default;

    static void ListAll();
    int getID() const;
    int getRating() const;
    static bool fetchLogin(std::string login);
    static Passenger logIn(std::string login, std::string password);
    static Passenger reg(std::string login, std::string password, std::string name);
    static void remove(Passenger *passenger); //TODO remove from Order DB
    void addOrder(int i);
    bool getCanOrder();
};

#endif //PASSENGER_PASSENGER_H
