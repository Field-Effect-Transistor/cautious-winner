#pragma once

#include <QBoxLayout>

#include <array>

#include "pSlot.hpp"

class mapWidget : public QWidget {
    Q_OBJECT
public:
    static const int pSlotCount = 40;
    //std::array<pSlot*, pSlotCount> pSlots;
    pSlot* pSlots[pSlotCount];
    
protected:
    QBoxLayout* layout;


public:
    mapWidget(QWidget* parent = nullptr);
    ~mapWidget();


};
