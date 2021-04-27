//
// Created by genom10 on 25.04.2021.
//

#include <iostream>
#include "../includes/sqlite_orm.h"

#include "Admin.h"
#include "AdminGateway.h"

int main() {
    Admin admin;
    AdminGateway::ListAllPassengers();
    return 0;
}