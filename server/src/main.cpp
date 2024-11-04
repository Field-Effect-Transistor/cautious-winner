#include <iostream>

#include "database/Database.hpp"
#include "models/User.hpp"

int main(int argc, char** argv) { 
    Database db("server/database/db.sqlite");

    User user(db);

    if(user.findUser("user8@example.com").getLastHandler() == User::Handler::SUCCESS) {
        std::cout << user.toJson() << std::endl;
    }

    return 0;
} 