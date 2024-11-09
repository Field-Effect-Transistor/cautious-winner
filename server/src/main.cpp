#include <iostream>

#include "database/Database.hpp"
#include "network/Server.hpp"
#include "models/Slot.hpp"

int main(int argc, char** argv) { 
    Database db("server/database/db.sqlite");
    Slot slot(db);    

    //std::cout << slot.getMap() << std::endl;

    boost::asio::io_context io_context;

    Server server(3469, db, io_context);

    io_context.run();

    return 0;
}
