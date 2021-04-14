//
// Created by genom10 on 14.04.2021.
//

#include "PassengerGateway.h"

int PassengerGateway::makeOrder(Order order) {
    auto orderStorage = make_storage("orders.sqlite", //TODO compilation error here
                                     make_table("orders",
                                               make_column("orderID", &Order::orderID, primary_key()),
                                               make_column("clientID", &Order::clientID),
                                               make_column("driverID", &Order::driverID),
                                               make_column("status", &Order::status),
                                               make_column("addressFrom", &Order::addressFrom),
                                               make_column("addressTo", &Order::addressTo),
                                               make_column("carType", &Order::carType)));
    orderStorage.sync_schema();
    //int id = orderStorage.insert(order);
    //return id;
    return -1;
}
