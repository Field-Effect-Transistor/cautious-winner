#include "mainWindow.hpp"
#include <iostream>

mainWindow::mainWindow(Client& client, QWidget* parent) : QWidget(parent), client(client) {
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

    actionsGB->setLayout(actionsLayout);
    actionsLayout->addWidget(actionsWidget);
    actionsWidget->addWidget(park);
    actionsWidget->addWidget(book);
    connect(parkBtn, &QPushButton::clicked, this, [&](){
        actionsWidget->setCurrentIndex(0);
    });
    connect(parkBtn, &QPushButton::clicked, this, &mainWindow::updateMap);
    connect(bookBtn, &QPushButton::clicked, this, [&](){
        actionsWidget->setCurrentIndex(1);
    });
    connect(bookBtn, &QPushButton::clicked, this, &mainWindow::updateMap);

    leftLayout->addWidget(menuGB);
    leftLayout->addWidget(actionsGB);

    alignLayout->addLayout(leftLayout);
    alignLayout->addWidget(mapTableGB);
    alignLayout->setSizeConstraint(QLayout::SetFixedSize);

    alignWidget->setLayout(alignLayout);
    layout->addWidget(alignWidget);

    alignLayout->setAlignment(leftLayout, Qt::AlignTop);

    updateMap();

    for(int i = 0; i < mapWidget::pSlotCount; ++i) {

        connect(map->pSlots[i], &pSlot::clicked, this, [=](){  // Capture i by value
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

    connect(park->parkBtn, &QPushButton::clicked, this, &mainWindow::parkSlot);
    connect(park->endParkBtn, &QPushButton::clicked, this, &mainWindow::endParkSlot);

    //setLayout(layout);
    setWindowTitle("Parking System");
    setWindowIcon(QIcon(":resources/icon"));
}

mainWindow::~mainWindow() {} ;

void mainWindow::updateMap(void) {
    QString mapString = client.getMap();
    mapString = client.getMap();
    auto response = client.bigDataTransfering(QJsonDocument::fromJson(mapString.toUtf8()).object());

    if (response["status"].toString() == "success") {
        QJsonArray map = response["data"].toArray();
        for (int i = 0; i < mapWidget::pSlotCount; ++i) {
            for (const QJsonValue& value : map) {
                if (value["slot_id"].toInt() == i) {
                    if (value["status"].toString() == "FREE") {
                        this->map->pSlots[i]->setStatus(status::FREE);
                    } else if (value["status"].toString() == "BUSY") {
                        this->map->pSlots[i]->setStatus(status::BUSY);
                    } else if (value["status"].toString() == "BOOKED") {
                        this->map->pSlots[i]->setStatus(status::BOOKED);
                    }
                    break;
                }
            }
        }
    } else {
        errorDialog dialog("Something went wrong", this);
        dialog.exec();
    }
    
}

void mainWindow::parkSlot(void) {
    if (park->getCurrPSlotID() == -1) {
        errorDialog dialog("Please select a slot", this);
        dialog.exec();
        return;
    }
    QJsonObject response = client.parkingRequest(park->getCurrPSlotID());

    if (response["status"].toString() == "success") {
        updateMap();
    } else {
        errorDialog dialog(response["message"].toString(), this);
        dialog.exec();
    }
}

void mainWindow::bookSlot(void) {

}

void mainWindow::endParkSlot(void) {
    if (park->getCurrPSlotID() == -1) {
        errorDialog dialog("Please select a slot", this);
        dialog.exec();
        return;
    }
    QJsonObject response = client.endParkingRequest(park->getCurrPSlotID());

    if (response["status"].toString() == "success") {
        updateMap();
    } else {
        errorDialog dialog(response["message"].toString(), this);
        dialog.exec();
    }
}