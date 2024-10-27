#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>
#include <QDebug>

class guestWidget : public QWidget {
    Q_OBJECT

protected:
    QBoxLayout* layout;
    QBoxLayout* inputBoxLayout;
    QBoxLayout* buttonBoxLayout;

    QGroupBox* inputGB;
    QGroupBox* buttonGB;

public:
    QLineEdit* emailIn;
    QLineEdit* licenseIn;

    QPushButton* guestLoginBtn;
    QPushButton* retBtn;

    explicit guestWidget(QWidget *parent = nullptr);
    ~guestWidget();
};