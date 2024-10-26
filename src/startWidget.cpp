#include "startWidget.hpp"
#include <QTimer>

startWidget::startWidget(QWidget *parent) : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    alignLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    
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
    connect(reg->passwdIn, &QLineEdit::textChanged, this, &startWidget::passwdValidation);
    connect(reg->rPasswdIn, &QLineEdit::textChanged, this, &startWidget::rPasswdValidation);

    //picture
    try {
        picLabel = new QLabel(this);
        QPixmap pixmap("resources/pictures/loginPic282x260.png");
        if (pixmap.isNull()) {
            throw std::runtime_error("Image could not be loaded");
        }
        picLabel->setPixmap(pixmap);
        picLabel->setScaledContents(true);
        picLabel->setFixedSize(200, 185);
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", e.what());
    }

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

    //setLayout(layout);
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

        errorDialog dialog("Wrong email or password", this);
        dialog.exec();

    } else {
        hide();
    }
}

void startWidget::guestSlot() {
    if (false and validation::isEmailInvalid(guest->emailIn->text())) {
        
        errorDialog dialog("Wrong email or password", this);
        dialog.exec();

    } else {
        mapWidget* map = new mapWidget();
        map->show();

        QTimer::singleShot(5000, [=]() {
            map->pSlots[0]->setStatus(status::BOOKED);
                QTimer::singleShot(5000, [=]() {
                    map->pSlots[0]->setStatus(status::BUSY);
            });
        });

    }
}

void startWidget::regSlot() {
    if (validation::isEmailInvalid(reg->emailIn->text())) {
        errorDialog dialog("Wrong email", this);
        dialog.exec();
    } else if(validation::isPasswdInvalid(reg->passwdIn->text()) ||
              validation::isPasswdInvalid(reg->rPasswdIn->text())) {
        errorDialog dialog("Wrong password", this);
        dialog.exec();
    } else if (reg->rPasswdIn->text() != reg->passwdIn->text()) {
        errorDialog dialog("Passwords don't match", this);
        dialog.exec();
    } else if (reg->licenseIn->text().length() < 6) {
        errorDialog dialog("Wrong license", this);
        dialog.exec();
    } else {
        hide();
    }
}

void startWidget::passwdValidation() {
    int error = validation::isPasswdInvalid(reg->passwdIn->text());
    if(error) {
        QString msg;
        switch(error) {
            case validation::invalidPasswd::TOO_SHORT:
                msg = validation::invalidPasswd::detail::TOO_SHORT_MSG;
                break;
            case validation::invalidPasswd::NO_LOWER:
                msg = validation::invalidPasswd::detail::NO_LOWER_MSG;
                break;
            case validation::invalidPasswd::NO_UPPER:
                msg = validation::invalidPasswd::detail::NO_UPPER_MSG;
                break;
            case validation::invalidPasswd::NO_DIGIT:
                msg = validation::invalidPasswd::detail::NO_DIGIT_MSG;
                break;
            case validation::invalidPasswd::NO_SPECIAL:
                msg = validation::invalidPasswd::detail::NO_SPECIAL_MSG;
                break;
            default:
                break;
        }
        QToolTip::showText(reg->passwdIn->mapToGlobal(QPoint(0, reg->passwdIn->height())), msg, reg->passwdIn);

    } else {
        QToolTip::hideText();
    }
}   

void startWidget::rPasswdValidation() {
    if(reg->rPasswdIn->text() != reg->passwdIn->text()) {
        QToolTip::showText(reg->rPasswdIn->mapToGlobal(QPoint(0, reg->rPasswdIn->height())), "Passwords don't match", reg->rPasswdIn);
    } else {
        QToolTip::hideText();
    }
}