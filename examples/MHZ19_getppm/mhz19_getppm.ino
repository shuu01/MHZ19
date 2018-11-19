/*----------------------------------------------------------
    MH-Z19 CO2 sensor  SAMPLE
  ----------------------------------------------------------*/

#include <MHZ19.h>

const int rx_pin = 4; //Serial rx pin no
const int tx_pin = 5; //Serial tx pin no

MHZ19 mhz19;
protocol = MHZ19_PROTOCOL UART;

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup() {
  Serial.begin(9600);
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(false);
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop() {
  setData(protocol);
  int co2ppm = mhz19.getPPM();
  int temp = mhz19.getTemperature();
  int status = mhz19.getStatus();

  Serial.print("co2: "); Serial.println(co2ppm);
  Serial.print("temp: "); Serial.println(temp);
  Serial.print("status: "); Serial.println(status);

  delay(5000);
}

