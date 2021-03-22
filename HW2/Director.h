//
// Created by egord on 07.03.2021.
//

#ifndef HW2_DIRECTOR_H
#define HW2_DIRECTOR_H

#include <vector>
#include "User.h"

class Director : public User {
public:
    Director(std::string name, std::string creator);
    void drop(User* toDrop, std::vector<User*>&);
};


#endif //HW2_DIRECTOR_H
