#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtGui"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << event->pos();
        draw();
    }
};

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    this->painter = &p;
}

void MainWindow::draw() {

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(200, 150, 10));
    painter->drawRect(QRect(10, 10, 100, 100));
}
