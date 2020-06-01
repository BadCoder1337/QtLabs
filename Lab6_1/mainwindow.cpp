#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtGui"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buffer = nullptr;
    valInputBuff = nullptr;
    resizeEvent(nullptr);

    N = 2;
    str = "не задано";
    flag = false;

    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

static const float sqrt3by2 = sqrt(3) / 2;

void MainWindow::resizeEvent(QResizeEvent *event) {
    delete buffer;
    delete valInputBuff;

    buffer = new QPixmap(this->width(), this->height());
    valInputBuff = new QPixmap(this->width(), this->height());

    buffer->fill(Qt::white);

    refresh();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (flag) {
        painter.drawPixmap(0, 0, *buffer);
    } else {
        painter.drawPixmap(0, 0, *valInputBuff);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << event->pos();
        draw(event->pos());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
        QRegExp reg("[0-9]{1,2}");
        QRegExpValidator* validator = new QRegExpValidator(reg, this);
        int pos = 0; // эта переменная нужна для вызова валидатора
        if (flag) {
            str.clear(); // начинаем ввод сначала
            flag = false;
        } else {
            if (str == "не задано") str = "";
            switch (event->key()) {
                case Qt::Key_Return: {
                    N = str.toInt();
                    if (N < 2) {
                        N = 2;
                        str.setNum(N);
                    };
                    R = qMin(this->height(), this->width()) / N;
                    flag = true;
                } break;

                case Qt::Key_Backspace: {
                    str.chop(1);
                } break;

                default: {
                    QString ch = event->text();
                    QString tmp = str + ch;
                    if (validator->validate(tmp, pos))
                        str += ch;
                }
            }
        }

        refresh();
};

void MainWindow::draw(QPoint pos) {

    if (!flag) return;

    buffer->fill(Qt::white);

    QPainter painter(buffer);
    auto &pRef = painter;

    painter.setRenderHint(QPainter::Antialiasing);

    int height = this->height(),
        width = this->width();

    float H = sqrt3by2 * R,
          dx = R * sqrt(3),
          dy = R * 3 / 2;

    int rows = int(2 * height / (3 * R)) + 2,
        columns = int(width / (R * sqrt(3))) + 2,
        count = 0;

    auto center = QPointF(H, 0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            switch (rand() % 4) {
                case 0: painter.setBrush(QColor("#D04E02")); break;
                case 1: painter.setBrush(QColor("#FE6E0E")); break;
                case 2: painter.setBrush(QColor("#FB9300")); break;
                case 3: painter.setBrush(QColor("#FBCE11")); break;
            }
            drawHex(pRef, center, R, 30);

            count++;
            refresh(count);
            QThread::msleep(200 / N);

            center += QPointF(dx, 0);
        }
        center += QPointF(0, dy);
        if (i % 2)
            center.setX(H);
        else
            center.setX(0);
    }
}

void MainWindow::refresh(int count) {
    this->setWindowTitle(QString("HoneyCombs N:%1 R:%2 C:%3 %4").arg(str).arg(R).arg(count).arg(flag ? "👌" : ""));

    if (!flag) {
        valInputBuff->fill(Qt::white);
        buffer->fill(Qt::white);

        QPainter painter(valInputBuff);

        painter.setRenderHint(QPainter::Antialiasing);

        auto font = painter.font();

        font.setPointSize(font.pointSize() * 2);
        painter.setFont(font);

        painter.setPen(QPen(QColor(100, 0, 100), 3));
        painter.drawText(10, 30, "Задайте N: " + str);

    }

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
