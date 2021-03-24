// Copyright 2021 Rustamov Azer

#include <random>
#include <iostream>
// #include "../../../modules/task_1/rustamov_a_histogram_stretch/histogram_stretch.h"
#include "histogram_stretch.h"



Matrix generate_random_image(int w, int h, int min_y, int max_y) {
    if ((w <= 0) || (h <= 0) || (min_y < 0) || (max_y < 0) ||
        (min_y > 255) || (max_y > 255)) {
        throw std::exception("Incorrect input for 'generate_random_image'");
    }
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


Matrix make_histogram(const Matrix& image, int w, int h) {
    if ((w <= 0) || (h <= 0))
        throw std::exception("Incorrect input for 'make_histogram'");
    Matrix histogram(256);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            histogram[image[i * w + j]]++;
        }
    }
    return histogram;
}

void min_max_y(const Matrix& histogram, int* min_y, int* max_y) {
    *min_y = NULL;
    *max_y = NULL;
    for (int i = 0; i < 256; i++) {
        if ((histogram[i] != 0) && (min_y == NULL)) {
            *min_y = i;
            break;
        }
    }
    for (int i = 255; i >= 0; i--) {
        if ((histogram[i] != 0) && (max_y == NULL)) {
            *max_y = i;
            break;
        }
    }
    /*
    std::cout << std::endl;
    std::cout << "Min y = " << min_y << std::endl;
    std::cout << "Max y = " << max_y << std::endl;
    */
}

Matrix stretch_histogram(const Matrix& histogtram, const int* p_min_y, const int* p_max_y) {

    if (*p_min_y >= *p_max_y)
        throw std::exception("Cannot stretch histohram with provided min_y and max_y");
    Matrix result_histogram(256);
    for (int i = min_y; i < max_y + 1; i++) {
        result_histogram[255 * (i - min_y) / (max_y - min_y)] = histogtram[i];
    }
    return result_histogram;
}

Matrix increase_contrast(const Matrix& image, int w, int h, int* p_min_y, int* p_max_y) {
    if ((w <= 0) || (h <= 0))
        throw std::exception("Incorrect input for 'increase_contrast'");
    if ((*p_min_y >= *p_max_y) || ((*p_min_y == 0) && (*p_max_y == 255)))
        throw std::exception("Cannot stretch histohram with provided min_y and max_y");
    Matrix result_image(h * w);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            result_image[i * w + j] = 255 * (image[i * w + j] - *p_min_y) / (*p_max_y - *p_min_y);
        }
    }
    return result_image;
}

Matrix histogram_sretch_algorithm(const Matrix& image, const int w, const int h) {
    if ((w <= 0) || (h <= 0))
        throw std::exception("Incorrect input for 'make_histogram'");
    Matrix histogram = make_histogram(image, w, h);
    int min_y, max_y;
    int* p_min_y = &min_y, * p_max_y = &max_y;
    min_max_y(histogram, p_min_y, p_max_y);
    return increase_contrast(image, w, h, p_min_y, p_max_y);
}
