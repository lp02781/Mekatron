#include <math.h>
#include "serial.h"
#define PI		3.14159265358
#define DTR 	PI/180.0				   // Conversi degree to radian
#define RTD 	180.0/PI				   // Conversi degree to radian

#define L1  0.08
#define L2	0.08   // link1
#define L3	0.068   // link2
#define L4  0.025
#define L5  0.16
#define L6  0.025

float q1,dq1,q1_cmd=0,q1_awal=q1,err_q1=0,q1_ref=0,dq1_ref=0;
float q2,dq2,q2_cmd=0,q2_awal=q2,err_q2=0,q2_ref=0,dq2_ref=0;
float q3,dq3,q3_cmd=0,q3_awal=q3,err_q3=0,q3_ref=0,dq3_ref=0;
float q4,dq4,q4_cmd=0,q4_awal=q4,err_q4=0,q4_ref=0,dq4_ref=0;
float q5,dq5,q5_cmd=0,q5_awal=q5,err_q5=0,q5_ref=0,dq5_ref=0;
float q6,dq6,q6_cmd=0,q6_awal=q6,err_q6=0,q6_ref=0,dq6_ref=0;
float objx=0.3;
float objy=0.5;
float samplingtime = 0.02, T=0.02, k=0;
float Kp=2010;
int gerak = 0;

void init_robot()
{
	q1=0*DTR;
	q2=90*DTR;
	q3=90*DTR;
	q4=0*DTR;
	q5=0*DTR;
	q6=0*DTR;
	q1_awal=q1;
	q2_awal=q2;
	q3_awal=q3;
	q4_awal=q4;
}
void controlrobot(){
  
  q1_cmd =q1_awal + dq1 * k/(50.0*T);
  err_q1 = q1_cmd - q1;
  dq1_ref = Kp*(err_q1);
  q1_ref = q1_ref + dq1_ref * samplingtime;
  q1 = q1_ref * DTR;
  //printf("q1 = %f   q1_awal = %f   k = %f\n",q1*RTD,q1_awal*RTD,k);
 
  q2_cmd =q2_awal + dq2 * k/(50.0*T);
  err_q2 = q2_cmd - q2;
  dq2_ref = Kp*(err_q2);
  q2_ref = q2_ref + dq2_ref * samplingtime;
  q2 = q2_ref * DTR;
  //printf("q2 = %f   q2_awal = %f   k = %f\n",q2*RTD,q2_awal*RTD,k);
  
  q3_cmd =q3_awal + dq3 * k/(50.0*T);
  err_q3 = q3_cmd - q3;
  dq3_ref = Kp*(err_q3);
  q3_ref = q3_ref + dq3_ref * samplingtime;
  q3 = q3_ref * DTR;
  //printf("q3 = %f   q3_awal = %f   k = %f\n",q3*RTD,q3_awal*RTD,k);
  
  q4_cmd =q4_awal + dq4 * k/(50.0*T);
  err_q4 = q4_cmd - q4;
  dq4_ref = Kp*(err_q4);
  q4_ref = q4_ref + dq4_ref * samplingtime;
  q4 = q4_ref * DTR;
  //printf("q4 = %f   q4_awal = %f   k = %f\n",q4*RTD,q4_awal*RTD,k);
  
  q5_cmd =q5_awal + dq5 * k/(50.0*T);
  err_q5 = q5_cmd - q5;
  dq5_ref = Kp*(err_q5);
  q5_ref = q5_ref + dq5_ref * samplingtime;
  q5 = q5_ref * DTR;
  //printf("q5 = %f   q5_awal = %f   k = %f\n",q5*RTD,q5_awal*RTD,k);
  
  q6_cmd =q6_awal + dq6 * k/(50.0*T);
  err_q6 = q6_cmd - q6;
  dq6_ref = Kp*(err_q6);
  q6_ref = q6_ref + dq6_ref * samplingtime;
  q6 = q6_ref * DTR;
  //printf("q6 = %f   q6_awal = %f   k = %f\n",q6*RTD,q6_awal*RTD,k);
  
  if(q3>90*DTR){
  	q3=90*DTR;
  }
  if (k>=50.0*T)
  {k=0;gerak=0;
  dq1=0; q1_awal=q1;dq2=0; q2_awal=q2;
  dq3=0; q3_awal=q3;dq4=0; q4_awal=q4;
  dq5=0; q5_awal=q5;dq6=0; q6_awal=q6;}

}
void Retrieve_serial(void) {
  int retval=1, i,j,k,l;

  unsigned char sdata[3]; 
  unsigned char baca;
  
  
	i=1;

  while (i>0) {
    fcntl(fd, F_SETFL, FNDELAY); 
    i=read(fd, &baca, 1);
    if ((i==1) && (baca == 0xF5)) {
    	//printf("masuk\n");
    	sdata[0]=baca;
    	while (i<3) {
    		  if (read(fd, &baca, 1)>0) {sdata[i]=baca; i++;}
    	}
   	  //printf("terbaca %x  %x  %x \n",sdata[0],sdata[1],sdata[2]);
   	  q1=(sdata[1])*180.0/255.0*DTR;
   	  q2=(sdata[1])*180.0/255.0*DTR;
   	  q3=(sdata[1])*180.0/255.0*DTR;
   	  q4=(sdata[1])*180.0/255.0*DTR;
   	  q5=(sdata[1])*180.0/255.0*DTR;
   	  q6=(sdata[1])*180.0/255.0*DTR;
    }
  } 

}
