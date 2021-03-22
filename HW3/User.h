//
// Created by genom10 on 07.03.2021.
//

#ifndef HW2_USER_H
#define HW2_USER_H

class UserList;

#include "UserType.h"
#include "AccessLevel.h"
#include "Classroom.h"

class User {
protected:
    UserType::Type type;
    int room = -1;
    std::string creator;
    std::string name;
    User(UserType::Type type, std::string name);
    virtual void f();

public:
    UserType::Type getUserType() const;
    void setUserType(UserType::Type userType);
    std::string getTextUserType() const;
    std::string getTextUserType(UserType::Type userType);
    bool hasAccessTo(const Classroom& classroom);
    int getRoom() const;
    void setRoom(int room);
    const std::string &getCreator() const;
    void setCreator(const std::string &creator);
    const std::string &getName() const;
    std::string getBio() const;
    User(UserType::Type type, std::string name, std::string creator);
};


#endif //HW2_USER_H
