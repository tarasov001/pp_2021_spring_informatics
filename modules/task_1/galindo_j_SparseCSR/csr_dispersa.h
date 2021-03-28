// Copyright 2021 Galindo Buitrago Julio Cesar
#ifndef MODULES_TASK_1_GALINDO_J_SPARSECSR_CSR_DISPERSA_H_
#define MODULES_TASK_1_GALINDO_J_SPARSECSR_CSR_DISPERSA_H_
#include <vector>
#include <complex>

struct DispersaMatrix{
    std::vector<std::complex<double>> valor;
    std::vector<int> filaN, columnaN;
    int n;
};
DispersaMatrix transposicion(DispersaMatrix AT);
DispersaMatrix multiplicacion(DispersaMatrix p, DispersaMatrix q);
DispersaMatrix ma_generacion(int m, const std::vector<std::complex<double>> &vectorial);

#endif  // MODULES_TASK_1_GALINDO_J_SPARSECSR_CSR_DISPERSA_H_