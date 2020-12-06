#include "myserver.h"
#include "ui_myserver.h"
#include <QtNetwork>
#include <QByteArray>
#include <QMessageBox>
 // в конструктор в качестве параметра добавляем номер порта:
MyServer::MyServer(int port, QWidget *parent) :
    QWidget(parent), nextBlockSize(0),  // инициализируем размер блока
    ui(new Ui::MyServer)
{
    ui->setupUi(this);
    server = new QTcpServer(this); // инициализируем указатель на объект "сервер"
    if (!server->listen(QHostAddress::Any, port))
 // переводим сервер в слушающее состояние по указанному порту
    {
        QMessageBox::critical(0,"Server Error",
                          "Unable to start the server: " + server->errorString());
        return;
    }
    ui->textEdit->append("Server started\n");
    connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    // сигнал newConnection() высылается при присоединении клиента
}
MyServer::~MyServer()
{
    delete ui;
}
 // -------------------------------------------------------------------------------------------------------------------

void MyServer::slotNewConnection()
// вызывается каждый раз при соединении с новым клиентом
{
    QTcpSocket* clientSocket = server->nextPendingConnection();
    // возвращает сокет для осуществления связи с клиентом
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater())); // при отсоединении клиента сокет уничтожается
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
 /* при поступлении сооб¬щений от клиентов сокет посылает сигнал readyRead() и вызывается слот  slotReadClient() */
    sendToClient(clientSocket, "Server Response: Connected!");
// отсылаем клиенту сообщение об установке соединения
}
 // -------------------------------------------------------------------------------------------------------------------

void MyServer::sendToClient(QTcpSocket *socket, const QString &str)
        // формируем данные, которые будут отосланы клиенту
{
    QByteArray arrBlock;
/* нам заранее не известен размер блока, а размер блока должен быть выслан в первую очередь */
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
// создаем поток на основе массива arrBlock
    out.setVersion(QDataStream::Qt_4_7);
    out << quint16(0) << QTime::currentTime() << str;
    /* записываем все данные (вместо реального размера записываем 0, поскольку размер блока пока неизвестен) */
    out.device()->seek(0); // перемещаем указатель на начало блока
    out << quint16(arrBlock.size() - sizeof(quint16));
    // записываем в начало блока его реальный размер
    socket->write(arrBlock); // передаем данные
}
 // -------------------------------------------------------------------------------------------------------------------

void MyServer::slotReadClient() // считывает сообщение от клиента
{
   QTcpSocket* clientSocket = (QTcpSocket*)sender();
// создаем сокет для чтения сообщения
   QDataStream in(clientSocket);
 // поток для чтения данных, которые могут быть не только текстовыми
   in.setVersion(QDataStream::Qt_4_7);

// каждый переданный сокетом блок начинается полем размера блока
   forever
// повторяем чтение данных, поскольку возможно , что не все данные пришли одновременно
    {
       // сначала считываем размер блока данных
    if(!nextBlockSize) // если размер блока равен 0
       {
            if (clientSocket->bytesAvailable()<sizeof(quint16)) break;
 // если размер полученных данных меньше 2 байт, завершаем чтение данных
            in >> nextBlockSize; // считываем размер блока
       }
        qDebug() << "nextBlockSize: " << nextBlockSize;

       if (clientSocket->bytesAvailable() < nextBlockSize) break;
// если данных пришло меньше, чем указано, чтение прекращается

    QTime time;
    QString str;
    in >> time >> str; // считываем время отправки сообщения и текст
    QString strMessage = time.toString() + " Client has sent - " + str;
 // выводим на экран  полученное сообщение:
    ui->textEdit->append(strMessage);
    nextBlockSize = 0;

    str = str.toLower();

    //шифр цезаря (сдвиг 1)
    int offset = 1;
    for (int i = 0; i < str.length(); i++) {
        if (str[i].toLatin1() >= 'a' && str[i].toLatin1() <= 'z')
            str[i] = 'a' + (str[i].toLatin1() - 'a' + offset) % 26;
    }

    sendToClient(clientSocket, "Server Response: Encrypted \"" + str + "\"") ;
 // отправляем клиенту подтверждение о получении сооб¬щения
    } // end forever
}
