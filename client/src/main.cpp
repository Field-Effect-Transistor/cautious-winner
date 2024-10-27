#include <QApplication>
#include <QLabel>
#include <QWidget>

#include <array>

#include "auth/startWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    //app.setStyleSheet("QToolTip { color: #6C0808; }");
        
    std::array<QLabel, 5> labels;

    startWidget w;
    w.show();

    return app.exec();
}