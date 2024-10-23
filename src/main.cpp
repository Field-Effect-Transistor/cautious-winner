#include <QApplication>
#include <QTimer>
#include "startWidget.hpp"
#include "authWidget.hpp"
#include "loginWidget.hpp"
#include "regWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    startWidget startWithAuth;
    startWithAuth.show();
    
    return app.exec();
}
