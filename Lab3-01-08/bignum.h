#ifndef BIGNUM_H
#define BIGNUM_H
#include <QtCore>  // обеспечивает работу с контейнерами
class BigNum
{
    QVector<qint8> vec; /* поскольку нам нужно хранить цифры в массиве, достаточно самого короткого типа элементов */
public:
    BigNum(){};
    BigNum(QString);
    QString toString();
// эта функция будет выполнять преобразование массива цифр в строку
    BigNum operator +(BigNum);
    BigNum operator -(BigNum);
    bool operator >(BigNum);

    int dotOffset;
    bool negative;
};
#endif // BIGNUM_H
