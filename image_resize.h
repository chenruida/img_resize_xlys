//
// Created by 陈瑞达 on 2022/1/8.
//

#ifndef IMAGE_RESIZE_IMAGE_RESIZE_H
#define IMAGE_RESIZE_IMAGE_RESIZE_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

class imageResize {

private:
    /**
     * 原始地址
     */
    std::string srcPath;
    /**
     * 输出地址
     */
    std::string outPath;
    /**
     *
     */
    cv::Mat srcImage;
    cv::Mat outImage;

    /**
     * 印章外边框
     */
    cv::Rect sealRect;

public:
    imageResize(std::string srcPath, std::string outPath);

    void run();

private:
    /**
     * 边框面积大小比较
     * @param contour_1 边框-1
     * @param contour_2 边框-2
     * @return 是否大于
     */
    static bool contourArea(const std::vector<cv::Point> &contour_1, const std::vector<cv::Point> &contour_2);

    /**
     *
     * @param winName 窗口名称
     * @param image images
     * @param contours 边框s
     * @param draw_on_blank 是否在白底上绘制
     */
    static void
    drawMyContours(const std::string &winName, cv::Mat &image, const std::vector<std::vector<cv::Point>> &contours,
                   bool draw_on_blank);

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

    void newSize(cv::)

};


#endif //IMAGE_RESIZE_IMAGE_RESIZE_H
