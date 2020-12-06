#ifndef MYCLIENT_H
#define MYCLIENT_H
#include <QWidget>
#include <QTcpSocket>
namespace Ui {
    class MyClient;
}
class MyClient : public QWidget
{
    Q_OBJECT

    QTcpSocket* socket; // Объект для обмена данными
quint16  nextBlockSize; // Размер блока данных
public:
    explicit MyClient(QWidget *parent = 0);
    ~MyClient();
private:
    Ui::MyClient *ui;
public slots:
    void slotReadyRead(); // выполняет чтение данных, пришедших с сервера
    void slotError(QAbstractSocket::SocketError);
// выводит сообщение об ошибке
    void slotSendToServer(); // отправляет данные серверу
    void slotConnected(); // выводит сообщение об установке соединения
private slots:
    void on_pushButton_clicked();
};
#endif // MYCLIENT_H
