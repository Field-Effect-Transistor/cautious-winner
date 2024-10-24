#include "authWidget.hpp"

authWidget::authWidget(QWidget *parent) : QWidget(parent) {
    try {
        layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
        authBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
        
        authGB = new QGroupBox(this);

        loginBtn = new QPushButton("Login", this);
        regBtn = new QPushButton("Register", this);
        guestBtn = new QPushButton("Guest", this);
        exitBtn = new QPushButton("Exit", this);

        layout->addSpacing(20);
        authBoxLayout->addWidget(loginBtn);
        authBoxLayout->addWidget(regBtn);
        authBoxLayout->addWidget(guestBtn);
        authBoxLayout->addWidget(exitBtn);
        
        authGB->setLayout(authBoxLayout);
        authGB->setMinimumWidth(300);
        
        layout->addWidget(authGB);
        layout->setAlignment(authGB, Qt::AlignHCenter | Qt::AlignTop);
        layout->setSizeConstraint(QLayout::SetFixedSize);
        
        setLayout(layout);
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

authWidget::~authWidget() {}
