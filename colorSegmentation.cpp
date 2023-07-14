#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 读取图像
Mat image;
// 阈值下限
int minH = 0, minS = 0, minV = 0;

// 阈值上限
int maxH = 20, maxS = 20, maxV = 20;
void mask_img(int pos, void* image1){
  
  Mat mask, dilate_img;
  Mat img = *(Mat*)(image1);
  // 定义颜色范围
  Scalar lowerc(minH, minS, minV);
  Scalar upperc(maxH, maxS, maxV);
  inRange(img, lowerc, upperc, mask);
  
  imshow("mask", mask);
  
  // 膨胀
  Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3), Point(-1,-1));
  dilate(mask, dilate_img, kernel);
  
  // 寻找轮廓
  vector< vector<Point> > contours;

  // 层次轮廓
  vector<Vec4i> hierarchy;

  findContours(dilate_img, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

  
  for (int i = 0; i < contours.size(); i++){
    int area = contourArea(contours[i]);
    if (area > 10){
      Rect boundRect = boundingRect(contours[i]);
      rectangle(image, boundRect, Scalar(0,0,255), 2);
    }

  }
  imshow("result", image);
  imshow("img", img);
  
}

void colorSegmentation(char* path) {
  Mat src = imread(path);
  image = src;
  // 转换为hsv图像  
  Mat hsv_img, mask;
  cvtColor(image, hsv_img, COLOR_BGR2HSV);
  imshow("hsv_image", hsv_img);
  
  namedWindow("img", WINDOW_AUTOSIZE);
  createTrackbar("minH", "img", &minH, 180, mask_img, &hsv_img);
  createTrackbar("maxH", "img", &maxH, 180, mask_img, &hsv_img);

  createTrackbar("minS", "img", &minS, 255, mask_img, &hsv_img);
  createTrackbar("maxS", "img", &maxS, 255, mask_img, &hsv_img);

  createTrackbar("minV", "img", &minV, 255, mask_img, &hsv_img);
  createTrackbar("maxV", "img", &maxV, 255, mask_img, &hsv_img);



  
  /*// 位于颜色范围内的设为白色
  inRange(hsv_img, lower_blue, upper_blue, mask);
  
  // 阈值化
  threshold(mask, mask, 1, 255, THRESH_BINARY);

  // 对原始图像应用遮罩
  Mat result;
  bitwise_and(image, image, result, mask);

  // 显示
  imshow("Original image", image);
  imshow("Color Segmentation", result);*/
  waitKey(0);
  destroyAllWindows();
}