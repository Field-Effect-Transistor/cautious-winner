#pragma once

//#include <QLabel>
#include <QBoxLayout>

#include <array>

#include "pSlot.hpp"

class mapWidget : public QWidget {
    Q_OBJECT
public:
    QBoxLayout* layout;
    std::array<pSlot*, 50> pSlots;  // Оголошення масиву без ініціалізації


public:
    mapWidget(QWidget* parent = nullptr);
    ~mapWidget();

};
