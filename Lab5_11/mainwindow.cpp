#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QTextCodec"
#include "QTextStream"
#include "QDebug"
#include "dialog.h"

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
    fileName = QFileDialog::getOpenFileName(
        this,
        "Открыть файл",
        QString(),
        QString("Текстовые файлы (*.txt);;Все файлы (*.*)")
    );
    trigger = "";
    processText();
}

void MainWindow::on_pushButton_clicked()
{
    Dialog dlg;
    dlg.move(ui->menu->parentWidget()->mapToGlobal(ui->menu->pos() + QPoint(10, 10)));
    if (dlg.exec() == QDialog::Accepted) {
        trigger = dlg.getTrigger();
        processText();
    }
}

void MainWindow::processText() {
    if (!fileName.isEmpty()) {
            file.setFileName(fileName);
            file.open(QIODevice::ReadOnly|QIODevice::Text);
            ui->listWidget->clear();
            while (!file.atEnd())
            {
                QString line = file.readLine();
                qDebug() << line;
                if (line.startsWith(trigger)) {
                    ui->listWidget->addItem(line);
                };
            }
    }
}
