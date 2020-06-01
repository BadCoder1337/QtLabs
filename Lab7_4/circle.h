#ifndef CIRCLE_H
#define CIRCLE_H
#include <QtGui>
class Circle
{
public:
    QPoint p;
    int r;
    QColor color;
    Circle();
    Circle(QPoint& _p, int _r, QColor col);
    Circle(const Circle& );
    Circle& operator = (const Circle& );
};
#endif // CIRCLE_H
