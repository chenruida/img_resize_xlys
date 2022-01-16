//
// Created by 陈瑞达 on 2022/1/9.
//

#include "color_inversion.h"

colorInversion::colorInversion(std::string srcPath) {
    this->srcPath = std::move(srcPath);

    srcImage = cv::imread(this->srcPath, 1);

}

void colorInversion::run() {
    if (srcImage.empty()) {
        std::cout << "没找到影像！";
    }
    cv::Mat gray, binary, hsv; // 临时变量
    cv::GaussianBlur(srcImage, gray, cv::Size(3, 3), 0);
    cv::GaussianBlur(gray, gray, cv::Size(3, 3), 0);
    cv::medianBlur(gray, gray, 3);
    cv::cvtColor(gray, hsv, CV_BGR2HSV);
    cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
    cv::morphologyEx(hsv, hsv, cv::MORPH_DILATE, element);
    cv::Scalar scalarL = cv::Scalar(8, 50, 20);
    cv::Scalar scalarH = cv::Scalar(80, 255, 255);
    cv::Mat mask;
    cv::inRange(hsv, scalarL, scalarH, mask);
    cv::imshow("mask", mask);
//    cv::imshow("hsv", hsv);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(
            mask,               // 输入二值图
            contours,                   // 存储轮廓的向量
            hierarchy,                      // 轮廓层次信息
            cv::RETR_TREE,            // 检索所有轮廓并重建嵌套轮廓的完整层次结构
            cv::CHAIN_APPROX_NONE);   // 每个轮廓的全部像素
    printf("find %lu contours \n", contours.size());


    cv::Mat result = srcImage.clone();
    // 排序
    sort(contours.begin(), contours.end(), contourTools::contourArea);
    std::cout << contours[0].size();
    // 矩形
    sealRect = cv::boundingRect(contours[0]);
    // 凸包
    std::vector<cv::Point> hull;
    cv::convexHull(contours[0], hull);
    cv::polylines(result, hull, true, cv::Scalar(0, 255, 0), 15);//画多边形
    cv::rectangle(result, sealRect, cv::Scalar(255, 0, 0), 15);//画矩形
    cv::imshow("result", result);
    cv::waitKey();
}
