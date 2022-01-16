//
// Created by 陈瑞达 on 2022/1/8.
//

#ifndef IMAGE_RESIZE_THRESHOLD_PARTITION_H
#define IMAGE_RESIZE_THRESHOLD_PARTITION_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "contour_tools.h"

class thresholdPartition {

private:
    /**
     * 原始地址
     */
    std::string srcPath;
    /**
     * 原始影像
     */
    cv::Mat srcImage;

    /**
     * 印章外边框
     */
    cv::Rect sealRect;

public:
    /**
     *
     * @param srcPath  原始地址
     * @param outPath  输出地址
     */
    thresholdPartition(std::string srcPath);

    /**
     * 主入口
     */
    void run();

private:
    /**
     * 预处理
     * @return 处理后图像
     */
    cv::Mat preProcess();

    /**
     * 查找轮廓
     * @param binary 二值影像
     * @param contours 存储轮廓的向量
     * @param hierarchy 轮廓层次信息
     */
    static void findContours(const cv::Mat &binary, std::vector<std::vector<cv::Point>> &contours,
                             std::vector<cv::Vec4i> &hierarchy);

    /**
     * 轮廓过滤
     * @param contours 存储轮廓的向量
     * @param hierarchy 轮廓层次信息
     * @param minSize 最小大小
     * @return 矩形边框
     */
    cv::Rect filterContours(std::vector<std::vector<cv::Point>> &contours, std::vector<cv::Vec4i> &hierarchy,
                            int minSize = 2000);

    /**
     *
     * @param rect 矩形边框
     */
    void drawRect(const cv::Rect &rect);

};


#endif //IMAGE_RESIZE_THRESHOLD_PARTITION_H
