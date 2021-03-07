//
// Created by genom_10 on 07.03.2021.
//

#include "Classroom.h"
#include "AccessLevel.h"

Classroom::Classroom(AccessLevel::Level level){
    accessLevel = level;
}

AccessLevel::Level Classroom::getAccessLevel(){
    return accessLevel;
}

std::string Classroom::getTextAccessLevel(){
    switch (accessLevel) {
        case AccessLevel::no_level : return "no_level";
        case AccessLevel::green : return "green";
        case AccessLevel::red : return "red";
        case AccessLevel::yellow : return "yellow";
    }
}