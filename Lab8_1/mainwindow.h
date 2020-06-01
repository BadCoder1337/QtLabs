#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#define maxR 5 // максимальное количество строк
#define maxC 7 // максимальное количество столбцов
#define HEXAGON_SIZE 20

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent* event);
    void createMatrices();
    void createNet();
    void createPolygon(int i, int j);
    void mousePressEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);

    QPolygon **Polygon;
    QRegion **Region;
    QColor Color[maxR][maxC];
    int previousRows, rows, columns;
    double w, h;
    double size, x0, y0, r;
    QBrush brush;
private:
    Ui::MainWindow *ui;
private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
};
#endif // MAINWINDOW_H
