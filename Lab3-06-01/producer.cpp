#include "producer.h"
 // глобальные переменные и объекты, доступные всем потокам (общие данные):
QQueue<int> queue;  // очередь целых чисел
// фактическое определение глобальной переменной:
int maxlen; // длина очереди
QMutex mutex; // объект для блокировки данных
 // условия ожидания:
QWaitCondition queueNotFull;
QWaitCondition queueNotEmpty;
Producer::Producer(QObject *parent) :
    QThread(parent)
{
    n = 0;
}
void Producer::produce()
{
    qDebug() << "Producing... ";
    mutex.lock(); /* блокирует доступ всем другим потокам к общим данным до тех пор, пока он не закончит работу с очередью */
    if (queue.size() == maxlen) // если очередь заполнена
    {
        qDebug() << "Queue is full, waiting!";
        queueNotFull.wait(&mutex);
/* поток должен ждать пока не появится место в очереди (поток consumer должен прислать сообщение об этом) */
    }
 // если в очереди есть место:
    n++;  // для наглядности генерируем число на 1 больше
    //n = 1+qrand() % 100;
    qDebug() << "produce " << n;
    queue.enqueue(n); // поток добавляет число в очередь
    queueNotEmpty.wakeAll();
 // сообщает всем другим потокам, что условие "очередь не пуста" выполнено
    mutex.unlock(); // текущий поток освобождает общие данные
}
void Producer::run() // основная функция
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i=1; i<=10; ++i) // поток должен сгенерировать 10 чисел
    {
        msleep(qrand() % 300 + 1); /* останавливает выполнение потока на заданное количество миллисекунд (имитация какой-то деятельности) */
        produce();  // генерирует следующее число
    }
}
