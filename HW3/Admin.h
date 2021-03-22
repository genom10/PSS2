//
// Created by genom10 on 07.03.2021.
//

#ifndef HW2_ADMIN_H
#define HW2_ADMIN_H

#include "User.h"
#include "UserType.h"

class Admin: public User {
public:
    Admin(std::string name, std::string creator);
    User* createUser(UserType::Type, std::string name);
    void changeUserType(User*, UserType::Type);
};


#endif //HW2_ADMIN_H
