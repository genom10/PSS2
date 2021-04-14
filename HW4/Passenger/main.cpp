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
void orderMenu(Passenger*);

int main() {
    Passenger passenger;
    mainMenu(&passenger);

    return 0;
}

void mainMenu(Passenger* passenger){
    int choice;
    while (true){
        Passenger::ListAll();
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
        std::cout << "1 - delete profile\n2-Order a ride\n3 - return";
        std::cin >> choice;
        switch (choice) {
            case 1:
                Passenger::remove(passenger);
                return;
            case 2:
                orderMenu(passenger);
                break;
            case 3:
                return;
            default:
                std::cout << "incorrect input\n";
        }
    }
}

void orderMenu(Passenger* passenger){
    std::cout << "type adress from:";
    std::string addressFrom;
    std::cin >> addressFrom;
    std::cout << "type adress to:";
    std::string addressTo;
    std::cin >> addressTo;
    std::cout << "chose car type:\n1 - economy\n2 - comfort\n3 - comfortPlus\n4 - business";
    int carChoice;
    CarType carType;
    switch (carChoice) {
        case 1:
            carType = CarType::economy;
            break;
        case 2:
            carType = CarType::comfort;
            break;
        case 3:
            carType = CarType::comfortPlus;
            break;
        case 4:
            carType = CarType::business;
            break;
        default:
            carType = CarType::economy;
            std::cout << "incorrect input. You'll get economy car";
    }
    Order order{
        -1,
        passenger->getID(),
        -1,
        OrderStatus::lookingForDriver,
        addressFrom,
        addressTo,
        carType
    };
    int id = PassengerGateway::makeOrder(order);
}