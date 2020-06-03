#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void draw(QPoint pos);
    void refresh(int count = 0);
    void drawText(QString text);

    QPixmap *buffer;

private:
    Ui::MainWindow *ui;

    int N;
    float R;

    QLabel *label1, *label2; 

    QString str;
    bool flag;

    bool drawHex(QPainter &pRef, QPointF pos, float sideLength, float angle);
    QPolygonF windowPoly;

};
#endif // MAINWINDOW_H
