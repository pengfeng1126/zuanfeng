#include "morphology.h"

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void morphology(char* path) {
  Mat img = imread(path, 0);
  imshow("img", img);
  Mat erode_img, dilate_img, morphology_cimg, morphology_oimg;
  Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
  cout << "kernel's value" << kernel << endl;
  erode(img, erode_img, kernel, Point(-1, -1), 1);
  imshow("erode", erode_img);
  dilate(erode_img, dilate_img, kernel, Point(-1, -1), 1);
  imshow("dilate_img", dilate_img);

  morphologyEx(img, morphology_oimg, MORPH_OPEN, kernel, Point(-1, -1), 1);
  imshow("morphologyEx_open", morphology_oimg);

  morphologyEx(img, morphology_cimg, MORPH_CLOSE, kernel, Point(-1, -1), 1);
  imshow("morphologyEx_close", morphology_cimg);

  Mat morphology_gimg;
  morphologyEx(img, morphology_gimg, MORPH_GRADIENT, kernel, Point(-1, -1), 1);
  imshow("morphologyEx_gradient", morphology_gimg);

  Mat topHat, blackHat;
  morphologyEx(img, topHat, MORPH_TOPHAT, kernel, Point(-1, -1), 1);
  imshow("morphologyEx_topHat", topHat);
  morphologyEx(img, blackHat, MORPH_BLACKHAT, kernel, Point(-1, -1), 1);
  imshow("morphologyEx_blackHat", blackHat);
  waitKey(0);
  destroyAllWindows();
}