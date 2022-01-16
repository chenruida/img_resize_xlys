//
// Created by 陈瑞达 on 2022/1/8.
//

#include "threshold_partition.h"

#include <utility>

thresholdPartition::thresholdPartition(std::string srcPath) {
    this->srcPath = std::move(srcPath);
    srcImage = cv::imread(this->srcPath, 1);
}

cv::Mat thresholdPartition::preProcess() {
    cv::Mat gray, binary, element; // 临时变量
    cv::cvtColor(srcImage, gray, CV_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(3, 3), 0);
    cv::medianBlur(gray, gray, 3);
    cv::threshold(gray, binary, 200, 255, CV_THRESH_BINARY + CV_THRESH_OTSU);
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));//3*3全1结构元素
    cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, element);
//    cv::imshow("binary", binary);
//    cv::waitKey();
    return binary;

}

void thresholdPartition::findContours(const cv::Mat &binary, std::vector<std::vector<cv::Point>> &contours,
                                      std::vector<cv::Vec4i> &hierarchy) {
    cv::findContours(
            binary,               // 输入二值图
            contours,             // 存储轮廓的向量
            hierarchy,            // 轮廓层次信息
            cv::RETR_TREE,            // 检索所有轮廓并重建嵌套轮廓的完整层次结构
            cv::CHAIN_APPROX_NONE);   // 每个轮廓的全部像素
    printf("find %lu contours \n", contours.size());
}

cv::Rect
thresholdPartition::filterContours(std::vector<std::vector<cv::Point>> &contours, std::vector<cv::Vec4i> &hierarchy,
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
    sort(contours.begin(), contours.end(), contourTools::contourArea);
    std::cout << contours[0].size();
    // 矩形
    sealRect = cv::boundingRect(contours[0]);
    std::cout << "左上角X:" << sealRect.tl().x
              << "左上角Y:" << sealRect.tl().y
              << "右下角X:" << sealRect.br().x
              << "右下角Y:" << sealRect.br().y << std::endl;
    return sealRect;
}

void thresholdPartition::drawRect(const cv::Rect &rect) {
    cv::Mat result = srcImage.clone();
    cv::rectangle(result, rect, 1, 10);//画矩形
    cv::imshow("bounding", result);
    cv::waitKey();
}

void thresholdPartition::run() {
    if (srcImage.empty()) {
        std::cout << "没有找到影像" << std::endl;
        return;
    }
    cv::Mat binary = preProcess();
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(binary, contours, hierarchy);
    cv::Rect rect = filterContours(contours, hierarchy);
    drawRect(rect);
}



