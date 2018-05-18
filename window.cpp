#include "window.h"
#include <iostream>
Window::Window(const std::string& name, const std::shared_ptr<cv::cuda::GpuMat>& source_mat):
    name_(name),
    resurs_(source_mat),
    result_(std::make_shared<cv::cuda::GpuMat>(*resurs_)),
    isOpen_(false)
{}

Window::~Window()
{
    if(isOpen_)
    {
        cv::destroyWindow(name_);
    }
}

void Window::open()
{
    if(!isOpen_)
    {
        cv::namedWindow(name_);
        doWhenCreated();
        isOpen_ = true;
    }
}

void Window::close()
{
    if(isOpen_)
    {
        cv::destroyWindow(name_);
    }
}

void Window::update()
{
    doWhenUpdate();

    if(isOpen_)
    {
        cv::Mat tmp;
        result_->download(tmp);
        cv::imshow(name_, tmp);
    }
}

std::shared_ptr<const cv::cuda::GpuMat> Window::getMat() const
{
    return result_;
}

void Window::doWhenCreated()
{}

void Window::doWhenUpdate()
{
    *result_ = *resurs_;
}
