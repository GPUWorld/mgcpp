
//          Copyright RedPortal, mujjingun 2017 - 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_OPERATIONS_MEAN_HPP_
#define _MGCPP_OPERATIONS_MEAN_HPP_

#include <mgcpp/matrix/dense_matrix.hpp>
#include <mgcpp/matrix/device_matrix.hpp>
#include <mgcpp/vector/dense_vector.hpp>
#include <mgcpp/vector/device_vector.hpp>

#include <cstdlib>

namespace mgcpp {
namespace strict {
template <typename DenseVec, typename Type, size_t DeviceId>
inline decltype(auto) mean(dense_vector<DenseVec, Type, DeviceId> const& vec);

template <typename DenseMat, typename Type, size_t DeviceId>
inline decltype(auto) mean(dense_matrix<DenseMat, Type, DeviceId> const& mat);
}  // namespace strict
}  // namespace mgcpp

#include <mgcpp/operations/mean.tpp>
#endif
