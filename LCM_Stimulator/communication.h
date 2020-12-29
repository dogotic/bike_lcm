#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QtSerialPort>

#define CMD_LEFT        'L'
#define CMD_RIGHT       'R'
#define CMD_HAZZARD     'H'
#define CMD_LOW_BEAM    'K'
#define CMD_HIGH_BEAM   'D'
#define CMD_PARKING     'P'

class Communication
{
public:
    Communication();
    ~Communication();
    void SendCommand(char cmd);

private:
    bool port_open = false;
    QSerialPort serial;
};

#endif // COMMUNICATION_H
