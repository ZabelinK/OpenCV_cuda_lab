#ifndef SELECTOR_H
#define SELECTOR_H

#include <opencv2/opencv.hpp>
#include <memory>
#include "window.h"
//Object for select color in interval, from cv::Mat (image)

class Selector : public Window
{
public:
    Selector(const std::string& selector_name, const std::shared_ptr<cv::cuda::GpuMat>& resurs,
             const cv::Vec3i& min = {0, 0, 0}, const cv::Vec3i& max = {255, 255, 255});
    Selector(const Selector&);
    Selector& operator=(const Selector&);

    cv::Scalar getMin() const;
    cv::Scalar getMax() const;

private:
    cv::Vec3i min_, max_;

    void swap(Selector&);
    void doWhenCreated() override;
    void doWhenUpdate() override;
};
#endif // SELECTOR_H
