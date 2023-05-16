#include<iostream>
#include<cmath>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main (void)
{
    // 画像データの読み込み
    cv::Mat img1 = cv::imread("../images/dog1_original.jpg");
    cv::Mat img2 = cv::imread("../images/dog1_rotate.png");

    // A-KAZE検出器の生成
    cv::Ptr<cv::AKAZE> akaze = cv::AKAZE::create();

    // 特徴量(keypoints)と特徴量描画(descriptors)を用意
    std::vector<cv::KeyPoint> kp1;
    std::vector<cv::KeyPoint> kp2;
    cv::Mat des1;
    cv::Mat des2;

    // 画像を読み込み特徴量を計算
    akaze->detectAndCompute(img1, cv::noArray(), kp1, des1);
    akaze->detectAndCompute(img2, cv::noArray(), kp2, des2);

    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector<std::vector<cv::DMatch>> nn_matches;
    matcher.knnMatch(des2, des1, nn_matches, 2);
    
    std::cout << "nn_matches.size()=" << nn_matches.size() << std::endl;

    const float ratio_thresh = 0.3f;
    std::vector<cv::DMatch> good_matches;
    for (size_t i = 0; i < nn_matches.size(); i++)
    {
        if (nn_matches[i][0].distance < ratio_thresh * nn_matches[i][1].distance)
        {
            good_matches.push_back(nn_matches[i][0]);
        }
    }

    cv::Mat matches_image;
    cv::drawMatches(img2, kp2, img1, kp1, good_matches, matches_image, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    cv::imshow("Good Matches & Object detection", matches_image);

    // キーが押されるまで待つ
	cv::waitKey(0);

    return 0;
}