//
// Created by 陈瑞达 on 2022/1/9.
//

#include "contour_tools.h"

bool contourTools::contourArea(const std::vector<cv::Point> &contour_1, const std::vector<cv::Point> &contour_2) {
    return cv::contourArea(contour_1) > cv::contourArea(contour_2);
}

void contourTools::drawMyContours(const std::string &winName, cv::Mat &image,
                                  const std::vector<std::vector<cv::Point>> &contours,
                                  bool draw_on_blank) {
    cv::Mat temp;
    if (draw_on_blank) // 在白底上绘制轮廓
    {
        temp = cv::Mat(image.size(), CV_8U, cv::Scalar(255));
        //画全部轮廓
        cv::drawContours(temp, contours, -1, 0, 5);
    } else // 在原图上绘制轮廓
    {
        temp = image.clone();
        cv::drawContours(temp, contours, -1, cv::Scalar(0, 0, 255), 1);
    }
    cv::imshow(winName, temp);
    cv::waitKey();
}
