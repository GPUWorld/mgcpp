
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_DEVICE_MANAGER_HPP_
#define _MGCPP_DEVICE_MANAGER_HPP_

#include <cublas_v2.h>

#include <memory>

namespace mgcpp
{
    class device_manager
    {
    private:
        size_t _device_id;
        std::unique_ptr<cublasHandle_t> _cublas_handle;

        cublasHandle_t create_cublas_handle() const;

    public:
        cublasHandle_t get_cublas();
    };
}

#endif
