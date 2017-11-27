#include<dht.h>
dht DHT;

float tempC;
#define LM35_PIN 0
 
void setupLM35() {
}
 
void readLM35() {
  Serial.println("***********  LM35  *********");
  tempC = analogRead(LM35_PIN);           //read the value from the sensor
  tempC = (5.0 * tempC * 100.0)/1024.0;  //convert the analog data to temperature
  Serial.print("Temp C: ");
  Serial.println(tempC);             //send the data to the computer
  delay(1000);                           //wait one second before sending new data
 
}
// if you require to change the pin number, Edit the pin with your arduino pin.

#define DHT11_PIN 6
void setupDHT11() {
}
void readDHT11() {
  // READ DATA

int chk = DHT.read11(DHT11_PIN);

Serial.println(" Humidity " );

Serial.println(DHT.humidity, 1);

Serial.println(" Temparature ");

Serial.println(DHT.temperature, 1);

delay(2000);
}
void setup(void) {
  // start serial port
  Serial.begin(9600);
 
  //init DS1820
  setupDHT11();
  setupLM35();
}
 
void loop(void) { 
  readDHT11();
  readLM35();
  delay(2000);  
}
