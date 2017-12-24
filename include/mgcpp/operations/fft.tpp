
#include <mgcpp/vector/dense_vector.hpp>
#include <mgcpp/vector/device_vector.hpp>

#include <mgcpp/cublas/cufft_fft.hpp>
#include <mgcpp/operations/mult.hpp>

namespace mgcpp
{
    template<typename DeviceVec,
             typename Type,
             allignment Align,
             size_t DeviceId>
    inline device_vector<Type, Align, DeviceId,
                         typename DeviceVec::allocator_type>
    rfft(dense_vector<DeviceVec, Type, Align, DeviceId> const& vec)
    {
        using allocator_type = typename DeviceVec::allocator_type;

        auto const& dev_vec = ~vec;

        size_t fft_size = dev_vec.shape();
        size_t output_size = (fft_size / 2 + 1) * 2;

        auto result = device_vector<Type, Align, DeviceId, allocator_type>(output_size);

        auto status = mgcpp::cublas_rfft(fft_size, dev_vec.data(), result.data_mutable());
        if(!status)
        { MGCPP_THROW_SYSTEM_ERROR(status.error()); }

        return result;
    }


    template<typename DeviceVec,
             typename Type,
             allignment Align,
             size_t DeviceId>
    inline device_vector<Type, Align, DeviceId,
                         typename DeviceVec::allocator_type>
    irfft(dense_vector<DeviceVec, Type, Align, DeviceId> const& vec, int n)
    {
        using allocator_type = typename DeviceVec::allocator_type;

        auto const& dev_vec = ~vec;

        size_t fft_size;
        if (n < 0)
            fft_size = (dev_vec.shape() / 2 - 1) * 2;
        else {
            fft_size = n;
            // FIXME: zero-pad input to match floor(n/2)+1 points
        }
        size_t output_size = fft_size;

        auto result = device_vector<Type, Align, DeviceId, allocator_type>(output_size);

        auto status = mgcpp::cublas_irfft(fft_size, dev_vec.data(), result.data_mutable());
        if(!status)
        { MGCPP_THROW_SYSTEM_ERROR(status.error()); }

        // Normalize the result
        result = mgcpp::strict::mult(static_cast<Type>(1. / fft_size), result);
        return result;
    }


    template<typename DeviceVec,
             typename Type,
             allignment Align,
             size_t DeviceId>
    inline device_vector<Type, Align, DeviceId,
                         typename DeviceVec::allocator_type>
    cfft(dense_vector<DeviceVec, Type, Align, DeviceId> const& vec, fft_direction direction)
    {
        using allocator_type = typename DeviceVec::allocator_type;

        auto const& dev_vec = ~vec;

        size_t fft_size = dev_vec.shape() / 2;
        size_t output_size = fft_size * 2;

        auto result = device_vector<Type, Align, DeviceId, allocator_type>(output_size);

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

        if (direction == fft_direction::inverse)
            result = mgcpp::strict::mult(static_cast<Type>(1. / fft_size), result);

        return result;
    }
}
