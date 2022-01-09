#include "image_resize.h"

int main() {
    auto *image = new imageResize("/Users/crd/Desktop/DSC00003.JPG",
                                  "/Users/crd/Desktop/DSC00012.JPG");
    image->run();
}
