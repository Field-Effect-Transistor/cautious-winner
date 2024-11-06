#pragma once

#include "../database/Database.hpp"

#include <ctime>
#include <list>

class Parking {
    private:
        Database& db;

        int id;
        int type;
        int start_date;
        int end_date;
        int slot_id;
        int user_id;
        std::string lPlate;

        int lastHandler;
public:
    Parking(Database& db);
    ~Parking();

    Parking& addParking(
        int slot_id,
        int user_id,
        const std::string& lPlate,
        int& handler
    );

    inline Parking& addParking(
        int slot_id,
        int user_id,
        const std::string& lPlate
    ) { return addParking( slot_id, user_id, lPlate, lastHandler); }

    Parking& addBooking(
        const std::time_t& startTime,
        const std::time_t& endTime,
        int slot_id,
        int user_id,
        const std::string& lPlate,
        int& handler
    );

    inline Parking& addBooking(
        const std::time_t& startTime,
        const std::time_t& endTime,
        int slot_id,
        int user_id,
        const std::string& lPlate
    ) { return addBooking(startTime, endTime, slot_id, user_id, lPlate, lastHandler); }

    std::list<Parking> getParkings(int user_id, int& handler);
    inline std::list<Parking> getParkings(int user_id) {
        return getParkings(user_id, lastHandler);
    }

    std::list<Parking> getParkings(const std::string lPlate, int& handler);
    inline std::list<Parking> getParkings(const std::string lPlate) {
        return getParkings(lPlate, lastHandler);
    }

    std::string toJson() const;

    enum Handler {
        ERROR = -1,
        SUCCESS = 0
    };

};