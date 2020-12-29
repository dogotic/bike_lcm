#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "communication.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_LEFT_clicked();

    void on_pushButton_HAZZARD_clicked();

    void on_pushButton_RIGHT_clicked();

    void on_pushButton_LOW_BEAM_clicked();

    void on_pushButton_HIGH_BEAM_clicked();

    void on_pushButton_PARKING_LIGHT_clicked();

private:
    Ui::MainWindow *ui;
    bool left_is_on             = false;
    bool right_is_on            = false;
    bool hazzard_is_on          = false;
    bool low_beam_is_on         = false;
    bool high_beam_is_on        = false;
    bool parking_light_is_on    = false;
    Communication   com;
};
#endif // MAINWINDOW_H
