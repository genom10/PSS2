//
// Created by genom10 on 13.04.2021.
//

#include <iostream>
#include "../includes/sqlite_orm.h"

#include "Driver.h"
#include "DriverGateway.h"


void mainMenu(Driver*);
void loginMenu(Driver*);
void regMenu(Driver*);
void driverMenu(Driver*);
void orderMenu(Driver*);
void confirmationMenu(Driver*);

int main() {
    Driver driver;
    mainMenu(&driver);

    return 0;
}

void mainMenu(Driver* driver){
    int choice;
    while (true){
        std::cout << "drivers\n";
        Driver::ListAll();
        std::cout << "orders\n";
        DriverGateway::ListAll();

        std::cout << "1 - login\n2 - register\n3 - exit\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                loginMenu(driver);
                break;
            case 2:
                regMenu(driver);
                break;
            case 3:
                return;
            default:
                std::cout << "incorrect input\n";
        }
    }
}

void regMenu(Driver* driver) {
    std::string login;
    std::string password;
    std::string name;
    std::cout << "\ntype your login:";
    std::cin >> login;
    while (!Driver::fetchLogin(login)) {
        std::cout << "this login is already in use: ";
        std::cin >> login;
    }
    std::cout << "type your password:";
    std::cin >> password;
    std::cout << "type your name:";
    std::cin >> name;
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
            *driver = Driver::reg(login, password, name, carType);
            driverMenu(driver);
}

void loginMenu(Driver* driver){
    std::string login;
    std::string password;
    std::string name;
    std::cout << "\ntype your login: ";
    std::cin >> login;
    while (Driver::fetchLogin(login)){
        std::cout << "There's no driver with such login: ";
        std::cin >> login;
    }
    std::cout << "type your password: ";
    std::cin >> password;
    *driver = Driver::logIn(login, password);
    driverMenu(driver);
}

void driverMenu(Driver* driver){
    int choice;
    std::cout << "your ID is " << driver->getID() << '\n';
    std::cout << "your rating is " << driver->getRating() << '\n';
    while (true) {
        std::cout << "1 - delete profile\n2 - Show active orders\n3 - return\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                Driver::remove(driver);
                return;
            case 2:
                orderMenu(driver);
                break;
            case 3:
                return;
            default:
                std::cout << "incorrect input\n";
        }
    }
}

void orderMenu(Driver* driver){
    while (true) {
        std::cout << "1 - List all requests\n2 - List requests for my car\n3 - complete a ride\n4 - return\n";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                DriverGateway::ListFit();
                break;
            case 2:
                DriverGateway::ListFit(*driver);
                confirmationMenu(driver);
                break;
            case 3:
                DriverGateway::complete(driver);
                break;
            case 4:
                return;
            default:
                std::cout << "incorrect input\n";
        }
    }
}

void confirmationMenu(Driver* driver){
    std::cout << "What order would you like to take?\n";
    int toTake;
    std::cin >> toTake;
    DriverGateway::take(*driver, toTake);
}