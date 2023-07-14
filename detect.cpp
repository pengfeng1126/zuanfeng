#include "detect.h"

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void getContours(Mat imgDil, Mat img) {
  //创建轮廓
  vector<vector<Point> > contours;
  //创建层级轮廓
  // Vec4i:每个向量具有4个整数值
  vector<Vec4i> hierarchy;
  //找到轮廓
  findContours(imgDil, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
  //绘制轮廓
  //绘制所有的，符号为-1,颜色为紫色，厚度为2
  // drawContours(img, contours, -1,Scalar(255, 0, 255),10);
  //过滤噪声点
  for (int i = 0; i < contours.size(); i++) {
    //先找到每个轮廓的面积
    int area = contourArea(contours[i]);
    //打印出面积
    // cout << area << endl;
    //定义轮廓对象的名称
    string objectType;
    //角点向量，仅存储轮廓中的角点
    vector<vector<Point> > conPoly(contours.size());
    //如果面积在可提取范围内，则提取对应轮廓
    if (area > 65) {
      //找到每个轮廓的周长
      float peri = arcLength(contours[i], true);
      //轮廓：contours[i]中包含所有的点
      //而角点：conPoly[i]中仅包含角点
      //如果是矩形，将有4个，三角形则是3个
      approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
      Point2f circlePoint;
      float c_width;
      //定义每个轮廓的角点数
      int objCor = (int)conPoly[i].size();
      if (objCor > 4 && objCor < 50) {
        minEnclosingCircle(conPoly[i], circlePoint, c_width);
        circle(img, circlePoint, c_width, Scalar(0, 255, 0));
      }
    }
  }
}

void detect(char* path) {
  Mat src = imread(path, 1);
  Mat gray_src, canny_src, dil_src;

  imshow("Gaussion_img", src);

  cvtColor(src, gray_src, COLOR_BGR2GRAY);
  namedWindow("src_gray", WINDOW_AUTOSIZE);
  imshow("src_gray", gray_src);

  GaussianBlur(gray_src, gray_src, Size(5, 5), 0, 0);

  Canny(gray_src, canny_src, 30, 200);
  imshow("canny_image", canny_src);

  Mat adaptiveBinary_src;
  adaptiveThreshold(gray_src, adaptiveBinary_src, 255,
                    ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, -2);
  namedWindow("adaptiveThreshold", WINDOW_AUTOSIZE);
  imshow("adaptiveThreshold", adaptiveBinary_src);
  Mat line_src, sobel_src;
  Mat kernel1 = getStructuringElement(MORPH_RECT, Size(5, 5));
  Sobel(adaptiveBinary_src, sobel_src, CV_8U, 0, 1, 3, 1.5, 0);
  imshow("sobel_src", sobel_src);

  dilate(sobel_src, line_src, kernel1, Point(-1, -1), 1);
  imshow("line_src", line_src);

  Mat kernel2 = getStructuringElement(MORPH_RECT, Size(2, 2));
  erode(line_src, line_src, kernel1, Point(-1, -1), 1);
  imshow("erode_line_src", line_src);

  vector<Vec4i> lines;
  HoughLinesP(line_src, lines, 1, CV_PI / 180, 50, 50, 10);
  for (const auto& li : lines) {
    line(src, Point(li[0], li[1]), Point(li[2], li[3]), Scalar(0, 0, 255), 1);
  }

  Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
  Mat erosion, dilation;
  erode(adaptiveBinary_src, erosion, kernel, Point(-1, -1), 1);
  imshow("erode img", erosion);
  dilate(erosion, dilation, kernel, Point(-1, -1), 1);
  imshow("dilate img", dilation);

  getContours(dilation, src);
  imshow("result img", src);
  waitKey(0);
  destroyAllWindows();
}

void detect_back(char* path) {
  Mat src = imread(path, 1);
  cout << "src's " << src.size() << endl;
  cout << src.channels() << endl;
  Mat gray_src, canny_src, dil_src;

  cvtColor(src, gray_src, COLOR_BGR2GRAY);

  namedWindow("src_gray", WINDOW_AUTOSIZE);
  imshow("src_gray", gray_src);

  Mat binary_src;
  int optimal_threshold = threshold(gray_src, binary_src, 0, 255, THRESH_OTSU);
  cout << "the optimal threshold is " << optimal_threshold << endl;
  namedWindow("threshold", WINDOW_AUTOSIZE);
  imshow("threshold", binary_src);
  imwrite("./threshold.bmp", binary_src);

  Mat adaptiveBinary_src;
  adaptiveThreshold(gray_src, adaptiveBinary_src, 255,
                    ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, -2);
  namedWindow("adaptiveThreshold", WINDOW_AUTOSIZE);
  imshow("adaptiveThreshold", adaptiveBinary_src);
  imwrite("./adaptiveThreshold.bmp", adaptiveBinary_src);

  Mat blur_src, boxFilter_src;
  cout << "adaptiveBinary_src's shape" << adaptiveBinary_src.size() << endl;
  blur(adaptiveBinary_src, blur_src, Size(5, 5));
  cout << "blur_src" << blur_src.size() << endl;
  imshow("blur", blur_src);

  boxFilter(adaptiveBinary_src, boxFilter_src, CV_8U, Size(50, 50),
            Point(-1, -1), true, BORDER_DEFAULT);
  imshow("boxFileter", boxFilter_src);

  Mat medianBlur_src, GaussianBlur_src, bilateralFilter_src;
  medianBlur(adaptiveBinary_src, medianBlur_src, 3);
  imshow("medianBlur", medianBlur_src);

  GaussianBlur(adaptiveBinary_src, GaussianBlur_src, Size(3, 3), 0, 0);
  imshow("GaussianBlur_src", GaussianBlur_src);

  bilateralFilter(adaptiveBinary_src, bilateralFilter_src, -1, 50, 50);
  imshow("bilateralFilter", bilateralFilter_src);

  // sobel运算近似梯度，更像是把x方向，y方向的像素值之差做了计算以此作为梯度，边缘检测
  Mat sobel_src;
  Sobel(adaptiveBinary_src, sobel_src, CV_8U, 0, 1, 3, 1.5, 0);
  imshow("sobel", sobel_src);

  Canny(gray_src, canny_src, 30, 200);
  imshow("canny_image", canny_src);

  Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
  Mat erosion, dilation;
  erode(adaptiveBinary_src, erosion, kernel, Point(-1, -1), 1);
  imshow("erode img", erosion);
  dilate(erosion, dilation, kernel, Point(-1, -1), 1);
  imshow("dilate img", dilation);
  // GaussianBlur(dilation, blur_src, Size(3,3), 3, 0);
  getContours(dilation, src);
  imshow("result img", src);
  waitKey(0);
  destroyAllWindows();
}
