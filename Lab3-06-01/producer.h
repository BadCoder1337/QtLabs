#ifndef PRODUCER_H
#define PRODUCER_H
#include <QtCore>
class Producer : public QThread
{
    Q_OBJECT
    int n; // число, которое генерирует этот поток
public:
    explicit Producer(QObject *parent = 0);
    void produce();  // функция, генерирующая число
    void run();
 /* виртуальный метод, который нужно обязательно переопределить, чтобы создать поток */
};
#endif // PRODUCER_H
