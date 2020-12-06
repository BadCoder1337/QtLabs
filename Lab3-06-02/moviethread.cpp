#include "moviethread.h"
#include <QDebug>
MovieThread::MovieThread() :
    QThread(), delay(100)
{
     loadPics(); // загружаем картинки
}
void MovieThread::run()
{
    int current = 0; // начальный номер картинки
    int count = pics.size(); // количество изображений
    forever
    {
        msleep(delay); // пауза на заданное количество миллисекунд
        emit show(&pics[current]);
// посылаем сигнал о показе картинки с текущим номером
        current = (current+1) % count; // переходим к следующей картинке
    }
}
void MovieThread::loadPics()
// создаем массив изображений, хранящихся в указанных файлах ресурсов
{
    for (int i = 1; i<=68; i++) {
        pics << QPixmap(QString(":/img/%1.png").arg(i));
    }
    qDebug() << "Frames loaded!" << pics;
}
void MovieThread::stop()
{
    terminate(); // завершаем поток
    wait(1000);  /* поток задерживает остановку приложения, чтобы завершить все текущие операции (msleep) */
}
 // Устанавливает для потока значение задержки, переданное из главного окна:
void MovieThread::setInterval(int delay)
{
    this->delay = delay;
// элемент данных класса делаем равным переданному значению
}
