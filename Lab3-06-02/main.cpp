#include <QtWidgets/QApplication>
#include "moviewin.h"
#include "moviethread.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MovieWin win; // главное окно
    MovieThread movie; // вспомогательный поток
 // при получении сигнала show с адресом картинки главное окно показывает эту картинку:
    a.connect(&movie, SIGNAL(show(const QPixmap*)), &win, SLOT(showPix(const QPixmap*)), Qt::QueuedConnection);
 // если пользователь изменил положение ползунка, поток получает новое значение задержки:
    a.connect(&win, SIGNAL(intervalChanged(int)), &movie, SLOT(setInterval(int)), Qt::QueuedConnection);
 /* если пользователь завершает работу приложения, оно посылает сигнал о завершении работы вспомогательному потоку: */
    a.connect(&a, SIGNAL(aboutToQuit()), &movie, SLOT(stop()));
    win.move(400,200);
    win.setDelay(500); // устанавливаем начальную задержку в миллисекундах
    movie.start(); // запускаем вспомогательный поток
    win.show();
    return a.exec();
}
