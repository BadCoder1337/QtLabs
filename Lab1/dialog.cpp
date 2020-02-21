#include "dialog.h"
#include "ui_dialog.h"
#include <QtDebug>
#include <QLocale>
#include <cmath>

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

void Dialog::refreshLabel() {
    auto a = ui->doubleSpinBoxA->value();
    auto b = ui->doubleSpinBoxB->value();
    auto c = ui->doubleSpinBoxC->value();
    ui->labelEquation->setText(
        QString::number(a)
        + "x^2"
        + (b >= 0 ? "+" : "")
        + QString::number(b)
        + "x"
        + (c >= 0 ? "+" : "")
        + QString::number(c)
        + "=0"
    );
}

void Dialog::on_calcButton_clicked()
{
    auto a = ui->doubleSpinBoxA->value();
    auto b = ui->doubleSpinBoxB->value();
    auto c = ui->doubleSpinBoxC->value();
    qDebug() << a << endl << b << endl << c << endl;

    refreshLabel();

    double x1 = 0.0, x2 = 0.0;

    if ( a != 0 ) {
        double d = b*b - 4*a*c;
        if ( d > 0 ) {
          x1 = (-b + sqrt(d)) / (2*a);
          x2 = (-b - sqrt(d)) / (2*a);
          ui->labelRoots->setText("Корни: x1=" + QString::number(x1) + ", x2=" + QString::number(x2));
        } else if ( d == 0 ) {
          x1=(-b) / (2*a);
          ui->labelRoots->setText("Корни: x=" + QString::number(x1));
        } else
          ui->labelRoots->setText("Корни: нет");
    } else {
        if (b) {
            x1 = -c / b;
            ui->labelRoots->setText("Корни: x=" + QString::number(x1));
        } else if (!c)
            ui->labelRoots->setText("Корни: любое число");
        else
            ui->labelRoots->setText("Корни: нет");
    }
}

void Dialog::on_doubleSpinBoxA_valueChanged() { refreshLabel(); }
void Dialog::on_doubleSpinBoxB_valueChanged() { refreshLabel(); }
void Dialog::on_doubleSpinBoxC_valueChanged() { refreshLabel(); }
