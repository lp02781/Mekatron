#include <iostream>
#include <stdio.h>
#include <ros/ros.h>
#include <iostream>
#include "jalan_dong/image_msgs.h"
#include <std_msgs/Int16MultiArray.h>

using namespace std;

FILE *servo_file;
FILE *image_file;

void image_process_cb(const jalan_dong::image_msgs& image);
void pwmCallback(const std_msgs::Int16MultiArray& pwm);

int camera_x, camera_y;
int servo_1, servo_2, servo_3;
int main(int argc, char **argv)
{
	ros::init(argc, argv, "debug_makara");
	ros::NodeHandle nh;
	
	ros::Subscriber sub_pwm = nh.subscribe("/mekatron/servo/pwm", 1, pwmCallback);
	ros::Subscriber sub_camera = nh.subscribe("/mekatron/camera/process", 1, image_process_cb);
	
	while( ros::ok() ){	
		ros::spinOnce();
		
		ROS_INFO("q1:%d\t q2:%d\t q3:%d", servo_1, servo_2, servo_3);
		ROS_INFO("x:%d\t y:%d", camera_x, camera_y);
		ROS_INFO(" ");
		
		servo_file = fopen("../servo.txt","w");
		image_file = fopen("../image.txt","w");
		
		fprintf(servo_file,"%d/%d/%d\n",servo_1,servo_2,servo_3);
		fprintf(image_file,"%d/%d\n",camera_x,camera_y);
			
		sleep(1);
		system("clear");
	}
}
void image_process_cb(const jalan_dong::image_msgs& camera){
	camera_x = camera.x;
	camera_y = camera.y;
}

void pwmCallback(const std_msgs::Int16MultiArray& pwm){
	servo_1 = pwm.data[0];
	servo_1 = pwm.data[1];
	servo_1 = pwm.data[2];
}
