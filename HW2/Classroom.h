//
// Created by genom_10 on 07.03.2021.
//

#ifndef HW2_CLASSROOM_H
#define HW2_CLASSROOM_H

#include <string>
#include "AccessLevel.h"


class Classroom {
private:
    AccessLevel::Level accessLevel;
public:
    Classroom(AccessLevel::Level level);
    AccessLevel::Level getAccessLevel();
    std::string getTextAccessLevel();
};

#endif //HW2_CLASSROOM_H
