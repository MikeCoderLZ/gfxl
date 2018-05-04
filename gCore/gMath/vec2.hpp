#pragma once

namespace gfx {

    union Vec2 {

    public:
        Vec2(float a, float b)
          : x(a), y(b) {}

        float& operator [] (const int index)       { return (reinterpret_cast<float*>(this))[index]; }
        float  operator [] (const int index) const { return (reinterpret_cast<float*>(this))[index]; }
        
        Vec2 operator + ( Vec2 const& b ) const { return Vec2( x + b.x, y + b.y ); }
        Vec2 operator - ( Vec2 const& b ) const { return Vec2( x - b.x, y - b.y ); }
        Vec2 operator * ( Vec2 const& b ) const { return Vec2( x * b.x, y * b.y ); }
        Vec2 operator / ( Vec2 const& b ) const { return Vec2( x / b.x, y / b.y ); }
        
        float* operator float*()
        {
            return reinterpret<float*>(this);
        }

        struct {
            float x,y;
        };
        
        struct {
            float s,t;
        };
        
        struct {
            float theta, phi;
        };

    };
}