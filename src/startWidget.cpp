#include "startWidget.hpp"

startWidget::startWidget(QWidget *parent)
    : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    alignLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    
    auth = new authWidget(this);
    login = new loginWidget(this);
    guest = new guestWidget(this);

    //picture
    picLabel = new QLabel(this);
    picLabel->setPixmap(QPixmap("resources/pictures/loginPic.png"));
    picLabel->setScaledContents(true);
    picLabel->setFixedSize(200, 200);

    //message
    mesg = new QLabel(this);
    mesg->setText("Welcome to our Parking!");
    {
        QFont font = mesg->font();
        font.setBold(true);
        font.setPointSize(10);
        mesg->setFont(font);
    }

    // Створюємо QStackedWidget
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(auth);  // Додаємо authWidget
    stackedWidget->addWidget(login); // Додаємо loginWidget
    stackedWidget->addWidget(guest); // Додаємо loginWidget

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
