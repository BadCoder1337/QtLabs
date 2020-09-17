#include "bignum.h"
#include <QDebug>
BigNum::BigNum(QString str) // основной конструктор
{
    /* поскольку операции сложения и вычитания выполняются справа налево, запишем числа, соответствующие цифрам в массив в обратном порядке: */
    for (int i = 0; i<str.length(); i++)
    {
        if (str[i] == '.') {
            dotOffset = i;
            continue;
        }
        if (str[i] == '-') {
            negative = true;
            continue;
        }
        qint8 item = str[i].toLatin1() - '0';
        vec.push_front(item);
    }
}
 // преобразование массива в строку:
QString BigNum::toString()
{
    QString tmp;
    int i = 0;
    // Итератор в стиле STL:
    QVector<qint8>::iterator it = vec.end(); // идем от конца вектора
    while (it != vec.begin()) // к началу
    {
        if (i == dotOffset) tmp+= '.';
        i++;
        qint8 item = *--it; // один элемент массива
        tmp += QChar(item+'0'); // создаем цифру из числа и добавляем к строке
    }
    if (tmp[0] == '.') tmp = '0' + tmp;
    return tmp;
}
 // Операторная функция сложения:
BigNum BigNum::operator +(BigNum b)
{
  BigNum sum;
  // Итераторы в стиле Java:
  QVectorIterator<qint8> it1(vec); // итератор для левого операнда
  QVectorIterator<qint8> it2(b.vec); // для правого операнда
  qint8 digit = 0; // число в текущем разряде результата
  qint8 carry = 0; // перенос в следующий разряд
  while (it1.hasNext()|| it2.hasNext())
    // пока хотя бы одно из чисел не закончено
  {
       // цифры в текущем разряде:
qint8 a = it1.hasNext()? it1.next() : 0;
     // если число закончилось, то складывается ноль
       qint8 b = it2.hasNext()? it2.next() : 0;
       digit = a + b+ carry ;  // сложение в текущем разряде
       carry = digit / 10; // перенос в следующий разряд
       digit %= 10; // цифра в текущем разряде
        qDebug() << carry << " " << digit;
       sum.vec.push_back(digit); // добавляем цифру к сумме
    }
  if (carry) sum.vec.push_back(carry);
// если перенос не равен нулю, добавляем его к результату
  return sum;
}

// Операторная функция вычитания
BigNum BigNum::operator -(BigNum b)
{
  BigNum difference; // разность

  int fracLength = qMax(vec.length() - dotOffset, b.vec.length() - b.dotOffset);
  while (vec.length() - dotOffset < fracLength) vec.push_front(0);
  while (b.vec.length() - b.dotOffset < fracLength) b.vec.push_front(0);
  // Итераторы в стиле Java:
  QVectorIterator<qint8> it1(vec); // итератор для уменьшаемого
  QVectorIterator<qint8> it2(b.vec); // для вычитаемого
  qint8 digit = 0; // цифра в текущем разряде
  qint8 borrow = 0; // заем из старшего разряда
  while (it1.hasNext()) // пока уменьшаемое не закончилось
  {
        qint8 a = it1.next(); // цифра уменьшаемого
if (borrow) a--; // Если занимали, то число в текущем разряде уменьшаем
        qint8 b = it2.hasNext()? it2.next() : 0; // цифра вычитаемого
/* если значение вычитаемого больше уменьшаемого, добавляем в текущем разряде 10 единиц к уменьшаемому: */
       borrow = (b > a) ? 10 : 0;
        a += borrow;
        digit = a - b; // вычитаем
        qDebug() << borrow << " " << digit;
        difference.vec.push_back(digit);
 // добавляем число в очередном разряде к результату
  }

  // Итератор в стиле STL:
 // удалим незначащие нули результата:
  QVector<qint8>::iterator it = difference.vec.end();
  qDebug() <<"difference:";
  while (*--it == 0 )
  {
      difference.vec.pop_back(); // удаляем последний элемент вектора:
      if (it == difference.vec.begin())break;
  }

  difference.dotOffset = difference.vec.length() - fracLength;

  QVectorIterator<qint8> diff(difference.vec);
  while (diff.hasNext() && diff.next() == 0)
  {
      difference.vec.pop_front();
  }

  return difference;
}

bool BigNum::operator >(BigNum b) {
    int fracLength = qMax(vec.length() - dotOffset, b.vec.length() - b.dotOffset);
    while (vec.length() - dotOffset < fracLength) vec.push_front(0);
    while (b.vec.length() - b.dotOffset < fracLength) b.vec.push_front(0);
    // Итераторы в стиле Java:
    QVectorIterator<qint8> it1(vec); // итератор для уменьшаемого
    QVectorIterator<qint8> it2(b.vec); // для вычитаемого
    it1.toBack(); it2.toBack();
    if (vec.length() > b.vec.length()) return true;
    if (vec.length() < b.vec.length()) return false;
    while (it1.hasPrevious()) {
        qint8 a = it1.previous() , b = it2.previous();
        qDebug() << "a: " << a << " b: " <<  b;
        if (a > b) return true;
        if (a < b) return false;
    }
    return false;
}
