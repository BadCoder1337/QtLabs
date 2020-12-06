#include <iostream>
#include <QtNetwork>
#include <QTextCodec>
#define STR(s) ((codec->fromUnicode(s)).constData())

#ifdef Q_OS_WIN32
#include <Windows.h>
#endif

#define IP_ADDR "127.0.0.1"

using namespace std;
int main(int /*argc*/, char** /*argv*/)
{
    #ifdef Q_OS_WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
// Обеспечивает перекодировку данных, вводимых с консоли
    QTcpSocket socket; // объявляем сокет
    QByteArray block; // буфер для обмена данными
    QString s;  // строка для чтения данных
// адрес сервера:
    char r[80] = IP_ADDR;   /* чтобы узнать адрес компьютера, наберите в терминале команду:
hostname -I
*/
    qint64 port = 5678;
   // cout << "Введите адрес или имя сервера ";
   // cin >> r;
    s = codec->toUnicode(r);
    // cout << "Введите номер порта сервера ";
    //  cin >> port;
    //  cin.get();// проглатываем признак конца строки
    socket.connectToHost(s, port); // пытаемся подключиться к серверу
    if (!socket.waitForConnected(5000))
// если в течение 5 сек подключение не произошло
    {
        cout << STR(QString("Не удалось связаться с сервером %1\n").arg(socket.errorString()));
        return 1; // завершаем работу
    }
 // соединение установлено
    // Ждем сигнал ReadyRead:
    if (!socket.waitForReadyRead(3000))
// если в течение 3 сек не получено приветствие от сервера
    {
        cout << STR(QString("Нет отклика от сервера %1\n").arg(socket.errorString()));
        return 2;// завершаем работу
    }
    // Если данные пришли:
    block = socket.readAll(); // считываем их
    s = codec->toUnicode(block.data());
    cout << STR(QString("Получено от сервера: %1\n").arg(s));
 // выводим строку приветствия на экран
// цикл обмена данными с сервером:
   forever // бесконечный цикл
   {
    cout << "Введите строку \n";
    cin.getline(r, 80);
    s = codec->toUnicode(r);
    // qDebug() << s;
// записываем данные во внутренний буфер сокета:
    if (socket.write(codec->fromUnicode(s)) < 0)
    {
        cout << STR(QString("не могу записать данные для отправки: %1\n").arg(socket.errorString()));
        return 3;// завершаем работу
    }
if (socket.waitForBytesWritten(3000)) // ждем отправки строки
        cout << STR(QString("Отправили на сервер строку:\n%1\n").arg(s));
    else
    {
        cout << STR(QString("Не могу отправить данные: %1\n").arg(socket.errorString()));
        return 4;// завершаем работу
    }
if (!socket.waitForReadyRead(3000)) // ждем данных от сервера (эхо)
    {
        cout << STR(QString("\nНет отклика от сервера: %1\n").arg(socket.errorString()));
        break; // прерываем цикл
    }
    //  Если сервер откликнулся:
    block = socket.readAll(); // считываем данные из сокета
    s = codec->toUnicode(block.data());
    cout << STR(QString("Получено от сервера: %1\n").arg(s));
}
    socket.disconnectFromHost(); // отключаемся от сервера
    cout << "Отключились от сервера\n";
    return 0;
}
