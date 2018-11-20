/*
  MHZ19.cpp - MH-Z19 CO2 sensor library for Arduino
  version 1.0

  License MIT
*/

#include "MHZ19.h"
#include "Arduino.h"

#define WAIT_READ_TIMES 100
#define WAIT_READ_DELAY 10

// public
MHZ19::MHZ19()
{
}

MHZ19::MHZ19(int rx, int tx)
{
    begin(rx, tx);
}

MHZ19::MHZ19(int pwm)
{
    begin(pwm);
}

MHZ19::~MHZ19()
{
}

void MHZ19::begin(int rx, int tx)
{
    _rx_pin = rx;
    _tx_pin = tx;
    _protocol = UART;
}

void MHZ19::begin(int pwm)
{
    _pwm_pin = pwm;
    _protocol = PWM;
}

void MHZ19::setPwmLimit(MHZ19_LIMIT type)
{
    PWM_LIMIT = type;
}

void MHZ19::setAutoCalibration(boolean autocalib)
{
    if (_protocol != UART)
        return;
    writeCommand(autocalib ? autocalib_on : autocalib_off);
}

void MHZ19::calibrateZero()
{
    if (_protocol != UART)
        return;
    writeCommand(zerocalib);
}

void MHZ19::calibrateSpan(int ppm)
{
    if (_protocol != UART)
        return;
    if (ppm < 1000)
        return;

    uint8_t cmd[MHZ19::REQUEST_CNT];
    for (int i = 0; i < MHZ19::REQUEST_CNT; i++)
    {
        cmd[i] = spancalib[i];
    }
    cmd[3] = (uint8_t)(ppm / 256);
    cmd[4] = (uint8_t)(ppm % 256);
    writeCommand(cmd);
}

int MHZ19::getPPM()
{
    switch (_protocol)
    {
    case MHZ19_PROTOCOL::UART:
        return getSerialPPM();
    case MHZ19_PROTOCOL::PWM:
        return getPwmPPM();
    }
    return 0;
}

//protected
void MHZ19::writeCommand(uint8_t cmd[])
{
    writeCommand(cmd, NULL);
}

void MHZ19::writeCommand(uint8_t cmd[], uint8_t *response)
{
    SoftwareSerial mhz19_serial(_rx_pin, _tx_pin);
    mhz19_serial.begin(9600);
    mhz19_serial.write(cmd, REQUEST_CNT);
    mhz19_serial.write(mhz19_checksum(cmd));
    mhz19_serial.flush();

    if (response != NULL)
    {
        int i = 0;
        while (mhz19_serial.available() <= 0)
        {
            if (++i > WAIT_READ_TIMES)
            {
                Serial.println("error: can't get MH-Z19 response.");
                return;
            }
            yield();
            delay(WAIT_READ_DELAY);
        }
        mhz19_serial.readBytes(response, MHZ19::RESPONSE_CNT);
    }
}

// private
int MHZ19::getSerialPPM()
{
    int ppm, temperature, status = 0;
    uint8_t buf[MHZ19::RESPONSE_CNT];

    for (int i = 0; i < MHZ19::RESPONSE_CNT; i++)
    {
        buf[i] = 0x0;
    }

    writeCommand(getppm, buf);

    // parse
    if (buf[0] == 0xff && buf[1] == 0x86 && mhz19_checksum(buf) == buf[MHZ19::RESPONSE_CNT - 1])
    {
        ppm = buf[2] * 256 + buf[3];
        temperature = buf[4] - 40;
        status = buf[5];
    }
    return ppm;
}

int MHZ19::getPwmPPM()
{
    unsigned long th, tl, ppm = 0;

    do
    {
        th = pulseIn(_pwm_pin, HIGH, 1004000) / 1000;
        tl = 1004 - th;
        switch (PWM_LIMIT)
        {
        case MHZ19_LIMIT::PPM_2000:
            ppm = 2000 * (th - 2) / (th + tl - 4);
            break;
        case MHZ19_LIMIT::PPM_5000:
            ppm = 5000 * (th - 2) / (th + tl - 4);
            break;
        }
    } while (th == 0);

    return ppm;
}

uint8_t MHZ19::mhz19_checksum(uint8_t com[])
{
    uint8_t sum = 0x00;
    for (int i = 1; i < MHZ19::REQUEST_CNT; i++)
    {
        sum += com[i];
    }
    sum = 0xff - sum + 0x01;
    return sum;
}
