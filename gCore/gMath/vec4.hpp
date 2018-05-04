#pragma once

namespace gfx {

    union Vec4 {

    public:
        Vec4(float a, float b, float c, float d )
          : x(a), y(b), z(c), w(d) {}

        float& operator [] (const int index)       { return (reinterpret_cast<float*>(this))[index]; }
        float  operator [] (const int index) const { return (reinterpret_cast<float*>(this))[index]; }
        
        Vec4 operator + ( Vec4 const& b ) const { return Vec4( x + b.x, y + b.y, z + b.z, w + b.w ); }
        Vec4 operator - ( Vec4 const& b ) const { return Vec4( x - b.x, y - b.y, z - b.z, w - b.w ); }
        Vec4 operator * ( Vec4 const& b ) const { return Vec4( x * b.x, y * b.y, z * b.z, w * b.w ); }
        Vec4 operator / ( Vec4 const& b ) const { return Vec4( x / b.x, y / b.y, z / b.z, w / b.w ); }
        
        float* operator float*()
        {
            return reinterpret<float*>(this);
        }

        struct {
            float x,y,z;
            float w;
        };
        
        struct {
            float s,t,p;
            float q;
        };
        
        struct {
            float theta, phi, radius;
            float zeta;
        };

    };
}