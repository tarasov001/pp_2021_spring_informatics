// Copyright 2021 Rustamov Azer

//#include <gtest/gtest.h>
#include <iostream>
#include "./histogram_stretch.h"

int main() {
    std::cout << "START" << std::endl;
    int w = 10;
    int h = 10;
    Matrix image = generate_random_image(w, h);
    for(int i = 1; i < w; i++) {
        for(int j = 0; j < h; j++) {
            std::cout << image[i * w + j] << "; ";
        }
        std::cout << std::endl;
    }
}