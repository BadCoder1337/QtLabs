#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "circle.h"
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPoint p[2];
    int r;
    bool drawMode;
    QList <Circle> DrawBuffer;
    QColor color;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
public slots:
    void Annul();
    void Clear();
    void showDialog();
    void save();
    void open();
private slots:
    void on_spinBoxR_valueChanged(int arg1);

    void on_spinBoxG_valueChanged(int arg1);

    void on_spinBoxB_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
