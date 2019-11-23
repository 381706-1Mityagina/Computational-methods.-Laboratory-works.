#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QTextStream>
#include <QVBoxLayout>
#include <QFontDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QDateTime>
#include <QDebug>
#include <QInputDialog>
#include <iostream>
#include "cubic_spline.h"

using namespace std;

IS is;

int count_points = 0;
int flag = 0, input = -1;
double _x_le, _y_le;

QString MainWindow::defaultFileName = "VM";

void MainWindow::updateCurrentFile(const QString& fullPath)
{
    currentFile = fullPath;
    QFileInfo fileInfo(fullPath);
}

Point::Point()
{}

Point::~Point()
{
    x = y = 0;
}

void Point::_to_file(IS &is, ofstream &out) {
    for (auto &smth : is)
        smth.second.show_all(out);
}

void MainWindow::save_w() {
    string name;
    bool ok;

    QString fileName = QFileDialog::getSaveFileName(
                           this, tr("Save file as..."),
                           currentFile, tr("Text files (*.txt)"));

    if (fileName.size() == 0) {
        return;
    }

    name = fileName.toStdString();
    ofstream file(name);
    if(file) {
        for (auto &smth : is)
            smth.second.show_all(file);
    }
    file.close();

    updateCurrentFile(fileName);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentFile(MainWindow::defaultFileName)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add()
{
    currentFile = defaultFileName;
    Point p;

    p.x = _x_le;
    p.y = _y_le;

    unsigned int id_now = count_points;
    if (!(p.x == 0 && p.y == 0))
    is[id_now] = Point(p.x, p.y, id_now);
    count_points++;
}

void MainWindow::show_p()
{

}

void MainWindow::show_g()
{

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 > 0)
       input = 0;
}

void MainWindow::on_pushButton_clicked()
{
    save_w();
}

void MainWindow::on_pushButton_4_clicked()
{
    //if (flag == 2)
    {
        add();
    //  flag = 3;
    }
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
     if (input == 0)
     {
         _x_le = arg1;
         //flag++;
     }
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    if (input == 0)
    {
        _y_le = arg1;
        //flag++;
    }
}

void MainWindow::on_pushButton_5_clicked() // show points
{
    QVector<double> _x(count_points + 1), _y(count_points + 1);
    QPen pen;
    pen.setColor((qSin(2+1.2)*80+80, qSin(0.6+0)*80+80, qSin(0.6+1.5)*80+80));

    {
        for (auto &point : is)
        {
           _x.push_back(point.second.x);
           _y.push_back(point.second.y);

           ui->widget->addGraph();
           ui->widget->graph()->setPen(pen);
           ui->widget->graph()->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);
           ui->widget->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
           ui->widget->graph()->setData(_x, _y);
           ui->widget->xAxis->setLabel("y");
           ui->widget->yAxis->setLabel("x");
           ui->widget->xAxis->setRange(-100, 100);
           ui->widget->yAxis->setRange(-100, 150);
           ui->widget->replot();
        }
    }
}

void MainWindow::on_pushButton_3_clicked() // show primitive
{
    QVector<double> _x_a((count_points + 1)), _y_a((count_points + 1));
    vector<point_cl> _points(count_points + 1);

    QPen pen;
    pen.setColor((qSin(2+1.2)*80+80, qSin(0.6+0)*80+80, qSin(0.6+1.5)*80+80));

    for (auto &point : is)
    {
       _points[point.second.id] = point_cl(point.second.x, point.second.y);
       _x_a.push_front(point.second.x);
       _y_a.push_front(point.second.y);
    }
    //qSort(_x_a.begin(), _x_a.end());

    ui->widget->graph()->setPen(pen);
    ui->widget->graph()->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsLine);
    ui->widget->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->widget->graph()->setData(_x_a, _y_a);
    ui->widget->xAxis->setLabel("y");
    ui->widget->yAxis->setLabel("x");
    ui->widget->xAxis->setRange(-100, 100);
    ui->widget->yAxis->setRange(-100, 150);
    ui->widget->replot();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    int n;
    if (input == 0)
    {
        input = 1;
        ui->widget->addGraph();
    }
    if (ui->doubleSpinBox_3->value() > 0)
        n = ui->doubleSpinBox_3->value();
    else
        n = 8;
    Point point[n];

    for (int i = 0; i < n; i++)
    {
        point[i] = Point(i + pow(-1, i) * 3 - pow(-2, i) - 10 * i - 8, i + pow(-1, i) * 2 + 5, i);
    }

    for (int i = 0; i < n; i++)
    {
        is[i] = point[i];
        count_points++;
    }
}

void MainWindow::on_pushButton_6_clicked() // show spline
{
    vector<pair<int, int>> _points(count_points + 1);
    int max = -1 * INT_MAX, min = INT_MIN;
    double* X, * Y;

    for (auto &point : is)
    {
        _points[point.second.id].first = point.second.x;
        _points[point.second.id].second = point.second.y;
    }
    sort(_points.begin(), _points.end());

    long count;
    int n = count_points + 1;
    double** answer = new double*[n];
      for (int i = 0; i < n; ++i)
          answer[i] = new double[4];

    CubicSplie(_points, answer, n); // main part of work

    count = 0;
    for (int i = 0; i < n - 1; ++i) {
      double j = (double)_points[i].first;
      while (j < _points[i + 1].first) {
        count++;
        j += 0.01f;
      }
    }

    X = new double[count];
    Y = new double[count];
    QVector<double> f(count), x_new(count);

    size_t k = 0;
    double delta;
    for (int i = 1; i < n; ++i)
    {
       double j = (double)_points[i - 1].first;  // for x
       while (j < _points[i].first) {
        X[k] = j;
        delta = X[k] - _points[i - 1].first;
        double one = (double)answer[i][0] + (double)answer[i][1] * delta;
        double two = (double)answer[i][2] * powf(delta, 2) + (double)answer[i][3] * powf(delta, 3);
        Y[k] = one + two;
        if (Y[k] < min) min = Y[k];
        if (Y[k] > max) max = Y[k];
        j += 0.01f;

        f.push_back(Y[k]); // for graphics
        x_new.push_back(X[k]);

        k++;
        }
      }
      max += 3;
      min -= 3;

    QPen pen;
    pen.setColor((qSin(2+1.2)*80+80, qSin(0.6+0)*80+80, qSin(0.6+1.5)*80+80));

    ui->widget->graph()->setPen(pen);
    ui->widget->graph()->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsLine);
    ui->widget->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->widget->graph()->setData(x_new, f);
    ui->widget->xAxis->setLabel("y");
    ui->widget->yAxis->setLabel("x");
    ui->widget->xAxis->setRange(-100, 100);
    ui->widget->yAxis->setRange(-100, 150);
    ui->widget->replot();
}
