// Copyright 2021 Rustamov Azer

#include <random>
#include "../../../modules/task_1/rustamov_a_histogram_stretch/histogram_stretch.h"



Matrix generate_random_image(int w, int h, int bit = 8, int min_y = 50, int max_y = 150) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution<> rnd(min_y, max_y);
    Matrix image(h * w);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            image[i * w + j] = static_cast<int>(rnd(mersenne));
        }
    }
    return image;
}