#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <stdexcept>
#include <iostream>
#include "../gUtility/datatypeinfo.hpp"
#include "../gVideo/gl_core_3_3.hpp"

namespace gfx {
  
// Five basic graphics primitives
template< typename T > class scalar;
template< typename T > class vec2;
template< typename T > class vec3;
template< typename T > class vec4;
class Qutn;

// Component swizzles
class swizz4;
class swizz3;
class swizz2;
class swizz1;

// An ABC that graphics primitives use to dela with mapping
// to OpenGL or any other memory.
class raw_mappable;

// A container class used to pass byte arrays of data around
class raw_map {
public:
                            raw_map( raw_map const& src );
                            raw_map( size_t new_n_bytes );
                            ~raw_map();
    size_t const            n_bytes;
    unsigned char&          operator[]( int const index );
    unsigned char           operator[]( int const index ) const;
protected:
    friend class            raw_mappable;
    unsigned char* bytes;
};

inline raw_map::raw_map( raw_map const& src ) :
                    n_bytes( src.n_bytes ),
                    bytes( new unsigned char[ src.n_bytes ] )
{
    size_t i;
    for( i = 0; i < n_bytes; ++i )
    { bytes[i] = src.bytes[i]; }
}

inline  raw_map::raw_map( size_t new_n_bytes ) :
            n_bytes( new_n_bytes ),
            bytes( new unsigned char[new_n_bytes] ) {}

inline  raw_map::~raw_map() { delete[] bytes; }

inline unsigned char&   raw_map::operator[]( int const index )
{
    if ( index < 0 ) {
            throw std::out_of_range( "access index of raw_map negative" );
        }
    size_t index_pos = index;
    if ( index_pos >= n_bytes ) {
        throw std::out_of_range( "access index of raw_map too large" );
    }
    return bytes[index];
}

inline unsigned char    raw_map::operator[]( int const index ) const
{
    if ( index < 0 ) {
        throw std::out_of_range( "access index of raw_map negative" );
    }
    size_t index_pos = index;
    if ( index_pos >= n_bytes ) {
        throw std::out_of_range( "access index of raw_map too large" );
    }
    return bytes[index];
}

// An ABC that graphics primitives use to dela with mapping
// to OpenGL or any other memory.
class raw_mappable {
public:
                    raw_mappable()                  {}
    virtual         ~raw_mappable()                 {}
    virtual         raw_map const to_map() const    = 0;
protected:
    // Implementers have a public version of raw_map().
    // This is intentional: this raw_map() is an internal
    // utility function used for cloning bytes.
    raw_map const   map_bytes( size_t n_bytes, unsigned char const* bytes ) const;
};

inline raw_map const    raw_mappable::map_bytes( size_t n_bytes, unsigned char const* bytes ) const
{
    raw_map raw( n_bytes );
    size_t i;
    for( i = 0; i < n_bytes; ++i ) {
        raw.bytes[i] = bytes[i];
    }
    return raw;
}


template< typename T >
class scalar : public raw_mappable {
public:
    typedef T               comp_type;
                            scalar();
                            scalar( comp_type x0 );
                            operator T() const;
                            operator T&();
    scalar                  operator+( scalar const& rhs ) const;
    scalar                  operator-( scalar const& rhs ) const;
    scalar                  operator*( scalar const& rhs ) const;
    scalar                  operator/( scalar const& rhs ) const;
    scalar                  operator+( T const& rhs ) const;
    scalar                  operator-( T const& rhs ) const;
    scalar                  operator*( T const& rhs ) const;
    scalar                  operator/( T const& rhs ) const;
    template< typename U>
    friend std::ostream&    operator<<( std::ostream& out, scalar<U> const& src );
    virtual raw_map const   to_map() const;
protected:
  // A union is used to access the value in full or the bytes individually.
    union {
        comp_type       value;
        unsigned char   bytes[sizeof(comp_type)];
    } data;
};

template< typename T > inline   scalar<T>::operator T() const   { return data.value; }
template< typename T > inline   scalar<T>::operator T&()        { return data.value; }

// This macro is defined in datatypeinfo.hpp; it expands to a template
// specialization of the typeinfo class with a further template param.
// Type information for library classes is only generated when code uses
// the functionality.
template< typename T >
G_TYPE( scalar<T>, type<T>().n_components(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename U > inline
std::ostream&   operator<<( std::ostream& out, scalar<U> const& src )
{
    out << '<' << src.data.value << '>';
    return out;
}

template< typename T > inline
raw_map const   scalar<T>::to_map() const
{
    return map_bytes( sizeof(T), data.bytes );
}

template< typename T >
class vec2 : public raw_mappable {
public:
    typedef T               comp_type;
                            vec2();
                            vec2( comp_type x0,
                                  comp_type x1 );
                            vec2( comp_type fill );
                            vec2( vec2<comp_type> const& src );
                            ~vec2();
    bool                    operator==( vec2<T> const& rhs );
    vec2<T>&                operator=( vec2<T> const& rhs );
    T&                      operator()( swizz2 const& x0 );
    T                       operator()( swizz2 const& x0 ) const;
    vec2<T>                 operator()( swizz2 const& x0,
                                        swizz2 const& x1 ) const;
    vec3<T>                 operator()( swizz2 const& x0,
                                        swizz2 const& x1,
                                        swizz2 const& x2 ) const;
    vec4<T>                 operator()( swizz2 const& x0,
                                        swizz2 const& x1,
                                        swizz2 const& x2,
                                        swizz2 const& x3 ) const;
    vec2<T>                 operator+( vec2<T> const& rhs ) const;
    vec2<T>                 operator-( vec2<T> const& rhs ) const;
    vec2<T>                 operator*( vec2<T> const& rhs ) const;
    vec2<T>                 operator/( vec2<T> const& rhs ) const;
    template< typename U >
    friend std::ostream&    operator<<( std::ostream& out, vec2<U> const& src );
    virtual raw_map const   to_map() const;
protected:
    union {
        comp_type       components[2];
        unsigned char   bytes[sizeof(T) * 2];
    } data;
};

template<typename T> inline
bool    vec2<T>::operator==( vec2<T> const& rhs )
{
    return data.components[0] == rhs.data.components[0] && data.components[1] == rhs.data.components[1];
}

template< typename U > inline
std::ostream&   operator<<( std::ostream& out, vec2<U> const& src )
{
    out << '<' << src.data.components[0];
    out << ',' << src.data.components[1] << '>';
    return out;
}

template< typename T > inline
raw_map const   vec2<T>::to_map()   const
{
    return map_bytes( sizeof(T) * 2, data.bytes );
}

template< typename T >
G_TYPE( vec2<T>, 2 * type<T>().n_components(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class vec3 : public raw_mappable  {
public:
    typedef T               comp_type;
                            vec3();
                            vec3( comp_type x0,
                                  comp_type x1,
                                  comp_type x2 );
                            vec3( comp_type fill );
                            vec3( vec3<comp_type> const& src );
                            ~vec3();
    bool                    operator==( vec3 const& rhs );
    vec3<T>&                operator=( vec3<T> const& rhs );
    T&                      operator()( swizz3 const& x0 );
    T                       operator()( swizz3 const& x0 ) const;
    vec2<T>                 operator()( swizz3 const& x0,
                                        swizz3 const& x1 ) const;
    vec3                    operator()( swizz3 const& x0,
                                        swizz3 const& x1,
                                        swizz3 const& x2 ) const;
    vec4<T>                 operator()( swizz3 const& x0,
                                        swizz3 const& x1,
                                        swizz3 const& x2,
                                        swizz3 const& x3 ) const;
    vec3                    operator+( vec3 const& rhs ) const;
    vec3                    operator-( vec3 const& rhs ) const;
    vec3                    operator*( vec3 const& rhs ) const;
    vec3                    operator/( vec3 const& rhs ) const;

    template< typename U >
    friend std::ostream&    operator<<( std::ostream& out, vec3<U> const& src );
    virtual raw_map const   to_map() const;
protected:
    union {
        comp_type       components[3];
        unsigned char   bytes[sizeof(T) * 3];
    } data;

};

template<typename T> inline
bool    vec3<T>::operator==( vec3<T> const& rhs )
{
    return data.components[0] == rhs.data.components[0] &&
           data.components[1] == rhs.data.components[1] &&
           data.components[2] == rhs.data.components[2];
}

template< typename U > inline
std::ostream&   operator<<( std::ostream& out, vec3<U> const& src )
{
    out << '<' << src.data.components[0];
    out << ',' << src.data.components[1];
    out << ',' << src.data.components[2] << '>';
    return out;
}

template< typename T > inline
raw_map const   vec3<T>::to_map()   const
{
    return map_bytes( sizeof(T) * 3, data.bytes );
}

template< typename T >
G_TYPE( vec3<T>, 3 * type<T>().n_components(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class vec4 : public raw_mappable  {
public:
    typedef T               comp_type;
                            vec4();
                            vec4( comp_type x0,
                                  comp_type x1,
                                  comp_type x2,
                                  comp_type x3 );
                            vec4( comp_type fill );
                            vec4( vec4<comp_type> const& src );
                            ~vec4();
    bool                    operator==( vec4 const& rhs );
    vec4<T>&                operator=( vec4<T> const& rhs );
    T&                      operator()( swizz4 const& x0 );
    T                       operator()( swizz4 const& x0 ) const;
    vec2<T>                 operator()( swizz4 const& x0,
                                        swizz4 const& x1 ) const;
    vec3<T>                 operator()( swizz4 const& x0,
                                        swizz4 const& x1,
                                        swizz4 const& x2 ) const;
    vec4                    operator()( swizz4 const& x0,
                                        swizz4 const& x1,
                                        swizz4 const& x2,
                                        swizz4 const& x3 ) const;
    vec4                    operator+( vec4 const& rhs ) const;
    vec4                    operator-( vec4 const& rhs ) const;
    vec4                    operator*( vec4 const& rhs ) const;
    vec4                    operator/( vec4 const& rhs ) const;
    template< typename U >
    friend std::ostream&    operator<<( std::ostream& out, vec4<U> const& src );
    virtual raw_map const   to_map() const;
protected:
    union {
        comp_type       components[4];
        unsigned char   bytes[sizeof(T) * 4];
    } data;
};

template< typename T > inline
bool    vec4<T>::operator==( vec4<T> const& rhs )
{
    return data.components[0] == rhs.data.components[0] &&
           data.components[1] == rhs.data.components[1] &&
           data.components[2] == rhs.data.components[2] &&
           data.components[3] == rhs.data.components[3];
}

template< typename U > inline
std::ostream&   operator<<( std::ostream& out, vec4<U> const& src )
{
    out << '<' << src.data.components[0];
    out << ',' << src.data.components[1];
    out << ',' << src.data.components[2];
    out << ',' << src.data.components[3] << '>';
    return out;
}

template< typename T > inline
raw_map const   vec4<T>::to_map()   const
{
    return map_bytes( sizeof(T) * 4, data.bytes );
}

template< typename T >
G_TYPE( vec4<T>, 4 * type<T>().n_components(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

// Here we instantiate all the datatypes that GLSL supports
// and provide typedef names.

typedef     vec4<float>             fvec4;
typedef     vec3<float>             fvec3;
typedef     vec2<float>             fvec2;
typedef     scalar<float>           float32;

typedef     vec4<double>            dvec4;
typedef     vec3<double>            dvec3;
typedef     vec2<double>            dvec2;
typedef     scalar<double>          double64;

typedef     vec4<int>               ivec4;
typedef     vec3<int>               ivec3;
typedef     vec2<int>               ivec2;
typedef     scalar<int>             int32;

typedef     vec4<short>             svec4;
typedef     vec3<short>             svec3;
typedef     vec2<short>             svec2;
typedef     scalar<short>           short16;

typedef     vec4<char>              cvec4;
typedef     vec3<char>              cvec3;
typedef     vec2<char>              cvec2;
typedef     scalar<char>            char8;

typedef     vec4<unsigned int>      uvec4;
typedef     vec3<unsigned int>      uvec3;
typedef     vec2<unsigned int>      uvec2;
typedef     scalar<unsigned int>    uint32;

typedef     vec4<unsigned short>    usvec4;
typedef     vec3<unsigned short>    usvec3;
typedef     vec2<unsigned short>    usvec2;
typedef     scalar<unsigned short>  ushort16;

typedef     vec4<unsigned char>     ucvec4;
typedef     vec3<unsigned char>     ucvec3;
typedef     vec2<unsigned char>     ucvec2;
typedef     scalar<unsigned char>   uchar8;

class swizz4 {
    public:
                                    swizz4() : index(0) {};
        swizz4                      operator-() const {return swizz4(-index);}
        template< class U > friend  class vec2;
        template< class U > friend  class vec3;
        template< class U > friend  class vec4;
        static swizz4               make_w() { return swizz4(4); }
        static swizz4               make_q() { return swizz4(4); }
        static swizz4               make_a() { return swizz4(4); }
        static swizz4               make_m() { return swizz4(4); }
        friend class Qutn;
    protected:
                                    swizz4( int index ) : index(index){};
        int                         index;
};

class swizz3 : public swizz4 {
    public:
                                    swizz3() {};
        swizz3                      operator-() const {return swizz3(-index);}
        template< class U > friend  class vec2;
        template< class U > friend  class vec3;
        template< class U > friend  class vec4;
        static swizz3               make_z() { return swizz3(3); }
        static swizz3               make_p() { return swizz3(3); }
        static swizz3               make_b() { return swizz3(3); }
        static swizz3               make_k() { return swizz3(3); }
        friend class Qutn;
    protected:
                                    swizz3( int index ) : swizz4( index ) {};
};

class swizz2 : public swizz3 {
    public:
                                    swizz2() {};
        swizz2                      operator-() const {return swizz2(-index);}
        template< class U > friend  class vec2;
        template< class U > friend  class vec3;
        template< class U > friend  class vec4;
        static swizz2               make_y() { return swizz2(2); }
        static swizz2               make_t() { return swizz2(2); }
        static swizz2               make_g() { return swizz2(2); }
        static swizz2               make_j() { return swizz2(2); }
        friend class Qutn;
    protected:
                                    swizz2( int index ) : swizz3( index ) {};
};

class swizz1 : public swizz2 {
    public:
                                    swizz1() {};
        swizz1                      operator-() const {return swizz1(-index);}
        template< class U > friend  class scalar;
        template< class U > friend  class vec2;
        template< class U > friend  class vec3;
        template< class U > friend  class vec4;
        static swizz1               make_x() { return swizz1(1); }
        static swizz1               make_s() { return swizz1(1); }
        static swizz1               make_r() { return swizz1(1); }
        static swizz1               make_i() { return swizz1(1); }
        friend class Qutn;
    protected:
                                    swizz1( int index ) : swizz2( index ) {};
};
// Test

// Classical Components
swizz1 const x = swizz1::make_x();
swizz2 const y = swizz2::make_y();
swizz3 const z = swizz3::make_z();
swizz4 const w = swizz4::make_w();
// Texture Coordinates
swizz1 const s = swizz1::make_s();
swizz2 const t = swizz2::make_t();
swizz3 const p = swizz3::make_p();
swizz4 const q = swizz4::make_q();
// Color Coordinates
swizz1 const r = swizz1::make_r();
swizz2 const g = swizz2::make_g();
swizz3 const b = swizz3::make_b();
swizz4 const a = swizz4::make_a();
// Hamiltonian Coordinates
swizz1 const i = swizz1::make_i();
swizz2 const j = swizz2::make_j();
swizz3 const k = swizz3::make_k();
swizz4 const m = swizz4::make_m();

template< typename T > inline
scalar<T>::scalar() : data( {0} ) {}

template< typename T > inline
scalar<T>::scalar( comp_type x0) : data( {x0} ) {}

template< typename T > inline
scalar<T> scalar<T>::operator+( scalar const& rhs ) const
{ return scalar<T>( data.value + rhs.data.value ); }

template< typename T > inline
scalar<T> scalar<T>::operator-( scalar const& rhs ) const
{ return scalar<T>( data.value - rhs.data.value ); }

template< typename T > inline
scalar<T> scalar<T>::operator*( scalar const& rhs ) const
{ return scalar<T>( data.value * rhs.data.value ); }

template< typename T > inline
scalar<T> scalar<T>::operator/( scalar const& rhs ) const
{ return scalar<T>( data.value / rhs.data.value ); }

template< typename T > inline
scalar<T> scalar<T>::operator+( T const& rhs ) const
{ return scalar<T>( data.value + rhs ); }

template< typename T > inline
scalar<T> scalar<T>::operator-( T const& rhs ) const
{ return scalar<T>( data.value - rhs ); }

template< typename T > inline
scalar<T> scalar<T>::operator*( T const& rhs ) const
{ return scalar<T>( data.value * rhs ); }

template< typename T > inline
scalar<T> scalar<T>::operator/( T const& rhs ) const
{ return scalar<T>( data.value / rhs ); }

template< typename T > inline
vec2<T>::vec2() : data( {{0,0}} ) {};

template< typename T >
inline vec2<T>::vec2( comp_type x0,
                      comp_type x1 ) : data( {{ x0, x1 }} ) {}

template< typename T >
inline vec2<T>::vec2( comp_type fill ) : data( {{fill, fill}} ){}

template< typename T >
inline vec2<T>::vec2( vec2<T> const& src ) : data( {{ src.data.components[0], src.data.components[1] }} ) {}

template< typename T >
inline vec2<T>::~vec2() {}

template< typename T >
inline vec2<T>& vec2<T>::operator=( vec2<T> const& rhs )
{
    this->data.components[0] = rhs.data.components[0];
    this->data.components[1] = rhs.data.components[1];
    return *this;
}

template< typename T >
inline T& vec2<T>::operator()( swizz2 const& x0 )
{
    switch( x0.index ){
      case 1:
          return data.components[0];
      case 2:
          return data.components[1];
      case -1:
      case -2:
          throw std::invalid_argument("Cannot modify components of a vec2 with a negative index.");
      default:
          throw std::out_of_range("Component index on vec2 out of range.");
    }
}

template< typename T >
inline T vec2<T>::operator()( swizz2 const& x0 ) const
{
    switch( x0.index ){
      case 1:
          return data.components[0];
      case 2:
          return data.components[1];
      case -1:
          return -data.components[0];
      case -2:
          return -data.components[1];
      default:
          throw std::out_of_range("Component index on vec2 out of range.");
    }
}

template< typename T >
inline vec2<T> vec2<T>::operator()( swizz2 const& x0,
                                    swizz2 const& x1 ) const
{
    return vec2( (*this)(x0), (*this)(x1) );
}

template< typename T >
inline vec3<T> vec2<T>::operator()( swizz2 const& x0,
                                    swizz2 const& x1,
                                    swizz2 const& x2 ) const
{
    return vec3<T>( (*this)(x0), (*this)(x1), (*this)(x2) );
}

template< typename T >
inline vec4<T> vec2<T>::operator()( swizz2 const& x0,
                                    swizz2 const& x1,
                                    swizz2 const& x2,
                                    swizz2 const& x3 ) const
{
    return vec4<T>( (*this)(x0), (*this)(x1), (*this)(x2), (*this)(x3) );
}

template< typename T >
inline vec2<T> vec2<T>::operator+( vec2<T> const& rhs ) const
{
    return vec2<T>( (*this)(x) + rhs(x), (*this)(y) + rhs(y) );
}

template< typename T >
inline vec2<T> vec2<T>::operator-( vec2<T> const& rhs ) const
{
    return vec2<T>( (*this)(x) - rhs(x), (*this)(y) - rhs(y) );
}

template< typename T >
inline vec2<T> vec2<T>::operator*( vec2<T> const& rhs ) const
{
    return vec2<T>( (*this)(x) * rhs(x), (*this)(y) * rhs(y) );
}

template< typename T >
inline vec2<T> vec2<T>::operator/( vec2<T> const& rhs ) const
{
    return vec2<T>( (*this)(x) / rhs(x), (*this)(y) / rhs(y) );
}

/* We specialize for numeric types; other types are allowed to default
 * to whatever they default to. */

template< typename T > inline
vec3<T>::vec3() : data( {{0,0,0}} ) {};

template< typename T > inline
vec3<T>::vec3( comp_type x0,
               comp_type x1,
               comp_type x2 ) : data( {{ x0, x1, x2 }} ) {}

template< typename T > inline
vec3<T>::vec3( comp_type fill ) : data( {{fill, fill, fill}} ) {}

template< typename T > inline
vec3<T>::vec3( vec3<T> const& src ) : data( {{ src.data.components[0],
                                               src.data.components[1],
                                               src.data.components[2] }} ) {}

template< typename T > inline vec3<T>::~vec3() {}

template< typename T > inline
vec3<T>&    vec3<T>::operator=( vec3<T> const& rhs )
{
    (*this)(x) = rhs(x);
    (*this)(y) = rhs(y);
    (*this)(z) = rhs(z);
    return *this;
}

template< typename T > inline
T&  vec3<T>::operator()( swizz3 const& x0 )
{
    switch( x0.index ){
      case 1:
          return data.components[0];
      case 2:
          return data.components[1];
      case 3:
          return data.components[2];
      case -1:
      case -2:
      case -3:
          throw std::invalid_argument("Cannot modify components of a vec3 with a negative index.");
      default:
          throw std::out_of_range("Component index on vec3 out of range.");
    }
}

template< typename T >
inline T vec3<T>::operator()( swizz3 const& x0 ) const
{
    switch( x0.index ){
      case 1:
          return data.components[0];
      case 2:
          return data.components[1];
      case 3:
          return data.components[2];
      case -1:
          return -data.components[0];
      case -2:
          return -data.components[1];
      case -3:
          return -data.components[2];
      default:
          throw std::out_of_range("Component index on vec3 out of range.");
    }
}

template< typename T >
inline vec2<T> vec3<T>::operator()( swizz3 const& x0,
                                    swizz3 const& x1 ) const
{
    return vec2<T>( (*this)(x0), (*this)(x1) );
}
template< typename T >
inline vec3<T> vec3<T>::operator()( swizz3 const& x0,
                                    swizz3 const& x1,
                                    swizz3 const& x2 ) const
{
    return vec3( (*this)(x0), (*this)(x1), (*this)(x2) );
}
template< typename T >
inline vec4<T> vec3<T>::operator()( swizz3 const& x0,
                                    swizz3 const& x1,
                                    swizz3 const& x2,
                                    swizz3 const& x3 ) const
{
    return vec4<T>( (*this)(x0), (*this)(x1), (*this)(x2), (*this)(x3) );
}

template< typename T >
inline vec3<T> vec3<T>::operator+( vec3<T> const& rhs ) const
{
    return vec3<T>( (*this)(x) + rhs(x),
                    (*this)(y) + rhs(y),
                    (*this)(z) + rhs(z) );
}

template< typename T >
inline vec3<T> vec3<T>::operator-( vec3<T> const& rhs ) const
{
    return vec3<T>( (*this)(x) - rhs(x),
                    (*this)(y) - rhs(y),
                    (*this)(z) - rhs(z) );
}
template< typename T >
inline vec3<T> vec3<T>::operator*( vec3<T> const& rhs ) const
{
    return vec3<T>( (*this)(x) * rhs(x),
                    (*this)(y) * rhs(y),
                    (*this)(z) * rhs(z) );
}
template< typename T >
inline vec3<T> vec3<T>::operator/( vec3<T> const& rhs ) const
{
    return vec3<T>( (*this)(x) / rhs(x),
                    (*this)(y) / rhs(y),
                    (*this)(z) / rhs(z) );
}

template< typename T >
inline vec4<T>::vec4() : data( {{ 0,0,0,0 }} ) {};

template< typename T > inline
vec4<T>::vec4( comp_type x0,
               comp_type x1,
               comp_type x2,
               comp_type x3 ) : data( {{ x0, x1, x2, x3 }} ) {}

template< typename T > inline
vec4<T>::vec4( comp_type fill ) : data( {{ fill, fill, fill, fill }} ) {}

template< typename T > inline
vec4<T>::vec4( vec4<T> const& src ) :
            data( {{ src.data.components[0],
                    src.data.components[1],
                    src.data.components[2],
                    src.data.components[3] }} ) {}

template< typename T > inline vec4<T>::~vec4() {}

template< typename T > inline
vec4<T>& vec4<T>::operator=( vec4<T> const& rhs )
{
    (*this)(x) = rhs(x);
    (*this)(y) = rhs(y);
    (*this)(z) = rhs(z);
    (*this)(w) = rhs(w);
    return *this;
}

template< typename T >
inline T& vec4<T>::operator()( swizz4 const& x0 )
{
    switch( x0.index ){
      case 1:
          return data.components[0];
      case 2:
          return data.components[1];
      case 3:
          return data.components[2];
      case 4:
          return data.components[3];
      case -1:
      case -2:
      case -3:
      case -4:
          throw std::invalid_argument("Cannot modify components of a vec4 with a negative index.");
      default:
          throw std::out_of_range("Component index on vec4 out of range.");
    }
}

template< typename T >
inline T vec4<T>::operator()( swizz4 const& x0 ) const
{
    switch( x0.index ){
      case 1:
          return data.components[0];
      case 2:
          return data.components[1];
      case 3:
          return data.components[2];
      case 4:
          return data.components[3];
      case -1:
          return -data.components[0];
      case -2:
          return -data.components[1];
      case -3:
          return -data.components[2];
      case -4:
          return -data.components[3];
      default:
          throw std::out_of_range("Component index on vec4 out of range.");
    }
}

template< typename T >
inline vec2<T> vec4<T>::operator()( swizz4 const& x0,
                                    swizz4 const& x1 ) const
{
    return vec2<T>( (*this)(x0), (*this)(x1) );
}
template< typename T >
inline vec3<T> vec4<T>::operator()( swizz4 const& x0,
                                    swizz4 const& x1,
                                    swizz4 const& x2 ) const
{
    return vec3<T>( (*this)(x0), (*this)(x1), (*this)(x2) );
}
template< typename T >
inline vec4<T> vec4<T>::operator()( swizz4 const& x0,
                                    swizz4 const& x1,
                                    swizz4 const& x2,
                                    swizz4 const& x3 ) const
{
    return vec4<T>( (*this)(x0), (*this)(x1), (*this)(x2), (*this)(x3) );
}

template< typename T >
inline vec4<T> vec4<T>::operator+( vec4<T> const& rhs ) const
{
    return vec4<T>( (*this)(x) + rhs(x),
                    (*this)(y) + rhs(y),
                    (*this)(z) + rhs(z),
                    (*this)(w) + rhs(w) );
}

template< typename T >
inline vec4<T> vec4<T>::operator-( vec4<T> const& rhs ) const
{
    return vec4<T>( (*this)(x) - rhs(x),
                    (*this)(y) - rhs(y),
                    (*this)(z) - rhs(z),
                    (*this)(w) - rhs(w) );
}

template< typename T >
inline vec4<T> vec4<T>::operator*( vec4<T> const& rhs ) const
{
    return vec4<T>( (*this)(x) * rhs(x),
                    (*this)(y) * rhs(y),
                    (*this)(z) * rhs(z),
                    (*this)(w) * rhs(w) );
}

template< typename T >
inline vec4<T> vec4<T>::operator/( vec4<T> const& rhs ) const
{
    return vec4<T>( (*this)(x) / rhs(x),
                    (*this)(y) / rhs(y),
                    (*this)(z) / rhs(z),
                    (*this)(w) / rhs(w) );
}

}

#endif
