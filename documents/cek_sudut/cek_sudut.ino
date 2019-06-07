#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH       1000
#define MAX_PULSE_WIDTH       2000
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  
}

void loop() {
//  pwm.setPWM(0, 0, pulseWidth(0));
//  Serial.println("0");
//  delay(500);
//  pwm.setPWM(0, 0, pulseWidth(45));
//  Serial.println("45");
//  delay(500);
//  pwm.setPWM(0, 0, pulseWidth(90));
//  Serial.println("90");
//  delay(500);
//  pwm.setPWM(0, 0, pulseWidth(135));
//  Serial.println("135");
//  delay(500);
//  pwm.setPWM(0, 0, pulseWidth(180));
//  Serial.println("180");
//  delay(500);
//  pwm.setPWM(0, 0, pulseWidth(135));
//  Serial.println("135");
//  delay(500);
//  pwm.setPWM(0, 0, pulseWidth(90));
//  Serial.println("90");
//  delay(500);
//  pwm.setPWM(0, 0, pulseWidth(45));
//  Serial.println("45");
//  delay(500);

    for(i=0;i<180;i++){
      pwm.setPWM(0, 0, pulseWidth(i));
      delay(250);
    }
}

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  Serial.println(analog_value);
  return analog_value;
}
