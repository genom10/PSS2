//
// Created by egord on 4/14/2021.
//

#ifndef DRIVER_DRIVERGATEWAY_H
#define DRIVER_DRIVERGATEWAY_H

#include <iostream>
#include <utility>
#include "../includes/sqlite_orm.h"
#include "Driver.h"
#include "PassengerStorage.h"

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

class DriverGateway{

public:
    static void ListAll();
    static void ListFit();
    static void ListFit(Driver&);
    static void take(Driver&, int);

    static void complete(Driver *driver);
};

#endif DRIVER_DRIVERGATEWAY_H
