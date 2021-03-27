// Copyright 2021 Solovev Aleksandr
#include "../../../modules/task_1/solovev_a_radix_sort/radix_sort.h"
#include <stdio.h>
#include <cstring>
#include <utility>
#include <iostream>

int generateRandomArray(int *buffer, size_t length, double min, double max)
{
    if ((length <= 0) || (buffer == nullptr))
        return -1;
    if (min >= max)
    {
        double temp = min;
        min = max;
        max = temp;
    }
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<double> buf(min, max);
    for (size_t i = 0; i < length; i++)
    {
        buffer[i] = static_cast<int>(buf(gen));
    }
    return 0;
}

int MergeArrays(int *buffer1, size_t length1, int *buffer2, size_t length2, int *result)
{
    if ((length1 < 0) || (length2 < 0))
        return -1;
    if ((buffer1 == nullptr) || (buffer2 == nullptr) || (result == nullptr))
        return -1;
    int k = 0;

    for (size_t i = 0; i < length1; i++)
    {
        result[k] = buffer1[i];
        k++;
    }
    for (size_t j = 0; j < length2; j++)
    {
        result[k] = buffer2[j];
        k++;
    }

    return 0;
}

int SortingCheck(int *buffer, size_t length)
{
    if (length < 1)
        return -1;
    if (buffer == nullptr)
        return -1;
    for (size_t i = 1; i < length / 2 + 1; i++)
    {
        if (buffer[i - 1] > buffer[i] || buffer[length - i] < buffer[length - i - 1])
        {
            return -1;
        }
    }
    return 0;
}

void CountingSort(int *input, int *output, int valbyte, size_t length)
{
    unsigned char *buffer = (unsigned char *)input;
    
    int counter[256];
    int value;
    std::fill(counter, counter + 256, 0);
    
    for (size_t i = 0; i < length; i++){
        counter[buffer[4 * i + valbyte]]++;
    }
    int j;
    for (j = 0; j < 256; j++)
    {
        if (counter[j] != 0)
            break;
    }

    value = counter[j];
    counter[j] = 0;
    j++;
    for (; j < 256; j++)
    {
        int tmp = counter[j];
        counter[j] = value;
        value += tmp;
    }

    for (int i = 0; i < length; i++)
    {
        output[counter[buffer[4 * i + valbyte]]++] = input[i];
    }
}

int RadixSortUnsigned(int *buffer, size_t length)
{
    if (length < 1)
    {
        return 0;
    }
    if ((length < 0) || (buffer == nullptr))
    {
        return -1;
    }
    int *outbuf = reinterpret_cast<int *>(malloc(sizeof(int) * length));
    if (outbuf == nullptr)
    {
        return -1;
    }

    for (int i = 0; i < 2; i++)
    {
        CountingSort(buffer, outbuf, 2 * i, length);
        CountingSort(outbuf, buffer, 2 * i + 1, length);
    }
    BufferClear(outbuf);

    return 0;
}

int RadixSort(int *buffer, size_t length)
{
    if (length < 1)
        return -1;
    if (buffer == nullptr)
        return -1;
    int *positive_numbers = nullptr;
    int *negative_numbers = nullptr;
    int positive_length = 0, negative_length = 0;
    int status = 0;

    positive_numbers = reinterpret_cast<int *>(malloc(sizeof(int) * length));
    if (positive_numbers == nullptr)
    {
        return -1;
    }
    negative_numbers = reinterpret_cast<int *>(malloc(sizeof(int) * length));
    if (negative_numbers == nullptr)
    {
        return -1;
    }

    for (size_t i = 0; i < length; i++)
    {
        if (buffer[i] >= 0)
        {
            positive_numbers[positive_length] = buffer[i];
            positive_length++;
        }
        else
        {
            negative_numbers[negative_length] = buffer[i];
            negative_length++;
        }
    }

    status = RadixSortUnsigned(negative_numbers, negative_length);
    status = RadixSortUnsigned(positive_numbers, positive_length);

    status = MergeArrays(negative_numbers, negative_length, positive_numbers, positive_length, buffer);
    BufferClear(positive_numbers);
    BufferClear(negative_numbers);

    return status;
}

void BufferClear(int *buffer)
{
    if (buffer)
    {
        free(buffer);
        buffer = nullptr;
    }
}