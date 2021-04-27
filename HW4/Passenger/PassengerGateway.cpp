//
// Created by genom10 on 14.04.2021.
//

#include "PassengerGateway.h"
#include "Driver.h"

int PassengerGateway::makeOrder(Passenger* passenger, Order order) {
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
    int id = orderStorage.insert(order);

    passenger->addOrder(id);
    //userStorage.update(passenger);
    return id;
}

void PassengerGateway::ListAll() {
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
                                             &Order::status))){
        std::cout << get<0>(i) << ' ' <<  get<1>(i) << ' ' <<  get<2>(i) << ' ' << get<3>(i) << '\n'; //TODO remove
    }
}

int PassengerGateway::calcPrice(std::string addressFrom, std::string addressTo, std::string carType) {
    return 999;
}

void PassengerGateway::listHistory(Passenger* passenger) {
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
    for (auto i : orderStorage.select(columns(&Order::orderID, &Order::driverID),
                                      where(is_equal(&Order::status, "completed") and is_equal(&Order::clientID, passenger->getID())))) {
        auto order = orderStorage.get<Order>(get<0>(i));
            try{auto driver = driverStorage.get<Driver>(get<1>(i));
                if (get<1>(i) != 1){
                    std::cout << "completed ride from " << order.addressFrom << " to " << order.addressTo << " by " << driver.name << '\n';
                }else {
                    std::cout << "completed ride from " << order.addressFrom << " to " << order.addressTo
                              << " driver is missing\n";
                }

            }catch (std::system_error error) {
                std::cout << error.what() << '\n';
                break;
            }
    }
}

void PassengerGateway::listActive(Passenger *passenger) {
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
    for (auto i : orderStorage.select(columns(&Order::orderID, &Order::driverID),
                                      where(is_not_equal(&Order::status, "completed") and is_equal(&Order::clientID, passenger->getID())))) {

        auto order = orderStorage.get<Order>(get<0>(i));
        if (order.status == "lookingForDriver") {
            std::cout << "waiting for driver for ride from " << order.addressFrom << " to " << order.addressTo << '\n';
            continue;
        }
        auto driver = driverStorage.get<Driver>(get<1>(i));

        if (order.status == "driverAccepted") {
            std::cout << "driver accepted a ride from " << order.addressFrom << " to " << order.addressTo
            << " with " << driver.name;
            continue;
        }
        if (order.status == "riding") {
        std::cout << "riding from " << order.addressFrom << " to " << order.addressTo << " with " << driver.name
                  << '\n';
            continue;
        }
        if (order.status == "driverCompleted") {
            std::cout << "driver waiting for a confirmation for a ride from " << order.addressFrom << " to "
                      << order.addressTo << " by " << driver.name << '\n';
            continue;
        }
        if (order.status == "passengerCompleted") {
            std::cout << "driver waiting for driver's a confirmation for a ride from " << order.addressFrom
                      << " to " << order.addressTo << " by " << driver.name << '\n';
            continue;
        }
        std::cout << "unknown order status for order " << order.orderID << '\n';
    }
}

void PassengerGateway::accept(Passenger* passenger) {
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

    for (auto i : orderStorage.select(columns(&Order::orderID, &Order::driverID),
                                      where(is_not_equal(&Order::status, "completed") and is_equal(&Order::clientID, passenger->getID())
                                      and is_not_equal(&Order::status, "passengerCompleted") and is_not_equal(&Order::status, "lookingForDriver")))) {

        auto order = orderStorage.get<Order>(get<0>(i));
        auto driver = driverStorage.get<Driver>(get<1>(i));

        if (order.status == "driverAccepted") {
            std::string confirmation;
            while (true) {
                std::cout << "driver accepted a ride from " << order.addressFrom << " to " << order.addressTo
                          << " with " << driver.name
                          << "\n do you wish to accept the ride? Y/N";
                std::cin >> confirmation;
                if (confirmation == "Y" || confirmation == "y") {
                    order.status = "riding";
                    orderStorage.update(order);
                    std::cout << "ride accepted. Enjoy your ride!\n";
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

        if (order.status == "riding") {
            std::string confirmation;
            while (true) {
                std::cout << "riding from " << order.addressFrom << " to " << order.addressTo
                          << " with " << driver.name
                          << "\n do you wish to complete the ride? Y/N";
                std::cin >> confirmation;
                if (confirmation == "Y" || confirmation == "y") {
                    order.status = "passengerCompleted";
                    orderStorage.update(order);
                    std::cout << "ride completed. Waiting for driver's confirmation\n";
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

        if (order.status == "driverCompleted") {
            std::string confirmation;
            while (true) {
                std::cout << "driver completed a ride from " << order.addressFrom << " to " << order.addressTo
                          << " with " << driver.name
                          << "\n do you wish to complete the ride? Y/N";
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

void PassengerGateway::getRidesCoordinates(Passenger *passenger) {
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
    for (auto i : orderStorage.select(columns(&Order::orderID, &Order::driverID),
                                      where(is_not_equal(&Order::status, "completed") and is_equal(&Order::clientID, passenger->getID())
                                            and is_not_equal(&Order::status, "passengerCompleted") and is_not_equal(&Order::status, "lookingForDriver")))) {
        auto order = orderStorage.get<Order>(get<0>(i));
        std::cout << "a ride from " << order.addressFrom << " to " << order.addressTo << " is at " << PassengerGateway::getRideCoordinates(order.orderID)<< '\n';
    }
}

std::string PassengerGateway::getRideCoordinates(int id) {
    return "somewhere in the middle of nowhere";
}