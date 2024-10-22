#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "login.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Login login(nullptr);
    login.show();

    return app.exec();
}
