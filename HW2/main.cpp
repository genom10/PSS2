//
// Created by genom_10 on 07.03.2021.
//

#include <iostream>
#include "Classroom.h"
#include "User.h"

using namespace std;

int main() {
    Classroom class1(AccessLevel::yellow);
    User user1(UserType::student);
    cout << user1.hasAccessTo(class1);
    return 0;
}
