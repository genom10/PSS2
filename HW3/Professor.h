//
// Created by genom_10 on 07.03.2021.
//

#ifndef HW2_PROFESSOR_H
#define HW2_PROFESSOR_H


#include "User.h"

class Professor : public User {
private:
    std::string favJoke;

public:
    Professor(std::string name, std::string creator);
    const std::string &getFavJoke() const;
    void setFavJoke(const std::string &favJoke);
    std::string getBio() const;
};


#endif //HW2_PROFESSOR_H
