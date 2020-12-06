#ifndef MYSERVER_H
#define MYSERVER_H
#include <QtGui>
#include <QWidget>
namespace Ui {
    class MyServer;
}
class QTcpServer;
class QTcpSocket;
class MyServer : public QWidget
{
    Q_OBJECT
    QTcpServer* server;
    quint16 nextBlockSize; // длина следующего полученного от сокета блока
    void sendToClient(QTcpSocket* socket, const QString& str);
public:
    explicit MyServer(int port, QWidget *parent = 0);
    ~MyServer();
private:
    Ui::MyServer *ui;
public slots:
    virtual void slotNewConnection();
    void slotReadClient();
};
#endif // MYSERVER_H
