#pragma once

#include <stdexcept>
#include "gfx_assertion.hpp"
#include "gfx_warning.hpp"

namespace gfx {

    class Mat2;
    class Mat3;
    class Mat4;

    class Mat2x3;
    class Mat2x4;

    class Mat3x2;
    class Mat3x4;

    class Mat4x2;
    class Mat4x3;

    class Matrix;
    
}

#include "mat2.hpp"
#include "mat3.hpp"
#include "mat4.hpp"

#include "mat2x3.hpp"
#include "mat2x4.hpp"

#include "mat3x2.hpp"
#include "mat3x4.hpp"

#include "mat4x2.hpp"
#include "mat4x3.hpp"

#include "matrix.hpp"

inline Mat3 homogenize( Mat2 const& a, float scale = 1.0f )
{
    return Mat3( a.xx, a.xy, 0.0f,
                 a.yx, a.yy, 0.0f,
                 0.0f, 0.0f, scale );
}

inline Mat4 homogenize( Mat3 const& a, float scale = 1.0f )
{
    return Mat4( a.xx, a.xy, a.xz, 0.0f,
                 a.yx, a.yy, a.yz, 0.0f,
                 a.zx, a.zy, a.zz, 0.0f,
                 0.0f, 0.0f, 0.0f, scale );
}

inline Mat3x2 transpose( Mat2x3 const& a )
{
    return Mat3x2( a.xx, a.yx,
                   a.xy, a.yy,
                   a.xz, a.yz );
}

inline Mat2x3 transpose( Mat3x2 const& a )
{
    return Mat2x3( a.xx, a.yx, a.zx,
                   a.xy, a.yy, a.zy );
}

inline Mat4x2 transpose( Mat2x4 const& a )
{
    return Mat4x2( a.xx, a.yx,
                   a.xy, a.yy,
                   a.xz, a.yz,
                   a.xw, a.yw );
}

inline Mat2x4 transpose( Mat4x2 const& a )
{
    return Mat2x4( a.xx, a.yx, a.zx, a.wx,
                   a.xy, a.yy, a.zy, a.wy );
}

inline float determinant( Mat2 const& a )
{
    return a.xx * a.yy - a.xy * a.yx;
}

inline float determinant( Mat3 const& a )
{    
    return   a.xx * a.yy * a.zz + a.xy * a.yz * a.zx + a.xz * a.yx * a.zy
           - a.xz * a.yy * a.zx - a.xy * a.yx * a.zz - a.xx * a.yz * a.zy;
}

inline float determinant( Mat4 const& a )
{ 
    float factorXX =   a.yy * ( a.zz*a.ww - a.wz*a.zw )
                     + a.zy * ( a.yz*a.ww - a.wz*a.yw )
                     + a.wy * ( a.yz*a.zw - a.zz*a.yw );
    
    float factorYX =   a.xy * ( a.zz*a.ww - a.wz*a.zw )
                     + a.zy * ( a.xz*a.ww - a.wz*a.xw )
                     + a.wy * ( a.xz*a.zw - a.zz*a.xw );
    
    float factorZX =   a.xy * ( a.yz*a.ww - a.wz*a.zw )
                     + a.yy * ( a.xz*a.ww - a.wz*a.xw )
                     + a.wy * ( a.xz*a.zw - a.yz*a.xw );
    
    float factorWX =   a.xy * ( a.yz*a.zw - a.zz*a.yw )
                     + a.yy * ( a.xz*a.zw - a.zz*a.yw )
                     + a.zy * ( a.xz*a.yw - a.yz*a.xw );
    
    return a.xx * factorXX + a.yx * factorXY + a.zx * factorZX + a.wx * factorWX;
}

inline Mat2 comatrix( Mat2 const& a )
{
    return Mat2(  a.yy, -a.yx,
                 -a.xy,  a.xx );
}

inline Mat3 comatrix( Mat3 const& a )
{    
    float xx = a.yy*a.zz - a.yz*a.zy;
    float xy = a.yx*a.zz - a.yz*a.zx;
    float xz = a.yx*a.zy - a.yy*a.zx;
    
    float yx = a.xy*a.zz - a.xz*a.zy;
    float yy = a.xx*a.zz - a.xz*a.zx;
    float yz = a.xx*a.zy - a.xy*a.zx;
    
    float zx = a.xy*a.zz - a.xz*a.zy;
    float zy = a.xx*a.yz - a.xz*a.yx;
    float zz = a.xx*a.yy - a.xy*a.yx;
    
    return Mat3(  xx, -xy,  xz,
                 -yx,  yy, -yz,
                  zx, -zy,  zz );
}

inline Mat4 comatrix( Mat4 const& a )
{
    return Mat4( a.cofactor(0,0), a.cofactor(0,1),  a.cofactor(0,2), a.cofactor(0,3),
                 a.cofactor(1,0), a.cofactor(1,1),  a.cofactor(1,2), a.cofactor(1,3),
                 a.cofactor(2,0), a.cofactor(2,1),  a.cofactor(2,2), a.cofactor(2,3),
                 a.cofactor(3,0), a.cofactor(3,1),  a.cofactor(3,2), a.cofactor(3,3) );
}

inline Mat2 inverse( Mat2 const& a )
{
    float det = determinant(a);
    gfx_assert( det != 0.0f, "Matrix not invertible.");
           
    float invDet = 1.0f / determinant(a);
    Mat2 adj = transpose(comatrix(a));
    
    return invDet * adj;
}

inline Mat3 inverse( Mat3 const& a )
{
    float det = determinant(a);
    gfx_assert( det != 0.0f, "Matrix not invertible.");
        
    float invDet = 1.0f / determinant(a);
    Mat3 adj = transpose(comatrix(a));
    
    return invDet * adj;        
}
/**
 * @return The inverse of the given matrix if it exists; otherwise just the matrix
 */
inline Mat4 inverse( Mat4 const& a )
{
    float det = determinant(a);
    gfx_assert( det != 0.0f, "Matrix not invertible.");
        
    float invDet = 1.0f / determinant(a);
    Mat4 adj = transpose(comatrix(a));
    
    return invDet * adj;
}

inline Mat2 operator /( Mat2 const& lhs, Mat2 const& rhs )
{
    gfx_assert( determinant(rhs) != 0.0f, "Division by 2x2 matrix impossible: determinant is zero." );
    
    return lhs * inverse(rhs);
}

inline Mat3 operator /( Mat3 const& lhs, Mat3 const& rhs )
{
    gfx_assert( determinant(rhs) != 0.0f, "Division by 3x3 matrix impossible: determinant is zero." );
    
    return lhs * inverse(rhs);
}

inline Mat3 operator /( Mat3 const& lhs, Mat3 const& rhs )
{
    gfx_assert( determinant(rhs) != 0.0f, "Division by 4x4 matrix impossible: determinant is zero." );
    
    return lhs * inverse(rhs);
}

inline Mat4 operator* ( Mat4x2 const& a, Mat2x4 const& b ) {
    
    Mat4( a.xx * b.xx + a.xy * b.yx, a.xx * b.xy + a.xy * b.yy, a.xx * b.xz + a.xy * b.yz, a.xx * b.xw + a.xy * b.yw,
          a.yx * b.xx + a.yy * b.yx, a.yx * b.xy + a.yy * b.yy, a.yx * b.xz + a.yy * b.yz, a.yx * b.xw + a.yy * b.yw,
          a.zx * b.xx + a.zy * b.yx, a.zx * b.xy + a.zy * b.yy, a.zx * b.xz + a.zy * b.yz, a.zx * b.xw + a.zy * b.yw,
          a.wx * b.xx + a.wy * b.yx, a.wx * b.xy + a.wy * b.yy, a.wx * b.xz + a.wy * b.yz, a.wx * b.xw + a.wy * b.yw );
    
}

inline Vec2 operator* ( Vec2 const& a, Mat2 const& b )
{
    return Vec2( a.x * b.xx + a.y * b.yx,
                 a.x * b.xy + a.y * b.yy );
}

inline Vec2 operator* ( Mat2 const& a, Vec2 const& b )
{
    return Vec2( a.xx * b.x + a.xy * b.y,
                 a.yx * b.x + a.yy * b.y );
}

inline Vec3 operator* ( Vec3 const& a, Mat3 const& b )
{
    return Vec3( a.x * b.xx + a.y * b.yx + a.z * b.zx,
                 a.x * b.xy + a.y * b.yy + a.z * b.zy,
                 a.x * b.xz + a.y * b.yz + a.z * b.zz );
}

inline Vec3 operator* ( Mat3 const& a, Vec3 const& b )
{
    return Vec3( a.xx * b.x + a.xy * b.y + a.xz * b.z,
                 a.yx * b.x + a.yy * b.y + a.yx * b.z, 
                 a.zx * b.x + a.zy * b.y + a.zx * b.z );
}

inline Vec4 operator* ( Vec4 const& a, Mat4 const& b )
{
    return Vec4( a.x * b.xx + a.y * b.yx + a.z * b.zx + a.w * b.wx,
                 a.x * b.xy + a.y * b.yy + a.z * b.zy + a.w * b.wy,
                 a.x * b.xz + a.y * b.yz + a.z * b.zz + a.w * b.wz,
                 a.x * b.xw + a.y * b.yw + a.z * b.zw + a.w * b.ww );
}

inline Vec4 operator* ( Mat4 const& a, Vec4 const& b )
{
    return Vec4( a.xx * b.x + a.xy * b.y + a.xz * b.z + a.xw * b.w,
                 a.yx * b.x + a.yy * b.y + a.yx * b.z + a.yw * b.w, 
                 a.zx * b.x + a.zy * b.y + a.zx * b.z + a.zw * b.w,
                 a.wx * b.x + a.wy * b.y + a.wx * b.z + a.ww * b.w );
}