// Copyright 2021 Napylov Evgenii
#include "../../../modules/task_1/napylov_e_contrast/contrast.h"

void print_vec(const VecImage& vec) {
    for (auto val : vec) {
        std::cout << static_cast<int>(val) << ' ';
    }
    std::cout << std::endl;
}

VecImage RandomVector(int size) {
    static std::mt19937 gen(time(0));
    VecImage result(size);
    std::uniform_int_distribution<unsigned int> distr(0, 255);
    for (int i = 0; i < size; i++) {
        result[i] = static_cast<unsigned char>(distr(gen));
    }
    return result;
}

VecImage add_contrast(VecImage image, unsigned char down, unsigned char up) {
    assert(up > down);
    unsigned char min = *std::min_element(image.begin(), image.end());
    unsigned char max = *std::max_element(image.begin(), image.end());
    if (max == min) {
        return image;
    } else {
        for (size_t i = 0; i < image.size(); i++) {
        image[i] = round((static_cast<double>((image[i] - min))
            / static_cast<double>((max - min))) * (up - down));
        }
        return image;
    }
}
