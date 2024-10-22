#include "startWidget.hpp"

startWidget::startWidget(QWidget* currWidget_, QWidget *parent) : QWidget(parent) {

    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    alignLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    {
        if(currWidget_)
            currWidget = currWidget_; 
        else
            currWidget = new authWidget(this);
    }

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
    
    //layouts
    layout->addLayout(alignLayout);
        alignLayout->addWidget(picLabel);
        alignLayout->addWidget(mesg);
        alignLayout->addWidget(currWidget);
        alignLayout->setAlignment(picLabel, Qt::AlignHCenter);
        alignLayout->setAlignment(mesg, Qt::AlignHCenter);
        alignLayout->setAlignment(currWidget, Qt::AlignHCenter);
        alignLayout->setAlignment(Qt::AlignVCenter);
        alignLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layout);
    setWindowTitle("Parking System");
    setWindowIcon(QIcon("resources/pictures/loginPic.ico"));

}

startWidget::~startWidget() {}