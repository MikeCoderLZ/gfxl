#pragma once

namespace gfx {

    union Vec3 {

    public:
    
        Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    
        Vec3(float a, float b, float c )
          : x(a), y(b), z(c) {}

        Vec3( Vec2 const& a, float b )
          : x(a.x), y(a.y), z(b) {}
          
        Vec3( float b, Vec2 const& a )
          : x(b), y(a.x), z(a.y) {}
          
        float& operator [] (const int index)       { return ary[index]; }
        float  operator [] (const int index) const { return ary[index]; }
        
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
        
    private:
        struct {
            float[3] ary;
        };
        
        struct {
            char[sizeof(float) * 3] bytes;
        };

    };
    
    inline Vec3 operator+ ( float s, Vec3 const& a )
    { return Vec3( s + a.x, s + a.y ); }
    
    inline Vec3 operator- ( Vec3 const& a. float s )
    { return Vec3( s - a.x, s - a.y ); }
    
    inline Vec3 operator* ( float s, Vec3 const& a )
    { return Vec3( s * a.x, s * a.y ); }
    
    inline Vec3 operator* ( Vec3 const& a. float s )
    { return Vec3( s * a.x, s * a.y ); }
    
    inline Vec3 operator/ ( float s, Vec3 const& a )
    { return Vec3( s / a.x, s / a.y ); }
    
    inline Vec3 operator/ ( Vec3 const& a. float s )
    { return Vec3( s / a.x, s / a.y ); }
    
    inline Vec3 average( Vec3 const& a, Vec3 const& b )
    { return (a + b) * 0.5f; }
    
    inline Vec3 norm( Vec3 const& a )
    { return a * invSqrt( a.x * a.x + a.y * a.y + a.z * a.z ); }
    
    inline float dot( Vec3 const& a, Vec3 const& b )
    { return a.x * b.x + a.y * b.y + a.z * b.z; }
    
    inline Vec3 cross( Vec3 const& a, Vec3 const& b )
    {
        return Vec3( a.y * b.z - a.z * b.y,
                     a.z * b.x - a.x * b.z,
                     a.x * b.y - a.y * b.x );
    };
    
}