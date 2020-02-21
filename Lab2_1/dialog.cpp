#include "dialog.h"
#include "ui_dialog.h"
#include "QtDebug"
#include "math.h"

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

double Dialog::F(double x) {
    double t = 1/x;
    return cos(2*t)-2*sin(t)+t;
}

double Dialog::calculate(double a, double b, double e) {
    double x = 0;
    int i = 0;

    do {
        double
            Fa = F(a),
            Fb = F(a);
        if (Fa == 0) { return a; }
        if (Fb == 0) { return b; }
        x = (a + b) / 2;
        double Fx = F(x);
        copysign(1, Fa) != copysign(1, Fx)
            ? b = x
            : a = x;
        qDebug() << i << ": a=" << a << " b=" << b << " x=" << x;
        qDebug() << i << ": Fa=" << Fa << " Fb=" << Fb << " Fx=" << Fx << endl;
        i++;
    } while (b - a > e);

    return x;
}

void Dialog::on_pushButton_clicked()
{
    double
        a = ui->dsbFrom->value(),
        b = ui->dsbTo->value(),
        e = ui->dsbE->value(),
        root = calculate(a, b, e),
        Fx = F(root);

    ui->resultEdit->setText("x0=" + QString::number(root) + ", F(x0)=" + QString::number(Fx, 'f', abs(round(log10(e))) + 1));

}
