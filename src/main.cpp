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

    // Створюємо таймер для зміни віджета через 5 секунд
    QTimer::singleShot(5000, [&]() {
        // Перемикаємося на loginWidget
        startWithAuth.switchTo(ID::REGISTER);
    });
/**
    // Створюємо таймер для зміни віджета через 5 секунд
    QTimer::singleShot(10000, [&]() {
        // Перемикаємося на loginWidget
        startWithAuth.switchTo(ID::LOGIN);
    });

    // Створюємо таймер для зміни віджета через 5 секунд
    QTimer::singleShot(15000, [&]() {
        // Перемикаємося на loginWidget
        startWithAuth.switchTo(ID::REGISTER);
    });
*/

    return app.exec();
}
