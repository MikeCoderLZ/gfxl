#ifndef OP_HPP
#define OP_HPP

namespace gfx {

//extern double const IN_DEGREES;
//extern double const IN_RADIANS;

extern double const G_PI;
extern double const G_TAU;
extern double const G_INV_PI;
extern double const G_INV_TAU;

extern double const G_PI_F;
extern double const G_TAU_F;
extern double const G_INV_PI_F;
extern double const G_INV_TAU_F;


class Mat;
class Vec4;
class Vec3;
class Vec2;
class Qutn;

Vec4 operator*( float lhs, Vec4 const& rhs );
Vec3 operator*( float lhs, Vec3 const& rhs );
Vec2 operator*( float lhs, Vec2 const& rhs );

Vec4 operator*( Vec4 const& lhs, float rhs );
Vec3 operator*( Vec3 const& lhs, float rhs );
Vec2 operator*( Vec2 const& lhs, float rhs );

Mat operator*( float lhs, Mat const& rhs );
Mat operator*( Mat const& lhs, float rhs );

Qutn operator*( float lhs, Qutn const& rhs );
Qutn operator*( Qutn const& lhs, float rhs );

Vec4 operator*( Mat const& lhs, Vec4 const& rhs );
Vec3 operator*( Mat const& lhs, Vec3 const& rhs );
Vec2 operator*( Mat const& lhs, Vec2 const& rhs );

Vec4 operator*( Vec4 const& lhs, Mat const& rhs );
Vec3 operator*( Vec3 const& lhs, Mat const& rhs );
Vec2 operator*( Vec2 const& lhs, Mat const& rhs );

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


class OperatorFactory;

template< typename OPERAND_T >
class UnaryOp {
    public:
        UnaryOp() {}
        OPERAND_T operator()( OPERAND_T const& aDatum ) const
            { return this->eval( aDatum ); }
        virtual ~UnaryOp() {}
    protected:
        virtual OPERAND_T eval( OPERAND_T const& aDatum ) const = 0;
};

template< typename RETURN_T,
          typename OPERAND_T >
class UnaryOp_Exp {
    public:
        UnaryOp_Exp() {}
        RETURN_T operator()( OPERAND_T const& aDatum ) const
            { return this->eval( aDatum ); }
        virtual ~UnaryOp_Exp() {}
    protected:
        virtual RETURN_T eval( OPERAND_T const& aDatum ) const = 0;
};

template < typename OPERAND_T >
class BinaryOp {
    public:
        BinaryOp() {}
        OPERAND_T operator()( OPERAND_T const& aDatum,
                              OPERAND_T const& bDatum ) const
            { return this->eval( aDatum, bDatum ); }
        virtual ~BinaryOp() {}
    protected:
        virtual OPERAND_T eval( OPERAND_T const& aDatum,
                                OPERAND_T const& bDatum ) const = 0;
};

template < typename RETURN_T,
           typename A_OPERAND_T,
           typename B_OPERAND_T >
class BinaryOp_Exp {
    public:
        BinaryOp_Exp() {}
        RETURN_T operator()( A_OPERAND_T const& aDatum,
                             B_OPERAND_T const& bDatum ) const
            { return this->eval( aDatum, bDatum ); }
        virtual ~BinaryOp_Exp() {}
    protected:
        virtual RETURN_T eval( A_OPERAND_T const& aDatum,
                               B_OPERAND_T const& bDatum ) const = 0;
};

template < typename OPERAND_T >
class TernaryOp {
    public:
        TernaryOp() {}
        OPERAND_T operator()( OPERAND_T const& aDatum,
                              OPERAND_T const& bDatum,
                              OPERAND_T const& cDatum ) const
            { return this->eval( aDatum, bDatum, cDatum ); }
        virtual ~TernaryOp() {}
    private:
        virtual OPERAND_T eval( OPERAND_T const& aDatum,
                                OPERAND_T const& bDatum,
                                OPERAND_T const& cDatum ) const = 0;
};

template < typename RETURN_T,
           typename A_OPERAND_T,
           typename B_OPERAND_T,
           typename C_OPERAND_T >
class TernaryOp_Exp {
    public:
        TernaryOp_Exp() {}
        RETURN_T operator()( A_OPERAND_T const& aDatum,
                             B_OPERAND_T const& bDatum,
                             C_OPERAND_T const& cDatum ) const
            { return this->eval( aDatum, bDatum, cDatum ); }
        virtual ~TernaryOp_Exp() {}
    private:
        virtual RETURN_T eval( A_OPERAND_T const& aDatum,
                               B_OPERAND_T const& bDatum,
                               C_OPERAND_T const& cDatum ) const = 0;
};

class Normalize : public UnaryOp<Vec4>,
                  public UnaryOp<Vec3>,
                  public UnaryOp<Vec2>,
                  public UnaryOp<Mat>,
                  public UnaryOp<Qutn>
{
    public:
        using UnaryOp<Vec4>::operator();
        using UnaryOp<Vec3>::operator();
        using UnaryOp<Vec2>::operator();
        using UnaryOp<Mat>::operator();
        using UnaryOp<Qutn>::operator();
        friend class OperatorFactory;
        ~Normalize() {}
    private:
        Normalize() {};
        Vec4 eval( Vec4 const& ) const;
        Vec3 eval( Vec3 const& ) const;
        Vec2 eval( Vec2 const& ) const;
        Mat eval( Mat const& ) const;
        Qutn eval( Qutn const& ) const;
};

extern Normalize const norm;

class Orthogonalize : public BinaryOp<Vec3>,
                      public BinaryOp<Vec2>
                      //,public UnaryOp<Mat>
{
    public:
        using BinaryOp<Vec3>::operator();
        using BinaryOp<Vec2>::operator();
        //using UnaryOp<Mat>::operator();
        friend class OperatorFactory;
        ~Orthogonalize() {}
    private:
        Orthogonalize() {}
        Vec3 eval( Vec3 const& vecA, Vec3 const& vecB ) const;
        Vec2 eval( Vec2 const& vecA, Vec2 const& vecB ) const;
        //Mat const eval( Mat const& mat ) const;
};

extern Orthogonalize const ortho;

class Interpolator : public virtual TernaryOp_Exp<Vec4, Vec4, Vec4, float>,
                     public virtual TernaryOp_Exp<Vec3, Vec3, Vec3, float>,
                     public virtual TernaryOp_Exp<Vec2, Vec2, Vec2, float>,
                     public virtual TernaryOp<float>
{
     public:
         using TernaryOp_Exp<Vec4, Vec4, Vec4, float>::operator();
         using TernaryOp_Exp<Vec3, Vec3, Vec3, float>::operator();
         using TernaryOp_Exp<Vec2, Vec2, Vec2, float>::operator();
         using TernaryOp<float>::operator();
         friend class OperatorFactory;
         virtual ~Interpolator() {}
    protected:
         Interpolator() {}
    private:
         virtual Vec4 eval( Vec4 const& vecA, Vec4 const& vecB, float const& p ) const = 0;
         virtual Vec3 eval( Vec3 const& vecA, Vec3 const& vecB, float const& p ) const = 0;
         virtual Vec2 eval( Vec2 const& vecA, Vec2 const& vecB, float const& p ) const = 0;
         virtual float eval( float const& a, float const& b, float const& p ) const = 0;
};

class Threshold : public Interpolator {
    public:
        friend class OperatorFactory;
        ~Threshold() {}
    private:
        Threshold() {}
        Vec4 eval( Vec4 const& vecA, Vec4 const& vecB, float const& p ) const;
        Vec3 eval( Vec3 const& vec3, Vec3 const& vecB, float const& p ) const;
        Vec2 eval( Vec2 const& vec2, Vec2 const& vecB, float const& p ) const;
        float eval( float const& a, float const& b, float const& p ) const;
};

extern Threshold const mix_th;

class Linear : public Interpolator {
    public:
        friend class OperatorFactory;
        ~Linear() {}
    private:
        Linear() {}
        Vec4 eval( Vec4 const& vecA, Vec4 const& vecB, float const& p ) const;
        Vec3 eval( Vec3 const& vec3, Vec3 const& vecB, float const& p ) const;
        Vec2 eval( Vec2 const& vec2, Vec2 const& vecB, float const& p ) const;
        float eval( float const& a, float const& b, float const& p ) const;
};

extern Linear const mix_ln;

class Cubic : public Interpolator {
    public:
        friend class OperatorFactory;
        ~Cubic() {}
    private:
        Cubic() {}
        Vec4 eval( Vec4 const& vecA, Vec4 const& vecB, float const& p ) const;
        Vec3 eval( Vec3 const& vec3, Vec3 const& vecB, float const& p ) const;
        Vec2 eval( Vec2 const& vec2, Vec2 const& vecB, float const& p ) const;
        float eval( float const& a, float const& b, float const& p ) const;
};

extern Cubic const mix_cb;

class OuterProduct : public BinaryOp<Vec3> {
    public:
        using BinaryOp<Vec3>::operator();
        friend class OperatorFactory;
        ~OuterProduct() {}
    private:
        OuterProduct() {}
        Vec3 eval( Vec3 const& vecA, Vec3 const& vecB ) const;
};

extern OuterProduct const cross;

class InnerProduct : public BinaryOp_Exp<float, Vec4, Vec4>,
                     public BinaryOp_Exp<float, Vec3, Vec3>,
                     public BinaryOp_Exp<float, Vec2, Vec2>
{
    public:
        using BinaryOp_Exp<float, Vec4, Vec4>::operator();
        using BinaryOp_Exp<float, Vec3, Vec3>::operator();
        using BinaryOp_Exp<float, Vec2, Vec2>::operator();
        friend class OperatorFactory;
        ~InnerProduct() {}
    private:
        InnerProduct() {}
        float eval( Vec4 const& vecA, Vec4 const& vecB ) const;
        float eval( Vec3 const& vecA, Vec3 const& vecB ) const;
        float eval( Vec2 const& vecA, Vec2 const& vecB ) const;
};

extern InnerProduct const dot;

class Magnitude : public UnaryOp_Exp<float, Vec4>,
                  public UnaryOp_Exp<float, Vec3>,
                  public UnaryOp_Exp<float, Vec2>
{
    public:
        using UnaryOp_Exp<float, Vec4>::operator();
        using UnaryOp_Exp<float, Vec3>::operator();
        using UnaryOp_Exp<float, Vec2>::operator();
        friend class OperatorFactory;
        ~Magnitude() {}
    private:
        Magnitude() {}
        float eval( Vec4 const& vec ) const;
        float eval( Vec3 const& vec ) const;
        float eval( Vec2 const& vec ) const;
};

extern Magnitude const mag;

class InverseMagnitude : public UnaryOp_Exp<float, Vec4>,
                         public UnaryOp_Exp<float, Vec3>,
                         public UnaryOp_Exp<float, Vec2>
 {
    public:
        using UnaryOp_Exp<float, Vec4>::operator();
        using UnaryOp_Exp<float, Vec3>::operator();
        using UnaryOp_Exp<float, Vec2>::operator();
        friend class OperatorFactory;
        ~InverseMagnitude() {}
    private:
        InverseMagnitude() {}
        float eval( Vec4 const& vec ) const;
        float eval( Vec3 const& vec ) const;
        float eval( Vec2 const& vec ) const;
};

extern InverseMagnitude const inv_mag;

class Transpose : public UnaryOp<Mat> {
    public:
        using UnaryOp<Mat>::operator();
        friend class OperatorFactory;
        ~Transpose() {}
    private:
        Transpose() {}
        Mat eval( Mat const& mat ) const;
};

extern Transpose const transpose;

class Homogenize : public UnaryOp<Mat> {
    public:
        using UnaryOp<Mat>::operator();
        friend class OperatorFactory;
        ~Homogenize() {}
    private:
        Homogenize() {}
        Mat eval( Mat const& mat ) const;
};

extern Homogenize const homogenize;

class ClipRange : public TernaryOp<float> {
    public:
        using TernaryOp<float>::operator();
        friend class OperatorFactory;
        ~ClipRange() {}
    private:
        ClipRange() {}
        float eval( float const& value, float const& min, float const& max ) const;
};

extern ClipRange const clip_rng;

template< typename DATA_T >
class Angle {
    public:
        static Angle<DATA_T> inRads( DATA_T inRads );
        static Angle<DATA_T> inGrads( DATA_T inGrads );
        static Angle<DATA_T> inDegs( DATA_T inDegs );
        
        DATA_T toRads();
        DATA_T toGrads();
        DATA_T toDegs();
    private:
        Angle( DATA_T newUnians ) : unians (newUnians) {};
        DATA_T unians;
};

typedef Angle<double> AngleD;
typedef Angle<float> AngleF;

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
