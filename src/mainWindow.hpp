#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QStackedWidget>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QPushButton>


class mainWindow : public QWidget {
    Q_OBJECT
protected:

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
};