#include "touchbar.h"

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int lowth_value = 0, higth_value = 80;
void on_Trackbar_Threshold(int pos, void* usrdata);
void on_Trackbar_Canny(int, void* usrdata);

void touchbar(char* path) {
  Mat srcImage;
  int lowth_count = 20, higth_count = 100;
  srcImage = imread(path);
  cout << "srcImage's channel" << srcImage.channels() << endl;
  cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
  namedWindow("Trackbar_Canny", WINDOW_NORMAL);
  imshow("Trackbar_Canny", srcImage);
  createTrackbar("Canny_HighTh:80-100", "Trackbar_Canny", &higth_value,
                 higth_count, on_Trackbar_Canny, &srcImage);
  createTrackbar("Canny_LowTh:0-20", "Trackbar_Canny", &lowth_value,
                 lowth_count, on_Trackbar_Canny, &srcImage);

  // namedWindow("Threshold", WINDOW_AUTOSIZE);
  imshow("Threshold", srcImage);
  createTrackbar("Threshold:", "Threshold", &lowth_value, higth_count,
                 on_Trackbar_Threshold, &srcImage);
  waitKey(0);
  destroyAllWindows();
}

void on_Trackbar_Threshold(int pos, void* usrdata) {
  Mat srcImage = *(Mat*)(usrdata);
  Mat dstImage;
  threshold(srcImage, dstImage, pos, 255, THRESH_BINARY);
  imshow("Threshold", dstImage);
}

void on_Trackbar_Canny(int, void* usrdata) {
  Mat srcImage = *(Mat*)(usrdata);
  Mat dstImage;
  // Canny(srcImage, dstImage, g_HighTh, g_LowTh);
  Canny(srcImage, dstImage, lowth_value, higth_value);
  imshow("Trackbar_Canny", dstImage);
}