//Copyright 2021 Tyurmina Alexandra 
#ifndef MODULES_TASK_1_TYURMINA_A_SHELL_BETCHER_SHELL_BETCHER_H
#define MODULES_TASK_1_TYURMINA_A_SHELL_BETCHER_SHELL_BETCHER_H
#include <iostream>
#include <vector>
#include <random>

std::vector<int> ShellSort(const std::vector<int>& massiv, int size); //шеловская 
std::vector<int> ShellBetcherS(const std::vector<int>& mass, int size); //совместка 
std::vector<int> BetcherMerge(const std::vector<int>& massiv1, const std::vector<int>& massiv2); //сама сборка массива четн нечетн 
std::vector<int> BetcherEven(const std::vector<int>& massiv1, const std::vector<int>& massiv2); //массив четных 
std::vector<int> BetcherOdd(const std::vector<int>& massiv1, const std::vector<int>& massiv2); //массив нечетных 

#endif  // MODULES_TASK_1_TYURMINA_A_SHELL_BETCHER_SHELL_BETCHER_H_ 
