
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mgcpp/cuda_libs/cublas.hpp>
#include <mgcpp/operations/add.hpp>
#include <mgcpp/system/exception.hpp>
#include <mgcpp/system/assert.hpp>

namespace mgcpp
{
    template<typename LhsDenseMat,
             typename RhsDenseMat,
             typename Type,
             size_t DeviceId>
    decltype(auto)
    strict::
    add(dense_matrix<LhsDenseMat, Type, DeviceId> const& lhs,
        dense_matrix<RhsDenseMat, Type, DeviceId> const& rhs)
    {
        using allocator_type = typename LhsDenseMat::allocator_type;
        using value_type = typename LhsDenseMat::value_type;
        
        auto const& lhs_mat = ~lhs;
        auto const& rhs_mat = ~rhs;

        MGCPP_ASSERT(lhs_mat.shape() == rhs_mat.shape(),
                     "matrix dimensions didn't match");

        auto set_device_status = cuda_set_device(DeviceId);
        if(!set_device_status)
        { MGCPP_THROW_SYSTEM_ERROR(set_device_status.error()); }

        auto* thread_context = lhs_mat.context();
        auto handle = thread_context->get_cublas_context(DeviceId);

        auto shape = lhs_mat.shape();

        size_t m = shape.first;
        size_t n = shape.second;

        value_type const alpha = 1;
        value_type const beta = 1;

        auto result = device_matrix<Type, DeviceId, allocator_type>{m, n};
        auto status = cublas_geam(handle,
                                  CUBLAS_OP_N,
                                  CUBLAS_OP_N,
                                  m, n,
                                  &alpha,
                                  lhs_mat.data(), m,
                                  &beta,
                                  rhs_mat.data(), m,
                                  result.data_mutable(), m);
        if(!status)
        { MGCPP_THROW_SYSTEM_ERROR(status.error()); }

        return result;
    }

    template<typename LhsDenseVec,
             typename RhsDenseVec,
             typename Type,
             size_t DeviceId,
             alignment Align>
    decltype(auto)
    strict::
    add(dense_vector<LhsDenseVec, Type, Align, DeviceId> const& lhs,
        dense_vector<RhsDenseVec, Type, Align, DeviceId> const& rhs)
    {
        using allocator_type = typename LhsDenseVec::allocator_type;
        using value_type = typename LhsDenseVec::value_type;

        auto const& lhs_vec = ~lhs;
        auto const& rhs_vec = ~rhs;

        MGCPP_ASSERT(lhs_vec.shape() == rhs_vec.shape(),
                     "vector size didn't match");

        auto set_device_status = cuda_set_device(DeviceId);
        if(!set_device_status)
        { MGCPP_THROW_SYSTEM_ERROR(set_device_status.error()); }

        auto* thread_context = lhs_vec.context();
        auto handle = thread_context->get_cublas_context(DeviceId);

        auto size = lhs_vec.shape();

        value_type const alpha = 1;

        auto result = device_vector<Type,
                                    Align,
                                    DeviceId,
                                    allocator_type>(lhs_vec);
        auto status = cublas_axpy(handle, size,
                                  &alpha,
                                  rhs_vec.data(), 1,
                                  result.data_mutable(), 1);
        if(!status)
        { MGCPP_THROW_SYSTEM_ERROR(status.error()); }

        return result;
    }
}
