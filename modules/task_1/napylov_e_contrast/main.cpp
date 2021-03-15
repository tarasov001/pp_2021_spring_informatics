// Copyright 2021 Napylov Evgenii
#include <gtest/gtest.h>
#include "./contrast.h"

TEST(Linear_stretch_contrast, Manual_Calc_1) {
    VecImage image = { 0, 1, 1, 1, 0, 1 };
    VecImage correct = { 0, 255, 255, 255, 0, 255 };
    VecImage res = add_contrast(image);
    for (size_t i = 0; i < image.size(); i++) {
        ASSERT_EQ(res[i], correct[i]);
    }
}

TEST(Linear_stretch_contrast, Manual_Calc_2) {
    VecImage image = { 5, 123, 28, 240 };
    VecImage correct = { 0, 128, 25, 255};
    VecImage res = add_contrast(image);
    for (size_t i = 0; i < image.size(); i++) {
        ASSERT_EQ(res[i], correct[i]);
    }
}

TEST(Linear_stretch_contrast, Manual_Calc_3) {
    VecImage image = { 5, 123, 28, 240 };
    VecImage correct = { 0, 128, 25, 255 };
    VecImage res = add_contrast(image);
    for (size_t i = 0; i < image.size(); i++) {
        ASSERT_EQ(res[i], correct[i]);
    }
}

TEST(Linear_stretch_contrast, Manual_Calc_4) {
    VecImage image = { 1, 2, 3, 4, 5 };
    VecImage correct = {0, 64, 128, 191, 255};
    VecImage res = add_contrast(image);
    for (size_t i = 0; i < image.size(); i++) {
        ASSERT_EQ(res[i], correct[i]);
    }
}

TEST(Linear_stretch_contrast, Random_No_Throw) {
    VecImage image = RandomVector(1920 * 1080);
    VecImage res;
    ASSERT_NO_THROW(res = add_contrast(image));
}
