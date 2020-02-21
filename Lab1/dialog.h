#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_calcButton_clicked();

    void on_doubleSpinBoxA_valueChanged();

    void on_doubleSpinBoxB_valueChanged();

    void on_doubleSpinBoxC_valueChanged();

private:
    void refreshLabel();
    Ui::Dialog *ui;
};
#endif // DIALOG_H
