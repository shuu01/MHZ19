/*----------------------------------------------------------
    MH-Z19 CO2 sensor  SAMPLE
  ----------------------------------------------------------*/

#include <MHZ19.h>

const int rx_pin = 4; //Serial rx pin no
const int tx_pin = 5; //Serial tx pin no

MHZ19 mhz19(rx_pin, tx_pin);

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup() {
  Serial.begin(9600);
  mhz19.setAutoCalibration(false);
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop() {
  int co2ppm = mhz19.getPPM();
  Serial.print("co2: ");
  Serial.println(co2ppm);
  delay(5000);
}

