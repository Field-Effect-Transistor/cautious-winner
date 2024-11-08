#pragma once

#include "../database/Database.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
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

    std::list<std::string> getParkings(int user_id, int& handler);
    inline std::list<std::string> getParkings(int user_id) {
        return getParkings(user_id, lastHandler);
    }

    std::list<std::string> getParkings(const std::string& lPlate, int& handler);
    inline std::list<std::string> getParkings(const std::string& lPlate) {
        return getParkings(lPlate, lastHandler);
    }

    std::string toJson() const;

    bool isParked(int slot_id, std::time_t startTime, int& handler);

    enum Handler {
        EXEC_ERROR = -3,
        PREPARE_ERROR = -2,
        ERROR = -1,
        SUCCESS = 0,
        SLOT_OCCUPIED = 1,
        INVALID_TIME_PERIOD = 2
    };

};