#pragma once

#include <stdexcept>

namespace gfx {
    
    union Mat3 {
    
    public:
        
        Mat3() : xx (0.0f), yy (0.0f), zx (0.0f),
                 xy (0.0f), yy (0.0f), zy (0.0f),
                 xz (0.0f), yz (0.0f), zz (0.0f) {}
    
        Mat3( float aa, float ab, float ac,
              float ba, float bb, float bc,
              float ca, float cb, float cc )
          : xx (aa), yx (ba), zx (ca),
            xy (ab), yy (bb), zy (cb),
            xz (ac), yz (bc), zz (cc) {}
        
        static Mat3 columns( Vec3 const& a, Vec3 const& b, Vec3 const& c )
        { return Mat3( a.x, b.x, c.x,
                       a.y, b.y, c.y,
                       a.z, b.z, c.z ); }
        
        static Mat3 rows( Vec3 const& a, Vec3 const& b, Vec3 const& c )
        { return Mat3( a.x, a.y, a.z,
                       b.x, b.y, b.z,
                       c.x, c.y, c.z ); }
        
        static Mat3 identity()
        { return Mat3( 1.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 1.0f ); }
        
        static Mat3 null() { return Mat3(); }
        
        static Mat3 crossProduct( Vec3 const& a )
        {
            return Mat3( 0.0f, -a.z,  a.y,
                          a.z,  0.0f, -a.x,
                         -a.y,   a.x, 0.0f  );
        }
        
        static Mat3 square( Vec3 const& a )
        {
            return Mat3( a.x * a.x, a.x * a.y, a.x * a.z,
                         a.y * a.x, a.y * a.y, a.y * a.z,
                         a.z * a.x, a.z * a.y, a.z * a.z );
        }
        
        static Mat3 scale( float sx, float sy, float sz = 1.0f )
        {
            return Mat3(   sx, 0.0f, 0.0f,
                         0.0f,   sy, 0.0f,
                         0.0f, 0.0f,   sz  );
        }
        
        static Mat3 scale( Vec2 const& svec )
        {
            return Mat3( svec.x,   0.0f, 0.0f,
                           0.0f, svec.y, 0.0f,
                           0.0f,   0.0f, 1.0f  );
        }
        
        static Mat3 scale( Vec3 const& svec )
        {
            return Mat3( svec.x,   0.0f,   0.0f,
                           0.0f, svec.y,   0.0f,
                           0.0f,   0.0f, svec.z  );
        }
        
        static Mat3 rotation( Vec3 const& axis,
                              AngleDouble const& ang )
        {
            // Rotation usually always requires double precision
            gfx_assert( axis.x != 0.0f && axis.y != 0.0f && axis.z != 0.0f, "Rotation axis is null." );
            
            double radians = ang.toRads();
            double cos_t ( cos( radians ) );
            double cm_cos_t ( 1.0 - cos_t );
            return   Mat3::identity() * cos_t
                   + Mat3::square( axis ) * cm_cos_t
                   + Mat3::crossProduct( axis ) * sin( radians );
        }
        
        static Mat3 rotation( AngleDouble const& angx,
                              AngleDouble const& angy,
                              AngleDouble const& angz )
        {
            // Rotation usually always requires double precision
            double radx ( angx.toRads() );
            double rady ( angy.toRads() );
            double radz ( angz.toRads() );
            
            double sin_x = std::sin( radx );
            double cos_x = std::cos( radx );
            double sin_y = std::sin( rady );
            double cos_y = std::cos( rady );
            double sin_z = std::sin( radz );
            double cos_z = std::cos( radz );
            
            return Mat3(
                                    cos_y*cos_z,                     -cos_y*sin_z,        sin_y,
                cos_x*sin_z + sin_x*sin_y*cos_z,  cos_x*cos_z - sin_x*sin_y*sin_z, -sin_x*cos_y,
                sin_x*sin_z - cos_x*sin_y*cos_z,  sin_x*cos_z + cos_x*sin_y*sin_z,  cos_x*cos_y
              );
            
        }
        
        static Mat3 rotation( Qutn const& qrot )
        {
            // Rotation usually always requires double precision
            double ii = qrot(i) * qrot(i) * 2.0;
            double ij = qrot(i) * qrot(j) * 2.0;
            double ik = qrot(i) * qrot(k) * 2.0;
            double im = qrot(i) * qrot(m) * 2.0;

            double jj = qrot(j) * qrot(j) * 2.0;
            double jk = qrot(j) * qrot(k) * 2.0;
            double jm = qrot(j) * qrot(m) * 2.0;

            double kk = qrot(k) * qrot(k) * 2.0;
            double km = qrot(k) * qrot(m) * 2.0;
            
            return Mat3( 1.0 - (jj + kk),         ij - km,        ik + jm,
                                 ij + km, 1.0 - (ii + kk),        jk - im,
                                 ik - jm,         jk + im, 1.0 - (ii + jj)  );
        }
        
        static Mat3 translate( float tx, float ty )
        {
            return Mat3( 1.0f, 0.0f,   tx,
                         0.0f, 1.0f,   ty,
                         0.0f, 0.0f, 1.0f  );
        }
        
        static Mat3 translate( Vec2 const& tvec )
        {
            return Mat3( 1.0f, 0.0f, tvec.x,
                         0.0f, 1.0f, tvec.y,
                         0.0f, 0.0f,   1.0f );
        }
        
        float& operator() ( int row, int col )
        {
            gfx_assert( row < 3 && row >= 0, "Row index out of bounds: expected 0 <= row <=2, was " << row );
            gfx_assert( col < 3 && col >= 0, "Column index out of bounds: expected 0 <= col <=2, was " << col );
            
            return ary[col * 3 + row];
        }
        
        Vec3 column( int col ) const
        {
            gfx_assert( col < 3 && col >= 0, "Column index out of bounds: expected 0 <= col <=2, was " << col );
            return Vec3( ary[col * 3], ary[col * 3 + 1], ary[col * 3 + 2] );
        }
        
        void setColumn( int col, Vec3 const& vec )
        {
            gfx_assert( col < 3 && col >= 0, "Column index out of bounds: expected 0 <= col <=2, was " << col );
            ary[col * 3]     = vec.x;
            ary[col * 3 + 1] = vec.y;
            ary[col * 3 + 2] = vec.z;
        }
        
        Vec3 row( int row ) const
        {
            gfx_assert( row < 3 && row >= 0, "Row index out of bounds: expected 0 <= row <=2, was " << row );
            return Vec3( ary[row], ary[3 + row], ary[6 + row] );
        }
        
        void setRow( int row, Vec3 const& vec )
        {
            gfx_assert( row < 3 && row >= 0, "Row index out of bounds: expected 0 <= row <=2, was " << row );
            ary[row]      = vec.x;
            ary[3 + row]  = vec.y;
            ary[6 + row]  = vec.z;
        }
        
        float cofactor( int row, int col ) const
        {
            gfx_assert( row < 3 && row >= 0, "Row index out of bounds: expected 0 <= row <=2, was " << row );
            gfx_assert( col < 3 && col >= 0, "Column index out of bounds: expected 0 <= col <=2, was " << col );
            
            float out = 0.0f;
            switch( row ) {
                case 0:
                    switch( col ) {
                        case 0:
                            out = yy*zz - yz*zy;
                            break;                    
                        case 1:
                            out = -(yx*zz - yz*zx);
                            break;
                        case 2:
                            out = yx*zy - yy*zx;
                            break;
                        default:
                            throw std::out_of_range("Column index out of bounds: was " << col);
                    }
                    break;
                case 1:
                    switch( col ) {
                        case 0:
                            out = -(xy*zz - xz*zy);
                            break;
                        case 1:
                            out = xx*zz - xz*zx;
                            break;
                        case 2:
                            out = -(xx*zy - xy*zx);
                            break;
                        default:
                            throw std::out_of_range("Column index out of bounds: was " << col);
                    } break;
                case 2:
                    switch( col ) {
                        case 0:
                            out = xy*zz - xz*zy;
                            break;
                        case 1:
                            out = -(xx*yz - xz*yx);
                            break;
                        case 2:
                            out = xx*yy - xy*yx;
                            break;
                        default:
                            throw std::out_of_range("Column index out of bounds: was " << col);
                    } break;
                default:
                    throw std::out_of_range( "Row index out of bounds: was " << row );
            }
            
            return out;
        }
        
        float* operator float*() { return ary; }
        
        Mat3 operator* ( Mat3 const& b ) {
            
            return Mat3( xx * b.xx + xy * b.yx + xz * b.zx, xx * b.yx + xy * b.yy + xz * b.yz, xx * b.zx + xy * b.zy + xz * b.zz,
                         yx * b.xx + yy * b.yx + yz * b.zx, yx * b.yx + yy * b.yy + yz * b.yz, yx * b.zx + yy * b.zy + yz * b.zz,
                         zx * b.xx + zy * b.yx + zz * b.zx, zx * b.yx + zy * b.yy + zz * b.yz, zx * b.zx + zy * b.zy + zz * b.zz );
        }
        
        struct {
            float xx,
                  yx,
                  zx;
                float xy,
                      yy,
                      zy;
                    float xz,
                          yz,
                          zz;
        };
        
        struct {
            float ss,
                  ts,
                  ps;
                float st,
                      tt,
                      pt;
                    float sp,
                          tp,
                          pp;
        };
        
    private:
    
        struct {
            float[9] ary;
        }
    
        struct {
            char[sizeof(float) * 9] bytes;
        };
        
    };
    
    inline Mat3 transpose( Mat3 const& a )
    {
        return Mat3( a.xx, a.yx, a.zx,
                     a.xy, a.yy, a.zy,
                     a.xz, a.yz, a.zz );
    }
    
}