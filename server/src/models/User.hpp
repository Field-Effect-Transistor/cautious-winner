#pragma once

#include "../database/Database.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdexcept>
#include <sqlite3.h>
#include <string>

class User {
private:
    Database& db;

    int id;
    std::string email;
    std::string password;
    std::string lPlate;

    mutable int lastHandler;
public:
    User(Database& db);
    ~User();

    User& findUser(int id, int& handler);
    inline  User& findUser(int id) { return findUser(id, lastHandler); }

    User& findUser(std::string email, int& handler);
    inline  User& findUser(std::string email) { return findUser(email, lastHandler); }

    User& createUser(std::string email_, std::string password_, std::string lPlate_, int& handler);
    inline User& createUser(std::string email_, std::string password_, std::string lPlate_) {
        return createUser(email_, password_, lPlate_, lastHandler);
    };

    bool auth(std::string email_, std::string password_, int& handler);
    inline bool auth(std::string email_, std::string password_) {
        return auth(email_, password_, lastHandler);
    }
    bool auth(std::string password_);

    int getLastHandler() const { return lastHandler; }

    std::string toJson() const;

    enum Handler {
        ERROR = -1,
        SUCCESS = 0,
        USER_NOT_FOUND = 1,
        NOT_UNIQUE_USER = 2
    };
};
