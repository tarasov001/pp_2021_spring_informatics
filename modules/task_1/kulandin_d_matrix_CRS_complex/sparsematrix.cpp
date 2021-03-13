// Copyright 2021 Kulandin Denis
#include <limits>
#include "../../../modules/task_1/kulandin_d_matrix_CRS_complex/sparsematrix.h"

bool equalZero(const std::complex<double> & a) {
    return std::abs(a) < std::numeric_limits<double>::epsilon();
}

SparseMatrix::SparseMatrix(int _size) {
    size = _size;
}

SparseMatrix::SparseMatrix(const SparseMatrix & a) : size(a.size) {
    values = a.values;
    cols = a.cols;
    pointers = a.pointers;
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix & a) {
    if (this == &a) return *this;
    size = a.size;
    values = a.values;
    cols = a.cols;
    pointers = a.pointers;
    return *this;
}

SparseMatrix::SparseMatrix(const std::vector<std::complex<double>> & a, int n) {
    size = n;
    pointers.push_back(0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (equalZero(a[i * n + j])) continue;
            values.push_back(a[i * n + j]);
            cols.push_back(j);
        }
        pointers.push_back(static_cast<int>(cols.size()));
    }
}

std::vector<std::complex<double>> SparseMatrix::getValues() const {
    return values;
}

std::vector<int> SparseMatrix::getCols() const {
    return cols;
}

std::vector<int> SparseMatrix::getPointers() const {
    return pointers;
}

int SparseMatrix::getSize() const {
    return size;
}

std::vector<std::complex<double>> SparseMatrix::createDenseMatrix() const {
    std::vector<std::complex<double>> ans(
        size * size,
        std::complex<double>(0, 0));
    for (int row = 0; row < size; ++row) {
        for (int j = pointers[row]; j < pointers[row + 1]; ++j) {
            ans[row * size + cols[j]] = values[j];
        }
    }
    return ans;
}

SparseMatrix SparseMatrix::transposition() const {
    SparseMatrix a(size);
    std::vector<std::vector<int>> helpCols(size);
    std::vector<std::vector<std::complex<double>>> helpValues(size);
    for (int row = 0; row < size; ++row) {
        for (int j = pointers[row]; j < pointers[row + 1]; ++j) {
            helpCols[cols[j]].push_back(row);
            helpValues[cols[j]].push_back(values[j]);
        }
    }
    a.pointers.push_back(0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < static_cast<int>(helpCols[i].size()); ++j) {
            a.values.push_back(helpValues[i][j]);
            a.cols.push_back(helpCols[i][j]);
        }
        a.pointers.push_back(
            a.pointers.back() + static_cast<int>(helpCols[i].size()));
    }
    return a;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix & a) {
    if (size != a.getSize()) {
        throw(std::string)"Wrong matrix sizes";
    }
    SparseMatrix ans(size);
    ans.pointers.push_back(0);
    SparseMatrix a_t = a.transposition();
    auto a_t_values = a_t.getValues();
    auto a_t_cols = a_t.getCols();
    auto a_t_pointers = a_t.getPointers();
    for (int row1 = 0; row1 < size; ++row1) {
        for (int row2 = 0; row2 < size; ++row2) {
            std::vector<int> used(size, -1);
            std::complex<double> cur(0, 0);
            for (int i = pointers[row1]; i < pointers[row1 + 1]; ++i) {
                used[cols[i]] = i;
            }
            for (int i = a_t_pointers[row2]; i < a_t_pointers[row2 + 1]; ++i) {
                if (used[a_t_cols[i]] == -1) continue;
                cur += values[used[a_t_cols[i]]] * a_t_values[i];
            }
            if (!equalZero(cur)) {
                ans.cols.push_back(row2);
                ans.values.push_back(cur);
            }
        }
        ans.pointers.push_back(ans.values.size());
    }
    return ans;
}
