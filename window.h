#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <memory>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>

class Window
{
public:

    Window(const std::string& name, const std::shared_ptr<cv::cuda::GpuMat>& sourse_mat);
    virtual ~Window();

    void open();
    void close();
    void update();
    std::shared_ptr<const cv::cuda::GpuMat> getMat() const;

protected:
    std::string name_;
    std::shared_ptr<cv::cuda::GpuMat> resurs_;
    std::shared_ptr<cv::cuda::GpuMat> result_;
    bool isOpen_;

    virtual void doWhenCreated();
    virtual void doWhenUpdate();
};

#endif // WINDOW_H
