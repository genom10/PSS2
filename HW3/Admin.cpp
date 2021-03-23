//
// Created by genom10 on 07.03.2021.
//

#include <iostream>
#include "Admin.h"
#include "User.h"
#include "Professor.h"
#include "Director.h"

Admin::Admin(std::string name, std::string creator) : User(UserType::admin, std::move(name), creator){};

User* Admin::createUser(UserType::Type type, std::string name){
    switch (type) {
        case UserType::admin : return new Admin(std::move(name), this->getName());
        case UserType::professor : return new Professor(std::move(name), this->getName());
        case UserType::director : return new Director(std::move(name), this->getName());
    }
    return new User(type, std::move(name), this->getName());
}

void Admin::changeUserType(User *user, UserType::Type type) {
    user->setUserType(type);
}

void Admin::triggerEmergency() {
    std::cout << "Emergency triggered by " << this->getName() << '\n';
    User::isEmergency = true;
}

void Admin::stopEmergency() {
    std::cout << "Emergency stopped by " << this->getName() << '\n';
    User::isEmergency = false;
}
