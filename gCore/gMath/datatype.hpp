#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <stdexcept>
#include <iostream>
#include <cmath>
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
template< size_t C, size_t R, typename T > class mat;

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

template< size_t C_R, size_t RL, size_t CR, typename D>
mat<CR,RL,D> operator*( mat<C_R,RL,D> const& lhs, mat<CR,C_R,D> const& rhs );

template< size_t C, size_t R, typename T >
class mat : public raw_mappable {
public:
    typedef mat<C,R,T>      mat_t;
    typedef T               comp_t;
    static size_t const     n_cols = C;
    static size_t const     n_rows = R;
    static size_t const     n_elem = C * R;
    
                            mat() { size_t i = n_cols * n_rows;
                                    while( i ){
                                        data.components[i-1] = 0.0f;
                                        --i;
                                    }
                                  };
    static mat_t            rows( comp_t rows[R][C] );
    static mat_t            columns( comp_t cols[C][R] );
    static mat_t            identity();
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
                                        
                                        
    template< size_t C_R, size_t RL, size_t CR, typename D>
    friend mat<CR,RL,D> operator*( mat<C_R,RL,D> const& lhs, mat<CR,C_R,D> const& rhs );
    
    //mat_t                   operator*( mat_t const& rhs ) const;
    mat_t                   operator+( mat_t const& rhs ) const;
    mat_t                   operator-( mat_t const& rhs ) const;
   
    friend mat_t            operator*( float lhs,
                                       mat_t const& rhs );
    friend mat_t            operator*( mat_t const& lhs,
                                       float rhs );
    
    mat<R,C,T>&             transpose();
    mat_t&                  norm( bool ignore_translate );
    
    virtual raw_map const   to_map() const;

    //friend std::ostream& operator<<( std::ostream& stream, mat_t const& src );
protected:
    union {
        comp_t              components[n_cols * n_rows];
        unsigned char       bytes[sizeof(comp_t) * n_cols * n_rows];
    } data;

};

class mat2 : public mat<2,2,float> {
public:
    typedef mat<2,2,float>  base_t;
    
                            mat2() : base_t() {};
                            mat2( float e00, float e10,
                                  float e01, float e11 );
    mat2&                   row( swizz2 const& row,
                                 fvec2 const& val );
    mat2&                   column( swizz2 const& col,
                                    fvec2 const& val );
    static mat2             rows( fvec2 const& row1,
                                  fvec2 const& row2 );
    static mat2             columns( fvec2 const& col1,
                                     fvec2 const& col2 );
    static mat2             scale( float sx,
                                   float sy );
    static mat2             scale( fvec2 const& svec );
    
    float&                  operator()( swizz2 col,
                                        swizz2 row );
    float                   operator()( swizz2 col,
                                        swizz2 row ) const;
};

class mat2x3 : public mat<2,3,float> {
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
};

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

template< size_t C, size_t R, typename T >
inline mat<C,R,T> mat<C,R,T>::rows( T rows[R][C] )
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
}

template< size_t C, size_t R, typename T >
inline mat<C,R,T> mat<C,R,T>::identity()
{
    mat<C,R,T> a_mat;
    
    size_t n_r = a_mat.n_rows;
    size_t min_dim = ( a_mat.n_cols < n_r ? a_mat.n_cols : n_r );
    
    // the offset into the array has the formula:
    // column * numbew_of_rows + row
    // when we are doing the diagonal, the column
    // and row are the same, so it reduces to:
    // i( number_of_rows + 1)
    // so we increment n_r here just once before the loop
    n_r++;
    
    for( size_t i = 0; i < min_dim; i++ ){
        a_mat.data.components[ i * n_r ] = 1;
    }
    
    return a_mat;
}

template< size_t C, size_t R, typename T >
inline T& mat<C,R,T>::operator()( size_t col, size_t row )
{
    return this->data.components[col * this->n_rows + row];
}

template< size_t C, size_t R, typename T >
inline T mat<C,R,T>::operator()( size_t col, size_t row ) const
{
    T out = this->data.components[col * this->n_rows + row];
    return out;
}

template< size_t C_R, size_t RL, size_t CR, typename D >
inline mat<CR,RL,D> operator*( mat<C_R,RL,D> const& lhs, mat<CR,C_R,D> const& rhs )
{   
    size_t element = 0;
    size_t addend = 0;

    D sum = 0.0;

    mat<CR,RL,D> out;

    for( element = 0; element < lhs.n_rows * rhs.n_cols; ++element ){
        for( addend = 0; addend < lhs.n_cols; ++addend ){
            sum += lhs( addend, element % lhs.n_rows ) * rhs( element / lhs.n_rows, addend );
        }
        out.data.components[element] = sum;
        sum = 0.0;
    }

    return out;
}

template< size_t C, size_t R, typename T >
inline mat<C,R,T> mat<C,R,T>::operator+( mat<C,R,T> const& rhs ) const
{
    mat<C,R,T>::mat_t a_mat();
    
    for( size_t i = 0; i < this->n_elem; i++ ) {
        a_mat.data.components[i] = this->data.components[i] + rhs.data.components[i];
    }
    
    return a_mat;
}

template< size_t C, size_t R, typename T >
inline mat<C,R,T> mat<C,R,T>::operator-( mat<C,R,T> const& rhs ) const
{
    mat<C,R,T>::mat_t a_mat();
    
    for( size_t i = 0; i < this->n_elem; i++ ) {
        a_mat.data.components[i] = this->data.components[i] - rhs.data.components[i];
    }
    
    return a_mat;
}

template< size_t C, size_t R, typename T >
inline mat<C,R,T>& mat<C,R,T>::transpose()
{
    return *this;
}

template< size_t C, size_t R, typename T >
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
}

template< size_t C, size_t R, typename T>
raw_map const mat<C,R,T>::to_map() const
{
    return map_bytes( sizeof(T) * 4, data.bytes );
}

template< size_t C, size_t R, typename T>
std::ostream& operator<<( std::ostream& stream, mat<C,R,T> const& src )
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

inline mat2::mat2( float e00, float e10,
                   float e01, float e11 )
{
    float* c = this->data.components;
    c[0] = e00;
    c[1] = e01;
    c[2] = e10;
    c[3] = e11;
}

inline mat2& mat2::row( swizz2 const& row,
                        fvec2 const& val )
{
    return *this;
}

inline mat2& mat2::column( swizz2 const& col,
                           fvec2 const& val )
{
    return *this;
}

inline mat2 mat2::rows( fvec2 const& row1,
                        fvec2 const& row2 )
{
    return *(new mat2());
}

inline mat2 mat2::columns( fvec2 const& col1,
                           fvec2 const& col2 )
{
    return *(new mat2());
}

inline mat2x3::mat2x3( float e00, float e10,
                       float e01, float e11,
                       float e02, float e12 )
{
    float* c = this->data.components;
    c[0] = e00;
    c[1] = e01;
    c[2] = e02;
    c[3] = e10;
    c[4] = e11;
    c[5] = e12;
}

inline mat2x3& mat2x3::row( swizz3 const& row,
                            fvec2 const& val )
{
    return *this;
}

inline mat2x3& mat2x3::column( swizz2 const& col,
                               fvec3 const& val )
{
    return *this;
}

inline mat2x3 mat2x3::rows( fvec2 const& row1,
                             fvec2 const& row2,
                             fvec2 const& row3 )
{
    return *(new mat2x3());
}

inline mat2x3 mat2x3::columns( fvec3 const& col1,
                                fvec3 const& col2 )
{
    return *(new mat2x3());
}

inline mat2x4::mat2x4( float e00, float e10,
                       float e01, float e11,
                       float e02, float e12,
                       float e03, float e13 )
{
    float* c = this->data.components;
    c[0] = e00;
    c[1] = e01;
    c[2] = e02;
    c[3] = e03;
    c[4] = e10;
    c[5] = e11;
    c[6] = e12;
    c[7] = e13;
}

inline mat2x4& mat2x4::row( swizz4 const& row,
                            fvec2 const& val )
{
    return *this;
}

inline mat2x4& mat2x4::column( swizz2 const& col,
                               fvec4 const& val )
{
    return *this;
}

inline mat2x4 mat2x4::rows( fvec2 const& row1,
                            fvec2 const& row2,
                            fvec2 const& row3,
                            fvec2 const& row4 )
{
    return *(new mat2x4());
}

inline mat2x4 mat2x4::columns( fvec4 const& col1,
                               fvec4 const& col2 )
{
    return *(new mat2x4());
}

inline mat3x2::mat3x2( float e00, float e10, float e20,
                       float e01, float e11, float e21 )
{
    float* c = this->data.components;
    c[0] = e00;
    c[1] = e01;
    c[2] = e10;
    c[3] = e11;
    c[4] = e20;
    c[5] = e21;
}

inline mat3x2& mat3x2::row( swizz2 const& row,
                            fvec3 const& val )
{
    return *this;
}

inline mat3x2& mat3x2::column( swizz3 const& col,
                               fvec2 const& val )
{
    return *this;
}

inline mat3x2 mat3x2::rows( fvec3 const& row1,
                            fvec3 const& row2 )
{
    return *(new mat3x2());
}

inline mat3x2 mat3x2::columns( fvec2 const& col1,
                               fvec2 const& col2,
                               fvec2 const& col3 )
{
    return *(new mat3x2());
}

inline mat3::mat3( float e00, float e10, float e20,
                   float e01, float e11, float e21,
                   float e02, float e12, float e22 )
{
    float* c = this->data.components;
    c[0] = e00;
    c[1] = e01;
    c[2] = e02;
    c[3] = e10;
    c[4] = e11;
    c[5] = e12;
    c[6] = e20;
    c[7] = e21;
    c[8] = e22;
}

inline mat3& mat3::row( swizz3 const& row,
                        fvec3 const& val )
{
    return *this;
}

inline mat3& mat3::column( swizz3 const& col,
                           fvec3 const& val )
{
    return *this;
}

inline mat3 mat3::rows( fvec3 const& row1,
                        fvec3 const& row2,
                        fvec3 const& row3 )
{
    return *(new mat3());
}

inline mat3 mat3::columns( fvec3 const& col1,
                           fvec3 const& col2,
                           fvec3 const& col3 )
{
    return *(new mat3());
}

inline mat3x4::mat3x4( float e00, float e10, float e20,
                       float e01, float e11, float e21,
                       float e02, float e12, float e22,
                       float e03, float e13, float e23 )
{
    float* c = this->data.components;
    c[0] = e00;
    c[1] = e01;
    c[2] = e02;
    c[3] = e03;
    c[4] = e10;
    c[5] = e11;
    c[6] = e12;
    c[7] = e13;
    c[8] = e20;
    c[9] = e21;
    c[10] = e22;
    c[11] = e23;
}

inline mat3x4& mat3x4::row( swizz4 const& row,
                            fvec3 const& val )
{
    return *this;
}

inline mat3x4& mat3x4::column( swizz3 const& col,
                               fvec4 const& val )
{
    return *this;
}

inline mat3x4 mat3x4::rows( fvec3 const& row1,
                            fvec3 const& row2,
                            fvec3 const& row3,
                            fvec3 const& row4 )
{
    return *(new mat3x4());
}

inline mat3x4 mat3x4::columns( fvec4 const& col1,
                               fvec4 const& col2,
                               fvec4 const& col3 )
{
    return *(new mat3x4());
}

inline mat4x2::mat4x2( float e00, float e10, float e20, float e30,
                       float e01, float e11, float e21, float e31 )
{
    float* c = this->data.components;
    c[0] = e00;
    c[1] = e01;
    c[2] = e10;
    c[3] = e11;
    c[4] = e20;
    c[5] = e21;
    c[6] = e30;
    c[7] = e31;
}

inline mat4x2& mat4x2::row( swizz2 const& row,
                            fvec4 const& val )
{
    return *this;
}

inline mat4x2& mat4x2::column( swizz4 const& col,
                               fvec2 const& val )
{
    return *this;
}

inline mat4x2 mat4x2::rows( fvec4 const& row1,
                            fvec4 const& row2)
{
    return *(new mat4x2());
}

inline mat4x2 mat4x2::columns( fvec2 const& col1,
                               fvec2 const& col2,
                               fvec2 const& col3,
                               fvec2 const& col4 )
{
    return *(new mat4x2());
}

inline mat4x3::mat4x3( float e00, float e10, float e20, float e30,
                       float e01, float e11, float e21, float e31,
                       float e02, float e12, float e22, float e32 )
{
    float* c = this->data.components;
    c[0] = e00;
    c[1] = e01;
    c[2] = e02;
    c[3] = e10;
    c[4] = e11;
    c[5] = e12;
    c[6] = e20;
    c[7] = e21;
    c[8] = e22;
    c[9] = e30;
    c[10] = e31;
    c[11] = e32;
}

inline mat4x3& mat4x3::row( swizz3 const& row,
                            fvec4 const& val )
{
    return *this;
}

inline mat4x3& mat4x3::column( swizz4 const& col,
                               fvec3 const& val )
{
    return *this;
}

inline mat4x3 mat4x3::rows( fvec4 const& row1,
                            fvec4 const& row2,
                            fvec4 const& row3 )
{
    return mat4x3();
}

inline mat4x3 mat4x3::columns( fvec3 const& col1,
                               fvec3 const& col2,
                               fvec3 const& col3,
                               fvec3 const& col4 )
{
    return mat4x3();
}

inline mat4::mat4( float e00, float e10, float e20, float e30,
                   float e01, float e11, float e21, float e31,
                   float e02, float e12, float e22, float e32,
                   float e03, float e13, float e23, float e33 )
{
    float* c = this->data.components;
    c[0] = e00;
    c[1] = e01;
    c[2] = e02;
    c[3] = e03;
    c[4] = e10;
    c[5] = e11;
    c[6] = e12;
    c[7] = e13;
    c[8] = e20;
    c[9] = e21;
    c[10] = e22;
    c[11] = e23;
    c[12] = e30;
    c[13] = e31;
    c[14] = e32;
    c[15] = e33;
}

inline mat4& mat4::row( swizz4 const& row,
                        fvec4 const& val )
{
    return *this;
}

inline mat4& mat4::column( swizz4 const& col,
                           fvec4 const& val )
{
    return *this;
}

inline mat4 mat4::rows( fvec4 const& row1,
                        fvec4 const& row2,
                        fvec4 const& row3,
                        fvec4 const& row4 )
{
    return *(new mat4());
}

inline mat4 mat4::columns( fvec4 const& col1,
                           fvec4 const& col2,
                           fvec4 const& col3,
                           fvec4 const& col4 )
{
    return *(new mat4());
}

}

#endif
