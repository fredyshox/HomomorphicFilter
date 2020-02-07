//
// Created by Kacper Raczy on 2020-01-31.
//

#include <opencv2/opencv.hpp>

namespace hf {

class HighPassFilter {
public:
    virtual cv::Mat createFilter(int rows, int cols, float sigma, float alpha, float beta) const = 0;
    virtual ~HighPassFilter() = default;
};

class GaussianHighPassFilter: public HighPassFilter {
    cv::Mat createFilter(int rows, int cols, float sigma, float alpha, float beta) const override;
};

class ButterworthHighPassFilter: public HighPassFilter {
private:
    int n;
public:
    ButterworthHighPassFilter(int n);
    cv::Mat createFilter(int rows, int cols, float sigma, float alpha, float beta) const override;
};

void homomorphicFilter(const cv::Mat& source, 
                       const cv::Mat& dest, 
                       float sigma, 
                       float alpha, 
                       float beta, 
                       HighPassFilter& hpf, 
                       int borderType = cv::BORDER_REPLICATE);
void dftShift(cv::InputOutputArray _out); 

}

