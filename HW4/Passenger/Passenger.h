//
// Created by genom10 on 14.04.2021.
//

#ifndef PASSENGER_PASSENGER_H
#define PASSENGER_PASSENGER_H

#include <iostream>
#include <utility>
#include "../includes/sqlite_orm.h"

using namespace sqlite_orm;


struct PassengerRecord{
    int id;
    std::string login;
    std::string password;
    std::string name;
    int rating;
    std::string orderHistory;
    std::string paymentMethods;
    std::string pinnedAddresses;
    PassengerRecord(std::string login, std::string password, std::string name){
        id = -1;
        this->login = std::move(login);
        this->password = std::move(password);
        this->name = std::move(name);
        rating = 0;
    }
};

class Passenger{
    int id;
    std::string login;
    std::string password;
    std::string name;
    int rating;
    std::vector<std::string> orderHistory;
    std::vector<std::string> paymentMethods;
    std::vector<std::string> pinnedAddresses;

public:
    Passenger(std::tuple <int, std::string, std::string, std::string, int, std::string, std::string, std::string> data);
    Passenger() = default;

    static void ListAll();
    int getID() const;
    int getRating() const;
    static bool fetchLogin(std::string login);
    static Passenger logIn(std::string login, std::string password);
    static Passenger reg(std::string login, std::string password, std::string name);
    static void remove(Passenger *passenger);
};

#endif //PASSENGER_PASSENGER_H
