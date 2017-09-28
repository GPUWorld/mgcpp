
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_GPU_MATRIX_HPP_
#define _MGCPP_GPU_MATRIX_HPP_

#include <mgcpp/cpu/forward.hpp>
#include <mgcpp/context/thread_context.hpp>

namespace mg
{
    enum class storage_order { column_major = 0, row_major}; 

    namespace gpu
    {
        template<typename ElemType,
                 size_t DeviceId,
                 storage_order StoreOrder>
        class matrix
        {
        private:
            ElemType* _data;
            thread_context* _context;
            size_t _row_dim;
            size_t _col_dim;
            bool _released;

        public:
            inline matrix();

            inline matrix(thread_context& context);

            inline matrix(size_t x_dim, size_t y_dim);

            inline matrix(thread_context& context,
                          size_t x_dim, size_t y_dim);

            inline matrix(size_t x_dim, size_t y_dim, ElemType init);

            inline matrix(thread_context& context,
                          size_t x_dim, size_t y_dim, ElemType init);

            template<size_t Xdim, size_t Ydim>
            inline matrix(cpu::matrix<ElemType> const& cpu_mat);

            inline void
            set_context(thread_context& context) noexcept;

            inline cpu::matrix<ElemType>
            copy_to_cpu() const;
   
            inline ElemType const*
            get_data() const;

            inline ElemType*
            get_data_mutable();

            inline ElemType*
            release_data();

            inline size_t
            rows() const noexcept;

            inline size_t
            columns() const noexcept;

            inline ~matrix();
        };
    }
}

#endif
