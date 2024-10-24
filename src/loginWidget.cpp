#include "loginWidget.hpp"

loginWidget::loginWidget(QWidget *parent) : QWidget(parent) {
    try {
        layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
        inputBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
        buttonBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

        inputGB = new QGroupBox(this);
        buttonGB = new QGroupBox(this);

        loginBtn = new QPushButton("Login", this);
        retBtn = new QPushButton("Return", this);

        // inputs
        emailIn = new QLineEdit(this);
        emailIn->setAlignment(Qt::AlignLeft);
        emailIn->setPlaceholderText("email");

        passwdIn = new QLineEdit(this);
        passwdIn->setAlignment(Qt::AlignLeft);
        passwdIn->setEchoMode(QLineEdit::Password);
        passwdIn->setPlaceholderText("password");

        // Arrange input fields
        inputBoxLayout->addWidget(emailIn);
        inputBoxLayout->addWidget(passwdIn);
        inputGB->setLayout(inputBoxLayout);
        inputGB->setMinimumWidth(300);

        // Arrange buttons
        buttonBoxLayout->addWidget(loginBtn);
        buttonBoxLayout->addWidget(retBtn);
        buttonGB->setLayout(buttonBoxLayout);
        buttonGB->setMinimumWidth(300);

        // Set layout and alignment
        layout->addWidget(inputGB);
        layout->addWidget(buttonGB);
        layout->setAlignment(inputGB, Qt::AlignHCenter | Qt::AlignTop);
        layout->setAlignment(buttonGB, Qt::AlignHCenter | Qt::AlignTop);
        setLayout(layout);
        setWindowTitle("Login");
    } catch (const std::bad_alloc& e) {
        qCritical() << "Memory allocation failed:" << e.what();
        QMessageBox::critical(this, "Error", "Failed to initialize UI due to memory allocation error.");
    } catch (const std::exception& e) {
        qCritical() << "Exception occurred:" << e.what();
        QMessageBox::critical(this, "Error", "An error occurred during widget initialization.");
    } catch (...) {
        qCritical() << "An unknown error occurred during widget initialization.";
        QMessageBox::critical(this, "Error", "An unknown error occurred.");
    }
}

loginWidget::~loginWidget() {}
