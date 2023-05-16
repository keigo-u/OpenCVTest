#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    cv::Mat baseImg = cv::imread("../dog3.jpg");
    cv::Mat img = cv::imread("../dog1.png");
    cv::Mat outImg;
    cout << baseImg.cols << ":" << baseImg.rows << endl;
    cout << img.cols << ":" << img.rows << endl;
    float colRatio = 0.13;
    float rowRatio = baseImg.rows/img.rows;
    cout << colRatio << ":" << rowRatio << endl;

    cv::resize(img, outImg, cv::Size(), colRatio, colRatio);

    cv::imshow("resized image", img);
    // キーが押されるまで待つ
	cv::waitKey(0);
	//  画像を書き出し
	cv::imwrite("../dog1_resized.png", outImg);	
 

    return 0;
}
