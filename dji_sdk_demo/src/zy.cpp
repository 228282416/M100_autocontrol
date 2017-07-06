#include "zy.h"
using namespace std;
using namespace cv;
const int Follow_Flag = 10;
const double delta = 40;
     //CvCapture* capture = cvCreateFileCapture("test5.mp4");
 IplImage* img;
 CvBox2D dt;

CvBox2D detection(IplImage* img);
uint8_t getImageFromMemory(Mat &image);

CvBox2D image_processing:: center(int &framecnt,CvCapture *capture)
    {
    cout<<capture<<endl;  
   // CvCapture* capture = cvCreateCameraCapture(0);

  //  CvCapture* capture = cvCreateFileCapture("test1.mp4");
  //    int framecnt = 0;
     //  Mat img0;  
          
        //    only_once = 1;
        
//       CvCapture* capture = cvCreateCameraCapture(0);
//  CvCapture* capture = cvCreateFileCapture("test1.mp4");
  //    IplImage *img;
//    int framecnt = 0;
 //     CvBox2D dt;
      CvBox2D result;
    result.center.x = 0;
    result.center.y = 0;
    Mat img0;
       img = cvQueryFrame(capture);
			if (img)
			{
			//	printf("ljyshadiao!\n");
//				break;
			

//    		CvBox2D result;
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
				
				cvSetImageROI(img, cvRect(kx, ky, dt.size.height + delta, dt.size.width + delta));//ÉèÖÃžÐÐËÈ€ÇøÓò
				IplImage *img2 = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);//ŽŽœšÒ»žöÐÂµÄÓÃÀŽÏÔÊŸŸÖ²¿
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
				double t = abs(dx - result.center.x) + abs(dy - result.center.y);//ÓëÉÏÒ»Ö¡ÍŒÏñ×ö±ÈœÏ
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
				printf("( %lf , %lf )\n",result.center.x, result.center.y);
				//TarmacSend(result.center.x, result.center.y);
				//cvCircle(&img, Point(result.center.x, result.center.y), 2, CV_RGB(0, 255, 255), 10, 8, 0);
			}


			cvShowImage("djshffdsssszss", img);
			cvWaitKey(30);
        }
	    system("pause");
        return result;
    
}
