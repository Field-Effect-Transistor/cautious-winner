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
#include "parkingTableWidget.hpp"
#include "slotStatusTable.hpp"
#include "../network/Client.hpp"
#include "../auth/errorDialog.hpp"

class mainWindow : public QWidget {
    Q_OBJECT
protected:
    Client& client;

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
    parkingTableWidget* parkingTable;
    slotStatusTable* slotStatus;
    QWidget* blank;

    QWidget* alignWidget;
    //QLabel* mapTableLabel;
    //QLabel* actionsLabel;
    //QLabel* menuLabel;

    QPushButton* parkBtn;
    QPushButton* parkHistoryBtn;
    QPushButton* bookBtn;
    QPushButton* slotInfoBtn;
    QPushButton* exitBtn;

public:
    explicit mainWindow(Client& client, QWidget *parent = nullptr);
    ~mainWindow();
public slots:
    void updateMap(void);
    void parkSlot(void);
    void endParkSlot(void);
    void bookSlot(void);
    void parkHistorySlot(void);
    void slotStatusSlot(void);
};