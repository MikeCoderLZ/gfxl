#pragma once

#include "angle.hpp"
#include "vec3.hpp"

namespace gfx {

    union Qtn {
    
    public:

        Qtn() : i(0.0f), j(0.0f), k(0.0f), w(1.0f) {}
        Qtn( float i, float j, float k, float m )
            : i(i), j(j), k(k), w(w) {}

        Qtn( float fill )
            : i(fill), j(fill), k(fill), w(fill) {}

        Qtn( Qtn const& other )
            : i(other.i), j(other.j), k(other.k), w(other.w) {}

        Qtn( Qtn&& other )
            : i(other.i), j(other.j), k(other.k), w(other.w) {}

        static Qtn pure( Vec3 const& point ) {
            return { point[0], point[1], point[2], 0.0f };
        }

        static Qtn rotation( Mat3 const& rmat );

        static Qtn rotation( Vec3 const&        axis,
                             AngleDouble const& ang );

        float& operator [] (const int index)       { return ary[index]; }
        float  operator [] (const int index) const { return ary[index]; }

        Qtn operator - () const { return {-i,-j,-k,w}; }

        Qtn operator + (const Qtn& b) const { return {i + b.i, j + b.j, k + b.k, w + b.w}; }
        Qtn operator - (const Qtn& b) const { return {i - b.i, j - b.j, k - b.k, w - b.w}; }
        Qtn operator * (const Qtn& b) const;
        Qtn operator / (const Qtn& b) const { return *this * -b; }

        struct {
            float   i,j,k;
            float   w;
        };

    private:

        struct {
            float   ary[4];
        };

        struct {
            unsigned char   bytes[sizeof(float) * 4UL]; 
        };

    };

    inline
    Qtn Qtn::rotation( Mat3 const& rmat )
    {
        double trace = rmat(0,0) + rmat(1,1) + rmat(2,2) + 1.0;

        T q0;
        T q1;
        T q2;
        T q3;

        if( trace > 0.0 ) {
            double s = 0.5 / std::sqrt( trace );
            q0 = (rmat(1,2) - rmat(2,1)) * s;
            q1 = (rmat(2,0) - rmat(0,2)) * s;
            q2 = (rmat(0,1) - rmat(1,0)) * s;
            q3 = 0.25 / s;
        } else {
            if(     rmat(0,0) > rmat(1,1)
                and rmat(0,0) > rmat(2,2) ) {
                double s = 0.5 / std::sqrt( 1.0 + rmat(0,0) - rmat(1,1) - rmat(2,2));
                q0 = 0.5 * s;
                q1 = (rmat(1,0) + rmat(0,1)) * s;
                q2 = (rmat(2,0) + rmat(0,2)) * s;
                q3 = (rmat(2,1) + rmat(1,2)) * s;
            } else if (     rmat(1,1) > rmat(0,0)
                        and rmat(1,1) > rmat(2,2) ) {
                double s = 0.5 / std::sqrt( 1.0 + rmat(1,1) - rmat(0,0) - rmat(2,2));
                q0 = (rmat(1,0) + rmat(0,1)) * s;
                q1 = 0.5 * s;
                q2 = (rmat(2,1) + rmat(1,2)) * s;
                q3 = (rmat(2,0) + rmat(0,2)) * s;
            } else {
                double s = 0.5 / std::sqrt( 1.0 + rmat(2,2) - rmat(0,0) - rmat(1,1));
                q0 = (rmat(2,0) + rmat(0,2)) * s;
                q1 = (rmat(2,1) + rmat(1,2)) * s;
                q2 = 0.5 * s;
                q3 = (rmat(1,0) + rmat(0,1)) * s;
            }
        }
        
        return {q0, q1, q2, q3};
    }

    inline
    Qtn Qtn::rotation( Vec3 const&        axis,
                       AngleDouble const& ang )
    {
        double h_rads = ang.toRads() * 0.5;
        Vec3 n_axis = axis.norm();
        double sin_h_rads = sin( h_rads );
        return Qtn( n_axis[0] * sin_h_rads,
                    n_axis[1] * sin_h_rads,
                    n_axis[2] * sin_h_rads,
                    cos( h_rads )           );
    }

    inline
    Qtn Qtn::operator * (const Qtn& b)
    {
        return {  ary[0] * b.ary[3] + ary[1] * b.ary[2]
                - ary[2] * b.ary[1] + ary[3] * b.ary[0],
                - ary[0] * b.ary[2] + ary[1] * b.ary[3]
                + ary[2] * b.ary[0] + ary[3] * b.ary[1],
                  ary[0] * b.ary[1] - ary[1] * b.ary[0]
                + ary[2] * b.ary[3] + ary[3] * b.ary[2],
                  ary[3] * b.ary[3] - ary[0] * b.ary[0]
                - ary[1] * b.ary[1] - ary[2] * b.ary[2] };
    }

} // namemspace gfx