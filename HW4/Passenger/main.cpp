//
// Created by genom10 on 13.04.2021.
//

#include <iostream>
#include "../includes/sqlite_orm.h"

#include "Passenger.h"
#include "PassengerGateway.h"


void mainMenu(Passenger*);
void loginMenu(Passenger*);
void regMenu(Passenger*);
void userMenu(Passenger*);
void activeMenu(Passenger*);
void orderMenu(Passenger*);

int main() {
    Passenger passenger;
    mainMenu(&passenger);

    return 0;
}

void mainMenu(Passenger* passenger){
    int choice;
    while (true){
        std::cout << "passengers\n";
        Passenger::ListAll();
        std::cout << "orders\n";
        PassengerGateway::ListAll();

        std::cout << "1 - login\n2 - register\n3 - exit\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                loginMenu(passenger);
                break;
            case 2:
                regMenu(passenger);
                break;
            case 3:
                return;
            default:
                std::cout << "incorrect input\n";
        }
    }
}

void regMenu(Passenger* passenger){
    std::string login;
    std::string password;
    std::string name;
    std::cout << "\ntype your login:";
    std::cin >> login;
    while (!Passenger::fetchLogin(login)){
        std::cout << "this login is already in use: ";
        std::cin >> login;
    }
    std::cout << "type your password:";
    std::cin >> password;
    std::cout << "type your name:";
    std::cin >> name;
    *passenger = Passenger::reg(login, password, name);
    userMenu(passenger);
}

void loginMenu(Passenger* passenger){
    std::string login;
    std::string password;
    std::string name;
    std::cout << "\ntype your login: ";
    std::cin >> login;
    while (Passenger::fetchLogin(login)){
        std::cout << "There's no user with such login: ";
        std::cin >> login;
    }
    std::cout << "type your password: ";
    std::cin >> password;
    *passenger = Passenger::logIn(login, password);
    userMenu(passenger);
}

void userMenu(Passenger* passenger){
    int choice;
    std::cout << "your ID is " << passenger->getID() << '\n';
    std::cout << "your rating is " << passenger->getRating() << '\n';
    while (true) {
        std::cout << "1 - delete profile\n2 - Order a ride\n3 - See active orders\n4 - See order history\n5 - Confirm a ride\n6 - get active rides coordinates\n7 - return\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                Passenger::remove(passenger);
                return;
            case 2:
                orderMenu(passenger);
                break;
            case 3:
                activeMenu(passenger);
                break;
            case 4:
                PassengerGateway::listHistory(passenger);
                break;
            case 5:
                PassengerGateway::accept(passenger);
                break;
            case 6:
                PassengerGateway::getRidesCoordinates(passenger);
                break;
            case 7:
                return;
            default:
                std::cout << "incorrect input\n";
        }
    }
}

void activeMenu(Passenger* passenger){
    PassengerGateway::listActive(passenger);
}

void orderMenu(Passenger* passenger){
    std::cout << "type address from:";
    std::string addressFrom;
    std::cin >> addressFrom;
    std::cout << "type address to:";
    std::string addressTo;
    std::cin >> addressTo;
    std::cout << "chose car type:\n1 - economy\n2 - comfort\n3 - comfortPlus\n4 - business\n";
    int carChoice;
    std::cin >> carChoice;
    std::string carType;
    switch (carChoice) {
        case 1:
            carType = "economy";
            break;
        case 2:
            carType = "comfort";
            break;
        case 3:
            carType = "comfortPlus";
            break;
        case 4:
            carType = "business";
            break;
        default:
            carType = "economy";
            std::cout << "incorrect input. You'll get economy car\n";
    }
    Order order{
        -1,
        passenger->getID(),
        -1,
        "lookingForDriver",
        addressFrom,
        addressTo,
        carType
    };
    while(true){
        std::cout << "The ride will cost " << PassengerGateway::calcPrice(addressFrom, addressTo, carType) << " do you wish to proceed? Y/N";
        std::string confirm;
        std::cin >> confirm;
        if (confirm == "y" || confirm == "Y")
            break;
        if (confirm == "n" || confirm == "N")
            return;
    }
    int orderId = PassengerGateway::makeOrder(passenger, order);
    std::cout << "your order's ID is " << orderId << '\n';
}