#include <algorithm>
#include <clocale>
#include <set>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <unordered_map>
#include <iostream>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QInputDialog>
#include <QGroupBox>
#include <QEvent>
#include <QTextCursor>
#include <QHelpEvent>
#include <QToolTip>
#include <QMainWindow>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

using namespace std;

#define IS unordered_map<int, Point>

class Point
{
public:
    double x, y;
    int id;
    Point();
    ~Point();
    Point(float _x, float _y, int id_now)
    {
        this->x = _x;
        this->y = _y;
        this->id = id_now;
    }

    void show_all(ostream &out) {
        QWidget window;
        QVBoxLayout layout(&window);
        QLineEdit _x;
        QLineEdit _y;
        layout.addWidget(&_x);
        layout.addWidget(&_y);
        QTextEdit text;
        layout.addWidget(&text);
        QObject::connect(&_x, &QLineEdit::textChanged, [&](const QString &_x) {
           text.setPlainText(QString("%1").arg(_x));
        });
        QObject::connect(&_y, &QLineEdit::textChanged, [&](const QString &_y) {
           text.setPlainText(QString("%1").arg(_y));
        });

        out << "\t|\t" << x << "\t|\t" << y << "\n";
    }

    void _to_file(IS &is, ofstream &out);
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
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
    void on_doubleSpinBox_valueChanged(double arg1);
    void on_doubleSpinBox_2_valueChanged(double arg1);
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    void show_p();
    void add();
    void show_g();
    void save_w();

    QAction *show_points;
    QAction *show_graphics;
    QString currentFile;

    static QString defaultFileName;

    void createActions();
    void updateCurrentFile(const QString& fullPath);
};

#endif // MAINWINDOW_H
