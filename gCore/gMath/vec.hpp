#pragma once

#include "math.hpp"

namespace {
    
    class Vec2;
    class Vec3;
    class Vec4;
    
    class Qutn;

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

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

#include "quaternion.hpp"

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

namespace {

inline float dot( Vec2 const& a, Vec2 const& b ) { return a.x * b.x + a.y * b.y; }
inline float dot( Vec3 const& a, Vec3 const& b ) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline float dot( Vec4 const& a, Vec4 const& b ) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

inline Vec2 norm( Vec2 const& a ) { return a * invSqrt( a.x * a.x + a.y * a.y ); }
inline Vec3 norm( Vec3 const& a ) { return a * invSqrt( a.x * a.x + a.y * a.y + a.z * a.z ); }
inline Vec4 norm( Vec4 const& a ) { return a * invSqrt( a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w ); }

inline Vec3 cross( Vec3 const& a, Vec3 const& b );



}