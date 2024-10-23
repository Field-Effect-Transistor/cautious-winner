#include <QApplication>
#include <QTimer>
#include "startWidget.hpp"
#include "authWidget.hpp"
#include "loginWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    startWidget startWithAuth;
    startWithAuth.show();

    // Створюємо таймер для зміни віджета через 5 секунд
    QTimer::singleShot(3000, [&]() {
        // Перемикаємося на loginWidget
        startWithAuth.switchTo(ID::GUEST);
    });

    // Створюємо таймер для зміни віджета через 5 секунд
    QTimer::singleShot(6000, [&]() {
        // Перемикаємося на loginWidget
        startWithAuth.switchTo(ID::GUEST);
    });

    // Створюємо таймер для зміни віджета через 5 секунд
    QTimer::singleShot(9000, [&]() {
        // Перемикаємося на loginWidget
        startWithAuth.switchTo(ID::GUEST);
    });


    return app.exec();
}
