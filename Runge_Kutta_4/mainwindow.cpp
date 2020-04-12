#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "read_coord.h"

#include <iostream>
#include <math.h>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <QGraphicsPixmapItem>

using namespace std;

int x0_val = 17, y0_val = 13, z0_val = 7, counter = 0;
int x1_otr = 0,  x2_otr = 30, r_val  = 28, count_cont = 0;
double step = 0.05, eps = 0.7;
vector<coordinates> xyz;

vector<long double> rungekutta(long double t0, vector<long double> u0, long double h, double eps);
vector<long double> lorenz(vector<long double> x);
string arrayHolder[165000];

istream& operator>>(istream& is, coordinates& v) { return is >> v.x >> v.y >> v.z; }

istream& operator>>(istream& is, vector<coordinates>& vv)
{
    string s;
    getline(is, s);
    istringstream ss(s);
    vector<coordinates>{istream_iterator<coordinates>{ss}, {}}.swap(vv);
    return is;
}

int main_show()
{
    ifstream inFile;
    inFile.open("Data.dat");
    ifstream ifs{ "Data.dat" };

    //check for error:
    if (inFile.fail()) {
        cerr << "ERROR OPENING FILE." << endl;
        exit(1);
    }
    string line;
    counter = 0;

    //Read from a file until you've reached the end and store values in an array:
    while (!inFile.eof()) {
        inFile >> line;
        arrayHolder[counter] = line; //Store each value inside the array variable.
        counter++; //increment the counter variable to store length of array.
    }
}

int main_work(vector<long double> D, double step) {
    ofstream fil("Data.dat");
    int j = 0;
    long double t0 = x1_otr;
    long double tf = x2_otr;
    int n = (int((long double)(tf - t0) / step) * (tf - t0));
    step *= ((long double)(1) / step);
    vector<long double> val(n);
    long double xpos1[n];
    long double xpos2[n];
    long double dt = (long double)((tf - t0) / n);
    val = rungekutta(t0, D, dt, eps);

    fil << val[0] << "     " << val[1] << "     " << val[2] << "\n";

    for (int i = 0; i < n; i += step)
    {
        val = rungekutta(t0, val, dt, eps);
        fil << val[0] << "     " << val[1] << "     " << val[2] << "\n";
    }
    fil.close();
    return 0;
}

//Lorenz Attractor
vector<long double> lorenz(vector<long double> x) {
    long double B = 2.0;
    long double R = r_val;
    long double sigma = 10.0;

    vector<long double> dxdt(3);

    dxdt[0] = sigma * (x[1] - x[0]);
    dxdt[1] = x[0] * (R - x[2]) - x[1];
    dxdt[2] = x[0] * x[1] - B * x[2];

    return dxdt;
}

//RK4
vector<long double> rungekutta(long double t0, vector<long double> u0, long double h, double eps){
    long double t1, t2, t3;
    vector<long double> f1(3), f2(3), f3(3), f4(3);
    vector<long double> u(3), u_sh(3), u1(3), u2(3), u3(3);

    f1 = lorenz(u0);
    for (int i = 0; i < 3; i++)
        u1[i] = u0[i] + h * f1[i] / 2.0;

    f2 = lorenz(u1);
    for (int i = 0; i < 3; i++)
        u2[i] = u0[i] + h * f2[i] / 2.0;

    f3 = lorenz(u2);
    for (int i = 0; i < 3; i++)
        u3[i] = u0[i] + h * f3[i];

    f4 = lorenz(u3);
    for (int i = 0; i < 3; i++)
        u[i] = u0[i] + h * (f1[i] + 2.0 * f2[i] + 2.0 * f3[i] + f4[i]) / 6.0;

    for (int t = 0; t < 2; t++)
    {
        f1 = lorenz(u0);
        for (int i = 0; i < 3; i++) {
            u1[i] = u0[i] + (h / 2)*f1[i] / 2.0;
        }

        f2 = lorenz(u1);
        for (int i = 0; i < 3; i++) {
            u2[i] = u0[i] + (h / 2) * f2[i] / 2.0;
        }

        f3 = lorenz(u2);
        for (int i = 0; i < 3; i++) {
            u3[i] = u0[i] + (h / 2) * f3[i];
        }

        f4 = lorenz(u3);
        for (int i = 0; i < 3; i++) {
            u_sh[i] = u0[i] + (h / 2) * (f1[i] + 2.0 * f2[i] + 2.0 * f3[i] + f4[i]) / 6.0;
        }
    }
    double check = abs((u_sh[0] - u[0]) / 15);
    double diff = h;

    if (check > eps)
        h /= 2;
    else if (check < 32)
        h *= 2;

    if (diff - h > 0)
        u = rungekutta(t0, u0, h, eps);

    return u;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setStyleSheet("background-image : url(/home/dariamityagina/VM_CPP_TRY_1/inf.png)");

    ui->r_slide->setRange(-15, 150);
    ui->r_slide->setValue(r_val);

    ui->doubleSpinBox_6->setValue(x0_val);
    ui->doubleSpinBox_5->setValue(y0_val);
    ui->doubleSpinBox_9->setValue(z0_val);

    ui->doubleSpinBox_7->setValue(x1_otr);
    ui->doubleSpinBox_8->setValue(x2_otr);

    ui->doubleSpinBox->setValue(step);
    ui->doubleSpinBox_2->setValue(eps);

    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(-30, 30);
    ui->plot->yAxis->setRange(-30, 30);

    ui->plot_yz->xAxis->setLabel("z");
    ui->plot_yz->yAxis->setLabel("y");
    ui->plot_yz->xAxis->setRange(0, 50);
    ui->plot_yz->yAxis->setRange(-50, 50);

    ui->plot_xz->xAxis->setLabel("z");
    ui->plot_xz->yAxis->setLabel("x");
    ui->plot_xz->xAxis->setRange(0, 50);
    ui->plot_xz->yAxis->setRange(-50, 50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_doubleSpinBox_6_valueChanged(double arg1) // нач условие (значение х)
{
    count_cont = 0;
    x0_val = arg1;
}

void MainWindow::on_doubleSpinBox_5_valueChanged(double arg1) // нач условие (значение у)
{
    count_cont = 0;
    y0_val = arg1;
}

void MainWindow::on_doubleSpinBox_7_valueChanged(double arg1) // отрезок интегр-я (х1)
{
    x1_otr = arg1;
}

void MainWindow::on_doubleSpinBox_8_valueChanged(double arg1) // отрезок интегр-я (х2)
{
    x2_otr = arg1;
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1) // величина шага
{
    step = arg1;
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1) // погрешность
{
    eps = arg1;
}

void MainWindow::on_doubleSpinBox_9_valueChanged(double arg1)
{
    count_cont = 0;
    z0_val = arg1;
}

void MainWindow::on_plot_g_btn_clicked()
{
    vector<long double> D(3);
    D[0] = x0_val;
    D[1] = y0_val;
    D[2] = z0_val;

    main_work(D, step);

    ifstream inFile;
    inFile.open("Data.dat");
    ifstream ifs{ "Data.dat" };

    //check for error:
    if (inFile.fail()) {
        cerr << "ERROR OPENING FILE." << endl;
        exit(1);
    }
    string line;
    counter = 0;

    //Read from a file until you've reached the end and store values in an array:
    while (!inFile.eof()) {
        inFile >> line;
        arrayHolder[counter] = line; //Store each value inside the array variable.
        counter++; //increment the counter variable to store length of array.
    }

    xyz = vector<coordinates>{ istream_iterator<coordinates>{ifs}, {} };

    PrintPhasePlanes();
    ifs.close();
}

void MainWindow::PrintPhasePlanes()
{
    QVector<double> x(xyz.size()), y(xyz.size()), z(xyz.size());
    QPen pen;
    ui->plot->replot();
    pen.setColor(QColor(33, 173, 173));
    pen.setStyle(Qt::SolidLine);

    ui->plot->clearItems();
    ui->plot->clearPlottables();
    ui->plot->update();
    ui->plot->addGraph();
    ui->plot->graph()->setPen(pen);
    ui->plot->graph()->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);
    ui->plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    ui->plot_yz->replot();
    ui->plot_yz->clearItems();
    ui->plot_yz->clearPlottables();
    ui->plot_yz->update();
    ui->plot_yz->addGraph();
    ui->plot_yz->graph()->setPen(pen);
    ui->plot_yz->graph()->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);
    ui->plot_yz->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    ui->plot_xz->replot();
    ui->plot_xz->clearItems();
    ui->plot_xz->clearPlottables();
    ui->plot_xz->update();
    ui->plot_xz->addGraph();
    ui->plot_xz->graph()->setPen(pen);
    ui->plot_xz->graph()->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);
    ui->plot_xz->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    for (int i = 0; i < xyz.size(); i++)
    {
        {
            x.push_back(xyz[i].x);
            y.push_back(xyz[i].y);
            z.push_back(xyz[i].z);
        }
    }
    double x_min = *std::min_element(x.begin(), x.end());
    double x_max = *std::max_element(x.begin(), x.end());
    double y_min = *std::min_element(y.begin(), y.end());
    double y_max = *std::max_element(y.begin(), y.end());
    double z_min = *std::min_element(z.begin(), z.end());
    double z_max = *std::max_element(z.begin(), z.end());

    ui->plot_xz->xAxis->setRange(z_min - 10, z_max + 10);
    ui->plot_xz->yAxis->setRange(x_min - 10, x_max + 10);

    ui->plot_yz->xAxis->setRange(z_min - 10, z_max + 10);
    ui->plot_yz->yAxis->setRange(y_min - 10, y_max + 10);

    ui->plot->xAxis->setRange(y_min - 10, y_max + 10);
    ui->plot->yAxis->setRange(x_min - 10, x_max + 10);

    ui->plot->graph()->setData(y, x);
    ui->plot->replot();

    ui->plot_yz->graph()->setData(z, y);
    ui->plot_yz->replot();

    ui->plot_xz->graph()->setData(z, x);
    ui->plot_xz->replot();
}

void MainWindow::on_r_slide_valueChanged(int value)
{
    count_cont = 0;
    ui->spinBox->setValue(value);
    r_val = value;
}

void MainWindow::on_clear_btn_clicked()
{
    ui->plot->clearItems();
    ui->plot->clearPlottables();
    ui->plot->replot();

    ui->plot_xz->clearItems();
    ui->plot_xz->clearPlottables();
    ui->plot_xz->replot();

    ui->plot_yz->clearItems();
    ui->plot_yz->clearPlottables();
    ui->plot_yz->replot();
}

void MainWindow::on_plot_cont_clicked()
{
    if (count_cont < 1)
    {
        x0_val = xyz[xyz.size() - 1].x;
        y0_val = xyz[xyz.size() - 1].y;
        z0_val = xyz[xyz.size() - 1].z;

        ui->doubleSpinBox_6->setValue(x0_val);
        ui->doubleSpinBox_5->setValue(y0_val);
        ui->doubleSpinBox_9->setValue(z0_val);

        vector<long double> D(3);
        D[0] = x0_val;
        D[1] = y0_val;
        D[2] = z0_val;

        main_work(D, step);

        ifstream inFile;
        inFile.open("Data.dat");
        ifstream ifs{ "Data.dat" };

        //check for error:
        if (inFile.fail()) {
            cerr << "ERROR OPENING FILE." << endl;
            exit(1);
        }
        string line;
        counter = 0;

        //Read from a file until you've reached the end and store values in an array:
        while (!inFile.eof()) {
            inFile >> line;
            arrayHolder[counter] = line; //Store each value inside the array variable.
            counter++; //increment the counter variable to store length of array.
        }

        xyz = vector<coordinates>{ istream_iterator<coordinates>{ifs}, {} };

        PrintPhasePlanes();
        count_cont++;
    }
}
