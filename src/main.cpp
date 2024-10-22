#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "startWidget.hpp"
#include "authWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    startWidget main;
    main.show();

    authWidget auth;
    auth.show();
    
    return app.exec();
}
