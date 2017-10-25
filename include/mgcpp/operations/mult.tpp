
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mgcpp/operations/mult.hpp>
#include <mgcpp/context/thread_context.hpp>
#include <mgcpp/system/error_code.hpp>
#include <mgcpp/system/exception.hpp>
#include <mgcpp/cublas/blas_lv1.hpp>
#include <mgcpp/cublas/blas_lv3.hpp>

namespace mgcpp
{
    template<typename T, size_t Device, storage_order SO>
    gpu::matrix<T, Device, SO>
    strict::
    mult(gpu::matrix<T, Device, SO> const& first,
         gpu::matrix<T, Device, SO> const& second)
    {
        T const alpha = 1;
        T const beta = 0;

        auto second_shape = second.shape();
        auto first_shape = first.shape();

        size_t m = first_shape.first;
        size_t k = first_shape.second;
        size_t n = second_shape.second;

        gpu::matrix<T, Device, row_major> result{m, n};

        auto* context = first.get_thread_context();
        auto handle = context->get_cublas_context(Device);
    
        auto status = cublas_gemm(handle,
                                  CUBLAS_OP_N, CUBLAS_OP_N,
                                  m, n, k,
                                  &alpha,
                                  first.get_data(), m,
                                  second.get_data(), k,
                                  &beta,
                                  result.get_data_mutable(), m);

        if(!status)
            MGCPP_THROW_SYSTEM_ERROR(status.error());

        return result;
    }
    
    template<typename T, size_t Device, allignment Allign>
    gpu::vector<T, Device, Allign>
    strict::
    mult(T scalar,
         gpu::vector<T, Device, Allign> const& vec)
    {
        auto* context = vec.get_thread_context();
        auto handle = context->get_cublas_context(Device);
        auto size = vec.shape();

        gpu::vector<T, Device, Allign> result(vec);

        auto status = cublas_scal(handle, size,
                                  &scalar,
                                  result.get_data_mutable(), 1);
        if(!status)
        {
            MGCPP_THROW_SYSTEM_ERROR(status.error());
        }

        return result;
    }
}
