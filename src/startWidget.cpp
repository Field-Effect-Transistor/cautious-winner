#include "startWidget.hpp"

startWidget::startWidget(QWidget *parent)
    : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    alignLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    
    auth = new authWidget(this);
    login = new loginWidget(this);

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
    setWindowTitle("Parking System");
    setWindowIcon(QIcon("resources/pictures/loginPic.ico"));
}

startWidget::~startWidget() {}

void startWidget::switchToLogin() {
    stackedWidget->setCurrentIndex(1);  // Перемикаємося на loginWidget
}
