#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>

class authWidget : public QWidget {
    Q_OBJECT

protected:
    QBoxLayout* layout;
    QBoxLayout* authBoxLayout;

    QGroupBox* authGB;

    QPushButton* loginBtn;
    QPushButton* regBtn;
    QPushButton* guestBtn;

public:
    explicit authWidget(QWidget *parent = nullptr);
    ~authWidget();
};