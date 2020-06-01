#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QColorDialog"
#include "dialog.h"

QDataStream& operator <<(QDataStream& ostream, const Circle& c)
{
    ostream << c.p.x()<< c.p.y() <<  c.r << c.color ;
    return ostream;
}

QDataStream& operator >> (QDataStream& istream, Circle& c)
{
    int x, y;
    istream >> x >> y >> c.r >> c.color;
    c.p.setX(x);
    c.p.setY(y);
    return istream;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAnnul, SIGNAL(triggered()), this, SLOT(Annul()));
    connect(ui->actionClear, SIGNAL(triggered()), this, SLOT(Clear()));
    connect(ui->actionColor, SIGNAL(triggered()), this, SLOT(showDialog()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    drawMode = false;
    p[0] = p[1] = QPoint(0,0);
    r = 0;
    color = Qt::darkCyan;
    dlg = new Dialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent * e)
{
    if (e->button() ==Qt::LeftButton)
    {
        drawMode = true;
        p[0] = e->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent * e)
{
    if (drawMode)
    {
        p[1] = e->pos();
        r = sqrt(pow(p[1].x()-p[0].x(),2) + pow(p[1].y()-p[0].y(),2));

        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    drawMode = false;
    int r = sqrt(pow(p[1].x()-p[0].x(),2) + pow(p[1].y()-p[0].y(),2));
    DrawBuffer.append(Circle(p[0], r, color));
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int size = DrawBuffer.size();
    if (size) {
        QList<Circle>::const_iterator it = DrawBuffer.begin();
        do {
            Circle c = *it++;
            painter.setPen(c.color);
            painter.setBrush(c.color);
            painter.drawEllipse(c.p, c.r, c.r);
        } while (it!= DrawBuffer.end());
    }
    if (drawMode) {
        int w = width();
        int h = height()-(ui->statusbar->height());
        QPixmap pixmap(w, h);
        pixmap.fill(Qt::transparent);
        QPainter pntPixmap(&pixmap);
        pntPixmap.setRenderHint(QPainter::Antialiasing);
        pntPixmap.setPen(color);
        pntPixmap.setBrush(color);
        pntPixmap.drawEllipse(p[0],r,r);
        painter.drawPixmap(0, 0, w, h, pixmap);
    }
}

void MainWindow::showDialog()
{
    color = QColorDialog::getColor();
}

void MainWindow::Annul()
{
    DrawBuffer.removeLast();
    update();
}

void MainWindow::Clear()
{
    DrawBuffer.clear();
    update();
}

void MainWindow::open()
{
    QFile file("picture.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in>>DrawBuffer;
    update();
}

void MainWindow::save()
{
    QFile file("picture.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << DrawBuffer;
    file.close();
}

void MainWindow::on_actionColorDialog_triggered()
{
    dlg->show();
    dlg->activateWindow();
}
