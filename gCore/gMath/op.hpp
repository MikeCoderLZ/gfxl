#ifndef OP_HPP
#define OP_HPP

#include "datatype.hpp"

namespace gfx {

template< typename T >
class cnst {
public:
    constexpr static T const    pi           = 3.1415926535897932384626433;
    constexpr static T const    tau          = 6.2831853071795864769252867;
    constexpr static T const    inv_pi       = 0.31830988618379067153776752;
    constexpr static T const    inv_tau      = 0.15915494309189533586888376;
    constexpr static T const    e            = 2.7182818284590452353602874;
    constexpr static T const    sqrt_two     = 1.4142135623730950488016887;
    constexpr static T const    inv_sqrt_two = 0.70710678118654752440084436;
    constexpr static T const    phi          = 1.6180339887498948482045868;
    
};

template<>
class cnst<double> {
public:
    constexpr static double const    pi           = 3.1415926535897932384626433;
    constexpr static double const    tau          = 6.2831853071795864769252867;
    constexpr static double const    inv_pi       = 0.31830988618379067153776752;
    constexpr static double const    inv_tau      = 0.15915494309189533586888376;
    constexpr static double const    e            = 2.7182818284590452353602874;
    constexpr static double const    sqrt_two     = 1.4142135623730950488016887;
    constexpr static double const    inv_sqrt_two = 0.70710678118654752440084436;
    constexpr static double const    phi          = 1.6180339887498948482045868;
};

template<>
class cnst<float> {
public:
    constexpr static float const    pi           = 3.1415926535897932384626433f;
    constexpr static float const    tau          = 6.2831853071795864769252867f;
    constexpr static float const    inv_pi       = 0.31830988618379067153776752f;
    constexpr static float const    inv_tau      = 0.15915494309189533586888376f;
    constexpr static float const    e            = 2.7182818284590452353602874f;
    constexpr static float const    sqrt_two     = 1.4142135623730950488016887f;
    constexpr static float const    inv_sqrt_two = 0.70710678118654752440084436f;
    constexpr static float const    phi          = 1.6180339887498948482045868f;
};

/**
template< typename T >
fvec4 operator*( T lhs, fvec4 const& rhs );
template< typename T >
fvec3 operator*( T lhs, fvec3 const& rhs );
template< typename T >
fvec2 operator*( T lhs, fvec2 const& rhs );

template< typename T >
fvec4 operator*( fvec4 const& lhs, T rhs );
template< typename T >
fvec3 operator*( fvec3 const& lhs, T rhs );
template< typename T >
fvec2 operator*( fvec2 const& lhs, T rhs );

template< typename T >
fmat operator*( T lhs, fmat const& rhs );
template< typename T >
fmat operator*( fmat const& lhs, T rhs );

template< typename T >
qutn operator*( float lhs, qutn const& rhs );
template< typename T >
qutn operator*( qutn const& lhs, float rhs );

template< typename T >
fvec4 operator*( fmat const& lhs, fvec4 const& rhs );
template< typename T >
fvec3 operator*( fmat const& lhs, fvec3 const& rhs );
template< typename T >
fvec2 operator*( fmat const& lhs, fvec2 const& rhs );

template< typename T >
fvec4 operator*( fvec4 const& lhs, fmat const& rhs );
template< typename T >
fvec3 operator*( fvec3 const& lhs, fmat const& rhs );
template< typename T >
fvec2 operator*( fvec2 const& lhs, fmat const& rhs );
*/

/*
 * Okay, this is where things get a little complicated.
 * The operator type classes are meant to work like intrinsic
 * functions.  In order to organize the functionality, each
 * operation is represented by a single instance of a class
 * which has functional operator overloads for each data type
 * it operates on.
 *
 * The complicated part is that some operators have different
 * semantics for different data types and the wealth of operators
 * means that keeping all of the interfaces correct is a bit of
 * a maintenance nightmare.  So, there are three groups of
 * template classes, Unary, Binary, and Ternary.  These templates
 * specify an interface for their given data types in a way that
 * standardizes them.  Each functional object then multiply
 * inherits from these templates.
 *
 * The result is that each operator object 'stacks' interfaces
 * together so that all have standardized functionality but
 * different selections of that functionality.  It also very
 * explicitly documents how each operator works.
 *
 * Its also a little esoteric and insane; I wouldn't mess with it.
 */

// TODO This all needs to be integrated with the new types code.



class operator_factory;

template< typename ARG_T >
class unary_op {
    public:
        unary_op() {}
        ARG_T operator()( ARG_T const& arg ) const
            { return this->eval( arg ); }
        virtual ~unary_op() {}
    protected:
        virtual ARG_T eval( ARG_T const& arg ) const = 0;
};

template< typename RETURN_T,
          typename ARG_T >
class unary_op_exp {
    public:
        unary_op_exp() {}
        RETURN_T operator()( ARG_T const& arg ) const
            { return this->eval( arg ); }
        virtual ~unary_op_exp() {}
    protected:
        virtual RETURN_T eval( ARG_T const& arg ) const = 0;
};

template < typename ARG_T >
class binary_op {
    public:
        binary_op() {}
        ARG_T operator()( ARG_T const& arg1,
                          ARG_T const& arg2 ) const
            { return this->eval( arg1, arg2 ); }
        virtual ~binary_op() {}
    protected:
        virtual ARG_T eval( ARG_T const& arg1,
                            ARG_T const& arg2 ) const = 0;
};

template < typename RETURN_T,
           typename ARG1_T,
           typename ARG2_T >
class binary_op_exp {
    public:
        binary_op_exp() {}
        RETURN_T operator()( ARG1_T const& arg1,
                             ARG2_T const& arg2 ) const
            { return this->eval( arg1, arg2 ); }
        virtual ~binary_op_exp() {}
    protected:
        virtual RETURN_T eval( ARG1_T const& arg1,
                               ARG2_T const& arg2 ) const = 0;
};

template < typename ARG_T >
class ternary_op {
    public:
        ternary_op() {}
        ARG_T operator()( ARG_T const& arg1,
                          ARG_T const& arg2,
                          ARG_T const& arg3 ) const
            { return this->eval( arg1, arg2, arg3 ); }
        virtual ~ternary_op() {}
    private:
        virtual ARG_T eval( ARG_T const& arg1,
                            ARG_T const& arg2,
                            ARG_T const& arg3 ) const = 0;
};

template < typename RETURN_T,
           typename ARG1_T,
           typename ARG2_T,
           typename ARG3_T >
class ternary_op_exp {
    public:
        ternary_op_exp() {}
        RETURN_T operator()( ARG1_T const& arg1,
                             ARG2_T const& arg2,
                             ARG3_T const& arg3 ) const
            { return this->eval( arg1, arg2, arg3 ); }
        virtual ~ternary_op_exp() {}
    private:
        virtual RETURN_T eval( ARG1_T const& arg1,
                               ARG2_T const& arg2,
                               ARG3_T const& arg3 ) const = 0;
};

class __normalize__ : public unary_op<fvec4>,
                      public unary_op<fvec3>,
                      public unary_op<fvec2>,
                      public unary_op<fmat>,
                      public unary_op<qutn>
{
    public:
        using unary_op<fvec4>::operator();
        using unary_op<fvec3>::operator();
        using unary_op<fvec2>::operator();
        using unary_op<fmat>::operator();
        using unary_op<qutn>::operator();
        friend class operator_factory;
        ~__normalize__() {}
    private:
        __normalize__() {};
        fvec4 eval( fvec4 const& ) const;
        fvec3 eval( fvec3 const& ) const;
        fvec2 eval( fvec2 const& ) const;
        fmat eval( fmat const& ) const;
        qutn eval( qutn const& ) const;
};

extern __normalize__ const norm;

class __orthogonalize__ : public binary_op<fvec3>,
                          public binary_op<fvec2>
                          //,public unary_op<fmat>
{
    public:
        using binary_op<fvec3>::operator();
        using binary_op<fvec2>::operator();
        //using unary_op<fmat>::operator();
        friend class operator_factory;
        ~__orthogonalize__() {}
    private:
        __orthogonalize__() {}
        fvec3 eval( fvec3 const& vecA, fvec3 const& vecB ) const;
        fvec2 eval( fvec2 const& vecA, fvec2 const& vecB ) const;
        //fmat const eval( fmat const& fmat ) const;
};

extern __orthogonalize__ const ortho;

class __interpolator__ : public virtual ternary_op_exp<fvec4, fvec4, fvec4, float>,
                         public virtual ternary_op_exp<fvec3, fvec3, fvec3, float>,
                         public virtual ternary_op_exp<fvec2, fvec2, fvec2, float>,
                         public virtual ternary_op<float>
{
     public:
         using ternary_op_exp<fvec4, fvec4, fvec4, float>::operator();
         using ternary_op_exp<fvec3, fvec3, fvec3, float>::operator();
         using ternary_op_exp<fvec2, fvec2, fvec2, float>::operator();
         using ternary_op<float>::operator();
         friend class operator_factory;
         virtual ~__interpolator__() {}
    protected:
         __interpolator__() {}
    private:
         virtual fvec4 eval( fvec4 const& vecA, fvec4 const& vecB, float const& p ) const = 0;
         virtual fvec3 eval( fvec3 const& vecA, fvec3 const& vecB, float const& p ) const = 0;
         virtual fvec2 eval( fvec2 const& vecA, fvec2 const& vecB, float const& p ) const = 0;
         virtual float eval( float const& a, float const& b, float const& p ) const = 0;
};

class __threshold__ : public __interpolator__ {
    public:
        friend class operator_factory;
        ~__threshold__() {}
    private:
        __threshold__() {}
        fvec4 eval( fvec4 const& vecA, fvec4 const& vecB, float const& p ) const;
        fvec3 eval( fvec3 const& fvec3, fvec3 const& vecB, float const& p ) const;
        fvec2 eval( fvec2 const& fvec2, fvec2 const& vecB, float const& p ) const;
        float eval( float const& a, float const& b, float const& p ) const;
};

extern __threshold__ const mix_th;

class __linear__ : public __interpolator__ {
    public:
        friend class operator_factory;
        ~__linear__() {}
    private:
        __linear__() {}
        fvec4 eval( fvec4 const& vecA, fvec4 const& vecB, float const& p ) const;
        fvec3 eval( fvec3 const& fvec3, fvec3 const& vecB, float const& p ) const;
        fvec2 eval( fvec2 const& fvec2, fvec2 const& vecB, float const& p ) const;
        float eval( float const& a, float const& b, float const& p ) const;
};

extern __linear__ const mix_ln;

class __cubic__ : public __interpolator__ {
    public:
        friend class operator_factory;
        ~__cubic__() {}
    private:
        __cubic__() {}
        fvec4 eval( fvec4 const& vecA, fvec4 const& vecB, float const& p ) const;
        fvec3 eval( fvec3 const& fvec3, fvec3 const& vecB, float const& p ) const;
        fvec2 eval( fvec2 const& fvec2, fvec2 const& vecB, float const& p ) const;
        float eval( float const& a, float const& b, float const& p ) const;
};

extern __cubic_ const mix_cb;

class __outer_product__ : public binary_op<fvec3> {
    public:
        using binary_op<fvec3>::operator();
        friend class operator_factory;
        ~__outer_product__() {}
    private:
        __outer_product__() {}
        fvec3 eval( fvec3 const& vecA, fvec3 const& vecB ) const;
};

extern __outer_product__ const cross;

class __inner_product__ : public binary_op_exp<float, fvec4, fvec4>,
                          public binary_op_exp<float, fvec3, fvec3>,
                          public binary_op_exp<float, fvec2, fvec2>
{
    public:
        using binary_op_exp<float, fvec4, fvec4>::operator();
        using binary_op_exp<float, fvec3, fvec3>::operator();
        using binary_op_exp<float, fvec2, fvec2>::operator();
        friend class operator_factory;
        ~__inner_product__() {}
    private:
        __inner_product__() {}
        float eval( fvec4 const& vecA, fvec4 const& vecB ) const;
        float eval( fvec3 const& vecA, fvec3 const& vecB ) const;
        float eval( fvec2 const& vecA, fvec2 const& vecB ) const;
};

extern __inner_product__ const dot;

class __magnitude__ : public unary_op_exp<float, fvec4>,
                      public unary_op_exp<float, fvec3>,
                      public unary_op_exp<float, fvec2>
{
    public:
        using unary_op_exp<float, fvec4>::operator();
        using unary_op_exp<float, fvec3>::operator();
        using unary_op_exp<float, fvec2>::operator();
        friend class operator_factory;
        ~__magnitude__() {}
    private:
        __magnitude__() {}
        float eval( fvec4 const& vec ) const;
        float eval( fvec3 const& vec ) const;
        float eval( fvec2 const& vec ) const;
};

extern __magnitude__ const mag;

class __inverse_magnitude__ : public unary_op_exp<float, fvec4>,
                              public unary_op_exp<float, fvec3>,
                              public unary_op_exp<float, fvec2>
 {
    public:
        using unary_op_exp<float, fvec4>::operator();
        using unary_op_exp<float, fvec3>::operator();
        using unary_op_exp<float, fvec2>::operator();
        friend class operator_factory;
        ~__inverse_magnitude__() {}
    private:
        __inverse_magnitude__() {}
        float eval( fvec4 const& vec ) const;
        float eval( fvec3 const& vec ) const;
        float eval( fvec2 const& vec ) const;
};

extern __inverse_magnitude__ const inv_mag;

class __transpose__ : public unary_op<fmat> {
    public:
        using unary_op<fmat>::operator();
        friend class operator_factory;
        ~__transpose__() {}
    private:
        __transpose__() {}
        fmat eval( fmat const& fmat ) const;
};

extern __transpose__ const transpose;

class __homogenize__ : public unary_op<fmat> {
    public:
        using unary_op<fmat>::operator();
        friend class operator_factory;
        ~__homogenize__() {}
    private:
        __homogenize__() {}
        fmat eval( fmat const& fmat ) const;
};

extern __homogenize__ const homogenize;

class __clip_range__ : public ternary_op<float> {
    public:
        using ternary_op<float>::operator();
        friend class operator_factory;
        ~__clip_range__() {}
    private:
        __clip_range__() {}
        float eval( float const& value, float const& min, float const& max ) const;
};

extern __clip_range__ const clip_rng;

template< typename T >
class angle {
    public:
        static angle<T> in_rads( T in_rads );
        static angle<T> in_grads( T in_grads );
        static angle<T> in_degs( T in_degs );
        
        T to_rads();
        T to_grads();
        T to_degs();
    private:
        angle( T new_unians ) : unians (new_unians) {};
        T unians;
};

typedef angle<double> d_angle;
typedef angle<float> f_angle;


/**
class ClipMaximum {
    public:
    ClipMaximum() {};
    float operator()( float value, float max ) const;
};

extern ClipMaximum const clip_max;

class ClipMinimum {
    public:
    ClipMinimum() {};
    float operator()( float value, float min ) const;
};

extern ClipMinimum const clip_min;
*/

/**
 * The Converter class represents functors that convert values to native
 * Radians.
 * /

class Converter {
    public:
        virtual float operator()( float value ) const = 0;
        virtual double operator()( double value ) const = 0;
};

class FromDegrees : public Converter {
    public:
        FromDegrees() {};
        float operator()( float inDegrees ) const;
        double operator()( double inDegrees ) const;
};

extern FromDegrees const deg;

class FromGradians : public Converter {
    public:
        FromGradians() {};
        float operator()( float inGradians ) const;
        double operator()( double inGradians ) const;
};

extern FromGradians const grad;

class FromRadians : public Converter {
    public:
        FromRadians() {};
        float operator()( float inRadians ) const;
        double operator()( double inRadians ) const;
};

extern FromRadians const rad;

// Unians: 2*pi = 360 deg = 200 grads = 1 unn

class FromUnians : public Converter {
    public:
        FromUnians() {};
        float operator()( float inUnits ) const;
        double operator()( double inUnits ) const;
};

extern FromUnians const unit;

// */

}
#endif
