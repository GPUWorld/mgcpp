
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_OPERATIONS_SUBSTRACTION_HPP_
#define _MGCPP_OPERATIONS_SUBSTRACTION_HPP_

#include <mgcpp/matrix/dense_matrix.hpp>
#include <mgcpp/matrix/device_matrix.hpp>
#include <mgcpp/vector/dense_vector.hpp>
#include <mgcpp/vector/device_vector.hpp>

#include <cstdlib>

namespace mgcpp
{
    namespace strict
    {
        template<typename LhsDenseVec,
                 typename RhsDenseVec,
                 typename Type,
                 size_t DeviceId,
                 allignment Allign>
        inline device_vector<Type, DeviceId, Allign,
                             typename LhsDenseVec::allocator_type>
        sub(dense_vector<LhsDenseVec, Type, DeviceId, Allign> const& lhs,
            dense_vector<RhsDenseVec, Type, DeviceId, Allign> const& rhs);

        template<typename LhsDenseMat,
                 typename RhsDenseMat,
                 typename Type,
                 size_t DeviceId>
        inline device_matrix<Type, DeviceId, typename LhsDenseMat::allocator_type>
        sub(dense_matrix<LhsDenseMat, Type, DeviceId> const& rhs,
            dense_matrix<RhsDenseMat, Type, DeviceId> const& lhs);
    }
}

#include <mgcpp/operations/sub.tpp>
#endif
