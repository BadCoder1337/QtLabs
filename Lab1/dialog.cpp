#include "dialog.h"
#include "ui_dialog.h"
#include <QtDebug>

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


void Dialog::on_pushButton_clicked()
{
    auto a = ui->doubleSpinBoxA->value();
    auto b = ui->doubleSpinBoxB->value();
    auto c = ui->doubleSpinBoxC->value();
    qDebug() <<  a << endl << b << endl << c << endl;
//              << QString::number(a)+"x^2+"+QString::number(b)+"x+"+QString::number(c)+"=0" << endl;
// ui->labelEquation->setText(QString::number(a)+"x^2+"+QString::number(b)+"x+"+QString::number(c)+"=0");
}
