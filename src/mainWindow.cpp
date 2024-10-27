#include "mainWindow.hpp"

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
    parkHistoryBtn->setMinimumWidth(100);
    menuLayout->addWidget(bookBtn);
    menuLayout->addWidget(exitBtn);
    menuLayout->setSizeConstraint(QLayout::SetFixedSize);

    actionsGB->setLayout(actionsLayout);
    actionsLayout->addWidget(actionsWidget);

    leftLayout->addWidget(menuGB);
    leftLayout->addWidget(actionsGB);

    alignLayout->addLayout(leftLayout);
    alignLayout->addWidget(mapTableGB);
    alignLayout->setSizeConstraint(QLayout::SetFixedSize);

    alignWidget->setLayout(alignLayout);
    layout->addWidget(alignWidget);

    alignLayout->setAlignment(leftLayout, Qt::AlignTop);
    
    setLayout(layout);
    setWindowTitle("Parking System");
    setWindowIcon(QIcon("resources/pictures/loginPic.ico"));
}

mainWindow::~mainWindow() {} ;