#include <iostream>

#include "database/Database.hpp"
#include "network/Server.hpp"

int main(int argc, char** argv) { 
    Database db("server/database/db.sqlite");
    boost::asio::io_context io_context;

    Server server(3469, db, io_context);

    io_context.run();

    return 0;
}
