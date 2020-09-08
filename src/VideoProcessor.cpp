//
// Created by Ivan on 2020-09-08.
//

#include "VideoProcessor.h"

#include "opencv2/viz.hpp"


VideoProcessor::VideoProcessor() {
    mCamera = cv::VideoCapture(0);
    mFps = mCamera.get(cv::CAP_PROP_FPS);
    mWidth = static_cast<int>(mCamera.get(cv::CAP_PROP_FRAME_WIDTH));
    mHeight = static_cast<int>(mCamera.get(cv::CAP_PROP_FRAME_HEIGHT));
    mWriter = cv::VideoWriter();

}

void VideoProcessor::capture() {
    if (!mCamera.isOpened()) {
        std::cout << "Error: cant initiate webcam stream" << std::endl;
        return;
    }

    while (true) {
        // grab and retrieve each frames of the video sequentially
        cv::Mat3b frame;
        mCamera >> frame;
        if (frame.empty()) {
            std::cout << "Warning: Empty frame" << std::endl;
            continue;
        }

        cv::imshow("Webcam capture", frame);
        mFrames.push_back(frame);

        if (!nextFrame()) {
            break;
        }
    }
    mCamera.release();
    cv::destroyAllWindows();
}

bool VideoProcessor::save(const std::string &filename) {
    if (!mWriter.open(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), mFps, cv::Size(mWidth, mHeight))) {
        std::cout << "Error: cant open file to write" << std::endl;
        return false;
    }

    for (const auto &frame: mFrames) {
        mWriter.write(frame);
    }
    mFrames.clear();
    mWriter.release();
    return true;
}

bool VideoProcessor::load(const std::string &filename) {
    mCamera = cv::VideoCapture(filename);
    if (!mCamera.isOpened()) {
        std::cout << "Error: can't initiate capture with file" << std::endl;
        return false;
    }

    while (true) {
        cv::Mat3b frame;
        mCamera >> frame;
        if (frame.empty()) {
            break;
        }

        mFrames.push_back(frame);
    }

    return true;
}

void VideoProcessor::draw() {
    for (auto &frame: mFrames) {
        cv::Mat buffer;
        cv::cvtColor(frame, buffer, cv::COLOR_BGR2GRAY);
        cv::cvtColor(buffer, frame, cv::COLOR_GRAY2BGR);

        //draw line
        cv::Point fromLine(mWidth / 3, mHeight - mHeight / 3);
        cv::Point toLine(mWidth - mWidth / 3, mHeight - mHeight / 3);
        cv::line(frame, fromLine, toLine, cv::viz::Color::red(), 2, cv::LINE_AA);


        //draw rect
        cv::Point fromRect(mWidth - mWidth / 4, mHeight / 4);
        cv::Point toRect(mWidth - mWidth / 10, mHeight - mHeight / 4);
        cv::rectangle(frame, fromRect, toRect, cv::viz::Color::bluberry(), 3, cv::LINE_AA);
    }
}

void VideoProcessor::showProcessedCapture() {
    for (auto &frame: mFrames) {
        cv::imshow("Webcam capture", frame);
        //imitate initial fps, e.g. 30 fps <-> 1 frame each 1/30 s <-> 1 frame each 1*1000/30 ms
        int delay = static_cast<int>(1000 / mFps);
        if (!nextFrame(delay)) {
            break;
        }
    }
    cv::destroyAllWindows();
}

bool VideoProcessor::nextFrame(int delay) {
    return cv::waitKey(delay) != 27;
}


