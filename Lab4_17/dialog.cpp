#include "dialog.h"
#include "ui_dialog.h"

QRegularExpression regex("\\b\\d+\\w*");

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


void Dialog::on_plainTextEdit_textChanged()
{
    ui->listWidget->clear();
    auto str = ui->plainTextEdit->toPlainText();
    auto iter = regex.globalMatch(str);
    QStringList matches;
    while (iter.hasNext()) {
        auto match = iter.next();
        if (match.hasMatch()) matches << match.captured(0);
    }
    ui->listWidget->addItems(matches);
}
