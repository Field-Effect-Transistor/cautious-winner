#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "auth/startWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    startWidget w;
    w.show();

    return app.exec();
}