#include <iostream>
#include <string>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "HomomorphicFilter.hpp"

using namespace std;

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

    if (optind + 1 >= argc) {
        cout << "Usage: " << argv[0] << " [OPTIONS] <imagefile> <outputfile>" << endl;
        return 1;
    }

    string pathToImage = argv[optind++];
    string pathToOutput = argv[optind];
    cv::Mat bgrImage = cv::imread(pathToImage);
    cv::Mat image;
    cv::extractChannel(bgrImage, image, 2);

    if (image.data == nullptr) {
        cout << "Cannot read image at: " << pathToImage << endl;
        return 2;
    }

    cv::Mat dest(image.size(), image.type());
    hf::homomorphicFilter(image, dest, 15.0, 0.5, 2.0, *hpf, borderType);
    cv::imwrite(pathToOutput, dest);

    return 0;
}
