#ifndef SMOOTHING_H
#define SMOOTHING_H

#include <memory>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaobjdetect.hpp>
#include "window.h"

class BlureFace : public Window
{
public:
    BlureFace(const std::string& name, const std::shared_ptr<cv::cuda::GpuMat>& source_mat);

private:
    int mat_x, mat_y;
    cv::Ptr<cv::cuda::CascadeClassifier> face_cascade_;

    void doWhenCreated() override;
    void doWhenUpdate() override;
};

#endif // SMOOTHING_H
