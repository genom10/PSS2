//
// Created by egord on 25.04.2021.
//

#include "AdminGateway.h"

Passenger AdminGateway::getPassengerByID(int id) {
    auto userStorage = make_storage("../../users.sqlite",
                                    make_unique_index("idx_passengers_login",
                                                      indexed_column(&PassengerStorage::login).collate(
                                                              "BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &PassengerStorage::id, primary_key()),
                                               make_column("login", &PassengerStorage::login),
                                               make_column("password", &PassengerStorage::password),
                                               make_column("name", &PassengerStorage::name),
                                               make_column("rating", &PassengerStorage::rating),
                                               make_column("paymentMethods", &PassengerStorage::paymentMethods),
                                               make_column("pinnedAddresses", &PassengerStorage::pinnedAddresses),
                                               make_column("canOrder", &PassengerStorage::canOrder)));
    userStorage.sync_schema();
    auto row = userStorage.select(columns(&PassengerStorage::id,
                                          &PassengerStorage::login,
                                          &PassengerStorage::password,
                                          &PassengerStorage::name,
                                          &PassengerStorage::rating,
                                          &PassengerStorage::paymentMethods,
                                          &PassengerStorage::pinnedAddresses,
                                          &PassengerStorage::canOrder),
                                  where(is_equal(&PassengerStorage::id, id)));
    return Passenger{row[0]};
}

void AdminGateway::ListAllPassengers(){
    auto userStorage = make_storage("../../users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&PassengerStorage::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &PassengerStorage::id, primary_key()),
                                               make_column("login", &PassengerStorage::login),
                                               make_column("password", &PassengerStorage::password),
                                               make_column("name", &PassengerStorage::name),
                                               make_column("rating", &PassengerStorage::rating),
                                               make_column("paymentMethods", &PassengerStorage::paymentMethods),
                                               make_column("pinnedAddresses", &PassengerStorage::pinnedAddresses),
                                               make_column("canOrder", &PassengerStorage::canOrder)
                                    ));
    userStorage.sync_schema();
    for (auto i : userStorage.select(columns(&PassengerStorage::id,
                                             &PassengerStorage::login,
                                             &PassengerStorage::password,
                                             &PassengerStorage::name))){
        std::cout << get<0>(i) << ' ' << get<1>(i) << ' ' << get<2>(i) << ' ' << get<3>(i)<< '\n';
    }
}