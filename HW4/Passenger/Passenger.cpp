//
// Created by genom10 on 14.04.2021.
//
#include "Passenger.h"


Passenger::Passenger(
        std::tuple<int, std::string, std::string, std::string, int, std::string, std::string, bool> data) {
        //initialization from SQLite
        this->id = std::get<0>(data);
        this->login = std::get<1>(data);
        this->password = std::get<2>(data);
        this->name = std::get<3>(data);
        this->rating = std::get<4>(data);
        this->paymentMethods = std::get<5>(data);
        this->pinnedAddresses = std::get<6>(data);
        this->canOrder = std::get<7>(data);
}

void Passenger::ListAll(){
    auto userStorage = make_storage("../../users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Passenger::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &Passenger::id, primary_key()),
                                               make_column("login", &Passenger::login),
                                               make_column("password", &Passenger::password),
                                               make_column("name", &Passenger::name),
                                               make_column("rating", &Passenger::rating),
                                               make_column("paymentMethods", &Passenger::paymentMethods),
                                               make_column("pinnedAddresses", &Passenger::pinnedAddresses),
                                               make_column("canOrder", &Passenger::canOrder)
                                    ));
    userStorage.sync_schema();
    for (auto i : userStorage.select(columns(&Passenger::id,
                                             &Passenger::login,
                                             &Passenger::password,
                                             &Passenger::name))){
        std::cout << get<0>(i) << ' ' << get<1>(i) << ' ' << get<2>(i) << ' ' << get<3>(i)<< '\n';
    }
}

int Passenger::getID() const {
    return id;
}

int Passenger::getRating() const {
    return rating;
}

bool Passenger::fetchLogin(std::string login) {
    auto userStorage = make_storage("../../users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Passenger::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &Passenger::id, primary_key()),
                                               make_column("login", &Passenger::login),
                                               make_column("password", &Passenger::password),
                                               make_column("name", &Passenger::name),
                                               make_column("rating", &Passenger::rating),
                                               make_column("paymentMethods", &Passenger::paymentMethods),
                                               make_column("pinnedAddresses", &Passenger::pinnedAddresses),
                                               make_column("canOrder", &Passenger::canOrder)
                                    ));
    userStorage.sync_schema();

    auto row = userStorage.select(columns(&Passenger::id,
                                          &Passenger::login,
                                          &Passenger::password,
                                          &Passenger::name,
                                          &Passenger::rating,
                                          &Passenger::paymentMethods,
                                          &Passenger::pinnedAddresses),
                                  where(is_equal(&Passenger::login, login)));
    return row.empty();
}

Passenger Passenger::logIn(std::string login, std::string password) {
    auto userStorage = make_storage("../../users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Passenger::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &Passenger::id, primary_key()),
                                               make_column("login", &Passenger::login),
                                               make_column("password", &Passenger::password),
                                               make_column("name", &Passenger::name),
                                               make_column("rating", &Passenger::rating),
                                               make_column("paymentMethods", &Passenger::paymentMethods),
                                               make_column("pinnedAddresses", &Passenger::pinnedAddresses),
                                               make_column("canOrder", &Passenger::canOrder)
                                    ));
    userStorage.sync_schema();

    auto row = userStorage.select(columns(&Passenger::id,
                                          &Passenger::login,
                                          &Passenger::password,
                                          &Passenger::name,
                                          &Passenger::rating,
                                          &Passenger::paymentMethods,
                                          &Passenger::pinnedAddresses,
                                          &Passenger::canOrder),
                                  where(is_equal(&Passenger::login, login)));
    Passenger passenger{row[0]};
    if (passenger.password == password)
        return passenger;
    else
        throw "password mismatch";
}

Passenger Passenger::reg(std::string login, std::string password, std::string name) {
    auto userStorage = make_storage("../../users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Passenger::login).collate("BINARY").desc()),
                                    make_table("users",
                                           make_column("id", &Passenger::id, primary_key()),
                                           make_column("login", &Passenger::login),
                                           make_column("password", &Passenger::password),
                                           make_column("name", &Passenger::name),
                                           make_column("rating", &Passenger::rating),
                                           make_column("paymentMethods", &Passenger::paymentMethods),
                                           make_column("pinnedAddresses", &Passenger::pinnedAddresses),
                                           make_column("canOrder", &Passenger::canOrder)
                                           ));
    userStorage.sync_schema();

    Passenger passenger{login, password, name};
    int id = userStorage.insert(passenger);
    return Passenger(userStorage.select(columns(&Passenger::id,
                                                &Passenger::login,
                                                &Passenger::password,
                                                &Passenger::name,
                                                &Passenger::rating,
                                                &Passenger::paymentMethods,
                                                &Passenger::pinnedAddresses,
                                                &Passenger::canOrder),
                                        where(is_equal(&Passenger::id, id)))[0]);
}

void Passenger::remove(Passenger *passenger) {
    auto userStorage = make_storage("../../users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Passenger::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &Passenger::id, primary_key()),
                                               make_column("login", &Passenger::login),
                                               make_column("password", &Passenger::password),
                                               make_column("name", &Passenger::name),
                                               make_column("rating", &Passenger::rating),
                                               make_column("paymentMethods", &Passenger::paymentMethods),
                                               make_column("pinnedAddresses", &Passenger::pinnedAddresses),
                                               make_column("canOrder", &Passenger::canOrder)
                                    ));
    userStorage.sync_schema();

    userStorage.remove<Passenger>(passenger->getID());
    //TODO remove from associated rides
    passenger = NULL;
}

void Passenger::addOrder(int i) {
    auto userStorage = make_storage("../../users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Passenger::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &Passenger::id, primary_key()),
                                               make_column("login", &Passenger::login),
                                               make_column("password", &Passenger::password),
                                               make_column("name", &Passenger::name),
                                               make_column("rating", &Passenger::rating),
                                               make_column("paymentMethods", &Passenger::paymentMethods),
                                               make_column("pinnedAddresses", &Passenger::pinnedAddresses),
                                               make_column("canOrder", &Passenger::canOrder)
                                    ));
    userStorage.sync_schema();
    userStorage.update(*this);
}

