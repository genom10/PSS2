//
// Created by egord on 4/14/2021.
//

#include "Driver.h"


Driver::Driver(std::tuple<int, std::string, std::string, std::string, int, std::string, std::string> data) {
    //initialization from SQLite
    this->id = std::get<0>(data);
    this->login = std::get<1>(data);
    this->password = std::get<2>(data);
    this->name = std::get<3>(data);
    this->rating = std::get<4>(data);

    this->orderHistory = std::get<5>(data);
    this->car.carType = std::get<6>(data);
}

void Driver::ListAll(){
    auto driverStorage = make_storage("../../drivers.sqlite",
                                      make_unique_index("idx_passengers_login", indexed_column(&Driver::login).collate("BINARY").desc()),
                                      make_table("users",
                                               make_column("id", &Driver::id, primary_key()),
                                               make_column("login", &Driver::login),
                                               make_column("password", &Driver::password),
                                               make_column("name", &Driver::name),
                                               make_column("rating", &Driver::rating),
                                               make_column("orderHistory", &Driver::orderHistory),
                                               make_column("carType", &Driver::carType)));
    driverStorage.sync_schema();
    for (auto i : driverStorage.select(columns(&Driver::id,
                                               &Driver::login,
                                               &Driver::password,
                                               &Driver::name,
                                               &Driver::orderHistory))){
        std::cout << get<0>(i) << ' ' << get<1>(i) << ' ' << get<2>(i) << ' ' << get<3>(i) << ' ' << get<4>(i) << '\n';
    }
}

int Driver::getID() const {
    return id;
}

int Driver::getRating() const {
    return rating;
}

bool Driver::fetchLogin(std::string login) {
    auto userStorage = make_storage("../../drivers.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Driver::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &Driver::id, primary_key()),
                                               make_column("login", &Driver::login),
                                               make_column("password", &Driver::password),
                                               make_column("name", &Driver::name),
                                               make_column("rating", &Driver::rating),
                                               make_column("orderHistory", &Driver::orderHistory),
                                               make_column("carType", &Driver::carType)));
    userStorage.sync_schema();

    auto row = userStorage.select(columns(&Driver::id),
                                  where(is_equal(&Driver::login, login)));
    return row.empty();
}

Driver Driver::logIn(std::string login, std::string password) {
    auto userStorage = make_storage("../../drivers.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Driver::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &Driver::id, primary_key()),
                                               make_column("login", &Driver::login),
                                               make_column("password", &Driver::password),
                                               make_column("name", &Driver::name),
                                               make_column("rating", &Driver::rating),
                                               make_column("orderHistory", &Driver::orderHistory),
                                               make_column("carType", &Driver::carType)));
    userStorage.sync_schema();

    auto row = userStorage.select(columns(&Driver::id,
                                          &Driver::login,
                                          &Driver::password,
                                          &Driver::name,
                                          &Driver::rating,
                                          &Driver::orderHistory,
                                          &Driver::carType),
                                  where(is_equal(&Driver::login, login)));
    Driver passenger{row[0]};
    if (passenger.password == password)
        return passenger;
    else
        throw "password mismatch";
}

Driver Driver::reg(std::string login, std::string password, std::string name, std::string carType) {
    auto driverStorage = make_storage("../../drivers.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Driver::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &Driver::id, primary_key()),
                                               make_column("login", &Driver::login),
                                               make_column("password", &Driver::password),
                                               make_column("name", &Driver::name),
                                               make_column("rating", &Driver::rating),
                                               make_column("orderHistory", &Driver::orderHistory),
                                               make_column("carType", &Driver::carType)));
    driverStorage.sync_schema();

    Driver driver{login, password, name, carType};
    int id = driverStorage.insert(driver);
    return Driver(driverStorage.select(columns(&Driver::id,
                                                &Driver::login,
                                                &Driver::password,
                                                &Driver::name,
                                                &Driver::rating,
                                                &Driver::orderHistory,
                                                &Driver::carType),
                                        where(is_equal(&Driver::id, id)))[0]);
}

void Driver::remove(Driver *passenger) {
    auto userStorage = make_storage("../../drivers.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Driver::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &Driver::id, primary_key()),
                                               make_column("login", &Driver::login),
                                               make_column("password", &Driver::password),
                                               make_column("name", &Driver::name),
                                               make_column("rating", &Driver::rating),
                                               make_column("orderHistory", &Driver::orderHistory),
                                               make_column("carType", &Driver::carType)));
    userStorage.sync_schema();

    userStorage.remove<Driver>(passenger->getID());
    //TODO remove from associated rides
    passenger = NULL;
}

void Driver::addOrder(int i) {
    auto userStorage = make_storage("../../drivers.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&Driver::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &Driver::id, primary_key()),
                                               make_column("login", &Driver::login),
                                               make_column("password", &Driver::password),
                                               make_column("name", &Driver::name),
                                               make_column("rating", &Driver::rating),
                                               make_column("orderHistory", &Driver::orderHistory),
                                               make_column("carType", &Driver::carType)));
    userStorage.sync_schema();

    if (orderHistory == "")
        orderHistory = std::to_string(i);
    else
        orderHistory += "," + std::to_string(i);
    userStorage.update(*this);//todo
}

Car Driver::getCar() {
    return car;
}

