#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

#include <QColorDialog>

Dialog::Dialog(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Parent = parent;
    initValues();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::initValues()
{
    auto c = Parent->color;
    ui->spinBoxR->setValue(c.red());
    ui->spinBoxG->setValue(c.green());
    ui->spinBoxB->setValue(c.blue());
}

void Dialog::setColor()
{
    Parent->color = QColor(ui->spinBoxR->value(), ui->spinBoxG->value(), ui->spinBoxB->value());
}

void Dialog::on_spinBoxR_valueChanged(int arg1) { setColor(); }

void Dialog::on_spinBoxG_valueChanged(int arg1) { setColor(); }

void Dialog::on_spinBoxB_valueChanged(int arg1) { setColor(); }

void Dialog::on_paletteButton_clicked()
{
    Parent->color = QColorDialog::getColor();
    initValues();
}
