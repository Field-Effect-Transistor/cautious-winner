#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>

class regWidget : public QWidget {
    Q_OBJECT
protected:
    QBoxLayout* layout;
    QBoxLayout* passwdLayout;
    QBoxLayout* inputBoxLayout;
    QBoxLayout* buttonBoxLayout;

    QGroupBox* inputGB;
    QGroupBox* buttonGB;

    QLineEdit* emailIn;
    QLineEdit* passwdIn;
    QLineEdit* rPasswdIn;
    QLineEdit* licenseIn;

    QPushButton* regBtn;
    QPushButton* retBtn;


public:
    explicit regWidget(QWidget *parent = nullptr);
    ~regWidget();
};