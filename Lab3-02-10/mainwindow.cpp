#include "mainwindow.h++"
#include "ui_mainwindow.h"
#include "pole.h++"
#include "QScrollArea"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//        QTextCodec* codec = QTextCodec::codecForName("UTF-8");
//        QTextCodec::setCodecForCStrings(codec);
        QScrollArea* scroll = new QScrollArea(this);
     // создаем область прокрутки
        Pole* pole = new Pole(scroll);  // создаем новый виджет
        scroll->setWidget(pole);  // размещаем виджет в области прокрутки
        setCentralWidget(scroll);  // делаем область прокрутки рабочей областью окна
        connect(ui->actionOpen, SIGNAL(triggered()), pole, SLOT(fileOpen()));
        connect(ui->actionSave, SIGNAL(triggered()), pole, SLOT(fileSave()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
Программа считывает массив неотрицательных чи­сел из файла,
выводит его на экран, используя полосы прокрутки,
и рисует круговую диаграмму для 13 самых больших элементов,
ото­б­ражая остальные в сумме.
*/

/*
Создать приложение на основе главного окна с прокруткой,
которое считывает массив типа QVector из файла.
Элементы массива должны быть неотрицатель­ны­ми. Вывести исходный массив на экран.
Найти элементы, значения которых больше среднего (вывести на экран эти элементы и их количество).
 Затем отсортировать массив по убыванию,
построить круговую диаграмму по пер­вым 13 элемен­там, представив остальные в сумме.
Отсортированный массив за­пи­сать в файл.
*/
