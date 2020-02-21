#include "window.h"
#include "ui_window.h"
#include "QtDebug"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

void Window::calculateResult() {
    double
        a1 = ui->dsbA1->value(),
        a2 = ui->dsbA2->value(),
        b1 = ui->dsbB1->value(),
        b2 = ui->dsbB2->value(),
        c1 = ui->dsbC1->value(),
        c2 = ui->dsbC2->value(),
        d, dx, dy, x=0, y=0;

    d = a1*b2 - a2*b1;
    dx = c1*b2 - c2*b1;
    dy = a1*c2 - a2*c1;

    if (d!=0){
        x = dx/d;
        y = dy/d;

        setResult(QString::number(x), QString::number(y));
    } else if (dx == 0 && dy == 0 && !(
        a1 == 0 && a2 == 0
        && b1 == 0 && b2 == 0
        && (c1 != 0 || c2 != 0)
    )) {
        setResult("(-∞, +∞)", "(-∞, +∞)");
    } else {
        setResult("нет", "нет");
    }
}

void Window::setResult(QString x, QString y) {
    ui->resultX->setText(x);
    ui->resultY->setText(y);
}

void Window::on_dsbA1_valueChanged() { calculateResult(); }
void Window::on_dsbA2_valueChanged() { calculateResult(); }
void Window::on_dsbB1_valueChanged() { calculateResult(); }
void Window::on_dsbB2_valueChanged() { calculateResult(); }
void Window::on_dsbC1_valueChanged() { calculateResult(); }
void Window::on_dsbC2_valueChanged() { calculateResult(); }
