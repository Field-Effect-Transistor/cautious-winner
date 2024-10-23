#include "regWidget.hpp"

regWidget::regWidget(QWidget *parent) : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom);
    passwdLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    inputBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    buttonBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    //boxes
    inputGB = new QGroupBox(this);
    buttonGB = new QGroupBox(this);

    //buttons
    regBtn = new QPushButton("Register", this);
    retBtn = new QPushButton("Return", this);

    //inputs
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

    //layout
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
    //layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);  
    setWindowTitle("Register");
}

regWidget::~regWidget() {}