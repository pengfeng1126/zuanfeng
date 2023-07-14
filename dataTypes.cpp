#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void Op_dataTypes() {
  Vec2i v1(10, 5);
  cout << v1 << endl;
  Point2f pf(10.0), pff(pf);
  Point2i pi(0,0);
  cout << pff << endl;

  Scalar s(1,2);
  cout << s << endl;
  
  Rect rec(pi, Size(3,4));
  cout << rec.tl() << rec.br() << endl;

  // 固定矩阵类 已知维度的时候使用
  Matx32f mf = Matx32f::eye();
  cout << mf << endl;
  cout << mf.col(0) << endl;
  cout << mf(0,1) << endl;

  // 固定向量类
  Vec6f v2(9,42,50,12,0,12);
  cout << v2(1) << endl;

  // 动态可变的存储 Mat类表示任意维度的稠密矩阵
  Mat m;
  m.create(3, 2, CV_32FC3);
  cout << m.size() << endl;
  cout << m << endl;

  Mat m1(4, 2, CV_8UC3, Scalar(1,2,3));
  cout << m1 << endl;
  cout << m1.size() << endl;

  Mat affineMatrix = getRotationMatrix2D(cv::Point2f(100, 100), 60, 1.0);
  cout << "affineMatrix" << affineMatrix << endl;
  cout << "affineMatrix's channel" << affineMatrix.channels() << endl;

  Rect roi(Point(0,0), Size(3,1));
  Mat affineRoi(affineMatrix, roi);
  cout << "affineRoi" << affineRoi << endl;
  cout << "affineRoi's val" << affineRoi.at<double>(0,2) << endl;
  
  affineRoi.at<double>(0,2) = 40.0;
  cout << "new affineRoi" << affineRoi << endl;

  m1.at<Vec3b>(3,0) = Vec3b(6,5,4);
  m1.at<Vec3b>(3,0)[0] = 100;

  // mat.ptr<>(x) 返回的是第x行的第一个像素的地址
  // mat.at<>(x,0)返回第x行的第一个像素的值，mat.at<>(x) 返回的是第x个像素点的值
  cout << *(m1.ptr<Vec3b>(3)) << endl;
  cout << m1 << endl;

  // 另一种获取地址的方式，就如传统的c语言一样，获取首地址，通过迭代每一行计算地址
  // 利用迭代器的方式
  int sz[3] = {4,4,4};
  Mat mi(3, sz, CV_32FC3);
  randu(mi, -1.0f, 1.0f);

  float max = 0.0;
  float len2;
  MatConstIterator_<cv::Vec3f> it = mi.begin<Vec3f>();
  while(it != mi.end<Vec3f>()) {
    len2 = (*it)[0]*(*it)[0] + (*it)[1]*(*it)[1] + (*it)[2]*(*it)[2];
    if (len2 > max) 
      max = len2;
    it++;
  }
  
  // 另一种迭代器NAryMatlterator，不再返回单独的元素，而是返回一堆数组进行迭代，这些数组被称为面，
  // 有多少个面根据不连续的地址来看
  const int n_mat_size = 5;
  const int n_mat_sz[] = {n_mat_size, n_mat_size, n_mat_size};
  Mat n_mat(3, n_mat_sz, CV_32FC1);

  RNG rng;
  rng.fill(n_mat , cv::RNG::UNIFORM, 0.0, 1.0);

  // arrays指向所有我们想要迭代的Mat指针数组，它必须以0或NULL结尾
  const Mat* arrays[] = {&n_mat, 0};

  // 第二个需要一个可以作为面的参考的c风格的Mat数组，从而可以通过它们迭代
  // 数组长度为1，因为只有一个数组需要迭代
  Mat my_planes[1];
  NAryMatIterator its(arrays, my_planes);
  float s1 = 0.0;
  int n = 0;
  cout << "  its.nplanes  " << its.nplanes << endl;
  for (int p = 0; p < its.nplanes; p++, ++it) {
    s1 += cv::sum(its.planes[0])[0];
    n++;
  }
  cout << " n_mat.isContinuous is " << n_mat.isContinuous() << endl;
  //cout << "n_mat" << n_mat << endl;
  cout << "s1" << s1 << endl;

  // 通过块访问数组元素
  // 将一个数组的子集作为另一个数组访问，这个子集可能是一列或一行，也可能是一个子集
  Mat m23(4, 2, CV_32FC1);
  randu(m23, 0, 255);
  cout << "m23" << m23 << endl;
  cout << "m23.col(1)" << m23.col(1) << endl;
  cout << "m23.row(2)" << m23.row(2) << endl;

  // 这个是左闭右开的 （0，1-1）
  cout << "m23.rowRange(0,1)" << m23.rowRange(0,1) << endl;
  
  cout << "m23.diag(0)" << m23.diag(0) << endl;
  cout << "m23.diag(1)" << m23.diag(1) << endl;
  
  cout << "m23(Rect(0,0,2,1))" << m23(Rect(0,0,2,1)) << endl;
  cout << "m23(Rect(0,0,1,2))" << m23(Rect(0,0,1,2)) << endl;
  //cout << "m23(Range(0,0), Range(2,1))" << m23(Range(0,0), Range(2,1)) << endl;
  
  // 矩阵表达式 运算符重载
  Mat m23base = m23 + m23;
  cout << "m23base" << m23base << endl;
  
  cout << "m23 + 1" << m23 + 1 << endl;
  
  cout << "m23.t()" << m23.t() << endl;

  cout << "m23 * m23.t()" << m23 * m23.t() << endl;

  Mat_<Vec2b> mmm(2,2);
  mmm(0,0) = Vec2b(1,2);
  cout << "mmm" << mmm << endl;

  

}