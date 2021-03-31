//
// Created by genom10 on 07.03.2021.
//

#ifndef HW3_ADMIN_H
#define HW3_ADMIN_H

#include "User.h"
#include "UserType.h"

class Admin: public User {
public:
    Admin(std::string name, std::string creator);
    User* createUser(UserType::Type, std::string name);
    void changeUserType(User*, UserType::Type);
    void triggerEmergency();
    void stopEmergency();
};


#endif //HW3_ADMIN_H
