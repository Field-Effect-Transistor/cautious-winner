#include "mapWidget.hpp"

mapWidget::mapWidget(QWidget* parent) : QWidget(parent) {
        layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

        for(int i = 0; i < 10; i++) {
            pSlots[i] = new pSlot(10 + i * 35, 10, i, this, alignment::V);
        }

        for(int i = 0; i < 5; i++) {
            pSlots[i + 10] = new pSlot(10, 130 + i * 35, i + 10, this, alignment::H);
        }

        for(int i = 0; i < 5; i++) {
            pSlots[i + 15] = new pSlot(130, 130 + i * 35, i + 15, this, alignment::H);
        }

        for(int i = 0; i < 5; i++) {
            pSlots[i + 20] = new pSlot(185, 130 + i * 35, i + 20, this, alignment::H);
        }

        for(int i = 0; i < 5; i++) {
            pSlots[i + 25] = new pSlot(305, 130 + i * 35, i + 25, this, alignment::H);
        }

        for(int i = 0; i < 10; i++) {
            pSlots[30 + i] = new pSlot(10 + i * 35, 360, i + 30, this, alignment::V);
        }

        setWindowTitle("Parking Map");
        setFixedSize(365, 420);
}

mapWidget::~mapWidget() {}