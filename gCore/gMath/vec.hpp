#pragma once

namespace {
    
    class Vec2;
    class Vec3;
    class Vec4;
    
    class Qutn;

}

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

#include "quaternion.hpp"

namespace gfx {
    
    inline Vec3 homogenize( Vec2 const& a, float scale = 1.0f )
    { return Vec3( a.x, a.y, scale); }

    inline Vec4 homogenize( Vec3 const& a, float scale = 1.0f )
    { return Vec4( a.x, a.y, a.z, scale); }

}