#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(void)
{
    // 画像の読み込み
    cv::Mat im = cv::imread("../images/headPose.jpg");

    // 画像座標系での座標
    std::vector<cv::Point2d> image_points;
    image_points.push_back( cv::Point2d(359, 391) ); // 鼻先
    image_points.push_back( cv::Point2d(399, 561) ); // 顎
    image_points.push_back( cv::Point2d(337, 297) ); // 左目端点
    image_points.push_back( cv::Point2d(513, 301) ); // 右目端点
    image_points.push_back( cv::Point2d(345, 465) ); // 口左端
    image_points.push_back( cv::Point2d(453, 469) ); // 口右端

    // ワールド座標系での座標
    std::vector<cv::Point3d> model_points;
    model_points.push_back(cv::Point3d(0.0f, 0.0f, 0.0f));          // 鼻先
    model_points.push_back(cv::Point3d(0.0f, -330.0f, -65.0f));     // 顎
    model_points.push_back(cv::Point3d(-225.0f, 170.0f, -135.0f));  // 左目端点
    model_points.push_back(cv::Point3d(225.0f, 170.0f, -135.0f));   // 右目端点
    model_points.push_back(cv::Point3d(-150.0f, -150.0f, -125.0f)); // 口左端
    model_points.push_back(cv::Point3d(150.0f, -150.0f, -125.0f));  // 口右端

    // カメラパラメータの設定
    double focal_length = im.cols;
    Point2d center = cv::Point2d(im.cols/2,im.rows/2);
    cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << focal_length, 0, center.x, 0 , focal_length, center.y, 0, 0, 1);
    cv::Mat dist_coeffs = cv::Mat::zeros(4,1,cv::DataType<double>::type); // 歪なし

    cout << "Camera Matrix " << endl << camera_matrix << endl;

    // 回転ベクトルと並進ベクトル
    cv::Mat rotation_vector;
    cv::Mat translation_vector;

    // PnP問題を解く
    cv::solvePnP(model_points, image_points, camera_matrix, dist_coeffs, rotation_vector, translation_vector);

    vector<Point3d> nose_end_point3D;
    vector<Point2d> nose_end_point2D;
    nose_end_point3D.push_back(Point3d(0,0,1000.0));

    // 鼻先の端点を2次元に投影
    projectPoints(nose_end_point3D, rotation_vector, translation_vector, camera_matrix, dist_coeffs, nose_end_point2D);

    // 
    for(int i=0; i < image_points.size(); i++)
    {
        cv::circle(im, image_points[i], 3, cv::Scalar(0,0,255), -1);
    }
    
    cv::line(im,image_points[0], nose_end_point2D[0], cv::Scalar(255,0,0), 2);
 
    cout << "Rotation Vector " << endl << rotation_vector << endl;
    cout << "Translation Vector" << endl << translation_vector << endl;
 
    cout <<  nose_end_point2D << endl;
 
    // 画像の表示
    cv::imshow("Output", im);
    cv::imwrite("../images/output_pose.jpg", im);
    cv::waitKey(0);
}