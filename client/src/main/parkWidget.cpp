#include "parkWidget.hpp"

parkWidget::parkWidget(QWidget* parent) : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    status = new QLabel(this);
    idLabel = new QLabel(this);

    currPSlotID = -1;

    parkBtn = new QPushButton("Parking right now", this);

    idLabel->setText("Choose parking slot");
    status->setText("");

    layout->addWidget(idLabel);
    layout->addWidget(status);
    layout->addWidget(parkBtn);

    layout->setAlignment(idLabel, Qt::AlignHCenter | Qt::AlignTop);
    layout->setAlignment(status, Qt::AlignHCenter | Qt::AlignTop);
    layout->setAlignment(parkBtn, Qt::AlignHCenter | Qt::AlignTop);
}

parkWidget::~parkWidget() {}

void parkWidget::setCurrPSlotID(int ID, const QString& status) {
    currPSlotID = ID;
    idLabel->setText("Chosen parking slot: " + QString::number(ID));
    this->status->setText(status);

}
