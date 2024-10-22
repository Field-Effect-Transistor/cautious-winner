#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>

class loginWidget : public QWidget {
    Q_OBJECT

protected:
    QBoxLayout* layout;
    QBoxLayout* loginBoxLayout;

    

public:
    loginWidget(QWidget *parent = nullptr);
    ~loginWidget();
};