#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "startWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    //app.setStyleSheet("QToolTip { color: #6C0808; }");
        
    startWidget w;
    w.show();

    return app.exec();
}