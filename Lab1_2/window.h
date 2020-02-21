#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void on_dsbA1_valueChanged();
    void on_dsbA2_valueChanged();
    void on_dsbB1_valueChanged();
    void on_dsbB2_valueChanged();
    void on_dsbC1_valueChanged();
    void on_dsbC2_valueChanged();

private:
    Ui::Window *ui;
    void calculateResult();
    void setResult(QString x, QString y);
};
#endif // WINDOW_H
