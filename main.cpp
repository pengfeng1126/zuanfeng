#include <detect.h>
#include <touchbar.h>

#include <iostream>
#include <vector>
#include "ImageTransformation.h"
#include "colorDetect.h"
#include "colorSegmentation.h"
#include "morphology.h"
#include "ViedoCapture.h"
#include "dataTypes.h"
#include "ContoursTest.h"

using namespace std;
  // 关于二值图像的理解，所有非0像素都是一个定值
int main(){
  vector< vector<int> > matrix;
  printf("hello world");
  char* path = "./mini_src.bmp";
  char* pth = "/Users/yukijudai/Documents/Amaze.mp4";
  // detect(path);
  // touchbar(path);
  // char* threshold_path = "./threshold.bmp";
  // morphology(threshold_path);
  // colorSegmentation(path);
  // ImageTransformation(path);
  // videoShow(1,pth);
  // Op_dataTypes();
  Contours_test(path);
  return 0;
}
