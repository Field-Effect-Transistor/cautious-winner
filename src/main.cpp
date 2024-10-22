#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "startWidget.hpp"
#include "authWidget.hpp"
#include "loginWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    authWidget auth;
    auth.show();
    loginWidget login;
    login.show();

    startWidget startWithAuth(&auth), startWithLogin(&login);
    startWithAuth.show();
    startWithLogin.show();
    
    return app.exec();
}
