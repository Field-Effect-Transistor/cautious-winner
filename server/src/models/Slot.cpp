#include "Slot.hpp"

Slot::Slot(Database& db) : db(db) {
    init();
    updateAllSlots();
}

Slot::~Slot() {}

void Slot::init() {
    for (int id = 0; id <= 39; ++id) {
        // Перевіряємо, чи існує запис з даним slot_id
        std::string query = "SELECT COUNT(*) FROM slots WHERE slot_id = ?;";
        
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db.getDB())));
        }

        sqlite3_bind_int(stmt, 1, id);
        
        int step = sqlite3_step(stmt);
        bool slotExists = false;
        if (step == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            slotExists = (count > 0);
        }
        sqlite3_finalize(stmt);

        // Якщо слот не існує, додаємо його в базу даних
        if (!slotExists) {
            std::string insert_query = "INSERT INTO slots (slot_id, status) VALUES (?, 'FREE');";
            
            if (sqlite3_prepare_v2(db.getDB(), insert_query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
                throw std::runtime_error("Failed to prepare insert statement: " + std::string(sqlite3_errmsg(db.getDB())));
            }

            sqlite3_bind_int(stmt, 1, id);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                sqlite3_finalize(stmt);
                throw std::runtime_error("Failed to insert slot: " + std::string(sqlite3_errmsg(db.getDB())));
            }

            sqlite3_finalize(stmt);
        }
    }
}

std::string Slot::defineSlotStatus(int slot_id) {
    sqlite3_stmt* stmt;
    int status = STATUS::FREE;
    time_t currentTime = std::time(nullptr);

    // Перший SQL-запит для перевірки зайнятого паркомісця
    const char* sqlCheckBusy = R"(
        SELECT COUNT(*) FROM Parking 
        WHERE slot_id = ? 
          AND ((type = 0 AND end_date IS NULL) 
               OR (type = 1 AND start_date <= ? AND ? <= end_date))
    )";

    if (sqlite3_prepare_v2(db.getDB(), sqlCheckBusy, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, slot_id);
        sqlite3_bind_int64(stmt, 2, currentTime);
        sqlite3_bind_int64(stmt, 3, currentTime);

        if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_int(stmt, 0) > 0) {
            status = STATUS::BUSY;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing SQL statement (BUSY check): " << sqlite3_errmsg(db.getDB()) << std::endl;
    }

    // Якщо перший запит підтвердив "BUSY", повертаємо статус і виходимо
    if (status == STATUS::BUSY) return "BUSY";

    // Другий SQL-запит для перевірки заброньованого паркомісця
    const char* sqlCheckBooked = R"(
        SELECT COUNT(*) FROM Parking 
        WHERE slot_id = ? 
          AND type = 1 
          AND end_date >= ? 
          AND start_date >= ?
    )";

    if (sqlite3_prepare_v2(db.getDB(), sqlCheckBooked, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, slot_id);
        sqlite3_bind_int64(stmt, 2, currentTime);
        sqlite3_bind_int64(stmt, 3, currentTime);

        if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_int(stmt, 0) > 0) {
            status = STATUS::BOOKED;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing SQL statement (BOOKED check): " << sqlite3_errmsg(db.getDB()) << std::endl;
    }

    if (status == STATUS::BOOKED) return "BOOKED";

    // Якщо жоден з попередніх запитів не підтвердив статус "BUSY" або "BOOKED", повертаємо "FREE"
    return "FREE";
}


void Slot::updateSlotStatus(int slot_id) {
    try {
        // Викликаємо updateSlotStatus для кожного слота
        std::string status = defineSlotStatus(slot_id);

        // Оновлення статусу слота в базі даних (якщо потрібно)
        // Припустимо, ви можете зберігати цей статус в таблиці Slots
        std::string updateStatusQuery = "UPDATE Slots SET status = ? WHERE slot_id = ?";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db.getDB(), updateStatusQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db.getDB()) << std::endl;
            return;
        }

        sqlite3_bind_text(stmt, 1, status.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, slot_id);  // Передаємо id слота

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to update status for slot " << slot_id << ": " << sqlite3_errmsg(db.getDB()) << std::endl;
        }

        sqlite3_finalize(stmt);
    } catch (const std::exception& e) {
        std::cerr << "Error updating slot " << slot_id << ": " << e.what() << std::endl;
    }
}

void Slot::updateAllSlots() {
    for (int i = 0; i < 40; ++i) {
        updateSlotStatus(i);
    }
}

std::string Slot::getMap() {
    updateAllSlots();

    sqlite3_stmt* stmt;
    std::string query = "SELECT slot_id, status FROM Slots"; // Запит до таблиці Slots для отримання slot_id та status
    std::list<boost::json::object> slotList;

    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // Якщо виникла помилка при підготовці запиту, повертаємо JSON із повідомленням про помилку
        boost::json::object errorObj;
        errorObj["status"] = "error";
        errorObj["message"] = sqlite3_errmsg(db.getDB());
        return boost::json::serialize(errorObj);
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Отримуємо slot_id і status з кожного рядка
        int slot_id = sqlite3_column_int(stmt, 0);
        const char* status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        // Створюємо JSON-об'єкт для кожного слота
        boost::json::object slotObject;
        slotObject["slot_id"] = slot_id;
        slotObject["status"] = status;

        // Додаємо об'єкт до списку
        slotList.push_back(std::move(slotObject));
    }

    sqlite3_finalize(stmt);

    // Конвертуємо список об'єктів у JSON-масив
    boost::json::array jsonArray;
    for (const auto& slot : slotList) {
        jsonArray.push_back(slot);
    }

    // Повертаємо JSON-масив у вигляді рядка
    return boost::json::serialize(jsonArray);
}