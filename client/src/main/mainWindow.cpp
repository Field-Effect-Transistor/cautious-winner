#include "mainWindow.hpp"
#include <iostream>

mainWindow::mainWindow(QWidget* parent) : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    alignLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    leftLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    menuLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    actionsLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    mapTableLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    alignWidget = new QWidget(this);

    menuGB = new QGroupBox("Menu", this);
    mapTableGB = new QGroupBox("Map", this);
    actionsGB = new QGroupBox("Actions", this);

    mapTableWidget = new QStackedWidget(this);
    actionsWidget = new QStackedWidget(this);

    map = new mapWidget(this);
    park = new parkWidget(this);
    book = new bookWidget(this);

    parkBtn = new QPushButton("Park", this);
    parkHistoryBtn = new QPushButton("Park History", this);
    bookBtn = new QPushButton("Book", this);
    exitBtn = new QPushButton("Exit", this);
    connect(exitBtn, &QPushButton::clicked, this, &mainWindow::close);

    mapTableGB->setLayout(mapTableLayout);
    mapTableLayout->addWidget(mapTableWidget);
    mapTableWidget->addWidget(map);
    mapTableLayout->setSizeConstraint(QLayout::SetFixedSize);

    menuGB->setLayout(menuLayout);
    menuLayout->addWidget(parkBtn);
    menuLayout->addWidget(parkHistoryBtn);
    parkHistoryBtn->setMinimumWidth(190);
    menuLayout->addWidget(bookBtn);
    menuLayout->addWidget(exitBtn);
    //menuLayout->setSizeConstraint(QLayout::SetFixedSize);

    actionsGB->setLayout(actionsLayout);
    actionsLayout->addWidget(actionsWidget);
    actionsWidget->addWidget(park);
    actionsWidget->addWidget(book);
    connect(parkBtn, &QPushButton::clicked, this, [&](){
        actionsWidget->setCurrentIndex(0);
    });
    connect(bookBtn, &QPushButton::clicked, this, [&](){
        actionsWidget->setCurrentIndex(1);
    });

    leftLayout->addWidget(menuGB);
    leftLayout->addWidget(actionsGB);

    alignLayout->addLayout(leftLayout);
    alignLayout->addWidget(mapTableGB);
    alignLayout->setSizeConstraint(QLayout::SetFixedSize);

    alignWidget->setLayout(alignLayout);
    layout->addWidget(alignWidget);

    alignLayout->setAlignment(leftLayout, Qt::AlignTop);

    for(int i = 0; i < mapWidget::pSlotCount; ++i) {
    connect(map->pSlots[i], &pSlot::clicked, this, [=](){  // Capture i by value
        //std::cout << i << std::endl;

        QString temp;
        switch (map->pSlots[i]->getStatus()) {
            case status::FREE:
                temp = "Free";
                break;
            case status::BUSY:
                temp = "Busy";
                break;
            case status::BOOKED:
                temp = "Booked";
                break;
            default:
                break;
        }

        park->setCurrPSlotID(map->pSlots[i]->getID(), temp);
    });

    connect(map->pSlots[i], &pSlot::clicked, this, [=](){  // Capture i by value
        //std::cout << i << std::endl;

        QString temp;
        switch (map->pSlots[i]->getStatus()) {
            case status::FREE:
                temp = "Free";
                break;
            case status::BUSY:
                temp = "Busy";
                break;
            case status::BOOKED:
                temp = "Booked";
                break;
            default:
                break;
        }

        book->setCurrPSlotID(map->pSlots[i]->getID(), temp);
    });

    }

    //setLayout(layout);
    setWindowTitle("Parking System");
    setWindowIcon(QIcon("client/resources/pictures/loginPic.ico"));
}

mainWindow::~mainWindow() {} ;