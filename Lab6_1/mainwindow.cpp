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

//    this->setWindowFlags(Qt::WindowStaysOnTopHint);
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

    QPainter painter(buffer);
    auto &pRef = painter;

    painter.setRenderHint(QPainter::Antialiasing);

    int height = this->height(),
        width = this->width();

    float R = qMin(height, width) / ui->spinBox->value(),
          H = sqrt3by2 * R,
          dx = R * sqrt(3),
          dy = R * 3 / 2;

    int rows = int(2 * height / (3 * R)) + 2,
        columns = int(width / (R * sqrt(3))) + 2,
        count = 0;

    auto center = QPointF(H, 0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((i + j) % 2 == 0)
                painter.setBrush(QColor("#FE6E0E"));
            else
                painter.setBrush(QColor("#FB9300"));

            drawHex(pRef, center, R, 30);

            count++;
            refresh(R, count);
            QThread::msleep(100);

            center += QPointF(dx, 0);
        }
        center += QPointF(0, dy);
        if (i % 2)
            center.setX(H);
        else
            center.setX(0);
    }
}

void MainWindow::refresh(float R, int count) {
    this->setWindowTitle(QString("HoneyCombs L:%1 C:%2").arg(R).arg(count));
    this->repaint();
}

void MainWindow::drawHex(QPainter &painter, QPointF pos, float hexL, float angle = 30) {
    QPolygonF poly;

    for (int i = 0; i < 6; ++i) {
        poly << QPointF(hexL * qCos(qDegreesToRadians(angle)), hexL * qSin(qDegreesToRadians(angle)));
        angle += 60;
    }

    poly.translate(pos);

    painter.drawPolygon(poly);
}
