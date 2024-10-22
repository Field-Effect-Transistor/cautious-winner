#include "authWidget.hpp"

authWidget::authWidget(QWidget *parent) : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom);
    authBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    
    authGB = new QGroupBox(this);

    loginBtn = new QPushButton("Login", this);
    regBtn = new QPushButton("Register", this);
    guestBtn = new QPushButton("Guest", this);

    layout->addSpacing(35);
        authBoxLayout->addWidget(loginBtn);
        authBoxLayout->addWidget(regBtn);
        authBoxLayout->addWidget(guestBtn);
    authGB->setLayout(authBoxLayout);
    authGB->setMinimumWidth(300);
    layout->addWidget(authGB);
    layout->addSpacing(23);
    layout->setAlignment(authGB, Qt::AlignHCenter | Qt::AlignTop);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    
    setLayout(layout);
}

authWidget::~authWidget() {}