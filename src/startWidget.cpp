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
    guest = new guestWidget(this);
    connect(guest->retBtn, &QPushButton::clicked, this, &startWidget::switchToAuth);
    reg = new regWidget(this);
    connect(reg->retBtn, &QPushButton::clicked, this, &startWidget::switchToAuth);

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