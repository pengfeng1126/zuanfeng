#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void videoShow(int argc, char* argv) {
  namedWindow("example", WINDOW_AUTOSIZE);
  VideoCapture cap;
  cap.open(argv);
  Mat frame;
  for (;;) {
    cap >> frame;
    if (frame.empty()) {
        break;
    }
    imshow("example", frame);
    if (waitKey(16) >= 0) {
        break;
    }
  }
}