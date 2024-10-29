#include "startWidget.hpp"

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

    settingsBtn = new QPushButton(this);
    //settingsBtn->setText("Settings");
    settingsBtn->setFixedSize(22, 22);
    settingsBtn->setIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    connect(settingsBtn, &QPushButton::clicked, this, &startWidget::settingsSlot);

    //picture
    try {
        picLabel = new QLabel(this);
        pixmap = QPixmap("client/resources/pictures/loginPic282x260.png");
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
        alignLayout->addWidget(settingsBtn);
        alignLayout->addWidget(picLabel);
        alignLayout->addWidget(mesg);
        alignLayout->addWidget(stackedWidget);

        alignLayout->setAlignment(settingsBtn, Qt::AlignRight);
        alignLayout->setAlignment(picLabel, Qt::AlignCenter);
        alignLayout->setAlignment(mesg, Qt::AlignCenter);
        alignLayout->setAlignment(stackedWidget, Qt::AlignCenter);
        alignLayout->setAlignment(Qt::AlignCenter);
        alignLayout->setSizeConstraint(QLayout::SetFixedSize);

    //setLayout(layout);
    title = "Parking System";
    setWindowTitle(title);
    setWindowIcon(QIcon("client/resources/pictures/loginPic.ico"));
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
        mainWindow* mainW = new mainWindow();
        mainW->show();
    }
}

void startWidget::guestSlot() {
    if (false and validation::isEmailInvalid(guest->emailIn->text())) {
        
        errorDialog dialog("Wrong email or password", this);
        dialog.exec();

    } else {
        hide();
        mainWindow* mainW = new mainWindow();
        mainW->show();
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
        switchToLogin();
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

#include <QApplication>
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>

void startWidget::settingsSlot() {
    // Створюємо діалогове вікно для налаштувань
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Settings");

    // Створюємо віджети для діалогу
    QLabel* themeLabel = new QLabel("Choose theme", dialog);
    QComboBox* themeSelector = new QComboBox(dialog);

    // Додаємо варіанти тем
    themeSelector->addItem("System");
    themeSelector->addItem("Light");
    themeSelector->addItem("Dark");
    themeSelector->addItem("Hackers");

    // Створюємо макет для діалогу
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(themeLabel);
    layout->addWidget(themeSelector);
    dialog->setLayout(layout);
    dialog->resize(200, 100);

    // Обробник зміни вибраної теми
    connect(themeSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [themeSelector]() {
        // Вибір теми на основі індексу
        switch (themeSelector->currentIndex()) {
            case 0: // Системна тема
                qApp->setStyleSheet("");
                break;
            case 1: // Світла тема
                qApp->setStyleSheet(
                    "QWidget { background-color: #F0F0F0; color: #000000; }"
                    "QPushButton { background-color: #E0E0E0; border: 1px solid #A0A0A0; padding: 5px; }"
                    "QPushButton:hover { background-color: #D0D0D0; }"
                    "QLineEdit, QTextEdit, QComboBox, QListWidget { background-color: #FFFFFF; color: #000000; border: 1px solid #A0A0A0; }"
                    "QLabel { color: #202020; }"
                    "QMenu { background-color: #F0F0F0; color: #000000; border: 1px solid #A0A0A0; }"
                    "QMenu::item:selected { background-color: #D0D0D0; }"
                );
                break;
            case 2: // Темна тема
                qApp->setStyleSheet(
                    "QWidget { background-color: #333333; color: #EEEEEE; }"
                    "QPushButton { background-color: #555555; border: 1px solid #777777; padding: 5px; }"
                    "QPushButton:hover { background-color: #666666; }"
                    "QLineEdit, QTextEdit, QComboBox, QListWidget { background-color: #444444; color: #EEEEEE; border: 1px solid #666666; }"
                    "QLabel { color: #FFFFFF; }"
                    "QMenu { background-color: #333333; color: #EEEEEE; border: 1px solid #555555; }"
                    "QMenu::item:selected { background-color: #666666; }"
                );
                break;
            case 3: // Хакерська тема
                qApp->setStyleSheet(
                    "QWidget { background-color: black; color: #00FF00; font-family: monospace; }"
                    "QPushButton { background-color: #001100; color: #00FF00; border: 1px solid #00AA00; padding: 5px; }"
                    "QPushButton:hover { background-color: #002200; }"
                    "QLineEdit, QTextEdit, QComboBox, QListWidget { background-color: #001100; color: #00FF00; border: 1px solid #00AA00; }"
                    "QLabel { color: #00FF00; }"
                    "QMenu { background-color: #001100; color: #00FF00; border: 1px solid #00AA00; }"
                    "QMenu::item:selected { background-color: #002200; }"
                );
                break;
        }
    });

    // Відображення діалогу
    dialog->exec();
}