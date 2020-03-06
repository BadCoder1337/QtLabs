#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtGui"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    buffer = nullptr;
    resizeEvent(nullptr);
}

MainWindow::~MainWindow()
{
    delete ui;
}

static const float sqrt3by2 = sqrt(3) / 2;

void MainWindow::resizeEvent(QResizeEvent *event) {
    delete buffer;
    buffer=new QPixmap(this->width(), this->height());
    buffer->fill(Qt::white);

//    draw(QPoint(0, 0));
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, *buffer);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << event->pos();
        draw(event->pos());
    }
};

void MainWindow::draw(QPoint pos) {
    buffer->fill(Qt::white);
    float hexSideLength = this->height() / ui->spinBox->value();

    QPainter painter(buffer);
    auto &pRef = painter;

    painter.setRenderHint(QPainter::Antialiasing);

    const float hexH = sqrt3by2 * hexSideLength;

    int horizCount = qFloor(this->width() / (hexSideLength * 1.5)) + 2,
        vertCount = qFloor(this->height() / (hexH * 2)) + 2;

    qDebug() << horizCount << " " << vertCount;

    for (int i = 0; i < horizCount; i++) {
        for (int j = 0; j < vertCount; j++) {
            if ((i + j) % 2 == 0)
                painter.setBrush(Qt::darkGray);
            else
                painter.setBrush(Qt::lightGray);
            drawHex(pRef,
                // pos
                QPoint(-0.5 * hexSideLength, 0)
                + QPoint(
                    i * hexSideLength * 1.5,
                    (j * 2 + i % 2) * hexH),
                hexSideLength);
        }
    }


    this->repaint();
}

void MainWindow::drawHex(QPainter &painter, QPoint pos, float sideLength) {
    QPolygonF poly;

    const float hexH = sqrt3by2 * sideLength;

    poly << QPointF(0, 0)
         << QPointF(0.5 * sideLength, hexH)
         << QPointF(1.5 * sideLength, hexH)
         << QPointF(2.0 * sideLength, 0)
         << QPointF(1.5 * sideLength, -hexH)
         << QPointF(0.5 * sideLength, -hexH);

    poly.translate(pos);

    painter.drawPolygon(poly);
}
