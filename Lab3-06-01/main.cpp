#include <QCoreApplication>
#include "producer.h"
#include "consumer.h"
// глобальная переменная, в которой хранится максимальная длина очереди  чисел:
extern int maxlen; /* extern указывает, что фактическое определение глобальной переменной происходит в другом файле */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    maxlen = 5;
// задаем небольшую очередь, чтобы проследить, что происходит, когда она заполнена
    Producer* producer = new Producer;
 // поток, генерирующий числа и записывающий их в очередь
    Consumer* consumer = new Consumer; // поток, забирающий числа из очереди
    QObject::connect(producer, SIGNAL(finished()), consumer, SLOT(getStop()),Qt::DirectConnection); /* если producer закончил работу, вызывается слот getStop(), в котором consumer отмечает, что producer закончил генерировать данные; параметр DirectConnection предписывает немедленно обработать сигнал, а не ста¬вить его в очередь */
    QObject::connect(consumer, SIGNAL(finished()), &a,      SLOT(quit()));
// когда поток-потребитель заканчивает свою работу, приложение завершается
    producer->start(); // запускаем поток-производитель
    consumer->start(); // запускаем поток-потребитель
    return a.exec(); // очередь событий для основного потока
}
