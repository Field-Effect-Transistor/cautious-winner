#include "bookWidget.hpp"

bookWidget::bookWidget(QWidget* parent) : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    currPSlotID = -1;

    idLabel = new QLabel("Choose parking slot", this);
    statusLabel = new QLabel(this);

    startDateLabel = new QLabel("Start Date:", this);
    endDateLabel = new QLabel("End Date:", this);

    startDateEdit = new QDateEdit(QDate::currentDate(), this);
    startDateEdit->setCalendarPopup(true);

    endDateEdit = new QDateEdit(QDate::currentDate(), this);
    endDateEdit->setCalendarPopup(true);

    bookBtn = new QPushButton("Book Slot", this);

    layout->addWidget(idLabel);
    layout->addWidget(statusLabel);
    layout->addWidget(startDateLabel);
    layout->addWidget(startDateEdit);
    layout->addWidget(endDateLabel);
    layout->addWidget(endDateEdit);
    layout->addWidget(bookBtn);

    layout->setAlignment(idLabel, Qt::AlignHCenter | Qt::AlignTop);
    layout->setAlignment(statusLabel, Qt::AlignHCenter | Qt::AlignTop);
    layout->setAlignment(bookBtn, Qt::AlignHCenter | Qt::AlignTop);
}

bookWidget::~bookWidget() {}

void bookWidget::setCurrPSlotID(int ID, const QString& status) {
    currPSlotID = ID;
    idLabel->setText("Chosen parking slot: " + QString::number(ID));
    statusLabel->setText(status);
}
