#pragma once

#include <QLabel>
#include <QString>
#include <QBoxLayout>
#include <QPushButton>

namespace status {
    enum {
        FREE = 0,
        BUSY = 1,
        BOOKED = 2
    };
}

class pSlot: public QPushButton {
    Q_OBJECT
protected:
    int aleft;
    int atop;
    int ID;

    QBoxLayout* layout;

    int Status;
public:
    pSlot(int x, int y, int ID, QWidget* parent = nullptr);
    ~pSlot();

    void setID(int ID);
    int getID(void) const;

    void setPosition(int x, int y);
    void getPosition(int &x, int &y) const;

    void setStatus(int status);
    int getStatus(void) const;
};