#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtGui"
#include <QColorDialog>
#include <QFileDialog>

/*
1.	Создать приложение, которое расчерчивает окно правильными шестиуголь¬никами (размер – 1/20 высоты окна)
и при щелчке мышью в шестиугольнике закрашивает его цветом,
выбираемым с помощью немодального диалогового окна с наборными счетчиками (Spin),
которые позволяют установить интен¬сивности красной, зеленой и синей составляющих цвета.
Предоставьте воз¬можность сохранять изображение в файле и считывать его из файла.
Проверку, в какой ячейке пользователь щелкнул мышью, выполнять с помо¬щью областей QRegion!

*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < maxR; ++i)
        for (int j = 0; j < maxC; ++j)
            Color[i][j] = QColor(0, 100, 100);
    // Заполняем матрицу начальным цветом
    previousRows = rows = columns = 0; // начальные размеры сетки
}
MainWindow::~MainWindow()
{
    delete ui;
}
// Виртуальная функция, которая вызывается при изменении размеров окна
void MainWindow::resizeEvent(QResizeEvent *)
{
    w = width();               // ширина рабочего поля
    y0 = centralWidget()->y(); // Верхняя граница клиентской области
    h = height() - y0;         // высота рабочего поля
    size = qMin(w, h) / HEXAGON_SIZE;
    // размер одной ячейки (расстояние между двумя противоположными вершинами)
    if (size < 2)
        size = 2;
    // размер не может оказаться равным нулю, чтобы не произошло деление на ноль
    // qDebug() << "size = " << size;
    r = size / 2; // радиус окружности, в которую вписана ячейка
    x0 = r * sqrt(3) / 2;
    // расстояние от левой границы окна до центра первого 6-угольника (красная линия на рисунке)
    /* длина стороны правильного 6-угольника = r, а расстояние между ценрами ячеек (вертикаль-ный катет светлого треугольника) = r+r/2 = 3*r / 2 */
    rows = int(2 * h / (3 * r)) + 2; // количество полных рядов равно частному от деления высоты рабочей области на расстояние между центрами ячеек; к этому количеству нужно добавить 2 — неполные ряды на верхней и нижней границах окна
    if (rows > maxR)
        rows = maxR;
    // но количество рядов не может превышать задданый максимум
    //  qDebug() << "rows = " << rows;
    columns = int(w / (r * sqrt(3))) + 2;
    /* расстояние между центрами окружностей по горизонтали = (r*sqrt(3)/2) * 2 = r*sqrt(3), количество столбцов равно частному от деления ширины окна на расстояние между рядами + 2  неполных ряда на левой и правой границе */
    if (columns > maxC)
        columns = maxC;
    // количество столбцов неможет превышать заданный максимум
    // qDebug() << "columns = " <<columns;
    createMatrices(); /* при каждом изменении размеров окна создаем новые матрицы ячеек и соответствующих им областей */
    createNet();      // заполняем матрицы данными
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // рисуем многоугольники цветом, который записан в матрице цветов:
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
        {
            painter.setBrush(QBrush(Color[i][j]));
            painter.drawPolygon(Polygon[i][j]);
        }
}
// размещаем матрицы в памяти:
void MainWindow::createMatrices()
{
    if (previousRows)
    // удаляем предидущие матрицы из памяти, если они ненулевого размера
    {
        for (int i = 0; i < previousRows; ++i) // освобождаем память по строкам
        {
            delete[] Polygon[i]; // освобождаем память, выделенную для данных
            delete[] Region[i];
        }
        delete Polygon; // удаляем массивы указателей
        delete Region;
    }
    previousRows = rows; // запоминаем текущее количество строк
                         // создаем массивы указателей на строки данных:
    Polygon = new QPolygon *[rows];
    Region = new QRegion *[rows];
    //  захватываем память для строк данных:
    for (int i = 0; i < rows; ++i)
    {
        Polygon[i] = new QPolygon[columns]; // для координат 6-угольников
        Region[i] = new QRegion[columns];   // для областей
    }
}
void MainWindow::createNet() // заполняем матрицы данными
{
    double dx = r * sqrt(3);       // расстояние между центрами ячеек по горизонтали
    double dy = r * 3 / 2;         //  расстояние между центрами ячеек по вертикали
    for (int i = 0; i < rows; ++i) // проходим по строкам
    {
        for (int j = 0; j < columns; ++j) // проходим по одной строке
        {
            createPolygon(i, j);
            // создаем ячейку в i-ой строке и в j — м столбце (вызываем функцию)
            x0 += dx; // переходим в следующий столбец
        }
        y0 += dy; // переходим к следующей строке
        if (i % 2 == 0)
            x0 = 0;
        // начало следующего ряда, если текущая строка -  четная
        else
            x0 = r * sqrt(3) / 2; // если текущая строка - нечетная
    }
}
void MainWindow::createPolygon(int i, int j) // определяем координаты одной ячейки
{
    double x, y;                // координаты вершин многоугольника
    double da = M_PI / 3;       // угол между вершинами
    double angle = da / 2;      // начальный угол
    Polygon[i][j].clear();      // очищаем контейнер
    for (int k = 0; k < 6; ++k) // определяем вершины 6-угольника
    {
        // вычисляем координаты очередной вершины как точки на окружности
        x = x0 + r * cos(angle);
        y = y0 + r * sin(angle);
        Polygon[i][j] << QPoint(x, y);
        // добавляем координаты очередной точки к полигону
        angle += da; // переходим к следующей вершине
    }
    Region[i][j] = QRegion(Polygon[i][j]);
    // когда 6-угольник определен, создаем соответствующую область
}
// Слот, обрабатывающий щелчки мышью:
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();              // координаты курсора мыши
                                              // проверяем, в какой регион (в какой 6-угольник) попадает курсор мыши
    for (int i = 0; i < rows; ++i)            // проходим по строкам матрицы
        for (int j = 0; j < columns; ++j)     // по столбцам
            if (Region[i][j].contains(point)) // если курсор попадает в область
            {
                Color[i][j] = QColorDialog::getColor(); // выбираем цвет
                brush = QBrush(Color[i][j]);            // создаем кисть
                update(Region[i][j]);                   // перерисовываем 6-угольник
                goto exit;                              // выходим из циклов
            }
    exit:;
}
// слот для команды Save:
void MainWindow::on_actionSave_triggered()
{
    //  вызываем окно для выбора имени файла:
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить файл",
        QString(),
        QString("Файлы данных (*.dat);;Все файлы (*.*)")
    );
    QFile rezFile;           // Результирующий файл
    if (!fileName.isEmpty()) // Если имя файла задано
    {
        rezFile.setFileName(fileName);
        // присваиваем физическое имя результирующему файлу
        rezFile.open(QIODevice::WriteOnly);
        // открываем сохраняемый файл
        QDataStream out(&rezFile);
        /* создаем поток, связанный с файлом (запись файла обычно выполняется с помощью потока) */
        //   записываем матрицу цветов в файл:
        for (int i = 0; i < maxR; ++i)
            for (int j = 0; j < maxC; ++j)
                out << Color[i][j]; // записываем цвет ячейки с номерами i и j
        rezFile.close();
    }
}

// Слот, обрабатывающий команду Open:
void MainWindow::on_actionOpen_triggered()
{
    //   вызываем окно для выбора имени файла:
    QString fileName = QFileDialog::getOpenFileName(
        this,           //  указатель на родительское окно
        "Открыть файл", // заголовок окна
        QString(),      // выбор начинается с текущего каталога
        QString("Файлы с данными (*.dat);;Все файлы (*.*)")
    );
    // фильтры для списка файлов
    if (!fileName.isEmpty()) // если имя файла выбрано
    {
        QFile file;
        file.setFileName(fileName);
        // связываем объект file с физическим файлом
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file); // поток для чтения данных
        for (int i = 0; i < maxR; ++i)
            for (int j = 0; j < maxC; ++j)
                in >> Color[i][j]; // считываем цвет ячейки
        file.close();
    }
    /* Главное окно приложения автоматически перерисовывается при закрытии окна для выбора файла */
}
