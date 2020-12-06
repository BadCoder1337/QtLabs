#ifndef CONSUMER_H
#define CONSUMER_H
#include <QtCore>  // Содержит классы для работы с потоками
class Consumer : public QThread
{
    Q_OBJECT
    bool stop; // признак завершения всех операций
public:
    explicit Consumer(QObject *parent = 0);
    int consume();  // считывает число из очереди
    void run(); // основная функция
public slots:
    void getStop(); // слот, завершающий работу потока
};
#endif // CONSUMER_H
