#include <iostream>
#include <QtNetwork>
#include <QTextCodec>
 // макрос для преобразования QString в строку, которую может вывести cout :
#define STR(s) ((codec->fromUnicode(s)).constData())
 /* fromUnicode() - функция из класса QTextCodec, которая выполняет преобразование QString в заданную кодировку и возвращает массив типа QByteArray */
/* constData() - возвращает указатель на строку, заканчивающуюся байтом с кодом '\0', которая хранится в массиве QByteArray */

#ifdef Q_OS_WIN32
#include <Windows.h>
#endif

using namespace std;
int main(int /*argc*/, char** /*argv*/)
{
    #ifdef Q_OS_WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    QTextCodec* codec = QTextCodec::codecForName("Utf-8");
    QTextCodec::setCodecForLocale(codec);
    QTcpServer server;
    QTcpSocket* client; // Клиентский сокет
    QByteArray block; // блок для обмена данными
    QHostAddress addr; // адрес клиента
    QString s; // строка, которую присылает клиент
   if (!server.listen(QHostAddress::Any, 5678))
       // Переводим сервер в слушающий режим
       /* номер компьютера, от которого ожидается соединение - любой, номер порта, который прослушивает сервер - 5678 */
    {
        cout << codec->fromUnicode(QString("Не могу запустить сервер: %1 \n")
                                   /* например, если порт уже занят */
                                   .arg(server.errorString())).constData();
 // здесь приведен пример прямого использования функций fromUnicode() и constData()
        server.close();
        return 1;
    }
    cout << "Сервер запущен\n";  // здесь перекодировка не требуется
    // все функции wait... - блокируют работу потока
/* функция waitForNewConnection()возвращает false, если соединение не произошло, и цикл повторяется */
// если клиент подключился, функция завершается и возвращает true
    while (!server.waitForNewConnection(5000)) // Ожидаем подключения клиента
            cout << "Ожидание запроса на подключение клиента...\n";
// выводится каждые 5 сек
  // подключение поизошло, создаем для него новый сокет:
    client = server.nextPendingConnection();
    addr = client->peerAddress(); // определяем адрес клиента
    cout << STR(QString("Подключился новый клиент с адреса %1\n").arg(addr.toString())); // здесь используется макрос
    block = codec->fromUnicode(QString("Hello! Привет!"));
    client->write(block); // Отправляем клиенту приветственное сообщение
 // параметр функции write() должен иметь тип QByteArray
    // цикл для обмена данными с клиентом:
forever  // бесконечный цикл
    {
            if (!client || !client->isValid() || client->state() ==
                QAbstractSocket::UnconnectedState)
// проверяем, не отключился ли клиент
            {
                delete client; // уничтожаем клиентский сокет
                cout << "Клиент отключился\n";
                break;
            }
            if(client->waitForReadyRead(1000))
// в течение 1 сек ожидаем прихода от клиента каких-нибудь данных
// если данные поступили, функция сразуже завершается
            {
                block = client->readAll();
 // считываем данные (QByteArray), полученные через сокет
                s = codec->toUnicode(block.data()); // преобразование в QString

                // шифр цезаря (сдвиг 5)
                int offset = 5;
                s = s.toLower();
                for (int i = 0; i < s.length(); i++) {
                    if (s[i].toLatin1() >= 'a' && s[i].toLatin1() <= 'z')
                        s[i] = 'a' + (s[i].toLatin1() - 'a' + offset) % 26;
                }

                cout << STR(QString("Получены новые данные: %1 \n").arg(s));
                client->write(codec->fromUnicode(s));
// отправляем строку обратно клиенту
                if (s.contains("stop"))
                {
                    cout << "Сервер остановлен\n";
                    client->disconnectFromHost();
                    return 0;
                }
            }
        }
    return 0;
}
