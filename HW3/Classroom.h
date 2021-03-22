//
// Created by genom_10 on 07.03.2021.
//

#ifndef HW2_CLASSROOM_H
#define HW2_CLASSROOM_H

#include <string>
#include "AccessLevel.h"


class Classroom {
private:
    std::string number;
    AccessLevel::Level accessLevel;
public:
    Classroom(std::string number, AccessLevel::Level level);
    const std::string &getNumber() const;
    void setNumber(const std::string &number);
    AccessLevel::Level getAccessLevel() const;
    std::string getTextAccessLevel() const;
    void setAccessLevel(AccessLevel::Level accessLevel);
};

#endif //HW2_CLASSROOM_H
