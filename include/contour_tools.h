//
// Created by 陈瑞达 on 2022/1/9.
//

#ifndef IMAGE_RESIZE_CONTOUR_TOOLS_H
#define IMAGE_RESIZE_CONTOUR_TOOLS_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

static class contourTools {

public:
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
};


#endif //IMAGE_RESIZE_CONTOUR_TOOLS_H
