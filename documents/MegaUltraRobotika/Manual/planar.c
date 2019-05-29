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

float q1;
float q2;
float q3;
float q4;
float q5;
float q6;
float objx=0.3;
float objy=0.5;

void init_robot()
{
	q1=0*DTR;
	q2=90*DTR;
	q3=90*DTR;
	q4=0;
	q5=0;
	q6=0;
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
    }
  } 

}
