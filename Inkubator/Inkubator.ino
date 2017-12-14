/*****************************************************
Chip type               : ATmega328
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : N/A
Data Stack size         : N/A
 *****************************************************/
extern "C"{
#include "fsm.h"
}
//Library
#include <LiquidCrystal.h>
#include <dht.h>
#include <math.h>
#include <Arduino_FreeRTOS.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;

// Pin number :
#define LM35_PIN A0
#define DHT11_PIN 6
const int buttonMode = 7;
const int buttonSet = 8;
const int pinOut = 10;

// Variables will change :
float tempC;
int suhu;
int day=0;
int hour=0;
int minute=0;
int second=0;
int DAY_digit1=0;
int DAY_digit2=0;
int HOUR_digit1=0;
int HOUR_digit2=0;
int MIN_digit1=0;
int MIN_digit2=1;
int SEC_digit1=0;
int SEC_digit2=0;
int state = DATA_KEEP;

void setup() {
  // put your setup code here, to run once:
  xTaskCreate(MyTask1, "Task1", 64, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 32, NULL, 2, NULL);
  xTaskCreate(MyTask3, "Task2", 64, NULL, 2, NULL);
  xTaskCreate(MyTask4, "Task2", 64, NULL, 2, NULL);
  xTaskCreate(MyIdleTask, "IdleTask", 64, NULL, 0, NULL);
  
  pinMode(buttonMode, INPUT_PULLUP);
  pinMode(buttonSet, INPUT_PULLUP);
  pinMode(pinOut, OUTPUT);
  analogReference(INTERNAL);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

}

void loop() {
}

static void MyTask1(void* pvParameters)
{ 
  int counttemp = 0;
  float totaltemp;
  int lamp = 0;
  while(1)
  {
      suhu = analogRead(LM35_PIN); //read the value from the sensor
      totaltemp += suhu/9.309; //convert the analog data to temperature
      counttemp++;
      if (counttemp>=10){
        tempC = totaltemp/10;
         if ((lamp==0)&&(tempC >= 37.5)){
            digitalWrite(pinOut, LOW);
            lamp=1;
         }else if ((lamp==1)&&(tempC <= 37.8)) {
            digitalWrite(pinOut, HIGH);
            lamp=0;
         }
         counttemp=0;
      }
      vTaskDelay(20/portTICK_PERIOD_MS);
  }
}


static void MyTask2(void* pvParameters)
{ 
  while(1)
  {
  int chk = DHT.read11(DHT11_PIN);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
 
/* Task1 with priority 1 */
static void MyTask3(void* pvParameters)
{
  int pushMode;
  int pushSet;
  int Mode_Evt=0;
  int Set_Evt=0;
  int statemodeevent=11;
  int statesetevent=13;
  
  while(1)
  {    
        /* Pembacaan Input dari Pushbutton active LOW */
      if (digitalRead(buttonMode)==HIGH) {
            pushMode = 0;
      } else {
            pushMode = 1;
      }
      if (digitalRead(buttonSet)==HIGH) {
            pushSet = 0;
      } else {
            pushSet = 1;
      }
    
    detectmodeevent(pushMode,&Mode_Evt,&statemodeevent);
    detectsetevent(pushSet,&Set_Evt,&statesetevent);
    
      //inisialisasi nilai digit untuk mode  setting
      if((state==0)||(state==1)){
        DAY_digit1=day/10;
        DAY_digit2=day%10;
        HOUR_digit1=hour/10;
        HOUR_digit2=hour%10;
        MIN_digit1=minute/10;
        MIN_digit2=minute%10;
        SEC_digit1=second/10;
        SEC_digit2=second%10;
      }
    
      fsm(Mode_Evt, Set_Evt, &DAY_digit1, &DAY_digit2, &HOUR_digit1, &HOUR_digit2, &MIN_digit1, &MIN_digit2,
     &SEC_digit1, &SEC_digit2, &state);
    
      //set output nilai hasil settingan
    if(state==1){
        day=(DAY_digit1*10)+DAY_digit2;
        hour=(HOUR_digit1*10)+HOUR_digit2;
        minute=(MIN_digit1*10)+MIN_digit2;
        second=(SEC_digit1*10)+SEC_digit2;
    }
    
      vTaskDelay(100/portTICK_PERIOD_MS);
  }
}


/* Task2 with priority 2 */
static void MyTask4(void* pvParameters)
{
  while(1)
  {
  if ((state==0)||(state==1)){
    if (second > 0){
      second--;
    }else{
      second=59; 
      if (minute > 0){
        minute--;
      }else{
        minute=59; 
        if (hour > 0){
          hour--;
        }else{
          hour=23; 
          day--;
        }
      }
    }
    }
  
  if ((second==0)&&(minute==0)&&(hour==0)&&(day==0)){
    state=10;
  }
  
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}


/* Idle Task with priority Zero */ 
static void MyIdleTask(void* pvParameters)
{
  while(1)
  {
      switch (state){
        case 0:{
          lcd.setCursor(0, 0);  
          lcd.print("Temp       C");
          lcd.setCursor(5, 0);
          lcd.print(tempC);
          lcd.setCursor(0, 1);
          lcd.print("Humidity      %");
          lcd.setCursor(9, 1);
          lcd.print(DHT.humidity);
          break;
        }
        case 1:{
          printtime();
          break;
        }
        case 2:{
          printtime();
          lcd.setCursor(0, 1);
          lcd.blink();
          break;
        }
        case 3:{
          printtime();
          lcd.setCursor(1, 1);
          lcd.blink();
          break;
        }
        case 4:{
          printtime();
          lcd.setCursor(4, 1);
          lcd.blink();
          break;
        }
        case 5:{
          printtime();
          lcd.setCursor(5, 1);
          lcd.blink();
          break;
        }
        case 6:{
          printtime();
          lcd.setCursor(8, 1);
          lcd.blink();
          break;
        }
        case 7:{
          printtime();
          lcd.setCursor(9, 1);
          lcd.blink();
          break;
        }
        case 8:{
          printtime();
          lcd.setCursor(12, 1);
          lcd.blink();
          break;
        }
        case 9:{
          printtime();
          lcd.setCursor(13, 1);
          lcd.blink();
          break;
        }
        case 10:{
          lcd.setCursor(0, 0);  
          lcd.print("Selamat!");
          lcd.setCursor(0, 1);
          lcd.print("Telur sudah menetas!");
          break;
        }
      }

  }
}

void printtime(){
  lcd.setCursor(0, 0);
  lcd.print("DY  HR  MN  SC");
  lcd.setCursor(0, 1);
  lcd.print(DAY_digit1);
  lcd.setCursor(1, 1);
  lcd.print(DAY_digit2);
  lcd.setCursor(4, 1);
  lcd.print(HOUR_digit1);
  lcd.setCursor(5, 1);
  lcd.print(HOUR_digit2);
  lcd.setCursor(8, 1);
  lcd.print(MIN_digit1);
  lcd.setCursor(9, 1);
  lcd.print(MIN_digit2);
  lcd.setCursor(12, 1);
  lcd.print(SEC_digit1);
  lcd.setCursor(13, 1);
  lcd.print(SEC_digit2);
}

