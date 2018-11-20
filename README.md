# MHZ19
Arduino IDE library for operating the MH-Z19 CO2 sensor

# Credits and license
License MIT

# How to use

* Include this library to your Arduino IDE.
* Wiring MH-Z19 sensor to your Arduino.
```
MH-Z19 Vout to Arduino Vout(5V)
MH-Z19 GND  to Arduino GND
MH-Z19 Tx   to Arduino Digital Pin (Serial Rx pin)
MH-Z19 Rx   to Arduino Digital Pin (Serial Tx pin)
other MH-Z19 pins are not used.

pin 1 (brown)  // CO2 Vo
pin 2 (white)  // CO2 Nothings
pin 3 (black)  // CO2 GND
pin 4 (red)    // CO2 Vin
pin 5 (blue)   // CO2 Rx (UART)
pin 6 (green)  // CO2 Tx (UART)
pin 7 (yellow) // CO2 Nothings
```
* Read sample source code. It's very simple !

# caution

* MH-Z19 is supporting PWM and UART.

# MHZ19 library function

## Constructor

* MHZ19
  normal constructor. You must execute begin() function after execution this constructor.

* MHZ19(int rx, int tx)
  setting rx and tx pin, and initialize Software Serial.

* MHZ19(int pwm)
  setting pwm pin

## public function

* void begin(int rx, int tx)  
  setting rx and tx pin, and initialize Software Serial.

* void begin(int pwm)  
  setting pwm pin

* void setAutoCalibration(bool autocalib)  
  The automatic base calibration will set the lowest measured internal RAW value in the last 24h as new reference point at 400 ppm.  
  This means the base line will make a big jump when being used in a not well ventilated room for more than 24h. And when opening a door or window after such a recalibration, the measured value will hardly change and stay at 400ppm for hours.  
  If you use this sensor indoor, you should execute `setAutoCalibration(false)`.

* void calibrateZero()  
  execute zero point calibration.  
  if you want to execute zero point calibration, the MH-Z19 sensor must work in stable gas environment (400ppm) for over 20 minutes and you execute this function.

* void calibrateSpan(int ppm)  
  execute span point calibration.  
  if you want to execute span point calibration, the MH-Z19 sensor must work in between 1000 to 2000ppm level co2 for over 20 minutes and you execute this function.

* int getPPM()  
  get co2 ppm.
  
* void setPwmLimit(MHZ19_LIMIT limit)  
  set upper measurement limit for co2 data getting by pwm. 

# link
* MH-Z19 Data sheet
  http://www.winsen-sensor.com/d/files/PDF/Infrared%20Gas%20Sensor/NDIR%20CO2%20SENSOR/MH-Z19%20CO2%20Ver1.0.pdf
* MH-Z19B Data sheet v 1.0
  http://www.winsen-sensor.com/d/files/infrared-gas-sensor/mh-z19b-co2-ver1_0.pdf
* MH-Z19B Data sheet v 1.3
  http://style.winsensor.com/pro_pdf/MH-Z19B.pdf
