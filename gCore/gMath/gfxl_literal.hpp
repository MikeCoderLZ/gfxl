template< typename T >
class lit {
public:
    constexpr static T const    pi             = 3.1415926535897932384626433;
    constexpr static T const    tau            = 6.2831853071795864769252867;
    constexpr static T const    invPi          = 0.31830988618379067153776752;
    constexpr static T const    invTau         = 0.15915494309189533586888376;
    constexpr static T const    e              = 2.7182818284590452353602874;
    constexpr static T const    sqrtTwo        = 1.4142135623730950488016887;
    constexpr static T const    invSqrtTwo     = 0.70710678118654752440084436;
    constexpr static T const    sqrtThree      = 1.7320508075688772935274463;
    constexpr static T const    invSqrtThree   = 0.57735026919;
    constexpr static T const    phi            = 1.6180339887498948482045868;
    constexpr static T const    delta          = 1.0;
};

template<>
class lit<float> {
public:
    constexpr static float const    pi             = 3.1415926535897932384626433f;
    constexpr static float const    tau            = 6.2831853071795864769252867f;
    constexpr static float const    invPi          = 0.31830988618379067153776752f;
    constexpr static float const    invTau         = 0.15915494309189533586888376f;
    constexpr static float const    e              = 2.7182818284590452353602874f;
    constexpr static float const    sqrtTwo        = 1.4142135623730950488016887f;
    constexpr static float const    invSqrtTwo     = 0.70710678118654752440084436f;
    constexpr static float const    sqrtThree      = 1.7320508075688772935274463f;
    constexpr static float const    invSqrtThree   = 0.57735026919f;
    constexpr static float const    phi            = 1.6180339887498948482045868f;
    constexpr static float const    delta          = 0.00001f;
};

template<>
class lit<double> {
public:
    constexpr static double const    pi             = 3.1415926535897932384626433;
    constexpr static double const    tau            = 6.2831853071795864769252867;
    constexpr static double const    invPi          = 0.31830988618379067153776752;
    constexpr static double const    invTau         = 0.15915494309189533586888376;
    constexpr static double const    e              = 2.7182818284590452353602874;
    constexpr static double const    sqrtTwo        = 1.4142135623730950488016887;
    constexpr static double const    invSqrtTwo     = 0.70710678118654752440084436;
    constexpr static double const    sqrtThree      = 1.7320508075688772935274463;
    constexpr static double const    invSqrtThree   = 0.57735026919;
    constexpr static double const    phi            = 1.6180339887498948482045868;
    constexpr static double const    delta          = 0.0000000001;
};