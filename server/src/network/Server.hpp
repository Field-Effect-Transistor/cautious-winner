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

    std::string processRequest(
        const std::string& request,
        bool& keepConnection,
        bool& isLogined,
        std::string& bigData
    );
    std::string registerUser(const boost::json::value& jsonRequest);
    std::string userLogIn(const boost::json::value& jsonRequest, bool& isLogined);
    std::string guestLogIn(bool& isLogined);
    std::string parking(const boost::json::value& jsonRequest, const bool& isLogined);
    std::string endParking(const boost::json::value& jsonRequest, const bool& isLogined);
    std::string booking(const boost::json::value& jsonRequest, const bool& isLogined);
    std::string getMap(std::string& bigData);
    std::string getParkingList(
        const boost::json::value& jsonRequest,
        const bool& isLogined,
        std::string& bigData
    );
    std::string getSlotInfo(const boost::json::value& jsonRequest, const bool& isLogined);
    std::string bigDataTransfer(std::string& bigData);
};
