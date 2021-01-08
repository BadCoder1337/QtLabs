#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPainter>
#include <QPen>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    int margin = 20,
        extH = ui->menubar->height(),
        H = height() - extH,
        W = width();

    painter.translate(0, extH);

    painter.setPen(QPen(Qt::darkCyan, 1, Qt::DashLine));
    painter.drawLine(QPoint(0, 0), QPoint(0, H));

//    painter.drawLine(QPoint(0, margin), QPoint(W, margin));
//    painter.drawLine(QPoint(0, H - margin), QPoint(W, H - margin));

    if (!points.size()) return;

    auto [min, max] = std::minmax_element(points.begin(), points.end());

    double
        range = *max - *min,
        avH = (H - margin * 2),
        k = avH / range,
        dx = W / (points.size() - 1),
        x0 = 0,
        y0 = margin - (avH - *max * k),
        xp = 0,
        p;

    painter.translate(x0, y0);

    painter.setPen(QPen(QColor(0,0,100), 1));
    painter.setRenderHint(QPainter::Antialiasing);

    QPolygonF polygon; // контейнер (массив) для точек
    foreach (p, points) {
        polygon << QPointF(xp, (range - p) * k);
        xp += dx;
    }

    if ( ! polygon.isEmpty()) { // если массив не пустой
        painter.drawPolyline(polygon); // рисуем ломаную линию
        polygon.clear(); // очищаем контейнер
    }

    painter.resetTransform();
    painter.translate(0, extH + margin - (avH - *max * k));
    double step = range / 10;
    QFont font("Serif", 8); // шрифт для надписей
    painter.setFont(font);
    QRect rect; // прямоугольник, в котором будет располагаться надпись

    for (int i = 10; i >= 0; i--) {
        double j = *max - i * step,
               y = (range - j) * k;
        painter.setPen(QColor(100,0,0));
        painter.drawLine(QPoint(0, y), QPoint(5, y));
        QString legend(QString::number(j, 'g', 3));
        painter.save();
        painter.translate(0, y);
        rect = QRect(QPoint(3,-15), QPoint(50,0));
        painter.setPen(QColor(0,50,50));
        painter.drawText(rect, Qt::AlignLeft|Qt::AlignTop, legend);
        painter.restore();
    }
    // Масштабирование оси Y:
 // второй способ: пройдем по оси и сделаем отметки через каждые 50 точек на экране:
//        for (ye = 0; ye <= hp; ye += 50) // нижняя половина оси Y
//        {
//            painter.setPen(QColor(100,0,0));
//            painter.drawEllipse(QPoint(0, ye), 1,1 );
//            QString legend(QString::number(-ye/k,'g', 3));
//            painter.save();
//            painter.translate(0, ye);
//            rect = QRect( QPoint(-50,-15), QPoint(-3,0));
//            painter.setPen(QColor(0,50,50));
//            painter.drawText(rect, Qt::AlignRight|Qt::AlignTop, legend);
//            painter.restore();
//        }
//        for (ye = -50; ye >= -hp; ye -= 50) // верхняя половина оси Y
//        {
//            painter.setPen(QColor(100,0,0));
//            painter.drawEllipse(QPoint(0, ye), 1,1 );
//            QString legend(QString::number(-ye/k,'g', 3));
//            painter.save();
//            painter.translate(0, ye);
//            rect = QRect( QPoint(-50,0), QPoint(-3,15));
//            painter.setPen(QColor(0,50,50));
//            painter.drawText(rect, Qt::AlignRight|Qt::AlignTop, legend);
//            painter.restore();
//        }

}
void MainWindow::on_actionOpen_triggered()
{
    points.clear();
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл");
    if (!fileName.isEmpty()) {
        file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);

        while (!in.atEnd()) {
            float p;
            in >> p;
            points.append(p);
        }

        file.close();
        qDebug() << points;
    }
}
