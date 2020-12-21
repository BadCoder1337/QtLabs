#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtGui>
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPixmap pixmap; // используем для быстрого вывода изображения на экран
    void paintEvent(QPaintEvent *);
    QTimer timer; // будет подавать сигнал об изменении изображения в окне
    QPoint p;
 // определяет верхний левый угол прямоугольника, содержащего окружность
    int x0, y0, r; // параметры окружности
    int w, h; //  ширина и высота окна (рабочей области)
    float angle, step;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
