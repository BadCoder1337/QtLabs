#include "mainwindow.h++"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString name = QFileDialog::getOpenFileName(this, "Открыть","data.txt", QString("Текстовые файлы(*.txt);;Все файлы(*)"));
    QFile file(name); // объявляем объект для работы с файлом
    if (!file.open(QIODevice::ReadOnly)) return; // открываем файл
    QTextStream input(&file);
    rowCount = 0;
    colCount = 0;

    input >> rowCount >> colCount;// считываем строку из файла

    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(colCount);
    ui->tableWidget2->setRowCount(rowCount);
    ui->tableWidget2->setColumnCount(colCount);

    for (int i = 0; i < rowCount; i++) {
        QVector<int> row;
        for (int j = 0; j < colCount; j++) {
           int k;
           input >> k;
           row.append(k);
        }
        matrix.append(row);
    }

    fillTable(ui->tableWidget, matrix);

    qDebug() << rowCount << colCount << matrix;

    auto matrixCopy = matrix;

    for (int i = 0; i < rowCount; i++) {
        int min = matrixCopy[i][0];
        for (int j = 0; j < colCount; j++) {
            auto current = matrixCopy[i][j];
            min = current < min ? current : min;
        }
        for (int k = 0; k < colCount; k++) {
            matrixCopy[i][k] -= min;
        }
        qDebug() << min;
    }


    fillTable(ui->tableWidget2, matrixCopy);

    file.close();
}

void MainWindow::fillTable(QTableWidget *tableRef, QVector<QVector<int> > &matrixRef)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++) {
           QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrixRef[i][j]));
           tableRef->setItem(i, j, item);
        }

}

void MainWindow::on_actionExit_triggered()
{
    close();
}
