#ifndef CONSTANT_HPP
#define CONSTANT_HPP

// This little gizmo is a metaprogramming thing to make sure
// templates use the correctly typed values for common
// literals. I'm a paranoid programmer, and since the default
// type for floating point is double and the compiler is supposed
// to enforce that, we can lose some efficiency.
//
// Besides, you can never be too sure with matrices and graphics.

template< typename T >
class cnst {
public:
    constexpr static T const    zero         = 0;
    constexpr static T const    one          = 1;
    constexpr static T const    two          = 2;
    constexpr static T const    ten          = 10;
    constexpr static T const    hundred      = 100;
    constexpr static T const    neg_one      = -1;
    constexpr static T const    pi           = 3.1415926535897932384626433;
    constexpr static T const    tau          = 6.2831853071795864769252867;
    constexpr static T const    inv_pi       = 0.31830988618379067153776752;
    constexpr static T const    inv_tau      = 0.15915494309189533586888376;
    constexpr static T const    e            = 2.7182818284590452353602874;
    constexpr static T const    sqrt_two     = 1.4142135623730950488016887;
    constexpr static T const    inv_sqrt_two = 0.70710678118654752440084436;
    constexpr static T const    phi          = 1.6180339887498948482045868;
    constexpr static T const    delta        = 0;
};

template<>
class cnst<float> {
public:
    constexpr static float const    zero         = 0.0f;
    constexpr static float const    one          = 1.0f;
    constexpr static float const    two          = 2.0f;
    constexpr static float const    ten          = 10.0f;
    constexpr static float const    hundred      = 100.0f;
    constexpr static float const    neg_one      = -1.0f;
    constexpr static float const    pi           = 3.1415926535897932384626433f;
    constexpr static float const    tau          = 6.2831853071795864769252867f;
    constexpr static float const    inv_pi       = 0.31830988618379067153776752f;
    constexpr static float const    inv_tau      = 0.15915494309189533586888376f;
    constexpr static float const    e            = 2.7182818284590452353602874f;
    constexpr static float const    sqrt_two     = 1.4142135623730950488016887f;
    constexpr static float const    inv_sqrt_two = 0.70710678118654752440084436f;
    constexpr static float const    phi          = 1.6180339887498948482045868f;
    constexpr static float const    delta = 0.00001f;
};

template<>
class cnst<double> {
public:
    constexpr static double const    zero         = 0.0;
    constexpr static double const    one          = 1.0;
    constexpr static double const    two          = 2.0;
    constexpr static double const    ten          = 10.0;
    constexpr static double const    hundred      = 100.0;
    constexpr static double const    neg_one      = -1.0;
    constexpr static double const    pi           = 3.1415926535897932384626433;
    constexpr static double const    tau          = 6.2831853071795864769252867;
    constexpr static double const    inv_pi       = 0.31830988618379067153776752;
    constexpr static double const    inv_tau      = 0.15915494309189533586888376;
    constexpr static double const    e            = 2.7182818284590452353602874;
    constexpr static double const    sqrt_two     = 1.4142135623730950488016887;
    constexpr static double const    inv_sqrt_two = 0.70710678118654752440084436;
    constexpr static double const    phi          = 1.6180339887498948482045868;
    constexpr static double const    delta        = 0.0000000001;
};

#endif