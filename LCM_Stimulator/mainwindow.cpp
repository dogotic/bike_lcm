#include <QDebug>
#include <QIcon>

#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: darkgray;");
    ui->pushButton_LEFT->setIcon(QIcon(":/icons/icons/arrow_left_off.png"));
    ui->pushButton_HAZZARD->setIcon(QIcon(":/icons/icons/hazzard_off.png"));
    ui->pushButton_RIGHT->setIcon(QIcon(":/icons/icons/arrow_right_off.png"));
    ui->pushButton_LOW_BEAM->setIcon(QIcon(":/icons/icons/low-beam_off.png"));
    ui->pushButton_HIGH_BEAM->setIcon(QIcon(":/icons/icons/high-beam_off.png"));
    ui->pushButton_PARKING_LIGHT->setIcon(QIcon(":/icons/icons/parking-lights_off.png"));
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * @brief MainWindow::on_pushButton_LEFT_clicked
 */
void MainWindow::on_pushButton_LEFT_clicked()
{
    if (!left_is_on)
    {
        ui->pushButton_LEFT->setIcon(QIcon(":/icons/icons/arrow_left_on.png"));
        left_is_on = true;

        ui->pushButton_RIGHT->setIcon(QIcon(":/icons/icons/arrow_right_off.png"));
        right_is_on = false;

        ui->pushButton_HAZZARD->setIcon(QIcon(":/icons/icons/hazzard_off.png"));
        hazzard_is_on = false;
    }
    else
    {
        ui->pushButton_LEFT->setIcon(QIcon(":/icons/icons/arrow_left_off.png"));
        left_is_on = false;
    }
    com.SendCommand(CMD_LEFT);
}

/**
 * @brief MainWindow::on_pushButton_HAZZARD_clicked
 */
void MainWindow::on_pushButton_HAZZARD_clicked()
{
    if (!hazzard_is_on)
    {
        ui->pushButton_HAZZARD->setIcon(QIcon(":/icons/icons/hazzard_on.png"));
        hazzard_is_on = true;

        ui->pushButton_LEFT->setIcon(QIcon(":/icons/icons/arrow_left_off.png"));
        left_is_on = false;

        ui->pushButton_RIGHT->setIcon(QIcon(":/icons/icons/arrow_right_off.png"));
        right_is_on = false;
    }
    else
    {
        ui->pushButton_HAZZARD->setIcon(QIcon(":/icons/icons/hazzard_off.png"));
        hazzard_is_on = false;
    }
    com.SendCommand(CMD_HAZZARD);
}

/**
 * @brief MainWindow::on_pushButton_RIGHT_clicked
 */
void MainWindow::on_pushButton_RIGHT_clicked()
{
    if (!right_is_on)
    {
        ui->pushButton_RIGHT->setIcon(QIcon(":/icons/icons/arrow_right_on.png"));
        right_is_on = true;

        ui->pushButton_LEFT->setIcon(QIcon(":/icons/icons/arrow_left_off.png"));
        left_is_on = false;

        ui->pushButton_HAZZARD->setIcon(QIcon(":/icons/icons/hazzard_off.png"));
        hazzard_is_on = false;
    }
    else
    {
        ui->pushButton_RIGHT->setIcon(QIcon(":/icons/icons/arrow_right_off.png"));
        right_is_on = false;
    }
    com.SendCommand(CMD_RIGHT);
}

/**
 * @brief MainWindow::on_pushButton_LOW_BEAM_clicked
 */
void MainWindow::on_pushButton_LOW_BEAM_clicked()
{
    if (!low_beam_is_on)
    {
        ui->pushButton_LOW_BEAM->setIcon(QIcon(":/icons/icons/low-beam_on.png"));
        low_beam_is_on = true;
        ui->pushButton_HIGH_BEAM->setIcon(QIcon(":/icons/icons/high-beam_off.png"));
        high_beam_is_on = false;
        ui->pushButton_PARKING_LIGHT->setIcon(QIcon(":/icons/icons/parking-lights_off.png"));
        parking_light_is_on = false;
    }
    else
    {
        ui->pushButton_LOW_BEAM->setIcon(QIcon(":/icons/icons/low-beam_off.png"));
        low_beam_is_on = false;
    }
    com.SendCommand(CMD_LOW_BEAM);
}

/**
 * @brief MainWindow::on_pushButton_HIGH_BEAM_clicked
 */
void MainWindow::on_pushButton_HIGH_BEAM_clicked()
{
    if (!high_beam_is_on)
    {
        ui->pushButton_HIGH_BEAM->setIcon(QIcon(":/icons/icons/high-beam_on.png"));
        high_beam_is_on = true;
        ui->pushButton_PARKING_LIGHT->setIcon(QIcon(":/icons/icons/parking-lights_off.png"));
        parking_light_is_on = false;
        ui->pushButton_LOW_BEAM->setIcon(QIcon(":/icons/icons/low-beam_off.png"));
        low_beam_is_on = false;
    }
    else
    {
        ui->pushButton_HIGH_BEAM->setIcon(QIcon(":/icons/icons/high-beam_off.png"));
        high_beam_is_on = false;
    }
    com.SendCommand(CMD_HIGH_BEAM);
}

/**
 * @brief MainWindow::on_pushButton_PARKING_LIGHT_clicked
 */
void MainWindow::on_pushButton_PARKING_LIGHT_clicked()
{
    if (!parking_light_is_on)
    {
        ui->pushButton_PARKING_LIGHT->setIcon(QIcon(":/icons/icons/parking-lights_on.png"));
        parking_light_is_on = true;
        ui->pushButton_LOW_BEAM->setIcon(QIcon(":/icons/icons/low-beam_off.png"));
        low_beam_is_on = false;
        ui->pushButton_HIGH_BEAM->setIcon(QIcon(":/icons/icons/high-beam_off.png"));
        high_beam_is_on = false;
    }
    else
    {
        ui->pushButton_PARKING_LIGHT->setIcon(QIcon(":/icons/icons/parking-lights_off.png"));
        parking_light_is_on = false;
    }
    com.SendCommand(CMD_PARKING);
}
