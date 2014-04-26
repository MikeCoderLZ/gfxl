#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include "./vec.hpp"
#include "./op.hpp"

namespace gfx {

//////////////// Swizzlers ////////////////

class SwizzleFactory {
    public:
        static Swizz2 MakeSwizz2( int index );
        static Swizz3 MakeSwizz3( int index );
        static Swizz4 MakeSwizz4( int index );
};

inline Swizz2 SwizzleFactory::MakeSwizz2( int index )
{
    return Swizz2( index );
}

inline Swizz3 SwizzleFactory::MakeSwizz3( int index )
{
    return Swizz3( index );
}

inline Swizz4 SwizzleFactory::MakeSwizz4( int index )
{
    return Swizz4( index );
}

Swizz4 operator-( Swizz4 const& rhs )
{
    return Swizz4( -rhs.index );
}

Swizz4::Swizz4( int index )
{
    if(    abs(index) < 1
        || abs(index) > 4 ){
        throw std::out_of_range("Construction of Vec4 swizzle out of range.");
    }
    this->index = index;
}

Swizz4 const w = SwizzleFactory::MakeSwizz4( 4 );
Swizz4 const q = SwizzleFactory::MakeSwizz4( 4 );
Swizz4 const a = SwizzleFactory::MakeSwizz4( 4 );
Swizz4 const m = SwizzleFactory::MakeSwizz4( 4 );

Swizz3::Swizz3( int index )
{
    if(    abs(index) < 1
        || abs(index) > 3 ){
        throw std::out_of_range("Construction of Vec3 swizzle out of range.");
    }
    this->index = index;
}

Swizz3 operator-( Swizz3 const& rhs )
{
    return Swizz3( -rhs.index );
}

/*Swizz3::Swizz3( Swizz2 const& src )
{
    this->index = src.index;
}*/

Swizz3 const z = SwizzleFactory::MakeSwizz3( 3 );
Swizz3 const p = SwizzleFactory::MakeSwizz3( 3 );
Swizz3 const b = SwizzleFactory::MakeSwizz3( 3 );
Swizz3 const k = SwizzleFactory::MakeSwizz3( 3 );

Swizz2 operator-( Swizz2 const& rhs )
{
    return Swizz2( -rhs.index );
}

Swizz2::Swizz2( int index )
{
    if(    abs(index) < 1
        || abs(index) > 2 ){
        throw std::out_of_range("Construction of Vec2 swizzle out of range.");
    }
    this->index = index;
}

Swizz2 const x = SwizzleFactory::MakeSwizz2( 1 );
Swizz2 const y = SwizzleFactory::MakeSwizz2( 2 );

Swizz2 const s = SwizzleFactory::MakeSwizz2( 1 );
Swizz2 const t = SwizzleFactory::MakeSwizz2( 2 );

Swizz2 const r = SwizzleFactory::MakeSwizz2( 1 );
Swizz2 const g = SwizzleFactory::MakeSwizz2( 2 );

Swizz2 const i = SwizzleFactory::MakeSwizz2( 1 );
Swizz2 const j = SwizzleFactory::MakeSwizz2( 2 );

//////////////// Vec2 ///////////////////

Vec2::Vec2( float x0,
            float x1 )
{
    c0 = x0;
    c1 = x1;
}

Vec2::Vec2( float fill )
{
    c0 = fill;
    c1 = fill;
}

float& Vec2::operator[]( int index )
{
    switch( index ){
        case 0:
            return c0;
        case 1:
            return c1;
        default:
            throw std::out_of_range("vec2 index out of range");
    }
}

float Vec2::operator[]( int index ) const
{
    switch( index ){
        case 0:
            return c0;
        case 1:
            return c1;
        default:
            throw std::out_of_range("vec2 index out of range");
    }
}

float& Vec2::operator()( Swizz2 const& comp )
{
    switch( comp.index ){
        case 1:
            return c0;
        case 2:
            return c1;
        case -1:
        case -2:
            throw std::invalid_argument("cannot modify vec2 components with a negative swizzle");
        default:
            throw std::out_of_range("vec2 index out of range");
    }
}

float Vec2::operator()( Swizz2 const& comp ) const
{
    switch( comp.index ){
        case 1:
            return c0;
        case 2:
            return c1;
        case -1:
            return -c0;
        case -2:
            return -c1;
        default:
            throw std::out_of_range("vec2 index out of range");
    }
}

Vec2 Vec2::operator()( Swizz2 const& x0,
                       Swizz2 const& x1 ) const
{
    Vec2 out;

    if( x0.index < 0 ){
        out[0] = -(*this)[-(x0.index) - 1];
    } else {
        out[0] = (*this)[x0.index - 1];
    }
    if( x1.index < 0 ){
        out[1] = -(*this)[-(x1.index) - 1];
    } else {
        out[1] = (*this)[x1.index -1];
    }
    return out;
}

Vec3 Vec2::operator()( Swizz2 const& x0,
                       Swizz2 const& x1,
                       Swizz2 const& x2 ) const
{
    Vec3 out;

    if( x0.index < 0 ){
        out[0] = -(*this)[-(x0.index) - 1];
    } else {
        out[0] = (*this)[x0.index - 1];
    }
    if( x1.index < 0 ){
        out[1] = -(*this)[-(x1.index) - 1];
    } else {
        out[1] = (*this)[x1.index -1];
    }
    if( x2.index < 0 ){
        out[2] = -(*this)[-(x2.index) - 1];
    } else {
        out[2] = (*this)[x2.index -1];
    }
    
    return out;
}

Vec4 Vec2::operator()( Swizz2 const& x0,
                       Swizz2 const& x1,
                       Swizz2 const& x2,
                       Swizz2 const& x3 ) const
{
    Vec4 out;

       if( x0.index < 0 ){
        out[0] = -(*this)[-(x0.index) - 1];
    } else {
        out[0] = (*this)[x0.index - 1];
    }
    if( x1.index < 0 ){
        out[1] = -(*this)[-(x1.index) - 1];
    } else {
        out[1] = (*this)[x1.index -1];
    }
    if( x2.index < 0 ){
        out[2] = -(*this)[-(x2.index) - 1];
    } else {
        out[2] = (*this)[x2.index -1];
    }
    if( x3.index < 0 ){
        out[3] = -(*this)[-(x3.index) - 1];
    } else {
        out[3] = (*this)[x3.index - 1];
    }

    return out;
}

Vec2 Vec2::operator+( Vec2 const& rhs ) const
{
    return Vec2( c0 + rhs.c0,
                 c1 + rhs.c1 );
}

Vec2 Vec2::operator-( Vec2 const& rhs ) const
{
    return Vec2( c0 - rhs.c0,
                 c1 - rhs.c1 );
}

Vec2 Vec2::operator*( Vec2 const& rhs ) const
{
    return Vec2( c0 * rhs.c0,
                 c1 * rhs.c1 );
}

Vec2 Vec2::operator/( Vec2 const& rhs ) const
{
    return Vec2( c0 / rhs.c0,
                 c1 / rhs.c1 );
}

Vec2& Vec2::norm()
{
    float c0_lcl = c0;
    float c1_lcl = c1;

    float invMag = 1.0f / sqrt(  c0_lcl * c0_lcl
                               + c1_lcl * c1_lcl );
    this->c0 *= invMag;
    this->c1 *= invMag;

    return *this;
}

std::ostream& operator<<( std::ostream& out,
                          Vec2 const& rhs )
{
    out << "< " << rhs.c0 << ", " << rhs.c1 << " >";
    return out;
}

////////////////// Vec3 //////////////////

Vec3::Vec3( Vec3 const& src )
{
    c0 = src.c0;
    c1 = src.c1;
    c2 = src.c2;
}

Vec3::Vec3( float x0,
            float x1,
            float x2 )
{
    c0 = x0;
    c1 = x1;
    c2 = x2;
}

Vec3::Vec3( float fill )
{
    c0 = fill;
    c1 = fill;
    c2 = fill;
}

float& Vec3::operator[]( int index )
{
    switch( index ){
        case 0:
            return c0;
        case 1:
            return c1;
        case 2:
            return c2;
        default:
            throw std::out_of_range("vec3 index out of range");
    }
}

float Vec3::operator[]( int index ) const
{
    switch( index ){
        case 0:
            return c0;
        case 1:
            return c1;
        case 2:
            return c2;
        default:
            throw std::out_of_range("vec3 index out of range");
    }
}

float& Vec3::operator()( Swizz3 const& comp )
{
    switch( comp.index ){
        case 1:
            return c0;
        case 2:
            return c1;
        case 3:
            return c2;
        case -1:
        case -2:
        case -3:
            throw std::invalid_argument("cannot modify vec3 components with a negative swizzle");
        default:
            throw std::out_of_range("vec3 index out of range");
    }
}

float Vec3::operator()( Swizz3 const& comp ) const
{
    switch( comp.index ){
        case 1:
            return c0;
        case 2:
            return c1;
        case 3:
            return c2;
        case -1:
            return -c0;
        case -2:
            return -c1;
        case -3:
            return -c2;
        default:
            throw std::out_of_range("vec3 index out of range");
    }
}


Vec2 Vec3::operator()( Swizz3 const& x0,
                       Swizz3 const& x1 ) const
{
    Vec2 out;

    if( x0.index < 0 ){
        out[0] = -(*this)[-(x0.index) - 1];
    } else {
        out[0] = (*this)[x0.index - 1];
    }
    if( x1.index < 0 ){
        out[1] = -(*this)[-(x1.index) - 1];
    } else {
        out[1] = (*this)[x1.index -1];
    }
    return out;
}

Vec3 Vec3::operator()( Swizz3 const& x0,
                       Swizz3 const& x1,
                       Swizz3 const& x2 ) const
{
    Vec3 out;

    if( x0.index < 0 ){
        out[0] = -(*this)[-(x0.index) - 1];
    } else {
        out[0] = (*this)[x0.index - 1];
    }
    if( x1.index < 0 ){
        out[1] = -(*this)[-(x1.index) - 1];
    } else {
        out[1] = (*this)[x1.index -1];
    }
    if( x2.index < 0 ){
        out[2] = -(*this)[-(x2.index) - 1];
    } else {
        out[2] = (*this)[x2.index -1];
    }
    
    return out;
}

Vec4 Vec3::operator()( Swizz3 const& x0,
                       Swizz3 const& x1,
                       Swizz3 const& x2,
                       Swizz3 const& x3 ) const
{
    Vec4 out;

    if( x0.index < 0 ){
        out[0] = -(*this)[-(x0.index) - 1];
    } else {
        out[0] = (*this)[x0.index - 1];
    }
    if( x1.index < 0 ){
        out[1] = -(*this)[-(x1.index) - 1];
    } else {
        out[1] = (*this)[x1.index -1];
    }
    if( x2.index < 0 ){
        out[2] = -(*this)[-(x2.index) - 1];
    } else {
        out[2] = (*this)[x2.index -1];
    }
    if( x3.index < 0 ){
        out[3] = -(*this)[-(x3.index) - 1];
    } else {
        out[3] = (*this)[x3.index - 1];
    }

    return out;
}

Vec3 Vec3::operator+( Vec3 const& rhs ) const
{
    return Vec3( c0 + rhs.c0,
                 c1 + rhs.c1,
                 c2 + rhs.c2 );
}

Vec3 Vec3::operator-( Vec3 const& rhs ) const
{
    return Vec3( c0 - rhs.c0,
                 c1 - rhs.c1,
                 c2 - rhs.c2 );
}

Vec3 Vec3::operator*( Vec3 const& rhs ) const
{
    return Vec3( c0 * rhs.c0,
                 c1 * rhs.c1,
                 c2 * rhs.c2 );
}

Vec3 Vec3::operator/( Vec3 const& rhs ) const
{
    return Vec3( c0 / rhs.c0,
                 c1 / rhs.c1,
                 c2 / rhs.c2 );
}

Vec3& Vec3::norm()
{
    float c0_lcl = this->c0;
    float c1_lcl = this->c1;
    float c2_lcl = this->c2;

    float invMag = 1.0f / sqrt(   c0_lcl * c0_lcl
                                + c1_lcl * c1_lcl
                                + c2_lcl * c2_lcl );
    this->c0 *= invMag;
    this->c1 *= invMag;
    this->c2 *= invMag;

    return *this;
}

std::ostream& operator<<( std::ostream& out,
                          Vec3 const& rhs )
{
    out << "< " << rhs.c0 << ", " << rhs.c1 << ", " << rhs.c2 << " >";
    return out;
}

////////////////// Vec4 //////////////////

Vec4::Vec4( float x0,
            float x1,
            float x2,
            float x3 )
{
    c0 = x0;
    c1 = x1;
    c2 = x2;
    c3 = x3;
}

Vec4::Vec4( float fill )
{
    c0 = fill;
    c1 = fill;
    c2 = fill;
    c3 = fill;
}

float& Vec4::operator[]( int index )
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
            throw std::out_of_range("vec4 index out of range");
    }
}

float Vec4::operator[]( int index ) const
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
            throw std::out_of_range("vec4 index out of range");
    }
}

float& Vec4::operator()( Swizz4 const& comp )
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
            throw std::invalid_argument("cannot modify vec4 components with a negative swizzle");
        default:
            throw std::out_of_range("vec4 index out of range");
    }
}

float Vec4::operator()( Swizz4 const& comp ) const
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
            throw std::out_of_range("vec4 index out of range");
    }
}

Vec2 Vec4::operator()( Swizz4 const& x0,
                       Swizz4 const& x1 ) const
{
    Vec2 out;

    if( x0.index < 0 ){
        out[0] = -(*this)[-(x0.index) - 1];
    } else {
        out[0] = (*this)[x0.index - 1];
    }
    if( x1.index < 0 ){
        out[1] = -(*this)[-(x1.index) - 1];
    } else {
        out[1] = (*this)[x1.index -1];
    }
    return out;
}

Vec3 Vec4::operator()( Swizz4 const& x0,
                       Swizz4 const& x1,
                       Swizz4 const& x2 ) const
{
    Vec3 out;

    if( x0.index < 0 ){
        out[0] = -(*this)[-(x0.index) - 1];
    } else {
        out[0] = (*this)[x0.index - 1];
    }
    if( x1.index < 0 ){
        out[1] = -(*this)[-(x1.index) - 1];
    } else {
        out[1] = (*this)[x1.index -1];
    }
    if( x2.index < 0 ){
        out[2] = -(*this)[-(x2.index) - 1];
    } else {
        out[2] = (*this)[x2.index -1];
    }
    
    return out;
}

Vec4 Vec4::operator()( Swizz4 const& x0,
                       Swizz4 const& x1,
                       Swizz4 const& x2,
                       Swizz4 const& x3 ) const
{
    Vec4 out;

    if( x0.index < 0 ){
        out[0] = -(*this)[-(x0.index) - 1];
    } else {
        out[0] = (*this)[x0.index - 1];
    }
    if( x1.index < 0 ){
        out[1] = -(*this)[-(x1.index) - 1];
    } else {
        out[1] = (*this)[x1.index -1];
    }
    if( x2.index < 0 ){
        out[2] = -(*this)[-(x2.index) - 1];
    } else {
        out[2] = (*this)[x2.index -1];
    }
    if( x3.index < 0 ){
        out[3] = -(*this)[-(x3.index) - 1];
    } else {
        out[3] = (*this)[x3.index - 1];
    }

    return out;
}

Vec4 Vec4::operator+( Vec4 const& rhs ) const
{
    return Vec4( c0 + rhs.c0,
                 c1 + rhs.c1,
                 c2 + rhs.c2,
                 c3 + rhs.c3 );
}

Vec4 Vec4::operator-( Vec4 const& rhs ) const
{
    return Vec4( c0 - rhs.c0,
                 c1 - rhs.c1,
                 c2 - rhs.c2,
                 c3 - rhs.c3 );
}

Vec4 Vec4::operator*( Vec4 const& rhs ) const
{
    return Vec4( c0 * rhs.c0,
                 c1 * rhs.c1,
                 c2 * rhs.c2,
                 c3 * rhs.c3 );
}

Vec4 Vec4::operator/( Vec4 const& rhs ) const
{
    return Vec4( c0 / rhs.c0, c1 / rhs.c1, c2 / rhs.c2, c3 / rhs.c3 );
}

Vec4& Vec4::norm()
{
    float c0_lcl = this->c0;
    float c1_lcl = this->c1;
    float c2_lcl = this->c2;
    float c3_lcl = this->c3;

    float invMag = 1.0f / sqrt(   c0_lcl * c0_lcl
                                + c1_lcl * c1_lcl
                                + c2_lcl * c2_lcl
                                + c3_lcl * c3_lcl );

    this->c0 *= invMag;
    this->c1 *= invMag;
    this->c2 *= invMag;
    this->c3 *= invMag;

    return *this;
}

std::ostream& operator<<( std::ostream& out,
                          Vec4 const& rhs )
{
    out << "< " << rhs.c0 << ", " << rhs.c1 << ", " << rhs.c2 << ", " << rhs.c3 << " >";
    return out;
}

}
