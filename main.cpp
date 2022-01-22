#include "src/color_inversion.h"

int main(int argc, char *argv[]) {
//    auto *threshold = new thresholdPartition("/Users/crd/Code/Data/2/test/DSC00049.JPG");
//    threshold->run();
//    auto *color = new colorInversion("/Users/crd/Code/Data/2/DSC00011.JPG");
    if (argc != 4) {
        std::cout << "参数不正确" << std::endl;
    } else {
        auto *color = new colorInversion(argv[1]);
        color->run(strtol(argv[2], nullptr, 10), argv[3]);
    }

}
