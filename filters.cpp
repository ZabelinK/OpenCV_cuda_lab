#include "filters.h"
#include <iostream>
#include <utility>

Filters::Filters(const std::__cxx11::string &name, const std::shared_ptr<cv::cuda::GpuMat> &resurs):
    Window(name, resurs),
    power_(1),
    canny_(cv::cuda::createCannyEdgeDetector(2, 100))
{}

Filters::Filters(const Filters & filters):
    Window(filters.name_, filters.resurs_)
{}

Filters &Filters::operator=(const Filters & filters)
{
    Filters tmp(filters);
    Filters::swap(tmp);
    return *this;
}

void Filters::swap(Filters & filter)
{
    std::swap(name_, filter.name_);
    std::swap(resurs_, filter.resurs_);
    std::swap(result_, filter.result_);
}

void Filters::doWhenCreated()
{
    cv::createTrackbar("Power", name_, &power_, 100);
}

void Filters::doWhenUpdate()
{
    cv::Mat src, gray, det, dst;
    resurs_->download(src);

    cv::cvtColor(src, gray, CV_BGR2GRAY);
    cv::blur(gray, det, cv::Size(3,3));

    cv::Canny(det, det, power_, power_ * 3, 3);

    dst.create(src.size(), src.type());
    dst = cv::Scalar::all(0);

    src.copyTo(dst, det);
    cv::subtract(src, dst, dst);

    result_->upload(dst);
}
