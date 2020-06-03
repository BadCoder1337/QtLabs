#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtGui"
#include <QLabel>
#include <QColor>

/*
1.	Зарисовать окно «пчелиными сотами» (правильными шестиугольниками).
Процесс зарисовки начинается при нажатии одной из кнопок мыши. 
Размер стороны шестиугольника - 1/n – ая  часть длины меньшей стороны окна.
Число разбиений N ввести с клавиатуры.
Обеспечить контроль правильности ввода и возможность стирания символов, которые введены ошибочно.
В строке состояния вывести длину стороны шестиугольника и общее количество сот.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    flag = false;
    label1 = new QLabel(ui->statusbar);
    label1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label2 = new QLabel(ui->statusbar);
    label2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    QPalette pal = ui->statusbar->palette();
    pal.setColor(QPalette::Background, QColor(215,220,210));
    pal.setColor(QPalette::Foreground, QColor(0,50,0));
    ui->statusbar->setPalette(pal);
    ui->statusbar->setAutoFillBackground(true);
    ui->statusbar->setSizeGripEnabled(false);
    ui->statusbar->addPermanentWidget(label1);
    ui->statusbar->addPermanentWidget(label2);

    buffer = nullptr;
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

    buffer = new QPixmap(width(), height());

    buffer->fill(Qt::white);

    refresh();
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
                    R = qMin(height(), width()) / N;
                    flag = true;
                    buffer->fill(Qt::white);
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

    int rows = int(height / dy) + 2,
        columns = int(width / dx) + 2,
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
    label1->setText(QString("Длина стороны: %1").arg(N < 3 ? str : QString::number(R)));
    label2->setText(QString("Количество фигур: %1").arg(count));

    if (!flag) {
        buffer->fill(Qt::white);
        drawText("Задайте N: " + str);
    } else if (count == 0) {
        drawText("Нажмите мышью.");
    }

    repaint();
}

void MainWindow::drawText(QString text) {
    QPainter painter(buffer);

    if (!painter.isActive()) return;

        painter.setRenderHint(QPainter::Antialiasing);

        auto font = painter.font();

        font.setPointSize(font.pointSize() * 2);
        painter.setFont(font);

        painter.setPen(QPen(QColor(100, 0, 100), 3));
    painter.drawText(10, 30, text);
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
