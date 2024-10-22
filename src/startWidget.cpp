#include "startWidget.hpp"

startWidget::startWidget(QWidget *parent) : QWidget(parent) {

    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    alignLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    currWidget = new authWidget(this);

    //picture
    picLabel = new QLabel(this);
    picLabel->setPixmap(QPixmap("resources/pictures/loginPic.png"));
    picLabel->setScaledContents(true);
    picLabel->setFixedSize(200, 200);
    //picLabel->setAlignment(Qt::AlignHCenter);

    //message
    mesg = new QLabel(this);
    mesg->setText("Welcome to our Parking!");
    {
        QFont font = mesg->font();
        font.setBold(true);
        font.setPointSize(10);
        mesg->setFont(font);
    }
    
    //layouts
    layout->addLayout(alignLayout);
        alignLayout->addWidget(picLabel);
        alignLayout->addWidget(mesg);
        alignLayout->addWidget(currWidget);
        alignLayout->setAlignment(picLabel, Qt::AlignCenter);
        alignLayout->setAlignment(mesg, Qt::AlignCenter);
        alignLayout->setAlignment(currWidget, Qt::AlignCenter);
        alignLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layout);
    setWindowTitle("Parking System");
    setWindowIcon(QIcon("resources/pictures/loginPic.ico"));

}

startWidget::~startWidget() {}