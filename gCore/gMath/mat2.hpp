#pragma once

namespace gfx {
    
    
    // Really gotta look into column major vs row major for Vulkan etc.
    union Mat2 {
    
    public:
    
        Mat2() : xx(0.0f), yx (0.0f), xy (0.0f), yy (0.0f) {}
    
        Mat2( Mat2 const& src )
          : xx ( src.xx ),
            xy ( src.xy ),
            yx ( src.yx ),
            yy ( src.yy ) {}
    
        Mat2( float aa, float ab,
              float ba, float bb )
          : xx (aa), yx (ba), xy (ab), yy (bb) {}
        
        static Mat2 fill( float a ) {
            return Mat2( a, a, a, a );
        }
        
        static Mat2 columns( Vec2 const& a, Vec2 const& b )
        { return Mat2( a.x, b.x,
                       a.y, b.y ); }
        
        static Mat2 rows( Vec2 const& a, Vec2 const& b )
        { return Mat2( a.x, a.y,
                       b.x, b.y ); }
        
        static Mat2 identity()
        { return Mat2( 1.0f, 0.0f,
                       0.0f, 1.0f ); }
        
        static Mat2 null() { return Mat2(); }
        
        static Mat2 square( Vec2 const& a )
        {
            return Mat2( a.x * a.x, a.x * a.y, 
                         a.y * a.x, a.y * a.y, );
        }
        
        static Mat2 scale( float scaleX, float scaleY )
        {
            return Mat2( scaleX, 0.0f, 0.0f, scaleY);
        }
        
        static Mat2 scale( Vec2 const& scale )
        {
            return Mat2( scale.x, 0.0f, 0.0f, scale.y );
        }
        
        static Mat2 rotation( AngleDouble const& ang )
        {
            double rad ( angx.toRads() );
            
            double cos_z = std::cos( rad );
            double sin_z = std::sin( rad );

            return Mat2( cos_z, -sin_z,
                         sin_z,  cos_z );
            
        }
        
        float operator() ( const int row, const int col ) const { return ary[col * 2 + row]; }
        float& operator() ( const int row, const int col ) { return ary[col * 2 + row]; }
        
        Vec2 column( int col ) const
        {
            // Assert index range
            return Vec2( ary[col * 2], ary[col * 2 + 1] ); 
        }
        
        void setColumn( int col, Vec2 const& col )
        {
            // Assert index range
            ary[col * 2]     = col.x;
            ary[col * 2 + 1] = col.y;
        }
        
        Vec2 row( int row ) const
        {
            // Assert index range
            return Vec2( ary[row], ary[2 + row] );
        }
        
        void setRow( int row, Vec2 const& row )
        {
            // Assert index range
            ary[row]      = row.x;
            ary[4 + row]  = row.y;
        }
        
        bool operator ==( Mat2 const& other )
        {
            return    xx == other.xx
                   && yx == other.yx
                   && xy == other.xy
                   && yy == other.yy;
        }
        
        bool operator <( Mat2 const& other )
        {
            return    xx < other.xx
                   && yx < other.yx
                   && xy < other.xy
                   && yy < other.yy;
        }
        
        bool operator >( Mat2 const& other )
        {
            return    xx > other.xx
                   && yx > other.yx
                   && xy > other.xy
                   && yy > other.yy;
        }
        
        bool operator <=( Mat2 const& other )
        {
            return    xx <= other.xx
                   && yx <= other.yx
                   && xy <= other.xy
                   && yy <= other.yy;
        }
        
        bool operator >=( Mat2 const& other )
        {
            return    xx >= other.xx
                   && yx >= other.yx
                   && xy >= other.xy
                   && yy >= other.yy;
        }
        
        bool operator !=( Mat2 const& other )
        {
            return    xx != other.xx
                   && yx != other.yx
                   && xy != other.xy
                   && yy != other.yy;
        }
        
        Mat2 operator =( Mat2 const& other )
        {
            xx == other.xx;
            yx == other.yx;
            xy == other.xy;
            yy == other.y;
            
            return *this;
        }
        
        Mat2 operator+ ( Mat2 const& b ) const {
            return Mat2( xx + b.xx, xy + b.xy,
                         yx + b.yx, yy + b.yy );
            
        }
        
        Mat2 operator- ( Mat2 const& b ) const {
            return Mat2( xx - b.xx, xy - b.xy,
                         yx - b.yx, yy - b.yy );
            
        }
        
        Mat2 operator* ( Mat2 const& b ) const
        {
            return Mat2( xx * b.xx + xy * b.yx, xx * b.yx + xy * b.yy,
                         yx * b.xx + yy * b.yx, yx * b.yx + yy * b.yy );
        }
        
        float cofactor( const int row, const int col )
        {
            // Assert index range
            float out = 0.0f;
            switch( row ) {
                case 0:
                    switch( col ) {
                        case 0:
                            out = yy;
                            break;                    
                        case 1:
                            out = -yx;
                            break;
                        default:
                            // exception!
                    }
                    break;
                case 1:
                    switch( col ) {
                        case 0:
                            out = -xy;
                            break;
                        case 1:
                            out = xx;
                            break;
                        default:
                            // exception!
                    } break;
                default:
                    // exception!
            }
            
            return out;
        }
        
        float* operator float*() { return ary; }
        
        struct {
            float xx,
                  yx;
                float xy,
                      yy;
        };
        
        struct {
            float ss,
                  ts;
                float st,
                      tt;
        };
        
    private:
        
        struct {
            float[4] ary;
        };
        
        struct {
            char[sizeof(float) * 4] bytes;
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
