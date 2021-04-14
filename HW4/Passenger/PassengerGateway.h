//
// Created by genom10 on 14.04.2021.
//

#ifndef PASSENGER_PASSENGERGATEWAY_H
#define PASSENGER_PASSENGERGATEWAY_H

#include <iostream>
#include <utility>
#include "../includes/sqlite_orm.h"
#include "Passenger.h"

using namespace sqlite_orm;

struct Order{
    int orderID;
    int clientID;
    int driverID;
    std::string status;
    std::string addressFrom;
    std::string addressTo;
    std::string carType;
};

class PassengerGateway{

public:
    static void ListAll();
    static int makeOrder(Passenger*, Order);
    static int calcPrice(std::string, std::string, std::string);
    static void listHistory(Passenger*);
    static void listActive(Passenger*);
    static void accept(Passenger*);
    static void getRidesCoordinates(Passenger *passenger);
    static std::string getRideCoordinates(int id);
};


#endif //PASSENGER_PASSENGERGATEWAY_H
