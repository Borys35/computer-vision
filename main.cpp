#include <filesystem>
#include <iostream>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/types.hpp>

int main() {
    std::string path = "../resources/shapes.jpg";
    cv::Mat img = cv::imread(path);

    int t1, t2;

    cv::namedWindow("trackbars",cv::WINDOW_NORMAL);
    cv::createTrackbar("threshold1", "trackbars", &t1, 255);
    cv::createTrackbar("threshold2", "trackbars", &t2, 255);

    while (true) {
        cv::Mat imgOut;
        cv:Canny(img,imgOut,t1,t2);

        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
        cv::dilate(imgOut,imgOut,kernel);

        // cv::imshow("image", img);
        cv::imshow("image out", imgOut);
        cv::waitKey(1);
    }

    return 0;
}