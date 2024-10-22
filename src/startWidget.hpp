#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFont>

#include "login.hpp"
#include "authWidget.hpp"

class startWidget : public QWidget {
    Q_OBJECT

protected:

    QBoxLayout* layout;
    QBoxLayout* alignLayout;


    QWidget* currWidget;
    
    QLabel* mesg;
    //picture
    QLabel* picLabel;

public:
    explicit startWidget(QWidget *parent = nullptr);
    ~startWidget();
};