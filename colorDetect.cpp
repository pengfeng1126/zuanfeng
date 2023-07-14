#include "colorDetect.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int hmin = 170, hmax = 180, smin = 43, smax = 255, vmin = 46, vmax = 255;
int g_nStructElementSize = 3;
int g_nGaussianBlurValue = 6;

void colorDetect(char* path)
{
    Mat img = imread(path, 1);    
    Mat imghsv;
    cvtColor(img, imghsv, COLOR_BGR2HSV);//RGB to HSV
    imshow("hsv", imghsv);
    Mat mask;
    inRange(imghsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask);//filter red color
    imshow("mask", mask);
    Mat out2;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), Point(g_nStructElementSize, g_nStructElementSize));
    erode(mask, out2, element); //erode
    imshow("erode", out2);
    Mat gaussian;
    GaussianBlur(out2, gaussian, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1), 0, 0);//模糊化
    imshow("GaussianBlur", gaussian);
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Mat imgcontours;
    Point2f center;
    float radius;
    findContours(gaussian, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    double maxarea = 0;
    int maxareaidx = 0;
    for (int index = contours.size() - 1; index >= 0; index --)// find the maxarea return contour index
    {
    double tmparea = fabs(contourArea(contours[index]));
    if (tmparea > maxarea)
    {
    maxarea = tmparea;
    maxareaidx = index;
    }
    }
    /*minEnclosingCircle(contours[maxareaidx], center, radius);//using index ssearching the min circle
    circle(img, center, (int)radius, Scalar(255,0,0), 3);//using contour index to drawing circle
    imshow("轮廓", img);*/
    waitKey();
    destroyAllWindows();
}
