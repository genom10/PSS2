#include <iostream>
#include "../includes/sqlite_orm.h"

using namespace sqlite_orm;


struct PassengerRecord{
    int id;
    std::string login;
    std::string password;
    std::string name;
    int rating;
    std::string orderHistory;
    std::string paymentMethods;
    std::string pinnedAddresses;
    PassengerRecord(std::string login, std::string password, std::string name){
        this->login = login;
        this->password = password;
        this->name = name;
    }
};

class Passenger{
    int id;
    std::string login;
    std::string password;
    std::string name;
    int rating;
    std::vector<std::string> orderHistory;
    std::vector<std::string> paymentMethods;
    std::vector<std::string> pinnedAddresses;

public:

//    static void ListAll(){
//        auto storage = make_storage("users.sqlite",
//                                    make_unique_index("idx_passengers_login", indexed_column(&PassengerRecord::login).collate("BINARY").desc()),
//                                    make_table("users",
//                                               make_column("id", &PassengerRecord::id, primary_key()),
//                                               make_column("login", &PassengerRecord::login),
//                                               make_column("password", &PassengerRecord::password),
//                                               make_column("name", &PassengerRecord::name),
//                                               make_column("rating", &PassengerRecord::rating),
//                                               make_column("orderHistory", &PassengerRecord::orderHistory),
//                                               make_column("paymentMethods", &PassengerRecord::paymentMethods),
//                                               make_column("pinnedAddresses", &PassengerRecord::pinnedAddresses)));
//        storage.sync_schema();
//        for (int i = 0; i < 10; i++){
//            if(auto user = storage.get_pointer<PassengerRecord>(i)){
//                std::cout << "user = " << user->login << " " << user->password << std::endl;
//            }else{
//                std::cout << "no user with id " << i << std::endl;
//            }
//        }
//    }

    Passenger(std::tuple <int, std::string, std::string, std::string, int, std::string, std::string, std::string> data) {
        //initialization from SQLite
        this->id = std::get<0>(data);
        this->login = std::get<1>(data);
        this->password = std::get<2>(data);
        this->name = std::get<3>(data);
        this->rating = std::get<4>(data);

        std::string rawOrderHistory = std::get<5>(data);
        std::stringstream ss(rawOrderHistory);
        std::string str;
        while (getline(ss, str, ',')) {
            this->orderHistory.push_back(str);
        }

        std::string rawPaymentMethods = std::get<6>(data);
        ss = std::stringstream(rawPaymentMethods);
        while (getline(ss, str, ',')) {
            this->paymentMethods.push_back(str);
        }

        std::string rawPinnedAddresses = std::get<7>(data);
        ss = std::stringstream(rawPinnedAddresses);
        while (getline(ss, str, ',')) {
            this->pinnedAddresses.push_back(str);
        }
    }

    Passenger() {
    }

    int getID(){
        return id;
    }

    static bool fetchLogin(std::string login){
        auto storage = make_storage("users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&PassengerRecord::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &PassengerRecord::id, primary_key()),
                                               make_column("login", &PassengerRecord::login),
                                               make_column("password", &PassengerRecord::password),
                                               make_column("name", &PassengerRecord::name),
                                               make_column("rating", &PassengerRecord::rating),
                                               make_column("orderHistory", &PassengerRecord::orderHistory),
                                               make_column("paymentMethods", &PassengerRecord::paymentMethods),
                                               make_column("pinnedAddresses", &PassengerRecord::pinnedAddresses)));
        storage.sync_schema();

        auto row = storage.select(columns(&PassengerRecord::id,
                                          &PassengerRecord::login,
                                          &PassengerRecord::password,
                                          &PassengerRecord::name,
                                          &PassengerRecord::rating,
                                          &PassengerRecord::orderHistory,
                                          &PassengerRecord::paymentMethods,
                                          &PassengerRecord::pinnedAddresses),
                                  where(is_equal(&PassengerRecord::login, login)));
        return row.empty();
    }
    static Passenger logIn(std::string login, std::string password){
        auto storage = make_storage("users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&PassengerRecord::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &PassengerRecord::id, primary_key()),
                                               make_column("login", &PassengerRecord::login),
                                               make_column("password", &PassengerRecord::password),
                                               make_column("name", &PassengerRecord::name),
                                               make_column("rating", &PassengerRecord::rating),
                                               make_column("orderHistory", &PassengerRecord::orderHistory),
                                               make_column("paymentMethods", &PassengerRecord::paymentMethods),
                                               make_column("pinnedAddresses", &PassengerRecord::pinnedAddresses)));
        storage.sync_schema();

        auto row = storage.select(columns(&PassengerRecord::id,
                                          &PassengerRecord::login,
                                          &PassengerRecord::password,
                                          &PassengerRecord::name,
                                          &PassengerRecord::rating,
                                          &PassengerRecord::orderHistory,
                                          &PassengerRecord::paymentMethods,
                                          &PassengerRecord::pinnedAddresses),
                                  where(is_equal(&PassengerRecord::login, login)));
        Passenger passenger{row[0]};
        if (passenger.password == password)
            return Passenger(row[0]);
        else
            throw "password mismatch";
    }

    static Passenger reg(std::string login, std::string password, std::string name){
        auto storage = make_storage("users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&PassengerRecord::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &PassengerRecord::id, primary_key()),
                                               make_column("login", &PassengerRecord::login),
                                               make_column("password", &PassengerRecord::password),
                                               make_column("name", &PassengerRecord::name),
                                               make_column("rating", &PassengerRecord::rating),
                                               make_column("orderHistory", &PassengerRecord::orderHistory),
                                               make_column("paymentMethods", &PassengerRecord::paymentMethods),
                                               make_column("pinnedAddresses", &PassengerRecord::pinnedAddresses)));
        storage.sync_schema();

        PassengerRecord passenger{login, password, name};
        int id = storage.insert(passenger);
        return Passenger(storage.select(columns(&PassengerRecord::id,
                                                    &PassengerRecord::login,
                                                    &PassengerRecord::password,
                                                    &PassengerRecord::name,
                                                    &PassengerRecord::rating,
                                                    &PassengerRecord::orderHistory,
                                                    &PassengerRecord::paymentMethods,
                                                    &PassengerRecord::pinnedAddresses),
                                            where(is_equal(&PassengerRecord::id, id)))[0]);
    }

    static void remove(Passenger *passenger) {
        auto storage = make_storage("users.sqlite",
                                    make_unique_index("idx_passengers_login", indexed_column(&PassengerRecord::login).collate("BINARY").desc()),
                                    make_table("users",
                                               make_column("id", &PassengerRecord::id, primary_key()),
                                               make_column("login", &PassengerRecord::login),
                                               make_column("password", &PassengerRecord::password),
                                               make_column("name", &PassengerRecord::name),
                                               make_column("rating", &PassengerRecord::rating),
                                               make_column("orderHistory", &PassengerRecord::orderHistory),
                                               make_column("paymentMethods", &PassengerRecord::paymentMethods),
                                               make_column("pinnedAddresses", &PassengerRecord::pinnedAddresses)));
        storage.sync_schema();

        storage.remove<PassengerRecord>(passenger->getID());
        passenger = NULL;
    }
};


class PassengerGateway{

};

void mainMenu(Passenger*);
void loginMenu(Passenger*);
void regMenu(Passenger*);
void userMenu(Passenger *passenger);

int main() {
    //Passenger::ListAll();
    Passenger passenger;
    mainMenu(&passenger);

    return 0;
}

void mainMenu(Passenger* passenger){
    int choice;
    while (true){
        std::cout << "1 - login\n2 - register\n3 - exit\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                loginMenu(passenger);
                break;
            case 2:
                regMenu(passenger);
                break;
            case 3:
                return;
            default:
                std::cout << "incorrect input\n";
        }
    }
}

void regMenu(Passenger* passenger){
    std::string login;
    std::string password;
    std::string name;
    std::cout << "\ntype your login: ";
    std::cin >> login;
    while (!Passenger::fetchLogin(login)){
        std::cout << "this login is already in use: ";
        std::cin >> login;
    }
    std::cout << "type your password: ";
    std::cin >> password;
    std::cout << "type your name: ";
    std::cin >> name;
    *passenger = Passenger::reg(login, password, name);
    userMenu(passenger);
}

void loginMenu(Passenger* passenger){
    std::string login;
    std::string password;
    std::string name;
    std::cout << "\ntype your login: ";
    std::cin >> login;
    while (Passenger::fetchLogin(login)){
        std::cout << "There's no user with such login: ";
        std::cin >> login;
    }
    std::cout << "type your password: ";
    std::cin >> password;
    *passenger = Passenger::logIn(login, password);
    userMenu(passenger);
}

void userMenu(Passenger* passenger){
    int choice;
    std::cout << "your ID is " << passenger->getID() << '\n';
    while (true) {
        std::cout << "1 - delete profile\n2 - return";
        std::cin >> choice;
        switch (choice) {
            case 1:
                Passenger::remove(passenger);
                return;
            case 2:
                return;
            default:
                std::cout << "incorrect input\n";
        }
    }
}