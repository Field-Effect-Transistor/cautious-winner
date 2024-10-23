#include "guestWidget.hpp"

guestWidget::guestWidget(QWidget *parent) : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom);
    inputBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    buttonBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    inputGB = new QGroupBox(this);
    buttonGB = new QGroupBox(this);

    guestLoginBtn = new QPushButton("Guest login", this);
    retBtn = new QPushButton("Return", this);

    //inputs
    emailIn = new QLineEdit(this);
    emailIn->setAlignment(Qt::AlignLeft);
    emailIn->setPlaceholderText("email");
    licenseIn = new QLineEdit(this);
    licenseIn->setAlignment(Qt::AlignLeft);
    licenseIn->setPlaceholderText("license plate");

        inputBoxLayout->addWidget(emailIn);
        inputBoxLayout->addWidget(licenseIn);
    inputGB->setLayout(inputBoxLayout);
    inputGB->setMinimumWidth(300);
        buttonBoxLayout->addWidget(guestLoginBtn);
        buttonBoxLayout->addWidget(retBtn);
    buttonGB->setLayout(buttonBoxLayout);
    buttonGB->setMinimumWidth(300);
    layout->addWidget(inputGB);
    layout->addWidget(buttonGB);
    layout->setAlignment(inputGB, Qt::AlignHCenter | Qt::AlignTop);
    layout->setAlignment(buttonGB, Qt::AlignHCenter | Qt::AlignTop);
    setLayout(layout);
    setWindowTitle("Guest login");
}

guestWidget::~guestWidget() {}