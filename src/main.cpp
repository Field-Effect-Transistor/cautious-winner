#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "login.hpp"
#include "mainWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget main;
    main.show();

    return app.exec();
}
