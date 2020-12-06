#include "consumer.h"
 // Объявление общих данных:
extern QQueue<int> queue;
extern QMutex mutex;
extern QWaitCondition queueNotFull;
extern QWaitCondition queueNotEmpty;
Consumer::Consumer(QObject *parent) :
    QThread(parent), stop(false) // признак завершения работы
{
}
int Consumer::consume()
{
    qDebug() << "Consuming...";
    QMutexLocker locker(&mutex); // блокируем общие данные
    if (queue.isEmpty()) // если очередь пуста
    {
        qDebug()<<"Queue is empty, waiting!";
        queueNotEmpty.wait(&mutex); /* поток переходит в режим ожидания выполнения условия "очередь не пуста" */
    }
    if (stop && queue.isEmpty()) return 0; /* если очередь пуста и признак "стоп" принял значение "истина" (producer закончил работу), прекращаем выполнение функции */
    int val = queue.dequeue(); // поток считывает число из очереди
    qDebug() << "consume " << val;
    queueNotFull.wakeAll(); // сообщаем остальным потокам, что в очереди есть место
    return val;
}
void Consumer::run()
{
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
  while(!stop)
    {
        consume(); // поток считывает число из очереди
        msleep(qrand() % 700 + 1); // имитация обработки считанного числа
    }
// пока очередь не пуста, поток считывает оставшиеся данные:
    while (!(queue.isEmpty()))
        consume();
      quit(); // завершение работы очереди событий
      exec();  // создание очереди событий (эта команда записывается последней)
}
void Consumer::getStop()
{
    stop = true; // признак того, что поток producer закончил работу
}
