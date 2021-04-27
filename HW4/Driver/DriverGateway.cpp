//
// Created by egord on 4/14/2021.
//

#include "DriverGateway.h"
void DriverGateway::ListAll() {
    auto orderStorage = make_storage("../../orders.sqlite",
                                     make_table("orders",
                                                make_column("orderID", &Order::orderID, primary_key()),
                                                make_column("clientID", &Order::clientID),
                                                make_column("driverID", &Order::driverID),
                                                make_column("status", &Order::status),
                                                make_column("addressFrom", &Order::addressFrom),
                                                make_column("addressTo", &Order::addressTo),
                                                make_column("carType", &Order::carType)));
    orderStorage.sync_schema();
    for (auto i : orderStorage.select(columns(&Order::orderID,
                                             &Order::clientID,
                                             &Order::driverID,
                                             &Order::status,
                                             &Order::carType))) {
        std::cout << get<0>(i) << ' ' << get<1>(i) << ' ' << get<2>(i) << ' ' << get<3>(i) << ' ' << get<4>(i) << '\n'; //TODO remove
    }
}


void DriverGateway::ListFit() {
    auto orderStorage = make_storage("../../orders.sqlite",
                                     make_table("orders",
                                                make_column("orderID", &Order::orderID, primary_key()),
                                                make_column("clientID", &Order::clientID),
                                                make_column("driverID", &Order::driverID),
                                                make_column("status", &Order::status),
                                                make_column("addressFrom", &Order::addressFrom),
                                                make_column("addressTo", &Order::addressTo),
                                                make_column("carType", &Order::carType)));
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
                                               make_column("canOrder", &PassengerStorage::canOrder)));
    orderStorage.sync_schema();
    userStorage.sync_schema();
    for (auto i : orderStorage.select(columns(&Order::orderID, &Order::clientID),
                                            where(is_equal(&Order::status, "lookingForDriver")))) {
        auto order = orderStorage.get<Order>(get<0>(i));
        try{
            auto user = userStorage.get<PassengerStorage>(get<1>(i));
            std::cout << order.orderID << ")" << user.name << " want to ride from " << order.addressFrom << " to " << order.addressTo << " on " << order.carType << "\n";
        } catch (std::system_error error) {
            std::cout << error.what() << " for user with id " << get<1>(i) << '\n';
            continue;
        }
    }
    std::cout << "end of the list\n";
}

void DriverGateway::ListFit(Driver& driver) {
    auto orderStorage = make_storage("../../orders.sqlite",
                                     make_table("orders",
                                                make_column("orderID", &Order::orderID, primary_key()),
                                                make_column("clientID", &Order::clientID),
                                                make_column("driverID", &Order::driverID),
                                                make_column("status", &Order::status),
                                                make_column("addressFrom", &Order::addressFrom),
                                                make_column("addressTo", &Order::addressTo),
                                                make_column("carType", &Order::carType)));
    orderStorage.sync_schema();
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
                                               make_column("canOrder", &PassengerStorage::canOrder)));
    userStorage.sync_schema();
    for (auto car : driver.getCars()) {
        for (auto i : orderStorage.select(columns(&Order::orderID, &Order::clientID),
                                          where(is_equal(&Order::status, "lookingForDriver") and
                                                is_equal(&Order::carType, car.getCarType())))) {
            auto order = orderStorage.get<Order>(get<0>(i));
            auto user = userStorage.get<PassengerStorage>(get<1>(i));
            std::cout << order.orderID << ")" << user.name << " want to ride from " << order.addressFrom << " to "
                      << order.addressTo << "\n";
        }
    }
}

void DriverGateway::take(Driver& driver, int take) {
    auto orderStorage = make_storage("../../orders.sqlite",
                                     make_table("orders",
                                                make_column("orderID", &Order::orderID, primary_key()),
                                                make_column("clientID", &Order::clientID),
                                                make_column("driverID", &Order::driverID),
                                                make_column("status", &Order::status),
                                                make_column("addressFrom", &Order::addressFrom),
                                                make_column("addressTo", &Order::addressTo),
                                                make_column("carType", &Order::carType)));
    orderStorage.sync_schema();
    Order order;
    try{order = orderStorage.get<Order>(take);} catch (std::system_error error) {
        std::cout << error.what() << '\n';
        return;
    }
    if (order.status != "lookingForDriver") {
        std::cout << "order is taken or finished\n";
        return;
    }
    bool hasFittingCar = false;
    for (auto car : driver.getCars()){
        if (car.getCarType() == order.carType)
            hasFittingCar = true;
        break;
    }
    if (!hasFittingCar){
        std::cout << "your car does not satisfy user's needs\n";
        return;
    }

    order.driverID = driver.getID();
    order.status = "driverAccepted";
    orderStorage.update(order);
}

void DriverGateway::complete(Driver* driver) {
    auto orderStorage = make_storage("../../orders.sqlite",
                                     make_table("orders",
                                                make_column("orderID", &Order::orderID, primary_key()),
                                                make_column("clientID", &Order::clientID),
                                                make_column("driverID", &Order::driverID),
                                                make_column("status", &Order::status),
                                                make_column("addressFrom", &Order::addressFrom),
                                                make_column("addressTo", &Order::addressTo),
                                                make_column("carType", &Order::carType)));
    orderStorage.sync_schema();
    for (auto i : orderStorage.select(columns(&Order::orderID),
                                      where(is_not_equal(&Order::status, "completed") and is_equal(&Order::driverID, driver->getID())
                                            and is_not_equal(&Order::status, "driverCompleted") and is_not_equal(&Order::status, "lookingForDriver")))) {

        auto order = orderStorage.get<Order>(get<0>(i));

        if (order.status == "riding") {
            std::string confirmation;
            while (true) {
                std::cout << "riding from " << order.addressFrom << " to " << order.addressTo
                          << "\n do you wish to finish the ride? Y/N";
                std::cin >> confirmation;
                if (confirmation == "Y" || confirmation == "y") {
                    order.status = "driverCompleted";
                    orderStorage.update(order);
                    std::cout << "ride completed. Waiting for user's response\n";
                    break;
                }
                if (confirmation == "N" || confirmation == "n") {
                    break;
                }
            }
            if (confirmation == "N" || confirmation == "n" || confirmation == "Y" || confirmation == "y") {
                continue;
            }
        }

        if (order.status == "driverAccepted") {
            std::cout << "Wait for user to accept\n";
        }

        if (order.status == "passengerCompleted") {
            std::string confirmation;
            while (true) {
                std::cout << "riding from " << order.addressFrom << " to " << order.addressTo
                          << "\n do you wish to finish the ride? Y/N";
                std::cin >> confirmation;
                if (confirmation == "Y" || confirmation == "y") {
                    order.status = "completed";
                    orderStorage.update(order);
                    std::cout << "ride completed.\n";
                    break;
                }
                if (confirmation == "N" || confirmation == "n") {
                    break;
                }
            }
            if (confirmation == "N" || confirmation == "n" || confirmation == "Y" || confirmation == "y") {
                continue;
            }
        }

        std::cout << "unknown order status for order " << order.orderID << '\n';
    }
}