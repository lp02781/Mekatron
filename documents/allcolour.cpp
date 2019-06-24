//preprocessor
#include <iostream>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//namespace
using namespace cv;
using namespace std;

//matrix
Mat imgOriginal, imgHSV, imgThresholded, imgErode, imgDilate;

//hue
int LowH = 170;
int HighH = 179;

//saturation
int LowS = 150; 
int HighS = 255;

//value
int LowV = 60;
int HighV = 255;

//posisi awal dan akhir
int a = 0;
int b = 0;

//minimal pixel dan box
int minPix = 10;
int minBox = 100;

int value = 0;

double posisiAkhir = 320;//posisi akhir

int mx,my;//nilai koordinat
int mflags=0;//0

int main( int argc, char** argv )
{
	VideoCapture cap(0);//webcam
	
	if ( !cap.isOpened() )  // jika tidak terbaca, exit
    {
         cout << "webcam tidak terbaca" << endl;
         return -1;
    }
	
	cap.read(imgOriginal);//capture di imgOriginal
    namedWindow("ColourTracking", CV_WINDOW_AUTOSIZE);//nama window
	
	//trackbar
	createTrackbar("LowH", "ColourTracking", &LowH, 255); //Hue (0 - 255)
	createTrackbar("HighH", "ColourTracking", &HighH, 255);
	createTrackbar("LowS", "ColourTracking", &LowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "ColourTracking", &HighS, 255);
	createTrackbar("LowV", "ColourTracking", &LowV, 255);//Value (0 - 255)
	createTrackbar("HighV", "ColourTracking", &HighV, 255);
	printf("Hue values of basic colors\n Orange  0-22\n Yellow 22- 38\n Green 38-75\n Blue 75-130\n Violet 130-160\n Red 160-179\n");
	
	while (true)//loop sampai exit
    {
		bool bSuccess = cap.read(imgOriginal); // membaca frame baru dari video
		if (!bSuccess) //jika tidak sukses, menghentikan loop
        {
             cout << "tidak bisa membaca frame dari video" << endl;
             break;
        }
		
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //mengubah frame BGR jadi HSV
		inRange(imgHSV, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), imgThresholded);//range threshold
		
		//hapus objek kecil
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
		
		//menghapus hole
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
		
		Moments mu=moments(imgThresholded);
		int area = mu.m00; // sum of zero'th moment is area
		int posX = mu.m10/area; // center of mass = w*x/weight
		int posY = mu.m01/area;// center of mass = w*y/high
		area /= 255; // scale from bytes to pixels	
		
		if (area > 0){
			value = 1;
			cout<<value<<"\t"<<posX<<"\t"<<posY<<endl;
		}
		else{
			value = 0;
			cout<<value<<endl;
		}
		//menampilkan image
		imshow("Threshold", imgThresholded);
		imshow("Original", imgOriginal); 
        
        if (waitKey(30) == 27) //exit esc
        {
            cout << "esc di tekan" << endl;
            break; 
        }
	}
	return 0;
}
