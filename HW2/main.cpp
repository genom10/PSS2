//
// Created by genom_10 on 07.03.2021.
//

#include <iostream>
#include "Classroom.h"
#include "User.h"
#include "Admin.h"
#include "Professor.h"
#include "Director.h"
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
    students.reserve(16);
    for (int i = 0; i < 8; i++){
        students.push_back(admin1->createUser(UserType::student,"student "+to_string(i)));
    }
    for (int i = 8; i < 16; i++){
        students.push_back(admin2->createUser(UserType::student,"student "+to_string(i)));
    }

    vector<Professor*> professors;
    professors.reserve(16);
    for (int i = 0; i < 8; i++){
        professors.push_back(dynamic_cast<Professor*>(admin1->createUser(UserType::professor,"professor "+to_string(i))));
    }
    for (int i = 8; i < 16; i++){
        professors.push_back(dynamic_cast<Professor*>(admin2->createUser(UserType::professor,"professor "+to_string(i))));
    }

    vector<Director*> directors;
    directors.reserve(8);
    directors.push_back(dynamic_cast<Director*>(admin1->createUser(UserType::director,"director 0")));
    auto director = directors[0];

    vector<User*> lab_employees;
    students.reserve(8);
    for (int i = 0; i < 4; i++){
        students.push_back(admin1->createUser(UserType::lab_employee,"lab_employee "+to_string(i)));
    }
    for (int i = 4; i < 8; i++){
        students.push_back(admin2->createUser(UserType::lab_employee,"lab_employee "+to_string(i)));
    }


    admin1->hasAccessTo(*classrooms[0]);
    students[3]->hasAccessTo(*classrooms[15]);

    cout << admin1->getBio() << '\n';
    admin1->setRoom(404);
    cout << admin1->getBio() << '\n';
    cout << professors[7]->getBio() << '\n';
    cout << students[8]->getBio();
    director->drop(students[8], students);
    cout << '\n';
    cout << students[8]->getBio() << '\n';
    return 0;
}
