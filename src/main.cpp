#include <iostream>

#include "VideoProcessor.h"


int main() {

    VideoProcessor processor;
    processor.capture();
    if (!processor.save("webcam_output.avi")) {
        std::cout << "ERROR: couldn't save captured video" << std::endl;
        return 1;
    }

    if (!processor.load("webcam_output.avi")) {
        std::cout << "ERROR: couldn't load captured video" << std::endl;
        return 1;
    }

    processor.draw();
    processor.showProcessedCapture();
    processor.save("webcam_output_modified.avi");

    return 0;
}