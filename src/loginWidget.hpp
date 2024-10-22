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

    QLineEdit* unameIn;
    QLineEdit* passwdIn;

    QPushButton* loginBtn;
    QPushButton* retBtn;

public:
    loginWidget(QWidget *parent = nullptr);
    ~loginWidget();
};