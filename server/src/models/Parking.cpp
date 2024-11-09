#include "Parking.hpp"

Parking::Parking(Database& db) : db(db), slot(new Slot(db)) {}

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

    slot->updateSlotStatus(slot_id);

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

    slot->updateSlotStatus(slot_id);

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
std::string Parking::getParkings(int user_id, int& handler) {

    slot->updateAllSlots();

    using boost::json::object;
    using boost::json::array;
    using boost::json::value;

    object jsonResponse;
    array parkings;

    sqlite3_stmt* stmt;
    std::string query = "SELECT id, type, start_date, end_date, slot_id, user_id, lPlate FROM Parking WHERE user_id = ?";
    
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        handler = Handler::PREPARE_ERROR;
        return "{}";  // Повертаємо порожній JSON у разі помилки
    }

    sqlite3_bind_int(stmt, 1, user_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        object parkingObj;
        parkingObj["slot_id"] = value{std::to_string(sqlite3_column_int(stmt, 4))};
        parkingObj["type"] = value{std::to_string(sqlite3_column_int(stmt, 1))};
        parkingObj["start_date"] = value{std::to_string(sqlite3_column_int(stmt, 2))};
        parkingObj["end_date"] = value{std::to_string(sqlite3_column_int(stmt, 3))};

        parkings.push_back(parkingObj);
    }

    sqlite3_finalize(stmt);

    jsonResponse["parkings"] = parkings;

    handler = Handler::SUCCESS;

    // Перетворюємо об'єкт Boost.JSON в рядок JSON
    return boost::json::serialize(jsonResponse);
}

std::string Parking::getParkings(const std::string& lPlate, int& handler) {
    slot->updateAllSlots();

    using boost::json::object;
    using boost::json::array;
    using boost::json::value;

    object jsonResponse;
    array parkings;

    sqlite3_stmt* stmt;
    std::string query = "SELECT id, type, start_date, end_date, slot_id, user_id, lPlate FROM Parking WHERE lPlate = ?";
    
    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        handler = Handler::PREPARE_ERROR;
        return "{}";  // Повертаємо порожній JSON у разі помилки
    }

    sqlite3_bind_text(stmt, 1, lPlate.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        object parkingObj;
        parkingObj["slot_id"] = value{std::to_string(sqlite3_column_int(stmt, 4))};
        parkingObj["type"] = value{std::to_string(sqlite3_column_int(stmt, 1))};
        parkingObj["start_date"] = value{std::to_string(sqlite3_column_int(stmt, 2))};
        parkingObj["end_date"] = value{std::to_string(sqlite3_column_int(stmt, 3))};

        parkings.push_back(parkingObj);
    }

    sqlite3_finalize(stmt);

    jsonResponse["parkings"] = parkings;

    handler = Handler::SUCCESS;

    // Перетворюємо об'єкт Boost.JSON в рядок JSON
    return boost::json::serialize(jsonResponse);
}

std::string Parking::toJson() const {
    using boost::json::object;
    using boost::json::value;

    // Створюємо об'єкт JSON
    object parkingObj;

    // Додаємо поля до об'єкта JSON
    parkingObj["id"] = value{id};
    parkingObj["type"] = value{type};
    parkingObj["start_date"] = value{start_date};
    parkingObj["end_date"] = value{end_date};
    parkingObj["slot_id"] = value{slot_id};
    parkingObj["user_id"] = value{user_id};
    parkingObj["lPlate"] = value{lPlate};

    // Перетворюємо об'єкт JSON у рядок
    return boost::json::serialize(parkingObj);
}

std::string Parking::getSlotParkings(int slot_id) {
    slot->updateAllSlots();
    
    using boost::json::array;
    using boost::json::object;
    using boost::json::value;

    // Створення масиву для паркувань
    array parkingsArray;

    sqlite3_stmt* stmt;
    std::string query = "SELECT type, start_date, end_date FROM Parking WHERE slot_id = ?";

    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // Повернення порожнього JSON у випадку помилки
        return "{}";
    }

    sqlite3_bind_int(stmt, 1, slot_id);

    // Перебір результатів запиту та додавання їх до масиву
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        object parkingObj;

        parkingObj["type"] = value{sqlite3_column_int(stmt, 0)};
        parkingObj["start_date"] = value{sqlite3_column_int(stmt, 1)};
        parkingObj["end_date"] = value{sqlite3_column_int(stmt, 2)};

        parkingsArray.push_back(parkingObj);
    }

    sqlite3_finalize(stmt);

    // Створення об'єкта JSON для повернення
    object resultObj;
    resultObj["parkings"] = parkingsArray;

    // Перетворення об'єкта JSON в рядок
    return boost::json::serialize(resultObj);
}