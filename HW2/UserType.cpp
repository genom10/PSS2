//
// Created by egord on 07.03.2021.
//

#include "UserType.h"

static std::map<UserType::Type, std::set<AccessLevel::Level>> accessMap={
        {UserType::student, {AccessLevel::no_level, AccessLevel::green}},
        {UserType::professor, {AccessLevel::no_level, AccessLevel::green, AccessLevel::yellow, AccessLevel::red}},
        {UserType::lab_employee, {AccessLevel::no_level, AccessLevel::green, AccessLevel::yellow}},
        {UserType::director, {AccessLevel::no_level, AccessLevel::yellow, AccessLevel::red}},
        {UserType::admin, {AccessLevel::no_level, AccessLevel::green, AccessLevel::yellow, AccessLevel::red, AccessLevel::absolute}},
};

bool UserType::hasAccessTo(UserType::Type type, AccessLevel::Level level){
    return accessMap[type].find(level) != accessMap[type].end();
}
