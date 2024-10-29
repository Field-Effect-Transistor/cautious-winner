#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QStackedWidget>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QPushButton>
#include <QSignalMapper>

#include "mapWidget.hpp"
#include "parkWidget.hpp"
#include "bookWidget.hpp"

class mainWindow : public QWidget {
    Q_OBJECT
protected:
    QBoxLayout* layout;
    QBoxLayout* alignLayout;
    QBoxLayout* leftLayout;
    //QBoxLayout* rightLayout;
    QBoxLayout* menuLayout;
    QBoxLayout* actionsLayout;
    QBoxLayout* mapTableLayout;

    QGroupBox* menuGB;
    QGroupBox* mapTableGB;
    QGroupBox* actionsGB;

    QStackedWidget* mapTableWidget;
    QStackedWidget* actionsWidget;

    mapWidget* map;
    parkWidget* park;
    bookWidget* book;

    QWidget* alignWidget;
    //QLabel* mapTableLabel;
    //QLabel* actionsLabel;
    //QLabel* menuLabel;

    QPushButton* parkBtn;
    QPushButton* parkHistoryBtn;
    QPushButton* bookBtn;
    QPushButton* exitBtn;

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
};