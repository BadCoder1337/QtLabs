#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getTrigger() {
    return ui->lineEdit->text();
}
