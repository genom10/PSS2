//
// Created by genom10 on 14.04.2021.
//
#include "Passenger.h"


Passenger::Passenger(
        std::tuple<int, std::string, std::string, std::string, int, std::string, std::string, std::string> data) {
    //initialization from SQLite
    this->id = std::get<0>(data);
    this->login = std::get<1>(data);
    this->password = std::get<2>(data);
    this->name = std::get<3>(data);
    this->rating = std::get<4>(data);

    std::string rawOrderHistory = std::get<5>(data);
    std::stringstream ss(rawOrderHistory);
    std::string str;
    while (getline(ss, str, ',')) {
        this->orderHistory.push_back(str);
    }

    std::string rawPaymentMethods = std::get<6>(data);
    ss = std::stringstream(rawPaymentMethods);
    while (getline(ss, str, ',')) {
        this->paymentMethods.push_back(str);
    }

    std::string rawPinnedAddresses = std::get<7>(data);
    ss = std::stringstream(rawPinnedAddresses);
    while (getline(ss, str, ',')) {
        this->pinnedAddresses.push_back(str);
    }
}

void Passenger::ListAll(){
    auto storage = make_storage("users.sqlite",
                                make_unique_index("idx_passengers_login", indexed_column(&PassengerRecord::login).collate("BINARY").desc()),
                                make_table("users",
                                           make_column("id", &PassengerRecord::id, primary_key()),
                                           make_column("login", &PassengerRecord::login),
                                           make_column("password", &PassengerRecord::password),
                                           make_column("name", &PassengerRecord::name),
                                           make_column("rating", &PassengerRecord::rating),
                                           make_column("orderHistory", &PassengerRecord::orderHistory),
                                           make_column("paymentMethods", &PassengerRecord::paymentMethods),
                                           make_column("pinnedAddresses", &PassengerRecord::pinnedAddresses)));
    storage.sync_schema();
    for (auto i : storage.select(columns(&PassengerRecord::id,
                                         &PassengerRecord::login,
                                         &PassengerRecord::password,
                                         &PassengerRecord::name,
                                         &PassengerRecord::rating,
                                         &PassengerRecord::orderHistory,
                                         &PassengerRecord::paymentMethods,
                                         &PassengerRecord::pinnedAddresses))){
        std::cout << get<1>(i) << ' ' << get<2>(i) << '\n'; //TODO remove
    }
}

int Passenger::getID() const {
    return id;
}

int Passenger::getRating() const {
    return rating;
}

bool Passenger::fetchLogin(std::string login) {
    auto storage = make_storage("users.sqlite",
                                make_unique_index("idx_passengers_login", indexed_column(&PassengerRecord::login).collate("BINARY").desc()),
                                make_table("users",
                                           make_column("id", &PassengerRecord::id, primary_key()),
                                           make_column("login", &PassengerRecord::login),
                                           make_column("password", &PassengerRecord::password),
                                           make_column("name", &PassengerRecord::name),
                                           make_column("rating", &PassengerRecord::rating),
                                           make_column("orderHistory", &PassengerRecord::orderHistory),
                                           make_column("paymentMethods", &PassengerRecord::paymentMethods),
                                           make_column("pinnedAddresses", &PassengerRecord::pinnedAddresses)));
    storage.sync_schema();

    auto row = storage.select(columns(&PassengerRecord::id,
                                      &PassengerRecord::login,
                                      &PassengerRecord::password,
                                      &PassengerRecord::name,
                                      &PassengerRecord::rating,
                                      &PassengerRecord::orderHistory,
                                      &PassengerRecord::paymentMethods,
                                      &PassengerRecord::pinnedAddresses),
                              where(is_equal(&PassengerRecord::login, login)));
    return row.empty();
}

Passenger Passenger::logIn(std::string login, std::string password) {
    auto storage = make_storage("users.sqlite",
                                make_unique_index("idx_passengers_login", indexed_column(&PassengerRecord::login).collate("BINARY").desc()),
                                make_table("users",
                                           make_column("id", &PassengerRecord::id, primary_key()),
                                           make_column("login", &PassengerRecord::login),
                                           make_column("password", &PassengerRecord::password),
                                           make_column("name", &PassengerRecord::name),
                                           make_column("rating", &PassengerRecord::rating),
                                           make_column("orderHistory", &PassengerRecord::orderHistory),
                                           make_column("paymentMethods", &PassengerRecord::paymentMethods),
                                           make_column("pinnedAddresses", &PassengerRecord::pinnedAddresses)));
    storage.sync_schema();

    auto row = storage.select(columns(&PassengerRecord::id,
                                      &PassengerRecord::login,
                                      &PassengerRecord::password,
                                      &PassengerRecord::name,
                                      &PassengerRecord::rating,
                                      &PassengerRecord::orderHistory,
                                      &PassengerRecord::paymentMethods,
                                      &PassengerRecord::pinnedAddresses),
                              where(is_equal(&PassengerRecord::login, login)));
    Passenger passenger{row[0]};
    if (passenger.password == password)
        return Passenger(row[0]);
    else
        throw "password mismatch";
}

Passenger Passenger::reg(std::string login, std::string password, std::string name) {
    auto storage = make_storage("users.sqlite",
                                make_unique_index("idx_passengers_login", indexed_column(&PassengerRecord::login).collate("BINARY").desc()),
                                make_table("users",
                                           make_column("id", &PassengerRecord::id, primary_key()),
                                           make_column("login", &PassengerRecord::login),
                                           make_column("password", &PassengerRecord::password),
                                           make_column("name", &PassengerRecord::name),
                                           make_column("rating", &PassengerRecord::rating),
                                           make_column("orderHistory", &PassengerRecord::orderHistory),
                                           make_column("paymentMethods", &PassengerRecord::paymentMethods),
                                           make_column("pinnedAddresses", &PassengerRecord::pinnedAddresses)));
    storage.sync_schema();

    PassengerRecord passenger{login, password, name};
    int id = storage.insert(passenger);
    return Passenger(storage.select(columns(&PassengerRecord::id,
                                            &PassengerRecord::login,
                                            &PassengerRecord::password,
                                            &PassengerRecord::name,
                                            &PassengerRecord::rating,
                                            &PassengerRecord::orderHistory,
                                            &PassengerRecord::paymentMethods,
                                            &PassengerRecord::pinnedAddresses),
                                    where(is_equal(&PassengerRecord::id, id)))[0]);
}

void Passenger::remove(Passenger *passenger) {
    auto storage = make_storage("users.sqlite",
                                make_unique_index("idx_passengers_login", indexed_column(&PassengerRecord::login).collate("BINARY").desc()),
                                make_table("users",
                                           make_column("id", &PassengerRecord::id, primary_key()),
                                           make_column("login", &PassengerRecord::login),
                                           make_column("password", &PassengerRecord::password),
                                           make_column("name", &PassengerRecord::name),
                                           make_column("rating", &PassengerRecord::rating),
                                           make_column("orderHistory", &PassengerRecord::orderHistory),
                                           make_column("paymentMethods", &PassengerRecord::paymentMethods),
                                           make_column("pinnedAddresses", &PassengerRecord::pinnedAddresses)));
    storage.sync_schema();

    storage.remove<PassengerRecord>(passenger->getID());
    passenger = NULL;
}

