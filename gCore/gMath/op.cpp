#include <cstddef>
#include <stdexcept>
#include <cmath>
#include <iostream>

#include "./op.hpp"
#include "./vec.hpp"
#include "./matrix.hpp"
#include "./quaternion.hpp"

namespace gfx {

//double const IN_DEGREES = 180.0 / M_PI;
//double const IN_RADIANS = 1.0;

double const G_PI      = 3.1415926535897932384626433;
double const G_TAU     = 6.2831853071795864769252867;
double const G_INV_PI  = 0.31830988618379067153776752;
double const G_INV_TAU = 0.15915494309189533586888376;

double const G_PI_F      = 3.1415926535897932384626433F;
double const G_TAU_F     = 6.2831853071795864769252867F;
double const G_INV_PI_F  = 0.31830988618379067153776752F;
double const G_INV_TAU_F = 0.15915494309189533586888376F;



Vec4 operator*( float lhs, Vec4 const& rhs )
{
    return Vec4( rhs[0] * lhs, rhs[1] * lhs, rhs[2] * lhs, rhs[3] * lhs );
}

Vec3 operator*( float lhs, Vec3 const& rhs )
{
    return Vec3( rhs[0] * lhs, rhs[1] * lhs, rhs[2] * lhs );
}

Vec2 operator*( float lhs, Vec2 const& rhs )
{
    return Vec2( rhs[0] * lhs, rhs[1] * lhs );
}

Vec4 operator*( Vec4 const& lhs, float rhs )
{
    return Vec4( lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs );
}

Vec3 operator*( Vec3 const& lhs, float rhs )
{
    return Vec3( lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs );
}

Vec2 operator*( Vec2 const& lhs, float rhs )
{
    return Vec2( lhs[0] * rhs, lhs[1] * rhs );
}

Mat operator*( float lhs, Mat const& rhs )
{
    size_t i = 0;

    Mat out( rhs.nCols(), rhs.nRows() );

    for( i = 0; i < rhs.nRows() * rhs.nCols(); ++i ){
        out.e[i] = rhs.e[i] * lhs;
    }

    return out;
}

Mat operator*( Mat const& lhs, float rhs )
{
    size_t i = 0;

    Mat out( lhs.nCols(), lhs.nRows() );

    for( i = 0; i < lhs.nRows() * lhs.nCols(); ++i ){
        out.e[i] = lhs.e[i] * rhs;
    }

    return out;
}

Qutn operator*( float lhs, Qutn const& rhs )
{
    return Qutn( rhs[0] * lhs, rhs[1] * lhs, rhs[2] * lhs, rhs[3] * lhs );
}

Qutn operator*( Qutn const& lhs, float rhs )
{
    return Qutn( rhs * lhs[0], rhs * lhs[1], rhs * lhs[2], rhs * lhs[3] );
}

Vec4 operator*( Mat const& lhs, Vec4 const& rhs )
{
    if( lhs.nCols() != 4 || lhs.nRows() != 4 ){
        throw std::invalid_argument("dimension, column mismatch on matrix, vec4 multiply");
    }

    size_t row = 0;
    float sum = 0.0f;

    Vec4 out;

    for( row = 0; row < 4; ++row ){
        sum += lhs(0, row) * rhs[0];
        sum += lhs(1, row) * rhs[1];
        sum += lhs(2, row) * rhs[2];
        sum += lhs(3, row) * rhs[3];
        out[row] = sum;
        sum = 0.0f;
    }
    return out;
}

Vec3 operator*( Mat const& lhs, Vec3 const& rhs )
{
    if( lhs.nCols() != 3 || lhs.nRows() != 3 ){
        throw std::invalid_argument("dimension, column mismatch on matrix, vec3 multiply");
    }

    size_t row = 0;
    float sum = 0.0f;

    Vec3 out;

    for( row = 0; row < 3; ++row ){
        sum += lhs(0, row) * rhs[0];
        sum += lhs(1, row) * rhs[1];
        sum += lhs(2, row) * rhs[2];
        out[row] = sum;
        sum = 0.0f;
    }
    return out;
}

Vec2 operator*( Mat const& lhs, Vec2 const& rhs )
{
    if( lhs.nCols() != 2 || lhs.nRows() != 2 ){
        throw std::invalid_argument("dimension, column mismatch on matrix, vec2 multiply");
    }

    size_t row = 0;
    float sum = 0.0f;

    Vec2 out;

    for( row = 0; row < 2; ++row ){
        sum += lhs(0, row) * rhs[0];
        sum += lhs(1, row) * rhs[1];
        out[row] = sum;
        sum = 0.0f;
    }
    return out;
}

Vec4 operator*( Vec4 const& lhs, Mat const& rhs )
{
    if( rhs.nCols() != 4 || rhs.nRows() != 4 ){
        throw std::invalid_argument("dimension, column mismatch on vec4, matrix multiply");
    }

    size_t col = 0;
    float sum = 0.0f;

    Vec4 out;

    for( col = 0; col < 4; ++col ){
        sum += lhs[0] * rhs(col, 0);
        sum += lhs[1] * rhs(col, 1);
        sum += lhs[2] * rhs(col, 2);
        sum += lhs[3] * rhs(col, 3);
        out[col] = sum;
        sum = 0.0f;
    }
    return out;
}

Vec3 operator*( Vec3 const& lhs, Mat const& rhs )
{
    if( rhs.nCols() != 3 || rhs.nRows() != 3 ){
        throw std::invalid_argument("dimension, column mismatch on vec3, matrix multiply");
    }

    size_t col = 0;
    float sum = 0.0f;

    Vec3 out;

    for( col = 0; col < 3; ++col ){
        sum += lhs[0] * rhs(col, 0);
        sum += lhs[1] * rhs(col, 1);
        sum += lhs[2] * rhs(col, 2);
        out[col] = sum;
        sum = 0.0f;
    }
    return out;
}

Vec2 operator*( Vec2 const& lhs, Mat const& rhs )
{
    if( rhs.nCols() != 2 || rhs.nRows() != 2 ){
        throw std::invalid_argument("dimension, column mismatch on vec2, matrix multiply");
    }

    size_t col = 0;
    float sum = 0.0f;

    Vec2 out;

    for( col = 0; col < 2; ++col ){
        sum += lhs[0] * rhs(col, 0);
        sum += lhs[1] * rhs(col, 1);
        out[col] = sum;
        sum = 0.0f;
    }
    return out;
}

class OperatorFactory {
    public:
        OperatorFactory() {}
        static Normalize makeNormalize()
            { return Normalize(); }
        static Orthogonalize makeOrthogonalize()
            { return Orthogonalize(); }
        static Threshold makeThreshold()
            { return Threshold(); }
        static Linear makeLinear()
            { return Linear(); } 
        static Cubic makeCubic()
            { return Cubic(); }
        static OuterProduct makeOuterProduct()
            { return OuterProduct(); }
        static InnerProduct makeInnerProduct()
            { return InnerProduct(); }
        static Magnitude makeMagnitude()
            { return Magnitude(); }
        static InverseMagnitude makeInverseMagnitude()
            { return InverseMagnitude(); }
        static Transpose makeTranspose()
            { return Transpose(); }
        static Homogenize makeHomogenize()
            { return Homogenize(); }
        static ClipRange makeClipRange()
            { return ClipRange(); }
};

Vec4 Normalize::eval( Vec4 const& vec ) const
{
    Vec4 out = vec;

    float invMag = 1.0f / sqrt( vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] + vec[3]*vec[3] );

    return out*invMag;
}

Vec3 Normalize::eval( Vec3 const& vec ) const
{
    Vec3 out = vec;

    float invMag = 1.0f / sqrt( vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] );

    return out*invMag;
}

Vec2 Normalize::eval( Vec2 const& vec ) const
{
    Vec2 out = vec;

    float invMag = 1.0f / sqrt( vec[0]*vec[0] + vec[1]*vec[1] );

    return out*invMag;
}

Mat Normalize::eval( Mat const& mat ) const
{
    size_t row = 0;
    size_t col = 0;

    size_t nRows = mat.nRows();
    size_t nCols = mat.nCols();

    // Using double precision here promotes all operations to double _then_ truncates.
    // Slower, but more accurate and you should avoid matrix normalizations as much
    // as possible anyway so we have the budget and the need for more accuracy.
    double temp = 0.0;
    double invColMag = 0.0;

    Mat out (mat.nCols(), mat.nRows());

    // Normalize each column of the matrix
    for( col = 0; col < nCols; ++col ){
        for( row = 0; row < nRows; ++row ){
            temp = mat(col, row);
            invColMag += temp * temp;
        }
        invColMag = 1.0 / sqrt(invColMag);
        for( row = 0; row < nRows; ++row ){
            out(col, row) = mat(col, row) * invColMag;
        }
        invColMag = 0.0;
    }

    return out;
}

Qutn Normalize::eval( Qutn const& quat ) const
{
    Qutn out = quat;

    float invMag = 1.0f / sqrt(   quat[0]*quat[0]
                                + quat[1]*quat[1]
                                + quat[2]*quat[2]
                                + quat[3]*quat[3] );

    return out*invMag;
}


Normalize const norm = OperatorFactory::makeNormalize();

Vec3 Orthogonalize::eval( Vec3 const& vecA, Vec3 const& vecB ) const
{
    return cross( vecA, cross( vecB, vecA ));
}

Vec2 Orthogonalize::eval( Vec2 const& vecA, Vec2 const& vecB ) const
{
    Vec3 vecA3 (vecA[0], vecA[1], 0.0f );
    Vec3 vecB3 (vecB[0], vecB[1], 0.0f );
    Vec3 out3 = cross( vecA3, cross( vecB3, vecA3));

    return Vec2( out3[0], out3[1] );
}

Orthogonalize const ortho = OperatorFactory::makeOrthogonalize();

Vec4 Threshold::eval( Vec4 const& vecA, Vec4 const& vecB, float const& p ) const
{
    return p < 0.5f ? vecA : vecB;
}

Vec3 Threshold::eval( Vec3 const& vecA, Vec3 const& vecB, float const& p ) const
{
    return p < 0.5f ? vecA : vecB;
}

Vec2 Threshold::eval( Vec2 const& vecA, Vec2 const& vecB, float const& p ) const
{
    return p < 0.5f ? vecA : vecB;
}

float Threshold::eval( float const& a, float const& b, float const& p ) const
{
    return p < 0.5f ? a : b;
}


Threshold const mix_th = OperatorFactory::makeThreshold();

Vec4 Linear::eval( Vec4 const& vecA, Vec4 const& vecB, float const& p ) const
{
    return vecA + p * ( vecB - vecA );
}

Vec3 Linear::eval( Vec3 const& vecA, Vec3 const& vecB, float const& p ) const
{
    return vecA + p * ( vecB - vecA );
}

Vec2 Linear::eval( Vec2 const& vecA, Vec2 const& vecB, float const& p ) const
{
    return vecA + p * ( vecB - vecA );
}

float Linear::eval( float const& a, float const& b, float const& p ) const
{
    return a + p * ( b - a );
}

Linear const mix_ln = OperatorFactory::makeLinear();

Vec4 Cubic::eval( Vec4 const& vecA, Vec4 const& vecB, float const& p ) const
{
    return vecA + (p*p)*( 3.0f - 2.0f*p)*(vecB - vecA);
}

Vec3 Cubic::eval( Vec3 const& vecA, Vec3 const& vecB, float const& p ) const
{
    return vecA + (p*p)*( 3.0f - 2.0f*p)*(vecB - vecA);
}

Vec2 Cubic::eval( Vec2 const& vecA, Vec2 const& vecB, float const& p ) const
{
    return vecA + (p*p)*( 3.0f - 2.0f*p)*(vecB - vecA);
}

float Cubic::eval( float const& a, float const& b, float const& p ) const
{
    return a + ( 3.0f*p*p - 2.0f*p*p )*(b - a);
}

Cubic const mix_cb = OperatorFactory::makeCubic();

Vec3 OuterProduct::eval( Vec3 const& vecA, Vec3 const& vecB ) const
{
    return Vec3( vecA[1]*vecB[2] - vecA[2]*vecB[1],
                 vecA[2]*vecB[0] - vecA[0]*vecB[2],
                 vecA[0]*vecB[1] - vecA[1]*vecB[0] );
}

OuterProduct const cross = OperatorFactory::makeOuterProduct();

float InnerProduct::eval( Vec4 const& vecA, Vec4 const& vecB ) const
{
    return vecA[0]*vecB[0] + vecA[1]*vecB[1] + vecA[2]*vecB[2] + vecA[3]*vecB[3];
}

float InnerProduct::eval( Vec3 const& vecA, Vec3 const& vecB ) const
{
    return vecA[0]*vecB[0] + vecA[1]*vecB[1] + vecA[2]*vecB[2];
}

float InnerProduct::eval( Vec2 const& vecA, Vec2 const& vecB ) const
{
    return vecA[0]*vecB[0] + vecA[1]*vecB[1];
}

InnerProduct const dot = OperatorFactory::makeInnerProduct();

float Magnitude::eval( Vec4 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];
    float k = vec[2];
    float m = vec[3];

    return sqrt( i*i + j*j + k*k + m*m );
}

float Magnitude::eval( Vec3 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];
    float k = vec[2];

    return sqrt( i*i + j*j + k*k );
}

float Magnitude::eval( Vec2 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];

    return sqrt( i*i + j*j );
}

Magnitude const mag = OperatorFactory::makeMagnitude();

float InverseMagnitude::eval( Vec4 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];
    float k = vec[2];
    float m = vec[3];

    return 1.0f / sqrt( i*i + j*j + k*k + m*m );
}

float InverseMagnitude::eval( Vec3 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];
    float k = vec[2];

    return 1.0f / sqrt( i*i + j*j + k*k );
}

float InverseMagnitude::eval( Vec2 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];

    return 1.0f / sqrt( i*i + j*j );
}

InverseMagnitude const inv_mag = OperatorFactory::makeInverseMagnitude();

Mat Transpose::eval( Mat const& mat ) const
{
    Mat out ( mat.nRows(), mat.nCols() );

    size_t i = 0;
    size_t nElements = mat.size();

    for( i = 0; i < nElements; ++i ){
        out(i / out.nRows(), i % out.nRows() ) = mat( i % mat.nCols(), i / mat.nCols() );
    }

    return out;
}

Transpose const transpose = OperatorFactory::makeTranspose();

Mat Homogenize::eval( Mat const& mat ) const
{
    size_t cols = mat.nCols();
    size_t rows = mat.nRows();

    size_t dim = 0;

    if( rows >= cols ){
        dim = rows + 1;
    } else {
        dim = cols + 1;
    }

    Mat out = Mat::identity( dim);
    size_t size = dim * dim;

    size_t i = 0;

    bool colOutside = false;
    bool rowOutside = false;

    size_t row = 0;
    size_t col = 0;

    for( i =0; i < size; ++i ){
        col = i / dim;
        row = i % dim;
        colOutside = col >= cols;
        rowOutside = row >= rows;
    if ( colOutside && rowOutside ){
            break;
        } else if ( !(colOutside || rowOutside) ){
            out(col, row ) = mat( col, row );
        }
    }

    return out;
}

Homogenize const homogenize = OperatorFactory::makeHomogenize();

float ClipRange::eval( float const& value, float const& min, float const& max ) const
{
    return ( value < min ? min : ( value > max ? max : value ));
}

ClipRange const clip_rng = OperatorFactory::makeClipRange();

template < typename DATA_T >
Angle<DATA_T> Angle< DATA_T >::inRads( DATA_T inRads )
{
    return Angle<DATA_T>( inRads * G_INV_TAU );
}
template < typename DATA_T >
Angle<DATA_T> Angle< DATA_T >::inGrads( DATA_T inGrads )
{
    return Angle<DATA_T>( inGrads * 0.005 );
}
template < typename DATA_T >
Angle<DATA_T> Angle< DATA_T >::inDegs( DATA_T inDegs )
{
    return Angle<DATA_T>( inDegs * 0.00277777777777777777777777 );
}
template < typename DATA_T >
DATA_T Angle< DATA_T >::toRads()
{
    return unians * G_TAU;
}
template < typename DATA_T >
DATA_T Angle< DATA_T >::toGrads()
{
    return unians * 200.0;
}
template < typename DATA_T >
DATA_T Angle< DATA_T >::toDegs()
{
    return unians * 360.0;
}

/* ---- Float Specializations ---- */
template <>
AngleF AngleF::inRads( float inRads )
{
    return AngleF( inRads * G_INV_TAU_F );
}
template <>
AngleF AngleF::inGrads( float inGrads )
{
    return AngleF( inGrads * 0.005f );
}
template <>
AngleF AngleF::inDegs( float inDegs )
{
    return AngleF( inDegs * 0.002777777777777777777777777f );
}
template <>
float AngleF::toRads()
{
    return unians * G_TAU_F;
}
template <>
float AngleF::toGrads()
{
    return unians * 200.0f;
}
template <>
float AngleF::toDegs()
{
    return unians * 360.0f;
}

template class Angle< double >;
template class Angle< float >;

}
