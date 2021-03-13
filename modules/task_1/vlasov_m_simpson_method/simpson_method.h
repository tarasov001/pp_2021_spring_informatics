// Copyright 2021 Vlasov Maksim

#ifndef MODULES_TASK_1_VLASOV_M_SIMPSON_METHOD_SIMPSON_METHOD_H_
#define MODULES_TASK_1_VLASOV_M_SIMPSON_METHOD_SIMPSON_METHOD_H_

#include <functional>
#include <vector>

namespace SimpsonMethod {

double integrate(int steps, const std::vector<double>& seg_begin,
                 const std::vector<double>& seg_end,
                 const std::function<double(const std::vector<double>&)>& func);

}  // namespace SimpsonMethod

#endif  // MODULES_TASK_1_VLASOV_M_SIMPSON_METHOD_SIMPSON_METHOD_H_
