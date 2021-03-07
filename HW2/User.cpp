//
// Created by egord on 07.03.2021.
//

#include "User.h"

User::User(UserType::Type type) {
    userType = type;
}

UserType::Type User::getUserType() const {
    return userType;
}

void User::setUserType(UserType::Type userType) {
    User::userType = userType;
}

std::string User::getTextUserType() {
    switch(userType){
        case UserType::student : return "student";
        case UserType::admin : return "admin";
        case UserType::director : return "director";
        case UserType::lab_employee : return "lab_employee";
        case UserType::professor : return "professor";
    }
}

bool User::hasAccessTo(Classroom classroom) {
    return UserType::hasAccessTo(userType, classroom.getAccessLevel());
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