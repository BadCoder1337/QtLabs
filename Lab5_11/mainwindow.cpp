#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QTextCodec"
#include "QTextStream"
#include "QDebug"

/*
Написать программу с окном типа QMainWindow, которое считывает текст из файла и выводит его на экран,
затем выводит на экран те слова, которые начи­наются на заданную последовательность символов.
Имя файла должно считываться с помощью специального диалогового окна для открытия файлов.
Символы считывать с помощью вспомогательного диалогового окна, которое выводится на экран при нажатии на кнопку на панели инструментов.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Открыть файл",
        QString(),
        QString("Текстовые файлы (*.txt);;Все файлы (*.*)")
    );
    if (!fileName.isEmpty()) {
            file.setFileName(fileName);
            file.open(QIODevice::ReadOnly|QIODevice::Text);
            while (!file.atEnd())
            {
                qDebug() << file.readLine();
            }
    }
}

void MainWindow::on_pushButton_clicked()
{

}
