#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>

QVector<double> dx(3);       // производные
QVector<double> var_s(2);    // переменные у, x, ..
QVector<QVector<double>> y;   // матрица значений
double phi, b;
int phi1, b1;
int length = 8;                 // длина стержня
int t = 8;                      // время воздействия

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel;
    //Заголовки столбцов
    QStringList verticalHeader;
    verticalHeader.append("       b(i)    ");
    verticalHeader.append("      phi(i)   ");

    QStringList horizontalHeader;
    for (int i = 0; i < length; i++)
        horizontalHeader.append(" ");
    ui->table->setStyleSheet("color: rgb(0, 0, 0);");

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    QStandardItem *item;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < length; j++) {
           item = new QStandardItem("");
           model->setItem(i, j, item);
       }

    ui->table->setModel(model);

    ui->graphicsView_2->setStyleSheet("background-image : url(/home/dariamityagina/VM_LAB_2_Kraevaya_z/fe.png)");
    ui->graphicsView->setStyleSheet("border-image : url(/home/dariamityagina/VM_LAB_2_Kraevaya_z/fee.png) 8");

    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(0, 50);
    ui->plot->yAxis->setRange(-25, 25);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Part A
void declare_parameters_for_A()
{

}


