
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mgcpp/cublas/blaslike_ext.hpp>
#include <mgcpp/device/matrix.hpp>
#include <mgcpp/device/vector.hpp>
#include <mgcpp/operations/sub.hpp>
#include <mgcpp/system/exception.hpp>

namespace mgcpp
{
    template<typename T, size_t Device, allignment Allign, typename Alloc>
    device_vector<T, Device, Allign, Alloc>
    strict::
    sub(device_vector<T, Device, Allign, Alloc> const& first,
        device_vector<T, Device, Allign, Alloc> const& second)
    {
        MGCPP_ASSERT(first.shape() == second.shape(),
                     "vector dimensions didn't match");

        device_vector<T, Device, Allign, Alloc> result(first);

        auto* thread_context = first.context();
        auto handle = thread_context->get_cublas_context(Device);

        T const alpha = -1;

        auto size = first.shape();

        auto status = cublas_axpy(handle, size,
                                  &alpha,
                                  second.data(), 1,
                                  result.data_mutable(), 1);
        if(!status)
        {
            MGCPP_THROW_SYSTEM_ERROR(status.error());
        }

        return result;
    }
}
