#include <iostream>

#include "database/Database.hpp"
#include "models/User.hpp"

int main(int argc, char** argv) { 
    Database db("server/database/db.sqlite");

    User user(db);
    user.createUser("genocide@isUnixBad.com", "12345678", "1234");
    std::cout << user.getLastHandler() << std::endl;

    return 0;
}