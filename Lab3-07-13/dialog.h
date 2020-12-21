#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
class MainWindow;
namespace Ui {
    class Dialog;
}
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(MainWindow *parent = 0);
    ~Dialog();
    MainWindow* Parent; // Указатель на родительское окно
private:
    Ui::Dialog *ui;
public slots:
    void setRange(); // Слот для кнопки "Построить"
private slots:
    void on_pushButton_2_clicked();
};
#endif // DIALOG_H
