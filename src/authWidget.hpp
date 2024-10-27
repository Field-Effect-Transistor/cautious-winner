#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

class authWidget : public QWidget {
    Q_OBJECT

protected:
    QBoxLayout* layout;
    QBoxLayout* authBoxLayout;

    QGroupBox* authGB;

public:
    QPushButton* loginBtn;
    QPushButton* regBtn;
    QPushButton* guestBtn;
    QPushButton* exitBtn;

    explicit authWidget(QWidget *parent = nullptr);
    ~authWidget();
};