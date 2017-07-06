#ifndef __ZY_H__
#define __ZY_H__


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



class image_processing
{
    public:
            CvBox2D center(int &framecnt,CvCapture *capture);
};

#endif
