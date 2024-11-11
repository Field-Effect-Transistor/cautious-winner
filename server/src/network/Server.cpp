#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <array>
#include "Server.hpp"

Server::Server(unsigned short port, Database& db, boost::asio::io_context& io_context) :
    db(db), 
    acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    
    std::cout << "Server created on port " << port << std::endl;
    startAccept();
}

Server::~Server() {
    std::cout << "Server destroyed" << std::endl;
}

void Server::startAccept() {
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context);

    acceptor.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        if (!ec) {
            try {
                // Отримання IP-адреси клієнта
                auto remoteEndpoint = socket->remote_endpoint();
                std::string clientIP = remoteEndpoint.address().to_string();
                unsigned short clientPort = remoteEndpoint.port();

                std::cout << "Client connected from IP: " << clientIP 
                          << " Port: " << clientPort << std::endl;
                
                // Передаємо обробку клієнта в окремий потік
                std::thread(&Server::handleClient, this, socket).detach();
            } catch (const std::exception& e) {
                std::cerr << "Error retrieving client IP: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Error accepting connection: " << ec.message() << std::endl;
        }

        // Очікуємо наступне підключення після завершення поточного
        startAccept();
    });
}

// Зміни у функції handleClient
void Server::handleClient(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
    try {
        // Відправка привітального повідомлення
        std::string welcomeMessage = "Welcome to the server!\n";
        boost::system::error_code ec;
        boost::asio::write(*socket, boost::asio::buffer(welcomeMessage), ec);
        
        if (ec) {
            std::cerr << "Error sending welcome message: " << ec.message() << std::endl;
            return; // Якщо не вдалося відправити, виходимо з обробки клієнта
        }

        bool keepConnection = true;
        bool isLogined = false;
        std::string bigData;

        while (keepConnection) {
            // Читання запиту від клієнта
            std::array<char, 1024> buffer;
            size_t len = socket->read_some(boost::asio::buffer(buffer), ec);
            
            if (!ec) {
                std::string request(buffer.data(), len);
                std::cout << "Received request from IP: " << socket->remote_endpoint().address().to_string() << std::endl;
                std::cout << "Request: " << request << std::endl;
                std::string response = processRequest(request, keepConnection, isLogined, bigData);

                // Відправка відповіді на запит клієнта
                boost::asio::write(*socket, boost::asio::buffer(response), ec);
                
                if (ec) {
                    std::cerr << "Error sending response: " << ec.message() << std::endl;
                    break; // Виходимо з циклу, якщо не вдалося відправити
                }

                // Перевіряємо, чи потрібно закрити з'єднання
                if (!keepConnection) {
                    std::cout << "Closing connection with client from IP: " << socket->remote_endpoint().address().to_string() << std::endl;
                    break;
                }
            } else {
                std::cerr << "Error reading request: " << ec.message() << std::endl;
                break; // Виходимо з циклу у разі помилки
            }
        }

        // Закриття з'єднання з клієнтом
        socket->close();
    } catch (std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
    }
}

std::string Server::processRequest(
    const std::string& request,
    bool& keepConnection,
    bool& isLogined,
    std::string& bigData
) {
    try {
        boost::json::value jsonRequest = boost::json::parse(request);
        if (!jsonRequest.as_object().contains("command")) {
            return "{\"status\":\"error\",\"message\":\"Invalid request format\"}";
        }

        std::string command = boost::json::value_to<std::string>(jsonRequest.as_object().at("command"));

        if (command == "REGISTER_USER") {
            return registerUser(jsonRequest);
        } else if (command == "CLOSE_CONNECTION") {
            // Якщо команда "CLOSE_CONNECTION", змінюємо флаг для закриття з'єднання
            keepConnection = false;
            return "{\"status\":\"success\",\"message\":\"Connection will be closed.\"}";
        } else if (command == "USER_LOGIN") {
            return userLogIn(jsonRequest, isLogined);
        } else if (command == "GUEST_LOGIN") {
            return guestLogIn(isLogined);
        } else if (command == "GET_MAP") {
            return getMap(bigData);
        } else if (command == "BIG_DATA_TRANSFER"){
            return bigDataTransfer(bigData);
        } else if (command == "PARKING") {
            return parking(jsonRequest, isLogined);
        } else if (command == "BOOKING") {
            return booking(jsonRequest, isLogined);
        } else if ( command == "END_PARKING") {
            return endParking(jsonRequest, isLogined);
        } else if (command == "GET_PARKING_LIST") {
            return getParkingList(jsonRequest, isLogined, bigData);
        }

        return "{\"status\":\"error\",\"message\":\"Unknown command\"}";

    } catch (const std::exception& e) {
        return "{\"status\":\"error\",\"message\":\"Error processing request: " + std::string(e.what()) + "\"}";
    }
}

std::string Server::registerUser(const boost::json::value& jsonRequest) {
    std::string email = boost::json::value_to<std::string>(jsonRequest.as_object().at("email"));
    std::string password = boost::json::value_to<std::string>(jsonRequest.as_object().at("password"));
    std::string lPlate = boost::json::value_to<std::string>(jsonRequest.as_object().at("lPlate"));

    User user(db);

    int handler;
    user.createUser(email, password, lPlate, handler);

    if (handler == User::Handler::SUCCESS) {
        return "{\"status\":\"success\"}";
    } else if (handler == User::Handler::NOT_UNIQUE_USER) {
        return "{\"status\":\"error\",\"message\":\"User already exists\"}";
    } else {
        return "{\"status\":\"error\",\"message\":\"Failed to create user\"}";
    }
}

std::string Server::userLogIn(const boost::json::value& jsonRequest, bool& isLogined) {
    User user(db);

    std::string email = boost::json::value_to<std::string>(jsonRequest.as_object().at("email"));
    std::string password = boost::json::value_to<std::string>(jsonRequest.as_object().at("password"));

    isLogined = 0;
    int handler;
    bool temp = user.auth(email, password, handler);

    if (handler == User::Handler::SUCCESS) {
        isLogined = temp;
        if (temp) {
            boost::json::object toClient;
            toClient["status"] = "success";
            toClient["user_id"] = user.getId();
            toClient["lPlate"] = user.getLPlate();
            return boost::json::serialize(toClient);
        } else {
            return "{\"status\":\"error\",\"message\":\"Wrong password or email\"}";
        }
    } else if(handler == User::Handler::ERROR){
        return "{\"status\":\"error\",\"message\":\"ServerPart error, please try again.\"}";
    } else if(handler == User::Handler::USER_NOT_FOUND){
        return "{\"status\":\"error\",\"message\":\"Wrong passwort or email\"}";
    } else {
        return "{\"status\":\"error\",\"message\":\"Failed to log in for unknown reason.\"}";
    }
}

std::string Server::guestLogIn(bool& isLogined) {
    isLogined = 1;
    return "{\"status\":\"success\"}";
}

std::string Server::getMap(std::string& bigData) {
    Slot slot(db);  
    bigData =  slot.getMap();

    return "{\"status\":\"startBigDataTransfering\",\"command\":\"GET_MAP\"}";
}

std::string Server::bigDataTransfer(std::string& bigData) {
    boost::json::object toClient;

    toClient["data"] = bigData.substr(0, 512);
    bigData.erase(0, 512);

    if(bigData.empty()) {
        toClient["status"] = "endBigDataTransfering";
    } else {
        toClient["status"] = "bigDataTransfering";
    }

    return boost::json::serialize(toClient);
}

std::string Server::parking(const boost::json::value& jsonRequest, const bool& isLogined) {
    if (isLogined) {
        Parking parking(db);
        int handler;
        int slot_id = boost::json::value_to<int>(jsonRequest.as_object().at("slot_id"));
        int user_id = boost::json::value_to<int>(jsonRequest.as_object().at("user_id"));
        std::string lPlate = boost::json::value_to<std::string>(jsonRequest.as_object().at("lPlate"));
        parking.addParking(slot_id, user_id, lPlate, handler);

        switch (handler) {
            case Parking::Handler::SUCCESS:
                return "{\"status\":\"success\"}";
            case Parking::Handler::SLOT_OCCUPIED:
                return "{\"status\":\"error\",\"message\":\"Slot is occupied\"}"; 
        }
        return "{\"status\":\"error\",\"message\":\"Failed to add parking via server part\"}";
    } else {
        return "{\"status\":\"error\",\"message\":\"You are not logged in\"}";
    }
}

std::string Server::booking(const boost::json::value& jsonRequest, const bool& isLogined) {
    if (isLogined) {
        Parking parking(db);
        int handler;
        std::time_t startTime = boost::json::value_to<std::time_t>(jsonRequest.as_object().at("startTime"));
        std::time_t endTime = boost::json::value_to<std::time_t>(jsonRequest.as_object().at("endTime"));
        int slot_id = boost::json::value_to<int>(jsonRequest.as_object().at("slot_id"));
        int user_id = boost::json::value_to<int>(jsonRequest.as_object().at("user_id"));
        std::string lPlate = boost::json::value_to<std::string>(jsonRequest.as_object().at("lPlate"));
        parking.addBooking(startTime, endTime, slot_id, user_id, lPlate, handler);
        switch (handler) {
            case Parking::Handler::SUCCESS:
                return "{\"status\":\"success\"}";
            case Parking::Handler::SLOT_OCCUPIED:
                return "{\"status\":\"error\",\"message\":\"Slot is occupied\"}"; 
            case Parking::Handler::INVALID_TIME_PERIOD:
                return "{\"status\":\"error\",\"message\":\"Invalid time period\"}";
        }

        return "{\"status\":\"error\",\"message\":\"Failed to add booking via server part\"}";

    } else {
        return "{\"status\":\"error\",\"message\":\"You are not logged in\"}";
    }
}

std::string Server::endParking(const boost::json::value& jsonRequest, const bool& isLogined) {
    if (isLogined) {
        Parking parking(db);
        int handler;

        int slot_id = boost::json::value_to<int>(jsonRequest.as_object().at("slot_id"));
        int user_id = boost::json::value_to<int>(jsonRequest.as_object().at("user_id"));
        std::string lPlate = boost::json::value_to<std::string>(jsonRequest.as_object().at("lPlate"));

        parking.endParking(slot_id, user_id, lPlate, handler);

        switch (handler) {
            case Parking::Handler::SUCCESS:
                return "{\"status\":\"success\"}";
            case Parking::Handler::SLOT_NOT_OCCUPIED:
                return "{\"status\":\"error\",\"message\":\"Slot is not occupied\"}"; 
        }
        return "{\"status\":\"error\",\"message\":\"Failed to end parking via server part\"}";

    } else {
        return "{\"status\":\"error\",\"message\":\"You are not logged in\"}";
    }
}

std::string Server::getParkingList(
    const boost::json::value& jsonRequest,
    const bool& isLogined,
    std::string& bigData
) {
    if (true) {
        Parking parking(db);
        int handler;
        boost::json::object toClient;
        std::string temp;

        int user_id = boost::json::value_to<int>(jsonRequest.as_object().at("user_id"));
        std::string lPlate = boost::json::value_to<std::string>(jsonRequest.as_object().at("lPlate"));

        if (user_id != -1) {
            temp = parking.getParkings(user_id, handler);
            std::cout << user_id << " " << temp << " " << handler << std::endl;
            if (handler == Parking::Handler::SUCCESS ) {
                toClient["userParkings"] = temp;
            } else {
                return "{\"status\":\"error\",\"message\":\"Failed to get parkings via server part\"}";
            }
        }
        
        temp = parking.getParkings(lPlate, handler);
            std::cout << user_id << " " << temp << " " << handler << std::endl;
        if (handler == Parking::Handler::SUCCESS ) {
            toClient["lPlateParkings"] = temp;
        } else {
            return "{\"status\":\"error\",\"message\":\"Failed to get parkings via server part\"}";
        }

        toClient["status"] = "success";
        bigData = boost::json::serialize(toClient);
        return "{\"status\":\"startBigDataTransfering\",\"command\":\"GET_PARKING_LIST\"}";
    } else {
        return "{\"status\":\"error\",\"message\":\"You are not logged in\"}";
    }

}