#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
Dialog::Dialog(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Parent = parent; // Запоминаем указатель на родительское окно
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(setRange()));
    // соединяем сигнал от кнопки "Построить" со слотом setRange()
}
Dialog::~Dialog()
{
    delete ui;
}
void Dialog::setRange() // слот для кнопки "Построить"
{
 // передаем родительскому окну диапазон значений аргументов:
    Parent->a = ui->lineEdit->text().toDouble();
    Parent->b = ui->lineEdit_2->text().toDouble();
    Parent->update(); // перерисовываем график
}

void Dialog::on_pushButton_2_clicked()
{
    close();
}
