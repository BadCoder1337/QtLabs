#include "circle.h"

Circle::Circle()
{
    p = QPoint(0,0);
    r = 0;
    color = Qt::darkYellow;
}
Circle::Circle(QPoint &_p, int _r, QColor col = Qt::darkCyan)
{
    p = _p;
    r = _r;
    color = col;
}
Circle::Circle(const Circle & circle)
{
    p = circle.p;
    r = circle.r;
    color = circle.color;
}
Circle& Circle::operator =(const Circle & circle)
{
    p = circle.p;
    r = circle.r;
    color = circle.color;
    return *this;
}
