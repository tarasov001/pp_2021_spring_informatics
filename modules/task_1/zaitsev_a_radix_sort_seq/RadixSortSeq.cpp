// Copyright 2021 Zaitsev Andrey
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include "../../../modules/task_1/zaitsev_a_radix_sort_seq/RadixSortSeq.h"

std::vector<double> createVector(int size, double a, double b) {
	std::mt19937 gen;
	gen.seed(static_cast<unsigned int>(time(0)));
	std::uniform_real_distribution<double> distr(a, b);
	std::vector<double> vec(size);
	for (int i = 0; i < size; i++) {
		vec[i] = distr(gen);
	}
	return vec;
}

std::vector<double> radixSort(std::vector<double> vec, int size) {
	double* tmp = nullptr;
	double* arr = new double[size];
	for (int i = 0; i < size; i++)
		arr[i] = vec[i];
	double* out = new double[size];
	for (int i = 0; i < 7; i++) {

		unsigned char* arr2 = (unsigned char*)arr;
		int counter[256] = { 0 };
		int res = 0;
		for (int j = 0; j < size; j++)
			counter[arr2[8 * j + i]]++;
		for (int j = 0; j < 256; j++) {
			int tmp_ = counter[j];
			counter[j] = res;
			res += tmp_;
		}
		for (int j = 0; j < size; j++) {
			int ind = 8 * j + i;
			out[counter[arr2[ind]]] = arr[j];
			counter[arr2[ind]]++;
		}

		tmp = arr;
		arr = out;
		out = tmp;
	}

	unsigned char* arr2 = (unsigned char*)arr;
	int counter[256] = { 0 };
	int offset[256] = { 0 };
	std::vector<double> result(size);
	for (int i = 0; i < size; i++)
		counter[arr2[8 * i + 7]]++;
	offset[255] = counter[255] - 1;
	for (int i = 254; i >= 128; i--)
		offset[i] = offset[i + 1] + counter[i];
	offset[0] = offset[128] + 1;
	for (int i = 1; i < 128; i++)
		offset[i] = offset[i - 1] + counter[i - 1];
	for (int i = 0; i < size; i++) {
		if (arr2[8 * i + 7] < 128)
			result[offset[arr2[8 * i + 7]]++] = arr[i];
		else
			result[offset[arr2[8 * i + 7]]--] = arr[i];
	}
	return result;
}