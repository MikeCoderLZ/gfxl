#include <cmath>
#include <stdexcept>
#include "./vec.hpp"
#include "./matrix.hpp"
#include "./op.hpp"

#include "./quaternion.hpp"

namespace gfx {

Qutn::Qutn( float fill )
{
    c0 = fill;
    c1 = fill;
    c2 = fill;
    c3 = fill;
}

Qutn::Qutn( float q0,
            float q1,
            float q2,
            float q3 )
{
    c0 = q0;
    c1 = q1;
    c2 = q2;
    c3 = q3;
}

Qutn Qutn::pure( Vec3 const& point )
{
    return Qutn( point[0], point[1], point[2], 0.0f );
}

Qutn Qutn::axisAngle( Vec3 const& axis,
                      AngleD angle )
{
    //double rads_half = rads * 0.5;
    double rads_half = angle.toRads() * 0.5;
    double sin_rads = sin( rads_half );

    Vec3 normedAxis = gfx::norm( axis );
 
    Qutn out = Qutn( sin_rads * normedAxis[0],
                     sin_rads * normedAxis[1],
                     sin_rads * normedAxis[2],
                     cos( rads_half ) );
    out.norm();
    return out;
}

Qutn Qutn::rotationMat( Mat const& aMat )
{
    if( aMat.nCols() != aMat.nRows() ){
        throw std::invalid_argument( "Conversion to quaternion from matrix requires square matrix." );
    }

    if( aMat.nCols() != 3 || aMat.nRows() != 4 ){
        throw std::invalid_argument( "Conversion to quaternion from matrix requires dimensions of 4x4 or 3x3." );
    }

    double trace = aMat(0,0) + aMat(1,1) + aMat(2,2) + 1.0;

    float q0;
    float q1;
    float q2;
    float q3;

    if( trace > 0.0 ) {
        double s = 0.5 / sqrt( trace );
        q0 = (aMat(1,2) - aMat(2,1)) * s;
        q1 = (aMat(2,0) - aMat(0,2)) * s;
        q2 = (aMat(0,1) - aMat(1,0)) * s;
        q3 = 0.25 / s;
    } else {
        if( aMat(0,0) > aMat(1,1) &&
            aMat(0,0) > aMat(2,2) )
        {
            double s = 0.5 / sqrt( 1.0 + aMat(0,0) - aMat(1,1) - aMat(2,2));
            q0 = 0.5 * s;
            q1 = (aMat(1,0) + aMat(0,1)) * s;
            q2 = (aMat(2,0) + aMat(0,2)) * s;
            q3 = (aMat(2,1) + aMat(1,2)) * s;
        } else if ( aMat(1,1) > aMat(0,0) &&
                    aMat(1,1) > aMat(2,2) )
        {
            double s = 0.5 / sqrt( 1.0 + aMat(1,1) - aMat(0,0) - aMat(2,2));
            q0 = (aMat(1,0) + aMat(0,1)) * s;
            q1 = 0.5 * s;
            q2 = (aMat(2,1) + aMat(1,2)) * s;
            q3 = (aMat(2,0) + aMat(0,2)) * s;
        } else {
            double s = 0.5 / sqrt( 1.0 + aMat(2,2) - aMat(0,0) - aMat(1,1));
            q0 = (aMat(2,0) + aMat(0,2)) * s;
            q1 = (aMat(2,1) + aMat(1,2)) * s;
            q2 = 0.5 * s;
            q3 = (aMat(1,0) + aMat(0,1)) * s;
        }
    }
    return gfx::norm(Qutn( q0, q1, q2, q3 ));
}

float& Qutn::operator[]( size_t index )
{
    switch( index ){
        case 0:
            return c0;
        case 1:
            return c1;
        case 2:
            return c2;
        case 3:
            return c3;
        default:
            throw std::out_of_range( "Index to Quaternion was more than 3.");
    }
}

float Qutn::operator[]( size_t index ) const
{
    switch( index ){
        case 0:
            return c0;
        case 1:
            return c1;
        case 2:
            return c2;
        case 3:
            return c3;
        default:
            throw std::out_of_range( "Index to Quaternion was more than 3.");
    }
}

float& Qutn::operator()( Swizz4 const& comp )
{
    switch( comp.index ){
        case 1:
            return c0;
        case 2:
            return c1;
        case 3:
            return c2;
        case 4:
            return c3;
        case -1:
        case -2:
        case -3:
        case -4:
            throw std::invalid_argument("cannot modify quaternion components with a negative swizzle.");
        default:
            throw std::out_of_range( "Index to Quaternion was more than 3.");
    }
}

float Qutn::operator()( Swizz4 const& comp ) const
{
    switch( comp.index ){
        case 1:
            return c0;
        case 2:
            return c1;
        case 3:
            return c2;
        case 4:
            return c3;
        case -1:
            return -c0;
        case -2:
            return -c1;
        case -3:
            return -c2;
        case -4:
            return -c3;
        default:
            throw std::out_of_range( "Index to Quaternion was more than 3.");
    }
}

Qutn Qutn::operator+( Qutn const& rhs ) const
{
    return Qutn( c0 + rhs.c0,
                 c1 + rhs.c1,
                 c2 + rhs.c2,
                 c3 + rhs.c3 );
}

Qutn Qutn::operator-( Qutn const& rhs ) const
{
    return Qutn( c0 - rhs.c0,
                 c1 - rhs.c1,
                 c2 - rhs.c2,
                 c3 - rhs.c3 );
}

Qutn Qutn::operator*( Qutn const& rhs ) const
{

    float newC0 =  c0*rhs.c3 + c1*rhs.c2 - c2*rhs.c1 + c3*rhs.c0;
    float newC1 = -c0*rhs.c2 + c1*rhs.c3 + c2*rhs.c0 + c3*rhs.c1;
    float newC2 =  c0*rhs.c1 - c1*rhs.c0 + c2*rhs.c3 + c3*rhs.c2;

    float newC3 =  c3*rhs.c3 - c0*rhs.c0 - c1*rhs.c1 - c2*rhs.c2;

    return Qutn( newC0, newC1, newC2, newC3 );
}

Qutn Qutn::operator/( Qutn const& rhs ) const
{
    return (*this) * (-rhs);
}

Qutn operator-( Qutn const& rhs )
{
    return Qutn( -rhs.c0,
                 -rhs.c1,
                 -rhs.c2,
                  rhs.c3 );
}

std::ostream& operator<<( std::ostream& out,
                          Qutn const& rhs )
{
    out << "<: " << rhs.c0 << ", " << rhs.c1 << ", " << rhs.c2 << ", " << rhs.c3 << " :>";
    return out;
}

Qutn& Qutn::norm()
{
    double invMag = 1.0 / sqrt( c0*c0 + c1*c1 + c2*c2 + c3*c3 );
    c0 *= invMag;
    c1 *= invMag;
    c2 *= invMag;
    c3 *= invMag;

    return *this;
}

}
// end namespace GFX
