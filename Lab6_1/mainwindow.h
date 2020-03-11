#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

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
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void draw(QPoint pos);
    void refresh(float R, int count);

    QPixmap *buffer;

private:
    Ui::MainWindow *ui;

    void drawHex(QPainter &pRef, QPointF pos, float sideLength, float angle);

};
#endif // MAINWINDOW_H