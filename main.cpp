#include "threshold_partition.h"
#include "color_inversion.h"

int main() {
//    auto *threshold = new thresholdPartition("/Users/crd/Code/Data/2/test/DSC00049.JPG");
//    threshold->run();
//    auto *color = new colorInversion("/Users/crd/Code/Data/2/DSC00011.JPG");
    auto *color = new colorInversion("/Users/crd/Code/Data/2/test/DSC00012.JPG");
    color->run();
}
