#include <iostream>
#include <string>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "HomomorphicFilter.hpp"

using namespace std;

string mainWindow = "Homomorphic filter";
string previewWindow = "Original image";

struct ProgramData {
    cv::Mat image;
    int borderType;
    hf::HighPassFilter* hpf;
    float sigma;
    float alpha;
    float beta;
    int sliderSigma;
    int sliderAlpha;
    int sliderBeta;

    ProgramData(cv::Mat image, int borderType, hf::HighPassFilter* hpf):
        image(image),
        borderType(borderType),
        hpf(hpf)
    {
        this->sigma = 15.0;
        this->alpha = 0.5;
        this->beta = 2.0;
        this->sliderSigma = 15;
        this->sliderAlpha = 5;
        this->sliderBeta = 20;
    }
};

void filterAndShow(ProgramData& pdata) {
    cv::Mat& source = pdata.image;
    cv::Mat dest(source.size(), source.type());
    hf::HighPassFilter* hpf = pdata.hpf;
    hf::homomorphicFilter(source, dest, pdata.sigma, pdata.alpha, pdata.beta, *hpf, pdata.borderType);
    cv::imshow(mainWindow, dest);
    cv::imwrite("./output.jpg", dest);
}

void onSigma(int value, void* userdata) {
    ProgramData* pdata = (ProgramData*) userdata;
    pdata->sigma = (float) value;
    filterAndShow(*pdata);
}

void onAlpha(int value, void* userdata) {
    ProgramData* pdata = (ProgramData*) userdata;
    pdata->alpha = value / 10.0f;
    filterAndShow(*pdata);
}

void onBeta(int value, void* userdata) {
    ProgramData* pdata = (ProgramData*) userdata;
    pdata->beta = value / 10.0f;
    filterAndShow(*pdata);
}

int main(int argc, char** argv) {
    hf::HighPassFilter* hpf = new hf::GaussianHighPassFilter();
    int borderType = cv::BORDER_REPLICATE;
    int opt;
    while ((opt = getopt(argc, (char**) argv, ":b:gcr")) != -1) {
        switch (opt) {
            case 'b':
                delete hpf;
                hpf = new hf::ButterworthHighPassFilter(atoi(optarg));
                break;
            case 'g':
                delete hpf;
                hpf = new hf::GaussianHighPassFilter();
                break;
            case 'c':
                borderType = cv::BORDER_CONSTANT;
                cout << "sdsdff" << endl;
                break;
            case 'r':
                borderType = cv::BORDER_REPLICATE;
                break;
            default: break;
        }
    }

    if (optind >= argc) {
        cout << "Usage: " << argv[0] << " [OPTIONS] <imagefile>" << endl;
        return 1;
    }

    string pathToImage = argv[optind];
    cv::Mat bgrImage = cv::imread(pathToImage);

    if (bgrImage.data == nullptr) {
        cout << "Cannot read image at: " << pathToImage << endl;
        return 2;
    }

    cv::Mat image;
    cv::cvtColor(bgrImage, image, cv::COLOR_BGR2GRAY);
    ProgramData pdata(image, borderType, hpf);
    cv::namedWindow(mainWindow, cv::WINDOW_NORMAL);
    cv::namedWindow(previewWindow, cv::WINDOW_NORMAL);
    cv::createTrackbar("Sigma", mainWindow, &pdata.sliderSigma, 100, onSigma, &pdata);
    cv::createTrackbar("Alpha (/10)", mainWindow, &pdata.sliderAlpha, 100, onAlpha, &pdata);
    cv::createTrackbar("Beta (/10)", mainWindow, &pdata.sliderBeta, 100, onBeta, &pdata);
    cv::imshow(previewWindow, image);
    filterAndShow(pdata);

    cv::waitKey(0);
    cv::destroyAllWindows();
}
