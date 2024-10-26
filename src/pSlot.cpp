#include "pSlot.hpp"

pSlot::pSlot(int x, int y, int ID, QWidget* parent, int align): QPushButton(QString::number(ID), parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    setPosition(x, y);
    align == alignment::H ? setFixedSize(50, 30) : setFixedSize(30, 50);
    setStatus(status::FREE);
};

pSlot::~pSlot() {}

void pSlot::setID(int ID) {
    this->ID = ID;
    this->setText(QString::number(ID));
}

int pSlot::getID(void) const {
    return ID;
}   

void pSlot::setPosition(int x, int y) {
    aleft = x;
    atop = y;
    move(x, y);
}

void pSlot::getPosition(int &x, int &y) const {
    x = aleft;
    y = atop;
}

void pSlot::setStatus(int status) {
    Status = status;
    switch (status) {
        case status::FREE:
            setStyleSheet("background-color: rgb(0, 255, 0);");
            break;
        case status::BUSY:
            setStyleSheet("background-color: rgb(255, 0, 0);");
            break;
        case status::BOOKED:
            setStyleSheet("background-color: rgb(0, 0, 255);");
            break;
        default:
            break;
    }
}

int pSlot::getStatus(void) const {
    return Status;
}