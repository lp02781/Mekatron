#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH       1000
#define MAX_PULSE_WIDTH       2000
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

uint8_t servonum = 0;

float sudut1 = 0, sudut2 = 50, sudut3 = 60, sudut4 = 0, p=0;
int x0 = 0, x1 = 0, x2 = 0;
int y0 = 0, y1 = 0, y2 = 0;
int z0 = 0, z1 = 0, z2 = 0, a1=0;
float q1,q2,q3,q4;

float refA=0, refB=0, refC=0, refD=0, XOR, terima;

int EN_A = 11;
int in_1 = 9;
int in_2 = 8;

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
//  Serial.println(analog_value);
  return analog_value;
}

void setup() {
  Serial.begin(9600);
//  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  pinMode(EN_A,OUTPUT);
  pinMode(in_1,OUTPUT);
  pinMode(in_2,OUTPUT);

  digitalWrite(in_1,HIGH);
  digitalWrite(in_2,LOW);
  analogWrite(EN_A,65);
}

void loop() {
  while(Serial.available()>=1){
    if(Serial.read()==0xF5){
      XOR = Serial.read();
//        sudut1 = Serial.read();
//        sudut2 = Serial.read();
//        sudut3 = Serial.read();
//        sudut4 = Serial.read();

//        sudut1 = 1.778*sudut1 + 70;
//        sudut2 = 1.778*sudut2 + 70;
//        sudut3 = 1.778*sudut3 + 70;
//        sudut4 = 1.778*sudut4 + 70;
      x0 = Serial.read(); // buat nentuin sudutnya positifnya pos atau neg
      x1 = Serial.read();
//      x2 = Serial.read();
      y0 = Serial.read();
      y1 = Serial.read();
//      y2 = Serial.read();
      z0 = Serial.read();
      z1 = Serial.read();
//      z2 = Serial.read();
      a1 = Serial.read();
      
    
//      terima = x0^x1^x2^y0^y1^y2^z0^z1^z2;
      terima = x0^x1^y0^y1^z0^z1^a1;
      if(XOR==terima){
        sudut1 = x1;
        sudut2 = y1;
        sudut3 = z1;
//        p=sudut3;
//        sudut3 = sudut3 - (sudut2-90);
        sudut4 = a1;
      }
      if(x0==1){
        sudut1= 0;
      }
      if(y0==1){
        sudut2= 0;
      }
      if(z0==1){
        sudut3= 0;
      }


 

//      if (refA > 180){
//        refA = 180;
//      }
//      if (refA < 0){
//        refA = 0;
//      }
//      if (refB > 170){
//        refB = 170;
//      
//        if(refC > 135){
//          refC = 135;
//        }
//        if (refC < 30){
//          refC = 30;
//        }
//      }
//      if (refB < 37){
//        refB = 37;
//      
//        if (refC > 100){
//          refC = 100;
//        }
//        if (refC < 20){
//          refC = 20;
//        }
//      }
    }
  }

  refA=sudut1;
  refB=sudut2;
  refC=sudut3;
  refD=sudut4;
  
//  q1 = refA;
  q2 = refB;
  q3 = refC;
  q4 = refD;

  q1 = 1.636 * refA - 106.4;

//  q1 = 1.51442*q1 + 50.625;
//  q2 = 1.77632*q2-120.78947;
//  q3 = (q3 - (q2-90))*1.55405-67.2973;
//  q4 = refD;

//  if(q2 < 70){
//    q2 = 70;
//  }
//  if(q2 > 135){
//    q2 = 135;
//  }
//  if(q3 < 40){
//    q3 = 40;
//  }
//  if(q3 > 110){
//    q3 = 110;
//  }

  Serial.print(XOR);
  Serial.print(" ");
  Serial.print(terima);
  Serial.print(" ");
  Serial.print(x1);
  Serial.print(" ");
  Serial.print(refA);
  Serial.print(" ");
  Serial.print(sudut1);
  Serial.println(" ");

  pwm.setPWM(0, 0, pulseWidth(q1));
  pwm.setPWM(2, 0, pulseWidth(q2));
  pwm.setPWM(4, 0, pulseWidth(q3));
  pwm.setPWM(6, 0, pulseWidth(q4));

//    for(i=0;i<180;i++){
//      pwm.setPWM(0, 0, pulseWidth(i));
//      delay(250);
//    }
}
