#include <LiquidCrystal_I2C.h>
#include "VarSpeedServo.h"

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

float refA=0, errorA=0, integralA=0, derivativeA=0, last_errorA=0;
float refB=0, errorB=0, integralB=0, derivativeB=0, last_errorB=0;
float refC=0, refD=0;

//Posisi Awal
int x0 = 0, x1 = 0, x2 = 0;
int y0 = 0, y1 = 0, y2 = 0;
int z0 = 0, z1 = 0, z2 = 0, a1=0;
float sudut1 = 0, sudut2 = 0, sudut3 = 0, sudut4 = 0,p=0;

float aprintf(char *str, ...);

float a;
float check;
float terima;
//define servo and its perks

VarSpeedServo q1;
VarSpeedServo q2;
VarSpeedServo q3;
VarSpeedServo q4;
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
        x0 = Serial.read(); // buat nentuin sudutnya positifnya pos atau neg
        x1 = Serial.read();
        x2 = Serial.read();
        y0 = Serial.read();
        y1 = Serial.read();
        y2 = Serial.read();
        z0 = Serial.read();
        z1 = Serial.read();
        z2 = Serial.read();
        a1 = Serial.read();
        check = Serial.read();
    terima = x0^x1^x2^y0^y1^y2^z0^z1^z2;
    if(check==terima){
      sudut1 = x1 + x2;
      sudut2 = y1 + y2;
      sudut3 = z1 + z2;
      p=sudut3;
      sudut3 = sudut3 - (sudut2-90);
      sudut4 = a1;
    }
    if(x0==1){
      sudut1=0;
    }
    if(y0==1){
      sudut2=0;
    }
    if(z0==1){
      sudut3=0;
    }
 

  if (refA > 180)
  {
    refA = 180;
  }
  if (refA < 0)
  {
    refA = 0;
  }
  if (refB > 170)
  {
    refB = 170;
    if(refC > 135)
    {
      refC = 135;
    }
    if (refC < 30) //asilnya 80
    {
      refC = 30;
    }
  }
  if (refB < 37)
  {
    refB = 37;
    if (refC > 100) //aslinya 35
    {
      refC = 100;
    }
    if (refC < 20)
    {
      refC = 20;
    }
  }
//        if (sudut1 > 180) sudut1 = sudut1 - 360;
//        if (sudut2 > 180) sudut2 = sudut2 - 360;

//        lcd.clear();
//        lcd.print(sudut1);
//        lcd.print(" ");
//        lcd.print(sudut2);
  }
  
 }

  refA=sudut1;
  refB=sudut2;
  refC=sudut3;
  refD=sudut4;
    lcd.setCursor(1,0);
    lcd.print(refA);
    lcd.print(" ");
    lcd.print(refB);
    lcd.print(" ");
    lcd.print(refC);
    lcd.setCursor(1,1);
    lcd.print(" ");
    lcd.print(p);
    digitalWrite(13,LOW);
  refA = 0.6532*refA - 18.70;
//  refA = (refA-16.333)/1.1;
  refB = (refB-12.333)/1.1;
//  refB = (0.8663*refB-19.86);
  refC = (refC*1.57)+52.07;
  q1.write(100);
  q2.write(refB);
  q3.write(refC);
  q4.write(refD);
  delay(100);
}
