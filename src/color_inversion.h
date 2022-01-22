//
// Created by 陈瑞达 on 2022/1/9.
//

#ifndef IMAGE_RESIZE_COLOR_INVERSION_H
#define IMAGE_RESIZE_COLOR_INVERSION_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "contour_tools.h"

class colorInversion {

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
    explicit colorInversion(std::string srcPath);

    /**
     * 主入口
     */
    void run(int threshold, const char *resultPath);
};


#endif //IMAGE_RESIZE_COLOR_INVERSION_H
