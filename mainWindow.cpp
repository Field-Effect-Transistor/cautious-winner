#include "mainWindow.hpp"

mainWindow::mainWindow(QWidget* parent) : QWidget(parent) {
    layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    leftLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    menuLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    stackedLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    menuGB = new QGroupBox(this);
    workspaceGB = new QGroupBox(this);
    stackedGB = new QGroupBox(this);

    
}

mainWindow::~mainWindow() {} ;