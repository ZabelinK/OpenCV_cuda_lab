#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/opencv.hpp>
#include <memory>
#include <queue>

#include "window.h"

class Filters : public Window
{
public:
    Filters(const std::string& selector_name, const std::shared_ptr<cv::cuda::GpuMat>& resurs);
    Filters(const Filters&);
    Filters& operator=(const Filters&);

private:
    int power_;
    cv::Ptr<cv::cuda::CannyEdgeDetector> canny_;
    void swap(Filters&);

    void doWhenCreated() override;
    void doWhenUpdate() override;
};

#endif // FILTERS_H
