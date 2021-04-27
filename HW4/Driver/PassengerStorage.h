//
// Created by egord on 4/14/2021.
//

#ifndef PASSENGER_PASSENGERSTORAGE_H
#define PASSENGER_PASSENGERSTORAGE_H

#include <string>

struct PassengerStorage{
    int id;
    std::string login;
    std::string password;
    std::string name;
    int rating;
    std::string orderHistory;
    std::string paymentMethods;
    std::string pinnedAddresses;
    bool canOrder;
};


#endif //PASSENGER_PASSENGERSTORAGE_H
