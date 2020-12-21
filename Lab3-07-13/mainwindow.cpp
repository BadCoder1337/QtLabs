#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>

#define WINDOW_HEIGHT 1000

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menubar->addAction(ui->actionD);
 // размещаем команду в главном меню (без выпадающего меню)
    dlg = new Dialog(this); // создаем объект диалогового окна
    scroll = new QScrollArea(this); // создаем область прокрутки
    pole = new Pole(); // создаем рабочее поле
    a = -5;
    b = 5;
    setCentralWidget(scroll); // размещаем область прокрутки в главном окне
    pole->resize(width()-22, 1000); // задаем размеры рабочей области
    scroll->setWidget(pole);  // размещаем рабочую область в области прокрутки
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
 // передаем размеры и диапазон объекту "pole":
    pole->w = width()-22;
    pole->h = WINDOW_HEIGHT;
    pole->a = a;
    pole->b = b;
    pole->resize(width()-22, 1000);
    pole->update(); // при перерисовке главного окна перерисовываем график
    scroll->verticalScrollBar()->setValue(375);
    // устанавливаем начальную величину прокрутки
}
void MainWindow::on_actionD_triggered()
{
    dlg->move(400+width(), 250); // размещаем диалоговое окно справа от главного окна
    dlg->show();
    dlg->activateWindow();
}
