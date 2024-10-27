#include "regWidget.hpp"

regWidget::regWidget(QWidget *parent) : QWidget(parent) {
    try {
        layout = new QBoxLayout(QBoxLayout::TopToBottom);
        passwdLayout = new QBoxLayout(QBoxLayout::LeftToRight);
        inputBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
        buttonBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

        // Boxes
        inputGB = new QGroupBox(this);
        buttonGB = new QGroupBox(this);

        // Buttons
        regBtn = new QPushButton("Register", this);
        retBtn = new QPushButton("Return", this);

        // Inputs
        emailIn = new QLineEdit(this);
        emailIn->setAlignment(Qt::AlignLeft);
        emailIn->setPlaceholderText("email");

        passwdIn = new QLineEdit(this);
        passwdIn->setAlignment(Qt::AlignLeft);
        passwdIn->setEchoMode(QLineEdit::Password);
        passwdIn->setPlaceholderText("password");

        rPasswdIn = new QLineEdit(this);
        rPasswdIn->setAlignment(Qt::AlignLeft);
        rPasswdIn->setEchoMode(QLineEdit::Password);
        rPasswdIn->setPlaceholderText("repeat password");

        licenseIn = new QLineEdit(this);
        licenseIn->setAlignment(Qt::AlignLeft);
        licenseIn->setPlaceholderText("license plate");

        // Layout
        inputBoxLayout->addWidget(emailIn);
        passwdLayout->addWidget(passwdIn);
        passwdLayout->addWidget(rPasswdIn);
        inputBoxLayout->addLayout(passwdLayout);
        inputBoxLayout->addWidget(licenseIn);
        inputGB->setLayout(inputBoxLayout);
        inputGB->setMinimumWidth(300);

        buttonBoxLayout->addWidget(regBtn);
        buttonBoxLayout->addWidget(retBtn);
        buttonGB->setLayout(buttonBoxLayout);
        buttonGB->setMinimumWidth(300);

        layout->addWidget(inputGB);
        layout->addWidget(buttonGB);
        layout->setAlignment(inputGB, Qt::AlignHCenter | Qt::AlignTop);
        layout->setAlignment(buttonGB, Qt::AlignHCenter | Qt::AlignTop);
        
        setLayout(layout);  
        setWindowTitle("Register");
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

regWidget::~regWidget() {}
