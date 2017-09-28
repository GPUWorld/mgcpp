
//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mgcpp/gpu/matrix.hpp>
#include <mgcpp/cpu/matrix.hpp>
#include <mgcpp/cuda/cuda_template_stdlib.hpp>
#include <mgcpp/cublas/cublas_helpers.hpp>

namespace mg
{

    template<typename ElemType,
             size_t DeviceId,
             storage_order StoreOrder>
    gpu::matrix<ElemType, DeviceId, StoreOrder>::
    matrix()
        : _data(nullptr),
          _context(nullptr),
          _x_dim(0),
          _y_dim(0),
          _released(true) {}

    template<typename ElemType,
             size_t DeviceId,
             storage_order StoreOrder>
    gpu::matrix<ElemType, DeviceId, StoreOrder>::
    matrix(thread_context& context)
        : _data(nullptr),
          _context(&context),
          _x_dim(0),
          _y_dim(0),
          _released(true) {}

    template<typename ElemType,
             size_t DeviceId,
             storage_order StoreOrder>
    gpu::matrix<ElemType, DeviceId, StoreOrder>::
    matrix(size_t x_dim, size_t y_dim)
        :_data(cuda_malloc<ElemType>(x_dim * y_dim)),
         _context(nullptr),
         _x_dim(x_dim),
         _y_dim(y_dim),
         _released(false) {}

    template<typename ElemType,
             size_t DeviceId,
             storage_order StoreOrder>
    gpu::matrix<ElemType, DeviceId, StoreOrder>::
    matrix(thread_context& context,
           size_t x_dim, size_t y_dim)
        :_data(cuda_malloc<ElemType>(x_dim * y_dim)),
         _context(&context),
         _x_dim(x_dim),
         _y_dim(y_dim),
         _released(false) {}

    template<typename ElemType,
             size_t DeviceId,
             storage_order StoreOrder>
    gpu::matrix<ElemType, DeviceId, StoreOrder>::
    matrix(size_t x_dim, size_t y_dim, ElemType init)
        :_data(cuda_malloc<ElemType>(x_dim * y_dim)),
         _context(nullptr),
         _x_dim(x_dim),
         _y_dim(y_dim),
         _released(false)
    {
        
    }

    template<typename ElemType,
             size_t DeviceId,
             storage_order StoreOrder>
    gpu::matrix<ElemType, DeviceId, StoreOrder>::
    matrix(thread_context& context,
           size_t x_dim, size_t y_dim, ElemType init)
        :_data(cuda_malloc<ElemType>(x_dim * y_dim)),
         _context(&thread_context),
         _x_dim(x_dim),
         _y_dim(y_dim),
         _released(false)
    {

    }

    template<typename ElemType,
             size_t DeviceId,
             storage_order StoreOrder>
    gpu::matrix<ElemType, DeviceId, StoreOrder>::
    matrix(cpu::matrix<ElemType> const& cpu_mat)
    {
        auto rows = cpu_mat.rows();
        auto cols = cpu_mat.columns();
        _data = cuda_malloc<ElemType>(rows * cols);
        cubals_set_matrix(rows, cols, cpu_mat.get_data() ,_data);
    }

    template<typename ElemType,
             size_t DeviceId,
             storage_order StoreOrder>
    size_t 
    gpu::matrix<ElemType, DeviceId, StoreOrder>::
    rows() const noexcept
    {
        return _row_dim;
    }

    template<typename ElemType,
             size_t DeviceId,
             storage_order StoreOrder>
    size_t
    gpu::matrix<ElemType, DeviceId, StoreOrder>::
    columns() const noexcept
    {
        return _col_dim;
    }
}
