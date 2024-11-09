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
    //int executedScenarios = 0;
    sqlite3_stmt* stmt;
    time_t currentTime = time(nullptr); // Поточний час для порівнянь

    // Сценарій 1: Вибірка паркувань типу 0 з порожнім end_date
    std::string query1 = "SELECT slot_id, type, start_date, end_date FROM Parking WHERE slot_id = ? AND type = 0 AND (end_date IS NULL OR end_date = 0)";

    if (sqlite3_prepare_v2(db.getDB(), query1.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error in preparing statement 1: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return "ERROR1";
    }

    sqlite3_bind_int(stmt, 1, slot_id);

    // Перевірка паркувань з типом 0 і порожнім end_date (сценарій 1)
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Всі ці паркування підпадають під сценарій 1
        // Оновлення їх поля end_date або інших даних можна тут виконати
        // Наприклад, оновлення кінцевої дати для паркування типу 0:
        int parkingId = sqlite3_column_int(stmt, 0);

        std::string updateQuery1 = "UPDATE Parking SET end_date = ? WHERE id = ?";
        sqlite3_stmt* updateStmt1;
        if (sqlite3_prepare_v2(db.getDB(), updateQuery1.c_str(), -1, &updateStmt1, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(updateStmt1, 1, static_cast<int>(currentTime));
            sqlite3_bind_int(updateStmt1, 2, parkingId);

            if (sqlite3_step(updateStmt1) == SQLITE_DONE) {
                
                return "BUSY"; // Сценарій 1 виконано
            }

            sqlite3_finalize(updateStmt1);
        }
    }

    sqlite3_finalize(stmt);

    // Сценарій 2: Вибірка паркувань типу 1, де дата кінця пізніша за поточну
    std::string query2 = "SELECT slot_id, type, start_date, end_date FROM Parking WHERE slot_id = ? AND type = 1 AND end_date > ?";

    if (sqlite3_prepare_v2(db.getDB(), query2.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return "ERROR2"; // Повернення без змін у випадку помилки
    }

    sqlite3_bind_int(stmt, 1, slot_id);
    sqlite3_bind_int64(stmt, 2, static_cast<long long>(currentTime));

    // Перевірка паркувань типу 1 з end_date пізніше поточного часу (сценарій 2)
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Це паркування підпадає під сценарій 2
        // Оновлення їх поля start_date, end_date або інших даних можна тут виконати
        int parkingId = sqlite3_column_int(stmt, 0);
        int startDate = sqlite3_column_int(stmt, 2);

        // Якщо start_date менше за поточний час, виконуємо оновлення
        if (startDate < currentTime) {
            std::string updateQuery2 = "UPDATE Parking SET end_date = ? WHERE id = ?";
            sqlite3_stmt* updateStmt2;
            if (sqlite3_prepare_v2(db.getDB(), updateQuery2.c_str(), -1, &updateStmt2, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(updateStmt2, 1, static_cast<int>(currentTime));
                sqlite3_bind_int(updateStmt2, 2, parkingId);

                if (sqlite3_step(updateStmt2) == SQLITE_DONE) {
                    return "BUSY"; // Сценарій 2 виконано
                }

                sqlite3_finalize(updateStmt2);
            }
        }
    }

    sqlite3_finalize(stmt);

    // Сценарій 3: Вибірка паркувань типу 1, де дата початку менша за поточну
    std::string query3 = "SELECT slot_id, type, start_date FROM Parking WHERE slot_id = ? AND type = 1 AND start_date < ?";

    if (sqlite3_prepare_v2(db.getDB(), query3.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return "ERROR3"; // Повернення без змін у випадку помилки
    }

    sqlite3_bind_int(stmt, 1, slot_id);
    sqlite3_bind_int64(stmt, 2, static_cast<long long>(currentTime));

    // Перевірка паркувань типу 1, де start_date менше поточного часу (сценарій 3)
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Це паркування підпадає під сценарій 3
        // Оновлення їх даних можна тут виконати, якщо потрібно
        int parkingId = sqlite3_column_int(stmt, 0);
        int startDate = sqlite3_column_int(stmt, 2);

        // Якщо дата початку менша за поточний час, можна виконати певну дію
        if (startDate < currentTime) {
            std::string updateQuery3 = "UPDATE Parking SET start_date = ? WHERE id = ?";
            sqlite3_stmt* updateStmt3;
            if (sqlite3_prepare_v2(db.getDB(), updateQuery3.c_str(), -1, &updateStmt3, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(updateStmt3, 1, static_cast<int>(currentTime));
                sqlite3_bind_int(updateStmt3, 2, parkingId);

                if (sqlite3_step(updateStmt3) == SQLITE_DONE) {
                    return "BOOKED"; // Сценарій 3 виконано
                }

                sqlite3_finalize(updateStmt3);
            }
        }
    }

    sqlite3_finalize(stmt);

    // Повертаємо кількість виконаних сценаріїв
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
    boost::json::array slotArray; // Масив для зберігання слотів у форматі JSON

    if (sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return "{}"; // Якщо виникла помилка при підготовці запиту, повертаємо порожній JSON
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Отримуємо slot_id і status з кожного рядка
        int slot_id = sqlite3_column_int(stmt, 0);
        const char* status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        // Створюємо JSON-об'єкт для кожного слота
        boost::json::object slotObject;
        slotObject["slot_id"] = slot_id;
        slotObject["status"] = status;

        // Додаємо об'єкт до масиву
        slotArray.push_back(std::move(slotObject));
    }

    sqlite3_finalize(stmt);

    // Повертаємо всю інформацію у вигляді JSON рядка
    boost::json::array responseArray = std::move(slotArray);
    return boost::json::serialize(responseArray);
}