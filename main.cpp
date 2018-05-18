#include <QCoreApplication>

#include <opencv2/opencv.hpp>

#include "selector.h"
#include "filters.h"
#include "smoothing.h"
#include <opencv2/core/cuda.hpp>
#include <queue>
#include <memory>
#include <iostream>

int main()
{
    cv::VideoCapture cap(0);

    std::shared_ptr<cv::cuda::GpuMat> src(std::make_shared<cv::cuda::GpuMat>());

    Filters filters = Filters("Filter", src);
    filters.open();

    Selector select = Selector("Select", src);
    select.open();

    BlureFace smoothing = BlureFace("Smoothing", src);
    smoothing.open();

    bool loop = true;

    while(loop)
    {
        cv::Mat src2;
        cap >> src2;
        *src = cv::cuda::GpuMat(src2);

        select.update();
        filters.update();
        smoothing.update();

        switch (cvWaitKey(33)) {
        case -1:
            break;

        case 27:
            loop = false;
            break;
        default:
            break;
        }

    }
    cap.release();

    return 0;
}


