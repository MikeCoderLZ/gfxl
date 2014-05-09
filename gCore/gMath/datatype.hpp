#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <stdexcept>
#include <iostream>
#include <cmath>
#include <climits>
#include "../gUtility/datatypeinfo.hpp"
#include "../gVideo/gl_core_3_3.hpp"

namespace gfx {
  
// Five basic graphics primitives
template< typename T > class scalar;
template< typename T > class vec2;
template< typename T > class vec3;
template< typename T > class vec4;
class Qutn;

// Basic matrix primitive
template< typename T > class mat;
template< typename T > class mat2;
template< typename T > class mat3;
template< typename T > class mat4;
template< typename T > class mat2x3;
template< typename T > class mat2x4;
template< typename T > class mat3x2;
template< typename T > class mat3x4;
template< typename T > class mat4x2;
template< typename T > class mat4x3;

// Component swizzles
class swizz4;
class swizz3;
class swizz2;
class swizz1;

// This little gizmo is a metaprogramming thing to make sure
// templates use the correctly typed values for common
// literals. I'm a paranoid programmer, and since the default
// type for floating point is double and the compiler is supposed
// to enforce that, we can lose some efficiency.
//
// Besides, you can never be too sure with matrices and graphics.

template< typename T >
class lit {
public:
    constexpr static T const    zero = 0;
    constexpr static T const   one = 1;
    constexpr static T const   neg_one = -1;
};

template<>
class lit<float> {
public:
    constexpr static float const   zero = 0.0f;
    constexpr static float const   one = 1.0f;
    constexpr static float const   neg_one = -1.0f;
};

template<>
class lit<double> {
public:
    constexpr static float const   zero = 0.0;
    constexpr static float const   one = 1.0;
    constexpr static float const   neg_one = -1.0;
};

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
    typedef T               comp_t;
                            scalar();
                            scalar( comp_t x0 );
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
        comp_t       value;
        unsigned char   bytes[sizeof(comp_t)];
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
    typedef T               comp_t;
                            vec2();
                            vec2( comp_t x0,
                                  comp_t x1 );
                            vec2( comp_t fill );
                            vec2( vec2<comp_t> const& src );
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
        comp_t       components[2];
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
    typedef T               comp_t;
                            vec3();
                            vec3( comp_t x0,
                                  comp_t x1,
                                  comp_t x2 );
                            vec3( comp_t fill );
                            vec3( vec3<comp_t> const& src );
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
        comp_t       components[3];
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
    typedef T               comp_t;
                            vec4();
                            vec4( comp_t x0,
                                  comp_t x1,
                                  comp_t x2,
                                  comp_t x3 );
                            vec4( comp_t fill );
                            vec4( vec4<comp_t> const& src );
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
        comp_t       components[4];
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

template< typename T >
class mat : public raw_mappable {
public:
    typedef mat<T>          mat_t;
    typedef T               comp_t;
    size_t                  n_cols;
    size_t                  n_rows;
    size_t                  n_comp;
    
                            mat( size_t new_n_cols,
                                 size_t new_n_rows );
    static mat_t            fill( size_t new_n_cols,
                                  size_t new_n_rows,
                                  comp_t const val );
    static mat_t            identity( size_t new_dim );
    virtual                 ~mat();
    bool                    operator==( mat_t const& rhs ) const;
    mat_t&                  operator=( mat_t const& rhs );
    comp_t&                 operator()( size_t col, size_t row );
    comp_t                  operator()( size_t col, size_t row ) const;
    mat_t                   operator+( mat_t const& rhs ) const;
    mat_t                   operator-( mat_t const& rhs ) const;
    mat_t                   operator*( mat_t const& rhs ) const;
    mat_t                   operator*( comp_t rhs );
    template< typename D >
    friend mat<D>           operator*( D lhs, mat<D> const& rhs );
    mat_t                   operator/( comp_t rhs );
    mat_t&                  fill( comp_t const val );
    mat_t&                  transpose();
    virtual raw_map const   to_map() const;
protected:
    class mat_data {
    public:
        mat_t*                  owner;
        comp_t*                 components;
                                mat_data( mat_t* new_owner );
                                ~mat_data();
        mat_data*               clone();
        size_t                  n_bytes();
        unsigned char const*    bytes();
    };
    mat_data* data;
};

template< typename T >
class mat2 {
public:
    typedef mat2<T>                 mat2_t;
    typedef T                       comp_t;
    constexpr static size_t const   n_cols = 2;
    constexpr static size_t const   n_rows = 2;
    constexpr static size_t const   n_comp = 4;
    
                        mat2();                        
                        mat2( comp_t e00, comp_t e10,
                              comp_t e01, comp_t e11 );
    static mat2_t       identity();
    static mat2_t       row_vectors( vec2<comp_t> const& row0,
                                     vec2<comp_t> const& row1 );
    static mat2_t       column_vectors( vec2<comp_t> const& col0,
                                        vec2<comp_t> const& col1 );
    static mat2_t       scale( comp_t sx,
                               comp_t sy );
    static mat2_t       scale( vec2<comp_t> const& svec );
    bool                operator==( mat2_t const& rhs ) const;
    bool                operator<( mat2_t const& rhs ) const;
    bool                operator>( mat2_t const& rhs ) const;
    bool                operator<=( mat2_t const& rhs ) const;
    bool                operator>=( mat2_t const& rhs ) const;
    bool                operator!=( mat2_t const& rhs ) const;
    mat2_t&             operator=( mat2_t const& rhs );
    comp_t&             operator()( size_t col,
                                    size_t row );
    comp_t              operator()( size_t col,
                                    size_t row ) const;
    mat2_t              operator+( mat2_t const& rhs );
    mat2_t              operator-();
    mat2_t              operator-( mat2_t const& rhs );
    mat2_t              operator*( mat2_t const& rhs );
    mat2_t              operator*( comp_t rhs );
    template< typename D >
    friend mat2<D>      operator*( D lhs, mat2<D> const& rhs );
    mat2_t              operator/( comp_t rhs );
    mat2_t&             fill( comp_t val );
    mat2_t&             transpose();
    mat2_t&             row( size_t const& row,
                             vec2<comp_t> const& val );
    vec2<T>             row( size_t const& row ) const;
    mat2_t&             column( size_t const& col,
                                vec2<comp_t> const& val );
    vec2<T>             column( size_t const& col ) const;
    mat2_t&             rows( vec2<comp_t> const& row0,
                              vec2<comp_t> const& row1 );
    mat2_t&             columns( vec2<comp_t> const& col0,
                                 vec2<comp_t> const& col1 );
protected:
    union {
        comp_t          components[4];
        unsigned char   bytes[sizeof(comp_t) * 4];
    } data;
};

template< typename T >
class mat3 {
public:
    typedef mat3<T>                 mat3_t;
    typedef T                       comp_t;
    constexpr static size_t const   n_cols = 3;
    constexpr static size_t const   n_rows = 3;
    constexpr static size_t const   n_comp = 9;
    
                        mat3();                        
                        mat3( comp_t e00, comp_t e10, comp_t e20,
                              comp_t e01, comp_t e11, comp_t e21,
                              comp_t e02, comp_t e12, comp_t e22 );
    static mat3_t       identity();
    static mat3_t       row_vectors( vec3<comp_t> const& row0,
                                     vec3<comp_t> const& row1,
                                     vec3<comp_t> const& row2 );
    static mat3_t       column_vectors( vec3<comp_t> const& col0,
                                        vec3<comp_t> const& col1,
                                        vec3<comp_t> const& col2 );
    static mat3_t       scale( comp_t sx,
                               comp_t sy,
                               comp_t sz );
    static mat3_t       scale( vec3<comp_t> const& svec );
    bool                operator==( mat3_t const& rhs ) const;
    bool                operator<( mat3_t const& rhs ) const;
    bool                operator>( mat3_t const& rhs ) const;
    bool                operator<=( mat3_t const& rhs ) const;
    bool                operator>=( mat3_t const& rhs ) const;
    bool                operator!=( mat3_t const& rhs ) const;
    mat3_t&             operator=( mat3_t const& rhs );
    comp_t&             operator()( size_t col,
                                    size_t row );
    comp_t              operator()( size_t col,
                                    size_t row ) const;
    mat4_t              operator+( mat3_t const& rhs );
    mat4_t              operator-();
    mat4_t              operator-( mat3_t const& rhs );
    mat3_t              operator*( mat3_t const& rhs );
    mat3_t              operator*( comp_t rhs );
    template< typename D >
    friend mat3<D>      operator*( D lhs, mat3<D> const& rhs );
    mat3_t              operator/( comp_t rhs );
    mat3_t&             fill( comp_t val );
    mat3_t&             transpose();
    mat3_t&             row( size_t const& row,
                             vec3<comp_t> const& val );
    vec3<T>             row( size_t const& row ) const;
    mat3_t&             column( size_t const& col,
                                vec3<comp_t> const& val );
    vec3<T>             column( size_t const& col ) const;
    mat3_t&             rows( vec3<comp_t> const& row0,
                              vec3<comp_t> const& row1,
                              vec3<comp_t> const& row2 );
    mat3_t&             columns( vec3<comp_t> const& col0,
                                 vec3<comp_t> const& col1,
                                 vec3<comp_t> const& col2 );
protected:
    union {
        comp_t          components[9];
        unsigned char   bytes[sizeof(comp_t) * 9];
    } data;
};

template< typename T >
class mat4 {
public:
    typedef mat4<T>                 mat4_t;
    typedef T                       comp_t;
    constexpr static size_t const   n_cols = 4;
    constexpr static size_t const   n_rows = 4;
    constexpr static size_t const   n_comp = 16;
    
                        mat4();                        
                        mat4( comp_t e00, comp_t e10, comp_t e20, comp_t e30,
                              comp_t e01, comp_t e11, comp_t e21, comp_t e31,
                              comp_t e02, comp_t e12, comp_t e22, comp_t e32,
                              comp_t e03, comp_t e13, comp_t e23, comp_t e33 );
    static mat4_t       identity();
    static mat4_t       row_vectors( vec4<comp_t> const& row0,
                                     vec4<comp_t> const& row1,
                                     vec4<comp_t> const& row2,
                                     vec4<comp_t> const& row3 );
    static mat4_t       column_vectors( vec4<comp_t> const& col0,
                                        vec4<comp_t> const& col1,
                                        vec4<comp_t> const& col2,
                                        vec4<comp_t> const& col3 );
    static mat4_t       scale( comp_t sx,
                               comp_t sy,
                               comp_t sz,
                               comp_t sw );
    static mat4_t       scale( vec4<comp_t> const& svec );
    bool                operator==( mat4_t const& rhs ) const;
    bool                operator<( mat4_t const& rhs ) const;
    bool                operator>( mat4_t const& rhs ) const;
    bool                operator<=( mat4_t const& rhs ) const;
    bool                operator>=( mat4_t const& rhs ) const;
    bool                operator!=( mat4_t const& rhs ) const;
    mat4_t&             operator=( mat4_t const& rhs );
    comp_t&             operator()( size_t col,
                                    size_t row );
    comp_t              operator()( size_t col,
                                    size_t row ) const;
    mat4_t              operator+( mat4_t const& rhs );
    mat4_t              operator-();
    mat4_t              operator-( mat4_t const& rhs );
    mat4_t              operator*( mat4_t const& rhs );
    mat4_t              operator*( comp_t rhs );
    template< typename D >
    friend mat4<D>      operator*( D lhs, mat4<D> const& rhs );
    mat4_t              operator/( comp_t rhs );
    mat4_t&             fill( comp_t val );
    mat4_t&             transpose();
    mat4_t&             row( size_t const& row,
                             vec4<comp_t> const& val );
    vec4<T>             row( size_t const& row ) const;
    mat4_t&             column( size_t const& col,
                                vec4<comp_t> const& val );
    vec4<T>             column( size_t const& col ) const;
    mat4_t&             rows( vec4<comp_t> const& row0,
                              vec4<comp_t> const& row1,
                              vec4<comp_t> const& row2,
                              vec4<comp_t> const& row3 );
    mat4_t&             columns( vec4<comp_t> const& col0,
                                 vec4<comp_t> const& col1,
                                 vec4<comp_t> const& col2,
                                 vec4<comp_t> const& col3 );
protected:
    union {
        comp_t          components[16];
        unsigned char   bytes[sizeof(comp_t) * 16];
    } data;
};

/**
template< typename T >
class mat2x3 : public mat<T> {
public:
    typedef mat<T>      base_t;
    typedef mat2x3<T>   mat2x3_t;
    typedef T           comp_t;
    
                        mat2x3();                    
                        mat2x3( comp_t e00, comp_t e10,
                                comp_t e01, comp_t e11,
                                comp_t e02, comp_t e12 );
    static mat2x3_t     row_vectors( vec2<comp_t> const& row0,
                                     vec2<comp_t> const& row1,
                                     vec2<comp_t> const& row2 );
    static mat2x3_t     column_vectors( vec3<comp_t> const& col0,
                                        vec3<comp_t> const& col1 );
    comp_t&             operator()( swizz2 col,
                                    swizz3 row );
    comp_t              operator()( swizz2 col,
                                    swizz3 row ) const;
    //mat2x3_t            operator*( mat3x2_t const& lhs );
    //mat4x2_t          operator*( mat4x2_t const& lhs );
    //mat3x2_t          operator*( mat3x2_t const& lhs );
    mat2x3_t            operator*( T rhs );
    template< typename D >
    friend mat2x3<D>    operator*( D lhs, mat2x3<D> const& rhs );
    mat2x3_t&           row( swizz3 const& row,
                             vec2<comp_t> const& val );
    vec2<T>             row( swizz3 const& row ) const;
    mat2x3_t&           column( swizz2 const& col,
                                vec3<comp_t> const& val );
    vec3<T>             column( swizz2 const& col ) const;
    mat2x3_t&           rows( vec2<comp_t> const& row0,
                              vec2<comp_t> const& row1,
                              vec2<comp_t> const& row2 );
    mat2x3_t&           columns( vec3<comp_t> const& col0,
                                 vec3<comp_t> const& col1 );
};

template< typename T >
class mat2x4 : public mat<T> {
public:
    typedef mat<T>      base_t;
    typedef mat2x4<T>   mat2x4_t;
    typedef T           comp_t;
    
                        mat2x4();                    
                        mat2x4( comp_t e00, comp_t e10,
                                comp_t e01, comp_t e11,
                                comp_t e01, comp_t e12,
                                comp_t e03, comp_t e13 );
    static mat2x4_t     row_vectors( vec2<comp_t> const& row0,
                                     vec2<comp_t> const& row1,
                                     vec2<comp_t> const& row2,
                                     vec2<comp_t> const& row3 );
    static mat2x4_t     column_vectors( vec4<comp_t> const& col0,
                                        vec4<comp_t> const& col1 );
    comp_t&             operator()( swizz2 col,
                                    swizz4 row );
    comp_t              operator()( swizz2 col,
                                    swizz4 row ) const;
    //mat2x3_t          operator*( mat3x2_t const& rhs );
    //mat4x2_t          operator*( mat4x2_t const& rhs );
    mat2x4_t            operator*( T rhs );
    template< typename D >
    friend mat2x4<D>    operator*( D lhs, mat2x4<D> const& rhs );
    mat2x4_t&           row( swizz4 const& row,
                             vec2<comp_t> const& val );
    vec2<T>             row( swizz4 const& row ) const;
    mat2x4_t&           column( swizz2 const& col,
                                vec4<comp_t> const& val );
    vec4<T>             column( swizz2 const& col ) const;
    mat2x4_t&           rows( vec2<comp_t> const& row0,
                              vec2<comp_t> const& row1,
                              vec2<comp_t> const& row2,
                              vec2<comp_t> const& row3 );
    mat2x4_t&           columns( vec4<comp_t> const& col0,
                                 vec4<comp_t> const& col1 );
};

template< typename T >
class mat3 : public mat<T> {
public:
    typedef mat<T>      base_t;
    typedef mat3<T>     mat3_t;
    typedef T           comp_t;
    
                        mat3();
                        mat3( comp_t e00, comp_t e10, comp_t e20,
                              comp_t e01, comp_t e11, comp_t e21,
                              comp_t e02, comp_t e12, comp_t e22 );
    static mat3_t       row_vectors( vec3<comp_t> const& row0,
                                     vec3<comp_t> const& row1,
                                     vec3<comp_t> const& row2 );
    static mat3_t       column_vectors( vec3<comp_t> const& col0,
                                        vec3<comp_t> const& col1,
                                        vec3<comp_t> const& col2 );
    static mat3_t       scale( comp_t sx,
                               comp_t sy,
                               comp_t sz = lit<comp_t>.one );
    static mat3_t       scale( vec3<comp_t> const& svec );
    static mat3_t       scale( vec2<comp_t> const& svec );
    comp_t&             operator()( swizz3 col,
                                    swizz3 row );
    comp_t              operator()( swizz3 col,
                                    swizz3 row ) const;
    mat3_t              operator*( mat3_t const& rhs );
    //mat2x3_t          operator*( mat2x3_t const& rhs );
    //mat4x3_t          operator*( mat4x3_t const& rhs );
    template< typename D >
    friend mat3<D>      operator*( D lhs, mat3<D> const& rhs );
    template< typename D >
    friend mat3<D>      operator*( mat3<D> const& lhs, D rhs );
    mat3_t&             row( swizz3 const& row,
                             vec3<comp_t> const& val );
    vec3<T>             row( swizz3 const& row ) const;
    mat3_t&             column( swizz3 const& col,
                                vec3<comp_t> const& val );
    vec3<T>             column( swizz3 const& col ) const;
    mat3_t&             rows( vec3<comp_t> const& row0,
                              vec3<comp_t> const& row1,
                              vec3<comp_t> const& row2 );
    mat3_t&             columns( vec3<comp_t> const& col0,
                                 vec3<comp_t> const& col1,
                                 vec3<comp_t> const& col2 );
};

template< typename T >
class mat4 : public mat<T> {
public:
    typedef mat<T>      base_t;
    typedef mat4<T>     mat4_t;
    typedef T           comp_t;
    
                        mat4();
                        mat4( comp_t e00, comp_t e10, comp_t e20, comp_t e30,
                              comp_t e01, comp_t e11, comp_t e21, comp_t e31,
                              comp_t e02, comp_t e12, comp_t e22, comp_t e32,
                              comp_t e03, comp_t e13, comp_t e23, comp_t e33 );
    static mat4_t       row_vectors( vec4<comp_t> const& row0,
                                     vec4<comp_t> const& row1,
                                     vec4<comp_t> const& row2,
                                     vec4<comp_t> const& row3 );
    static mat4_t       column_vectors( vec4<comp_t> const& col0,
                                        vec4<comp_t> const& col1,
                                        vec4<comp_t> const& col2,
                                        vec4<comp_t> const& col3 );
    static mat4_t       scale( comp_t sx,
                               comp_t sy,
                               comp_t sz,
                               comp_t sw = lit<comp_t>.one );
    static mat4_t       scale( vec4<comp_t> const& svec );
    static mat4_t       scale( vec3<comp_t> const& svec );
    comp_t&             operator()( swizz4 col,
                                    swizz4 row );
    comp_t              operator()( swizz4 col,
                                    swizz4 row ) const;
    mat4_t              operator*( mat4_t const& rhs );
    //mat2x4_t          operator*( mat2x4_t const& rhs );
    //mat3x4_t          operator*( mat3x4_t const& rhs );
    template< typename D >
    friend mat4<D>      operator*( D lhs, mat4<D> const& rhs );
    template< typename D >
    friend mat4<D>      operator*( mat4<D> const& lhs, D rhs );
    mat4_t&             row( swizz4 const& row,
                             vec4<comp_t> const& val );
    vec4<T>             row( swizz4 const& row ) const;
    mat4_t&             column( swizz4 const& col,
                                vec4<comp_t> const& val );
    vec4<T>             column( swizz4 const& col ) const;
    mat4_t&             rows( vec4<comp_t> const& row0,
                              vec4<comp_t> const& row1,
                              vec4<comp_t> const& row2,
                              vec4<comp_t> const& row3 );
    mat4_t&             columns( vec4<comp_t> const& col0,
                                 vec4<comp_t> const& col1,
                                 vec4<comp_t> const& col2,
                                 vec4<comp_t> const& col3 );
};*/

/**class mat2x3 : public mat<2,3,float> {
public:
    typedef mat<2,3,float>  base_t;
    
                            mat2x3() : base_t() {};
                            mat2x3( float e00, float e10,
                                    float e01, float e11,
                                    float e02, float e12 );
    mat2x3&                 row( swizz3 const& row,
                                 fvec2 const& val );
    mat2x3&                 column( swizz2 const& row,
                                    fvec3 const& val );
    static mat2x3           rows( fvec2 const& row1,
                                  fvec2 const& row2,
                                  fvec2 const& row3 );
    static mat2x3           columns( fvec3 const& col1,
                                     fvec3 const& col2 );
    
    float&                  operator()( swizz2 col,
                                        swizz3 row );
    float                   operator()( swizz2 col,
                                        swizz3 row ) const;
};

class mat2x4 : public mat<2,4,float> {
public:
    typedef mat<2,4,float>  base_t;
    
                            mat2x4() : base_t() {};
                            mat2x4( float e00, float e10,
                                    float e01, float e11,
                                    float e02, float e12,
                                    float e03, float e13 );
    mat2x4&                 row( swizz4 const& row,
                                 fvec2 const& val );
    mat2x4&                 column( swizz2 const& row,
                                    fvec4 const& val );
    static mat2x4           rows( fvec2 const& row1,
                                  fvec2 const& row2,
                                  fvec2 const& row3,
                                  fvec2 const& row4 );
    static mat2x4           columns( fvec4 const& col1,
                                     fvec4 const& col2 );
    
    float&                  operator()( swizz2 col,
                                        swizz4 row );
    float                   operator()( swizz2 col,
                                        swizz4 row ) const;
};

class mat3 : public mat<3,3,float> {
public:
    typedef mat<3,3,float>  base_t;
    
                            mat3() : base_t() {};
                            mat3( float e00, float e10, float e20,
                                  float e01, float e11, float e21,
                                  float e02, float e12, float e22 );
    mat3&                   row( swizz3 const& row,
                                 fvec3 const& val );
    mat3&                   column( swizz3 const& col,
                                    fvec3 const& val );
    static mat3             rows( fvec3 const& row1,
                                  fvec3 const& row2,
                                  fvec3 const& row3 );
    static mat3             columns( fvec3 const& col1,
                                     fvec3 const& col2,
                                     fvec3 const& col3 );
    static mat3             translate( float tx,
                                       float ty );
    static mat3             translate( fvec2 const& tvec );
    static mat3             scale( float sx,
                                   float sy );
    static mat3             scale( fvec2 const& svec );
    static mat3             scale( float sx,
                                   float sy,
                                   float sz );
    static mat3             scale( fvec3 const& svec );
    
    float&                  operator()( swizz3 col,
                                        swizz3 row );
    float                   operator()( swizz3 col,
                                        swizz3 row ) const;
};

class mat3x2 : public mat<3,2,float> {
public:
    typedef mat<3,2,float>  base_t;
    
                            mat3x2() : base_t() {};
                            mat3x2( float e00, float e10, float e20,
                                    float e01, float e11, float e21 );
    mat3x2&                 row( swizz2 const& row,
                                 fvec3 const& val );
    mat3x2&                 column( swizz3 const& row,
                                    fvec2 const& val );
    static mat3x2           rows( fvec3 const& row1,
                                  fvec3 const& row2 );
    static mat3x2           columns( fvec2 const& col1,
                                     fvec2 const& col2,
                                     fvec2 const& col3 );
    
    float&                  operator()( swizz3 col,
                                        swizz2 row );
    float                   operator()( swizz3 col,
                                        swizz2 row ) const;
};

class mat3x4 : public mat<3,4,float> {
public:
    typedef mat<3,4,float>  base_t;
    
                            mat3x4() : base_t() {};
                            mat3x4( float e00, float e10, float e20,
                                    float e01, float e11, float e21,
                                    float e02, float e12, float e22,
                                    float e03, float e13, float e23 );
    mat3x4&                 row( swizz4 const& row,
                                 fvec3 const& val );
    mat3x4&                 column( swizz3 const& row,
                                    fvec4 const& val );
    static mat3x4           rows( fvec3 const& row1,
                                  fvec3 const& row2,
                                  fvec3 const& row3,
                                  fvec3 const& row4 );
    static mat3x4           columns( fvec4 const& col1,
                                     fvec4 const& col2,
                                     fvec4 const& col3 );
    
    float&                  operator()( swizz3 col,
                                        swizz4 row );
    float                   operator()( swizz3 col,
                                        swizz4 row ) const;
};

class mat4 : public mat<4,4,float> {
public:
    typedef mat<4,4,float>  base_t;
    
                            mat4() : base_t() {};
                            mat4( float e00, float e10, float e20, float e30,
                                  float e01, float e11, float e21, float e31,
                                  float e02, float e12, float e22, float e32,
                                  float e03, float e13, float e23, float e33 );
    mat4&                   row( swizz4 const& row,
                                 fvec4 const& val );
    mat4&                   column( swizz4 const& col,
                                    fvec4 const& val );
    static mat4             rows( fvec4 const& row1,
                                  fvec4 const& row2,
                                  fvec4 const& row3,
                                  fvec4 const& row4 );
    static mat4             columns( fvec4 const& col1,
                                     fvec4 const& col2,
                                     fvec4 const& col3,
                                     fvec4 const& col4 );
    static mat4             translate( float tx,
                                       float ty,
                                       float tz );
    static mat4             translate( fvec3 const& tvec );
    static mat4             scale( float sx,
                                   float sy,
                                   float sz );
    static mat4             scale( fvec3 const& svec );
    static mat4             scale( float sx,
                                   float sy,
                                   float sz,
                                   float sw );
    static mat4             scale( fvec4 const& svec );
    
    float&                  operator()( swizz4 col,
                                        swizz4 row );
    float                   operator()( swizz4 col,
                                        swizz4 row ) const;
};

class mat4x2 : public mat<4,2,float> {
public:
    typedef mat<4,2,float>  base_t;
    
                            mat4x2() : base_t() {};
                            mat4x2( float e00, float e10, float e20, float e30,
                                    float e01, float e11, float e21, float e31 );
    mat4x2&                 row( swizz2 const& row,
                                 fvec4 const& val );
    mat4x2&                 column( swizz4 const& row,
                                    fvec2 const& val );
    static mat4x2           rows( fvec4 const& row1,
                                  fvec4 const& row2 );
    static mat4x2           columns( fvec2 const& col1,
                                     fvec2 const& col2,
                                     fvec2 const& col3,
                                     fvec2 const& col4 );
    
    float&                  operator()( swizz4 col,
                                        swizz2 row );
    float                   operator()( swizz4 col,
                                        swizz2 row ) const;
};

class mat4x3 : public mat<4,3,float> {
public:
    typedef mat<4,3,float>  base_t;
    
                            mat4x3() : base_t() {};
                            mat4x3( float e00, float e10, float e20, float e30,
                                    float e01, float e11, float e21, float e31,
                                    float e02, float e12, float e22, float e32 );
    mat4x3&                 row( swizz3 const& row,
                                 fvec4 const& val );
    mat4x3&                 column( swizz4 const& row,
                                    fvec3 const& val );
    static mat4x3           rows( fvec4 const& row1,
                                  fvec4 const& row2,
                                  fvec4 const& row3 );
    static mat4x3           columns( fvec3 const& col1,
                                     fvec3 const& col2,
                                     fvec3 const& col3,
                                     fvec3 const& col4 );
    
    float&                  operator()( swizz4 col,
                                        swizz3 row );
    float                   operator()( swizz4 col,
                                        swizz3 row ) const;
}; */

class swizz4 {
    public:
                                    swizz4() : index(0) {};
        swizz4                      operator-() const {return swizz4(-index);}
        template< class U > friend  class vec2;
        template< class U > friend  class vec3;
        template< class U > friend  class vec4;
        template< class U > friend  class mat;
        template< class U > friend  class mat2;
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
        template< class U > friend  class mat;
        template< class U > friend  class mat2;
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
        template< class U > friend  class mat;
        template< class U > friend  class mat2;
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
        template< class U > friend  class mat;
        template< class U > friend  class mat2;
        static swizz1               make_x() { return swizz1(1); }
        static swizz1               make_s() { return swizz1(1); }
        static swizz1               make_r() { return swizz1(1); }
        static swizz1               make_i() { return swizz1(1); }
        friend class Qutn;
    protected:
                                    swizz1( int index ) : swizz2( index ) {};
};

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
scalar<T>::scalar( comp_t x0) : data( {x0} ) {}

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
inline vec2<T>::vec2( comp_t x0,
                      comp_t x1 ) : data( {{ x0, x1 }} ) {}

template< typename T >
inline vec2<T>::vec2( comp_t fill ) : data( {{fill, fill}} ){}

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
vec3<T>::vec3( comp_t x0,
               comp_t x1,
               comp_t x2 ) : data( {{ x0, x1, x2 }} ) {}

template< typename T > inline
vec3<T>::vec3( comp_t fill ) : data( {{fill, fill, fill}} ) {}

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
vec4<T>::vec4( comp_t x0,
               comp_t x1,
               comp_t x2,
               comp_t x3 ) : data( {{ x0, x1, x2, x3 }} ) {}

template< typename T > inline
vec4<T>::vec4( comp_t fill ) : data( {{ fill, fill, fill, fill }} ) {}

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

/**template< typename T >
inline mat<T> mat<T>::rows( T rows[R][C] )
{
    mat<C,R,T> a_mat;
    
    size_t c;
    size_t r;
    size_t n_c = a_mat.n_cols;
    size_t n_r = a_mat.n_rows;
    
    for( c = 0; c < n_c; c++ ) {
        for( r = 0; r < n_r; r++ ) {
            a_mat.data.components[ c * n_r + r ] = rows[r][c];
        }
    }
    
    return a_mat;
}

template< size_t C, size_t R, typename T >
inline mat<C,R,T> mat<C,R,T>::columns( T cols[C][R] )
{
    mat<C,R,T> a_mat;
    
    size_t c;
    size_t r;
    size_t n_c = a_mat.n_cols;
    size_t n_r = a_mat.n_rows;
    
    for( c = 0; c < n_c; c++ ) {
        for( r = 0; r < n_r; r++ ) {
            a_mat.data.components[ c * n_r + r ] = rows[c][r];
        }
    }
    
    return a_mat;
}*/

template< typename T >
mat<T>::mat( size_t new_n_cols, size_t new_n_rows )
           : n_cols( new_n_cols ), n_rows( new_n_rows ),
             n_comp( n_cols * n_rows )
{ // TODO Need to throw an exception when dimensions are zero
    data = new mat_data( this );
    size_t i = n_comp;
    while( i ){ data->components[--i] = lit<comp_t>::zero; }
}

template< typename T >
inline mat<T> mat<T>::fill( size_t new_n_cols, size_t new_n_rows,
                    comp_t const val )
{
    mat<T> out( new_n_cols, new_n_rows );
    
    size_t i = out.n_comp;
    T* out_cm = out.data->components;
    
    while(i) { out_cm[--i] = val; }
    
    return out;
}

template< typename T >
inline mat<T> mat<T>::identity( size_t new_dim )
{
    mat<T> a_mat( new_dim, new_dim );
    
    size_t i = new_dim;
    ++new_dim;
    
    // The indices of the diagonal components in the array have
    // the form:
    // i * (1 + d)
    // where:
    // i is the number of the diagonal component, starting at zero
    // d is the dimension of the square matrix
    // 'i' is initialized to the dimension and we loop with it, so it
    // is decremented each loop. new_dim is incremented once, ahead of time.
    while(i) { a_mat.data->components[ --i * new_dim ] = lit<T>::one; }
    
    return a_mat;
}

template< typename T >
mat<T>::~mat() { delete data; }

template< typename T > inline
bool    mat<T>::operator==( mat<T> const& rhs ) const
{
    size_t i = n_comp;
    bool equal = true;
    if ( n_rows == rhs.n_rows and n_cols == rhs.n_cols) {
        while(i){ --i; equal &= data->components[i] == rhs.data->components[i]; }
    } else {
        equal = false;
    }
    return equal;
}

template< typename T > inline
mat<T>&     mat<T>::operator=( mat<T> const& rhs)
{
    // Do we need to allocate new memory?
    if ( n_comp == rhs.n_comp ) {
        size_t i = n_comp;
        while(i){ --i; data->components[i] = rhs.data->components[i]; }
    // Damn, guess we do...
    } else {
        // Dangling pointers are bad!
        mat_data* old_data = data;
        data = rhs.data->clone();
        data->owner = this;
        delete old_data;
    }
    n_rows = rhs.n_rows;
    n_cols = rhs.n_cols;
    return *this;
}

template< typename T >
inline T& mat<T>::operator()( size_t col, size_t row )
{ return data->components[col * n_rows + row]; }

template< typename T >
inline T mat<T>::operator()( size_t col, size_t row ) const
{ return data->components[col * n_rows + row]; }

template< typename T >
inline mat<T> mat<T>::operator+( mat<T> const& rhs ) const
{
    if( n_cols != rhs.n_cols || n_rows != rhs.n_rows ){
        throw std::invalid_argument("matrices not dimensionally similar on addition.");
    }
    
    mat<T> out( n_cols, n_rows );
    
    size_t i = n_comp;
    
    T* lhs_cm = data->components;
    T* rhs_cm = rhs.data->components;
    T* out_cm = out.data->components;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] + rhs_cm[i]; }
    
    return out;
}

template< typename T >
inline mat<T> mat<T>::operator-( mat<T> const& rhs ) const
{
    if( n_cols != rhs.n_cols || n_rows != rhs.n_rows ){
        throw std::invalid_argument("matrices not dimensionally similar on addition.");
    }
    
    mat<T> out( n_cols, n_rows );
    
    size_t i = n_comp;
    
    T const* lhs_cm = data->components;
    T const* rhs_cm = rhs.data->components;
    T* out_cm = out.data->components;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] - rhs_cm[i]; }
    
    return out;
}

template< typename T >
inline mat<T> mat<T>::operator*( mat<T> const& rhs ) const
{   
    if( n_cols != rhs.n_rows ){
        throw std::invalid_argument("row, column mismatch on multiplication.");
    }
    
    size_t element = 0;
    size_t addend = 0;

    T val = lit<T>::zero;

    mat<T> out( rhs.n_cols, n_rows );
    size_t n_cm = out.n_comp;
    
    T* lhs_cm = data->components;
    T* rhs_cm = rhs.data->components;
    T* out_cm = out.data->components;

    size_t rhs_nr = rhs.n_rows;

    for( element = 0; element < n_cm; ++element ){
        for( addend = 0; addend < rhs_nr; ++addend ){
            val += lhs_cm[ addend * n_rows + element % n_rows ]
                 * rhs_cm[ element / n_rows * rhs_nr + addend ];
        }
        out_cm[element] = val;
        val = lit<T>::zero;
    }

    return out;
}

template< typename T >
inline mat<T> mat<T>::operator*( T rhs )
{
    mat<T> out( n_cols, n_rows );
    size_t i = n_comp;
    
    T* out_cm = out.data->components;
    T const* lhs_cm = data->components;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] * rhs; }
    
    return out;
}

template< typename T >
inline mat<T> operator*( T lhs, mat<T> const& rhs )
{
    mat<T> out( rhs.n_cols, rhs.n_rows );
    size_t i = rhs.n_comp;
    
    T* out_cm = out.data->components;
    T const* rhs_cm = rhs.data->components;
    
    while(i) { --i; out_cm[i] = rhs_cm[i] * lhs; }
    
    return out;
}

template< typename T >
inline mat<T> mat<T>::operator/( T rhs )
{
    mat<T> out( n_cols, n_rows );
    size_t i = n_comp;
    
    T* out_cm = out.data->components;
    T const* lhs_cm = data->components;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] / rhs; }
    
    return out;
}

template< typename T >
inline mat<T>& mat<T>::fill( comp_t const val )
{    
    size_t i = n_comp;
    T* cm = data->components;
    
    while(i) { cm[--i] = val; }
    
    return *this;
}

template< typename T >
mat<T>& mat<T>::transpose()
{    
    mat_data* new_data = new mat_data(this);
    T const* old_cm = data->components;
    T* new_cm = new_data->components;
    size_t i = n_comp;
    
    while(i) {
        --i;
        new_cm[(i % n_rows) * n_cols + i / n_rows] = old_cm[i];
    }
    
    mat_data* old_data = data;
    data = new_data;
    delete old_data;
    
    // Now we can swap the dimensions, and all is well
    size_t dummy = n_rows;
    n_rows = n_cols;
    n_cols = dummy;
    return *this;
}

template< typename T>
raw_map const mat<T>::to_map() const
{ return map_bytes( data->n_bytes(), data->bytes() ); }

template< typename T >
inline mat<T>::mat_data::mat_data( mat_t* new_owner )
    : owner( new_owner )
{ components = new comp_t[owner->n_comp]; }

template< typename T >
inline mat<T>::mat_data::~mat_data() { delete[] components; }

template< typename T >
typename mat<T>::mat_data* mat<T>::mat_data::clone()
{
    mat_data* new_clone = new mat_data(this->owner);
    size_t i = owner->n_comp;
    while(i) {
        --i;
        new_clone->components[i] =
        this->components[i];
    }
    return new_clone;
}

template< typename T >
inline size_t mat<T>::mat_data::n_bytes()
{ return owner->n_comp * sizeof( comp_t ); }

template< typename T >
inline unsigned char const* mat<T>::mat_data::bytes()
{ return (unsigned char*) components; }

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat<T> const& src )
{
    size_t i = 0;
    size_t j = 0;

    for( i = 0; i < src.n_rows; ++i ){
        stream << "[ ";
        for( j = 0; j < src.n_cols; ++j ){
            stream << src(j,i) << " ";
        }
        stream << "]";
        // this makes sure the formatting behaves like other types
        if( i + 1 != src.n_rows && j + 1 != src.n_cols ){
             stream << std::endl;
        }
    }
    return stream;
}

/**template< size_t C, size_t R, typename T >
inline mat<C,R,T>& mat<C,R,T>::norm( bool ignore_translate = false )
{
    double inv_mag = 0.0;
    double comp_store;
    
    size_t n_c = ( ignore_translate ? this->n_cols - 1 : this->n_cols );
    size_t n_r = this->n_rows;
    
    for( size_t i = 0; i < n_c; i++ ) {
        for( size_t j = 0; j < n_r; j++ ) {
            comp_store = this->data.components[ i * n_r + j ];
            comp_store *= comp_store;
            inv_mag += comp_store;
        }
        
        inv_mag = 1.0 / std::sqrt( inv_mag );
        
        for( size_t j = 0; j < n_r; j++ ) {
            this->data.components[ i * n_r + j ] *= inv_mag;
        }
        
        inv_mag = 0.0;
    }
    return *this;
} */

template< typename T > inline
mat2<T>::mat2()
{ T* c = this->data.components;
  c[0] = lit<T>::zero;   c[2] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[3] = lit<T>::zero; }

template< typename T >
mat2<T>::mat2( T e00, T e10,
               T e01, T e11 )
{ T* c = this->data.components;
  c[0] = e00;   c[2] = e10;
  c[1] = e01;   c[3] = e11; }
  
template< typename T >
mat2<T>     mat2<T>::identity()
{ return mat2( lit<T>::one,  lit<T>::zero,
               lit<T>::zero; lit<T>::one   ); }

template< typename T > inline
mat2<T>     mat2<T>::row_vectors( vec2<T> const& row0,
                                  vec2<T> const& row1 )
{ return mat2( row0(x), row0(y),
               row1(x), row1(y) ); }
               
template< typename T > inline
mat2<T>     mat2<T>::column_vectors( vec2<T> const& col0,
                                     vec2<T> const& col1 )
{ return mat2( col0(x), col1(x),
               col0(y), col1(y) ); }

template< typename T > inline
mat2<T>     mat2<T>::scale( T sx, T sy )
{ return mat2( sx,           lit<T>::zero,
               lit<T>::zero, sy            ); }
               
template< typename T > inline
mat2<T>     mat2<T>::scale( vec2<T> const& svec )
{ return mat2( svec(x),      lit<T>::zero,
               lit<T>::zero, svec(y)       ); }
template< typename T > inline
bool    operator==( mat2<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] == rhs_c[0]
           and lhs_c[1] == rhs_c[1]
           and lhs_c[2] == rhs_c[2]
           and lhs_c[3] == rhs_c[3];
}

template< typename T > inline
bool    operator<( mat2<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] < rhs_c[0]
           and lhs_c[1] < rhs_c[1]
           and lhs_c[2] < rhs_c[2]
           and lhs_c[3] < rhs_c[3];
}

template< typename T > inline
bool    operator>( mat2<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] > rhs_c[0]
           and lhs_c[1] > rhs_c[1]
           and lhs_c[2] > rhs_c[2]
           and lhs_c[3] > rhs_c[3];
}

template< typename T > inline
bool    operator<=( mat2<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] <= rhs_c[0]
           and lhs_c[1] <= rhs_c[1]
           and lhs_c[2] <= rhs_c[2]
           and lhs_c[3] <= rhs_c[3];
}

template< typename T > inline
bool    operator>=( mat2<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] >= rhs_c[0]
           and lhs_c[1] >= rhs_c[1]
           and lhs_c[2] >= rhs_c[2]
           and lhs_c[3] >= rhs_c[3];
}

template< typename T > inline
bool    operator!=( mat2<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] != rhs_c[0]
           and lhs_c[1] != rhs_c[1]
           and lhs_c[2] != rhs_c[2]
           and lhs_c[3] != rhs_c[3];
}

tempalte< typename T > inline
mat2<T>&    operator=( mat2<T> const& rhs )
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    lhs_c[0] = rhs_c[0];
    lhs_c[1] = rhs_c[1];
    lhs_c[2] = rhs_c[2];
    lhs_c[3] = rhs_c[3];
    return *this;
}
               
template< typename T > inline
T&     mat2<T>::operator()( size_t col,
                            size_t row )
{
    if ( col > 1 or row > 1 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat2 used out of bounds index");
    }
    
    return this->data.components[col * 2 + row];
}

template< typename T > inline
T      mat2<T>::operator()( size_t col,
                            size_t row ) const
{
    if ( col > 1 or row > 1 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat2 used out of bounds index");
    }
    
    return this->data.components[col * 2 + row];
}

template< typename T > inline
mat2<T>     mat2<T>::operator+( mat2<T> const& rhs )
{
    T const* lhs_c = this->data.components;
    T const* rhs_c = rhs.data.components;
    
    T e00 = lhs_c[0] + rhs_c[0];
    T e10 = lhs_c[1] + rhs_c[1];
    T e01 = lhs_c[2] + rhs_c[2];
    T e11 = lhs_c[3] + rhs_c[3];
    
    return mat2( e00, e10,
                 e01, e11 );
}

template< typename T > inline
mat2<T>     mat2<T>::operator-()
{
    T const* lhs_c = this->data.components;
    
    T e00 = -lhs_c[0];
    T e10 = -lhs_c[1];
    T e01 = -lhs_c[2];
    T e11 = -lhs_c[3];
    
    return mat2( e00, e10,
                 e01, e11 );
}

template< typename T > inline
mat2<T>     mat2<T>::operator-( mat2<T> const& rhs )
{
    T const* lhs_c = this->data.components;
    T const* rhs_c = rhs.data.components;
    
    T e00 = lhs_c[0] - rhs_c[0];
    T e10 = lhs_c[1] - rhs_c[1];
    T e01 = lhs_c[2] - rhs_c[2];
    T e11 = lhs_c[3] - rhs_c[3];
    
    return mat2( e00, e10,
                 e01, e11 );
}
               
template< typename T > inline
mat2<T>     mat2<T>::operator*( mat2<T> const& rhs )
{
    T const* lhs_c = this->data.components;
    T const* rhs_c = rhs.data.components;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1];
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[2] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[3] * rhs_c[3];
    
    return mat2( e00, e10,
                 e01, e11 );
}

template< typename T >
mat2<T>     mat2<T>::operator*( T rhs )
{
    T const* rhs_c = this->data.components;
    
    T e00 = rhs_c[0] * rhs;
    T e01 = rhs_c[1] * rhs;
    T e10 = rhs_c[2] * rhs;
    T e11 = rhs_c[3] * rhs;
    
    return mat2( e00, e10,
                 e01, e11 );
}

template< typename D >
mat2<D>     operator*( D lhs, mat2<D> const& rhs )
{
    D const* rhs_c = rhs.data.components;
    
    D e00 = rhs_c[0] * lhs;
    D e01 = rhs_c[1] * lhs;
    D e10 = rhs_c[2] * lhs;
    D e11 = rhs_c[3] * lhs;
    
    return mat2<D>( e00, e10,
                    e01, e11 );
}

template< typename T >
mat2<T>     mat2<T>::operator/( T rhs )
{
    T const* rhs_c = this->data.components;
    
    T e00 = rhs_c[0] / rhs;
    T e01 = rhs_c[1] / rhs;
    T e10 = rhs_c[2] / rhs;
    T e11 = rhs_c[3] / rhs;
    
    return mat2( e00, e10,
                 e01, e11 );
}

template< typename T >
mat2<T>& mat2<T>::fill( T val )
{
    T* c = this->data.components;
    c[0] = val;
    c[1] = val;
    c[2] = val;
    c[3] = val;
    return *this;
}

template< typename T >
mat2<T>& mat2<T>::transpose()
{
    T* c = this->data.components;
    T swap = c[2];
    c[2] = c[1];
    c[1] = swap;
    return *this;
}

template< typename T > inline
mat2<T>&    mat2<T>::row( size_t row,
                          vec2<T> const& val )
{
    switch( row ){
        case 0:
            this->data.components[0] = val(x);
            this->data.components[2] = val(y);
            break;
        case 1:
            this->data.components[1] = val(x);
            this->data.components[3] = val(y);
            break;
        default:
          throw std::out_of_range("Component index on mat2 out of range.");
    }
          
    return *this;
}

template< typename T > inline
vec2<T>     mat2<T>::row( size_t row ) const
{
    T out_x, out_y;
    switch( row ){
        case 0:
            out_x = this->data.components[0];
            out_y = this->data.components[2];
            break;
        case 1:
            out_x = this->data.components[1];
            out_y = this->data.components[3];
            break;
        default:
          throw std::out_of_range("Component index on mat2 out of range.");
    }
    return vec2<T>(out_x, out_y);
}

template< typename T > inline
mat2<T>&    mat2<T>::column( size_t col,
                             vec2<T> const& val )
{
    switch( col ){
        case 0:
            this->data.components[0] = val(x);
            this->data.components[1] = val(y);
            break;
        case 1:
            this->data.components[2] = val(x);
            this->data.components[3] = val(y);
            break;
        default:
          throw std::out_of_range("Component index on mat2 out of range.");
    }
    return *this;
}

template< typename T > inline
vec2<T>     mat2<T>::column( size_t col ) const
{
    T out_x, out_y;
    switch( col ){
        case 0:
            out_x = this->data.components[0];
            out_y = this->data.components[1];
            break;
        case 1:
            out_x = this->data.components[2];
            out_y = this->data.components[3];
            break;
        default:
          throw std::out_of_range("Component index on mat2 out of range.");
    }
    return vec2<T>(out_x, out_y);
}

template< typename T >
inline mat2<T>& mat2<T>::rows( vec2<T> const& row0,
                               vec2<T> const& row1 )
{
    T* cm = this->data.components;
    
    cm[0] = row0(x);
    cm[2] = row0(y);
    cm[1] = row1(x);
    cm[3] = row1(y);
    
    return *this;
}

template< typename T > inline
mat2<T>&    mat2<T>::columns( vec2<T> const& col0,
                              vec2<T> const& col1 )
{
    T* cm = this->data.components;
    
    cm[0] = col0(x);
    cm[1] = col0(y);
    cm[2] = col1(x);
    cm[3] = col1(y);
    
    return *this;
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat2<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " ]" << std::endl;
    return stream;
}

// --------- MAT 3X3 -------------

template< typename T > inline
mat3<T>::mat3()
{ T* c = this->data.components;
  c[0] = lit<T>::zero;   c[3] = lit<T>::zero; c[6] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[4] = lit<T>::zero; c[7] = lit<T>::zero;
  c[2] = lit<T>::zero;   c[5] = lit<T>::zero; c[8] = lit<T>::zero; }

template< typename T >
mat3<T>::mat3( T e00, T e10, T e20, 
               T e01, T e11, T e21,
               T e02, T e13, T e22 )
{ T* c = this->data.components;
  c[0] = e00;   c[2] = e10;   c[2] = e20;
  c[1] = e01;   c[3] = e11;   c[3] = e21;
  c[1] = e02;   c[3] = e12;   c[3] = e22; }

template< typename T >
mat3<T>     mat3<T>::identity()
{ return mat3( lit<T>::one,  lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::one;  lit<T>::zero,
               lit<T>::zero, lit<T>::zero; lit<T>::one ); }
  
template< typename T > inline
mat3<T>     mat3<T>::row_vectors( vec3<T> const& row0,
                                  vec3<T> const& row1,
                                  vec3<T> const& row2 )
{ return mat3( row0(x), row0(y), row0(z),
               row1(x), row1(y), row1(z),
               row2(x), row2(y), row2(z) ); }
               
template< typename T > inline
mat3<T>     mat3<T>::column_vectors( vec3<T> const& col0,
                                     vec3<T> const& col1,
                                     vec3<T> const& col2 )
{ return mat3( col0(x), col1(x), col2(x),
               col0(y), col1(y), col2(y),
               col0(z), col1(z), col2(z) ); }

template< typename T > inline
mat3<T>     mat3<T>::scale( T sx, T sy, T sz )
{ return mat3( sx,           lit<T>::zero, lit<T>::zero,
               lit<T>::zero, sy,           lit<T>::zero,
               lit<T>::zero, lit<T>::zero, sz            ); }
               
template< typename T > inline
mat3<T>     mat3<T>::scale( vec3<T> const& svec )
{ return mat3( svec(x),      lit<T>::zero, lit<T>::zero,
               lit<T>::zero, svec(y),      lit<T>::zero,
               lit<T>::zero, lit<T>::zero, svec(z)       ); }
template< typename T > inline
bool    operator==( mat3<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] == rhs_c[0]
           and lhs_c[1] == rhs_c[1]
           and lhs_c[2] == rhs_c[2]
           and lhs_c[3] == rhs_c[3]
           and lhs_c[4] == rhs_c[4]
           and lhs_c[5] == rhs_c[5]
           and lhs_c[6] == rhs_c[6]
           and lhs_c[7] == rhs_c[7]
           and lhs_c[8] == rhs_c[8];
}

template< typename T > inline
bool    operator<( mat3<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] < rhs_c[0]
           and lhs_c[1] < rhs_c[1]
           and lhs_c[2] < rhs_c[2]
           and lhs_c[3] < rhs_c[3]
           and lhs_c[4] < rhs_c[4]
           and lhs_c[5] < rhs_c[5]
           and lhs_c[6] < rhs_c[6]
           and lhs_c[7] < rhs_c[7]
           and lhs_c[8] < rhs_c[8];
}

template< typename T > inline
bool    operator>( mat3<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] > rhs_c[0]
           and lhs_c[1] > rhs_c[1]
           and lhs_c[2] > rhs_c[2]
           and lhs_c[3] > rhs_c[3]
           and lhs_c[4] > rhs_c[4]
           and lhs_c[5] > rhs_c[5]
           and lhs_c[6] > rhs_c[6]
           and lhs_c[7] > rhs_c[7]
           and lhs_c[8] > rhs_c[8];
}

template< typename T > inline
bool    operator<=( mat3<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] <= rhs_c[0]
           and lhs_c[1] <= rhs_c[1]
           and lhs_c[2] <= rhs_c[2]
           and lhs_c[3] <= rhs_c[3]
           and lhs_c[4] <= rhs_c[4]
           and lhs_c[5] <= rhs_c[5]
           and lhs_c[6] <= rhs_c[6]
           and lhs_c[7] <= rhs_c[7]
           and lhs_c[8] <= rhs_c[8];
}

template< typename T > inline
bool    operator>=( mat3<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] >= rhs_c[0]
           and lhs_c[1] >= rhs_c[1]
           and lhs_c[2] >= rhs_c[2]
           and lhs_c[3] >= rhs_c[3]
           and lhs_c[4] >= rhs_c[4]
           and lhs_c[5] >= rhs_c[5]
           and lhs_c[6] >= rhs_c[6]
           and lhs_c[7] >= rhs_c[7]
           and lhs_c[8] >= rhs_c[8];
}

template< typename T > inline
bool    operator!=( mat3<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] != rhs_c[0]
           and lhs_c[1] != rhs_c[1]
           and lhs_c[2] != rhs_c[2]
           and lhs_c[3] != rhs_c[3]
           and lhs_c[4] != rhs_c[4]
           and lhs_c[5] != rhs_c[5]
           and lhs_c[6] != rhs_c[6]
           and lhs_c[7] != rhs_c[7]
           and lhs_c[8] != rhs_c[8];
}

tempalte< typename T > inline
mat3<T>&    operator=( mat3<T> const& rhs )
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    lhs_c[0] = rhs_c[0];
    lhs_c[1] = rhs_c[1];
    lhs_c[2] = rhs_c[2];
    lhs_c[3] = rhs_c[3];
    lhs_c[4] = rhs_c[4];
    lhs_c[5] = rhs_c[5];
    lhs_c[6] = rhs_c[6];
    lhs_c[7] = rhs_c[7];
    lhs_c[8] = rhs_c[8];
    return *this;
}
               
template< typename T > inline
T&     mat3<T>::operator()( size_t col,
                            size_t row )
{
    if ( col > 2 or row > 2 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat3 used out of bounds index");
    }
    
    return this->data.components[col * 3 + row];
}

template< typename T > inline
T      mat3<T>::operator()( size_t col,
                            size_t row ) const
{
    if ( col > 2 or row > 2 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat3 used out of bounds index");
    }
    
    return this->data.components[col * 3 + row];
}

template< typename T > inline
mat3<T>     mat3<T>::operator+( mat3<T> const& rhs )
{
    T const* lhs_c = this->data.components;
    T const* rhs_c = rhs.data.components;
    
    T e00 = lhs_c[0] + rhs_c[0];
    T e01 = lhs_c[1] + rhs_c[1];
    T e02 = lhs_c[2] + rhs_c[2];
    T e10 = lhs_c[3] + rhs_c[3];
    T e11 = lhs_c[4] + rhs_c[4];
    T e12 = lhs_c[5] + rhs_c[5];
    T e20 = lhs_c[6] + rhs_c[6];
    T e21 = lhs_c[7] + rhs_c[7];
    T e22 = lhs_c[8] + rhs_c[8];
    
    return mat3( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

template< typename T > inline
mat3<T>     mat3<T>::operator-()
{
    T const* lhs_c = this->data.components;
    
    T e00 = -lhs_c[0];
    T e01 = -lhs_c[1];
    T e02 = -lhs_c[2];
    T e10 = -lhs_c[3];
    T e11 = -lhs_c[4];
    T e12 = -lhs_c[5];
    T e20 = -lhs_c[6];
    T e21 = -lhs_c[7];
    T e22 = -lhs_c[8];
    
    return mat3( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

template< typename T > inline
mat3<T>     mat3<T>::operator-( mat3<T> const& rhs )
{
    T const* lhs_c = this->data.components;
    T const* rhs_c = rhs.data.components;
    
    T e00 = lhs_c[0] - rhs_c[0];
    T e01 = lhs_c[1] - rhs_c[1];
    T e02 = lhs_c[2] - rhs_c[2];
    
    T e10 = lhs_c[3] - rhs_c[3];
    T e11 = lhs_c[4] - rhs_c[4];
    T e12 = lhs_c[5] - rhs_c[5];
    
    T e20 = lhs_c[6] - rhs_c[6];
    T e21 = lhs_c[7] - rhs_c[7];
    T e22 = lhs_c[8] - rhs_c[8];
    
    return mat3( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}
               
template< typename T > inline
mat3<T>     mat3<T>::operator*( mat3<T> const& rhs )
{
    T const* lhs_c = this->data.components;
    T const* rhs_c = rhs.data.components;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[6] * rhs_c[2];
    T e10 = lhs_c[0] * rhs_c[3] + lhs_c[3] * rhs_c[4] + lhs_c[6] * rhs_c[5];
    T e20 = lhs_c[0] * rhs_c[6] + lhs_c[3] * rhs_c[7] + lhs_c[6] * rhs_c[8];
    
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[7] * rhs_c[2];
    T e11 = lhs_c[1] * rhs_c[3] + lhs_c[4] * rhs_c[4] + lhs_c[7] * rhs_c[5];
    T e21 = lhs_c[1] * rhs_c[6] + lhs_c[4] * rhs_c[7] + lhs_c[7] * rhs_c[8];
    
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[8] * rhs_c[2];
    T e12 = lhs_c[2] * rhs_c[3] + lhs_c[5] * rhs_c[4] + lhs_c[8] * rhs_c[5];
    T e22 = lhs_c[2] * rhs_c[6] + lhs_c[5] * rhs_c[7] + lhs_c[8] * rhs_c[8];
    
    return mat3( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

template< typename T >
mat3<T>     mat3<T>::operator*( T rhs )
{
    T const* rhs_c = this->data.components;
    
    T e00 = rhs_c[0] * rhs;
    T e01 = rhs_c[1] * rhs;
    T e02 = rhs_c[2] * rhs;
    T e10 = rhs_c[3] * rhs;
    T e11 = rhs_c[4] * rhs;
    T e12 = rhs_c[5] * rhs;
    T e20 = rhs_c[6] * rhs;
    T e21 = rhs_c[7] * rhs;
    T e22 = rhs_c[8] * rhs;
    
    return mat3( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

template< typename D >
mat3<D>     operator*( D lhs, mat3<D> const& rhs )
{
    D const* rhs_c = rhs.data.components;
    
    D e00 = rhs_c[0] * lhs;
    D e01 = rhs_c[1] * lhs;
    D e02 = rhs_c[2] * lhs;
    D e10 = rhs_c[3] * lhs;
    D e11 = rhs_c[4] * lhs;
    D e12 = rhs_c[5] * lhs;
    D e20 = rhs_c[6] * lhs;
    D e21 = rhs_c[7] * lhs;
    D e22 = rhs_c[8] * lhs;
    
    return mat3( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

template< typename T >
mat3<T>     mat3<T>::operator/( T rhs )
{
    T const* rhs_c = this->data.components;
    
    T e00 = rhs_c[0] / rhs;
    T e01 = rhs_c[1] / rhs;
    T e02 = rhs_c[2] / rhs;
    T e10 = rhs_c[3] / rhs;
    T e11 = rhs_c[4] / rhs;
    T e12 = rhs_c[5] / rhs;
    T e20 = rhs_c[6] / rhs;
    T e21 = rhs_c[7] / rhs;
    T e22 = rhs_c[8] / rhs;
    
    return mat3( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

template< typename T >
mat3<T>& mat3<T>::fill( T val )
{
    T* c = this->data.components;
    c[0] = val;
    c[1] = val;
    c[2] = val;
    c[3] = val;
    c[4] = val;
    c[5] = val;
    c[6] = val;
    c[7] = val;
    c[8] = val;
    return *this;
}

template< typename T >
mat3<T>& mat3<T>::transpose()
{
    T* c = this->data.components;
    T swap = c[3];
    c[3] = c[1];
    c[1] = swap;
    swap = c[6];
    c[6] = c[2];
    c[2] = swap;
    swap = c[7];
    c[7] = c[5];
    c[5] = swap;
    return *this;
}

template< typename T > inline
mat3<T>&    mat3<T>::row( size_t row,
                          vec3<T> const& val )
{
    switch( row ){
        case 0:
            this->data.components[0] = val(x);
            this->data.components[3] = val(y);
            this->data.components[6] = val(z);
            break;
        case 1:
            this->data.components[1] = val(x);
            this->data.components[4] = val(y);
            this->data.components[7] = val(z);
            break;
        case 2:
            this->data.components[2] = val(x);
            this->data.components[5] = val(y);
            this->data.components[8] = val(z);
            break;
        default:
          throw std::out_of_range("Component index on mat3 out of range.");
    }
          
    return *this;
}

template< typename T > inline
vec2<T>     mat3<T>::row( size_t row ) const
{
    T out_x, out_y, out_z;
    switch( row ){
        case 0:
            out_x = this->data.components[0];
            out_y = this->data.components[3];
            out_z = this->data.components[6];
            break;
        case 1:
            out_x = this->data.components[1];
            out_y = this->data.components[4];
            out_z = this->data.components[7];
            break;
        case 2:
            out_x = this->data.components[2];
            out_y = this->data.components[5];
            out_z = this->data.components[8];
            break;
        default:
          throw std::out_of_range("Component index on mat3 out of range.");
    }
    return vec3<T>(out_x, out_y, out_z);
}

template< typename T > inline
mat3<T>&    mat3<T>::column( size_t col,
                             vec3<T> const& val )
{
    switch( col ){
        case 0:
            this->data.components[0] = val(x);
            this->data.components[1] = val(y);
            this->data.components[2] = val(z);
            break;
        case 1:
            this->data.components[3] = val(x);
            this->data.components[4] = val(y);
            this->data.components[5] = val(z);
            break;
        case 2:
            this->data.components[6] = val(x);
            this->data.components[7] = val(y);
            this->data.components[8] = val(z);
            break;
        default:
          throw std::out_of_range("Component index on mat3 out of range.");
    }
    return *this;
}

template< typename T > inline
vec2<T>     mat3<T>::column( size_t col ) const
{
    T out_x, out_y;
    switch( col ){
        case 0:
            out_x = this->data.components[0];
            out_y = this->data.components[1];
            out_z = this->data.components[2];
            break;
        case 1:
            out_x = this->data.components[3];
            out_y = this->data.components[4];
            out_z = this->data.components[5];
            break;
        case 2:
            out_x = this->data.components[6];
            out_y = this->data.components[7];
            out_z = this->data.components[8];
            break;
        default:
          throw std::out_of_range("Component index on mat3 out of range.");
    }
    return vec3<T>(out_x, out_y, out_z);
}

template< typename T >
inline mat3<T>& mat3<T>::rows( vec3<T> const& row0,
                               vec3<T> const& row1,
                               vec3<T> const& row2 )
{
    T* c = this->data.components;
    
    c[0] = row0(x);
    c[3] = row0(y);
    c[6] = row0(z);
    c[1] = row1(x);
    c[4] = row1(y);
    c[7] = row1(z);
    c[2] = row2(x);
    c[5] = row2(y);
    c[8] = row2(z);
    
    return *this;
}

template< typename T > inline
mat3<T>&    mat3<T>::columns( vec3<T> const& col0,
                              vec3<T> const& col1,
                              vec3<T> const& col2 )
{
    T* c = this->data.components;
    
    c[0] = col0(x);
    c[1] = col0(y);
    c[2] = col0(z);
    c[3] = col1(x);
    c[4] = col1(y);
    c[5] = col1(z);
    c[6] = col2(x);
    c[7] = col2(y);
    c[8] = col2(z);
    
    return *this;
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat3<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " " << src(2,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " " << src(2,1) << " ]" << '\n';
    stream << "[ " << src(0,2) << " " << src(1,2) << " " << src(2,2) << " ]" << std::endl;
    return stream;
}

// --------- MAT 4X4 -------------

template< typename T > inline
mat4<T>::mat4()
{ T* c = this->data.components;
  c[0] = lit<T>::zero;   c[4] = lit<T>::zero;   c[8] = lit<T>::zero;   c[12] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[5] = lit<T>::zero;   c[9] = lit<T>::zero;   c[13] = lit<T>::zero;
  c[2] = lit<T>::zero;   c[6] = lit<T>::zero;   c[10] = lit<T>::zero;  c[14] = lit<T>::zero;
  c[3] = lit<T>::zero;   c[7] = lit<T>::zero;   c[11] = lit<T>::zero;  c[15] = lit<T>::zero; }

template< typename T >
mat4<T>::mat4( T e00, T e10, T e20, T e30,
               T e01, T e11, T e21, T e31,
               T e02, T e12, T e22, T e32,
               T e03, T e13, T e23, T e33 )
{ T* c = this->data.components;
  c[0] = e00;   c[4] = e10;   c[8] = e20;   c[12] = e30;
  c[1] = e01;   c[5] = e11;   c[9] = e21;   c[13] = e31;
  c[2] = e02;   c[6] = e12;   c[10] = e22;  c[14] = e32;
  c[3] = e03;   c[7] = e13;   c[11] = e23;  c[15] = e33; }

template< typename T >
mat4<T>     mat4<T>::identity()
{ return mat4( lit<T>::one,  lit<T>::zero, lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::one;  lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::zero; lit<T>::one,  lit<T>::zero,
               lit<T>::zero, lit<T>::zero; lit<T>::zero,  lit<T>::one  ); }
  
template< typename T > inline
mat4<T>     mat4<T>::row_vectors( vec4<T> const& row0,
                                  vec4<T> const& row1,
                                  vec4<T> const& row2,
                                  vec4<T> const& row3 )
{ return mat4( row0(x), row0(y), row0(z), row0(w),
               row1(x), row1(y), row1(z), row1(w),
               row2(x), row2(y), row2(z), row2(w),
               row3(x), row3(y), row3(z), row3(w), ); }
               
template< typename T > inline
mat4<T>     mat4<T>::column_vectors( vec4<T> const& col0,
                                     vec4<T> const& col1,
                                     vec4<T> const& col2,
                                     vec4<T> const& col3 )
{ return mat4( col0(x), col1(x), col2(x), col3(x),
               col0(y), col1(y), col2(y), col3(y),
               col0(z), col1(z), col2(z), col3(z),
               col0(w), col1(w), col2(w), col3(w) ); }

template< typename T > inline
mat4<T>     mat4<T>::scale( T sx, T sy, T sz )
{ return mat4( sx,           lit<T>::zero, lit<T>::zero, lit<T>::zero,
               lit<T>::zero, sy,           lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::zero, sz,           lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::zero, sw            ); }
               
template< typename T > inline
mat4<T>     mat4<T>::scale( vec4<T> const& svec )
{ return mat4( svec(x),      lit<T>::zero, lit<T>::zero, lit<T>::zero,
               lit<T>::zero, svec(y),      lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::zero, svec(z),      lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::zero, svec(w)       ); }
               
template< typename T > inline
bool    operator==( mat4<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] == rhs_c[0]
           and lhs_c[1] == rhs_c[1]
           and lhs_c[2] == rhs_c[2]
           and lhs_c[3] == rhs_c[3]
           and lhs_c[4] == rhs_c[4]
           and lhs_c[5] == rhs_c[5]
           and lhs_c[6] == rhs_c[6]
           and lhs_c[7] == rhs_c[7]
           and lhs_c[8] == rhs_c[8]
           and lhs_c[9] == rhs_c[9]
           and lhs_c[10] == rhs_c[10]
           and lhs_c[11] == rhs_c[11]
           and lhs_c[12] == rhs_c[12]
           and lhs_c[13] == rhs_c[13]
           and lhs_c[14] == rhs_c[14]
           and lhs_c[15] == rhs_c[15];
}

template< typename T > inline
bool    operator<( mat4<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] < rhs_c[0]
           and lhs_c[1] < rhs_c[1]
           and lhs_c[2] < rhs_c[2]
           and lhs_c[3] < rhs_c[3]
           and lhs_c[4] < rhs_c[4]
           and lhs_c[5] < rhs_c[5]
           and lhs_c[6] < rhs_c[6]
           and lhs_c[7] < rhs_c[7]
           and lhs_c[8] < rhs_c[8]
           and lhs_c[9] < rhs_c[9]
           and lhs_c[10] < rhs_c[10]
           and lhs_c[11] < rhs_c[11]
           and lhs_c[12] < rhs_c[12]
           and lhs_c[13] < rhs_c[13]
           and lhs_c[14] < rhs_c[14]
           and lhs_c[15] < rhs_c[15];
}

template< typename T > inline
bool    operator>( mat4<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] > rhs_c[0]
           and lhs_c[1] > rhs_c[1]
           and lhs_c[2] > rhs_c[2]
           and lhs_c[3] > rhs_c[3]
           and lhs_c[4] > rhs_c[4]
           and lhs_c[5] > rhs_c[5]
           and lhs_c[6] > rhs_c[6]
           and lhs_c[7] > rhs_c[7]
           and lhs_c[8] > rhs_c[8]
           and lhs_c[9] > rhs_c[9]
           and lhs_c[10] > rhs_c[10]
           and lhs_c[11] > rhs_c[11]
           and lhs_c[12] > rhs_c[12]
           and lhs_c[13] > rhs_c[13]
           and lhs_c[14] > rhs_c[14]
           and lhs_c[15] > rhs_c[15];
}

template< typename T > inline
bool    operator<=( mat4<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] <= rhs_c[0]
           and lhs_c[1] <= rhs_c[1]
           and lhs_c[2] <= rhs_c[2]
           and lhs_c[3] <= rhs_c[3]
           and lhs_c[4] <= rhs_c[4]
           and lhs_c[5] <= rhs_c[5]
           and lhs_c[6] <= rhs_c[6]
           and lhs_c[7] <= rhs_c[7]
           and lhs_c[8] <= rhs_c[8]
           and lhs_c[9] <= rhs_c[9]
           and lhs_c[10] <= rhs_c[10]
           and lhs_c[11] <= rhs_c[11]
           and lhs_c[12] <= rhs_c[12]
           and lhs_c[13] <= rhs_c[13]
           and lhs_c[14] <= rhs_c[14]
           and lhs_c[15] <= rhs_c[15];
}

template< typename T > inline
bool    operator>=( mat4<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] >= rhs_c[0]
           and lhs_c[1] >= rhs_c[1]
           and lhs_c[2] >= rhs_c[2]
           and lhs_c[3] >= rhs_c[3]
           and lhs_c[4] >= rhs_c[4]
           and lhs_c[5] >= rhs_c[5]
           and lhs_c[6] >= rhs_c[6]
           and lhs_c[7] >= rhs_c[7]
           and lhs_c[8] >= rhs_c[8]
           and lhs_c[9] >= rhs_c[9]
           and lhs_c[10] >= rhs_c[10]
           and lhs_c[11] >= rhs_c[11]
           and lhs_c[12] >= rhs_c[12]
           and lhs_c[13] >= rhs_c[13]
           and lhs_c[14] >= rhs_c[14]
           and lhs_c[15] >= rhs_c[15];
}

template< typename T > inline
bool    operator!=( mat4<T> const& rhs ) const
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    return     lhs_c[0] != rhs_c[0]
           and lhs_c[1] != rhs_c[1]
           and lhs_c[2] != rhs_c[2]
           and lhs_c[3] != rhs_c[3]
           and lhs_c[4] != rhs_c[4]
           and lhs_c[5] != rhs_c[5]
           and lhs_c[6] != rhs_c[6]
           and lhs_c[7] != rhs_c[7]
           and lhs_c[8] != rhs_c[8]
           and lhs_c[9] != rhs_c[9]
           and lhs_c[10] != rhs_c[10]
           and lhs_c[11] != rhs_c[11]
           and lhs_c[12] != rhs_c[12]
           and lhs_c[13] != rhs_c[13]
           and lhs_c[14] != rhs_c[14]
           and lhs_c[15] != rhs_c[15];
}

tempalte< typename T > inline
mat4<T>&    operator=( mat4<T> const& rhs )
{
    T* rhs_c = rhs.data.components;
    T* lhs_c = this->data.components;
    lhs_c[0] = rhs_c[0];
    lhs_c[1] = rhs_c[1];
    lhs_c[2] = rhs_c[2];
    lhs_c[3] = rhs_c[3];
    lhs_c[4] = rhs_c[4];
    lhs_c[5] = rhs_c[5];
    lhs_c[6] = rhs_c[6];
    lhs_c[7] = rhs_c[7];
    lhs_c[8] = rhs_c[8];
    lhs_c[9] = rhs_c[9];
    lhs_c[10] = rhs_c[10];
    lhs_c[11] = rhs_c[11];
    lhs_c[12] = rhs_c[12];
    lhs_c[13] = rhs_c[13];
    lhs_c[14] = rhs_c[14];
    lhs_c[15] = rhs_c[15];
    return *this;
}
               
template< typename T > inline
T&     mat4<T>::operator()( size_t col,
                            size_t row )
{
    if ( col > 3 or row > 3 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat4 used out of bounds index");
    }
    
    return this->data.components[col * 4 + row];
}

template< typename T > inline
T      mat4<T>::operator()( size_t col,
                            size_t row ) const
{
    if ( col > 3 or row > 3 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat4 used out of bounds index");
    }
    
    return this->data.components[col * 4 + row];
}

template< typename T > inline
mat4<T>     mat4<T>::operator+( mat4<T> const& rhs )
{
    T const* lhs_c = this->data.components;
    T const* rhs_c = rhs.data.components;
    
    return mat4( lhs_c[0] + rhs_c[0], lhs_c[4] + rhs_c[4], lhs_c[8] + rhs_c[8],   lhs_c[12] + rhs_c[12],
                 lhs_c[1] + rhs_c[1], lhs_c[5] + rhs_c[5], lhs_c[9] + rhs_c[9],   lhs_c[13] + rhs_c[13],
                 lhs_c[2] + rhs_c[2], lhs_c[6] + rhs_c[6], lhs_c[10] + rhs_c[10], lhs_c[14] + rhs_c[14],
                 lhs_c[3] + rhs_c[3], lhs_c[7] + rhs_c[7], lhs_c[11] + rhs_c[11], lhs_c[15] + rhs_c[15] );
}

template< typename T > inline
mat4<T>     mat4<T>::operator-()
{
    T const* lhs_c = this->data.components;
    
    return mat4( -lhs_c[0], -lhs_c[4], -lhs_c[8],  -lhs_c[12],
                 -lhs_c[1], -lhs_c[5], -lhs_c[9],  -lhs_c[13],
                 -lhs_c[2], -lhs_c[6], -lhs_c[10], -lhs_c[14],
                 -lhs_c[3], -lhs_c[7], -lhs_c[11], -lhs_c[15] );
}

template< typename T > inline
mat4<T>     mat4<T>::operator-( mat4<T> const& rhs )
{
    T const* lhs_c = this->data.components;
    T const* rhs_c = rhs.data.components;
    
    return mat4( lhs_c[0] - rhs_c[0], lhs_c[4] - rhs_c[4], lhs_c[8] - rhs_c[8], lhs_c[12] - rhs_c[12],
                 lhs_c[1] - rhs_c[1], lhs_c[5] - rhs_c[5], lhs_c[9] - rhs_c[9], lhs_c[13] - rhs_c[13],
                 lhs_c[2] - rhs_c[2], lhs_c[6] - rhs_c[6], lhs_c[10] - rhs_c[10], lhs_c[14] - rhs_c[14],
                 lhs_c[3] - rhs_c[3], lhs_c[7] - rhs_c[7], lhs_c[11] - rhs_c[11], lhs_c[15] - rhs_c[15] );
}
               
template< typename T > inline
mat4<T>     mat4<T>::operator*( mat4<T> const& rhs )
{
    T const* lhs_c = this->data.components;
    T const* rhs_c = rhs.data.components;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[8] * rhs_c[2] + lhs_c[12] * rhs_c[3];
    T e10 = lhs_c[0] * rhs_c[4] + lhs_c[4] * rhs_c[5] + lhs_c[8] * rhs_c[6] + lhs_c[12] * rhs_c[7];
    T e20 = lhs_c[0] * rhs_c[8] + lhs_c[4] * rhs_c[9] + lhs_c[8] * rhs_c[10] + lhs_c[12] * rhs_c[11];
    T e30 = lhs_c[0] * rhs_c[12] + lhs_c[4] * rhs_c[13] + lhs_c[8] * rhs_c[14] + lhs_c[12] * rhs_c[15];
    
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[9] * rhs_c[2] + lhs_c[13] * rhs_c[3];
    T e11 = lhs_c[1] * rhs_c[4] + lhs_c[5] * rhs_c[4] + lhs_c[9] * rhs_c[6] + lhs_c[13] * rhs_c[7];
    T e21 = lhs_c[1] * rhs_c[8] + lhs_c[5] * rhs_c[9] + lhs_c[9] * rhs_c[10] + lhs_c[13] * rhs_c[11];
    T e31 = lhs_c[1] * rhs_c[12] + lhs_c[5] * rhs_c[13] + lhs_c[9] * rhs_c[14] + lhs_c[13] * rhs_c[15];
    
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[6] * rhs_c[1] + lhs_c[10] * rhs_c[2] + lhs_c[14] * rhs_c[3];
    T e12 = lhs_c[2] * rhs_c[4] + lhs_c[6] * rhs_c[4] + lhs_c[10] * rhs_c[6] + lhs_c[14] * rhs_c[7];
    T e22 = lhs_c[2] * rhs_c[8] + lhs_c[6] * rhs_c[9] + lhs_c[10] * rhs_c[10] + lhs_c[14] * rhs_c[11];
    T e32 = lhs_c[2] * rhs_c[12] + lhs_c[6] * rhs_c[13] + lhs_c[10] * rhs_c[14] + lhs_c[14] * rhs_c[15];
    
    T e03 = lhs_c[3] * rhs_c[0] + lhs_c[7] * rhs_c[1] + lhs_c[11] * rhs_c[2] + lhs_c[15] * rhs_c[3];
    T e13 = lhs_c[3] * rhs_c[4] + lhs_c[7] * rhs_c[4] + lhs_c[11] * rhs_c[6] + lhs_c[15] * rhs_c[7];
    T e23 = lhs_c[3] * rhs_c[8] + lhs_c[7] * rhs_c[9] + lhs_c[11] * rhs_c[10] + lhs_c[15] * rhs_c[11];
    T e33 = lhs_c[3] * rhs_c[12] + lhs_c[7] * rhs_c[13] + lhs_c[11] * rhs_c[14] + lhs_c[15] * rhs_c[15];
    
    return mat4( e00, e10, e20, e30,
                 e01, e11, e21, e31,
                 e02, e12, e22, e32,
                 e03, e13, e23, e33 );
}

template< typename T >
mat4<T>     mat4<T>::operator*( T rhs )
{
    T const* rhs_c = this->data.components;
    
    return mat4( rhs_c[0] * rhs, rhs_c[4] * rhs, rhs_c[8] * rhs,  rhs_c[12] * rhs,
                 rhs_c[1] * rhs, rhs_c[5] * rhs, rhs_c[9] * rhs,  rhs_c[13] * rhs,
                 rhs_c[2] * rhs, rhs_c[6] * rhs, rhs_c[10] * rhs, rhs_c[14] * rhs,
                 rhs_c[3] * rhs, rhs_c[7] * rhs, rhs_c[11] * rhs, rhs_c[15] * rhs  );
}

template< typename D >
mat4<D>     operator*( D lhs, mat4<D> const& rhs )
{
    D const* rhs_c = rhs.data.components;
    
    return mat4( rhs_c[0] * lhs, rhs_c[4] * lhs, rhs_c[8] * lhs,  rhs_c[12] * lhs,
                 rhs_c[1] * lhs, rhs_c[5] * lhs, rhs_c[9] * lhs,  rhs_c[13] * lhs,
                 rhs_c[2] * lhs, rhs_c[6] * lhs, rhs_c[10] * lhs, rhs_c[14] * lhs,
                 rhs_c[3] * lhs, rhs_c[7] * lhs, rhs_c[11] * lhs, rhs_c[15] * lhs );
}

template< typename T >
mat4<T>     mat4<T>::operator/( T rhs )
{
    T const* rhs_c = this->data.components;
    
    return mat4( rhs_c[0] / lhs, rhs_c[4] / lhs, rhs_c[8] / lhs,  rhs_c[12] / lhs,
                 rhs_c[1] / lhs, rhs_c[5] / lhs, rhs_c[9] / lhs,  rhs_c[13] / lhs,
                 rhs_c[2] / lhs, rhs_c[6] / lhs, rhs_c[10] / lhs, rhs_c[14] / lhs,
                 rhs_c[3] / lhs, rhs_c[7] / lhs, rhs_c[11] / lhs, rhs_c[15] / lhs );
}

template< typename T >
mat4<T>& mat4<T>::fill( T val )
{
    T* c = this->data.components;
    c[0] = val;     c[4] = val;     c[8] = val;     c[12] = val;
    c[1] = val;     c[5] = val;     c[9] = val;     c[13] = val;
    c[2] = val;     c[6] = val;     c[10] = val;    c[14] = val;
    c[3] = val;     c[7] = val;     c[11] = val;    c[15] = val;
 
    return *this;
}

template< typename T >
mat4<T>& mat4<T>::transpose()
{
    T* c = this->data.components;
    T swap = c[4];
    c[4] = c[1];
    c[1] = swap;
    swap = c[8];
    c[8] = c[2];
    c[2] = swap;
    swap = c[9];
    c[9] = c[6];
    c[6] = swap;
    swap = c[12];
    c[12] = c[3];
    c[3] = swap;
    swap = c[13];
    c[13] = c[7];
    c[7] = swap;
    swap = c[14];
    c[14] = c[11];
    c[11] = swap;
    return *this;
}

template< typename T > inline
mat4<T>&    mat4<T>::row( size_t row,
                          vec4<T> const& val )
{
    switch( row ){
        case 0:
            this->data.components[0] = val(x);
            this->data.components[3] = val(y);
            this->data.components[6] = val(z);
            break;
        case 1:
            this->data.components[1] = val(x);
            this->data.components[4] = val(y);
            this->data.components[7] = val(z);
            break;
        case 2:
            this->data.components[2] = val(x);
            this->data.components[5] = val(y);
            this->data.components[8] = val(z);
            break;
        default:
          throw std::out_of_range("Component index on mat4 out of range.");
    }
          
    return *this;
}

template< typename T > inline
vec2<T>     mat4<T>::row( size_t row ) const
{
    T out_x, out_y, out_z;
    switch( row ){
        case 0:
            out_x = this->data.components[0];
            out_y = this->data.components[3];
            out_z = this->data.components[6];
            break;
        case 1:
            out_x = this->data.components[1];
            out_y = this->data.components[4];
            out_z = this->data.components[7];
            break;
        case 2:
            out_x = this->data.components[2];
            out_y = this->data.components[5];
            out_z = this->data.components[8];
            break;
        default:
          throw std::out_of_range("Component index on mat4 out of range.");
    }
    return vec3<T>(out_x, out_y, out_z);
}

template< typename T > inline
mat4<T>&    mat4<T>::column( size_t col,
                             vec3<T> const& val )
{
    switch( col ){
        case 0:
            this->data.components[0] = val(x);
            this->data.components[1] = val(y);
            this->data.components[2] = val(z);
            break;
        case 1:
            this->data.components[3] = val(x);
            this->data.components[4] = val(y);
            this->data.components[5] = val(z);
            break;
        case 2:
            this->data.components[6] = val(x);
            this->data.components[7] = val(y);
            this->data.components[8] = val(z);
            break;
        default:
          throw std::out_of_range("Component index on mat4 out of range.");
    }
    return *this;
}

template< typename T > inline
vec2<T>     mat4<T>::column( size_t col ) const
{
    T out_x, out_y;
    switch( col ){
        case 0:
            out_x = this->data.components[0];
            out_y = this->data.components[1];
            out_z = this->data.components[2];
            break;
        case 1:
            out_x = this->data.components[3];
            out_y = this->data.components[4];
            out_z = this->data.components[5];
            break;
        case 2:
            out_x = this->data.components[6];
            out_y = this->data.components[7];
            out_z = this->data.components[8];
            break;
        default:
          throw std::out_of_range("Component index on mat4 out of range.");
    }
    return vec3<T>(out_x, out_y, out_z);
}

template< typename T >
inline mat4<T>& mat4<T>::rows( vec3<T> const& row0,
                               vec3<T> const& row1,
                               vec3<T> const& row2 )
{
    T* c = this->data.components;
    
    c[0] = row0(x);
    c[3] = row0(y);
    c[6] = row0(z);
    c[1] = row1(x);
    c[4] = row1(y);
    c[7] = row1(z);
    c[2] = row2(x);
    c[5] = row2(y);
    c[8] = row2(z);
    
    return *this;
}

template< typename T > inline
mat4<T>&    mat4<T>::columns( vec3<T> const& col0,
                              vec3<T> const& col1,
                              vec3<T> const& col2 )
{
    T* c = this->data.components;
    
    c[0] = col0(x);
    c[1] = col0(y);
    c[2] = col0(z);
    c[3] = col1(x);
    c[4] = col1(y);
    c[5] = col1(z);
    c[6] = col2(x);
    c[7] = col2(y);
    c[8] = col2(z);
    
    return *this;
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat4<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " " << src(2,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " " << src(2,1) << " ]" << '\n';
    stream << "[ " << src(0,2) << " " << src(1,2) << " " << src(2,2) << " ]" << std::endl;
    return stream;
}

}

#endif
