#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVector<double> points;
    QFile file;
    void paintEvent(QPaintEvent *);

private slots:
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
