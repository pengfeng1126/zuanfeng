#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void ImageTransformation(char* path){
  
  Mat img = imread(path);
  Mat res_img;

  // 均匀调整
  resize(img, res_img, Size(480,270), 0, 0, 1);
  cout << "img.size" << img.size() << "res_img.size()" << res_img.size() << endl;
  resize(img, res_img, Size(0,0), 0.5, 1, 1);
  cout << "size" << img.size() << "size()" << res_img.size() << endl; 

  // 图像金字塔
  Mat down_img;
  vector<Mat> pyramid_img;
  pyrDown(img, down_img);
  cout << down_img.size() << "down_img.size()" << endl;

  buildPyramid(img, pyramid_img, 3);
  cout << pyramid_img[3].size() << "up_img[3].size()" << endl;
  
  Mat up_img;
  pyrUp(img, up_img, Size(960 * 2, 540 * 2));
  cout << "up_img.size()" << up_img.size() << endl;

  // 密集仿射变换(密集的意思是适用于图像)
  Mat affine_img, affine_matrix;
  Point2f center(img.cols / 2, img.rows / 2);
  double theta = 45;

  // 第一种产生仿射变换矩阵的方式
  affine_matrix = getRotationMatrix2D(center, theta, 1.0);
  warpAffine(img, affine_img, affine_matrix, Size(img.cols, img.rows));
  imshow("affine_img", affine_img);

  // 第二种
  // 定义源图像上的三个点和目标图像上对应的三个点
  cv::Point2f srcPoints[3];
  cv::Point2f dstPoints[3];

  srcPoints[0] = cv::Point2f(50, 50);
  srcPoints[1] = cv::Point2f(200, 50);
  srcPoints[2] = cv::Point2f(50, 200);

  dstPoints[0] = cv::Point2f(100, 100);
  dstPoints[1] = cv::Point2f(250, 100);
  dstPoints[2] = cv::Point2f(100, 250);

  affine_matrix = getAffineTransform(srcPoints, dstPoints);
  warpAffine(img, affine_img, affine_matrix, img.size());
  imshow("second", affine_img);

  // 第三种 简单粗暴 直接赋值生成
  Mat t_mat =cv::Mat::zeros(2, 3, CV_32FC1);
 
  t_mat.at<float>(0, 0) = 1;
  t_mat.at<float>(0, 2) = 20; //水平平移量
  t_mat.at<float>(1, 1) = 1;
  t_mat.at<float>(1, 2) = 10; //竖直平移量
  warpAffine(img, affine_img, t_mat, img.size()); 
  imshow("third", affine_img);

  // 稀疏仿射变化（作用于一系列的点，单个点列表的映射）
  vector<Point2f> srcPoint;
  srcPoint.push_back(cv::Point2f(50, 50));
  srcPoint.push_back(cv::Point2f(200, 50));
  srcPoint.push_back(cv::Point2f(50, 200));

  Mat affineMatrix = getRotationMatrix2D(cv::Point2f(100, 100), 45, 1.0);

  vector<Point2f> dstPoint;
  transform(srcPoint, dstPoint, affineMatrix);

  // 求取仿射变化的逆变换矩阵，逆变换可以将仿射变换后的图像或点集恢复到原始状态
  Mat invertMatrix;
  invertAffineTransform(affineMatrix, invertMatrix);
  
  //再使用 一次transform即可完成逆变换

  //透视变换
  
  waitKey(0);
  destroyAllWindows();
} 


