
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mgcpp/cublas/blaslike_ext.hpp>
#include <mgcpp/device/device.hpp>
#include <mgcpp/device/matrix.hpp>
#include <mgcpp/operations/trans.hpp>
#include <mgcpp/system/exception.hpp>

namespace mgcpp
{
    template<typename T,
             size_t Device,
             storage_order SO>
    gpu::matrix<T, Device, SO>
    strict::
    trans(gpu::matrix<T, Device, SO> const& mat)
    {
        auto* thread_context = mat.get_thread_context();
        auto handle = thread_context->get_cublas_context(Device);

        auto shape = mat.shape();

        auto m = shape[0];
        auto n = shape[1];

        size_t alpha = 1;
        size_t beta = 0;

        gpu::matrix<T, Device, SO> result{m, n};

        auto status = cublas_geam(handle,
                                  CUBLAS_OP_T,
                                  CUBLAS_OP_N,
                                  m, n,
                                  &alpha,
                                  mat.get_data(), n,
                                  &beta,
                                  nullptr, m,
                                  result.get_data_mutable(), m);

        if(!status)
            MGCPP_THROW_SYSTEM_ERROR(status.error());

        return result;
    }
}
