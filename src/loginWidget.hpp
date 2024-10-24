#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>

class loginWidget : public QWidget {
    Q_OBJECT

protected:
    QBoxLayout* layout;
    QBoxLayout* inputBoxLayout;
    QBoxLayout* buttonBoxLayout;

    QGroupBox* inputGB;
    QGroupBox* buttonGB;

public:
    QLineEdit* emailIn;
    QLineEdit* passwdIn;

    QPushButton* loginBtn;
    QPushButton* retBtn;

    loginWidget(QWidget *parent = nullptr);
    ~loginWidget();
};