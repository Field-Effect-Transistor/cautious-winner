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
#include "guestWidget.hpp"
#include "regWidget.hpp"

class startWidget : public QWidget {
    Q_OBJECT

protected:
    QString title;

    QBoxLayout* layout;
    QBoxLayout* alignLayout;

    QLabel* mesg;
    QLabel* picLabel;

    QStackedWidget* stackedWidget;

    authWidget* auth;
    loginWidget* login;
    guestWidget* guest;
    regWidget* reg;

public:
    explicit startWidget(QWidget *parent = nullptr);
    ~startWidget();

    void switchTo(int ID);

private slots:
    void switchToAuth();
    void switchToLogin();
    void switchToGuest();
    void switchToReg();
    void exitApp();
};

namespace ID {
    enum {
        AUTH        = 0,
        LOGIN       = 1,
        GUEST       = 2,
        REGISTER    = 3
    };
}