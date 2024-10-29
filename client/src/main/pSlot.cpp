#include "pSlot.hpp"

pSlot::pSlot(int x, int y, int ID, QWidget* parent, int align): QPushButton(QString::number(ID), parent) {
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    setPosition(x, y);
    align ? setFixedSize(30, 50) : setFixedSize(50, 30);
    setStatus(status::FREE);
    setID(ID);
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
            setStyleSheet("QPushButton { "
              "font-size: 16px; "
              "color: white; "
              "background-color: rgb(0, 180, 0); "
              "border: none; "
              "border-radius: 5px; "
              "padding: 5px; "
              "}");
            break;
        case status::BUSY:
            setStyleSheet("QPushButton { "
              "font-size: 16px; "
              "color: white; "
              "background-color: rgb(180, 0, 0); "
              "border: none; "
              "border-radius: 5px; "
              "padding: 5px; "
              "}");
            break;
        case status::BOOKED:
            setStyleSheet("QPushButton { "
              "font-size: 16px; "
              "color: white; "
              "background-color: rgb(0, 0, 180); "
              "border: none; "
              "border-radius: 5px; "
              "padding: 5px; "
              "}");
            break;
        default:
            break;
    }
}

int pSlot::getStatus(void) const {
    return Status;
}