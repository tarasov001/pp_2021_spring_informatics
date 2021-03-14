// Copyright 2021 Shagov Maksim
#include "../../../modules/task_1/shagov_m_fox/fox.h"

bool is_equal(double x, double y) {
    return std::fabs(x - y) < 0.0001;
}

bool isEqualMatrix(Matrix A, Matrix B) {
    if ((A.size() <= 0) || (B.size() <= 0)) {
        throw "Size of matrix must be > 0";
    }
    if (A.size() != B.size()) {
        throw "Different size of matrix";
    }
    size_t size = A.size();
    for (size_t i = 0; i < size; i++) {
        if(!is_equal(A[i], B[i]))
            return false;
    }
    return true;
};

Matrix createRandomMatrix(size_t size) {
    if (size <= 0) {
        throw "Size of matrix must be > 0";
    }
    Matrix result(size, 0);
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<> urd(-100000.0, 100000.0);
    for (size_t i = 0; i < size; i++) {
        result[i] = static_cast<double>(urd(mersenne));
    }
    return result;
};

Matrix sequentialMatrixmultiplication(std::vector<double> A, std::vector<double> B, size_t Size) {
    if (Size <= 0) {
        throw "Block size of matrix must be > 0";
    }
    if ((A.size() <= 0) || (B.size() <= 0)) {
        throw "Size of matrix must be > 0";
    }
    if (A.size() != B.size()) {
        throw "Different size of matrix";
    }
    size_t BlockSize = static_cast<size_t>(sqrt(Size));
    Matrix result(BlockSize * BlockSize, 0);
    for(size_t i = 0; i < BlockSize; i++) {
        for (size_t j = 0; j < BlockSize; j++) {
            for (size_t k = 0; k < BlockSize; k++)
                result[i * BlockSize  + j] += A[i * BlockSize + k] * B[k * BlockSize + j];
        }
    }
    return result;
};
