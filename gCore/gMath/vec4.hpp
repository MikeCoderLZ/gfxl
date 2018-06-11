#pragma once

namespace gfx {

    union Vec4 {

    public:
    
        Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        
        Vec4(float a, float b, float c, float d )
          : x(a), y(b), z(c), w(d) {}
          
        Vec4(Vec2 const& a, float b, float c )
          : x(a.x), y(a.y), z(b), w(c) {}
          
        Vec4(float a, Vec2 const& b, float c )
          : x(a), y(b.x), z(b.y), w(c) {}
          
        Vec4(float a, float b, Vec2 const& c )
          : x(a), y(b), z(c.x), w(c.y) {}

        Vec4(Vec3 const& a, float b )
          : x(a.x), y(a.y), z(a.z), w(b) {}
          
        Vec4(float a, Vec3 const& b )
          : x(a), y(b.x), z(b.y), w(b.z) {}
          
        float& operator [] (const int index)       { return ary[index]; }
        float  operator [] (const int index) const { return ary[index]; }
        
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
        
    private:
    
        struct {
            float[4] ary;
        };
        
        struct {
            char[sizeof(float) * 4] bytes;
        };

    };
    
    inline Vec4 operator+ ( float s, Vec4 const& a )
    { return Vec4( s + a.x, s + a.y ); }
    
    inline Vec4 operator- ( Vec4 const& a. float s )
    { return Vec4( s - a.x, s - a.y ); }
    
    inline Vec4 operator* ( float s, Vec4 const& a )
    { return Vec4( s * a.x, s * a.y ); }
    
    inline Vec4 operator* ( Vec4 const& a. float s )
    { return Vec4( s * a.x, s * a.y ); }
    
    inline Vec4 operator/ ( float s, Vec4 const& a )
    { return Vec4( s / a.x, s / a.y ); }
    
    inline Vec4 operator/ ( Vec4 const& a. float s )
    { return Vec4( s / a.x, s / a.y ); }
    
    inline Vec4 average( Vec4 const& a, Vec4 const& b )
    { return (a + b) * 0.5f; }
    
    inline Vec4 norm( Vec4 const& a )
    { return a * invSqrt( a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w ); }
    
    inline float dot( Vec4 const& a, Vec4 const& b )
    { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
}