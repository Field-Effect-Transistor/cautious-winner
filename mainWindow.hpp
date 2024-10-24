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
    QBoxLayout* layout;
    QBoxLayout* menuLayout;
    QBoxLayout* stackedLayout;
    QBoxLayout* leftLayout;
    QBoxLayout* mapLayout;

    QStackedWidget* workspace;

    QGroupBox* menuGB;
    QGroupBox* workspaceGB;
    QGroupBox* stackedGB;

    QLabel* menutitle;

    QPushButton* 


public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
};