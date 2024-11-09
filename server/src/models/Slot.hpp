#pragma once 

#include "../database/Database.hpp"

#include <ctime>
#include <boost/json.hpp>

class Slot {
private:
    Database& db;

    int slot_id;
    std::string status;

public:
    Slot(Database& db);
    ~Slot();

    void init();
    std::string defineSlotStatus(int slot_id);
    void updateSlotStatus(int slot_id);
    void updateAllSlots(void);
    
    std::string getMap();
};