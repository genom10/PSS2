//
// Created by genom10 on 07.03.2021.
//

#ifndef HW2_USERTYPE_H
#define HW2_USERTYPE_H

#include "AccessLevel.h"
#include <map>
#include <set>

class UserType
{
public:
    enum Type
    {
        guest, student, professor, lab_employee, director, admin
    };
    static bool hasAccessTo(UserType::Type, AccessLevel::Level);
};


#endif //HW2_USERTYPE_H
