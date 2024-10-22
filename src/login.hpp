#pragma once

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QPixmap>
#include <QFont>

class Login : public QWidget {
    Q_OBJECT
protected:
    //boxes
    QBoxLayout* windowLayout;
    QBoxLayout* inputLayout;
    QBoxLayout* unameInputLayout;
    QBoxLayout* passwdInputLayout;
    QBoxLayout* buttonLayout;
    QBoxLayout* RGbuttonLayout;

    //for alignment
    QBoxLayout* unameInLayout;
    QBoxLayout* passwdInLayout;

    //groups
    QGroupBox* inputGB;
    QGroupBox* buttonGB;

    //input
    QLineEdit* unameIn;
    QLineEdit* passwdIn;

    //buttons
    QPushButton* loginBtn;
    QPushButton* regBtn;
    QPushButton* guestBtn;

    //picture
    QLabel* picLabel;

public:

    explicit Login(QWidget *parent = nullptr);
    ~Login();

};
