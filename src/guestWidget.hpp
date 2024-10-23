#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>

class guestWidget : public QWidget {
    Q_OBJECT

protected:
    QBoxLayout* layout;
    QBoxLayout* inputBoxLayout;
    QBoxLayout* buttonBoxLayout;

    QGroupBox* inputGB;
    QGroupBox* buttonGB;

    QLineEdit* emailIn;
    QLineEdit* licenseIn;

public:
    QPushButton* guestLoginBtn;
    QPushButton* retBtn;

    explicit guestWidget(QWidget *parent = nullptr);
    ~guestWidget();
};