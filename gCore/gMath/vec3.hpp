#pragma once

namespace gfx {

    union Vec3 {

    public:
        Vec3(float a, float b, float c )
          : x(a), y(b), z(c) {}

        float& operator [] (const int index)       { return (reinterpret_cast<float*>(this))[index]; }
        float  operator [] (const int index) const { return (reinterpret_cast<float*>(this))[index]; }
        
        Vec3 operator + ( Vec3 const& b ) const { return Vec3( x + b.x, y + b.y, z + b.z); }
        Vec3 operator - ( Vec3 const& b ) const { return Vec3( x - b.x, y - b.y, z - b.z ); }
        Vec3 operator * ( Vec3 const& b ) const { return Vec3( x * b.x, y * b.y, z * b.z ); }
        Vec3 operator / ( Vec3 const& b ) const { return Vec3( x / b.x, y / b.y, z / b.z ); }
        
        float* operator float*()
        {
            return reinterpret<float*>(this);
        }

        struct {
            float x,y,z;
        };
        
        struct {
            float s,t,p;
        };
        
        struct {
            float theta, phi, radius;
        };

    };
}