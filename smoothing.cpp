#include "smoothing.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/cudaarithm.hpp>
#include <iostream>

BlureFace::BlureFace(const std::__cxx11::string &name, const std::shared_ptr<cv::cuda::GpuMat> &source_mat):
    Window(name, source_mat),
    mat_x(21),
    mat_y(21),
    face_cascade_(cv::cuda::CascadeClassifier::create("haarcascade_frontalface_default.xml"))
{}

void BlureFace::doWhenCreated()
{
    cv::createTrackbar("Power", name_, &mat_x, 100);
}

void BlureFace::doWhenUpdate()
{
    *result_ = *resurs_;
    std::vector<cv::Rect> faces;
    cv::cuda::GpuMat frame_gray;

    cv::cuda::GpuMat outRect;
    cv::cuda::cvtColor(*result_, frame_gray, CV_BGR2GRAY);
    cv::cuda::equalizeHist(frame_gray, frame_gray);
    face_cascade_->detectMultiScale(frame_gray, outRect);

    face_cascade_->convert(outRect, faces);
    cv::Ptr<cv::cuda::Filter> gau_filtr = cv::cuda::createGaussianFilter(result_->type(), result_->type(), cv::Size(21,21), mat_x);

    for(size_t i = 0; i < faces.size(); ++i)
    {
       gau_filtr->apply((*result_)(faces[i]), (*result_)(faces[i]));
    }
}
