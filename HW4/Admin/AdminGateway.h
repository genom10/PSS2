//
// Created by egord on 25.04.2021.
//

#ifndef ADMIN_ADMINGATEWAY_H
#define ADMIN_ADMINGATEWAY_H

#include "../Passenger/Passenger.h"
#include "../Driver/PassengerStorage.h"
#include "../Driver/Driver.h"

class AdminGateway {
public:
    static Passenger getPassengerByID(int id);
    static void ListAllPassengers();
};


#endif //ADMIN_ADMINGATEWAY_H
