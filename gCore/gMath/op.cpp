#include <cstddef>
#include <stdexcept>
#include <cmath>
#include <iostream>

#include "./datatype.hpp"
#include "./op.hpp"

namespace gfx {
/**
vec4 operator*( float lhs, vec4 const& rhs )
{
    return vec4( rhs[0] * lhs, rhs[1] * lhs, rhs[2] * lhs, rhs[3] * lhs );
}

vec3 operator*( float lhs, vec3 const& rhs )
{
    return vec3( rhs[0] * lhs, rhs[1] * lhs, rhs[2] * lhs );
}

vec2 operator*( float lhs, vec2 const& rhs )
{
    return vec2( rhs[0] * lhs, rhs[1] * lhs );
}

vec4 operator*( vec4 const& lhs, float rhs )
{
    return vec4( lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs );
}

vec3 operator*( vec3 const& lhs, float rhs )
{
    return vec3( lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs );
}

vec2 operator*( vec2 const& lhs, float rhs )
{
    return vec2( lhs[0] * rhs, lhs[1] * rhs );
}

mat operator*( float lhs, mat const& rhs )
{
    size_t i = 0;

    mat out( rhs.nCols(), rhs.nRows() );

    for( i = 0; i < rhs.nRows() * rhs.nCols(); ++i ){
        out.e[i] = rhs.e[i] * lhs;
    }

    return out;
}

mat operator*( mat const& lhs, float rhs )
{
    size_t i = 0;

    mat out( lhs.nCols(), lhs.nRows() );

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

vec4 operator*( mat const& lhs, vec4 const& rhs )
{
    if( lhs.nCols() != 4 || lhs.nRows() != 4 ){
        throw std::invalid_argument("dimension, column mismatch on matrix, vec4 multiply");
    }

    size_t row = 0;
    float sum = 0.0f;

    vec4 out;

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

vec3 operator*( mat const& lhs, vec3 const& rhs )
{
    if( lhs.nCols() != 3 || lhs.nRows() != 3 ){
        throw std::invalid_argument("dimension, column mismatch on matrix, vec3 multiply");
    }

    size_t row = 0;
    float sum = 0.0f;

    vec3 out;

    for( row = 0; row < 3; ++row ){
        sum += lhs(0, row) * rhs[0];
        sum += lhs(1, row) * rhs[1];
        sum += lhs(2, row) * rhs[2];
        out[row] = sum;
        sum = 0.0f;
    }
    return out;
}

vec2 operator*( mat const& lhs, vec2 const& rhs )
{
    if( lhs.nCols() != 2 || lhs.nRows() != 2 ){
        throw std::invalid_argument("dimension, column mismatch on matrix, vec2 multiply");
    }

    size_t row = 0;
    float sum = 0.0f;

    vec2 out;

    for( row = 0; row < 2; ++row ){
        sum += lhs(0, row) * rhs[0];
        sum += lhs(1, row) * rhs[1];
        out[row] = sum;
        sum = 0.0f;
    }
    return out;
}

vec4 operator*( vec4 const& lhs, mat const& rhs )
{
    if( rhs.nCols() != 4 || rhs.nRows() != 4 ){
        throw std::invalid_argument("dimension, column mismatch on vec4, matrix multiply");
    }

    size_t col = 0;
    float sum = 0.0f;

    vec4 out;

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

vec3 operator*( vec3 const& lhs, mat const& rhs )
{
    if( rhs.nCols() != 3 || rhs.nRows() != 3 ){
        throw std::invalid_argument("dimension, column mismatch on vec3, matrix multiply");
    }

    size_t col = 0;
    float sum = 0.0f;

    vec3 out;

    for( col = 0; col < 3; ++col ){
        sum += lhs[0] * rhs(col, 0);
        sum += lhs[1] * rhs(col, 1);
        sum += lhs[2] * rhs(col, 2);
        out[col] = sum;
        sum = 0.0f;
    }
    return out;
}

vec2 operator*( vec2 const& lhs, mat const& rhs )
{
    if( rhs.nCols() != 2 || rhs.nRows() != 2 ){
        throw std::invalid_argument("dimension, column mismatch on vec2, matrix multiply");
    }

    size_t col = 0;
    float sum = 0.0f;

    vec2 out;

    for( col = 0; col < 2; ++col ){
        sum += lhs[0] * rhs(col, 0);
        sum += lhs[1] * rhs(col, 1);
        out[col] = sum;
        sum = 0.0f;
    }
    return out;
}
*/

class operator_factory {
    public:
        operator_factory() {}
        static __normalize__ make__normalize__()
            { return __normalize__(); }
        static __orthogonalize__ make__orthogonalize__()
            { return __orthogonalize__(); }
        static __threshold__ make__threshold__()
            { return __threshold__(); }
        static __linear__ make__linear__()
            { return __linear__(); } 
        static __cubic__ make__cubic__()
            { return __cubic__(); }
        static __outer_product__ make__outer_product__()
            { return __outer_product__(); }
        static __inner_product__ make__inner_product__()
            { return __inner_product__(); }
        static __magnitude__ make__magnitude__()
            { return __magnitude__(); }
        static __inverse_magnitude__ make__inverse_magnitude__()
            { return __inverse_magnitude__(); }
        static __transpose__ make__transpose__()
            { return __transpose__(); }
        static __homogenize__ make__homogenize__()
            { return __homogenize__(); }
        static __clip_range__ make__clip_range__()
            { return __clip_range__(); }
};

vec4 __normalize__::eval( vec4 const& vec ) const
{
    vec4 out = vec;

    float invMag = 1.0f / sqrt(   vec[0] * vec[0]
                                + vec[1] * vec[1]
                                + vec[2] * vec[2]
                                + vec[3] * vec[3] );

    return out*invMag;
}

vec3 __normalize__::eval( vec3 const& vec ) const
{
    vec3 out = vec;

    float invMag = 1.0f / sqrt(   vec[0] * vec[0]
                                + vec[1] * vec[1]
                                + vec[2] * vec[2] );

    return out*invMag;
}

vec2 __normalize__::eval( vec2 const& vec ) const
{
    vec2 out = vec;

    float invMag = 1.0f / sqrt(   vec[0] * vec[0]
                                + vec[1] * vec[1] );

    return out*invMag;
}

mat4 __normalize__::eval( mat4 const& amat ) const
{
    mat4 out;
    out[0] = vec4( amat.column(0)(x,y,z).norm(), amat.column(0)(w) );
    out[1] = vec4( amat.column(1)(x,y,z).norm(), amat.column(1)(w) );
    out[2] = vec4( amat.column(2)(x,y,z).norm(), amat.column(2)(w) );
    out[3] = amat.column(3);
    return out;
}

mat __normalize__::eval( mat const& amat ) const
{
    size_t row = 0;
    size_t col = 0;

    size_t n_rows = amat.n_rows();
    size_t n_cols = amat.n_cols();

    // Using double precision here promotes all operations to double _then_ truncates.
    // Slower, but more accurate and you should avoid matrix normalizations as much
    // as possible anyway so we have the budget and the need for more accuracy.
    double temp = 0.0;
    double invColMag = 0.0;

    mat out (amat.n_cols(), amat.n_rows());

    // __normalize__ each column of the matrix
    for( col = 0; col < n_cols; ++col ){
        for( row = 0; row < n_rows; ++row ){
            temp = amat(col, row);
            invColMag += temp * temp;
        }
        invColMag = 1.0 / sqrt(invColMag);
        for( row = 0; row < n_rows; ++row ){
            out(col, row) = amat(col, row) * invColMag;
        }
        invColMag = 0.0;
    }

    return out;
}

qutn __normalize__::eval( qutn const& quat ) const
{
    double invMag = 1.0f / sqrt(   quat[0] * quat[0]
                                 + quat[1] * quat[1]
                                 + quat[2] * quat[2]
                                 + quat[3] * quat[3] );
    return qutn( quat[0] * invMag,
                  quat[1] * invMag,
                  quat[2] * invMag,
                  quat[3] * invMag );
}


__normalize__ const norm = operator_factory::make__normalize__();


vec3 __orthogonalize__::eval( vec3 const& A, vec3 const& B ) const
{
    return vec3( A[0]*( B[1]*B[1]+B[2]*B[2] ) - B[0]*(A[1]*B[1] + A[2]*B[2]),
                 A[1]*( B[2]*B[2]+B[0]*B[0] ) - B[1]*(A[2]*B[2] + A[0]*B[0]),
                 A[2]*( B[0]*B[0]+B[1]*B[1] ) - B[2]*(A[0]*B[0] + A[1]*B[1]) );
    
//     return cross( B, cross( A, B ) );
}

mat4 __orthogonalize__::eval( mat4 const& amat ) const
{
    mat4 out;
    out[0] = amat[0];
    out[1] = vec4( ortho( amat.column(1)(x,y,z), amat.column(0)(x,y,z) ), amat.column(1)(w) );
    out[2] = vec4( ortho( amat.column(2)(x,y,z), amat.column(0)(x,y,z) ), amat.column(2)(w) );
    out[3] = amat[3];
    return out;
}

// vec2 __orthogonalize__::eval( vec2 const& vecA, vec2 const& vecB ) const
// {
//     vec3 vecA3 (vecA[0], vecA[1], 0.0f );
//     vec3 vecB3 (vecB[0], vecB[1], 0.0f );
//     vec3 out3 = cross( vecA3, cross( vecB3, vecA3));
// 
//     return vec2( out3[0], out3[1] );
// }

__orthogonalize__ const ortho = operator_factory::make__orthogonalize__();



vec4 __threshold__::eval( vec4 const& vecA, vec4 const& vecB, float const& p ) const
{
    return p < 0.5f ? vecA : vecB;
}

vec3 __threshold__::eval( vec3 const& vecA, vec3 const& vecB, float const& p ) const
{
    return p < 0.5f ? vecA : vecB;
}

vec2 __threshold__::eval( vec2 const& vecA, vec2 const& vecB, float const& p ) const
{
    return p < 0.5f ? vecA : vecB;
}

float __threshold__::eval( float const& a, float const& b, float const& p ) const
{
    return p < 0.5f ? a : b;
}


__threshold__ const mix_th = operator_factory::make__threshold__();


vec4 __linear__::eval( vec4 const& vecA, vec4 const& vecB, float const& p ) const
{
    return vecA + p * ( vecB - vecA );
}

vec3 __linear__::eval( vec3 const& vecA, vec3 const& vecB, float const& p ) const
{
    return vecA + p * ( vecB - vecA );
}

vec2 __linear__::eval( vec2 const& vecA, vec2 const& vecB, float const& p ) const
{
    return vecA + p * ( vecB - vecA );
}

float __linear__::eval( float const& a, float const& b, float const& p ) const
{
    return a + p * ( b - a );
}

__linear__ const mix_ln = operator_factory::make__linear__();

vec4 __cubic__::eval( vec4 const& vecA, vec4 const& vecB, float const& p ) const
{
    return vecA + p*p*( 3.0f - 2.0f*p)*(vecB - vecA);
}

vec3 __cubic__::eval( vec3 const& vecA, vec3 const& vecB, float const& p ) const
{
    return vecA + p*p*( 3.0f - 2.0f*p)*(vecB - vecA);
}

vec2 __cubic__::eval( vec2 const& vecA, vec2 const& vecB, float const& p ) const
{
    return vecA + p*p*( 3.0f - 2.0f*p)*(vecB - vecA);
}

float __cubic__::eval( float const& a, float const& b, float const& p ) const
{
    return a + p*p*( 3.0f - 2.0f*p )*(b - a);
}
__cubic__ const mix_cb = operator_factory::make__cubic__();


vec3 __outer_product__::eval( vec3 const& vecA, vec3 const& vecB ) const
{
    return vec3( vecA[1]*vecB[2] - vecA[2]*vecB[1],
                 vecA[2]*vecB[0] - vecA[0]*vecB[2],
                 vecA[0]*vecB[1] - vecA[1]*vecB[0] );
}

__outer_product__ const cross = operator_factory::make__outer_product__();


float __inner_product__::eval( vec4 const& vecA, vec4 const& vecB ) const
{
    return vecA[0]*vecB[0] + vecA[1]*vecB[1] + vecA[2]*vecB[2] + vecA[3]*vecB[3];
}

float __inner_product__::eval( vec3 const& vecA, vec3 const& vecB ) const
{
    return vecA[0]*vecB[0] + vecA[1]*vecB[1] + vecA[2]*vecB[2];
}

float __inner_product__::eval( vec2 const& vecA, vec2 const& vecB ) const
{
    return vecA[0]*vecB[0] + vecA[1]*vecB[1];
}

__inner_product__ const dot = operator_factory::make__inner_product__();

float __magnitude__::eval( vec4 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];
    float k = vec[2];
    float m = vec[3];

    return sqrt( i*i + j*j + k*k + m*m );
}

float __magnitude__::eval( vec3 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];
    float k = vec[2];

    return sqrt( i*i + j*j + k*k );
}

float __magnitude__::eval( vec2 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];

    return sqrt( i*i + j*j );
}

__magnitude__ const mag = operator_factory::make__magnitude__();

float __inverse_magnitude__::eval( vec4 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];
    float k = vec[2];
    float m = vec[3];

    return 1.0f / sqrt( i*i + j*j + k*k + m*m );
}

float __inverse_magnitude__::eval( vec3 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];
    float k = vec[2];

    return 1.0f / sqrt( i*i + j*j + k*k );
}

float __inverse_magnitude__::eval( vec2 const& vec ) const
{
    float i = vec[0];
    float j = vec[1];

    return 1.0f / sqrt( i*i + j*j );
}

__inverse_magnitude__ const inv_mag = operator_factory::make__inverse_magnitude__();

mat __transpose__::eval( mat const& amat ) const
{
    mat out ( amat.n_rows(), amat.n_cols() );

    size_t i = amat.n_comp();
    size_t amat_cols = amat.n_cols();
    size_t out_rows = out.n_rows();

    while(i)
    {
        --i;
        out(i / out_rows, i % out_rows )
            = amat( i % amat_cols, i / amat_cols );
    }

    return out;
}

__transpose__ const transpose = operator_factory::make__transpose__();

mat __homogenize__::eval( mat const& amat ) const
{
    size_t cols = amat.n_cols();
    size_t rows = amat.n_rows();

    size_t dim = 0;

    if( rows >= cols ){
        dim = rows + 1;
    } else {
        dim = cols + 1;
    }

    mat out = mat::identity( dim);
    size_t size = dim * dim;

    size_t i = 0;

    bool col_outside = false;
    bool row_outside = false;

    size_t row = 0;
    size_t col = 0;

    for( i =0; i < size; ++i ){
        col = i / dim;
        row = i % dim;
        col_outside = col >= cols;
        row_outside = row >= rows;
    if ( col_outside and row_outside ){
            break;
        } else if ( not (col_outside or row_outside) ){
            out(col, row ) = amat( col, row );
        }
    }

    return out;
}

mat4 __homogenize__::eval( mat3 const& amat ) const
{
    return mat4( amat(0,0), amat(1,0), amat(2,0), 0.0f,
                 amat(0,1), amat(1,1), amat(2,1), 0.0f,
                 amat(0,2), amat(1,2), amat(2,2), 0.0f,
                 0.0f,      0.0f,      0.0f,      1.0f );
}

__homogenize__ const homogenize = operator_factory::make__homogenize__();

float __clip_range__::eval( float const& value, float const& min, float const& max ) const
{
    return ( value < min ? min : ( value > max ? max : value ));
}

__clip_range__ const clip_rng = operator_factory::make__clip_range__();


/**
/* ---- Float Specializations ---- * /
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
*/
}
