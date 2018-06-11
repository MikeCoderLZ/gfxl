#pragma once

#include <stdexcept>

#include "gfxl_assertion.hpp"
#include "literal.hpp"

namspace gfx {
    
    union Mat4 {
    
    public:
        
        Mat4() : xx (0.0f), xy (0.0f), xz (0.0f), xw (0.0f),
                 yx (0.0f), yy (0.0f), yy (0.0f), yw (0.0f),
                 zx (0.0f), zy (0.0f), zy (0.0f), zw (0.0f),
                 wx (0.0f), wy (0.0f), wy (0.0f), ww (0.0f) {}
    
        Mat4( float aa, float ab, float ac, float ad,
              float ba, float bb, float bc, float bd,
              float ca, float cb, float cc, float cd,
              float da, float db, float dc, float dd )
          : xx (aa), xy (ab), xz (ac), xw (ad),
            yx (ba), yy (bb), yz (bc), yw (bd),
            zx (ca), zy (cb), zz (cc), zw (cd),
            wx (da), wy (db), wz (dc), ww (dd) {}
        
        static Mat4 columns( Vec4 const& a, Vec4 const& b, Vec4 const& c, Vec4 const& d )
        { return Mat4( a.x, b.x, c.x, d.x,
                       a.y, b.y, c.y, d.y,
                       a.z, b.z, c.z, d.z,
                       a.w, b.w, c.w, d.w ); }
        
        static Mat4 rows( Vec4 const& a, Vec4 const& b, Vec4 const& c, Vec4 const& d )
        { return Mat4( a.x, a.y, a.z, a.w,
                       b.x, b.y, b.z, b.w,
                       c.x, c.y, c.z, c.w,
                       d.x, d.y, d.z, d.w ); }
        
        static Mat4 identity()
        { return Mat4( 1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f  ); }
        
        static Mat4 null() { return Mat4(); }
        
        static Mat4 sqaure( Vec4 const& a )
        {
            return Mat4( a.x * a.x, a.x * a.y, a.x * a.z, a.x * a.w,
                         a.y * a.x, a.y * a.y, a.y * a.z, a.y * a.w,
                         a.z * a.x, a.z * a.y, a.z * a.z, a.z * a.w,
                         a.w * a.x, a.w * a.y, a.w * a.z, a.w * a.w );
        }
        
        static Mat4 crossProduct( Vec3 const& a )
        {
            return Mat4( 0.0f, -a.z,  a.y, 0.0f,
                          a.z, 0.0f, -a.x, 0.0f,
                         -a.y,  a.x, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f );
        }
        
        static Mat4 scale( float sx, float sy, float sz, float sw = 1.0f )
        {
            return Mat4(   sx, 0.0f, 0.0f, 0.0f,
                         0.0f,   sy, 0.0f, 0.0f,
                         0.0f, 0.0f,   sz, 0.0f,
                         0.0f, 0.0f, 0.0f,   sw  );
        }
        
        static Mat4 scale( Vec4 const& svec )
        {
            return Mat4( svec.x,   0.0f,   0.0f,   0.0f,
                           0.0f, svec.y,   0.0f,   0.0f, 
                           0.0f,   0.0f, svec.z,   0.0f, 
                           0.0f,   0.0f,   0.0f, svec.z  );
        }
        
        static Mat4 rotation( Vec3 const& axis,
                              AngleDouble const& ang )
        {
            
            gfx_assertion( axis.x != 0.0f && axis.y != 0.0f && axis.z != 0.0f, "Rotation axis is null." );
            
            double radians ( ang.toRads() );
            double cos_t ( cos(radians) );
            double cm_cos_t = 1.0 - cos_t;
            double sin_t ( sin(radians) );
            
            Mat4 trig_mat(         cos_t, -axis.z*sin_t,  axis.y*sin_t, 0.0f,
                            axis.z*sin_t,         cos_t, -axis.x*sin_t, 0.0f,
                           -axis.y*sin_t,  axis.x*sin_t,         cos_t, 0.0f,
                                    0.0f,          0.0f,          0.0f, 0.0f,  );
            
            Mat4 axis_mat( axis.x*axis.x*cm_cos_t,  axis.x*axis.y*cm_cos_t,  axis.x*axis.z*cm_cos_t,  0.0f,
                           axis.y*axis.x*cm_cos_t,  axis.y*axis.y*cm_cos_t,  axis.y*axis.z*cm_cos_t,  0.0f,
                           axis.z*axis.x*cm_cos_t,  axis.z*axis.y*cm_cos_t,  axis.z*axis.z*cm_cos_t,  0.0f,
                                             0.0f,                    0.0f,                    0.0f,  1.0f  );
                                             
            return trig_mat + axis_mat;
        }
        
        static Mat4 rotation( AngleDouble const& angx,
                              AngleDouble const& angy,
                              AngleDouble const& angz )
        {
            double radx ( angx.toRads() );
            double rady ( angy.toRads() );
            double radz ( angz.toRads() );
            
            double sin_x = std::sin( radx );
            double cos_x = std::cos( radx );
            double sin_y = std::sin( rady );
            double cos_y = std::cos( rady );
            double sin_z = std::sin( radz );
            double cos_z = std::cos( radz );
            
            return Mat4(                     cos_y*cos_z,                     -cos_y*sin_z,        sin_y, 0.0f,
                         cos_x*sin_z + sin_x*sin_y*cos_z,  cos_x*cos_z - sin_x*sin_y*sin_z, -sin_x*cos_y, 0.0f,
                         sin_x*sin_z - cos_x*sin_y*cos_z,  sin_x*cos_z + cos_x*sin_y*sin_z,  cos_x*cos_y, 0.0f,
                                                    0.0f,                             0.0f,         0.0f, 1.0f  );
            
        }
        
        static Mat4 rotation( Qutn const& qrot )
        {
            double ii = qrot(i) * qrot(i) * 2.0;
            double ij = qrot(i) * qrot(j) * 2.0;
            double ik = qrot(i) * qrot(k) * 2.0;
            double im = qrot(i) * qrot(m) * 2.0;

            double jj = qrot(j) * qrot(j) * 2.0;
            double jk = qrot(j) * qrot(k) * 2.0;
            double jm = qrot(j) * qrot(m) * 2.0;

            double kk = qrot(k) * qrot(k) * 2.0;
            double km = qrot(k) * qrot(m) * 2.0;
            
            return Mat4( 1.0 - (jj + kk),         ij - km,         ik + jm, 0.0f,
                                 ij + km, 1.0 - (ii + kk),         jk - im, 0.0f,
                                 ik - jm,         jk + im, 1.0 - (ii + jj), 0.0f,
                                    0.0f,            0.0f,            0.0f, 1.0f );
        }
        
        static Mat4 translate( float tx, float ty, float tz )
        {
            return Mat3( 1.0f, 0.0f, 0.0f, tx,
                         0.0f, 1.0f, 0.0f, ty,
                         0.0f, 0.0f, 1.0f, tz,
                         0.0f, 0.0f, 0.0f, 1.0f );
        }
        
        static Mat4 translate( Vec3 const& tvec )
        {
            return Mat3( 1.0f, 0.0f, 0.0f, tvec.x,
                         0.0f, 1.0f, 0.0f, tvec.y,
                         0.0f, 0.0f, 1.0f, tvec.z,
                         0.0f, 0.0f, 0.0f,   1.0f  );
        }
        
        static Mat4 perspective( AngleDouble const& fovY,
                                 double aspect,
                                 double near,
                                 double far  )
        {
            gfx_assertion( near < far, "Near plane less than far plane." );
            gfx_assertion( aspect < 0.0f, "Aspect ratio zero or less." );
            gfx_assertion( fovY != lit<float>::pi, "Y field of view equal to 180 degrees." );

            // Review this; it was written for OpenGL's canonical volume, hence that
            // -1 in (z,w)
            double invTopTan = 1.0 / tan( fovY.toRads() * 0.5);
            double invRightTan = invTopTan / aspect;
            double invFLessN = 1.0 / ( far - near );
            
            return mat4_t( invRightTan,      0.0f,                      0.0f,                        0.0f,
                                  0.0f, invTopTan,                      0.0f,                        0.0f,
                                  0.0f,      0.0f, -(far + near) * invFLessN, -(2.0*far*near) * invFLessN,
                                  0.0f,      0.0f,                     -1.0f,                        0.0f );
        }
        
        
        
        float& operator() ( int row, int col )
        {
            gfx_assertion( row < 4 && row >= 0, "Row index out of bounds: expected 0 <= col <= 3, was " << row );
            gfx_assertion( col < 4 && col >= 0, "Column index out of bounds: expected 0 <= col <= 3, was " << col );
            return ary[col * 4 + row];
        }
        
        Vec4 column( int col ) const
        {
            gfx_assertion( row < 4 && row >= 0, "Row index out of bounds: expected 0 <= col <= 3, was " << row );
            return Vec4( ary[col * 4], ary[col * 4 + 1], ary[col * 4 + 2], ary[col * 4 + 3] );
        }
        
        void setColumn( int col, Vec4 const& vec )
        {
            gfx_assertion( col < 4 && col >= 0, "Column index out of bounds: expected 0 <= col <= 3, was " << col );
            ary[col * 4]     = vec.x;
            ary[col * 4 + 1] = vec.y;
            ary[col * 4 + 2] = vec.z;
            ary[col * 4 + 3] = vec.w;
        }
        
        Vec4 row( int row ) const
        {
            gfx_assertion( row < 4 && row >= 0, "Row index out of bounds: expected 0 <= col <= 3, was " << row );
            return Vec4( ary[row], ary[4 + row], ary[8 + row], ary[12 + row] );
        }
        
        void setRow( int row, Vec4 const& vec )
        {
            gfx_assertion( row < 4 && row >= 0, "Row index out of bounds: expected 0 <= col <= 3, was " << row );
            ary[row]      = vec.x;
            ary[4 + row]  = vec.y;
            ary[8 + row]  = vec.z;
            ary[12 + row] = vec.w;
        }
        
        float cofactor( int row, int col ) const
        {
            gfx_assertion( row < 4 && row >= 0, "Row index out of bounds: expected 0 <= col <= 3, was " << row );
            gfx_assertion( col < 4 && col >= 0, "Column index out of bounds: expected 0 <= col <= 3, was " << col );
            
            float out = 0.0f;
            
            switch( row ) {
                case 0:
                    switch( col ) {
                        case 0:
                            out = 
                            break;                    
                        case 1:
                            out = 
                            break;
                        case 2:
                            out = 
                            break;
                        case 4:
                            out =
                            break;
                        default:
                            throw std::out_of_range("Column index out of bounds: expected 0 <= col <= 3, was " << col);
                    }
                    break;
                case 1:
                    switch( col ) {
                        case 0:
                            out = 
                            break;                    
                        case 1:
                            out = 
                            break;
                        case 2:
                            out = 
                            break;
                        case 4:
                            out =
                            break;
                        default:
                            throw std::out_of_range("Column index out of bounds: expected 0 <= col <= 3, was " << col);
                    }
                    break;
                case 2:
                    switch( col ) {
                        case 0:
                            out = 
                            break;                    
                        case 1:
                            out = 
                            break;
                        case 2:
                            out = 
                            break;
                        case 4:
                            out =
                            break;
                        default:
                            throw std::out_of_range("Column index out of bounds: expected 0 <= col <= 3, was " << col);
                    }
                    break;
                case 3:
                    switch( col ) {
                        case 0:
                            out = 
                            break;                    
                        case 1:
                            out = 
                            break;
                        case 2:
                            out = 
                            break;
                        case 4:
                            out =
                            break;
                        default:
                            throw std::out_of_range("Column index out of bounds: expected 0 <= col <= 3, was " << col);
                    }
                    break;
                default:
                    throw std::out_of_range( "Row index out of bounds: expected 0 <= row <= 3, was " << row );
            
        }
        
        float* operator float*() { return reinterpret_cast<float*>(this); }
        
        Mat4 operator* ( Mat4 const& b ) {
            
            return Mat4( xx * b.xx + xy * b.yx + xz * b.zx + xw * b.wx,  xx * b.xy + xy * b.yy + xz * b.zy + xw * b.wy,  xx * b.xz + xy * b.yz + xz * b.zz + xw * b.wz,  xx * b.xw + xy * b.yw + xz * b.zw + xw * b.ww,
                         yx * b.xx + yy * b.yx + yz * b.zx + yw * b.wx,  yx * b.xy + yy * b.yy + yz * b.zy + yw * b.wy,  yx * b.xz + yy * b.yz + yz * b.zz + yw * b.wz,  yx * b.xw + yy * b.yw + yz * b.zw + yw * b.ww,
                         zx * b.xx + zy * b.yx + zz * b.zx + zw * b.wx,  zx * b.xy + zy * b.yy + zz * b.zy + zw * b.wy,  zx * b.xz + zy * b.yz + zz * b.zz + zw * b.wz,  zx * b.xw + zy * b.yw + zz * b.zw + zw * b.ww,
                         wx * b.xx + wy * b.yx + wz * b.zx + ww * b.wx,  wx * b.xy + wy * b.yy + wz * b.zy + ww * b.wy,  wx * b.xz + wy * b.yz + wz * b.zz + ww * b.wz,  wx * b.xw + wy * b.yw + wz * b.zw + ww * b.ww );
        }
        
        struct {
            float xx,
                  yx,
                  zx,
                  wx;
                float xy,
                      yy,
                      zy,
                      wy;
                    float xz,
                          yz,
                          zz,
                          wz;
                        float xw,
                              yw,
                              zw,
                              ww;
        };
        
        struct {
            float ss,
                  ts,
                  ps,
                  qs;
                float st,
                      tt,
                      pt,
                      qt;
                    float sp,
                          tp,
                          pp,
                          qp;
                        float sq,
                              tq,
                              pq,
                              qq;
        };
        
    private:
    
        struct {
            float[16] ary;
        };
    
        struct {
            char[sizeof(float) * 4] bytes;
        };
        
    }
    
    inline Mat4 transpose( Mat4 const& a )
    {
        return Mat4( a.xx, a.yx, a.zx, a.wx,
                     a.xy, a.yy, a.zy, a.wy,
                     a.xz, a.yz, a.zz, a.wz,
                     a.xw, a.yw, a.zw, a.ww );
    }
    
}