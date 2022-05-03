#pragma once

namespace gfx {
    
    
    // Really gotta look into column major vs row major for Vulkan etc.
    union Mat2x3 {
    
    public:
    
        Mat2x3() : xx(0.0f), yx (0.0f), zx (0.0f), xy (0.0f), yy (0.0f), zy(0.0f) {}
    
        Mat2x3( float aa, float ab,
                float ba, float bb,
                float ca, float cb )
          : xx (aa), yx (ba), zx (ca), xy (ab), yy (bb), zy (cb) {}
        
        static Mat2x3 columns( Vec3 const& a, Vec3 const& b )
        { return Mat2x3( a.x, b.x,
                         a.y, b.y,
                         a.z, b.z ); }
        
        static Mat2x3 rows( Vec2 const& a, Vec2 const& b, Vec2 const& c )
        { return Mat2x3( a.x, a.y,
                         b.x, b.y,
                         c.x, c.y ); }
        
        static Mat2x3 upper_identity()
        { return Mat2x3( 1.0f, 0.0f,
                         0.0f, 1.0f,
                         0.0f, 0.0f ); }
        
        static Mat2x3 null() { return Mat2x3(); }
        
        static Mat2x3 upper_scale( float scaleX, float scaleY )
        {
            return Mat2x3( scaleX, 0.0f, 0.0f, scaleY, 0.0f, 0.0f );
        }
        
        static Mat2x3 upper_scale( Vec2 const& scale )
        {
            return Mat2x3( scale.x, 0.0f, 0.0f, scale.y, 0.0f, 0.0f );
        }
        
        static Mat2x3 inverse( Mat2x3 const& a )
        {
            // Do the inverse
            return Mat2x3();
        }
        
        float operator() ( const int row, const int col ) const { return ary[col * 3 + row]; }
        float& operator() ( const int row, const int col ) { return ary[col * 3 + row]; }
        
        Vec3 column( int col ) const { return Vec3( ary[col * 3], ary[col * 3 + 1], ary[col * 3 + 2] ); }
        
        void setColumn( int col, Vec3 const& col )
        {
            ary[col * 3]     = col.x;
            ary[col * 3 + 1] = col.y;
            ary[col * 3 + 2] = col.z;
        }
        
        Vec2 row( int row ) const { return Vec2( ary[row], ary[2 + row] ); }
        
        void setRow( int row, Vec2 const& row )
        {
            ary[row]      = row.x;
            ary[4 + row]  = row.y;
        }
        
        float* operator float*() { return ary; }
        
        Mat2x3 operator+ ( Mat2x3 const& b ) const {
            return Mat2x3( xx + b.xx, xy + b.xy,
                           yx + b.yx, yy + b.yy,
                           zx + b.zx, zy + b.zy );
            
        }
        
        Mat2x3 operator- ( Mat2x3 const& b ) const {
            return Mat2x3( xx - b.xx, xy - b.xy,
                           yx - b.yx, yy - b.yy,
                           zx - b.zx, zy - b.zy );
            
        }
        
        Mat2 operator* ( Mat2 const& b ) const
        {
            return Mat2( xx * b.xx + xy * b.yx, xx * b.yx + xy * b.yy,
                         yx * b.xx + yy * b.yx, yx * b.yx + yy * b.yy );
        }
        
        struct {
            float xx,
                  yx,
                  zx;
                float xy,
                      yy,
                      zy;
        };
        
        struct {
            float ss,
                  ts,
                  ps;
                float st,
                      tt,
                      pt;
        };
        
    private:
        
        struct {
            float[6] ary;
        };
        
        struct {
            char[sizeof(float) * 6] bytes;
        };
        
    };
    
    inline Mat2 transpose( Mat2 const& a )
    {
        return Mat2( a.xx, a.yx,
                     a.xy, a.yy );
    }
    
    Mat2 operator* (float s, Mat2 const& a)
    {
        return Mat2( s * a.xx, s * a.xy,
                     s * a.yx, s * a.yy );
    }
    
    Mat2 operator* (Mat2 const& a, float s )
    {
        return Mat2( s * a.xx, s * a.xy,
                     s * a.yx, s * a.yy );
    }
    
}