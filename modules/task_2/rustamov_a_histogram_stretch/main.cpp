// Copyright 2021 Rustamov Azer

#include <gtest/gtest.h>
#include <iostream>
#include "../../../modules/task_2/rustamov_a_histogram_stretch/histogram_stretch.h"

// #include "histogram_stretch.h"



TEST(Histogram_Stretch, Generate_Image_Parallel_1000x1000) {
    int w = 1000, h = 1000;
    double time1, time2, time3;
    time1 = omp_get_wtime();
    Matrix image_seq = generate_random_image(w, h);
    time2 = omp_get_wtime();
    Matrix image_omp = generate_random_image_parallel(w, h);
    time3 = omp_get_wtime();
    std::cout << "TOTAL TIME: " << (time3 - time1) << std::endl <<
                "1: GENERATE RANDOM IMAGE SEQUENTIAL: " << time2 - time1 << std::endl <<
                "2: GENERATE RANDOM IMAGE PARALLEL: " << time3 - time2 << std::endl;
    SUCCEED();
}

TEST(Histogram_Stretch, Correct_Make_Histogram_Parallel) {    
    double time1, time2, time3, time4;
    int w = 500, h = 500;
    time1 = omp_get_wtime();
    Matrix image = generate_random_image_parallel(w, h);
    time2 = omp_get_wtime();
    Matrix hist_seq = make_histogram(image, w, h);
    time3 = omp_get_wtime();
    Matrix hist_omp = make_histogram_parallel(image, w, h);
    time4 = omp_get_wtime();
    std::cout << "TOTAL TIME: " << (time4 - time1) << std::endl <<
                "1: GENERATE RANDOM IMAGE PARALLEL: " << time2 - time1 << std::endl <<
                "2: HISTOGRAM SEQUENTIAL: " << time3 - time2 << std::endl <<
                "3: HISTOGRAM PARALLEL: " << time4 - time3 << std::endl;
    for (int i = 0; i < 256; i++) {
        ASSERT_EQ(hist_seq[i], hist_omp[i]);
    }
}

TEST(Histogram_Stretch, Correct_Stretch_histogram_Parallel) {    
    double time1, time2, time3, time4, time5, time6;
    int min_y, max_y;
    int w = 500, h = 500;
    Matrix str_hist_seq(256), str_hist_omp(256);
    time1 = omp_get_wtime();

    Matrix image = generate_random_image_parallel(w, h);
    time2 = omp_get_wtime();

    Matrix hist_omp = make_histogram_parallel(image, w, h);
    time3 = omp_get_wtime();

    min_y = get_min_y(hist_omp);
    max_y = get_max_y(hist_omp);

    time4 = omp_get_wtime();
    Matrix res_seq = increase_contrast(image, w, h, min_y, max_y);
    time5 = omp_get_wtime();

    Matrix res_omp = increase_contrast_parallel(image, w, h, min_y, max_y);
    time6 = omp_get_wtime();

    std::cout << "TOTAL TIME: " << time6 - time1 << std::endl <<
                "1: GENERATE RANDOM IMAGE PARALLEL: " << time2 - time1 << std::endl <<
                "2: MAKE HISTOGRAM: " << time3 - time2 << std::endl <<
                "3: FIND MIN_Y AND MAX_Y: " << time4 - time3 << std::endl <<
                "4: INCREASE CONTRAST SEQUENTIAL: " << time5 - time4 << std::endl <<
                "5: INCREASE CONTRAST PARALLEL: " << time6 - time5 << std::endl;
                
    for (int i = 0; i < h * w; i++) {
        ASSERT_EQ(res_seq[i], res_omp[i]);
    }
}

TEST(Histogram_Stretch, Correct_Histogram_stretch_Algorithm) {
    int w = 5000, h = 5000;
    double time1, time2, time3, time4;
    time1 = omp_get_wtime();

    Matrix image = generate_random_image_parallel(w, h);
    time2 = omp_get_wtime();

    Matrix result_seq = histogram_sretch_algorithm(image, w, h);
    time3 = omp_get_wtime();

    Matrix result_omp = histogram_sretch_algorithm_parallel(image, w, h);
    time4 = omp_get_wtime();

    std::cout << "TOTAL TIME: " << time4 - time1 << std::endl <<
                "1: GENERATE RANDOM IMAGE PARALLEL: " << time2 - time1 << std::endl <<
                "2: HISTOGRAM STRETCH ALGORITHM SEQUENTIAL: " << time3 - time2 << std::endl <<
                "3: HISTOGRAM STRETCH ALGORITHM PARALLEL: " << time4 - time3 << std::endl <<
                "4: COMPARATIVE ACCELERATION: " << (time3 - time2) / (time4 - time3) << std::endl;

    for (int i = 0; i < h * w; i++) {
        ASSERT_EQ(result_seq[i], result_omp[i]);
    }
}

/*
TEST(Histogram_Stretch, Incorrect_Image) {
    int w = 0, h = 10;
    ASSERT_ANY_THROW(generate_random_image(w, h));
}

TEST(Histogram_Stretch, Histogram_Of_Result_Equal_To_Stretched_Histogram) {
    int w = 100, h = 100;
    Matrix image = generate_random_image(w, h);
    Matrix histogram = make_histogram(image, w, h);
    int min_y, max_y;
    min_y = get_min_y(histogram);
    max_y = get_max_y(histogram);
    Matrix str_histogram = stretch_histogram(histogram, min_y, max_y);
    Matrix result = histogram_sretch_algorithm(image, w, h);
    Matrix res_histogram = make_histogram(result, w, h);
    for (int i = 0; i < 256; i++) {
        ASSERT_EQ(str_histogram[i], res_histogram[i]);
    }
}

TEST(Histogram_Stretch, Correct_Stretching_2x2) {
    int w = 2, h = 2;
    Matrix image = { 0, 1,
                     1, 0 };
    Matrix exp_result = { 0, 255,
                         255, 0 };
    Matrix histogram = make_histogram(image, w, h);
    Matrix result = histogram_sretch_algorithm(image, w, h);
    for (int i = 0; i < h * w; i++) {
        ASSERT_EQ(result[i], exp_result[i]);
    }
}

TEST(Histogram_Stretch, Correct_Stretching_10x10) {
    int w = 10, h = 10;
    Matrix image = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    Matrix exp_result = { 0, 28, 56, 85, 113, 141, 170, 198, 226, 255,
                          0, 28, 56, 85, 113, 141, 170, 198, 226, 255,
                          0, 28, 56, 85, 113, 141, 170, 198, 226, 255,
                          0, 28, 56, 85, 113, 141, 170, 198, 226, 255,
                          0, 28, 56, 85, 113, 141, 170, 198, 226, 255,
                          0, 28, 56, 85, 113, 141, 170, 198, 226, 255,
                          0, 28, 56, 85, 113, 141, 170, 198, 226, 255,
                          0, 28, 56, 85, 113, 141, 170, 198, 226, 255,
                          0, 28, 56, 85, 113, 141, 170, 198, 226, 255,
                          0, 28, 56, 85, 113, 141, 170, 198, 226, 255, };
    Matrix histogram = make_histogram(image, w, h);
    Matrix result = histogram_sretch_algorithm(image, w, h);
    for (int i = 0; i < h * w; i++) {
        ASSERT_EQ(result[i], exp_result[i]);
    }
}


TEST(Histogram_Stretch, Cannot_Stretch_Twice) {
    int w = 100, h = 100;
    Matrix image = generate_random_image(w, h);
    Matrix result = histogram_sretch_algorithm(image, w, h);
    Matrix second_result = histogram_sretch_algorithm(result, w, h);
    for (int i = 0; i < h * w; i++) {
        ASSERT_EQ(result[i], second_result[i]);
    }
}
*/
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
