#include "selector.h"
#include <iostream>
#include <utility>

Selector::Selector(const std::__cxx11::string &selector_name, const std::shared_ptr<cv::cuda::GpuMat> &resurs, const cv::Vec3i &min, const cv::Vec3i &max):
    Window(selector_name, resurs),
    min_(min),
    max_(max)
{}

Selector::Selector(const Selector& selector):
    Window(selector.name_, selector.resurs_),
    min_(selector.min_),
    max_(selector.max_)
{}

Selector& Selector::operator=(const Selector& selector)
{
    Selector tmp(selector);
    Selector::swap(tmp);
    return *this;
}

cv::Scalar Selector::getMin() const
{
    return min_;
}

cv::Scalar Selector::getMax() const
{
    return max_;
}

void Selector::swap(Selector& selector)
{
    std::swap(name_, selector.name_);
    std::swap(resurs_, selector.resurs_);
    std::swap(result_, selector.result_);
    std::swap(min_, selector.min_);
    std::swap(max_, selector.max_);
}

void Selector::doWhenCreated()
{
    cv::createTrackbar("minR", name_, &min_[2], 255);
    cv::createTrackbar("minG", name_, &min_[1], 255);
    cv::createTrackbar("minB", name_, &min_[0], 255);
    cv::createTrackbar("maxR", name_, &max_[2], 255);
    cv::createTrackbar("maxG", name_, &max_[1], 255);
    cv::createTrackbar("maxB", name_, &max_[0], 255);
}

void Selector::doWhenUpdate()
{
    cv::Mat tmp1, tmp2;
    resurs_->download(tmp1);
    cv::inRange(tmp1, min_, max_, tmp2);
    result_->upload(tmp2);
}

