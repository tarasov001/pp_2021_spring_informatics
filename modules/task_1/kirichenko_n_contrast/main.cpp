// Copyright 2021 Kirichenko Nikita
#include <gtest/gtest.h>
#include "./contrast.h"

TEST(Image_contrast, Test1) {
    int l = 2;
    int k = 2;
    Result manual = { 0, 3, 3, 0 };
    Result count = { 0, 254, 254, 0 };
    Result total = Contrast(manual);
    for (int i = 0; i < l * k; i++) {
        ASSERT_NEAR(total[i], count[i], 1);
    }
}
TEST(Image_contrast, Test2) {
    int l = 3;
    int k = 3;
    Result manual = { 0, 3, 5, 7, 9, 6, 8, 10, 14 };
    Result count = { 0, 54, 90, 126, 162, 108, 144, 180, 252 };
    Result total = Contrast(manual);
    for (int i = 0; i < l * k; i++) {
        ASSERT_NEAR(total[i], count[i], 1);
    }
}
TEST(Image_contrast, Test3) {
    int l = 4;
    int k = 4;
    Result manual = { 0, 1, 5, 14, 16, 12, 6, 9, 19, 25, 255, 230, 156, 78, 45, 96 };
    Result count = { 0, 1, 5, 14, 16, 12, 6, 9, 19, 25, 255, 230, 156, 78, 45, 96 };
    Result total = Contrast(manual);
    for (int i = 0; i < l * k; i++) {
        ASSERT_NEAR(total[i], count[i], 1);
    }
}
TEST(Image_contrast, Test4) {
    int l = 5;
    int k = 5;
    Result manual = { 0, 26, 43, 25, 68, 29, 78, 95, 145, 156, 190, 201, 205, 220, 146, 250, 230, 35, 5, 26, 40, 18, 15, 75, 39, 255 };
    Result count = { 0, 26, 43, 25, 68, 29, 78, 95, 145, 156, 190, 201, 205, 220, 146, 250, 230, 35, 5, 26, 40, 18, 15, 75, 39, 255 };
    Result total = Contrast(manual);
    for (int i = 0; i < l * k; i++) {
        ASSERT_NEAR(total[i], count[i], 1);
    }
}
TEST(Image_contrast, Test5) {
    int l = 40;
    int k = 40;
    ASSERT_NO_THROW(RandomM(l, k));
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
