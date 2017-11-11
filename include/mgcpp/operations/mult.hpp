
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_OPERATIONS_MULTIPLICATION_HPP_
#define _MGCPP_OPERATIONS_MULTIPLICATION_HPP_

#include <mgcpp/matrix/dense_matrix.hpp>
#include <mgcpp/matrix/device_matrix.hpp>
#include <mgcpp/vector/dense_vector.hpp>
#include <mgcpp/vector/device_vector.hpp>

#include <cstdlib> 

namespace mgcpp
{
    namespace strict
    {
        template<typename LhsDenseMat,
                 typename RhsDenseMat,
                 typename Type,
                 size_t DeviceId>
        inline device_matrix<Type, DeviceId,
                             typename LhsDenseMat::allocator_type>
        mult(dense_matrix<LhsDenseMat, Type, DeviceId> const& lhs,
             dense_matrix<RhsDenseMat, Type, DeviceId> const& rhs);

        // template<typename LhsDenseVec,
        //          typename RhsDenseVec,
        //          typename Type,
        //          size_t Device,
        //          allignment Allign>
        // inline device_vector<Type, Device, Allign,
        //                      typename LhsDenseVec::allocator_type>
        // mult(dense_vector<LhsDenseVec, Type, Device, Allign> const& first,
        //      dense_vector<RhsDenseVec, Type, Device, Allign> const& second);

        template<typename DenseVec,
                 typename Type,
                 size_t DeviceId,
                 allignment Allign>
        inline device_vector<Type, DeviceId, Allign,
                             typename DenseVec::allocator_type>
        mult(Type scalar,
             dense_vector<DenseVec, Type, DeviceId, Allign> const& vec);


        // template<typename T, size_t Device, storage_order SO>
        // void
        // mult_assign(gpu::matrix<T, Device, SO>& first,
        //             gpu::matrix<T, Device, SO> const& second);
    }
}

#include <mgcpp/operations/mult.tpp>
#endif
