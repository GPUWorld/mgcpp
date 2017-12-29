//          Copyright RedPortal 2017 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mgcpp/cublas/cufft_fft.hpp>
#include <mgcpp/operations/fft.hpp>
#include <mgcpp/operations/mult.hpp>
#include <mgcpp/vector/dense_vector.hpp>
#include <mgcpp/vector/device_vector.hpp>

namespace mgcpp
{
    template<typename DeviceVec,
<<<<<<< HEAD
             typename Type,
             alignment Align,
             size_t DeviceId,
             typename Alloc>
    device_vector<complex<Type>, Align, DeviceId, Alloc>
=======
            typename Type,
            alignment Align,
            size_t DeviceId,
            typename Alloc>
    inline device_vector<complex<Type>, Align, DeviceId>
>>>>>>> e8549c1f199e3098e00f5bdd35fae4b497d9fa97
    strict::
    rfft(dense_vector<DeviceVec, Type, Align, DeviceId> const& vec)
    {
        using allocator_type = typename DeviceVec::allocator_type;

        auto const& dev_vec = ~vec;

        size_t fft_size = dev_vec.shape();
        size_t output_size = fft_size / 2 + 1;

        allocator<Type>
            allocator<complex<Type>>

            auto result = device_vector<complex<Type>, Align, DeviceId, Alloc>(output_size);

        auto status = mgcpp::cublas_rfft(fft_size, dev_vec.data(), result.data_mutable());
        if(!status)
        { MGCPP_THROW_SYSTEM_ERROR(status.error()); }

        return result;
    }

    template<typename DeviceVec,
<<<<<<< HEAD
             typename Type,
             alignment Align,
             size_t DeviceId,
             typename Alloc>
    device_vector<Type, Align, DeviceId, Alloc>
=======
            typename Type,
            alignment Align,
            size_t DeviceId,
            typename Alloc>
    inline device_vector<Type, Align, DeviceId>
>>>>>>> e8549c1f199e3098e00f5bdd35fae4b497d9fa97
    strict::
    irfft(dense_vector<DeviceVec, complex<Type>, Align, DeviceId> const& vec, int n)
    {
        using allocator_type = typename DeviceVec::allocator_type;

        auto const& dev_vec = ~vec;

        size_t fft_size = n;
        if (n < 0)
            fft_size = (dev_vec.shape() - 1) * 2;
        else if (fft_size / 2 + 1 > dev_vec.shape())
        {
            // FIXME: zero-pad input to length floor(n/2)+1
            MGCPP_THROW_RUNTIME_ERROR("Zero-pad FFT unimplemented");
        }
        size_t output_size = fft_size;

        auto result = device_vector<Type, Align, DeviceId, Alloc>(output_size);

        auto status = mgcpp::cublas_irfft(fft_size, dev_vec.data(), result.data_mutable());
        if(!status)
        { MGCPP_THROW_SYSTEM_ERROR(status.error()); }

        // Normalize the result
        result = mgcpp::strict::mult(static_cast<Type>(1. / fft_size), result);
        return result;
    }


    template<typename DeviceVec,
             typename Type,
             alignment Align,
             size_t DeviceId,
             typename Alloc>
    device_vector<complex<Type>, Align, DeviceId, Alloc>
    strict::
    cfft(dense_vector<DeviceVec, complex<Type>, Align, DeviceId> const& vec, fft_direction direction)
    {
        using allocator_type = typename DeviceVec::allocator_type;

        auto const& dev_vec = ~vec;

        size_t fft_size = dev_vec.shape();
        size_t output_size = fft_size;

        auto result = device_vector<complex<Type>, Align, DeviceId, Alloc>(output_size);

        cublas::fft_direction dir;
        if (direction == fft_direction::forward)
            dir = cublas::fft_direction::forward;
        else
            dir = cublas::fft_direction::inverse;

        auto status = mgcpp::cublas_cfft(fft_size, dev_vec.data(),
                                         result.data_mutable(),
                                         dir);
        if(!status)
        { MGCPP_THROW_SYSTEM_ERROR(status.error()); }

        // Normalize the result
        if (direction == fft_direction::inverse)
            result = mgcpp::strict::mult(static_cast<Type>(1. / fft_size), result);

        return result;
    }
}
