/*#include "opencv2/opencv.hpp"
using namespace cv;

int main() {
    Mat img = imread("/Users/yukijudai/Desktop/task2.jpg");    //引号内选一张自己计算机内的图片的路径
    if (img.empty()){
        printf("error the file not found\n");
        return -1;
    }
    imshow("deceye", img);    //打开一个窗口，显示图片
    waitKey(0);    //在键盘敲入字符前程序处于等待状态
    destroyAllWindows();    //关闭所有窗口
    return 0;
}*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
 
using namespace std;
using namespace cv;

Mat src, dst, src_gray, mini_src;

const char* window_name = "Demo";


int main( int argc, char** argv )
{
    src = imread(argv[1], 1 );
    printf("width : %d, higth: %d",src.cols,src.rows);

    /// 将图片转换成灰度图片
    /*cvtColor(src, src_gray, CV_RGB2GRAY);
    namedWindow(window_name, CV_WINDOW_AUTOSIZE);
    imshow(window_name, src_gray);*/
    
    // 缩放图像
    resize(src, mini_src, Size(src.cols / 2, src.rows / 2));
    imshow("mini_src",mini_src);
    printf("mini_src's width: %d, higth: %d", mini_src.cols, mini_src.rows);
    
    // 保存图像
    const char *save_path = "./mini_src.bmp";
    imwrite(save_path, mini_src);
    waitKey(0);    
    destroyAllWindows();   
    return 0;
}