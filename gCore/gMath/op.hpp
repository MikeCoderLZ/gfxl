#ifndef OP_HPP
#define OP_HPP

#include "datatype.hpp"
#include "constant.hpp"

namespace gfx {

/**
template< typename T >
vec4 operator*( T lhs, vec4 const& rhs );
template< typename T >
vec3 operator*( T lhs, vec3 const& rhs );
template< typename T >
vec2 operator*( T lhs, vec2 const& rhs );

template< typename T >
vec4 operator*( vec4 const& lhs, T rhs );
template< typename T >
vec3 operator*( vec3 const& lhs, T rhs );
template< typename T >
vec2 operator*( vec2 const& lhs, T rhs );

template< typename T >
mat operator*( T lhs, mat const& rhs );
template< typename T >
mat operator*( mat const& lhs, T rhs );

template< typename T >
qutn operator*( float lhs, qutn const& rhs );
template< typename T >
qutn operator*( qutn const& lhs, float rhs );

template< typename T >
vec4 operator*( mat const& lhs, vec4 const& rhs );
template< typename T >
vec3 operator*( mat const& lhs, vec3 const& rhs );
template< typename T >
vec2 operator*( mat const& lhs, vec2 const& rhs );

template< typename T >
vec4 operator*( vec4 const& lhs, mat const& rhs );
template< typename T >
vec3 operator*( vec3 const& lhs, mat const& rhs );
template< typename T >
vec2 operator*( vec2 const& lhs, mat const& rhs );
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

class __normalize__ : public unary_op<vec4>,
                      public unary_op<vec3>,
                      public unary_op<vec2>,
                      public unary_op<mat>,
                      public unary_op<qutn>
{
    public:
        using unary_op<vec4>::operator();
        using unary_op<vec3>::operator();
        using unary_op<vec2>::operator();
        using unary_op<mat>::operator();
        using unary_op<qutn>::operator();
        friend class operator_factory;
        ~__normalize__() {}
    private:
        __normalize__() {};
        vec4 eval( vec4 const& ) const;
        vec3 eval( vec3 const& ) const;
        vec2 eval( vec2 const& ) const;
        mat eval( mat const& ) const;
        qutn eval( qutn const& ) const;
};

extern __normalize__ const norm;

class __orthogonalize__ : public binary_op<vec3>
                          //public binary_op<vec2>
                          //,public unary_op<mat>
{
    public:
        using binary_op<vec3>::operator();
        //using binary_op<vec2>::operator();
        //using unary_op<mat>::operator();
        friend class operator_factory;
        ~__orthogonalize__() {}
    private:
        __orthogonalize__() {}
        vec3 eval( vec3 const& vecA, vec3 const& vecB ) const;
        //vec2 eval( vec2 const& vecA, vec2 const& vecB ) const;
        //mat const eval( mat const& mat ) const;
};

extern __orthogonalize__ const ortho;

class __interpolator__ : public virtual ternary_op_exp<vec4, vec4, vec4, float>,
                         public virtual ternary_op_exp<vec3, vec3, vec3, float>,
                         public virtual ternary_op_exp<vec2, vec2, vec2, float>,
                         public virtual ternary_op<float>
{
     public:
         using ternary_op_exp<vec4, vec4, vec4, float>::operator();
         using ternary_op_exp<vec3, vec3, vec3, float>::operator();
         using ternary_op_exp<vec2, vec2, vec2, float>::operator();
         using ternary_op<float>::operator();
         friend class operator_factory;
         virtual ~__interpolator__() {}
    protected:
         __interpolator__() {}
    private:
         virtual vec4 eval( vec4 const& vecA, vec4 const& vecB, float const& p ) const = 0;
         virtual vec3 eval( vec3 const& vecA, vec3 const& vecB, float const& p ) const = 0;
         virtual vec2 eval( vec2 const& vecA, vec2 const& vecB, float const& p ) const = 0;
         virtual float eval( float const& a, float const& b, float const& p ) const = 0;
};

class __threshold__ : public __interpolator__ {
    public:
        friend class operator_factory;
        ~__threshold__() {}
    private:
        __threshold__() {}
        vec4 eval( vec4 const& vecA, vec4 const& vecB, float const& p ) const;
        vec3 eval( vec3 const& vecA, vec3 const& vecB, float const& p ) const;
        vec2 eval( vec2 const& vecA, vec2 const& vecB, float const& p ) const;
        float eval( float const& a, float const& b, float const& p ) const;
};

extern __threshold__ const mix_th;

class __linear__ : public __interpolator__ {
    public:
        friend class operator_factory;
        ~__linear__() {}
    private:
        __linear__() {}
        vec4 eval( vec4 const& vecA, vec4 const& vecB, float const& p ) const;
        vec3 eval( vec3 const& vecA, vec3 const& vecB, float const& p ) const;
        vec2 eval( vec2 const& vecA, vec2 const& vecB, float const& p ) const;
        float eval( float const& a, float const& b, float const& p ) const;
};

extern __linear__ const mix_ln;

class __cubic__ : public __interpolator__ {
    public:
        friend class operator_factory;
        ~__cubic__() {}
    private:
        __cubic__() {}
        vec4 eval( vec4 const& vecA, vec4 const& vecB, float const& p ) const;
        vec3 eval( vec3 const& vecA, vec3 const& vecB, float const& p ) const;
        vec2 eval( vec2 const& vecA, vec2 const& vecB, float const& p ) const;
        float eval( float const& a, float const& b, float const& p ) const;
};

extern __cubic__ const mix_cb;

class __outer_product__ : public binary_op<vec3> {
    public:
        using binary_op<vec3>::operator();
        friend class operator_factory;
        ~__outer_product__() {}
    private:
        __outer_product__() {}
        vec3 eval( vec3 const& vecA, vec3 const& vecB ) const;
};

extern __outer_product__ const cross;

class __inner_product__ : public binary_op_exp<float, vec4, vec4>,
                          public binary_op_exp<float, vec3, vec3>,
                          public binary_op_exp<float, vec2, vec2>
{
    public:
        using binary_op_exp<float, vec4, vec4>::operator();
        using binary_op_exp<float, vec3, vec3>::operator();
        using binary_op_exp<float, vec2, vec2>::operator();
        friend class operator_factory;
        ~__inner_product__() {}
    private:
        __inner_product__() {}
        float eval( vec4 const& vecA, vec4 const& vecB ) const;
        float eval( vec3 const& vecA, vec3 const& vecB ) const;
        float eval( vec2 const& vecA, vec2 const& vecB ) const;
};

extern __inner_product__ const dot;

class __magnitude__ : public unary_op_exp<float, vec4>,
                      public unary_op_exp<float, vec3>,
                      public unary_op_exp<float, vec2>
{
    public:
        using unary_op_exp<float, vec4>::operator();
        using unary_op_exp<float, vec3>::operator();
        using unary_op_exp<float, vec2>::operator();
        friend class operator_factory;
        ~__magnitude__() {}
    private:
        __magnitude__() {}
        float eval( vec4 const& vec ) const;
        float eval( vec3 const& vec ) const;
        float eval( vec2 const& vec ) const;
};

extern __magnitude__ const mag;

class __inverse_magnitude__ : public unary_op_exp<float, vec4>,
                              public unary_op_exp<float, vec3>,
                              public unary_op_exp<float, vec2>
 {
    public:
        using unary_op_exp<float, vec4>::operator();
        using unary_op_exp<float, vec3>::operator();
        using unary_op_exp<float, vec2>::operator();
        friend class operator_factory;
        ~__inverse_magnitude__() {}
    private:
        __inverse_magnitude__() {}
        float eval( vec4 const& vec ) const;
        float eval( vec3 const& vec ) const;
        float eval( vec2 const& vec ) const;
};

extern __inverse_magnitude__ const inv_mag;

class __transpose__ : public unary_op<mat> {
    public:
        using unary_op<mat>::operator();
        friend class operator_factory;
        ~__transpose__() {}
    private:
        __transpose__() {}
        mat eval( mat const& amat ) const;
};

extern __transpose__ const transpose;

class __homogenize__ : public unary_op<mat> {
    public:
        using unary_op<mat>::operator();
        friend class operator_factory;
        ~__homogenize__() {}
    private:
        __homogenize__() {}
        mat eval( mat const& mat ) const;
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

// template< typename T >
// class angle_t {
//     public:
//         static angle_t<T> in_rads( T in_rads );
//         static angle_t<T> in_grads( T in_grads );
//         static angle_t<T> in_degs( T in_degs );
//         
//         T to_rads();
//         T to_grads();
//         T to_degs();
//     private:
//         angle_t( T new_unians ) : unians (new_unians) {};
//         T unians;
// };
// 
// typedef angle_t<float> angle;
// typedef angle_t<double> d_angle;

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
 */

/**
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

*/

}
#endif
