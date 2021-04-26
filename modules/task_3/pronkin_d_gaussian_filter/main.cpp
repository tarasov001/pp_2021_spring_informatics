#include <gtest/gtest.h>
#include <tbb/tick_count.h>
#include "../../../modules/task_3/pronkin_d_gaussian_filter/gaussian_filter.h"

TEST(TBB, JustTest) {
    std::vector<double> image = getRandomImage(12000, 12000);
    tbb::tick_count start, end;
    std::vector<double> test;
    std::vector<double> res;
    start = tbb::tick_count::now();
    //for (int i = 0; i < 5; i++)
        test = seqGaussianFilter(image, 12000, 12000, 1.0);
    end = tbb::tick_count::now();
    std::cout << "Seq time: " << (end - start).seconds() << "\n";
    start = tbb::tick_count::now();
    //for (int i = 0; i < 5; i++)
        res = parGaussianFilter(image, 12000, 12000, 1.0);
    end = tbb::tick_count::now();
    std::cout << "Par time: " << (end - start).seconds() << "\n";
    ASSERT_EQ(test, res);
}

TEST(TBB, DISABLED_Just) {
    std::vector<double> image = getRandomImage(1000, 1000);
    std::vector<double> test = seqGaussianFilter(image, 1000, 1000, 1.0);
    std::vector<double> img = parGaussianFilter(image, 1000, 1000, 1.0);
    ASSERT_EQ(test, img);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}