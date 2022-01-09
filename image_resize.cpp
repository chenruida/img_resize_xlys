//
// Created by 陈瑞达 on 2022/1/8.
//

#include "image_resize.h"

#include <utility>

bool imageResize::contourArea(const std::vector<cv::Point> &contour_1, const std::vector<cv::Point> &contour_2) {
    return cv::contourArea(contour_1) > cv::contourArea(contour_2);
}

void imageResize::drawMyContours(const std::string &winName, cv::Mat &image,
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

imageResize::imageResize(std::string srcPath, std::string outPath) {
    this->srcPath = std::move(srcPath);
    this->outPath = std::move(outPath);
    srcImage = cv::imread(this->srcPath, 1);
}

cv::Mat imageResize::preProcess() {
    cv::Mat gray, binary, element; // 临时变量
    cv::cvtColor(srcImage, gray, CV_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(3, 3), 0);
    cv::medianBlur(gray,gray,3);
    cv::threshold(gray, binary, 200,255,CV_THRESH_BINARY+CV_THRESH_OTSU);
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));//3*3全1结构元素
    cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, element);
    cv::imshow("binary", binary);
    cv::waitKey();
    return binary;

}

void imageResize::findContours(const cv::Mat &binary, std::vector<std::vector<cv::Point>> &contours,
                               std::vector<cv::Vec4i> &hierarchy) {
    cv::findContours(
            binary,               // 输入二值图
            contours,             // 存储轮廓的向量
            hierarchy,            // 轮廓层次信息
            cv::RETR_TREE,            // 检索所有轮廓并重建嵌套轮廓的完整层次结构
            cv::CHAIN_APPROX_NONE);   // 每个轮廓的全部像素
    printf("find %lu contours \n", contours.size());
}

cv::Rect imageResize::filterContours(std::vector<std::vector<cv::Point>> &contours, std::vector<cv::Vec4i> &hierarchy,
                                     int minSize) {
    auto itc = contours.begin();
    auto itc_hierarchy = hierarchy.begin();

    // 1. 使用层级结构筛选轮廓
    int i = 0;
    while (itc_hierarchy != hierarchy.end()) {
        //验证轮廓大小
        if (hierarchy[i][3] > 0) // 存在父轮廓
        {
            itc = contours.erase(itc);
            itc_hierarchy = hierarchy.erase(itc_hierarchy);
        } else {
            ++i;
            ++itc;
            ++itc_hierarchy;
        }
    }
    printf("%lu contours remaining after hierarchy filtering \n", contours.size());
    // 2. 使用轮廓长度滤波
    int min_size = 20;
    int max_size = 30000;
    itc = contours.begin();
    itc_hierarchy = hierarchy.begin();
    while (itc != contours.end()) {
        //验证轮廓大小
        if (itc->size() < min_size || itc->size() > max_size) {
            itc = contours.erase(itc);
            itc_hierarchy = hierarchy.erase(itc_hierarchy);
        } else {
            ++itc;
            ++itc_hierarchy;
        }
    }
    printf("%lu contours remaining after length filtering \n", contours.size());
    // 排序
    sort(contours.begin(), contours.end(), imageResize::contourArea);
    std::cout<<contours[0].size();
    // 矩形
    cv::Rect rect = cv::boundingRect(contours[0]);
    rectTlX = rect.tl().x;
    rectTlY = rect.tl().y;
    rectBrX = rect.br().x;
    rectBrY = rect.br().y;
    std::cout << "左上角X:" << rectTlX << "左上角Y:" << rectTlY << "右下角X:" << rectBrX << "右下角Y:" << rectBrY << std::endl;
    return rect;
}

void imageResize::drawRect(const cv::Rect &rect) {
    cv::Mat result = srcImage.clone();
    cv::rectangle(result, rect, 1, 10);//画矩形
    cv::imshow("bounding", result);
    cv::waitKey();
}

void imageResize::run() {
    cv::Mat binary = preProcess();
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(binary, contours, hierarchy);
    cv::Rect rect = filterContours(contours, hierarchy);
    drawRect(rect);
}



