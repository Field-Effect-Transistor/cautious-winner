#include "Database.hpp"

Database::~Database() {
    sqlite3_close(db);
}

Database::Database(const std::string &dbPath) {
    int result = sqlite3_open(dbPath.c_str(), &db);
    if (result != SQLITE_OK) {
        throw std::runtime_error("Failed to open database: " + std::string(sqlite3_errmsg(db)));
    }

    execFromFile("server/database/init_db.sql");
}


void Database::execFromFile(const std::string &filePath) {
    if (std::filesystem::exists(filePath)) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::string line;
        std::stringstream sql;

        while (std::getline(file, line)) {
            //std::cout << line << std::endl;
            if (line.empty() || line[0] == '-') continue;
            sql << line;
            if (line.back() == ';') {
                exec(sql.str());
                sql.str("");
                sql.clear();
            }
        }
    } else {
        throw std::runtime_error("File not found: " + filePath);
    }
}

void Database::exec(const std::string &query) {
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK) {
        std::string errorMsg = "SQL error: " + std::string(errMsg);
        sqlite3_free(errMsg);
        throw std::runtime_error(errorMsg);
    }
}

sqlite3* Database::getDB(void) const {
    return db;
}