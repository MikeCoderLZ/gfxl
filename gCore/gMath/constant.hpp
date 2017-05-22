#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <iostream>

namespace gfx {

// This is a method to ensure the correctly typed values for
// common literals are used. Since the default type for floating
// point is double and the compiler is supposed to enforce that,
// some time can be lost to type promotion. A good programmer
// naturallywould avoid this, but in templated contexts it saves
// some dev time and precious lines of code.

template< typename T >
class lit {
public:
    constexpr static T const    thousandth     = 0.001;
    constexpr static T const    hundredth      = 0.01;
    constexpr static T const    tenth          = 0.1;
    constexpr static T const    quarter        = 0.25;
    constexpr static T const    half           = 0.5;
    constexpr static T const    zero           = 0.0;
    constexpr static T const    one            = 1.0;
    constexpr static T const    two            = 2.0;
    constexpr static T const    three          = 3.0;
    constexpr static T const    four           = 4.0;
    constexpr static T const    five           = 5.0;
    constexpr static T const    ten            = 10.0;
    constexpr static T const    hundred        = 100.0;
    constexpr static T const    neg_one        = -1.0;
    constexpr static T const    pi             = 3.1415926535897932384626433;
    constexpr static T const    tau            = 6.2831853071795864769252867;
    constexpr static T const    n360           = 360.0;
    constexpr static T const    inv_360        = 1.0 / 360.0;
    constexpr static T const    inv_pi         = 0.31830988618379067153776752;
    constexpr static T const    inv_tau        = 0.15915494309189533586888376;
    constexpr static T const    e              = 2.7182818284590452353602874;
    constexpr static T const    sqrt_two       = 1.4142135623730950488016887;
    constexpr static T const    inv_sqrt_two   = 0.70710678118654752440084436;
    constexpr static T const    sqrt_three     = 1.7320508075688772935274463;
    constexpr static T const    inv_sqrt_three = 0.57735026919;
    constexpr static T const    phi            = 1.6180339887498948482045868;
    constexpr static T const    delta          = 1.0;
};

template<>
class lit<float> {
public:
    constexpr static float const    thousandth     = 0.001f;
    constexpr static float const    hundredth      = 0.01f;
    constexpr static float const    tenth          = 0.1f;
    constexpr static float const    quarter        = 0.25f;
    constexpr static float const    half           = 0.5f;
    constexpr static float const    zero           = 0.0f;
    constexpr static float const    one            = 1.0f;
    constexpr static float const    two            = 2.0f;
    constexpr static float const    three          = 3.0f;
    constexpr static float const    four           = 4.0f;
    constexpr static float const    five           = 5.0f;
    constexpr static float const    ten            = 10.0f;
    constexpr static float const    hundred        = 100.0f;
    constexpr static float const    neg_one        = -1.0f;
    constexpr static float const    pi             = 3.1415926535897932384626433f;
    constexpr static float const    tau            = 6.2831853071795864769252867f;
    constexpr static float const    n360           = 360.0f;
    constexpr static float const    inv_360        = 1.0f / 360.0f;
    constexpr static float const    inv_pi         = 0.31830988618379067153776752f;
    constexpr static float const    inv_tau        = 0.15915494309189533586888376f;
    constexpr static float const    e              = 2.7182818284590452353602874f;
    constexpr static float const    sqrt_two       = 1.4142135623730950488016887f;
    constexpr static float const    inv_sqrt_two   = 0.70710678118654752440084436f;
    constexpr static float const    sqrt_three     = 1.7320508075688772935274463f;
    constexpr static float const    inv_sqrt_three = 0.57735026919f;
    constexpr static float const    phi            = 1.6180339887498948482045868f;
    constexpr static float const    delta          = 0.00001f;
};

typedef lit<float>  f_lit;

template<>
class lit<double> {
public:
    constexpr static double const    thousandth     = 0.001;
    constexpr static double const    hundredth      = 0.01;
    constexpr static double const    tenth          = 0.1;
    constexpr static double const    quarter        = 0.25;
    constexpr static double const    half           = 0.5;
    constexpr static double const    zero           = 0.0;
    constexpr static double const    one            = 1.0;
    constexpr static double const    two            = 2.0;
    constexpr static double const    three          = 3.0;
    constexpr static double const    four           = 4.0;
    constexpr static double const    five           = 5.0;
    constexpr static double const    ten            = 10.0;
    constexpr static double const    hundred        = 100.0;
    constexpr static double const    neg_one        = -1.0;
    constexpr static double const    pi             = 3.1415926535897932384626433;
    constexpr static double const    tau            = 6.2831853071795864769252867;
    constexpr static double const    n360           = 360.0;
    constexpr static double const    inv_360        = 1.0 / 360.0;
    constexpr static double const    inv_pi         = 0.31830988618379067153776752;
    constexpr static double const    inv_tau        = 0.15915494309189533586888376;
    constexpr static double const    e              = 2.7182818284590452353602874;
    constexpr static double const    sqrt_two       = 1.4142135623730950488016887;
    constexpr static double const    inv_sqrt_two   = 0.70710678118654752440084436;
    constexpr static double const    sqrt_three     = 1.7320508075688772935274463;
    constexpr static double const    inv_sqrt_three = 0.57735026919;
    constexpr static double const    phi            = 1.6180339887498948482045868;
    constexpr static double const    delta          = 0.0000000001;
};

typedef lit<double>  d_lit;

// The angle_t template is a method to disambiguate angular units.
// Instead of using POD numbers which inevitably lead to bugs
// and confusion, the angle_t class forces a coder to specify
// the angular system they are using to describe the rotation.
// Furthermore, code from one area can 'think' in one system
// but recieve information that was specified in another system.

// TODO angle_t might need to be expanded in the future to act more
// like the types over in datatype.hpp.

template< typename T >
class angle_t {
    public:
        static angle_t<T> in_rads( T in_rads );
        static angle_t<T> in_grads( T in_grads );
        static angle_t<T> in_degs( T in_degs );
        
        T to_rads() const;
        T to_grads() const;
        T to_degs() const;
        
        template< typename U >
        friend std::ostream&   operator<<( std::ostream& out, angle_t<U> const& src );
    private:
        angle_t( T new_unians ) : unians (new_unians) {};
        T unians;
        // One unian = tau radians = 2*pi radians = 200 gradians = 360 degrees
};

typedef angle_t<float> angle;
typedef angle_t<double> d_angle;

template < typename T > inline
angle_t<T> angle_t< T >::in_rads( T in_rads )
{
    return angle_t<T>( in_rads * lit<T>::inv_tau );
}
template < typename T > inline
angle_t<T> angle_t< T >::in_grads( T in_grads )
{
    return angle_t<T>( in_grads * (lit<T>::thousandth * lit<T>::five) );
}
template < typename T > inline
angle_t<T> angle_t< T >::in_degs( T in_degs )
{
    return angle_t<T>( in_degs * lit<T>::inv_360 );
}
template < typename T > inline
T angle_t< T >::to_rads() const
{
    return unians * lit<T>::tau;
}
template < typename T > inline
T angle_t< T >::to_grads() const
{
    return unians * (lit<T>::two * lit<T>::hundred);
}
template < typename T > inline
T angle_t< T >::to_degs() const
{
    return unians * lit<T>::n360;
}

template< typename T >
std::ostream& operator<<( std::ostream& out, angle_t<T> const& src )
{
    out << src.to_degs() << "°";
    return out;
}

}
#endif