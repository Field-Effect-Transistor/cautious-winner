#pragma once

#include <boost/asio.hpp>
#include <thread>
#include <list>
#include <iostream>
#include <boost/json.hpp>
#include <string>

#include "../models/Parking.hpp"
#include "../models/User.hpp"
#include "../database/Database.hpp"

class Server {
private:
    Database& db;

    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::io_context io_context;

public:
    Server(unsigned short port, Database& db, boost::asio::io_context& io_context);
    ~Server();

private:
    void startAccept();
    void handleClient(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

    std::string processRequest(const std::string& request, bool& keepConnection);
    std::string registerUser(const boost::json::value& jsonRequest);
};
