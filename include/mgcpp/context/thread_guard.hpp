
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_CONTEXT_THREAD_GUARD_HPP_
#define _MGCPP_CONTEXT_TRHEAD_GUARD_HPP_

#include <initializer_list>

namespace mgcpp
{
    class thread_guard
    {
    public:
        explicit thread_guard(std::initializer_list<size_t> device,
                              bool cublas);

        explicit thread_guard(size_t device, bool cublas);

        ~thread_guard();
    };
}

#include <mgcpp/context/thread_guard.ipp>
#endif