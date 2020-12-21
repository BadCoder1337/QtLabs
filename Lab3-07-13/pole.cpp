#include "pole.h"
#include <qmath.h>
Pole::Pole(QWidget *parent) :
    QWidget(parent)
{
}

void Pole::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int hp = h/2; // половина высоты рабочей области
    if (b > a)
    {
        k = w/(b-a); // вычисляем масштабный коэффициент
    // Определяем, где должно быть начало координат:
      x0 = -k * a;
        y0 = hp;
        painter.translate(x0, y0); // перемещаем начало координат
// Оси:
        painter.setPen(QPen(Qt::darkCyan, 1, Qt::DashLine));
        painter.drawLine(QPoint(-x0,0), QPoint(k*b, 0));
        painter.drawLine(QPoint(0, -hp), QPoint(0, hp));
// График:
        painter.setPen(QPen(QColor(0,0,100), 1));
        painter.setRenderHint(QPainter::Antialiasing); // режим сглаживания линий
        double dx = (b-a)/w; // шаг, с которым мы будемпроходить отрезок
        double an = a; // начальная точка графика
        while (! _finite(F(an))) an += dx;
// если на левой границе функция не определена, сдвигаемся вправо
        double xe = k*an, ye= -k*F(an);
// экранные координаты начальной точки графика
        bool flag = true; // признак того, что текущая точка определена
        double y; // текущее значение функции
        QPolygonF polygon; // контейнер (массив) для точек
        polygon << QPointF(xe,ye); // записываем начальную точку
        for (double x = an+dx; x <= b + dx/2; x += dx) // проходим по отрезку [a, b]
        {
           if (_finite(y = F(x))) // если в текущей точке функция определена
           {
        //   вычисляем экранные координаты точки:
         xe = k*x;
             ye = -k*y;
             if (fabs(ye)  < 2*hp)  // если точка не слишком далеко отстоит от оси X
                    flag = true; // будем ее рисовать
             else flag = false; // иначе сделаем разрыв
            }
           else flag = false; // функция не определена, делаем разрыв
           if (flag) // если точку нужно отобразить на графике
                    polygon << QPointF(xe,ye); // добавляем ее в массив
           else
           if ( ! polygon.isEmpty()) // если массив не пустой
           {
                    painter.drawPolyline(polygon); // рисуем ломаную линию
                    polygon.clear(); // очищаем контейнер
            }
        } // end for
        painter.drawPolyline(polygon); // рисуем оставшуюся часть графика
        // масштабирование оси X:
 /* первый способ: разделим всю ось X на 20 частей и для каждой точки деления сделаем надпись */
        QFont font("Serif", 8); // шрифт для надписей
        painter.setFont(font);
        QRect rect; // прямоугольник, в котором будет располагаться надпись
        dx = (b-a)/20; // шаг прохождения по оси X
        for (double x = a; x <= b + dx/2; x += dx) // проходим отрезок [a, b]
        {
            if (fabs(x) < 1e-10) continue;
// ноль не подписываем, подпишем его на оси Y
            xe = k*x; // экранная ордината
            painter.setPen(QColor(100,0,0));
            painter.drawEllipse(QPoint(xe, 0), 1,1 ); // отмечаем точки
            QString legend(QString::number(x, 'g', 3));
// надпись представляет значение X в точке деления
             // сделаем надписи, идущие снизу-вверх:
        painter.save(); // сохраняем текущую систему координат
            painter.translate(xe, 0);
// переводим начало координат в точку, которую нужно подписать
            painter.rotate(-90.);
 // поворачиваем систему координат вокруг начальной точки
 /* задаем прямоугольники так, чтобы надписи на границах окна были видны и слева и справа: */
            if (x>0) rect = QRect( QPoint(-50,-10), QPoint(-3,0));
            else rect = QRect( QPoint(-50,0), QPoint(-3,10));
            painter.setPen(QColor(0,50,50));
            painter.drawText(rect, Qt::AlignRight|Qt::AlignBottom, legend);
// делаем надпись в прямоугольнике
            painter.restore(); // восстанавливаем систему координат
        }
    // Масштабирование оси Y:
 // второй способ: пройдем по оси и сделаем отметки через каждые 50 точек на экране:
        for (ye = 0; ye <= hp; ye += 50) // нижняя половина оси Y
        {
            painter.setPen(QColor(100,0,0));
            painter.drawEllipse(QPoint(0, ye), 1,1 );
            QString legend(QString::number(-ye/k,'g', 3));
            painter.save();
            painter.translate(0, ye);
            rect = QRect( QPoint(-50,-15), QPoint(-3,0));
            painter.setPen(QColor(0,50,50));
            painter.drawText(rect, Qt::AlignRight|Qt::AlignTop, legend);
            painter.restore();
        }
        for (ye = -50; ye >= -hp; ye -= 50) // верхняя половина оси Y
        {
            painter.setPen(QColor(100,0,0));
            painter.drawEllipse(QPoint(0, ye), 1,1 );
            QString legend(QString::number(-ye/k,'g', 3));
            painter.save();
            painter.translate(0, ye);
            rect = QRect( QPoint(-50,0), QPoint(-3,15));
            painter.setPen(QColor(0,50,50));
            painter.drawText(rect, Qt::AlignRight|Qt::AlignTop, legend);
            painter.restore();
        }
    }
}
double Pole::F(double x) // вид функции, график которой нужно построить:
{
    return tan(x);
}
