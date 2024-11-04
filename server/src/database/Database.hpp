#pragma once

#include <sqlite3.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

class Database {
private:
    sqlite3 *db;
    //void init(void);

public:
    Database(const std::string &dbPath);
    ~Database();
    void exec(const std::string &querry);
    void execFromFile(const std::string &filePath);
    sqlite3* getDB(void) const;
};