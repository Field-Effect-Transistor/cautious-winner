#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>

class authWidget : public QWidget {
protected:

    QBoxLayout* layout;
    QBoxLayout* authBoxLayout;

    QGroupBox* authGB;

    QPushButton* loginBtn;
    QPushButton* regBtn;
    QPushButton* guestBtn;

    Q_OBJECT
public:
    explicit authWidget(QWidget *parent = nullptr);
    ~authWidget();
};