#include "User.hpp"

User::User(Database& db) : db(db) {
    lastHandler = SUCCESS;
};

User::~User() {};

#include <stdexcept>
#include <sqlite3.h>
#include <string>
#include "User.hpp"

User& User::findUser(int id, int& handler) {
    std::string query = "SELECT user_id, email, password, lPlate FROM Users WHERE user_id = ?";
    sqlite3_stmt* stmt;

    // Підготовка запиту
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        handler = Handler::ERROR;  
        return *this;
    }

    // Прив'язка параметра `id`
    sqlite3_bind_int(stmt, 1, id);

    // Виконання запиту та перевірка результату
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        this->id = sqlite3_column_int(stmt, 0);
        this->email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        this->password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        this->lPlate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        
        handler = Handler::SUCCESS;  // 0 для успішного виконання
    } else {
        handler = Handler::USER_NOT_FOUND;  // 1 для помилки — користувача не знайдено
    }

    // Завершення запиту
    sqlite3_finalize(stmt);
    return *this;
}

User& User::findUser(std::string email_, int& handler) {
    std::string query = "SELECT user_id, email, password, lPlate FROM Users WHERE email = ?";
    sqlite3_stmt* stmt;
    
    // Підготовка запиту
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        handler = ERROR;  
        return *this;
    }

    // Прив'язка параметра `email`
    sqlite3_bind_text(stmt, 1, email_.c_str(), -1, SQLITE_STATIC);

    // Виконання запиту та перевірка результату
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        this->id = sqlite3_column_int(stmt, 0);
        this->email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        this->password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        this->lPlate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        
        handler = SUCCESS;  // 0 для успішного виконання
    } else {
        handler = USER_NOT_FOUND;  // 1 для помилки — користувача не знайдено
    }

    // Завершення запиту
    sqlite3_finalize(stmt);
    return *this;
}

User& User::createUser(std::string email_, std::string password_, std::string lPlate_) {
    std::string query = "INSERT INTO Users (email, password, lPlate) VALUES (?, ?, ?)";
    sqlite3_stmt* stmt;
    
    // Підготовка запиту
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare createUser statement");
    }

    // Прив'язка параметрів
    sqlite3_bind_text(stmt, 1, email_.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password_.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, lPlate_.c_str(), -1, SQLITE_STATIC);

    // Виконання запиту та перевірка результату
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to create user");
    }

    // Завершення запиту
    sqlite3_finalize(stmt);
    return findUser(email_);
}

void User::deleteUser(int id) {
    std::string query = "DELETE FROM Users WHERE user_id = ?";
    sqlite3_stmt* stmt;
    
    // Підготовка запиту
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare deleteUser statement");
    }

    // Прив'язка параметра `id`
    sqlite3_bind_int(stmt, 1, id);  

    // Виконання запиту та перевірка результату
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to delete user");
    }

    // Завершення запиту
    sqlite3_finalize(stmt);
}

bool User::auth(std::string email_, std::string password_) {
    findUser(email_);
    return password == password_ && email == email_;
}

bool User::auth(std::string password_) {
    return password == password_;
}

std::string User::toJson() const {
    boost::property_tree::ptree pt;

    pt.put("id", id);
    pt.put("email", email);
    //pt.put("password", password);
    pt.put("lPlate", lPlate);

    std::ostringstream oss;
    boost::property_tree::write_json(oss, pt);
    return oss.str();
}