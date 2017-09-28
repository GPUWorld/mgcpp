
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_CPU_MATRIX_HPP_
#define _MGCPP_CPU_MATRIX_HPP_

#include <mgcpp/gpu/fwd.hpp>

namespace mg
{
    namespace cpu
    {
        template<typename ElemType>
        class matrix
        {
        private:
            ElemType* _data; 
            size_t _x_dim;
            size_t _y_dim;
        
        public:
            inline matrix();

            inline matrix(size_t rows, size_t columns);

            inline matrix(size_t rows, size_t columns,
                          ElemType init);

            template<size_t DeviceId>
            inline matrix(
                gpu::matrix<ElemType, DeviceId> const& gpu_mat);

            template<size_t DeviceId>
            inline gpu::matrix<ElemType, DeviceId>
            copy_to_gpu() const;

            inline ElemType*
            get_data() const;

            inline size_t
            rows() const noexcept;

            inline size_t
            columns() const noexcept;
        };
    }
}

#endif
