#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

/*
    12. Два нечетных простых числа, разность которых равна 2, называются близнецами.
    Написать программу, которая находит все числа-близнецы на заданном отрезке и выводит их на экран.
    Проверку "простое – не простое" оформить в виде функции.
*/


bool Dialog::isPrime(int x) {
    double t = sqrt(x);
    for (int i = 2; i <=t; i++)
        if (x % i == 0)
            return false;
    return true;
}


void Dialog::on_pushButton_clicked()
{
    int
        from = ui->sbFrom->value(),
        to = ui->sbTo->value(),
        width = log10(to) + 1;

    ui->memo->clear();

    for (int i = from; i < to; i++) {
        if (isPrime(i) && isPrime(i + 2))
            ui->memo->appendPlainText(
                QString::number(i).rightJustified(width, '0')
                + " - "
                + QString::number(i + 2).rightJustified(width, '0')
            );
    }
}
