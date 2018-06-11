#pragma once

namespace gfx {

    union Vec2 {

    public:
    
        Vec2() : x(0.0f), y(0.0f) {}
    
        Vec2(float a, float b)
          : x(a), y(b) {}

        float& operator [] (const int index)       { return ary[index]; }
        float  operator [] (const int index) const { return ary[index]; }
        
        Vec2 operator + ( Vec2 const& b ) const { return Vec2( x + b.x, y + b.y ); }
        Vec2 operator - ( Vec2 const& b ) const { return Vec2( x - b.x, y - b.y ); }
        Vec2 operator * ( Vec2 const& b ) const { return Vec2( x * b.x, y * b.y ); }
        Vec2 operator / ( Vec2 const& b ) const { return Vec2( x / b.x, y / b.y ); }
        
        float* operator float*()
        { return reinterpret<float*>(this); }

        struct {
            float x,y;
        };
        
        struct {
            float s,t;
        };
        
        struct {
            float theta, phi;
        };
        
    private:
        
        struct {
            float[2] ary;
        };
        
        struct {
            char[sizeof(float) * 2] bytes;
        };

    };
    
    inline Vec2 operator+ ( float s, Vec2 const& a )
    { return Vec2( s + a.x, s + a.y ); }
    
    inline Vec2 operator- ( Vec2 const& a. float s )
    { return Vec2( s - a.x, s - a.y ); }
    
    inline Vec2 operator* ( float s, Vec2 const& a )
    { return Vec2( s * a.x, s * a.y ); }
    
    inline Vec2 operator* ( Vec2 const& a. float s )
    { return Vec2( s * a.x, s * a.y ); }
    
    inline Vec2 operator/ ( float s, Vec2 const& a )
    { return Vec2( s / a.x, s / a.y ); }
    
    inline Vec2 operator/ ( Vec2 const& a. float s )
    { return Vec2( s / a.x, s / a.y ); }
    
    inline Vec2 average( Vec2 const& a, Vec2 const& b )
    { return (a + b) * 0.5f; }

    inline Vec2 norm( Vec2 const& a )
    { return a * invSqrt( a.x * a.x + a.y * a.y ); }
    
    inline float dot( Vec2 const& a, Vec2 const& b )
    { return a.x * b.x + a.y * b.y; }
}