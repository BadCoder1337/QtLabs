#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class MainWindow;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(MainWindow *parent = 0);
    ~Dialog();
    MainWindow* Parent;
    void initValues();
    void setColor();

private slots:
    void on_spinBoxB_valueChanged(int arg1);

    void on_spinBoxG_valueChanged(int arg1);

    void on_spinBoxR_valueChanged(int arg1);

    void on_paletteButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
