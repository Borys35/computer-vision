#include <filesystem>
#include <iostream>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <opencv4/opencv2/core/mat.hpp>

int main() {
    std::string path = "../resources/shapes.jpg";
    cv::Mat img = cv::imread(path);
    cv::imshow("image", img);
    cv::waitKey(0);

    return 0;
}