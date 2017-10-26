
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_GPU_MATRIX_HPP_
#define _MGCPP_GPU_MATRIX_HPP_

#include <mgcpp/cpu/forward.hpp>
#include <mgcpp/device/forward.hpp>
#include <mgcpp/global/storage_order.hpp>
#include <mgcpp/context/global_context.hpp>
#include <mgcpp/context/thread_context.hpp>

namespace mgcpp
{
    template<typename T,
             size_t DeviceId = 0,
             storage_order SO = row_major>
    class device_matrix
    {
    private:
        T* _data;
        thread_context* _context;
        size_t _m_dim;
        size_t _n_dim;
        bool _released;

    public:
        inline device_matrix() noexcept;

        inline ~device_matrix() noexcept;

        inline device_matrix(size_t i, size_t j);

        inline device_matrix(size_t i, size_t j, T init);
        
        inline device_matrix(size_t i, size_t j, T* init);

        inline device_matrix(cpu::matrix<T, SO> const& cpu_mat);

        inline
        device_matrix(device_matrix<T, DeviceId, SO> const& other);

        inline
        device_matrix(device_matrix<T, DeviceId, SO>&& other) noexcept;

        device_matrix<T, DeviceId, SO>&
        operator=(device_matrix<T, DeviceId, SO> const& other);

        device_matrix<T, DeviceId, SO>&
        operator=(device_matrix<T, DeviceId, SO>&& other) noexcept;

        inline device_matrix<T, DeviceId, SO>&
        zero();

        inline device_matrix<T, DeviceId, SO>&
        resize(size_t i, size_t j);

        inline device_matrix<T, DeviceId, SO>&
        resize(size_t i, size_t j, T init);

        inline device_matrix<T, DeviceId, SO>&
        copy_from_host(cpu::matrix<T, SO> const& cpu_mat);

        inline cpu::matrix<T, SO>
        copy_to_host() const;

        inline T
        check_value(size_t i, size_t j) const;

        inline T const*
        data() const noexcept;

        inline T*
        data_mutable() noexcept;

        inline thread_context*
        context() const noexcept;

        inline T*
        release_data();

        inline std::pair<size_t, size_t>
        shape() const noexcept;
    };
}

#include <mgcpp/device/matrix.tpp>
#endif
