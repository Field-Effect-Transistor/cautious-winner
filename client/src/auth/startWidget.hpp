#pragma once

#include <QApplication>
#include <QComboBox>
#include <QWidget>
#include <QCheckBox>
#include <QStyle>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QStackedWidget>
#include <QIcon>
#include <QToolTip>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>
#include <QFile>

#include <iostream>

#include "authWidget.hpp"
#include "loginWidget.hpp"
#include "guestWidget.hpp"
#include "regWidget.hpp"
#include "../../../include/validation.hpp"
#include "errorDialog.hpp"
#include "../main/mainWindow.hpp"
#include "../network/Client.hpp"

class startWidget : public QWidget {
    Q_OBJECT

protected:
    Client& client;

    QString title;

    QBoxLayout* layout;
    QBoxLayout* alignLayout;

    QLabel* mesg;
    QLabel* picLabel;
    QPixmap pixmap;

    QStackedWidget* stackedWidget;

    QPushButton* settingsBtn;

    authWidget* auth;
    loginWidget* login;
    guestWidget* guest;
    regWidget* reg;

public:
    explicit startWidget(Client& client, QWidget *parent = nullptr);
    ~startWidget();

    void switchTo(int ID);

private slots:
    void switchToAuth();
    void switchToLogin();
    void switchToGuest();
    void switchToReg();
    void exitApp();
    void loginSlot();
    void guestSlot();
    void regSlot();
    void passwdValidation();
    void rPasswdValidation();
    void settingsSlot();
};  

namespace ID {
    enum {
        AUTH        = 0,
        LOGIN       = 1,
        GUEST       = 2,
        REGISTER    = 3
    };
}