#include "loginWidget.hpp"

loginWidget::loginWidget(QWidget *parent) : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom);
    inputBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    buttonBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    inputGB = new QGroupBox(this);
    buttonGB = new QGroupBox(this);

    loginBtn = new QPushButton("Login", this);
    retBtn = new QPushButton("Return", this);

    //inputs
    unameIn = new QLineEdit(this);
    unameIn->setAlignment(Qt::AlignLeft);
    unameIn->setPlaceholderText("login");
    passwdIn = new QLineEdit(this);
    passwdIn->setAlignment(Qt::AlignLeft);
    passwdIn->setEchoMode(QLineEdit::Password);
    passwdIn->setPlaceholderText("password");

        inputBoxLayout->addWidget(unameIn);
        inputBoxLayout->addWidget(passwdIn);
    inputGB->setLayout(inputBoxLayout);
    inputGB->setMinimumWidth(300);
        buttonBoxLayout->addWidget(loginBtn);
        buttonBoxLayout->addWidget(retBtn);
    buttonGB->setLayout(buttonBoxLayout);
    buttonGB->setMinimumWidth(300);
    layout->addWidget(inputGB);
    layout->addWidget(buttonGB);
    layout->setAlignment(inputGB, Qt::AlignHCenter | Qt::AlignTop);
    layout->setAlignment(buttonGB, Qt::AlignHCenter | Qt::AlignTop);
    setLayout(layout);
}

loginWidget::~loginWidget() {}