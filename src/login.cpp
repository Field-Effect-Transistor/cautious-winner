#include "login.hpp"

Login::Login(QWidget *parent) : QWidget(parent) {
        //boxes
        windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
        inputLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
        unameInputLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
        passwdInputLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
        buttonLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
        RGbuttonLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);

        //for input alignment
        unameInLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
        unameInLayout->setAlignment(Qt::AlignHCenter);
        passwdInLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
        passwdInLayout->setAlignment(Qt::AlignHCenter);

        //labels
        picLabel = new QLabel(this);

        //picture
        picLabel->setPixmap(QPixmap("resources/pictures/loginPic.png"));
        picLabel->setScaledContents(true);
        picLabel->setFixedSize(200, 200);

        //inputs
        unameIn = new QLineEdit(this);
        unameIn->setAlignment(Qt::AlignLeft);
        unameIn->setPlaceholderText("login");
        passwdIn = new QLineEdit(this);
        passwdIn->setAlignment(Qt::AlignLeft);
        passwdIn->setEchoMode(QLineEdit::Password);
        passwdIn->setPlaceholderText("password");

        //buttons
        loginBtn = new QPushButton("Log in", this);
        regBtn = new QPushButton("Register", this);
        guestBtn = new QPushButton("Guest", this);
        
        //groups
        inputGB = new QGroupBox(this);
        inputGB->setAlignment(Qt::AlignHCenter);
        inputGB->setTitle("Welcome to our parking!!!");
        {
            QFont font = inputGB->font();
            font.setBold(true);
            font.setPointSize(10);
            inputGB->setFont(font);
        }
        buttonGB = new QGroupBox(this);
        buttonGB->setMinimumWidth(300);
        
        inputGB->setLayout(inputLayout);
        buttonGB->setLayout(buttonLayout);

        //layouts
        windowLayout->addWidget(picLabel);
            inputLayout->addLayout(unameInputLayout);
                unameInputLayout->addLayout(unameInLayout);
                    unameInLayout->addWidget(unameIn);
            inputLayout->addLayout(passwdInputLayout);
                passwdInputLayout->addLayout(passwdInLayout);
                    passwdInLayout->addWidget(passwdIn);
        windowLayout->addWidget(inputGB);
        windowLayout->addStretch(2);
            buttonLayout->addWidget(loginBtn);
            buttonLayout->addLayout(RGbuttonLayout);
                RGbuttonLayout->addWidget(regBtn);
                RGbuttonLayout->addWidget(guestBtn);
            buttonGB->setLayout(buttonLayout);
        windowLayout->addWidget(buttonGB);

        windowLayout->setAlignment(picLabel, Qt::AlignHCenter);
        windowLayout->setSizeConstraint(QLayout::SetFixedSize);

        //Window
        setWindowIcon(QIcon("resources/pictures/loginPic.ico"));
        setWindowTitle("Log in");
        setLayout(windowLayout);

    }

Login::~Login() {}