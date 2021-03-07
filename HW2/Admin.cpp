//
// Created by genom10 on 07.03.2021.
//

#include "Admin.h"
#include "User.h"

Admin::Admin(std::string name, std::string creator) : User(UserType::admin, std::move(name), creator) {
    this->type = UserType::admin;
}

User* Admin::createUser(UserType::Type type, std::string name){
    switch (type) {
        case UserType::admin :
            return new Admin(std::move(name), this->getName());
    }
    return new User(type, std::move(name), this->getName());
}


