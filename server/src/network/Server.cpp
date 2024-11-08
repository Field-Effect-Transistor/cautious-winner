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

        // Читання запиту від клієнта
        std::array<char, 1024> buffer;
        size_t len = socket->read_some(boost::asio::buffer(buffer), ec);
        
        if (!ec) {
            std::string request(buffer.data(), len);
            std::string response = processRequest(request);

            // Відправка відповіді на запит клієнта
            boost::asio::write(*socket, boost::asio::buffer(response), ec);
        } else {
            std::cerr << "Error reading request: " << ec.message() << std::endl;
        }

        // Закриття з'єднання з клієнтом
        socket->close();
    } catch (std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
    }
}

std::string Server::processRequest(const std::string& request) {
    try {
        boost::json::value jsonRequest = boost::json::parse(request);
        if (!jsonRequest.as_object().contains("command")) {
            return "{\"status\":\"error\",\"message\":\"Invalid request format\"}";
        }

        std::string command = boost::json::value_to<std::string>(jsonRequest.as_object().at("command"));

        if (command == "REGISTER_USER") {
            return registerUser(jsonRequest);
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
