#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QFile file;
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSet_triggered();

private:
    Ui::MainWindow *ui;

    QString trigger;
    QString fileName;

    void processText();

};
#endif // MAINWINDOW_H
