#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

#define R 50
#define CENTER_X 0.5
#define CENTER_Y 0.1
#define PEND_RADIUS 0.5

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),pixmap(R*2,R*2),r(R),// задаем размеры
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pixmap.fill(Qt::transparent);// прозрачный цвет фона
    QPainter painter(&pixmap); // контекст устройства в памяти на базе изображения
    painter.setBrush(Qt::blue);// цвет  круга
    painter.setRenderHint(QPainter::Antialiasing);// сглаживание
    painter.drawEllipse(QPoint(R, R), R, R); // рисуем окружность в памяти
    timer.start(5);// запускаем таймер
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
// по каждому сигналу таймера перерисовываем окно
    step = qDegreesToRadians(0.25); // смещение изображения
    // p = QPoint(r-51,0); // начальное положение верхнего левого угла изображения
    angle = -180;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter pntr(this);
    w = width()-1;
    h = height()-ui->statusbar->height();

    angle += step;

    QPoint pendPoint(w * CENTER_X, h * CENTER_Y);
    QPoint ballPoint = pendPoint + QPoint(cos(angle) * PEND_RADIUS * w, sin(angle) * PEND_RADIUS * w);

    pntr.drawLine(pendPoint, ballPoint);
    pntr.drawPixmap(ballPoint - QPoint(R, R), pixmap);

    QPoint radius(R, 0);
    if ((ballPoint - radius).x() < 0 || (ballPoint + radius).x() > w) step = -step;
//    p.setX(p.x()+step);
}
