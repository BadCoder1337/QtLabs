#ifndef MOVIETHREAD_H
#define MOVIETHREAD_H
#include <QPixmap>
#include <QThread>
class MovieThread : public QThread
{
    Q_OBJECT
    QVector<QPixmap> pics; // массив изображений
    int delay; // задержка (время показа очередной картинки на экране)
public:
    explicit MovieThread();
    ~MovieThread(){}
    void run(); // основная функция
    void loadPics(); // создает массив изображений
signals:
    void show(const QPixmap* image);
public slots:
    void stop(); // завершает работу потока
    void setInterval(int delay); // задает задержку
};
#endif // MOVIETHREAD_H
