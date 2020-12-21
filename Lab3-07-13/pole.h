#ifndef POLE_H
#define POLE_H
#include <QtGui>
#include <QWidget>
class Pole : public QWidget
{
    Q_OBJECT
public:
    explicit Pole(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    double a, b; // диапазон построения графика
    double w, h; // ширина и высота поля
    double x0, y0; // координаты центра
    double k;// масштабный коэффициент
    double F(double); // определяет вид функции
signals:
public slots:
};
#endif // POLE_H
