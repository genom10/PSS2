//
// Created by genom_10 on 07.03.2021.
//

#include <iostream>
#include "Classroom.h"
#include "User.h"
#include "Admin.h"
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<Classroom*> classrooms;
    for (int i = 0; i < 8; i++){
        classrooms.push_back(new Classroom("30"+to_string(i), AccessLevel::yellow));
    }
    for (int i = 0; i < 2; i++){
        classrooms.push_back(new Classroom("20"+to_string(i), AccessLevel::green));
    }
    for (int i = 0; i < 4; i++){
        classrooms.push_back(new Classroom("40"+to_string(i), AccessLevel::red));
    }
    for (int i = 0; i < 16; i++){
        classrooms.push_back(new Classroom("10"+to_string(i), AccessLevel::no_level));
    }

    vector<Admin*> admins;
    admins.push_back(new Admin("firstborn", "god I guess"));
    admins.push_back(dynamic_cast<Admin*>(admins[0]->createUser(UserType::admin,"second in charge")));

    Admin* admin1 = admins[0];
    Admin* admin2 = admins[1];

    vector<User*> students;
    for (int i = 0; i < 8; i++){
        students.push_back(admin1->createUser(UserType::student,"student "+to_string(i)));
    }
    for (int i = 8; i < 16; i++){
        students.push_back(admin2->createUser(UserType::student,"student "+to_string(i)));
    }
    admin1->hasAccessTo(*classrooms[0]);
    students[3]->hasAccessTo(*classrooms[15]);

    cout << admin1->getBio();
    admin1->setRoom(404);
    cout << admin1->getBio();
    return 0;
}
