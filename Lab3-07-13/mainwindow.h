#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QScrollArea>
#include "dialog.h"
#include "pole.h"
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Dialog* dlg; // указатель на диалоговое окно
    double a, b; // диапазон построения графика
    QScrollArea* scroll; // указатель на область прокрутки
    Pole* pole; // указатель на рабочее поле
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
private slots:
    void on_actionD_triggered(); // слот для команды "Диапазон"
};
#endif // MAINWINDOW_H
