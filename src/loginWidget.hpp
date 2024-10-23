#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class loginWidget : public QWidget {
    Q_OBJECT

protected:
    QBoxLayout* layout;
    QBoxLayout* inputBoxLayout;
    QBoxLayout* buttonBoxLayout;

    QGroupBox* inputGB;
    QGroupBox* buttonGB;

    QLineEdit* emailIn;
    QLineEdit* passwdIn;

public:
    QPushButton* loginBtn;
    QPushButton* retBtn;

    loginWidget(QWidget *parent = nullptr);
    ~loginWidget();
};