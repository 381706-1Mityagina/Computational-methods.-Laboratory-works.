#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Matrix_generator.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QScrollArea>
#include <ctime>
#include "Gauss.h"
#include "Cramer.h"
#include "Gauss_Seidel.h"
#include "Simple_iterations.h"
#include "methods.cpp"
#include "LU_decomposition.h"
#include "yakobi.h"
#include "successive_over_relaxation.h"

int method = -1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setStyleSheet("color: rgb(255, 255, 255);");

    QStandardItemModel *model2 = new QStandardItemModel;
    QStandardItem *item;

    //Заголовки столбцов
    QStringList horizontalHeader2;
    horizontalHeader2.append("    0    ");
    horizontalHeader2.append("    1    ");
    horizontalHeader2.append("    2    ");
    horizontalHeader2.append("    3    ");

    //Заголовки строк
    QStringList verticalHeader2;

    model2->setHorizontalHeaderLabels(horizontalHeader2);
    model2->setVerticalHeaderLabels(verticalHeader2);

    for (int i = 0; i < 3; i++)
     for (int j = 0; j < 4; j++) {
        item = new QStandardItem("");
        model2->setItem(i, j, item);
    }
    ui->tableView->setModel(model2);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_pushButton_clicked()
{
    QWidget* Form = new QWidget;
    Form->setWindowTitle("Справка");
    Form->setAttribute(Qt::WA_DeleteOnClose, true);
    QPixmap pix("/home/dariamityagina/SLAE_lab2/src/all.jpg");
    Form->resize(865, 16800);
    QPalette palette;
    palette.setBrush(QPalette::Background, pix);
    Form->setPalette(palette);
    QScrollArea *tagCloudScrollArea = new QScrollArea;
    tagCloudScrollArea->setWindowTitle("Теория");
    tagCloudScrollArea->setWidget(Form);
    tagCloudScrollArea->resize(865, 500);
    tagCloudScrollArea->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    int n = ui->spinBox->value();
    std::vector<std::vector<double>> matrix;
    matrix = std::vector<std::vector<double>>(n);
    for (int i = 0; i < n; i++)
        matrix[i] = std::vector<double>(n, 0);
    std::vector<double> right_part = std::vector<double>(n, 0);
    std::vector<double> solution = std::vector<double>(n, 0);
    double t1, t2, dt;

    if (ui->tab->isEnabled() && ui->tab_2->isHidden()) // auto generation
    {
        matrix = SLAE::GenerateMatrix(n);
        right_part = SLAE::GenerateVector(n);

        QStandardItemModel *model1 = new QStandardItemModel;
        QStandardItem *item;
        //Заголовки столбцов
        QStringList horizontalHeader;
        //Заголовки строк
        QStringList verticalHeader;

        model1->setHorizontalHeaderLabels(horizontalHeader);
        model1->setVerticalHeaderLabels(verticalHeader);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
               item = new QStandardItem(QString::number(matrix[i][j]));
               model1->setItem(j, i, item);
            }
        for (int j = 0; j < n; j++) {
            item = new QStandardItem(QString::number(right_part[j]));
            model1->setItem(j, n, item);
        }
        ui->tableView->setModel(model1);
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();

    }
    if (ui->tab_2->isEnabled() && ui->tab->isHidden()) // user input
    {
        int n = ui->spinBox->value();
        QVariant myData; //Сюда положим данные из ячейки
        QModelIndex myIndex;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
               myIndex = ui->tableView->model()->index(j, i, QModelIndex());
               myData = ui->tableView->model()->data(myIndex, Qt::DisplayRole);
               matrix[i][j] = myData.toDouble();
            }
        for (int j = 0; j < n; j++)
        {
            myIndex = ui->tableView->model()->index(j, n, QModelIndex());
            myData = ui->tableView->model()->data(myIndex, Qt::DisplayRole);
            right_part[j] = myData.toDouble();
        }
    }
    if (ui->checkBox->isChecked())
    {
        method = 1;
    }
    if (ui->checkBox_2->isChecked())
    {
        method = 2;
    }
    if (ui->checkBox_3->isChecked())
    {
        method = 3;
    }
    if (ui->checkBox_4->isChecked())
    {
        method = 4;
    }
    if (ui->checkBox_5->isChecked())
    {
        method = 5;
    }
    if (ui->checkBox_6->isChecked())
    {
        method = 6;
    }
    if (ui->checkBox_7->isChecked())
    {
        method = 7;
    }

    switch (method) {
        case -1:
        {
            ui->plainTextEdit->setPlainText("");
            ui->plainTextEdit->setPlainText("Метод не выбран\n");
        }
            break;
        case 1:
        {
            ui->plainTextEdit->setPlainText("");
            solution.clear();
            t1 = clock();
            solution = SLAE::Solve_Gauss(matrix, right_part, n);
            t2 = clock();
            dt = t2 - t1;
            // solution = gauss(matrix, right_part, n);
            QString solution_out = "";
            for (int i = 0; i < n; i++)
            {
                solution_out.push_back("x[" + QString::number(i) + "] = " + QString::number(solution[i]) + "\n");
            }
            ui->plainTextEdit_2->setPlainText(QString::number(dt) + " ms\n");
            ui->plainTextEdit->setPlainText("Метод Гаусса\n\nРешение : \n" + solution_out);
        }
            break;
        case 2:
        {
            ui->plainTextEdit->setPlainText("");
            solution.clear();
            t1 = clock();
            solution = SLAE::Solve_Cramer(matrix, right_part, n);
            t2 = clock();
            dt = t2 - t1;
            QString solution_out = "";
            for (int i = 0; i < n; i++)
            {
                solution_out.push_back("x[" + QString::number(i) + "] = " + QString::number(solution[i]) + "\n");
            }
            ui->plainTextEdit_2->setPlainText(QString::number(dt) + " ms\n");
            ui->plainTextEdit->setPlainText("Метод Крамера\n\nРешение : \n" + solution_out);
        }
            break;
        case 3:
        {
            solution.clear();
            t1 = clock();
            solution = SLAE::Solve_GaussSeidel(matrix, right_part, n);
            t2 = clock();
            dt = t2 - t1;
            QString solution_out = "";
            for (int i = 0; i < n; i++)
            {
                solution_out.push_back("x[" + QString::number(i) + "] = " + QString::number(solution[i]) + "\n");
            }
            ui->plainTextEdit_2->setPlainText(QString::number(dt) + " ms\n");
            ui->plainTextEdit->setPlainText("Метод Зейделя\n\nРешение : \n" + solution_out);
        }
            break;
        case 4:
        {
            solution.clear();
            t1 = clock();
            solution = SLAE::Solve_sor(matrix, right_part, 600, 0.00001, 1.0);
            t2 = clock();
            dt = t2 - t1;
            QString solution_out = "";
            for (int i = 0; i < n; i++)
            {
                solution_out.push_back("x[" + QString::number(i) + "] = " + QString::number(solution[i]) + "\n");
            }
            ui->plainTextEdit_2->setPlainText(QString::number(dt) + " ms\n");
            ui->plainTextEdit->setPlainText("Метод верхней релаксации\n\nРешение : \n" + solution_out);
        }
            break;
        case 5:
        {
            solution.clear();
            t1 = clock();
            solution = SLAE::Solve_simple_it(matrix, right_part, n);
            t2 = clock();
            dt = t2 - t1;
            QString solution_out = "";
            for (int i = 0; i < n; i++)
            {
                solution_out.push_back("x[" + QString::number(i) + "] = " + QString::number(solution[i]) + "\n");
            }
            ui->plainTextEdit_2->setPlainText(QString::number(dt) + " ms\n");
            ui->plainTextEdit->setPlainText("Метод простой итерации\n\nРешение : \n" + solution_out);
        }
            break;
        case 6:
        {
            solution.clear();
            t1 = clock();
            solution = SLAE::Solve_LU(matrix, right_part, n);
            t2 = clock();
            dt = t2 - t1;
            QString solution_out = "";
            for (int i = 0; i < n; i++)
            {
                solution_out.push_back("x[" + QString::number(i) + "] = " + QString::number(solution[i]) + "\n");
            }
            ui->plainTextEdit_2->setPlainText(QString::number(dt) + " ms\n");
            ui->plainTextEdit->setPlainText("LU-декомпозиция\n\nРешение : \n" + solution_out);
        }
            break;
        case 7:
        {
            solution.clear();
            t1 = clock();
            solution = SLAE::Solve_Yakobi(matrix, right_part, n, 0.0001);
            t2 = clock();
            dt = t2 - t1;
            QString solution_out = "";
            for (int i = 0; i < n; i++)
            {
                solution_out.push_back("x[" + QString::number(i) + "] = " + QString::number(solution[i]) + "\n");
            }
            ui->plainTextEdit_2->setPlainText(QString::number(dt) + " ms\n");
            ui->plainTextEdit->setPlainText("Метод Якоби\n\nРешение : \n" + solution_out);
        }
            break;
        default:
        {
            ui->plainTextEdit->setPlainText("");
            ui->plainTextEdit->setPlainText("Метод не выбран\n");
        }
            break;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    int n = ui->spinBox->value();

    QStandardItemModel *model1 = new QStandardItemModel;
    QStandardItem *item;
    //Заголовки столбцов
    QStringList horizontalHeader;
    //Заголовки строк
    QStringList verticalHeader;

    model1->setHorizontalHeaderLabels(horizontalHeader);
    model1->setVerticalHeaderLabels(verticalHeader);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n + 1; j++) {
           item = new QStandardItem("");
           model1->setItem(i, j, item);
    }
    ui->tableView->setModel(model1);
    ui->tableView->resizeColumnsToContents();
}
