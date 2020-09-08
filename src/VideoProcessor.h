//
// Created by Ivan on 2020-09-08.
//

#ifndef LAB1_VIDEOPROCESSOR_H
#define LAB1_VIDEOPROCESSOR_H

#include <iostream>
#include "opencv2/opencv.hpp"

class VideoProcessor {

public:
    VideoProcessor();

    void capture();

    bool save(const std::string &filename);

    bool load(const std::string &filename);

    void draw();

    void showProcessedCapture();

private:
    bool nextFrame(int delay = 50);

    cv::VideoCapture mCamera;
    cv::VideoWriter mWriter;

    std::vector<cv::Mat3b> mFrames;

    double mFps = 0;
    int mWidth = 0;
    int mHeight = 0;

};


#endif //LAB1_VIDEOPROCESSOR_H
