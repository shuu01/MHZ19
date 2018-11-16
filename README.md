# MHZ19 
Arduino IDE library for operating the MH-Z19 CO2 sensor in ESP-WROOM-02/32(ESP8266/ESP32) or Arduino  
version 0.3

# Credits and license  
License MIT

# How to use

* Include this library to your Arduino IDE.
* Wiring MH-Z19 sensor to your Arduino or ESP-WROOM-02/32(ESP8266/ESP32).

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

* Read sample source code. It's very simple !

# caution

* MH-Z19 is supporting PWM , but this library is supporting only serial connection. 
* this library is testing only ESP-WROOM-02/32(ESP8266/ESP32) boards. if you can't execute this library on your arduino (or clone) boards, please contact me.

# MHZ19 library function

## Constructor

* MHZ19 
  normal constructor. if you use this constructor, you must execute begin() function after this constructor execute.

* MHZ19(int rx, int tx)  
  setting rx and tx pin, and initialize Software Serial.

## public function

* void begin(int rx, int tx)  
  setting rx and tx pin, and initialize Software Serial.
  
* void setAutoCalibration(bool autocalib)  
  MH-Z19 has automatic calibration procedure. the MH-Z19 executing automatic calibration, its do zero point(stable gas environment (400ppm)) judgement.
  The automatic calibration cycle is every 24 hours after powered on.  
  If you use this sensor indoor, you should execute `setAutoCalibration(false)`.

* void calibrateZero()  
  execute zero point calibration. 
  if you want to execute zero point calibration, the MH-Z19 sensor must work in stable gas environment (400ppm) for over 20 minutes and you execute this function.

* void calibrateSpan(int ppm)  
  execute span point calibration.
  if you want to execute span point calibration, the MH-Z19 sensor must work in between 1000 to 2000ppm level co2 for over 20 minutes and you execute this function.
  
* int getPPM()  
  get co2 ppm.
  
* int getTemperature()  
  get temperature (MH-Z19 hidden function?  this function is not support.)

* int getStatus()  
  get ths MH-Z19 sensor status value (but I don't know what this value is. this function do not support, too.)

* bool isWarming()  
  check the MH-Z19 sensor is warming up.

# link
* MH-Z19 Data sheet  
  http://www.winsen-sensor.com/d/files/PDF/Infrared%20Gas%20Sensor/NDIR%20CO2%20SENSOR/MH-Z19%20CO2%20Ver1.0.pdf

* MH-Z19B Data sheet  
  http://www.winsen-sensor.com/d/files/infrared-gas-sensor/mh-z19b-co2-ver1_0.pdf
  v 1.3
  http://style.winsensor.com/pro_pdf/MH-Z19B.pdf

# history
* ver. 0.1: closed version.
* ver. 0.2: first release version.
* ver. 0.3: support ESP-WROOM-32(ESP32), Change library name. (MHZ19_Serial -> MHZ19_uart)
