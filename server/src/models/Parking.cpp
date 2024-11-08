#include "Parking.hpp"

Parking::Parking(Database& db) : db(db) {}

Parking::~Parking() {}

Parking& Parking::addParking(
    int slot_id,
    int user_id,
    const std::string& lPlate,
    int& handler
) {
    std::time_t currentTime = std::time(nullptr);

    // Перевірка, чи місце зайняте
    if (isParked(slot_id, currentTime, handler)) {
        if (handler == Handler::SUCCESS) {
            handler = Handler::SLOT_OCCUPIED; // Місце зайняте
        }
        return *this;
    }

    sqlite3_stmt* stmt;
    std::string query;

    // Якщо це гостьовий користувач, додаємо номерний знак
    if (user_id == -1) {
        query = "INSERT INTO Parking (type, start_date, slot_id, user_id, lPlate) VALUES (0, ?, ?, -1, ?)";
    } else {
        query = "INSERT INTO Parking (type, start_date, slot_id, user_id) VALUES (0, ?, ?, ?)";
    }

    // Підготовка запиту
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        handler = Handler::PREPARE_ERROR;
        return *this;
    }

    // Прив'язка параметрів
    sqlite3_bind_int(stmt, 1, static_cast<int>(currentTime));
    sqlite3_bind_int(stmt, 2, slot_id);
    if (user_id != -1) {
        sqlite3_bind_int(stmt, 3, user_id);
    } else {
        sqlite3_bind_text(stmt, 3, lPlate.c_str(), -1, SQLITE_STATIC);
    }

    // Виконання запиту
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        handler = Handler::SUCCESS; // Успішне додавання запису
    } else {
        handler = Handler::EXEC_ERROR; // Помилка виконання запиту
    }

    sqlite3_finalize(stmt);
    return *this;
}


Parking& Parking::addBooking(
    const std::time_t& startTime,
    const std::time_t& endTime,
    int slot_id,
    int user_id,
    const std::string& lPlate,
    int& handler
) {
    // Перевірка коректності часу початку і завершення
    if (endTime <= startTime) {
        handler = Handler::INVALID_TIME_PERIOD;
        return *this;
    }

    // Перевірка, чи місце зайняте в заданий період
    if (isParked(slot_id, startTime, handler)) {
        if (handler == Handler::SUCCESS) {
            handler = Handler::SLOT_OCCUPIED;
        }
        return *this;
    }

    sqlite3_stmt* stmt;
    std::string query;

    // Якщо це гостьовий користувач, додаємо номерний знак
    if (user_id == -1) {
        query = "INSERT INTO Parking (type, start_date, end_date, slot_id, user_id, lPlate) VALUES (1, ?, ?, ?, -1, ?)";
    } else {
        query = "INSERT INTO Parking (type, start_date, end_date, slot_id, user_id) VALUES (1, ?, ?, ?, ?)";
    }

    // Підготовка запиту
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        handler = Handler::PREPARE_ERROR;
        return *this;
    }

    // Прив'язка параметрів
    sqlite3_bind_int(stmt, 1, static_cast<int>(startTime));
    sqlite3_bind_int(stmt, 2, static_cast<int>(endTime));
    sqlite3_bind_int(stmt, 3, slot_id);
    if (user_id != -1) {
        sqlite3_bind_int(stmt, 4, user_id);
    } else {
        sqlite3_bind_text(stmt, 4, lPlate.c_str(), -1, SQLITE_STATIC);
    }

    // Виконання запиту
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        handler = Handler::SUCCESS; // Успішне додавання запису
    } else {
        handler = Handler::EXEC_ERROR; // Помилка виконання запиту
    }

    sqlite3_finalize(stmt);
    return *this;
}

bool Parking::isParked(int slot_id, std::time_t startTime, int& handler) {
    sqlite3_stmt* stmt;
    std::string query;

    // Перевірка, чи є активне паркування без вказаного endTime
    query = "SELECT COUNT(*) FROM Parking WHERE slot_id = ? AND end_date IS NULL";
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        handler = Handler::PREPARE_ERROR;
        return false;
    }

    sqlite3_bind_int(stmt, 1, slot_id);

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (count > 0) {
        handler = Handler::SUCCESS;
        return true; // Знайдено активне паркування без end_date
    }

    // Перевірка на наявність запису, де start_date менший за startTime і end_date більший за startTime
    query = "SELECT COUNT(*) FROM Parking WHERE slot_id = ? AND start_date <= ? AND end_date > ?";
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        handler = Handler::PREPARE_ERROR;
        return false;
    }

    sqlite3_bind_int(stmt, 1, slot_id);
    sqlite3_bind_int(stmt, 2, static_cast<int>(startTime));
    sqlite3_bind_int(stmt, 3, static_cast<int>(startTime));

    count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (count > 0) {
        handler = Handler::SUCCESS;
        return true; // Знайдено запис, що відповідає умові
    }

    handler = Handler::SUCCESS;
    return false; // Нічого не знайдено
}

std::list<std::string> Parking::getParkings(int user_id, int& handler) {
    std::list<std::string> jsonList;

    sqlite3_stmt* stmt;
    std::string query = "SELECT id, type, start_date, end_date, slot_id, user_id, lPlate FROM Parking WHERE user_id = ?";
    
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        handler = Handler::PREPARE_ERROR;
        return jsonList;
    }

    sqlite3_bind_int(stmt, 1, user_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Parking parking(db);
        parking.id = sqlite3_column_int(stmt, 0);
        parking.type = sqlite3_column_int(stmt, 1);
        parking.start_date = sqlite3_column_int(stmt, 2);
        parking.end_date = sqlite3_column_int(stmt, 3);
        parking.slot_id = sqlite3_column_int(stmt, 4);
        parking.user_id = sqlite3_column_int(stmt, 5);
        parking.lPlate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

        jsonList.push_back(parking.toJson());
    }

    sqlite3_finalize(stmt);
    handler = Handler::SUCCESS;
    return jsonList;
}

std::list<std::string> Parking::getParkings(const std::string& lPlate, int& handler) {
    std::list<std::string> jsonList;

    sqlite3_stmt* stmt;
    std::string query = "SELECT id, type, start_date, end_date, slot_id, user_id, lPlate FROM Parking WHERE lPlate = ?";
    
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        handler = Handler::PREPARE_ERROR;
        return jsonList;
    }

    sqlite3_bind_text(stmt, 1, lPlate.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Parking parking(db);
        parking.id = sqlite3_column_int(stmt, 0);
        parking.type = sqlite3_column_int(stmt, 1);
        parking.start_date = sqlite3_column_int(stmt, 2);
        parking.end_date = sqlite3_column_int(stmt, 3);
        parking.slot_id = sqlite3_column_int(stmt, 4);
        parking.user_id = sqlite3_column_int(stmt, 5);
        parking.lPlate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

        jsonList.push_back(parking.toJson());
    }

    sqlite3_finalize(stmt);
    handler = Handler::SUCCESS;
    return jsonList;
}


std::string Parking::toJson() const {
    boost::property_tree::ptree pt;

    pt.put("id", id);
    pt.put("type", type);
    pt.put("start_date", start_date);
    pt.put("end_date", end_date);
    pt.put("slot_id", slot_id);
    pt.put("user_id", user_id);
    pt.put("lPlate", lPlate);

    std::ostringstream oss;
    boost::property_tree::write_json(oss, pt);
    return oss.str();
}
