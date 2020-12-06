#include "myclient.h"
#include "ui_myclient.h"
#include <QTime>
MyClient::MyClient( QWidget *parent) :
    QWidget(parent), nextBlockSize(0),
    ui(new Ui::MyClient)
{
    ui->setupUi(this);
    ui->lineEditHost->setText("localhost"); // указываем имя или адрес сервера
    ui->lineEditPort->setText("2323");
    socket = new QTcpSocket(this); // создаем сокет
    // Коммуникация сокетов асинхронная
 // при поступлении сигнала об установке соединения выводится сообщение об этом:
    connect(socket, SIGNAL(connected()), SLOT(slotConnected()));
 // при поступлении данных вызывается слот, считывающий эти данные:
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
     connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(slotError(QAbstractSocket::SocketError)));
 // при щелчке по кнопке "Отправить" или при нажатии клавиши <Enter> вызывается слот
 // для отправки данных серверу:
     connect(ui->pushButtonSend, SIGNAL(clicked()), SLOT(slotSendToServer()));
     connect(ui->lineEditSend, SIGNAL(returnPressed()), SLOT(slotSendToServer()));
}
 // Слот для кнопки "Соединиться":
void MyClient::on_pushButton_clicked()
{
     QString strHost = ui->lineEditHost->text(); // считываем номер компьютера
     int port = ui->lineEditPort->text().toInt(); // считываем номер порта
    socket->connectToHost(strHost, port); // Устанавливаем связь с сервером
}
MyClient::~MyClient()
{
    delete ui;
}
// слот выводит сообщение об установке соединения:
void MyClient::slotConnected()
{
    ui->textEdit->append("Received the connected signal \n");
}
// слот выводит сообщение об ошибке:
void MyClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError = "Error: " + (err ==QAbstractSocket::HostNotFoundError?
                                    "The host was not found." :
                               err == QAbstractSocket::RemoteHostClosedError?
                                    "The remote host is closed." :
                               err == QAbstractSocket::ConnectionRefusedError?
                                    "The connection was refused.":
                                    QString(socket->errorString()));
    ui->textEdit->append(strError);
}
 // слот для чтения данных, поступивших через сокет:
void MyClient::slotReadyRead()
{
    QDataStream in(socket);  // создаем поток на основе сокета
    in.setVersion(QDataStream::Qt_4_8);  // задаем версию формата потока
    forever  // бесконечный цикл на случай когда поток состоит из несколькх блоков
    {
        if ( ! nextBlockSize)  // если текущий размер блока равен 0
        {
            if (socket->bytesAvailable() < sizeof(quint16))
                break; // если размер данных меньше 2 байт, прерываем цикл
            in >> nextBlockSize;  // считываем размер очередного блока
        }
        if (socket->bytesAvailable() < nextBlockSize)
             break;  /* исли данных в потоке меньше, чем указанный рамер блока, значит произошла ошибка, прерываем цикл */

       QTime time;
       QString str;
       in >> time >> str;   // считываем время и текст
       ui->textEdit->append(time.toString() + " " + str);
// отображаем полученные данные в окне
       nextBlockSize = 0;  // признак окончания чтения очередного блока
    }
}
 // слот для отправки данных серверу:
void MyClient::slotSendToServer()
{
    QByteArray arrBlock;  // массив байт для передачи данных через сокет
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
     // поток для формирования данных
    out.setVersion(QDataStream::Qt_4_8);  // версия формата потока
    QString text = ui->lineEditSend->text();
     // считываем данные, которые пользователь ввел в окне
    out << quint16(0) << QTime::currentTime() << text;
// записываемразмер блока (в начале ноль), время и текст
    out.device()->seek(0);  // переходим в начало блока
    out << quint16(arrBlock.size() - sizeof(quint16));
 // записываем действительный размер данных
    //  qDebug() <<"n = " << quint16(arrBlock.size() - sizeof(quint16));
     socket->write(arrBlock); // передаем данные
    ui->lineEditSend->clear(); // очищаем окно
}
