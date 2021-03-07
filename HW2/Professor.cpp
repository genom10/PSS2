//
// Created by genom_10 on 07.03.2021.
//

#include "Professor.h"

Professor::Professor(std::string name, std::string creator) : User(UserType::professor, std::move(name), creator) {
    this->type = UserType::professor;
}

const std::string &Professor::getFavJoke() const {
    return favJoke;
}

std::string Professor::getBio() const {
    return getName()+" is a "+getTextUserType()+"\n"
           +"he/she was registered by "+getCreator()+" and currently "+(getRoom() != -1 ? "lives in room #"+std::to_string(getRoom()) : "is homeless")+"\n"
           +(favJoke=="" ? "and hi/she has no favorite joke" : "and his/her favorite joke is: "+favJoke);
}