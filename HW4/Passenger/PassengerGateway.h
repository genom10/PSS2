//
// Created by genom10 on 14.04.2021.
//

#ifndef PASSENGER_PASSENGERGATEWAY_H
#define PASSENGER_PASSENGERGATEWAY_H

#include <iostream>
#include <utility>
#include "../includes/sqlite_orm.h"

using namespace sqlite_orm;

enum OrderStatus{
    lookingForDriver,
    driving,
    finished,
    emergency
};

enum CarType{
    economy,
    comfort,
    comfortPlus,
    business
};

struct Order{
    int orderID;
    int clientID;
    int driverID;
    OrderStatus status;
    std::string addressFrom;
    std::string addressTo;
    CarType carType;
};

class PassengerGateway{

public:
    static int makeOrder(Order);
};


#endif //PASSENGER_PASSENGERGATEWAY_H
