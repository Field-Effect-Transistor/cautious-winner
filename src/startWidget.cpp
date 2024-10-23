#include <iostream>
#include <QDialog>

#include "startWidget.hpp"

startWidget::startWidget(QWidget *parent)
    : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    alignLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    
    //widgets and buttons binding
    auth = new authWidget(this);
    connect(auth->loginBtn, &QPushButton::clicked, this, &startWidget::switchToLogin);
    connect(auth->regBtn, &QPushButton::clicked, this, &startWidget::switchToReg);
    connect(auth->guestBtn, &QPushButton::clicked, this, &startWidget::switchToGuest);
    connect(auth->exitBtn, &QPushButton::clicked, this, &startWidget::exitApp);
    login = new loginWidget(this);
    connect(login->retBtn, &QPushButton::clicked, this, &startWidget::switchToAuth);
    connect(login->loginBtn, &QPushButton::clicked, this, &startWidget::loginSlot);
    guest = new guestWidget(this);
    connect(guest->retBtn, &QPushButton::clicked, this, &startWidget::switchToAuth);
    connect(guest->guestLoginBtn, &QPushButton::clicked, this, &startWidget::guestSlot);
    reg = new regWidget(this);
    connect(reg->retBtn, &QPushButton::clicked, this, &startWidget::switchToAuth);
    connect(reg->regBtn, &QPushButton::clicked, this, &startWidget::regSlot);

    //picture
    picLabel = new QLabel(this);
    picLabel->setPixmap(QPixmap("resources/pictures/loginPic282x260.png"));
    picLabel->setScaledContents(true);
    picLabel->setFixedSize(200, 185);

    //message
    mesg = new QLabel(this);
    mesg->setText("Welcome to our Parking!!!");
    {
        QFont font = mesg->font();
        font.setBold(true);
        font.setPointSize(12);
        mesg->setFont(font);
    }

    // Створюємо QStackedWidget
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(auth); 
    stackedWidget->addWidget(login);
    stackedWidget->addWidget(guest); 
    stackedWidget->addWidget(reg); 

    //layouts
    layout->addLayout(alignLayout);
        alignLayout->addWidget(picLabel);
        alignLayout->addWidget(mesg);
        alignLayout->addWidget(stackedWidget);
        alignLayout->setAlignment(picLabel, Qt::AlignCenter);
        alignLayout->setAlignment(mesg, Qt::AlignCenter);
        alignLayout->setAlignment(stackedWidget, Qt::AlignCenter);
        alignLayout->setAlignment(Qt::AlignCenter);
        alignLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layout);
    title = "Parking System";
    setWindowTitle(title);
    setWindowIcon(QIcon("resources/pictures/loginPic.ico"));
}

startWidget::~startWidget() {}

void startWidget::switchTo(int ID) {
    stackedWidget->setCurrentIndex(ID);
    if (stackedWidget->currentWidget()->windowTitle().length() == 0) {
        setWindowTitle(title);
    } else {
        setWindowTitle(title + " - " + stackedWidget->currentWidget()->windowTitle());
    }
}

void startWidget::switchToAuth() {
    switchTo(ID::AUTH);
}

void startWidget::switchToLogin() {
    switchTo(ID::LOGIN);
}   

void startWidget::switchToGuest() {
    switchTo(ID::GUEST);
}

void startWidget::switchToReg() {
    switchTo(ID::REGISTER);
}

void startWidget::exitApp() {
    hide();
    close();
}

void startWidget::loginSlot() {
    if (validation::isEmailInvalid(login->emailIn->text()) ||
        validation::isPasswdInvalid(login->passwdIn->text())) {

        QDialog dialog(this);
        dialog.setWindowTitle("Error");
        QVBoxLayout layout(&dialog);

        QLabel label("Wrong email or password", &dialog);
        layout.addWidget(&label);

        QPushButton *okButton = new QPushButton("OK");
        layout.addWidget(okButton);
        
        connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        dialog.setFixedSize(200, 100); // Set fixed size for the dialog
        dialog.exec(); // Show the dialog
    } else {
        hide();
    }
}

void startWidget::guestSlot() {
    if (validation::isEmailInvalid(guest->emailIn->text())) {
        QDialog dialog(this);
        dialog.setWindowTitle("Error");
        QVBoxLayout layout(&dialog);

        QLabel label("Wrong email", &dialog);
        layout.addWidget(&label);

        QPushButton *okButton = new QPushButton("OK");
        layout.addWidget(okButton);
        
        connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        dialog.setFixedSize(200, 100); // Set fixed size for the dialog
        dialog.exec(); // Show the dialog
    } else {
        hide();
    }
}

void startWidget::regSlot() {
    if (validation::isEmailInvalid(reg->emailIn->text())) {
        QDialog dialog(this);
        dialog.setWindowTitle("Error");
        QVBoxLayout layout(&dialog);

        QLabel label("Wrong email", &dialog);
        layout.addWidget(&label);

        QPushButton *okButton = new QPushButton("OK");
        layout.addWidget(okButton);
        
        connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        dialog.setFixedSize(200, 100); // Set fixed size for the dialog
        dialog.exec(); // Show the dialog
    } else if(validation::isPasswdInvalid(reg->passwdIn->text()) ||
              validation::isPasswdInvalid(reg->rPasswdIn->text())) {

        QDialog dialog(this);
        dialog.setWindowTitle("Error");
        QVBoxLayout layout(&dialog);

        QLabel label("Wrong password", &dialog);
        layout.addWidget(&label);

        QPushButton *okButton = new QPushButton("OK");
        layout.addWidget(okButton);
        
        connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        dialog.setFixedSize(200, 100); // Set fixed size for the dialog
        dialog.exec(); // Show the dialog
    } else if (reg->rPasswdIn->text() != reg->passwdIn->text()) {
        QDialog dialog(this);
        dialog.setWindowTitle("Error");
        QVBoxLayout layout(&dialog);

        QLabel label("Passwords don't match", &dialog);
        layout.addWidget(&label);

        QPushButton *okButton = new QPushButton("OK");
        layout.addWidget(okButton);
        
        connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        dialog.setFixedSize(200, 100); // Set fixed size for the dialog
        dialog.exec(); // Show the dialog
    } else if (reg->licenseIn->text().length() < 6) {
        QDialog dialog(this);
        dialog.setWindowTitle("Error");
        QVBoxLayout layout(&dialog);

        QLabel label("Wrong license", &dialog);
        layout.addWidget(&label);

        QPushButton *okButton = new QPushButton("OK");
        layout.addWidget(okButton);
        
        connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        dialog.setFixedSize(200, 100); // Set fixed size for the dialog
        dialog.exec(); // Show the dialog
    } else {
        hide();
    }
}