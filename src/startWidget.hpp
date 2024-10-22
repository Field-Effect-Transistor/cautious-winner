#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QStackedWidget>
#include <QIcon>

#include "authWidget.hpp"
#include "loginWidget.hpp"

class startWidget : public QWidget {
    Q_OBJECT

public:
    QBoxLayout* layout;
    QBoxLayout* alignLayout;

    QLabel* mesg;
    QLabel* picLabel;

    QStackedWidget* stackedWidget;

    authWidget* auth;
    loginWidget* login;

public:
    explicit startWidget(QWidget *parent = nullptr);
    ~startWidget();

    void switchToLogin();  // Функція для зміни на loginWidget
};
