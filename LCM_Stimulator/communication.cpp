#include "communication.h"

Communication::Communication()
{
    serial.setPortName("COM3");
    serial.setBaudRate(19200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setParity(QSerialPort::NoParity);
    serial.open(QIODevice::ReadWrite);
}

Communication::~Communication()
{
    if (serial.isOpen())
    {
        serial.close();
    }
}

void Communication::SendCommand(char cmd)
{
    serial.write(&cmd,1);
}
