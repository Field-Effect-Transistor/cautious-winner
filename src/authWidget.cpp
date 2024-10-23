#include "authWidget.hpp"

authWidget::authWidget(QWidget *parent) : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom);
    authBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    
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
}

authWidget::~authWidget() {}