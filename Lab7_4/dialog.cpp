#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Parent = parent;
    ui->spinBoxR->setValue(Parent->color.red());
    ui->spinBoxG->setValue(Parent->color.green());
    ui->spinBoxB->setValue(Parent->color.blue());
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_spinBoxR_valueChanged(int arg1)
{
    Parent->color = QColor(arg1, ui->spinBoxG->value(), ui->spinBoxB->value());
}

void Dialog::on_spinBoxG_valueChanged(int arg1)
{
    Parent->color = QColor(ui->spinBoxR->value(), arg1, ui->spinBoxB->value());
}

void Dialog::on_spinBoxB_valueChanged(int arg1)
{
    Parent->color = QColor(ui->spinBoxR->value(), ui->spinBoxG->value(), arg1);
}
