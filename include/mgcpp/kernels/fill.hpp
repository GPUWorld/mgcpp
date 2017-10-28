
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_KERNELS_FILL_HPP_
#define _MGCPP_KERNELS_FILL_HPP_

#include <outcome.hpp>

#include <cstdlib>

namespace mgcpp
{
    // template<typename ElemType>
    // inline outcome::result<void>
    // fill(ElemType* device_ptr, ElemType value, size_t count);

    void fill64(void* ptr, uint64_t bitvec, size_t size);

    void fill32(void* ptr, uint32_t bitvec, size_t size);

    void fill16(void* ptr, uint16_t bitvec, size_t size);
}

#endif