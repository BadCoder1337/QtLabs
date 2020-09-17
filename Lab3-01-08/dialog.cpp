#include "dialog.h"
#include "ui_dialog.h"
#include "bignum.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
}

Dialog::~Dialog()
{
    delete ui;
}

/*
Создать приложение, которое находит разность
двух больших чисел , у ко­то­рых может быть
дробная часть,  используя контейнеры и итераторы.
*/

void Dialog::on_pushButton_clicked()
{
    auto str1 = ui->lineEdit->text(),
         str2 = ui->lineEdit_2->text();

    if (str1.indexOf('.') == -1) str1 += ".0";
    if (str2.indexOf('.') == -1) str2 += ".0";

    QStringList list1 = str1.split('.');
    QStringList list2 = str2.split('.');

    auto l = qMax(list1[1].length(), list2[1].length());
    str1 = list1[0] + '.' + list1[1].leftJustified(l, '0');
    str2 = list2[0] + '.' + list2[1].leftJustified(l, '0');

    BigNum a(str1), b(str2);

    if (b > a) {
        ui->lineEdit_3->setText('-' + (b - a).toString());
    } else {
        ui->lineEdit_3->setText((a - b).toString());
    }
}
