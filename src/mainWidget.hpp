#pragma once

#include <QWidget>
#include <QBoxLayout>

#include "login.hpp"

class MainWidget : public QWidget {
    Q_OBJECT

protected:

    QBoxLayout* currLayout;
    QWidget* currWidget;

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
};