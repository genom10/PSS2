//
// Created by genom10 on 07.03.2021.
//

#include <iostream>
#include <utility>
#include "User.h"

bool User::isEmergency = false;
User::User(UserType::Type type, std::string name){
    this->type = type;
    this->name = std::move(name);
}

User::User(UserType::Type type, std::string name, std::string creator) : User::User(type, name) {
    this->creator = std::move(creator);
}

UserType::Type User::getUserType() const {
    return type;
}

void User::setUserType(UserType::Type userType) {
    User::type = userType;
}

std::string User::getTextUserType() const{
    switch(type){
        case UserType::guest : return  "guest";
        case UserType::student : return "student";
        case UserType::admin : return "admin";
        case UserType::director : return "director";
        case UserType::lab_employee : return "lab_employee";
        case UserType::professor : return "professor";
        default: return "unknown level";
    }
}

std::string User::getTextUserType(UserType::Type userType) {
    switch(userType){
        case UserType::guest : return  "guest";
        case UserType::student : return "student";
        case UserType::admin : return "admin";
        case UserType::director : return "director";
        case UserType::lab_employee : return "lab_employee";
        case UserType::professor : return "professor";
        default: return "unknown level";
    }
}

bool User::hasAccessTo(const Classroom& classroom) {
    if (isEmergency){
        std::cout << "Emergency situation, please leave the building immediately. " << this->getTextUserType() << ' ' << this->getName() << " passed through " << classroom.getNumber() << '\n';
        return true;
    }
    std::cout << this->getTextUserType() << ' ' << this->getName() << " tried to access room"
        << classroom.getNumber() << " with access level " << classroom.getTextAccessLevel() << '\n';
    return UserType::hasAccessTo(User::type, classroom.getAccessLevel());
}

int User::getRoom() const {
    return room;
}

void User::setRoom(int room) {
    User::room = room;
}

const std::string &User::getCreator() const {
    return creator;
}

const std::string &User::getName() const {
    return name;
}

void User::setCreator(const std::string &creator) {
    User::creator = creator;
}



void User::f() {
    std::cout << "why would you call me?";
}

std::string User::getBio() const {
    return getName()+" is a "+getTextUserType()+"\n"
    +"he/she was registered by "+getCreator()+" and currently "+(getRoom() != -1 ? "lives in room #"+std::to_string(getRoom()) : "is homeless")+"\n";
}
