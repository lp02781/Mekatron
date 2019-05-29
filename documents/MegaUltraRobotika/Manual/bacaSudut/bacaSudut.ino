#include "RTClib.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <SPI.h>
#include <SD.h>
#include <MPU9255.h>
#include "Servo.h"

#define I2C_LCD 0x27

LiquidCrystal_I2C lcd(0x27, 16, 2);

//#define PI    3.14159265358
#define DTR   PI/180.0           // Konversi degree to radian
#define RTD   180.0/PI           // Konversi radian to degree

extern unsigned int speedL, speedR, pwmperiod;
extern long encL, encR, encLold, encRold;
extern float tetaL, tetaR;
//int sudut1, 
int i;

//Untuk PID
float dt=0.02;
float refA=0, errorA=0, integralA=0, derivativeA=0, last_errorA=0;
float refB=0, errorB=0, integralB=0, derivativeB=0, last_errorB=0;
float refC=0;
float kp=3, ki=0, kd=0;
float kp2=10, ki2=0, kd2=0;

//Posisi Awal
float x1 = 0, x2 = 0;
float y1 = 0, y2 = 0;
float z1 = 0, z2 = 0;
float sudut1 = 0, sudut2 = 0, sudut3 = 0;

float aprintf(char *str, ...);

float a;

//define servo and its perks

Servo q1;
Servo q2;
Servo q3;
Servo q4;
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  q1.attach(11);
  q2.attach(10);
  q3.attach(9);
  q4.attach(6);
}

void loop() {
    while(Serial.available()>=1){
    if(Serial.read()==0xF5){
        x1 = Serial.read();
        x2 = Serial.read();
        y1 = Serial.read();
        y2 = Serial.read();
        z1 = Serial.read();
        z2 = Serial.read();
    sudut1 = x1 + x2;
    sudut2 = y1 + y2;
    sudut3 = z1 + z2;
    
//        if (sudut1 > 180) sudut1 = sudut1 - 360;
//        if (sudut2 > 180) sudut2 = sudut2 - 360;

//        lcd.clear();
//        lcd.print(sudut1);
//        lcd.print(" ");
//        lcd.print(sudut2);
  }
  else if(Serial.read()==0xF6){
        x1 = Serial.read();
        x2 = Serial.read();
        y1 = Serial.read();
        y2 = Serial.read();
        z1 = Serial.read();
        z2 = Serial.read();
    sudut1 = -1*(x1 + x2);
    sudut2 = -1*(y1 + y2);
    sudut3 = -1*(z1 + z2);
    
    }
 }
  refA=sudut1;
  refB=sudut2;
  refC=sudut3;
    lcd.setCursor(1,0);
    lcd.print(refA);
    lcd.print(" ");
    lcd.print(refB);
    lcd.print(" ");
    lcd.print(refC);
    lcd.setCursor(1,0);
    digitalWrite(13,LOW);
  delay(100);
  refA = (refA-6.333)/1.1;
  refB = (0.8663*refB-19.86);
  refC = (refC*1.57)+52.07;
  q1.write(refA);
  q2.write(refB);
  q3.write(refC);
}
