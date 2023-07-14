#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat gray_img, binary_img;
int low_threshold = 0;

void on_trackbar(int, void* ) {

  // imshow("src", src);

  threshold(gray_img, binary_img, low_threshold, 255, THRESH_BINARY);
  
  // 寻找轮廓
  vector< vector<Point> > contours;
  findContours(binary_img, contours, RETR_LIST, CHAIN_APPROX_NONE);
  cout << contours.size() << endl;
  if (contours.size() > 0) {
    cout << "contours[0].size()   " << contours[0][0] << endl;
  }

  drawContours(binary_img, contours, -1, Scalar(255,255,255), 1, 8);
  imshow("result", binary_img);

}

void Contours_test(char* path) {
  // 读取图像
  Mat img = imread(path);
  if (img.empty())
    cout << "empty" << endl;
  
  // Mat gray_img;

  // int low_threshold = 0;

  cvtColor(img, gray_img, COLOR_BGR2GRAY);
  // imshow("gray_Img", gray_img);
  
  namedWindow("result", WINDOW_AUTOSIZE);
  createTrackbar("threshold", "result", &low_threshold, 255, on_trackbar);
  // imshow("result", gray_img);

  // 直接调用这个函数可以省下自己拉开图片
  on_trackbar(0, 0);

  waitKey(0);
  destroyAllWindows(); 
}