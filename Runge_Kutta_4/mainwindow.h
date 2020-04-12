#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

struct coordinates
{
    double x;
    double y;
    double z;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_doubleSpinBox_6_valueChanged(double arg1);

    void on_doubleSpinBox_5_valueChanged(double arg1);

    void on_doubleSpinBox_7_valueChanged(double arg1);

    void on_doubleSpinBox_8_valueChanged(double arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_9_valueChanged(double arg1);

    void on_plot_g_btn_clicked();

    void on_r_slide_valueChanged(int value);

    void on_clear_btn_clicked();

    void PrintPhasePlanes();

    void on_plot_cont_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
