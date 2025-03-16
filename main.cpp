#include <filesystem>
#include <iostream>
#include <vector>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/core/matx.hpp>

void getContours(cv::Mat imgDil, cv::Mat img) {

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRects(contours.size());

    for (int i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        std::string objectType = "rectangle";
        // We can filter out noise if needed

        float perimeter = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], conPoly[i], 0.02 * perimeter, true);
        cv::drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 2);
        boundRects[i] = cv::boundingRect(conPoly[i]);
        // cv::rectangle(img, boundRects[i], cv::Scalar(255, 255, 0), 5);

        if (conPoly[i].size() == 3)
            objectType = "triangle";
        else if (conPoly[i].size() == 4) {
            const float aspRatio = static_cast<float>(boundRects[i].width) / static_cast<float>(boundRects[i].height);
            if (aspRatio == 1.0) {
                objectType = "square";
            }
            else {
                objectType = "rectangle";
            }

        }
        else if (conPoly[i].size() == 5)
            objectType = "pentagon";
        else if (conPoly[i].size() >= 6)
            objectType = "circle";

        cv::putText(img, objectType, { boundRects[i].x, boundRects[i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 0.75, cv::Scalar(0, 0, 0));
    }
}

int main() {
    std::string path = "../resources/shapes2.jpg";
    cv::Mat img = cv::imread(path);

    int t1 = 25, t2 = 75;

    // cv::namedWindow("trackbars",cv::WINDOW_NORMAL);
    // cv::createTrackbar("threshold1", "trackbars", &t1, 255);
    // cv::createTrackbar("threshold2", "trackbars", &t2, 255);

    //while (true) {
        cv::Mat imgOut;
        cv::cvtColor(img, imgOut, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(imgOut, imgOut, cv::Size(7, 7), 0);
        cv:Canny(img,imgOut,t1,t2);

        cv::imshow("img 0", imgOut);

        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::dilate(imgOut,imgOut,kernel);

        cv::imshow("img 1", imgOut);

        getContours(imgOut,img);

        // cv::imshow("image", img);
        cv::imshow("image out", img);
        cv::waitKey(0);
    //}

    return 0;
}