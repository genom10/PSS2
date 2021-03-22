//
// Created by genom_10 on 07.03.2021.
//

#include "Classroom.h"

Classroom::Classroom(std::string number, AccessLevel::Level level){
    Classroom::number = std::move(number);
    accessLevel = level;
}

const std::string &Classroom::getNumber() const {
    return number;
}

void Classroom::setNumber(const std::string &number) {
    Classroom::number = number;
}

AccessLevel::Level Classroom::getAccessLevel() const {
    return accessLevel;
}

std::string Classroom::getTextAccessLevel() const{
    switch (accessLevel) {
        case AccessLevel::no_level : return "no_level";
        case AccessLevel::green : return "green";
        case AccessLevel::red : return "red";
        case AccessLevel::yellow : return "yellow";
    }
    return "unknown level";
}

void Classroom::setAccessLevel(AccessLevel::Level accessLevel) {
    Classroom::accessLevel = accessLevel;
}