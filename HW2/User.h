//
// Created by egord on 07.03.2021.
//

#ifndef HW2_USER_H
#define HW2_USER_H


#include "UserType.h"
#include "AccessLevel.h"
#include "Classroom.h"

class User {
private:
    UserType::Type userType;
    int room;
    std::string creator;
public:
    User(UserType::Type);
    UserType::Type getUserType() const;
    void setUserType(UserType::Type userType);
    std::string getTextUserType();
    bool hasAccessTo(Classroom classroom);
    int getRoom() const;
    void setRoom(int room);
    const std::string &getCreator() const;
    void setCreator(const std::string &creator);
};


#endif //HW2_USER_H
