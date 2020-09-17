#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "circle.h"
#include "dialog.h"
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
    Dialog* dlg;
public slots:
    void Annul();
    void Clear();
    void save();
    void open();

private slots:
    void on_actionColorDialog_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
