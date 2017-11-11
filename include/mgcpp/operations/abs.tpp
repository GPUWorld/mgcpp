
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mgcpp/kernels/mgblas_lv1.hpp>
#include <mgcpp/operations/abs.hpp>
#include <mgcpp/system/exception.hpp>

#include <cstdlib>

namespace mgcpp
{
    template<typename DenseVec,
             typename Type,
             size_t DeviceId,
             allignment Allign>
    device_vector<Type, DeviceId, Allign, typename DenseVec::allocator_type>
    strict::
    abs(dense_vector<DenseVec, Type, DeviceId, Allign> const& vec)
    {
        using allocator_type = typename DenseVec::allocator_type;

        auto const& original_vec = ~vec;

        auto set_device_status = cuda_set_device(DeviceId);
        if(!set_device_status)
        { MGCPP_THROW_SYSTEM_ERROR(set_device_status.error()); }

        size_t n = original_vec.shape();

        auto result = mgcpp::device_vector<Type,
                                           DeviceId,
                                           Allign,
                                           allocator_type>(original_vec);
        auto status = mgblas_vab(result.data_mutable(), n);
        if(!status)
        { MGCPP_THROW_SYSTEM_ERROR(status.error()); }

        return result;
    }

    template<typename DenseMat,
             typename Type,
             size_t DeviceId>
    device_matrix<Type, DeviceId, typename DenseMat::allocator_type>
    strict::
    abs(dense_matrix<DenseMat, Type, DeviceId> const& mat)
    {
        using allocator_type = typename DenseMat::allocator_type;

        auto const& original_mat = ~mat;

        auto set_device_status = cuda_set_device(DeviceId);
        if(!set_device_status)
        { MGCPP_THROW_SYSTEM_ERROR(set_device_status.error()); }

        auto shape = original_mat.shape();

        auto result = device_matrix<Type, DeviceId, allocator_type>(original_mat);
        auto status = mgblas_vab(result.data_mutable(), shape.first * shape.second);
        if(!status)
        { MGCPP_THROW_SYSTEM_ERROR(status.error()); }

        return result;
    }
}

