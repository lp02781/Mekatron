#include <ros/ros.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h> // Header file for sleeping.
#include <math.h> 
#include <fcntl.h>			/* File control definitions */
#include <errno.h>			/* Error number definitions */
#include <termios.h>		/* POSIX terminal control definitions */
#include <sys/time.h>
#include <complex.h>
#include <std_msgs/Int16MultiArray.h>
#include "jalan_dong/image_msgs.h"

using namespace std;

int object_x, object_y;

#define PI		3.14159265358
#define DTR 	PI/180.0				   // Conversi degree to radian
#define RTD 	180.0/PI				   // Conversi degree to radian

#define L1  0.08
#define L2	0.08   // link1
#define L3	0.068   // link2
#define L4  0.025
#define L5  0.16
#define L6  0.025
#define L0  0.23 //Link 4 ketika dibagi 2 pergerakan
#define PERIOD 0.001

float q1=30*DTR;
float q2=90*DTR;
float q3=90*DTR;
float q4=0*DTR;
float q5=0*DTR;
float q6=0*DTR;
float q3_servo;
float objx=0.3;
float objy=0.5;
float samplingtime = 0.001, T=0.001;

int gerak = 0, gerak1=0;

float k = 0;
int N = 1000;
float r;
float x_init,y_init, z_init,x_final, y_final, z_final;
float x = 0, x_cmd = 0, x_cmd_old = 0, dx_cmd = 0;
float y = 0, y_cmd = 0, y_cmd_old = 0, dy_cmd = 0;
float z = 0, z_cmd = 0, z_cmd_old = 0, dz_cmd = 0;
float x_old = 0, y_old = 0, z_old = 0,dx = 0, ddx = 0, dy = 0, ddy = 0, dz = 0, ddz = 0;

float dq1 = 0, dq2 = 0, dq3 = 0, dq4 = 0, dq5 = 0, dq6 = 0;
float dq1_ref = 0, dq2_ref = 0, dq3_ref = 0, dq4_ref = 0, dq5_ref = 0, dq6_ref = 0;
float dq1_refold = 0, dq2_refold = 0, dq3_refold = 0, dq4_refold = 0, dq5_refold = 0, dq6_refold = 0;
float ddq1 = 0, ddq2 = 0, ddq3 = 0, ddq4 = 0, ddq5 = 0, ddq6 = 0;
float torque1 = 0, torque2 = 0, torque3 = 0, torque4 = 0, torque5 = 0, torque6 = 0;
float ddq1_ref = 0, ddq2_ref = 0, ddq3_ref = 0, ddq4_ref = 0, ddq5_ref = 0, ddq6_ref = 0;
float dz_ref = 0, dx_ref = 0, dy_ref = 0, dx_refold = 0, dy_refold = 0, dz_refold = 0;
float ddz_ref = 0, ddx_ref = 0, ddy_ref = 0;

int counter = 0;
int divider = 20;

float Kp = 0.009, Kv = 0.6, Ki=0.003;

float qa,qb;

float *tetha1=&q1;
float *tetha2=&q2;
float *tetha3=&q3;
float *theta4=&q4;
float *theta5=&q5;
float *theta6=&q6;

float *tes1=&dq1;
float *tes2=&dq2;
float *tes3=&dq3;
float *tes4=&dq4;
float *tes5=&dq5;
float *tes6=&dq6;

float *count=&k;
float q1_servo;
//deklarasi variabel Jinv
double detJ;
double J11,J12,J13,J14,J15,J16;
double J21,J22,J23,J24,J25,J26;
double J31,J32,J33,J34,J35,J36;

void image_process_cb(const jalan_dong::image_msgs& image);

std_msgs::Int16MultiArray servo;

void init_robot();
void forward_kinematics();
void inverse_jacobian();
void controller();
void double_integrator();
void trajectory_init();
void trajectory_planning();
void hitung_dydz();
void convert();
void convert2();

int main(int argc, char **argv){
	ros::init(argc, argv, "videoRec");
	ros::NodeHandle nh;
	
	ros::Subscriber sub_image_process 	= nh.subscribe("/mekatron/image/process", 1, image_process_cb);
	ros::Publisher pub_servo_pwm 	= nh.advertise<std_msgs::Int16MultiArray>("/mekatron/servo/pwm", 1);
	
	while (ros::ok()) {
		ros::spinOnce();
		
		if (gerak == 1) {
			convert();
			trajectory_init();
			//printf("init y=%.2f z=%.2f\n", y_init, z_init);
			while (k <= N*PERIOD) {
				k += PERIOD;
				counter++;
				if(gerak1!=2){
					trajectory_planning();
					hitung_dydz();
					// inverse_jacobian();
					controller();
					inverse_jacobian();
					double_integrator();
					forward_kinematics();
				}				  
				gerak1=0;
				if (counter%((N/divider)) == 0) {
					printf("%.4f %.4f %.4f %.4f %.4f %.4f %.4f\n",x,y,z, q1*RTD-90, q2*RTD,q3*RTD,q4*RTD);
				}
			}
			gerak = 0;
			convert2();
		}
		servo.data[0] = q1*RTD-90;
		servo.data[1] = q2*RTD;
		servo.data[2] = q3*RTD;
		pub_servo_pwm.publish(servo);
	}
}

void image_process_cb(const jalan_dong::image_msgs& image){
	object_x 		= image.x;
	object_y 		= image.y;
	gerak = 1;
}

void init_robot()
{
	q1=90*DTR;
	q2=90*DTR;
	q3=90*DTR;
	q4=0*DTR;
	q5=0*DTR;
	q6=0*DTR;
}

void forward_kinematics() {

	y=L3*sin(q1) - L2*cos(q2)*sin(q1) + L1*cos(q2)*cos(q3)*sin(q1) + L1*sin(q1)*sin(q2)*sin(q3);
	x=L3*cos(q1) - L2*cos(q1)*cos(q2) + L1*cos(q1)*cos(q2)*cos(q3) + L1*cos(q1)*sin(q2)*sin(q3);
	z=L2*sin(q2) + L1*cos(q2)*sin(q3) - L1*cos(q3)*sin(q2);

  //printf("x = %.2f y = %.2f z = %.2f \n",x,y,z);

}

void inverse_jacobian() {
  // dq1_refold = dq1_ref;
  // dq2_refold = dq2_ref;
  // dq3_refold = dq3_ref;
	
	J11=-(L2*L1*sin(q1)*sin(q3)*cos(q2)*cos(q2) + L2*L1*sin(q1)*sin(q3)*sin(q2)*sin(q2))/(L2*L1*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3));
	J12=(L2*L1*cos(q1)*sin(q3)*cos(q2)*cos(q2) + L2*L1*cos(q1)*sin(q3)*sin(q2)*sin(q2))/(L2*L1*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3));
	J13=0;
	J21=((L1*cos(q2)*cos(q3) + L1*sin(q2)*sin(q3))*(L3*cos(q1) - L2*cos(q1)*cos(q2) + L1*cos(q1)*cos(q2)*cos(q3) + L1*cos(q1)*sin(q2)*sin(q3)))/(L2*L1*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3));
	J22=((L1*cos(q2)*cos(q3) + L1*sin(q2)*sin(q3))*(L3*sin(q1) - L2*cos(q2)*sin(q1) + L1*cos(q2)*cos(q3)*sin(q1) + L1*sin(q1)*sin(q2)*sin(q3)))/(L2*L1*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3));
	J23=-(L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*cos(q3)*sin(q2) - L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q3)*sin(q3) + L1*L1*cos(q2)*cos(q3)*cos(q3)*sin(q1)*sin(q1)*sin(q2) - L1*L1*cos(q1)*cos(q1)*cos(q2)*sin(q2)*sin(q3)*sin(q3) + L1*L1*cos(q1)*cos(q1)*cos(q3)*sin(q2)*sin(q2)*sin(q3) - L1*L1*cos(q2)*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q3) + L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q3) - L1*L1*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q3)*sin(q3) + L1*L1*cos(q3)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L2*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) - L3*L1*cos(q1)*cos(q1)*cos(q2)*sin(q3) + L3*L1*cos(q1)*cos(q1)*cos(q3)*sin(q2) - L3*L1*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L3*L1*cos(q3)*sin(q1)*sin(q1)*sin(q2) - L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*sin(q2) - L2*L1*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q2))/(L2*L1*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3));
	J31=((L1*cos(q2)*cos(q3) - L2*cos(q2) + L1*sin(q2)*sin(q3))*(L3*cos(q1) - L2*cos(q1)*cos(q2) + L1*cos(q1)*cos(q2)*cos(q3) + L1*cos(q1)*sin(q2)*sin(q3)))/(L2*L1*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3));
	J32=((L1*cos(q2)*cos(q3) - L2*cos(q2) + L1*sin(q2)*sin(q3))*(L3*sin(q1) - L2*cos(q2)*sin(q1) + L1*cos(q2)*cos(q3)*sin(q1) + L1*sin(q1)*sin(q2)*sin(q3)))/(L2*L1*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3));
	J33=(L3*L2*cos(q1)*cos(q1)*sin(q2) - L2*L2*cos(q2)*sin(q1)*sin(q1)*sin(q2) + L3*L2*sin(q1)*sin(q1)*sin(q2) - L2*L2*cos(q1)*cos(q1)*cos(q2)*sin(q2) - L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*cos(q3)*sin(q2) + L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q3)*sin(q3) - L1*L1*cos(q2)*cos(q3)*cos(q3)*sin(q1)*sin(q1)*sin(q2) + L1*L1*cos(q1)*cos(q1)*cos(q2)*sin(q2)*sin(q3)*sin(q3) - L1*L1*cos(q1)*cos(q1)*cos(q3)*sin(q2)*sin(q2)*sin(q3) + L1*L1*cos(q2)*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q3) - L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q3) + L1*L1*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q3)*sin(q3) - L1*L1*cos(q3)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L2*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q3) - L2*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L2*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L1*cos(q1)*cos(q1)*cos(q2)*sin(q3) - L3*L1*cos(q1)*cos(q1)*cos(q3)*sin(q2) + L3*L1*cos(q2)*sin(q1)*sin(q1)*sin(q3) - L3*L1*cos(q3)*sin(q1)*sin(q1)*sin(q2) + 2*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*sin(q2) + 2*L2*L1*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q2))/(L2*L1*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q2)*sin(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q3) - L2*L2*L1*cos(q1)*cos(q1)*cos(q2)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q3) - L2*L2*L1*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q1)*cos(q1)*sin(q2)*sin(q2)*sin(q3) + L3*L2*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q3) + L3*L2*L1*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q2)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q2)*cos(q2)*sin(q1)*sin(q1)*sin(q2)*sin(q3)*sin(q3) + L2*L1*L1*cos(q1)*cos(q1)*cos(q2)*cos(q3)*sin(q2)*sin(q2)*sin(q3) + L2*L1*L1*cos(q2)*cos(q3)*sin(q1)*sin(q1)*sin(q2)*sin(q2)*sin(q3));
  
  ddq1_ref = J11*torque1+J12*torque2+J13*torque3;
  ddq2_ref = J21*torque1+J22*torque2+J23*torque3;
  ddq3_ref = J31*torque1+J32*torque2+J33*torque3;

}

void controller() {
  ddx_ref = (dx_ref - dx_refold)/PERIOD;
  ddy_ref = (dy_ref - dy_refold)/PERIOD;
  ddz_ref = (dz_ref - dz_refold)/PERIOD;

  torque1 = Kp*dx_ref + Kv*ddx_ref+Ki*dx_ref*PERIOD;
  torque2 = Kp*dy_ref + Kv*ddy_ref+Ki*dy_ref*PERIOD;
  torque3 = Kp*dz_ref + Kv*ddz_ref+Ki*dz_ref*PERIOD;

}

void double_integrator() {
  // ddq1 = torque1;
  // ddq2 = torque2;
  // ddq3 = torque3;

  dq1 = dq1 + ddq1_ref*PERIOD;
  dq2 = dq2 + ddq2_ref*PERIOD;
  dq3 = dq3 + ddq3_ref*PERIOD;

  q1 = q1 + dq1*PERIOD;
  q2 = q2 + dq2*PERIOD;
  q3 = q3 + dq3*PERIOD;
  
  //q3_servo = q3-(q2-90*DTR);
	
	//printf("q1 = %.2f q2 = %.2f q3 = %.2f \n",q1*RTD,q2*RTD,q3*RTD);
}

void trajectory_init() {
  float d;
  k = 0;
  counter = 0;
  forward_kinematics();
  x_init = x;
  y_init = y;
  z_init = z;
  torque1 = 0;
  torque2 = 0;
  torque3 = 0;

}

void trajectory_planning() {
  x_cmd = x_init + (x_final - x_init)*k/(N*PERIOD);
  y_cmd = y_init + (y_final - y_init)*k/(N*PERIOD);
  z_cmd = z_init + (z_final - z_init)*k/(N*PERIOD);
  //printf("x_cmd = %.2f y_cmd = %.2f z_cmd = %.2f \n",x_cmd,y_cmd,z_cmd);
}

void hitung_dydz() {
  dx_refold = dx_ref;
  dy_refold = dy_ref;
  dz_refold = dz_ref;

  dx_ref = (x_cmd - x)/PERIOD;
  dy_ref = (y_cmd - y)/PERIOD;
  dz_ref = (z_cmd - z)/PERIOD;
}
void convert(){
	float d;
	d=x_final;
	x_final=-y_final;
	y_final=d;
}
void convert2(){
	float d;
	d=x_final;
	x_final=y_final;
	y_final=-d;
}
