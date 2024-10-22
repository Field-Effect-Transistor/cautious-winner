#include "mainWidget.hpp"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    
    currWidget = new Login(this);

    currLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    
    currLayout->addWidget(currWidget);
    currLayout->setAlignment(Qt::AlignCenter);

    setWindowTitle("Parking System");
    setLayout(currLayout);
    resize(325, 425);
}

MainWidget::~MainWidget() {}