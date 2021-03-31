//
// Created by egord on 07.03.2021.
//

#include <iostream>
#include "Director.h"

Director::Director(std::string name, std::string creator) : User(UserType::professor, std::move(name), creator){}

void Director::drop(User* toDrop, std::vector<User*> &dropFrom) {
    for (int i = 0; i < dropFrom.size(); i++){
        if (dropFrom[i] == toDrop){
            std::cout << this->getName()+" has dropped "+toDrop->getName()+"\n Press F to pay respect\n";
            dropFrom.erase(dropFrom.begin()+i);
        }
    }
}

