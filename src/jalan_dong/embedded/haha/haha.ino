#include <ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <Stepper.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver(0x40);

#define trigPin 13
#define echoPin 12

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

ros::NodeHandle  nh;
std_msgs::Int16MultiArray pwm_msg;

int pwm_servo_1;
int pwm_servo_2;
int pwm_servo_3;

int pwmRisingTime = 0;
int pwmFallingTime = 0;

void messageCb( const std_msgs::Int16MultiArray& msg){
  pwm_servo_1=msg.data[0];
  pwm_servo_2=msg.data[1];
  pwm_servo_3=msg.data[2];
}

void ambil_posisi();
void tutup_gripper();
void taruh_barang();
void buka_gripper();

ros::Subscriber<std_msgs::Int16MultiArray> sub("/mekatron/servo/pwm", &messageCb );

void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myStepper.setSpeed(60);

  pwmDriver.begin();
  pwmDriver.setPWMFreq(51);
}

void loop()
{  
  nh.spinOnce();
  myStepper.step(stepsPerRevolution);
  delay(500);
  
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if(distance < 20){
    buka_gripper();
    ambil_posisi();
    tutup_gripper();
    taruh_barang();
    buka_gripper();
  }
  delay(1);
}

void ambil_posisi(){
  pwmFallingTime = map(pwm_servo_1, 0, 180, 0, 4096);
  pwmDriver.setPWM(1, pwmRisingTime, pwmFallingTime);
  pwmFallingTime = map(pwm_servo_2, 0, 180, 0, 4096);
  pwmDriver.setPWM(2, pwmRisingTime, pwmFallingTime);
  pwmFallingTime = map(pwm_servo_3, 0, 180, 0, 4096);
  pwmDriver.setPWM(3, pwmRisingTime, pwmFallingTime);
}

void tutup_gripper(){
  pwmDriver.setPWM(4, 0, 4096);
}

void buka_gripper(){
  pwmDriver.setPWM(4, 0, 0);
}

void taruh_barang(){// masih asal
  pwmDriver.setPWM(4, 0, 0);
  pwmFallingTime = 500;
  pwmDriver.setPWM(1, pwmRisingTime, pwmFallingTime);
  pwmDriver.setPWM(2, pwmRisingTime, pwmFallingTime);
  pwmDriver.setPWM(3, pwmRisingTime, pwmFallingTime);
}
