
// include the library code:
#include <LiquidCrystal.h>
#include <dht.h>
#include <math.h>


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;

int pinOut = 10;
float tempC;
int suhu;
#define LM35_PIN A0
 
void setupLM35() {
}
 
void readLM35() {
  Serial.println("***********  LM35  *********");
  suhu = analogRead(LM35_PIN);           //read the value from the sensor
  tempC = suhu/9.309;  //convert the analog data to temperature
  Serial.print("Temp C: ");
  Serial.println(tempC);             //send the data to the computer
  lcd.setCursor(5, 0);
  lcd.print(tempC);
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
lcd.setCursor(9, 1);
lcd.print(DHT.humidity, 1);
Serial.println(" Temparature ");
Serial.println(DHT.temperature, 1);
delay(2000);
}


void setup() {
  pinMode(10, OUTPUT);
  analogReference(INTERNAL);
  Serial.begin(9600);
  setupDHT11();
  setupLM35();
  // set up the LCD's number of columns and rows:
   lcd.begin(16, 2);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // Print a message to the LCD.
  lcd.setCursor(0, 0);  
  lcd.print("Temp       C");
  readLM35();
  lcd.setCursor(0, 1);
  lcd.print("Humidity      %"); 
  readDHT11();
  if (tempC >= 37.5){
    digitalWrite(pinOut, LOW);
  }
  else {
    digitalWrite(pinOut, HIGH);
  }
  delay(2000);  
}
