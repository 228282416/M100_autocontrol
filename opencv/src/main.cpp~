#include "ros/ros.h"
#include "std_msgs/String.h"
#include <opencv/Center.h>

#include <stdlib.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

const int Follow_Flag = 10;
const double delta = 40;
//struct Center
//{
//    double x = 0;
//    double y = 0;
//}z_center;

CvBox2D detection(IplImage* img);

int main(int argc,char **argv)
{
	CvCapture* capture = cvCreateCameraCapture(0);
	//CvCapture* capture = cvCreateFileCapture("test5.mp4");
	IplImage* img;
	int framecnt = 0;//识别到的帧数，大于Follow_Flag时进入跟随模式
	CvBox2D dt;
	Mat img0;
    opencv::Center center_1; 
    ros::init(argc,argv,"opencv");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<opencv::Center>("chatter",10);
	while (ros::ok())
	{
			img = cvQueryFrame(capture);
			if (!img)
			{
				printf("ljyshadiao!\n");
				break;
			}

			CvBox2D result;
			if (framecnt >= Follow_Flag)
			{
				double kx = dt.center.x - dt.size.height / 2 - delta / 2;
				double ky = dt.center.y - dt.size.width / 2 - delta / 2;
				if (kx < 0) kx = 0;
				if (ky < 0) ky = 0;
				
				cout <<"kx : "<<kx<<endl;
				cout <<"ky : "<<ky<<endl;
				cout <<"height : "<<dt.size.height + delta<<endl;
				cout <<"width"<<dt.size.width<<endl;
				
				cvSetImageROI(img, cvRect(kx, ky, dt.size.height + delta, dt.size.width + delta));//设置感兴趣区域
				IplImage *img2 = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);//创建一个新的用来显示局部
				cvCopy(img, img2, NULL);
				cvResetImageROI(img);

				result = detection(img2);
				cvReleaseImage(&img2);
				if (result.center.x == -1 && result.center.y == -1)
				{
					result = detection(img);
					dt = result;
					framecnt = 1;
				}
				else{
					result.center.x += kx;
					result.center.y += ky;
					dt = result;
					framecnt = 11;
				}
			}
			else{
				result = detection(img);
				double dx = dt.center.x;
				double dy = dt.center.y;
				double t = abs(dx - result.center.x) + abs(dy - result.center.y);//与上一帧图像做比较
				if ((result.center.x == -1 && result.center.y == -1) || t > delta)
				{
					framecnt = 1;
				}
				else framecnt++;
				dt = result;
			}
			//cout << framecnt << endl;
			//cout << result.center.x << ' ' << result.center.y << endl;
			

			if (result.center.x != -1 && result.center.y != -1)
			{
       		    center_1.x = result.center.x;
       		    center_1.y = result.center.y;
       		    chatter_pub.publish(center_1);
           	    ros::spinOnce();
				printf("( %lf , %lf )\n",center_1.x, center_1.y);
				//TarmacSend(result.center.x, result.center.y);
				//cvCircle(&img, Point(result.center.x, result.center.y), 2, CV_RGB(0, 255, 255), 10, 8, 0);
			}

           
			cvShowImage("djshffdsssszss", img);
			cvWaitKey(30);
	}
	system("pause");
	return 0;
}
