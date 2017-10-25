
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mgcpp/operations/sub.hpp>
#include <mgcpp/cublas/blaslike_ext.hpp>
#include <mgcpp/system/exception.hpp>

namespace mgcpp
{
    template<typename T, size_t Device, allignment Allign>
    gpu::vector<T, Device, Allign>
    strict::
    sub(gpu::vector<T, Device, Allign> const& first,
        gpu::vector<T, Device, Allign> const& second)
    {
        gpu::vector<T, Device, Allign> result(first);

        auto* thread_context = first.get_thread_context();
        auto handle = thread_context->get_cublas_context(Device);

        T const alpha = -1;

        auto size = first.shape();

        auto status = cublas_axpy(handle, size,
                                  &alpha,
                                  second.get_data(), 1,
                                  result.get_data_mutable(), 1);
        if(!status)
        {
            MGCPP_THROW_SYSTEM_ERROR(status.error());
        }

        return result;
    }
}
