#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <exception>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <climits>
#include "../gUtility/datatypeinfo.hpp"
#include "../gVideo/gl_core_3_3.hpp"
#include "constant.hpp"

namespace gfx {
  
// Five basic graphics primitives
template< typename T > class scalar;
template< typename T > class vec2_t;
template< typename T > class vec3_t;
template< typename T > class vec4_t;
template< typename T > class qutn_t;

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
    typedef scalar<T>       scalar_t;
    typedef T               comp_t;
                            scalar();
                            scalar( comp_t x0 );
                            operator T() const;
                            operator T&();
    scalar_t&               operator=( scalar_t const& src );                      
    scalar_t&               operator=( comp_t const& src );
    scalar_t                operator+( scalar_t const& rhs ) const;
    scalar_t                operator-( scalar_t const& rhs ) const;
    scalar_t                operator*( scalar_t const& rhs ) const;
    scalar_t                operator/( scalar_t const& rhs ) const;
    scalar_t                operator+( comp_t const& rhs ) const;
    scalar_t                operator-( comp_t const& rhs ) const;
    scalar_t                operator*( comp_t const& rhs ) const;
    scalar_t                operator/( comp_t const& rhs ) const;
    template< typename U>
    friend std::ostream&    operator<<( std::ostream& out, scalar<U> const& src );
    virtual raw_map const   to_map() const;
protected:
  // A union is used to access the value in full or the bytes individually.
    union {
        comp_t          value;
        unsigned char   bytes[sizeof(comp_t)];
    } data;
};

// This macro is defined in datatypeinfo.hpp; it expands to a template
// specialization of the typeinfo class with a further template param.
// Type information for library classes is only generated when code uses
// the functionality.
template< typename T >
G_TYPE( scalar<T>, type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class vec2_t : public raw_mappable {
public:
    typedef T               comp_t;
                            vec2_t();
                            vec2_t( comp_t x0,
                                    comp_t x1 );
                            vec2_t( comp_t fill );
                            vec2_t( vec2_t<comp_t> const& src );
                            ~vec2_t();
    bool                    operator==( vec2_t<T> const& rhs ) const;
    bool                    operator!=( vec2_t<T> const& rhs ) const;
    vec2_t<T>&              operator=( vec2_t<T> const& rhs );
    comp_t&                 operator[]( size_t i );
    comp_t                  operator[]( size_t i ) const;
    comp_t&                 operator()( swizz2 const& x0 );
    comp_t                  operator()( swizz2 const& x0 ) const;
    vec2_t<T>               operator()( swizz2 const& x0,
                                        swizz2 const& x1 ) const;
    vec3_t<T>               operator()( swizz2 const& x0,
                                        swizz2 const& x1,
                                        swizz2 const& x2 ) const;
    vec4_t<T>               operator()( swizz2 const& x0,
                                        swizz2 const& x1,
                                        swizz2 const& x2,
                                        swizz2 const& x3 ) const;
    vec2_t<T>               operator+( vec2_t<T> const& rhs ) const;
    vec2_t<T>               operator-( vec2_t<T> const& rhs ) const;
    vec2_t<T>               operator*( vec2_t<T> const& rhs ) const;
    vec2_t<T>               operator*( comp_t rhs ) const;
    vec2_t<T>               operator/( vec2_t<T> const& rhs ) const;
    template< typename U > friend
    std::ostream&           operator<<( std::ostream& out,
                                        vec2_t<U> const& src );
    virtual raw_map const   to_map() const;
    template< typename U > friend   class mat2;
    template<typename D > friend
    vec2_t<D>               operator*( vec2_t<D> const& lhs,
                                       mat2<D> const& rhs );
    template<typename D > friend
    vec2_t<D>               operator*( D lhs,
                                       vec2_t<D> const& rhs );
    vec2_t<T>&              norm();
protected:
    union {
        comp_t          c[2];
        unsigned char   bytes[sizeof(T) * 2];
    } data;
};

template< typename T >
G_TYPE( vec2_t<T>, 2 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class vec3_t : public raw_mappable  {
public:
    typedef T               comp_t;
                            vec3_t();
                            vec3_t( comp_t x0,
                                    comp_t x1,
                                    comp_t x2 );
                            vec3_t( comp_t fill );
                            vec3_t( vec3_t<T> const& src );
                            ~vec3_t();
    bool                    operator==( vec3_t<T> const& rhs ) const;
    bool                    operator!=( vec3_t<T> const& rhs ) const;
    vec3_t<T>&              operator=( vec3_t<T> const& rhs );
    comp_t&                 operator[]( size_t i );
    comp_t                  operator[]( size_t i ) const;
    comp_t&                 operator()( swizz3 const& x0 );
    comp_t                  operator()( swizz3 const& x0 ) const;
    vec2_t<T>               operator()( swizz3 const& x0,
                                        swizz3 const& x1 ) const;
    vec3_t<T>               operator()( swizz3 const& x0,
                                        swizz3 const& x1,
                                        swizz3 const& x2 ) const;
    vec4_t<T>               operator()( swizz3 const& x0,
                                        swizz3 const& x1,
                                        swizz3 const& x2,
                                        swizz3 const& x3 ) const;
    vec3_t<T>               operator+( vec3_t<T> const& rhs ) const;
    vec3_t<T>               operator-( vec3_t<T> const& rhs ) const;
    vec3_t<T>               operator*( vec3_t<T> const& rhs ) const;
    vec3_t<T>               operator*( comp_t rhs ) const;
    vec3_t<T>               operator/( vec3_t<T> const& rhs ) const;

    template< typename U > friend
    std::ostream&           operator<<( std::ostream& out,
                                        vec3_t<U> const& src );
    virtual raw_map const   to_map() const;
    template< typename D > friend class mat3;
    template< typename D > friend
    vec3_t<D>               operator*( vec3_t<D> const& lhs,
                                       mat3<D> const& rhs );
    template< typename D > friend
    vec3_t<D>               operator*( D lhs,
                                       vec3_t<D> const& rhs );
    vec3_t<T>&              norm();
    vec3_t<T>&              cross( vec3_t<T> const& rhs );
protected:
    union {
        comp_t          c[3];
        unsigned char   bytes[sizeof(T) * 3];
    } data;

};

template< typename T >
G_TYPE( vec3_t<T>, 3 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class vec4_t : public raw_mappable  {
public:
    typedef T               comp_t;
                            vec4_t();
                            vec4_t( comp_t x0,
                                    comp_t x1,
                                    comp_t x2,
                                    comp_t x3 );
                            vec4_t( comp_t fill );
                            vec4_t( vec4_t<T> const& src );
                            ~vec4_t();
    bool                    operator==( vec4_t<T> const& rhs ) const;
    bool                    operator!=( vec4_t<T> const& rhs ) const;
    vec4_t<T>&              operator=( vec4_t<T> const& rhs );
    comp_t&                 operator[]( size_t i );
    comp_t                  operator[]( size_t i ) const;
    comp_t&                 operator()( swizz4 const& x0 );
    comp_t                  operator()( swizz4 const& x0 ) const;
    vec2_t<T>               operator()( swizz4 const& x0,
                                        swizz4 const& x1 ) const;
    vec3_t<T>               operator()( swizz4 const& x0,
                                        swizz4 const& x1,
                                        swizz4 const& x2 ) const;
    vec4_t<T>               operator()( swizz4 const& x0,
                                        swizz4 const& x1,
                                        swizz4 const& x2,
                                        swizz4 const& x3 ) const;
    vec4_t<T>               operator+( vec4_t<T> const& rhs ) const;
    vec4_t<T>               operator-( vec4_t<T> const& rhs ) const;
    vec4_t<T>               operator*( vec4_t<T> const& rhs ) const;
    vec4_t<T>               operator*( comp_t rhs ) const;
    vec4_t<T>               operator/( vec4_t<T> const& rhs ) const;
    template< typename U > friend
    std::ostream&           operator<<( std::ostream& out,
                                        vec4_t<U> const& src );
    virtual raw_map const   to_map() const;
    template< typename D > friend class mat4;
    template< typename D > friend
    vec4_t<D>               operator*( vec4_t<D> const& lhs,
                                       mat4<D> const& rhs );
    template< typename D > friend
    vec4_t<D>               operator*( D lhs,
                                       vec4_t<D> const& rhs );
    vec4_t<T>&              norm();
protected:
    union {
        comp_t          c[4];
        unsigned char   bytes[sizeof(T) * 4];
    } data;
};

template< typename T >
G_TYPE( vec4_t<T>, 4 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class qutn_t : public raw_mappable  {
public:
    typedef T               comp_t;
    
                            qutn_t();
                            qutn_t( comp_t ei,
                                  comp_t ej,
                                  comp_t ek,
                                  comp_t em );
                            qutn_t( comp_t fill );
                            qutn_t( qutn_t<T> const& src );
                            ~qutn_t();
                            
    static qutn_t<T>        pure( vec3_t<comp_t> const& point );
    static qutn_t<T>        rotation( mat3<T> const& rmat );
    static qutn_t<T>        rotation( vec3_t<T> const& axis,
                                      d_angle const& ang );
    
    bool                    operator==( qutn_t<T> const& rhs ) const;
    bool                    operator!=( qutn_t<T> const& rhs ) const;
    qutn_t<T>&              operator=( qutn_t<T> const& rhs );
    
    qutn_t<T>               operator+( qutn_t<T> const& rhs ) const;
    qutn_t<T>               operator-( qutn_t<T> const& rhs ) const;
    qutn_t<T>               operator*( qutn_t<T> const& rhs ) const;
    qutn_t<T>               operator/( qutn_t<T> const& rhs ) const;
    qutn_t<T>               operator-() const;
    
    comp_t&                 operator[]( size_t i );
    comp_t                  operator[]( size_t i ) const;
    comp_t&                 operator()( swizz4 const& e0 );
    comp_t                  operator()( swizz4 const& e0 ) const;
    
    qutn_t<T>&              norm();
    
    template< typename U >
    friend std::ostream&    operator<<( std::ostream& out, qutn_t<U> const& src );
    virtual raw_map const   to_map() const;
protected:
    union {
        comp_t          c[4];
        unsigned char   bytes[sizeof(T) * 4];
    } data;
};

// Here we instantiate all the datatypes that GLSL supports
// and provide typedef names.

typedef     vec4_t<float>           vec4;
typedef     vec3_t<float>           vec3;
typedef     vec2_t<float>           vec2;
typedef     scalar<float>           float32;
typedef     qutn_t<float>           qutn;

typedef     vec4_t<double>          dvec4;
typedef     vec3_t<double>          dvec3;
typedef     vec2_t<double>          dvec2;
typedef     scalar<double>          double64;
typedef     qutn_t<double>          dqutn;

typedef     vec4_t<int>             ivec4;
typedef     vec3_t<int>             ivec3;
typedef     vec2_t<int>             ivec2;
typedef     scalar<int>             int32;

typedef     vec4_t<short>           svec4;
typedef     vec3_t<short>           svec3;
typedef     vec2_t<short>           svec2;
typedef     scalar<short>           short16;

typedef     vec4_t<char>            cvec4;
typedef     vec3_t<char>            cvec3;
typedef     vec2_t<char>            cvec2;
typedef     scalar<char>            char8;

typedef     vec4_t<unsigned int>    uvec4;
typedef     vec3_t<unsigned int>    uvec3;
typedef     vec2_t<unsigned int>    uvec2;
typedef     scalar<unsigned int>    uint32;

typedef     vec4_t<unsigned short>  usvec4;
typedef     vec3_t<unsigned short>  usvec3;
typedef     vec2_t<unsigned short>  usvec2;
typedef     scalar<unsigned short>  ushort16;

typedef     vec4_t<unsigned char>   ucvec4;
typedef     vec3_t<unsigned char>   ucvec3;
typedef     vec2_t<unsigned char>   ucvec2;
typedef     scalar<unsigned char>   uchar8;

template< typename T >
class col2 {
public:
    typedef T   comp_t;
    
                col2( col2<comp_t> const& acol );
    col2&       operator=( col2<comp_t> const& acol );
    col2&       operator=( vec2_t<comp_t> const& avec );
    comp_t&     operator[]( size_t i );
    comp_t      operator[]( size_t i ) const;
                operator vec2_t<comp_t>() const;
    template< typename U > friend class mat2;
                ~col2();
    template< typename U > friend
    std::ostream&   operator<<( std::ostream& out,
                                col2<U> const& rhs );
private:
    col2( comp_t* col_adr, bool liveness );
    bool        live_handle;
    comp_t*     column;
};


template< typename T >
class col3 {
public:
    typedef T   comp_t;
    
                col3( col3<comp_t> const& acol );
    col3&       operator=( col3<comp_t> const& acol );
    col3&       operator=( vec3_t<comp_t> const& avec );
    comp_t&     operator[]( size_t i );
    comp_t      operator[]( size_t i ) const;
                operator vec3_t<comp_t>() const;
    template< typename U > friend class mat3;
                ~col3();
    template< typename U > friend
    std::ostream&   operator<<( std::ostream& out,
                                col3<U> const& rhs );
private:
    col3( comp_t* col_adr, bool liveness );
    bool        live_handle;
    comp_t*     column;
};


template< typename T >
class col4 {
public:
    typedef T   comp_t;
    
                col4( col4<comp_t> const& acol );
    col4&       operator=( vec4_t<comp_t> const& avec );
    col4&       operator=( col4<comp_t> const& acol );
    comp_t&     operator[]( size_t i );
    comp_t      operator[]( size_t i ) const;
                operator vec4_t<comp_t>() const;
    template< typename U > friend class mat4;
                ~col4();
    template< typename U > friend
    std::ostream&   operator<<( std::ostream& out,
                                col4<U> const& rhs );
private:
    col4( comp_t* col_adr, bool liveness );
    bool        live_handle;
    comp_t*     column;
};

/**
template< typename T >
class col {
public:
    typedef T       comp_t;
    
                    col();
                    col( T comp );
                    ~col();
    size_t          n_comp();
    col&            e( T comp );
    T&              next();
    T&              prev();

private:
    class node {
        T       value;
        node*   next;
    };
    node*   first;
    node*   cursor;
    size_t  n_comp;
    size_t  cur_idx;
}; */

template< typename T >
class mat : public raw_mappable {
public:
    typedef mat<T>          mat_t;
    typedef T               comp_t;

                            mat();
                            mat( mat_t const& copy );
                            mat( size_t new_n_cols,
                                 size_t new_n_rows );
    static mat_t            fill( size_t new_n_cols,
                                  size_t new_n_rows,
                                  comp_t const val );
    static mat_t            identity( size_t new_dim );
    virtual                 ~mat();
    size_t                  n_cols() const;
    size_t                  n_rows() const;
    size_t                  n_comp() const;
    bool                    operator==( mat_t const& rhs ) const;
    bool                    operator!=( mat_t const& rhs ) const;
    mat_t&                  operator=( mat_t const& rhs );
    comp_t&                 operator()( size_t col, size_t row );
    comp_t                  operator()( size_t col, size_t row ) const;
    mat_t                   operator+( mat_t const& rhs ) const;
    mat_t                   operator-( mat_t const& rhs ) const;
    mat_t                   operator*( mat_t const& rhs ) const;
    mat_t                   operator*( comp_t rhs );
    template< typename D >
    friend mat<D>           operator*( D lhs, mat<D> const& rhs );
    mat_t                   operator*( scalar<comp_t> rhs );
    template< typename D >
    friend mat<D>           operator*( scalar<D> lhs, mat<D> const& rhs );
    mat_t                   operator/( comp_t rhs );
    mat_t                   operator/( scalar<comp_t> rhs );
    mat_t&                  fill( comp_t const val );
    mat_t&                  transpose();
    virtual raw_map const   to_map() const;
protected:
    class mat_data {
    public:
        mat_t*                  owner;
        comp_t*                 c;
                                mat_data( mat_t* new_owner );
                                ~mat_data();
        mat_data*               clone();
        size_t                  n_bytes();
        unsigned char const*    bytes();
    };
    mat_data* data;
    size_t cols;
    size_t rows;
    size_t comp;
};

template< typename T >
class mat2 : public raw_mappable {
public:
    typedef mat2<T>                 mat2_t;
    typedef T                       comp_t;
    constexpr static size_t const   n_cols = 2;
    constexpr static size_t const   n_rows = 2;
    constexpr static size_t const   n_comp = 4;
    // Construction
                            mat2();
                            mat2( mat2 const& copy );
                            mat2( comp_t e00, comp_t e10,
                                  comp_t e01, comp_t e11 );
    // Named Construction
    static mat2_t           column_vectors( vec2_t<comp_t> const& col0,
                                            vec2_t<comp_t> const& col1 );
    static mat2_t           identity();
    static mat2_t           row_vectors( vec2_t<comp_t> const& row0,
                                         vec2_t<comp_t> const& row1 );
    static mat2_t           scale( comp_t sx,                            
                                   comp_t sy );
    static mat2_t           scale( vec2_t<comp_t> const& svec );
    static mat2_t           rotation( d_angle const& ang );
    // Comparison
    bool                    operator==( mat2_t const& rhs ) const;
    bool                    operator<( mat2_t const& rhs ) const;
    bool                    operator>( mat2_t const& rhs ) const;
    bool                    operator<=( mat2_t const& rhs ) const;
    bool                    operator>=( mat2_t const& rhs ) const;
    bool                    operator!=( mat2_t const& rhs ) const;
    // Arithmetic
    mat2_t                  operator+( mat2_t const& rhs );
    mat2_t                  operator-();
    mat2_t                  operator-( mat2_t const& rhs );
    mat2_t                  operator*( mat2_t const& rhs );
    vec2_t<comp_t>          operator*( vec2_t<comp_t> const& rhs );
    template<typename D >
    friend vec2_t<D>        operator*( vec2_t<D> const& lhs, mat2<D> const& rhs );
    mat2_t                  operator*( comp_t rhs );
    template< typename D >
    friend mat2<D>          operator*( D lhs, mat2<D> const& rhs );
    mat2_t                  operator/( comp_t rhs );
    // Mutatative Operators
    mat2_t&                 operator=( mat2_t const& rhs );
    col2<comp_t>            operator[]( size_t i );
    col2<comp_t>            operator[]( size_t i ) const;
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
    // Mutative Functions
    mat2_t&                 column( size_t col,
                                    vec2_t<comp_t> const& val );
    vec2_t<T>               column( size_t col ) const;
    mat2_t&                 columns( vec2_t<comp_t> const& col0,
                                     vec2_t<comp_t> const& col1 );
    mat2_t&                 fill( comp_t val );
    mat2_t&                 row( size_t row,
                                 vec2_t<comp_t> const& val );
    vec2_t<T>               row( size_t row ) const;
    mat2_t&                 rows( vec2_t<comp_t> const& row0,
                                  vec2_t<comp_t> const& row1 );
    mat2_t&                 transpose();
    // Utility
    virtual raw_map const   to_map() const;
protected:
    union {
        comp_t          c[4];
        unsigned char   bytes[sizeof(comp_t) * 4];
    } data;
};

template< typename T >
G_TYPE( mat2<T>, 4 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class mat3 : public raw_mappable {
public:
    typedef mat3<T>                 mat3_t;
    typedef T                       comp_t;
    constexpr static size_t const   n_cols = 3;
    constexpr static size_t const   n_rows = 3;
    constexpr static size_t const   n_comp = 9;
    // Construction
                            mat3();
                            mat3( mat3 const& copy );
                            mat3( comp_t e00, comp_t e10, comp_t e20,
                                  comp_t e01, comp_t e11, comp_t e21,
                                  comp_t e02, comp_t e12, comp_t e22 );
    // Named Construction
    static mat3_t           column_vectors( vec3_t<comp_t> const& col0,
                                            vec3_t<comp_t> const& col1,
                                            vec3_t<comp_t> const& col2 );
    static mat3_t           cross_product( vec3_t<comp_t> const& vec );
    static mat3_t           homogenize( mat2<comp_t> const& amat );
    static mat3_t           identity();
    static mat3_t           row_vectors( vec3_t<comp_t> const& row0,
                                         vec3_t<comp_t> const& row1,
                                         vec3_t<comp_t> const& row2 );
    static mat3_t           rotation( vec3_t<comp_t> const& axis,
                                      d_angle const& ang );
    static mat3_t           rotation( d_angle const& angx,
                                      d_angle const& angy,
                                      d_angle const& angz );
    static mat3_t           scale( comp_t sx,
                                   comp_t sy,
                                   comp_t sz );
    static mat3_t           scale( vec3_t<comp_t> const& svec );
    static mat3_t           scale( vec2_t<comp_t> const& svec );
    static mat3_t           square( vec3_t<comp_t> const& vec );
    static mat3_t           translate( comp_t tx,
                                       comp_t ty );
    static mat3_t           translate( vec2_t<comp_t> const& tvec );
    // Comparison
    bool                    operator==( mat3_t const& rhs ) const;
    bool                    operator<( mat3_t const& rhs ) const;
    bool                    operator>( mat3_t const& rhs ) const;
    bool                    operator<=( mat3_t const& rhs ) const;
    bool                    operator>=( mat3_t const& rhs ) const;
    bool                    operator!=( mat3_t const& rhs ) const;
    // Arithmetic
    mat3_t                  operator+( mat3_t const& rhs );
    mat3_t                  operator-();
    mat3_t                  operator-( mat3_t const& rhs );
    mat3_t                  operator*( mat3_t const& rhs );
    vec3_t<comp_t>          operator*( vec3_t<comp_t> const& rhs );
    template< typename D >
    friend vec3_t<D>        operator*( vec3_t<D> const& lhs, mat3<D> const& rhs );
    mat3_t                  operator*( comp_t rhs );
    template< typename D >
    friend mat3<D>          operator*( D lhs, mat3<D> const& rhs );
    mat3_t                  operator/( comp_t rhs );
    // Mutative Operators
    mat3_t&                 operator=( mat3_t const& rhs );
    col3<comp_t>            operator[]( size_t i );
    col3<comp_t>            operator[]( size_t i ) const;
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
    // Mutative Functions
    mat3_t&                 column( size_t col,
                                    vec3_t<comp_t> const& val );
    vec3_t<T>               column( size_t col ) const;
    mat3_t&                 columns( vec3_t<comp_t> const& col0,
                                     vec3_t<comp_t> const& col1,
                                     vec3_t<comp_t> const& col2 );
    mat3_t&                 fill( comp_t val );
    mat3_t&                 normalize();
    mat3_t&                 row( size_t row,
                                 vec3_t<comp_t> const& val );
    vec3_t<T>               row( size_t row ) const;
    
    mat3_t&                 rows( vec3_t<comp_t> const& row0,
                                  vec3_t<comp_t> const& row1,
                                  vec3_t<comp_t> const& row2 );
    mat3_t&                 transpose();
    // Utility
    virtual raw_map const   to_map() const;
protected:
    union {
        comp_t          c[9];
        unsigned char   bytes[sizeof(comp_t) * 9];
    } data;
};

template< typename T >
G_TYPE( mat3<T>, 9 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class mat4 : public raw_mappable {
public:
    typedef mat4<T>                 mat4_t;
    typedef T                       comp_t;
    constexpr static size_t const   n_cols = 4;
    constexpr static size_t const   n_rows = 4;
    constexpr static size_t const   n_comp = 16;
    
                            mat4();
                            mat4( mat4 const& copy );
                            mat4( comp_t e00, comp_t e10, comp_t e20, comp_t e30,
                                  comp_t e01, comp_t e11, comp_t e21, comp_t e31,
                                  comp_t e02, comp_t e12, comp_t e22, comp_t e32,
                                  comp_t e03, comp_t e13, comp_t e23, comp_t e33 );
    static mat4_t           identity();
    static mat4_t           row_vectors( vec4_t<comp_t> const& row0,
                                         vec4_t<comp_t> const& row1,
                                         vec4_t<comp_t> const& row2,
                                         vec4_t<comp_t> const& row3 );
    static mat4_t           column_vectors( vec4_t<comp_t> const& col0,
                                            vec4_t<comp_t> const& col1,
                                            vec4_t<comp_t> const& col2,
                                            vec4_t<comp_t> const& col3 );
    static mat4_t           square( vec4_t<comp_t> const& vec );
    static mat4_t           homogenize( mat3<comp_t> const& amat );
    static mat4_t           scale( comp_t sx,
                                   comp_t sy,
                                   comp_t sz );
    static mat4_t           scale( vec3_t<comp_t> const& svec );
    static mat4_t           translate( comp_t tx,
                                       comp_t ty,
                                       comp_t tz );          
    static mat4_t           translate( vec3_t<comp_t> const& tvec ); 
    static mat4_t           cross_product( vec3_t<comp_t> const& vec );
    static mat4_t           perspective( double fovY,
                                         double aspect,
                                         double near,
                                         double far );
    static mat4_t           rotation( vec3_t<comp_t> const& axis,
                                      d_angle const& ang );
    static mat4_t           rotation( d_angle const& angx,
                                      d_angle const& angy,
                                      d_angle const& angz );
    bool                    operator==( mat4_t const& rhs ) const;
    bool                    operator<( mat4_t const& rhs ) const;
    bool                    operator>( mat4_t const& rhs ) const;
    bool                    operator<=( mat4_t const& rhs ) const;
    bool                    operator>=( mat4_t const& rhs ) const;
    bool                    operator!=( mat4_t const& rhs ) const;
    mat4_t&                 operator=( mat4_t const& rhs );
    col4<comp_t>            operator[]( size_t i );
    col4<comp_t>            operator[]( size_t i ) const;
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
    mat4_t                  operator+( mat4_t const& rhs );
    mat4_t                  operator-();
    mat4_t                  operator-( mat4_t const& rhs );
    mat4_t                  operator*( mat4_t const& rhs );
    vec4_t<comp_t>            operator*( vec4_t<comp_t> const& rhs );
    template< typename D >
    friend vec4_t<D>          operator*( vec4_t<D> const& lhs, mat4<D> const& rhs );
    mat4_t                  operator*( comp_t rhs );
    template< typename D >
    friend mat4<D>          operator*( D lhs, mat4<D> const& rhs );
    mat4_t                  operator/( comp_t rhs );
    mat4_t&                 fill( comp_t val );
    mat4_t&                 transpose();
    mat4_t&                 row( size_t row,
                                 vec4_t<comp_t> const& val );
    vec4_t<T>                 row( size_t row ) const;
    mat4_t&                 column( size_t col,
                                    vec4_t<comp_t> const& val );
    vec4_t<T>                 column( size_t col ) const;
    mat4_t&                 rows( vec4_t<comp_t> const& row0,
                                  vec4_t<comp_t> const& row1,
                                  vec4_t<comp_t> const& row2,
                                  vec4_t<comp_t> const& row3 );
    mat4_t&                 columns( vec4_t<comp_t> const& col0,
                                     vec4_t<comp_t> const& col1,
                                     vec4_t<comp_t> const& col2,
                                     vec4_t<comp_t> const& col3 );
    virtual raw_map const   to_map() const;
protected:
    union {
        comp_t          c[16];
        unsigned char   bytes[sizeof(comp_t) * 16];
    } data;
};

template< typename T >
G_TYPE( mat4<T>, 16 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

typedef     mat<float>              fmat;
typedef     mat2<float>             fmat2;
typedef     mat3<float>             fmat3;
typedef     mat4<float>             fmat4;

typedef     mat<double>              dmat;
typedef     mat2<double>             dmat2;
typedef     mat3<double>             dmat3;
typedef     mat4<double>             dmat4;

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
    static mat2x3_t     row_vectors( vec2_t<comp_t> const& row0,
                                     vec2_t<comp_t> const& row1,
                                     vec2_t<comp_t> const& row2 );
    static mat2x3_t     column_vectors( vec3_t<comp_t> const& col0,
                                        vec3_t<comp_t> const& col1 );
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
                             vec2_t<comp_t> const& val );
    vec2_t<T>             row( swizz3 const& row ) const;
    mat2x3_t&           column( swizz2 const& col,
                                vec3_t<comp_t> const& val );
    vec3_t<T>             column( swizz2 const& col ) const;
    mat2x3_t&           rows( vec2_t<comp_t> const& row0,
                              vec2_t<comp_t> const& row1,
                              vec2_t<comp_t> const& row2 );
    mat2x3_t&           columns( vec3_t<comp_t> const& col0,
                                 vec3_t<comp_t> const& col1 );
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
    static mat2x4_t     row_vectors( vec2_t<comp_t> const& row0,
                                     vec2_t<comp_t> const& row1,
                                     vec2_t<comp_t> const& row2,
                                     vec2_t<comp_t> const& row3 );
    static mat2x4_t     column_vectors( vec4_t<comp_t> const& col0,
                                        vec4_t<comp_t> const& col1 );
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
                             vec2_t<comp_t> const& val );
    vec2_t<T>             row( swizz4 const& row ) const;
    mat2x4_t&           column( swizz2 const& col,
                                vec4_t<comp_t> const& val );
    vec4_t<T>             column( swizz2 const& col ) const;
    mat2x4_t&           rows( vec2_t<comp_t> const& row0,
                              vec2_t<comp_t> const& row1,
                              vec2_t<comp_t> const& row2,
                              vec2_t<comp_t> const& row3 );
    mat2x4_t&           columns( vec4_t<comp_t> const& col0,
                                 vec4_t<comp_t> const& col1 );
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
    static mat3_t       row_vectors( vec3_t<comp_t> const& row0,
                                     vec3_t<comp_t> const& row1,
                                     vec3_t<comp_t> const& row2 );
    static mat3_t       column_vectors( vec3_t<comp_t> const& col0,
                                        vec3_t<comp_t> const& col1,
                                        vec3_t<comp_t> const& col2 );
    static mat3_t       scale( comp_t sx,
                               comp_t sy,
                               comp_t sz = lit<comp_t>.one );
    static mat3_t       scale( vec3_t<comp_t> const& svec );
    static mat3_t       scale( vec2_t<comp_t> const& svec );
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
                             vec3_t<comp_t> const& val );
    vec3_t<T>             row( swizz3 const& row ) const;
    mat3_t&             column( swizz3 const& col,
                                vec3_t<comp_t> const& val );
    vec3_t<T>             column( swizz3 const& col ) const;
    mat3_t&             rows( vec3_t<comp_t> const& row0,
                              vec3_t<comp_t> const& row1,
                              vec3_t<comp_t> const& row2 );
    mat3_t&             columns( vec3_t<comp_t> const& col0,
                                 vec3_t<comp_t> const& col1,
                                 vec3_t<comp_t> const& col2 );
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
    static mat4_t       row_vectors( vec4_t<comp_t> const& row0,
                                     vec4_t<comp_t> const& row1,
                                     vec4_t<comp_t> const& row2,
                                     vec4_t<comp_t> const& row3 );
    static mat4_t       column_vectors( vec4_t<comp_t> const& col0,
                                        vec4_t<comp_t> const& col1,
                                        vec4_t<comp_t> const& col2,
                                        vec4_t<comp_t> const& col3 );
    static mat4_t       scale( comp_t sx,
                               comp_t sy,
                               comp_t sz,
                               comp_t sw = lit<comp_t>.one );
    static mat4_t       scale( vec4_t<comp_t> const& svec );
    static mat4_t       scale( vec3_t<comp_t> const& svec );
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
                             vec4_t<comp_t> const& val );
    vec4_t<T>             row( swizz4 const& row ) const;
    mat4_t&             column( swizz4 const& col,
                                vec4_t<comp_t> const& val );
    vec4_t<T>             column( swizz4 const& col ) const;
    mat4_t&             rows( vec4_t<comp_t> const& row0,
                              vec4_t<comp_t> const& row1,
                              vec4_t<comp_t> const& row2,
                              vec4_t<comp_t> const& row3 );
    mat4_t&             columns( vec4_t<comp_t> const& col0,
                                 vec4_t<comp_t> const& col1,
                                 vec4_t<comp_t> const& col2,
                                 vec4_t<comp_t> const& col3 );
};*/

/**class mat2x3 : public mat<2,3,float> {
public:
    typedef mat<2,3,float>  base_t;
    
                            mat2x3() : base_t() {};
                            mat2x3( float e00, float e10,
                                    float e01, float e11,
                                    float e02, float e12 );
    mat2x3&                 row( swizz3 const& row,
                                 fvec2_t const& val );
    mat2x3&                 column( swizz2 const& row,
                                    fvec3_t const& val );
    static mat2x3           rows( fvec2_t const& row1,
                                  fvec2_t const& row2,
                                  fvec2_t const& row3 );
    static mat2x3           columns( fvec3_t const& col1,
                                     fvec3_t const& col2 );
    
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
                                 fvec2_t const& val );
    mat2x4&                 column( swizz2 const& row,
                                    fvec4_t const& val );
    static mat2x4           rows( fvec2_t const& row1,
                                  fvec2_t const& row2,
                                  fvec2_t const& row3,
                                  fvec2_t const& row4 );
    static mat2x4           columns( fvec4_t const& col1,
                                     fvec4_t const& col2 );
    
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
                                 fvec3_t const& val );
    mat3&                   column( swizz3 const& col,
                                    fvec3_t const& val );
    static mat3             rows( fvec3_t const& row1,
                                  fvec3_t const& row2,
                                  fvec3_t const& row3 );
    static mat3             columns( fvec3_t const& col1,
                                     fvec3_t const& col2,
                                     fvec3_t const& col3 );
    static mat3             translate( float tx,
                                       float ty );
    static mat3             translate( fvec2_t const& tvec );
    static mat3             scale( float sx,
                                   float sy );
    static mat3             scale( fvec2_t const& svec );
    static mat3             scale( float sx,
                                   float sy,
                                   float sz );
    static mat3             scale( fvec3_t const& svec );
    
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
                                 fvec3_t const& val );
    mat3x2&                 column( swizz3 const& row,
                                    fvec2_t const& val );
    static mat3x2           rows( fvec3_t const& row1,
                                  fvec3_t const& row2 );
    static mat3x2           columns( fvec2_t const& col1,
                                     fvec2_t const& col2,
                                     fvec2_t const& col3 );
    
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
                                 fvec3_t const& val );
    mat3x4&                 column( swizz3 const& row,
                                    fvec4_t const& val );
    static mat3x4           rows( fvec3_t const& row1,
                                  fvec3_t const& row2,
                                  fvec3_t const& row3,
                                  fvec3_t const& row4 );
    static mat3x4           columns( fvec4_t const& col1,
                                     fvec4_t const& col2,
                                     fvec4_t const& col3 );
    
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
                                 fvec4_t const& val );
    mat4&                   column( swizz4 const& col,
                                    fvec4_t const& val );
    static mat4             rows( fvec4_t const& row1,
                                  fvec4_t const& row2,
                                  fvec4_t const& row3,
                                  fvec4_t const& row4 );
    static mat4             columns( fvec4_t const& col1,
                                     fvec4_t const& col2,
                                     fvec4_t const& col3,
                                     fvec4_t const& col4 );
    static mat4             translate( float tx,
                                       float ty,
                                       float tz );
    static mat4             translate( fvec3_t const& tvec );
    static mat4             scale( float sx,
                                   float sy,
                                   float sz );
    static mat4             scale( fvec3_t const& svec );
    static mat4             scale( float sx,
                                   float sy,
                                   float sz,
                                   float sw );
    static mat4             scale( fvec4_t const& svec );
    
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
                                 fvec4_t const& val );
    mat4x2&                 column( swizz4 const& row,
                                    fvec2_t const& val );
    static mat4x2           rows( fvec4_t const& row1,
                                  fvec4_t const& row2 );
    static mat4x2           columns( fvec2_t const& col1,
                                     fvec2_t const& col2,
                                     fvec2_t const& col3,
                                     fvec2_t const& col4 );
    
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
                                 fvec4_t const& val );
    mat4x3&                 column( swizz4 const& row,
                                    fvec3_t const& val );
    static mat4x3           rows( fvec4_t const& row1,
                                  fvec4_t const& row2,
                                  fvec4_t const& row3 );
    static mat4x3           columns( fvec3_t const& col1,
                                     fvec3_t const& col2,
                                     fvec3_t const& col3,
                                     fvec3_t const& col4 );
    
    float&                  operator()( swizz4 col,
                                        swizz3 row );
    float                   operator()( swizz4 col,
                                        swizz3 row ) const;
}; */

class swizz4 {
    public:
                                    swizz4() : index(0) {};
        swizz4                      operator-() const {return swizz4(-index);}
        template< typename U > friend  class vec2_t;
        template< typename U > friend  class vec3_t;
        template< typename U > friend  class vec4_t;
        static swizz4               make_w() { return swizz4(4); }
        static swizz4               make_q() { return swizz4(4); }
        static swizz4               make_a() { return swizz4(4); }
        static swizz4               make_m() { return swizz4(4); }
        template< typename U > friend class qutn_t;
    protected:
                                    swizz4( int index ) : index(index){};
        int                         index;
};

class swizz3 : public swizz4 {
    public:
                                    swizz3() {};
        swizz3                      operator-() const {return swizz3(-index);}
        template< typename U > friend  class vec2_t;
        template< typename U > friend  class vec3_t;
        template< typename U > friend  class vec4_t;
        static swizz3               make_z() { return swizz3(3); }
        static swizz3               make_p() { return swizz3(3); }
        static swizz3               make_b() { return swizz3(3); }
        static swizz3               make_k() { return swizz3(3); }
        template< typename U > friend class qutn_t;
    protected:
                                    swizz3( int index ) : swizz4( index ) {};
};

class swizz2 : public swizz3 {
    public:
                                    swizz2() {};
        swizz2                      operator-() const {return swizz2(-index);}
        template< typename U > friend  class vec2_t;
        template< typename U > friend  class vec3_t;
        template< typename U > friend  class vec4_t;
        static swizz2               make_y() { return swizz2(2); }
        static swizz2               make_t() { return swizz2(2); }
        static swizz2               make_g() { return swizz2(2); }
        static swizz2               make_j() { return swizz2(2); }
        template< typename U > friend class qutn_t;
    protected:
                                    swizz2( int index ) : swizz3( index ) {};
};

class swizz1 : public swizz2 {
    public:
                                    swizz1() {};
        swizz1                      operator-() const {return swizz1(-index);}
        template< typename U > friend  class scalar;
        template< typename U > friend  class vec2_t;
        template< typename U > friend  class vec3_t;
        template< typename U > friend  class vec4_t;
        static swizz1               make_x() { return swizz1(1); }
        static swizz1               make_s() { return swizz1(1); }
        static swizz1               make_r() { return swizz1(1); }
        static swizz1               make_i() { return swizz1(1); }
        template< typename U > friend class qutn_t;
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
scalar<T>::operator T() const   { return data.value; }

template< typename T > inline
scalar<T>::operator T&()        { return data.value; }

template< typename T > inline
scalar<T>::scalar() : data( {cnst<T>::zero} ) {}

template< typename T > inline
scalar<T>::scalar( comp_t x0) : data( {x0} ) {}

template< typename T > inline
scalar<T>& scalar<T>::operator=( scalar<T> const& src )
{   this->data.value = src.data.value;
    return *this; }
    
template< typename T > inline
scalar<T>& scalar<T>::operator=( T const& src )
{   this->data.value = src;
    return *this; }

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

template< typename T > inline
vec2_t<T>::vec2_t() : data( {{0,0}} ) {};

template< typename T > inline
vec2_t<T>::vec2_t( comp_t x0,
                      comp_t x1 ) : data( {{ x0, x1 }} ) {}

template< typename T > inline
vec2_t<T>::vec2_t( comp_t fill ) : data( {{fill, fill}} ){}

template< typename T > inline
vec2_t<T>::vec2_t( vec2_t<T> const& src ) : data( {{ src.data.c[0], src.data.c[1] }} ) {}

template< typename T > inline   vec2_t<T>::~vec2_t() {}

template< typename T > inline
vec2_t<T>& vec2_t<T>::operator=( vec2_t<T> const& rhs )
{
    this->data.c[0] = rhs.data.c[0];
    this->data.c[1] = rhs.data.c[1];
    return *this;
}

template< typename T > inline
T&  vec2_t<T>::operator[]( size_t i )
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index out of range on vec2_t lookup" );
    }
    return data.c[i];
}

template< typename T > inline
T   vec2_t<T>::operator[]( size_t i ) const
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index out of range on vec2_t lookup" );
    }
    return data.c[i];    
}

template< typename T > inline
T&  vec2_t<T>::operator()( swizz2 const& x0 )
{
    switch( x0.index ){
      case 1:
          return data.c[0];
      case 2:
          return data.c[1];
      case -1:
      case -2:
          throw std::invalid_argument("Cannot modify c of a vec2_t with a negative index.");
      default:
          throw std::out_of_range("Component index on vec2_t out of range.");
    }
}

template< typename T > inline
T   vec2_t<T>::operator()( swizz2 const& x0 ) const
{
    switch( x0.index ){
      case 1:
          return data.c[0];
      case 2:
          return data.c[1];
      case -1:
          return -data.c[0];
      case -2:
          return -data.c[1];
      default:
          throw std::out_of_range("Component index on vec2_t out of range.");
    }
}

template< typename T > inline
vec2_t<T>     vec2_t<T>::operator()( swizz2 const& x0,
                                 swizz2 const& x1 ) const
{ return vec2_t( (*this)(x0), (*this)(x1) ); }

template< typename T > inline
vec3_t<T>     vec2_t<T>::operator()( swizz2 const& x0,
                                 swizz2 const& x1,
                                 swizz2 const& x2 ) const
                                 
{ return vec3_t<T>( (*this)(x0), (*this)(x1), (*this)(x2) ); }

template< typename T > inline
vec4_t<T>     vec2_t<T>::operator()( swizz2 const& x0,
                                 swizz2 const& x1,
                                 swizz2 const& x2,
                                 swizz2 const& x3 ) const
                                 
{ return vec4_t<T>( (*this)(x0), (*this)(x1), (*this)(x2), (*this)(x3) ); }

template< typename T > inline
vec2_t<T>     vec2_t<T>::operator+( vec2_t<T> const& rhs ) const

{ return vec2_t<T>( (*this)(x) + rhs(x), (*this)(y) + rhs(y) ); }

template< typename T > inline
vec2_t<T>     vec2_t<T>::operator-( vec2_t<T> const& rhs ) const

{ return vec2_t<T>( (*this)(x) - rhs(x), (*this)(y) - rhs(y) ); }

template< typename T > inline
vec2_t<T>     vec2_t<T>::operator*( vec2_t<T> const& rhs ) const
{
    return vec2_t<T>( (*this)(x) * rhs(x), (*this)(y) * rhs(y) );
}

template< typename T > inline
vec2_t<T>     vec2_t<T>::operator*( T rhs ) const
{
    return vec2_t<T>( this->data.c[0] * rhs,
                    this->data.c[1] * rhs );
}

template< typename T > inline
vec2_t<T>     operator*( T lhs, vec2_t<T> const& rhs )
{
    return vec2_t<T>( lhs * rhs.data.c[0],
                    lhs * rhs.data.c[1] );
}

template< typename T > inline
vec2_t<T>     vec2_t<T>::operator/( vec2_t<T> const& rhs ) const
{ return vec2_t<T>( (*this)(x) / rhs(x),
                  (*this)(y) / rhs(y) ); }

template<typename T> inline
bool    vec2_t<T>::operator==( vec2_t<T> const& rhs ) const
{
    return     std::abs(data.c[0] - rhs.data.c[0]) < cnst<T>::delta
           and std::abs(data.c[1] - rhs.data.c[1]) < cnst<T>::delta;
}

template<typename T> inline
bool    vec2_t<T>::operator!=( vec2_t<T> const& rhs ) const
{
    return    data.c[0] != rhs.data.c[0]
           or data.c[1] != rhs.data.c[1];
}

template< typename U > inline
std::ostream&   operator<<( std::ostream& out, vec2_t<U> const& src )
{
    out << '<' << src.data.c[0];
    out << ',' << src.data.c[1] << '>';
    return out;
}

template< typename T > inline
raw_map const   vec2_t<T>::to_map()   const
{
    return map_bytes( sizeof(T) * 2, data.bytes );
}

template< typename T > inline
vec2_t<T>&    vec2_t<T>::norm()
{
    float imag = 1.0 / sqrt(   this->data.c[0] * this->data.c[0]
                             + this->data.c[1] * this->data.c[1] );
    this->data.c[0] *= imag;
    this->data.c[1] *= imag;
    return *this;
}

/* We specialize for numeric types; other types are allowed to default
 * to whatever they default to. */

template< typename T > inline
vec3_t<T>::vec3_t() : data( {{0,0,0}} ) {};

template< typename T > inline
vec3_t<T>::vec3_t( comp_t x0,
               comp_t x1,
               comp_t x2 ) : data( {{ x0, x1, x2 }} ) {}

template< typename T > inline
vec3_t<T>::vec3_t( comp_t fill ) : data( {{fill, fill, fill}} ) {}

template< typename T > inline
vec3_t<T>::vec3_t( vec3_t<T> const& src ) : data( {{ src.data.c[0],
                                               src.data.c[1],
                                               src.data.c[2] }} ) {}

template< typename T > inline vec3_t<T>::~vec3_t() {}

template< typename T > inline
vec3_t<T>&    vec3_t<T>::operator=( vec3_t<T> const& rhs )
{
    (*this)(x) = rhs(x);
    (*this)(y) = rhs(y);
    (*this)(z) = rhs(z);
    return *this;
}

template< typename T > inline
T&     vec3_t<T>::operator[]( size_t i )
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index out of range on vec3_t lookup" );
    }
    return data.c[i];
}

template< typename T > inline
T     vec3_t<T>::operator[]( size_t i ) const
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index out of range on vec3_t lookup" );
    }
    return data.c[i];    
}

template< typename T > inline
T&  vec3_t<T>::operator()( swizz3 const& x0 )
{
    switch( x0.index ){
      case 1:
          return data.c[0];
      case 2:
          return data.c[1];
      case 3:
          return data.c[2];
      case -1:
      case -2:
      case -3:
          throw std::invalid_argument("Cannot modify c of a vec3_t with a negative index.");
      default:
          throw std::out_of_range("Component index on vec3_t out of range.");
    }
}

template< typename T > inline
T   vec3_t<T>::operator()( swizz3 const& x0 ) const
{
    switch( x0.index ){
      case 1:
          return data.c[0];
      case 2:
          return data.c[1];
      case 3:
          return data.c[2];
      case -1:
          return -data.c[0];
      case -2:
          return -data.c[1];
      case -3:
          return -data.c[2];
      default:
          throw std::out_of_range("Component index on vec3_t out of range.");
    }
}

template< typename T > inline
vec2_t<T>     vec3_t<T>::operator()( swizz3 const& x0,
                                 swizz3 const& x1 ) const
{ return vec2_t<T>( (*this)(x0), (*this)(x1) ); }

template< typename T > inline
vec3_t<T>     vec3_t<T>::operator()( swizz3 const& x0,
                                 swizz3 const& x1,
                                 swizz3 const& x2 ) const
{ return vec3_t( (*this)(x0), (*this)(x1), (*this)(x2) ); }

template< typename T > inline
vec4_t<T>     vec3_t<T>::operator()( swizz3 const& x0,
                                 swizz3 const& x1,
                                 swizz3 const& x2,
                                 swizz3 const& x3 ) const
{ return vec4_t<T>( (*this)(x0), (*this)(x1), (*this)(x2), (*this)(x3) ); }

template< typename T > inline
vec3_t<T>     vec3_t<T>::operator+( vec3_t<T> const& rhs ) const
{
    return vec3_t<T>( (*this)(x) + rhs(x),
                    (*this)(y) + rhs(y),
                    (*this)(z) + rhs(z) );
}

template< typename T >
inline vec3_t<T> vec3_t<T>::operator-( vec3_t<T> const& rhs ) const
{
    return vec3_t<T>( (*this)(x) - rhs(x),
                    (*this)(y) - rhs(y),
                    (*this)(z) - rhs(z) );
}
template< typename T >
inline vec3_t<T> vec3_t<T>::operator*( vec3_t<T> const& rhs ) const
{
    return vec3_t<T>( (*this)(x) * rhs(x),
                    (*this)(y) * rhs(y),
                    (*this)(z) * rhs(z) );
}
    
template< typename T >
inline vec3_t<T> vec3_t<T>::operator*( T rhs ) const
{
    return vec3_t<T>( this->data.c[0] * rhs,
                    this->data.c[1] * rhs,
                    this->data.c[2] * rhs );
}

template< typename T >
inline vec3_t<T> operator*( T lhs, vec3_t<T> const& rhs )
{
    return vec3_t<T>( lhs * rhs.data.c[0],
                    lhs * rhs.data.c[1],
                    lhs * rhs.data.c[2] );
}

template< typename T >
inline vec3_t<T> vec3_t<T>::operator/( vec3_t<T> const& rhs ) const
{
    return vec3_t<T>( (*this)(x) / rhs(x),
                    (*this)(y) / rhs(y),
                    (*this)(z) / rhs(z) );
}

template<typename T> inline
bool    vec3_t<T>::operator==( vec3_t<T> const& rhs ) const
{
    return     std::abs(data.c[0] - rhs.data.c[0]) < cnst<T>::delta
           and std::abs(data.c[1] - rhs.data.c[1]) < cnst<T>::delta
           and std::abs(data.c[2] - rhs.data.c[2]) < cnst<T>::delta;
}

template<typename T> inline
bool    vec3_t<T>::operator!=( vec3_t<T> const& rhs ) const
{
    return    data.c[0] != rhs.data.c[0]
           or data.c[1] != rhs.data.c[1]
           or data.c[2] != rhs.data.c[2];
}

template< typename U > inline
std::ostream&   operator<<( std::ostream& out, vec3_t<U> const& src )
{
    out << '<' << src.data.c[0];
    out << ',' << src.data.c[1];
    out << ',' << src.data.c[2] << '>';
    return out;
}

template< typename T > inline
raw_map const   vec3_t<T>::to_map()   const
{
    return map_bytes( sizeof(T) * 3, data.bytes );
}

template< typename T > inline
vec3_t<T>&    vec3_t<T>::norm()
{
    float imag = 1.0 / sqrt(   this->data.c[0] * this->data.c[0]
                             + this->data.c[1] * this->data.c[1]
                             + this->data.c[2] * this->data.c[2] );
    this->data.c[0] *= imag;
    this->data.c[1] *= imag;
    this->data.c[2] *= imag;
    return *this;
}

template< typename T > inline
vec3_t<T>&    vec3_t<T>::cross( vec3_t<T> const& rhs )
{
    T* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    T x0 = lhs_c[1]* rhs_c[2] - lhs_c[2] * rhs_c[1];
    T x1 = lhs_c[2]* rhs_c[0] - lhs_c[0] * rhs_c[2];
    T x2 = lhs_c[0]* rhs_c[1] - lhs_c[1] * rhs_c[0];
    
    lhs_c[0] = x0;
    lhs_c[1] = x1;
    lhs_c[2] = x2;
    return *this;
}


template< typename T >
inline vec4_t<T>::vec4_t() : data( {{ 0,0,0,0 }} ) {};

template< typename T > inline
vec4_t<T>::vec4_t( comp_t x0,
               comp_t x1,
               comp_t x2,
               comp_t x3 ) : data( {{ x0, x1, x2, x3 }} ) {}

template< typename T > inline
vec4_t<T>::vec4_t( comp_t fill ) : data( {{ fill, fill, fill, fill }} ) {}

template< typename T > inline
vec4_t<T>::vec4_t( vec4_t<T> const& src ) :
            data( {{ src.data.c[0],
                    src.data.c[1],
                    src.data.c[2],
                    src.data.c[3] }} ) {}

template< typename T > inline vec4_t<T>::~vec4_t() {}

template< typename T > inline
vec4_t<T>& vec4_t<T>::operator=( vec4_t<T> const& rhs )
{
    (*this)(x) = rhs(x);
    (*this)(y) = rhs(y);
    (*this)(z) = rhs(z);
    (*this)(w) = rhs(w);
    return *this;
}

template< typename T >
T&     vec4_t<T>::operator[]( size_t i )
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index out of range on vec4_t lookup" );
    }
    return data.c[i];
}

template< typename T >
T     vec4_t<T>::operator[]( size_t i ) const
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index out of range on vec4_t lookup" );
    }
    return data.c[i];
}

template< typename T >
inline T& vec4_t<T>::operator()( swizz4 const& x0 )
{
    switch( x0.index ){
      case 1:
          return data.c[0];
      case 2:
          return data.c[1];
      case 3:
          return data.c[2];
      case 4:
          return data.c[3];
      case -1:
      case -2:
      case -3:
      case -4:
          throw std::invalid_argument("Cannot modify c of a vec4_t with a negative index.");
      default:
          throw std::out_of_range("Component index on vec4_t out of range.");
    }
}

template< typename T >
inline T vec4_t<T>::operator()( swizz4 const& x0 ) const
{
    switch( x0.index ){
      case 1:
          return data.c[0];
      case 2:
          return data.c[1];
      case 3:
          return data.c[2];
      case 4:
          return data.c[3];
      case -1:
          return -data.c[0];
      case -2:
          return -data.c[1];
      case -3:
          return -data.c[2];
      case -4:
          return -data.c[3];
      default:
          throw std::out_of_range("Component index on vec4_t out of range.");
    }
}

template< typename T >
inline vec2_t<T> vec4_t<T>::operator()( swizz4 const& x0,
                                    swizz4 const& x1 ) const
{
    return vec2_t<T>( (*this)(x0), (*this)(x1) );
}
template< typename T >
inline vec3_t<T> vec4_t<T>::operator()( swizz4 const& x0,
                                    swizz4 const& x1,
                                    swizz4 const& x2 ) const
{
    return vec3_t<T>( (*this)(x0), (*this)(x1), (*this)(x2) );
}
template< typename T >
inline vec4_t<T> vec4_t<T>::operator()( swizz4 const& x0,
                                    swizz4 const& x1,
                                    swizz4 const& x2,
                                    swizz4 const& x3 ) const
{
    return vec4_t<T>( (*this)(x0), (*this)(x1), (*this)(x2), (*this)(x3) );
}

template< typename T >
inline vec4_t<T> vec4_t<T>::operator+( vec4_t<T> const& rhs ) const
{
    return vec4_t<T>( (*this)(x) + rhs(x),
                    (*this)(y) + rhs(y),
                    (*this)(z) + rhs(z),
                    (*this)(w) + rhs(w) );
}

template< typename T >
inline vec4_t<T> vec4_t<T>::operator-( vec4_t<T> const& rhs ) const
{
    return vec4_t<T>( (*this)(x) - rhs(x),
                    (*this)(y) - rhs(y),
                    (*this)(z) - rhs(z),
                    (*this)(w) - rhs(w) );
}

template< typename T >
inline vec4_t<T> vec4_t<T>::operator*( vec4_t<T> const& rhs ) const
{
    return vec4_t<T>( (*this)(x) * rhs(x),
                    (*this)(y) * rhs(y),
                    (*this)(z) * rhs(z),
                    (*this)(w) * rhs(w) );
}

template< typename T >
inline vec4_t<T> vec4_t<T>::operator*( T rhs ) const
{
    return vec4_t<T>( this->data.c[0] * rhs,
                    this->data.c[1] * rhs,
                    this->data.c[2] * rhs,
                    this->data.c[3] * rhs );
}

template< typename T >
inline vec4_t<T> operator*( T lhs, vec4_t<T> const& rhs )
{
    return vec4_t<T>( lhs * rhs.data.c[0],
                    lhs * rhs.data.c[1],
                    lhs * rhs.data.c[2],
                    lhs * rhs.data.c[3] );
}

template< typename T >
inline vec4_t<T> vec4_t<T>::operator/( vec4_t<T> const& rhs ) const
{
    return vec4_t<T>( (*this)(x) / rhs(x),
                    (*this)(y) / rhs(y),
                    (*this)(z) / rhs(z),
                    (*this)(w) / rhs(w) );
}


template< typename T > inline
bool    vec4_t<T>::operator==( vec4_t<T> const& rhs ) const
{
    return     std::abs(data.c[0] - rhs.data.c[0]) < cnst<T>::delta
           and std::abs(data.c[1] - rhs.data.c[1]) < cnst<T>::delta
           and std::abs(data.c[2] - rhs.data.c[2]) < cnst<T>::delta
           and std::abs(data.c[3] - rhs.data.c[3]) < cnst<T>::delta;
}

template< typename T > inline
bool    vec4_t<T>::operator!=( vec4_t<T> const& rhs ) const
{
    return    data.c[0] != rhs.data.c[0]
           or data.c[1] != rhs.data.c[1]
           or data.c[2] != rhs.data.c[2]
           or data.c[3] != rhs.data.c[3];
}

template< typename U > inline
std::ostream&   operator<<( std::ostream& out, vec4_t<U> const& src )
{
    out << '<' << src.data.c[0];
    out << ',' << src.data.c[1];
    out << ',' << src.data.c[2];
    out << ',' << src.data.c[3] << '>';
    return out;
}

template< typename T > inline
raw_map const   vec4_t<T>::to_map()   const
{
    return map_bytes( sizeof(T) * 4, data.bytes );
}

template< typename T > inline
vec4_t<T>&    vec4_t<T>::norm()
{
    T* c = this->data.c;
    float imag = 1.0 / sqrt(   c[0] * c[0]
                             + c[1] * c[1]
                             + c[2] * c[2]
                             + c[3] * c[3] );
    c[0] *= imag;
    c[1] *= imag;
    c[2] *= imag;
    c[3] *= imag;
    return *this;
}

template< typename T > inline
qutn_t<T>::qutn_t()
{
    this->data.c[0] = cnst<T>::zero;
    this->data.c[1] = cnst<T>::zero;
    this->data.c[2] = cnst<T>::zero;
    this->data.c[3] = cnst<T>::one;
}

template< typename T > inline
qutn_t<T>::qutn_t( comp_t ei,
               comp_t ej,
               comp_t ek,
               comp_t em )
{
    this->data.c[0] = ei;
    this->data.c[1] = ej;
    this->data.c[2] = ek;
    this->data.c[3] = em;
}

template< typename T > inline
qutn_t<T>::qutn_t( T fill )
{
    this->data.c[0] = fill;
    this->data.c[1] = fill;
    this->data.c[2] = fill;
    this->data.c[3] = fill;
}

template< typename T > inline
qutn_t<T>::qutn_t( qutn_t<T> const& src )
{
    this->data.c[0] = src.data.c[0];
    this->data.c[1] = src.data.c[1];
    this->data.c[2] = src.data.c[2];
    this->data.c[3] = src.data.c[3];
}

template< typename T > inline
qutn_t<T>::~qutn_t() {}

template< typename T > inline
qutn_t<T>     qutn_t<T>::pure( vec3_t<T> const& point )
{
    return qutn_t( point[0], point[1], point[2], cnst<T>::zero );
}

template< typename T > inline
qutn_t<T>     qutn_t<T>::rotation( mat3<T> const& rmat )
{
    double trace = rmat(0,0) + rmat(1,1) + rmat(2,2) + 1.0;

    T q0;
    T q1;
    T q2;
    T q3;

    if( trace > 0.0 ) {
        double s = 0.5 / sqrt( trace );
        q0 = (rmat(1,2) - rmat(2,1)) * s;
        q1 = (rmat(2,0) - rmat(0,2)) * s;
        q2 = (rmat(0,1) - rmat(1,0)) * s;
        q3 = 0.25 / s;
    } else {
        if(     rmat(0,0) > rmat(1,1)
            and rmat(0,0) > rmat(2,2) ) {
            double s = 0.5 / sqrt( 1.0 + rmat(0,0) - rmat(1,1) - rmat(2,2));
            q0 = 0.5 * s;
            q1 = (rmat(1,0) + rmat(0,1)) * s;
            q2 = (rmat(2,0) + rmat(0,2)) * s;
            q3 = (rmat(2,1) + rmat(1,2)) * s;
        } else if (     rmat(1,1) > rmat(0,0)
                    and rmat(1,1) > rmat(2,2) ) {
            double s = 0.5 / sqrt( 1.0 + rmat(1,1) - rmat(0,0) - rmat(2,2));
            q0 = (rmat(1,0) + rmat(0,1)) * s;
            q1 = 0.5 * s;
            q2 = (rmat(2,1) + rmat(1,2)) * s;
            q3 = (rmat(2,0) + rmat(0,2)) * s;
        } else {
            double s = 0.5 / sqrt( 1.0 + rmat(2,2) - rmat(0,0) - rmat(1,1));
            q0 = (rmat(2,0) + rmat(0,2)) * s;
            q1 = (rmat(2,1) + rmat(1,2)) * s;
            q2 = 0.5 * s;
            q3 = (rmat(1,0) + rmat(0,1)) * s;
        }
    }
    
    return qutn_t( q0, q1, q2, q3 );
}

template< typename T > inline
qutn_t<T>     qutn_t<T>::rotation( vec3_t<T> const& axis,
                                   d_angle const& ang )
{
    double h_rads = ang.to_rads() * 0.5;
    vec3_t<T> n_axis = axis;
    n_axis.norm();
    double sin_h_rads = sin( h_rads );
    return qutn_t<T>( n_axis[0] * sin_h_rads,
                      n_axis[1] * sin_h_rads,
                      n_axis[2] * sin_h_rads,
                      cos( h_rads )           );
}

template< typename T > inline
bool    qutn_t<T>::operator==( qutn_t<T> const& rhs ) const
{
    return     std::abs(data.c[0] - rhs.data.c[0]) < cnst<T>::delta
           and std::abs(data.c[1] - rhs.data.c[1]) < cnst<T>::delta
           and std::abs(data.c[2] - rhs.data.c[2]) < cnst<T>::delta
           and std::abs(data.c[3] - rhs.data.c[3]) < cnst<T>::delta;
}

template< typename T > inline
bool    qutn_t<T>::operator!=( qutn_t<T> const& rhs ) const
{
    return    data.c[0] != rhs.data.c[0]
           or data.c[1] != rhs.data.c[1]
           or data.c[2] != rhs.data.c[2]
           or data.c[3] != rhs.data.c[3];
}

template< typename T > inline
qutn_t<T>&    qutn_t<T>::operator=( qutn_t<T> const& rhs )
{
    this->data.c[0] = rhs.data.c[0];
    this->data.c[1] = rhs.data.c[1];
    this->data.c[2] = rhs.data.c[2];
    this->data.c[3] = rhs.data.c[3];
    return *this;
}

template< typename T > inline
qutn_t<T>    qutn_t<T>::operator-() const
{
    return qutn_t( -this->data.c[0],
                 -this->data.c[1],
                 -this->data.c[2],
                  this->data.c[3] );
}

template< typename T >
T&     qutn_t<T>::operator[]( size_t i )
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index out of range on qutn_t lookup" );
    }
    return data.c[i];
}

template< typename T >
T     qutn_t<T>::operator[]( size_t i ) const
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index out of range on qutn_t lookup" );
    }
    return data.c[i];
}

template< typename T > inline 
T&  qutn_t<T>::operator()( swizz4 const& e0 )
{
    switch( e0.index ){
      case 1:
          return data.c[0];
      case 2:
          return data.c[1];
      case 3:
          return data.c[2];
      case 4:
          return data.c[3];
      case -1:
      case -2:
      case -3:
      case -4:
          throw std::invalid_argument("Cannot modify c of a qutn_t with a negative index.");
      default:
          throw std::out_of_range("Component index on qutn_t out of range.");
    }
}

template< typename T > inline
T   qutn_t<T>::operator()( swizz4 const& e0 ) const
{
    switch( e0.index ){
      case 1:
          return data.c[0];
      case 2:
          return data.c[1];
      case 3:
          return data.c[2];
      case 4:
          return data.c[3];
      case -1:
          return -data.c[0];
      case -2:
          return -data.c[1];
      case -3:
          return -data.c[2];
      case -4:
          return -data.c[3];
      default:
          throw std::out_of_range("Component index on qutn_t out of range.");
    }
}

template< typename T > inline 
qutn_t<T> qutn_t<T>::operator+( qutn_t<T> const& rhs ) const
{
    return qutn_t<T>( this->data.c[0] + rhs.data.c[0],
                    this->data.c[1] + rhs.data.c[1],
                    this->data.c[2] + rhs.data.c[2],
                    this->data.c[3] + rhs.data.c[3]);
}

template< typename T > inline 
qutn_t<T> qutn_t<T>::operator-( qutn_t<T> const& rhs ) const
{
    return qutn_t<T>( this->data.c[0] - rhs.data.c[0],
                    this->data.c[1] - rhs.data.c[1],
                    this->data.c[2] - rhs.data.c[2],
                    this->data.c[3] - rhs.data.c[3]);
}

template< typename T > inline
qutn_t<T> qutn_t<T>::operator*( qutn_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    return qutn_t(   lhs_c[0] * rhs_c[3] + lhs_c[1] * rhs_c[2]
                 - lhs_c[2] * rhs_c[1] + lhs_c[3] * rhs_c[0],
                  -lhs_c[0] * rhs_c[2] + lhs_c[1] * rhs_c[3]
                 + lhs_c[2] * rhs_c[0] + lhs_c[3] * rhs_c[1],
                   lhs_c[0] * rhs_c[1] - lhs_c[1] * rhs_c[0]
                 + lhs_c[2] * rhs_c[3] + lhs_c[3] * rhs_c[2],
                   lhs_c[3] * rhs_c[3] - lhs_c[0] * rhs_c[0]
                 - lhs_c[1] * rhs_c[1] - lhs_c[2] * rhs_c[2] );
}

template< typename T > inline
qutn_t<T> qutn_t<T>::operator/( qutn_t<T> const& rhs ) const
{
    return (*this) * (-rhs);
}

template< typename T > inline
qutn_t<T>& qutn_t<T>::norm()
{
    T inv_mag = 1.0 / sqrt(   this->data.c[0] * this->data.c[0]
                            + this->data.c[1] * this->data.c[1]
                            + this->data.c[2] * this->data.c[2]
                            + this->data.c[3] * this->data.c[3] );
    this->data.c[0] *= inv_mag;
    this->data.c[1] *= inv_mag;
    this->data.c[2] *= inv_mag;
    this->data.c[3] *= inv_mag;
    
    return *this;
}

template< typename U > inline
std::ostream&   operator<<( std::ostream& out, qutn_t<U> const& src )
{
    out << "«" << src.data.c[0];
    out << ',' << src.data.c[1];
    out << ',' << src.data.c[2];
    out << ',' << src.data.c[3] << "»";
    return out;
}

template< typename T > inline
raw_map const   qutn_t<T>::to_map()   const
{
    return map_bytes( sizeof(T) * 4, data.bytes );
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
            a_mat.data.c[ c * n_r + r ] = rows[r][c];
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
            a_mat.data.c[ c * n_r + r ] = rows[c][r];
        }
    }
    
    return a_mat;
}*/

template< typename T > inline
col2<T>::col2( col2<T> const& acol )
{
    this->column = new T[2];
    this->column[0] = acol[0];
    this->column[1] = acol[1];
    live_handle = false;
}

template< typename T > inline
col2<T>&    col2<T>::operator=( vec2_t<T> const& avec )
{
    this->column[0] = avec[0];
    this->column[1] = avec[1];
    return *this;
}

template< typename T > inline
col2<T>&    col2<T>::operator=( col2<T> const& acol )
{
    this->column[0] = acol[0];
    this->column[1] = acol[1];
    return *this;
}

template< typename T > inline
T&      col2<T>::operator[]( size_t i )
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index on lookup of column vector out of range." );
    }
    
    return this->column[i];
}

template< typename T > inline
T       col2<T>::operator[]( size_t i ) const
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index on lookup of column vector out of range." );
    }
    
    return this->column[i];
}

template< typename T > inline
col2<T>::operator vec2_t<T>() const
{
    return vec2_t<T>( this->column[0], this->column[1] );
}

template< typename T > inline
col2<T>::~col2()
{
    if ( !live_handle ) { delete[] column; }
}

template< typename T > inline
col2<T>::col2( T* col_adr, bool liveness )
{ this->column = col_adr; this->live_handle = liveness; }

template< typename T > inline
std::ostream&   operator<<( std::ostream& out,
                            col2<T> const& rhs )
{
    out << "[ " << rhs[0] << " ]\n";
    out << "[ " << rhs[1] << " ]" << std::endl;
    return out;
}

template< typename T > inline
col3<T>::col3( col3<T> const& acol )
{
    this->column = new T[3];
    this->column[0] = acol[0];
    this->column[1] = acol[1];
    this->column[2] = acol[2];
    this->live_handle = false;
}

template< typename T > inline
col3<T>&    col3<T>::operator=( vec3_t<T> const& avec )
{
    this->column[0] = avec[0];
    this->column[1] = avec[1];
    this->column[2] = avec[2];
    return *this;
}

template< typename T > inline
col3<T>&    col3<T>::operator=( col3<T> const& acol )
{
    this->column[0] = acol[0];
    this->column[1] = acol[1];
    this->column[2] = acol[2];
    return *this;
}

template< typename T > inline
T&      col3<T>::operator[]( size_t i )
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index on lookup of column vector out of range." );
    }
    
    return this->column[i];
}

template< typename T > inline
T       col3<T>::operator[]( size_t i ) const
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index on lookup of column vector out of range." );
    }
    
    return this->column[i];
}

template< typename T > inline
col3<T>::operator vec3_t<T>() const
{
    return vec3_t<T>( this->column[0], this->column[1], this->column[2] );
}

template< typename T > inline
col3<T>::~col3()
{
    if ( !live_handle ) { delete[] column; }
}

template< typename T > inline
col3<T>::col3( T* col_adr, bool liveness )
{ this->column = col_adr; this->live_handle = liveness; }

template< typename T > inline
std::ostream&   operator<<( std::ostream& out,
                            col3<T> const& rhs )
{
    out << "[ " << rhs[0] << " ]\n";
    out << "[ " << rhs[1] << " ]\n";
    out << "[ " << rhs[2] << " ]" << std::endl;
    return out;
}

template< typename T > inline
col4<T>::col4( col4<T> const& acol )
{
    this->column = new T[4];
    this->column[0] = acol[0];
    this->column[1] = acol[1];
    this->column[2] = acol[2];
    this->column[3] = acol[3];
    this->live_handle = false;
}

template< typename T > inline
col4<T>&    col4<T>::operator=( vec4_t<T> const& avec )
{
    this->column[0] = avec[0];
    this->column[1] = avec[1];
    this->column[2] = avec[2];
    this->column[3] = avec[3];
    return *this;
}

template< typename T > inline
col4<T>&    col4<T>::operator=( col4<T> const& acol )
{
    this->column[0] = acol[0];
    this->column[1] = acol[1];
    this->column[2] = acol[2];
    this->column[3] = acol[3];
    return *this;
}

template< typename T > inline
T&      col4<T>::operator[]( size_t i )
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index on lookup of column vector out of range." );
    }
    
    return this->column[i];
}

template< typename T > inline
T       col4<T>::operator[]( size_t i ) const
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index on lookup of column vector out of range." );
    }
    
    return this->column[i];
}

template< typename T > inline
col4<T>::operator vec4_t<T>() const
{
    return vec4_t<T>( this->column[0], this->column[1],
                    this->column[2], this->column[3] );
}

template< typename T > inline
col4<T>::~col4()
{
    if ( !live_handle ) { delete[] column; }
}

template< typename T > inline
col4<T>::col4( T* col_adr, bool liveness )
{ this->column = col_adr; this->live_handle = liveness; }

template< typename T > inline
std::ostream&   operator<<( std::ostream& out,
                            col4<T> const& rhs )
{
    out << "[ " << rhs[0] << " ]\n";
    out << "[ " << rhs[1] << " ]\n";
    out << "[ " << rhs[2] << " ]\n";
    out << "[ " << rhs[3] << " ]" << std::endl;
    return out;
}

template< typename T > inline
mat<T>::mat() : cols( 1 ), rows( 1 ), comp( 1 )
{
    data = new mat_data( this );
    data->c[0] = cnst<T>::zero;
}

template< typename T > inline
mat<T>::mat( mat<T> const& copy)
           : cols( copy.cols ),
             rows( copy.rows ),
             comp( copy.comp )
{
    data = new mat_data( this );
    size_t i = comp;
    while( i ){
        --i;
        data->c[i] = copy.data->c[i];
    }
}

template< typename T >
mat<T>::mat( size_t new_n_cols, size_t new_n_rows )
           : cols( new_n_cols ), rows( new_n_rows ),
             comp( cols * rows )
{ // TODO Need to throw an exception when dimensions are zero
    data = new mat_data( this );
    size_t i = comp;
    while( i ){ data->c[--i] = cnst<T>::zero; }
}

template< typename T >
inline mat<T> mat<T>::fill( size_t new_n_cols, size_t new_n_rows,
                    comp_t const val )
{
    mat<T> out( new_n_cols, new_n_rows );
    
    size_t i = out.comp;
    T* out_cm = out.data->c;
    
    while(i) { out_cm[--i] = val; }
    
    return out;
}

template< typename T >
inline mat<T> mat<T>::identity( size_t new_dim )
{
    mat<T> a_mat( new_dim, new_dim );
    
    size_t i = new_dim;
    ++new_dim;
    
    // The indices of the diagonal c in the array have
    // the form:
    // i * (1 + d)
    // where:
    // i is the number of the diagonal component, starting at zero
    // d is the dimension of the square matrix
    // 'i' is initialized to the dimension and we loop with it, so it
    // is decremented each loop. new_dim is incremented once, ahead of time.
    while(i) { a_mat.data->c[ --i * new_dim ] = cnst<T>::one; }
    
    return a_mat;
}

template< typename T >
mat<T>::~mat() { delete data; }

template< typename T > inline
size_t      mat<T>::n_cols() const
{ return this->cols; }

template< typename T > inline
size_t      mat<T>::n_rows() const
{ return this->rows; }

template< typename T > inline
size_t      mat<T>::n_comp() const
{ return this->comp; }

template< typename T > inline
bool    mat<T>::operator==( mat<T> const& rhs ) const
{
    size_t i = comp;
    bool equal = true;
    if ( rows == rhs.rows and cols == rhs.cols ) {
        while (i) {
            --i;
            equal =     equal
                    and abs(data->c[i] - rhs.data->c[i]) < cnst<T>::delta;
        }
    } else {
        equal = false;
    }
    return equal;
}

template< typename T > inline
bool    mat<T>::operator!=( mat<T> const& rhs ) const
{
    size_t i = comp;
    bool not_equal = false;
    if ( rows == rhs.rows and cols == rhs.cols) {
        while(i){
            --i;
            not_equal = not_equal
                        or data->c[i]
                            != rhs.data->c[i];
            if ( not_equal ) { i = 0; }
        }
    } else {
        not_equal = true;
    }
    
    return not_equal;
}

template< typename T > inline
mat<T>&     mat<T>::operator=( mat<T> const& rhs)
{
    // Do we need to allocate new memory?
    if ( comp == rhs.comp ) {
        size_t i = comp;
        while(i){ --i; data->c[i] = rhs.data->c[i]; }
    // Damn, guess we do...        
    } else {
        
        // Dangling pointers are bad!
        mat_data* old_data = data;
        
        data = rhs.data->clone();
        data->owner = this;
        delete old_data;
    }
    rows = rhs.rows;
    cols = rhs.cols;
    comp = rhs.comp;
    return *this;
}

template< typename T >
inline T& mat<T>::operator()( size_t col, size_t row )
{ return data->c[col * rows + row]; }

template< typename T >
inline T mat<T>::operator()( size_t col, size_t row ) const
{ return data->c[col * rows + row]; }

template< typename T >
inline mat<T> mat<T>::operator+( mat<T> const& rhs ) const
{
    if( cols != rhs.cols || rows != rhs.rows ){
        throw std::invalid_argument("matrices not dimensionally similar on addition.");
    }
    
    mat<T> out( cols, rows );
    
    size_t i = comp;
    
    T const* lhs_c = data->c;
    T const* rhs_c = rhs.data->c;
    T* out_c = out.data->c;
    
    while(i) { --i; out_c[i] = lhs_c[i] + rhs_c[i]; }
    
    return out;
}

template< typename T >
inline mat<T> mat<T>::operator-( mat<T> const& rhs ) const
{
    if( cols != rhs.cols || rows != rhs.rows ){
        throw std::invalid_argument("matrices not dimensionally similar on addition.");
    }
    
    mat<T> out( cols, rows );
    
    size_t i = comp;
    
    T const* lhs_cm = data->c;
    T const* rhs_cm = rhs.data->c;
    T* out_cm = out.data->c;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] - rhs_cm[i]; }
    
    return out;
}

template< typename T >
inline mat<T> mat<T>::operator*( mat<T> const& rhs ) const
{   
    if( cols != rhs.rows ){
        throw std::invalid_argument("row, column mismatch on multiplication.");
    }
    
    size_t element = 0;
    size_t addend = 0;

    T val = cnst<T>::zero;

    mat<T> out( rhs.cols, rows );
    size_t n_cm = out.comp;
    
    T* lhs_cm = data->c;
    T* rhs_cm = rhs.data->c;
    T* out_cm = out.data->c;

    size_t rhs_nr = rhs.rows;

    for( element = 0; element < n_cm; ++element ){
        for( addend = 0; addend < rhs_nr; ++addend ){
            val += lhs_cm[ addend * rows + element % rows ]
                 * rhs_cm[ element / rows * rhs_nr + addend ];
        }
        out_cm[element] = val;
        val = cnst<T>::zero;
    }

    return out;
}

template< typename T >
inline mat<T> mat<T>::operator*( T rhs )
{
    mat<T> out( cols, rows );
    size_t i = comp;
    
    T* out_cm = out.data->c;
    T const* lhs_cm = data->c;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] * rhs; }
    
    return out;
}

template< typename T >
inline mat<T> operator*( T lhs, mat<T> const& rhs )
{
    mat<T> out( rhs.cols, rhs.rows );
    size_t i = rhs.comp;
    
    T* out_cm = out.data->c;
    T const* rhs_cm = rhs.data->c;
    
    while(i) { --i; out_cm[i] = rhs_cm[i] * lhs; }
    
    return out;
}

template< typename T >
inline mat<T> mat<T>::operator*( scalar<T> rhs )
{
    mat<T> out( cols, rows );
    size_t i = comp;
    
    T* out_cm = out.data->c;
    T const* lhs_cm = data->c;
    T factor = rhs;
    while(i) { --i; out_cm[i] = lhs_cm[i] * factor; }
    
    return out;
}

template< typename T >
inline mat<T> operator*( scalar<T> lhs, mat<T> const& rhs )
{
    mat<T> out( rhs.cols, rhs.rows );
    size_t i = rhs.comp;
    
    T* out_cm = out.data->c;
    T const* rhs_cm = rhs.data->c;
    T factor = lhs;
    
    while(i) { --i; out_cm[i] = rhs_cm[i] * factor; }
    
    return out;
}

template< typename T >
inline mat<T> mat<T>::operator/( T rhs )
{
    mat<T> out( cols, rows );
    size_t i = comp;
    
    T* out_cm = out.data->c;
    T const* lhs_cm = data->c;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] / rhs; }
    
    return out;
}

template< typename T >
inline mat<T> mat<T>::operator/( scalar<T> rhs )
{
    mat<T> out( cols, rows );
    size_t i = comp;
    
    T* out_cm = out.data->c;
    T const* lhs_cm = data->c;
    T factor = rhs;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] / factor; }
    
    return out;
}

template< typename T >
inline mat<T>& mat<T>::fill( comp_t const val )
{    
    size_t i = comp;
    T* cm = data->c;
    
    while(i) { cm[--i] = val; }
    
    return *this;
}

template< typename T >
mat<T>& mat<T>::transpose()
{    
    mat_data* new_data = new mat_data(this);
    T const* old_cm = data->c;
    T* new_cm = new_data->c;
    size_t i = comp;
    
    while(i) {
        --i;
        new_cm[(i % rows) * cols + i / rows] = old_cm[i];
    }
    
    mat_data* old_data = data;
    data = new_data;
    delete old_data;
    
    // Now we can swap the dimensions, and all is well
    size_t dummy = rows;
    rows = cols;
    cols = dummy;
    return *this;
}

template< typename T>
raw_map const mat<T>::to_map() const
{ return map_bytes( data->n_bytes(), data->bytes() ); }

template< typename T >
inline mat<T>::mat_data::mat_data( mat<T>* new_owner )
{
    this->owner = new_owner;
    if ( owner->comp > 0 ) {
        c = new comp_t[owner->comp];
    } else {
        c = 0;
    }
}

template< typename T >
inline mat<T>::mat_data::~mat_data()
{ 
    if( owner->comp > 0 ) { delete[] c; }
}

template< typename T >
typename mat<T>::mat_data* mat<T>::mat_data::clone()
{
    mat<T>::mat_data* new_clone;
    new_clone = new mat_data(this->owner);
    if ( owner->comp > 0 ) {
        size_t i = owner->comp;
        while(i) {
            --i;
            new_clone->c[i] = this->c[i];
        }
    } else {
        new_clone->c = 0;
    }
    return new_clone;
}

template< typename T >
inline size_t mat<T>::mat_data::n_bytes()
{ return owner->comp * sizeof( comp_t ); }

template< typename T >
inline unsigned char const* mat<T>::mat_data::bytes()
{ return (unsigned char*) c; }

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat<T> const& src )
{
    size_t i = 0;
    size_t j = 0;

    for( i = 0; i < src.n_rows(); ++i ){
        stream << "[ ";
        for( j = 0; j < src.n_cols(); ++j ){
            stream << src(j,i) << " ";
        }
        stream << "]";
        // this makes sure the formatting behaves like other types
        if( i + 1 != src.n_rows() && j + 1 != src.n_cols() ){
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
            comp_store = this->data.c[ i * n_r + j ];
            comp_store *= comp_store;
            inv_mag += comp_store;
        }
        
        inv_mag = 1.0 / std::sqrt( inv_mag );
        
        for( size_t j = 0; j < n_r; j++ ) {
            this->data.c[ i * n_r + j ] *= inv_mag;
        }
        
        inv_mag = 0.0;
    }
    return *this;
} */

// Construction

template< typename T > inline
mat2<T>::mat2()
{ T* c = this->data.c;
  c[0] = cnst<T>::zero;   c[2] = cnst<T>::zero;
  c[1] = cnst<T>::zero;   c[3] = cnst<T>::zero; }

template< typename T > inline
mat2<T>::mat2( mat2<T> const& copy )
{ T* c = this->data.c;
  c[0] = copy.data.c[0];
  c[1] = copy.data.c[1];
  c[2] = copy.data.c[2];
  c[3] = copy.data.c[3]; }
  
template< typename T >
mat2<T>::mat2( T e00, T e10,
               T e01, T e11 )
{ T* c = this->data.c;
  c[0] = e00;   c[2] = e10;
  c[1] = e01;   c[3] = e11; }

// Named Construction

template< typename T > inline
mat2<T>     mat2<T>::column_vectors( vec2_t<T> const& col0,
                                     vec2_t<T> const& col1 )
{ return mat2( col0(x), col1(x),
               col0(y), col1(y) ); }

template< typename T >
mat2<T>     mat2<T>::identity()
{ return mat2<T>( cnst<T>::one,  cnst<T>::zero,
                  cnst<T>::zero, cnst<T>::one   ); }

template< typename T > inline
mat2<T>     mat2<T>::row_vectors( vec2_t<T> const& row0,
                                  vec2_t<T> const& row1 )
{ return mat2( row0(x), row0(y),
               row1(x), row1(y) ); }

template< typename T > inline
mat2<T>     mat2<T>::scale( T sx, T sy )
{ return mat2( sx,           cnst<T>::zero,
               cnst<T>::zero, sy            ); }
               
template< typename T > inline
mat2<T>     mat2<T>::scale( vec2_t<T> const& svec )
{ return mat2( svec(x),      cnst<T>::zero,
               cnst<T>::zero, svec(y)       ); }

template< typename T > inline
mat2<T>   mat2<T>::rotation( d_angle const& ang )
{
     double radians ( ang.to_rads() );
     float cos_rad = std::cos( radians );
     float sin_rad = std::sin( radians );
     
     return mat2<T>( cos_rad, -sin_rad,
                     sin_rad, cos_rad );
}
               
// Comparison
               
template< typename T > inline
bool    mat2<T>::operator==( mat2<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     abs(lhs_c[0] - rhs_c[0]) < cnst<T>::delta
           and abs(lhs_c[1] - rhs_c[1]) < cnst<T>::delta
           and abs(lhs_c[2] - rhs_c[2]) < cnst<T>::delta
           and abs(lhs_c[3] - rhs_c[3]) < cnst<T>::delta;
}

template< typename T > inline
bool    mat2<T>::operator<( mat2<T> const& rhs ) const
{
    T* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    return     lhs_c[0] < rhs_c[0]
           and lhs_c[1] < rhs_c[1]
           and lhs_c[2] < rhs_c[2]
           and lhs_c[3] < rhs_c[3];
}

template< typename T > inline
bool    mat2<T>::operator>( mat2<T> const& rhs ) const
{
    T* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    return     lhs_c[0] > rhs_c[0]
           and lhs_c[1] > rhs_c[1]
           and lhs_c[2] > rhs_c[2]
           and lhs_c[3] > rhs_c[3];
}

template< typename T > inline
bool    mat2<T>::operator<=( mat2<T> const& rhs ) const
{
    T* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    return     lhs_c[0] <= rhs_c[0]
           and lhs_c[1] <= rhs_c[1]
           and lhs_c[2] <= rhs_c[2]
           and lhs_c[3] <= rhs_c[3];
}

template< typename T > inline
bool    mat2<T>::operator>=( mat2<T> const& rhs ) const
{
    T* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    return     lhs_c[0] >= rhs_c[0]
           and lhs_c[1] >= rhs_c[1]
           and lhs_c[2] >= rhs_c[2]
           and lhs_c[3] >= rhs_c[3];
}

template< typename T > inline
bool    mat2<T>::operator!=( mat2<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     lhs_c[0] != rhs_c[0]
           or lhs_c[1] != rhs_c[1]
           or lhs_c[2] != rhs_c[2]
           or lhs_c[3] != rhs_c[3];
}

// Arithmetic

template< typename T > inline
mat2<T>     mat2<T>::operator+( mat2<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] + rhs_c[0];
    T e01 = lhs_c[1] + rhs_c[1];
    T e10 = lhs_c[2] + rhs_c[2];
    T e11 = lhs_c[3] + rhs_c[3];
    
    return mat2( e00, e10,
                 e01, e11 );
}

template< typename T > inline
mat2<T>     mat2<T>::operator-()
{
    T const* lhs_c = this->data.c;
    
    T e00 = -lhs_c[0];
    T e01 = -lhs_c[1];
    T e10 = -lhs_c[2];
    T e11 = -lhs_c[3];
    
    return mat2( e00, e10,
                 e01, e11 );
}

template< typename T > inline
mat2<T>     mat2<T>::operator-( mat2<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] - rhs_c[0];
    T e01 = lhs_c[1] - rhs_c[1];
    T e10 = lhs_c[2] - rhs_c[2];
    T e11 = lhs_c[3] - rhs_c[3];
    
    return mat2( e00, e10,
                 e01, e11 );
}
               
template< typename T > inline
mat2<T>     mat2<T>::operator*( mat2<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1];
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[2] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[3] * rhs_c[3];
    
    return mat2( e00, e10,
                 e01, e11 );
}

template< typename T > inline
vec2_t<T>     mat2<T>::operator*( vec2_t<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T x0 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1];
    T x1 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1];
    
    return vec2_t<T>( x0, x1 );
}

template< typename T > inline
vec2_t<T>     operator*( vec2_t<T> const& lhs,
                       mat2<T> const& rhs )
{
    T const* lhs_c = lhs.data.c;
    T const* rhs_c = rhs.data.c;
    
    T x0 = lhs_c[0] * rhs_c[0] + lhs_c[1] * rhs_c[1];
    T x1 = lhs_c[0] * rhs_c[2] + lhs_c[1] * rhs_c[3];
    
    return vec2_t<T>( x0, x1 );
}
template< typename T >
mat2<T>     mat2<T>::operator*( T rhs )
{
    T const* rhs_c = this->data.c;
    
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
    D const* rhs_c = rhs.data.c;
    
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
    T const* rhs_c = this->data.c;
    
    T e00 = rhs_c[0] / rhs;
    T e01 = rhs_c[1] / rhs;
    T e10 = rhs_c[2] / rhs;
    T e11 = rhs_c[3] / rhs;
    
    return mat2( e00, e10,
                 e01, e11 );
}

// Mutative Operatores

template< typename T > inline
mat2<T>&    mat2<T>::operator=( mat2<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    lhs_c[0] = rhs_c[0];
    lhs_c[1] = rhs_c[1];
    lhs_c[2] = rhs_c[2];
    lhs_c[3] = rhs_c[3];
    return *this;
}

template< typename T > inline
col2<T>     mat2<T>::operator[]( size_t i )
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat2 out of range" );
    }
    
    return col2<T>( this->data.c + (2*i), true );
}

template< typename T > inline
col2<T>     mat2<T>::operator[]( size_t i ) const
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat2 out of range" );
    }
    
    T* col_cpy = new T[2];
    
    col_cpy[0] = this-data->c[ 2 * i ];
    col_cpy[1] = this-data->c[ 2 * i + 1 ];
    
    return col2<T>( col_cpy, false );
}

template< typename T > inline
T&     mat2<T>::operator()( size_t col,
                            size_t row )
{
    if ( col > 1 or row > 1 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat2 used out of bounds index");
    }
    
    return this->data.c[col * 2 + row];
}

template< typename T > inline
T      mat2<T>::operator()( size_t col,
                            size_t row ) const
{
    if ( col > 1 or row > 1 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat2 used out of bounds index");
    }
    
    return this->data.c[col * 2 + row];
}

// Mutative Functions

template< typename T > inline
mat2<T>&    mat2<T>::column( size_t col,
                             vec2_t<T> const& val )
{
    switch( col ){
        case 0:
            this->data.c[0] = val(x);
            this->data.c[1] = val(y);
            break;
        case 1:
            this->data.c[2] = val(x);
            this->data.c[3] = val(y);
            break;
        default:
          throw std::out_of_range("Component index on mat2 out of range.");
    }
    return *this;
}

template< typename T > inline
vec2_t<T>     mat2<T>::column( size_t col ) const
{
    T out_x, out_y;
    switch( col ){
        case 0:
            out_x = this->data.c[0];
            out_y = this->data.c[1];
            break;
        case 1:
            out_x = this->data.c[2];
            out_y = this->data.c[3];
            break;
        default:
          throw std::out_of_range("Component index on mat2 out of range.");
    }
    return vec2_t<T>(out_x, out_y);
}

template< typename T > inline
mat2<T>&    mat2<T>::columns( vec2_t<T> const& col0,
                              vec2_t<T> const& col1 )
{
    T* cm = this->data.c;
    
    cm[0] = col0(x);
    cm[1] = col0(y);
    cm[2] = col1(x);
    cm[3] = col1(y);
    
    return *this;
}

template< typename T >
mat2<T>& mat2<T>::fill( T val )
{
    T* c = this->data.c;
    c[0] = val;
    c[1] = val;
    c[2] = val;
    c[3] = val;
    return *this;
}

template< typename T > inline
mat2<T>&    mat2<T>::row( size_t row,
                          vec2_t<T> const& val )
{
    switch( row ){
        case 0:
            this->data.c[0] = val(x);
            this->data.c[2] = val(y);
            break;
        case 1:
            this->data.c[1] = val(x);
            this->data.c[3] = val(y);
            break;
        default:
          throw std::out_of_range("Component index on mat2 out of range.");
    }
          
    return *this;
}

template< typename T > inline
vec2_t<T>     mat2<T>::row( size_t row ) const
{
    T out_x, out_y;
    switch( row ){
        case 0:
            out_x = this->data.c[0];
            out_y = this->data.c[2];
            break;
        case 1:
            out_x = this->data.c[1];
            out_y = this->data.c[3];
            break;
        default:
          throw std::out_of_range("Component index on mat2 out of range.");
    }
    return vec2_t<T>(out_x, out_y);
}

template< typename T >
inline mat2<T>& mat2<T>::rows( vec2_t<T> const& row0,
                               vec2_t<T> const& row1 )
{
    T* cm = this->data.c;
    
    cm[0] = row0(x);
    cm[2] = row0(y);
    cm[1] = row1(x);
    cm[3] = row1(y);
    
    return *this;
}

template< typename T >
mat2<T>& mat2<T>::transpose()
{
    T* c = this->data.c;
    T swap = c[2];
    c[2] = c[1];
    c[1] = swap;
    return *this;
}

// Utility

template< typename T > inline
raw_map const   mat2<T>::to_map() const
{
    return map_bytes( sizeof(T) * 4, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat2<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " ]" << std::endl;
    return stream;
}

// --------- MAT 3X3 -------------

// Construction
template< typename T > inline
mat3<T>::mat3()
{ T* c = this->data.c;
  c[0] = cnst<T>::zero;   c[3] = cnst<T>::zero; c[6] = cnst<T>::zero;
  c[1] = cnst<T>::zero;   c[4] = cnst<T>::zero; c[7] = cnst<T>::zero;
  c[2] = cnst<T>::zero;   c[5] = cnst<T>::zero; c[8] = cnst<T>::zero; }

template< typename T > inline
mat3<T>::mat3( mat3<T> const& copy )
{ T const* cpy = copy.data.c;
  T* c = this->data.c;
  c[0] = cpy[0];   c[3] = cpy[3]; c[6] = cpy[6];
  c[1] = cpy[1];   c[4] = cpy[4]; c[7] = cpy[7];
  c[2] = cpy[2];   c[5] = cpy[5]; c[8] = cpy[8]; }
  
template< typename T >
mat3<T>::mat3( T e00, T e10, T e20, 
               T e01, T e11, T e21,
               T e02, T e12, T e22 )
{ T* c = this->data.c;
  c[0] = e00;   c[3] = e10;   c[6] = e20;
  c[1] = e01;   c[4] = e11;   c[7] = e21;
  c[2] = e02;   c[5] = e12;   c[8] = e22; }

// Named Construction
  
template< typename T > inline
mat3<T>     mat3<T>::column_vectors( vec3_t<T> const& col0,
                                     vec3_t<T> const& col1,
                                     vec3_t<T> const& col2 )
{ return mat3( col0(x), col1(x), col2(x),
               col0(y), col1(y), col2(y),
               col0(z), col1(z), col2(z) ); }
               
template< typename T > inline
mat3<T>     mat3<T>::cross_product( vec3_t<T> const& vec )
{ return mat3<T>( cnst<T>::zero, vec(-z),      vec(y),
                  vec(z),       cnst<T>::zero, vec(-x),
                  vec(-y),      vec(x),       cnst<T>::zero ); }
                  
template< typename T > inline
mat3<T>     mat3<T>::homogenize( mat2<T> const& amat )
{ return mat3( amat(0,0),    amat(1,0),    cnst<T>::zero,
               amat(0,1),    amat(1,1),    cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::one  ); }

template< typename T >
mat3<T>     mat3<T>::identity()
{ return mat3( cnst<T>::one,  cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, cnst<T>::one,  cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::one ); }
  
template< typename T > inline
mat3<T>     mat3<T>::row_vectors( vec3_t<T> const& row0,
                                  vec3_t<T> const& row1,
                                  vec3_t<T> const& row2 )
{ return mat3( row0(x), row0(y), row0(z),
               row1(x), row1(y), row1(z),
               row2(x), row2(y), row2(z) ); }
               
template< typename T > inline
mat3<T>     mat3<T>::rotation( vec3_t<T> const& axis,
                               d_angle const& ang )
{
    double radians = ang.to_rads();
    double cos_t ( cos( radians ) );
    double cm_cos_t ( 1.0 - cos_t );
    return   mat3<T>::identity() * cos_t
           + mat3<T>::square( axis ) * cm_cos_t
           + mat3<T>::cross_product( axis ) * sin( radians );
}

template< typename T > inline
mat3<T>     mat3<T>::rotation( d_angle const& angx,
                               d_angle const& angy,
                               d_angle const& angz )
{
    double radx ( angx.to_rads() );
    double rady ( angy.to_rads() );
    double radz ( angz.to_rads() );
    
    double sin_x = std::sin( radx );
    double cos_x = std::cos( radx );
    double sin_y = std::sin( rady );
    double cos_y = std::cos( rady );
    double sin_z = std::sin( radz );
    double cos_z = std::cos( radz );
    
    return mat3<T>(
        cos_y*cos_z,                     -cos_y*sin_z,                      sin_y,
        cos_x*sin_z + sin_x*sin_y*cos_z,  cos_x*cos_z - sin_x*sin_y*sin_z, -sin_x*cos_y,
        sin_x*sin_z - cos_x*sin_y*cos_z,  sin_x*cos_z + cos_x*sin_y*sin_z,  cos_x*cos_y
      );
    
}

template< typename T > inline
mat3<T>     mat3<T>::scale( T sx, T sy, T sz = 1.0f )
{ return mat3( sx,           cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, sy,           cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, sz            ); }
               
template< typename T > inline
mat3<T>     mat3<T>::scale( vec3_t<T> const& svec )
{ return mat3( svec(x),      cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, svec(y),      cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, svec(z)       ); }
               
template< typename T > inline
mat3<T>     mat3<T>::scale( vec2_t<T> const& svec )
{ return mat3( svec(x),      cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, svec(y),      cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::one  ); }
               
template< typename T > inline
mat3<T>     mat3<T>::square( vec3_t<T> const& vec )
{ return mat3( vec[0] * vec[0], vec[0] * vec[1], vec[0] * vec[2],
               vec[1] * vec[0], vec[1] * vec[1], vec[1] * vec[2],
               vec[2] * vec[0], vec[2] * vec[1], vec[2] * vec[2]  ); }
               
template< typename T > inline
mat3<T>     mat3<T>::translate( T tx, T ty )
{ return mat3( cnst<T>::one,  cnst<T>::zero, tx,
               cnst<T>::zero, cnst<T>::one,  ty,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::one ); }
               
template< typename T > inline
mat3<T>     mat3<T>::translate( vec2_t<T> const& tvec )
{ return mat3( cnst<T>::one,  cnst<T>::zero, tvec(x),
               cnst<T>::zero, cnst<T>::one,  tvec(y),
               cnst<T>::zero, cnst<T>::zero, cnst<T>::one ); }
               
// Comparison

template< typename T > inline
bool    mat3<T>::operator==( mat3<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs(lhs_c[0] - rhs_c[0]) < cnst<T>::delta
           and std::abs(lhs_c[1] - rhs_c[1]) < cnst<T>::delta
           and std::abs(lhs_c[2] - rhs_c[2]) < cnst<T>::delta
           and std::abs(lhs_c[3] - rhs_c[3]) < cnst<T>::delta
           and std::abs(lhs_c[4] - rhs_c[4]) < cnst<T>::delta
           and std::abs(lhs_c[5] - rhs_c[5]) < cnst<T>::delta
           and std::abs(lhs_c[6] - rhs_c[6]) < cnst<T>::delta
           and std::abs(lhs_c[7] - rhs_c[7]) < cnst<T>::delta
           and std::abs(lhs_c[8] - rhs_c[8]) < cnst<T>::delta;
}

template< typename T > inline
bool    mat3<T>::operator<( mat3<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
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
bool    mat3<T>::operator>( mat3<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
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
bool    mat3<T>::operator<=( mat3<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
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
bool    mat3<T>::operator>=( mat3<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
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
bool    mat3<T>::operator!=( mat3<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     lhs_c[0] != rhs_c[0]
           or lhs_c[1] != rhs_c[1]
           or lhs_c[2] != rhs_c[2]
           or lhs_c[3] != rhs_c[3]
           or lhs_c[4] != rhs_c[4]
           or lhs_c[5] != rhs_c[5]
           or lhs_c[6] != rhs_c[6]
           or lhs_c[7] != rhs_c[7]
           or lhs_c[8] != rhs_c[8];
}

// Arithmetic


template< typename T > inline
mat3<T>     mat3<T>::operator+( mat3<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
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
    T const* lhs_c = this->data.c;
    
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
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
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
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
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
    T const* rhs_c = this->data.c;
    
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
    D const* rhs_c = rhs.data.c;
    
    D e00 = rhs_c[0] * lhs;
    D e01 = rhs_c[1] * lhs;
    D e02 = rhs_c[2] * lhs;
    D e10 = rhs_c[3] * lhs;
    D e11 = rhs_c[4] * lhs;
    D e12 = rhs_c[5] * lhs;
    D e20 = rhs_c[6] * lhs;
    D e21 = rhs_c[7] * lhs;
    D e22 = rhs_c[8] * lhs;
    
    return mat3<D>( e00, e10, e20,
                    e01, e11, e21,
                    e02, e12, e22 );
}

template< typename T > inline
vec3_t<T>     mat3<T>::operator*( vec3_t<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T x0 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[6] * rhs_c[2];
    T x1 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[7] * rhs_c[2];
    T x2 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[8] * rhs_c[2];
    
    return vec3_t<T>( x0, x1, x2 );
}

template< typename T > inline
vec3_t<T>     operator*( vec3_t<T> const& lhs, mat3<T> const& rhs )
{
    T const* lhs_c = lhs.data.c;
    T const* rhs_c = rhs.data.c;
    
    T x0 = lhs_c[0] * rhs_c[0] + lhs_c[1] * rhs_c[1] + lhs_c[2] * rhs_c[2];
    T x1 = lhs_c[0] * rhs_c[3] + lhs_c[1] * rhs_c[4] + lhs_c[2] * rhs_c[5];
    T x2 = lhs_c[0] * rhs_c[6] + lhs_c[1] * rhs_c[7] + lhs_c[2] * rhs_c[8];
    
    return vec3_t<T>( x0, x1, x2 );
}

template< typename T >
mat3<T>     mat3<T>::operator/( T rhs )
{
    T const* rhs_c = this->data.c;
    
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

// Mutative Operators

template< typename T > inline
mat3<T>&    mat3<T>::operator=( mat3<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
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
col3<T>     mat3<T>::operator[]( size_t i )
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat3 out of range" );
    }
    
    return col3<T>( this->data.c + (3*i), true );
}

template< typename T > inline
col3<T>     mat3<T>::operator[]( size_t i ) const
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat3 out of range" );
    }
    
    T* col_cpy = new T[3];
    
    col_cpy[0] = this-data->c[ 3 * i ];
    col_cpy[1] = this-data->c[ 3 * i + 1 ];
    col_cpy[2] = this-data->c[ 3 * i + 2 ];
    
    return col3<T>( col_cpy, false );
}
               
template< typename T > inline
T&     mat3<T>::operator()( size_t col,
                            size_t row )
{
    if ( col > 2 or row > 2 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat3 used out of bounds index");
    }
    
    return this->data.c[col * 3 + row];
}

template< typename T > inline
T      mat3<T>::operator()( size_t col,
                            size_t row ) const
{
    if ( col > 2 or row > 2 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat3 used out of bounds index");
    }
    
    return this->data.c[col * 3 + row];
}

// Mutative Functions

template< typename T > inline
mat3<T>&    mat3<T>::column( size_t col,
                             vec3_t<T> const& val )
{
    switch( col ){
        case 0:
            this->data.c[0] = val(x);
            this->data.c[1] = val(y);
            this->data.c[2] = val(z);
            break;
        case 1:
            this->data.c[3] = val(x);
            this->data.c[4] = val(y);
            this->data.c[5] = val(z);
            break;
        case 2:
            this->data.c[6] = val(x);
            this->data.c[7] = val(y);
            this->data.c[8] = val(z);
            break;
        default:
          throw std::out_of_range("Component index on mat3 out of range.");
    }
    return *this;
}

template< typename T > inline
vec3_t<T>     mat3<T>::column( size_t col ) const
{
    T out_x, out_y, out_z;
    switch( col ){
        case 0:
            out_x = this->data.c[0];
            out_y = this->data.c[1];
            out_z = this->data.c[2];
            break;
        case 1:
            out_x = this->data.c[3];
            out_y = this->data.c[4];
            out_z = this->data.c[5];
            break;
        case 2:
            out_x = this->data.c[6];
            out_y = this->data.c[7];
            out_z = this->data.c[8];
            break;
        default:
          throw std::out_of_range("Component index on mat3 out of range.");
    }
    return vec3_t<T>(out_x, out_y, out_z);
}

template< typename T > inline
mat3<T>&    mat3<T>::columns( vec3_t<T> const& col0,
                              vec3_t<T> const& col1,
                              vec3_t<T> const& col2 )
{
    T* c = this->data.c;
    
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

template< typename T >
mat3<T>& mat3<T>::fill( T val )
{
    T* c = this->data.c;
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
mat3<T>& mat3<T>::normalize()
{
    T* c = this->data.c;
    double inv_mag = 1.0 / sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    c[0] *= inv_mag;
    c[1] *= inv_mag;
    c[2] *= inv_mag;
    
    inv_mag = 1.0 / sqrt(c[3] * c[3] + c[4] * c[4] + c[5] * c[5]);
    c[3] *= inv_mag;
    c[4] *= inv_mag;
    c[5] *= inv_mag;
    
    inv_mag = 1.0 / sqrt(c[6] * c[6] + c[7] * c[7] + c[8] * c[8]);
    c[6] *= inv_mag;
    c[7] *= inv_mag;
    c[8] *= inv_mag;
    
    return *this;
}

template< typename T > inline
mat3<T>&    mat3<T>::row( size_t row,
                          vec3_t<T> const& val )
{
    switch( row ){
        case 0:
            this->data.c[0] = val(x);
            this->data.c[3] = val(y);
            this->data.c[6] = val(z);
            break;
        case 1:
            this->data.c[1] = val(x);
            this->data.c[4] = val(y);
            this->data.c[7] = val(z);
            break;
        case 2:
            this->data.c[2] = val(x);
            this->data.c[5] = val(y);
            this->data.c[8] = val(z);
            break;
        default:
          throw std::out_of_range("Component index on mat3 out of range.");
    }
          
    return *this;
}

template< typename T > inline
vec3_t<T>     mat3<T>::row( size_t row ) const
{
    T out_x, out_y, out_z;
    switch( row ){
        case 0:
            out_x = this->data.c[0];
            out_y = this->data.c[3];
            out_z = this->data.c[6];
            break;
        case 1:
            out_x = this->data.c[1];
            out_y = this->data.c[4];
            out_z = this->data.c[7];
            break;
        case 2:
            out_x = this->data.c[2];
            out_y = this->data.c[5];
            out_z = this->data.c[8];
            break;
        default:
          throw std::out_of_range("Component index on mat3 out of range.");
    }
    return vec3_t<T>(out_x, out_y, out_z);
}



template< typename T >
inline mat3<T>& mat3<T>::rows( vec3_t<T> const& row0,
                               vec3_t<T> const& row1,
                               vec3_t<T> const& row2 )
{
    T* c = this->data.c;
    
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

template< typename T >
mat3<T>& mat3<T>::transpose()
{
    T* c = this->data.c;
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

// Utilities

template< typename T > inline
raw_map const   mat3<T>::to_map() const
{
    return map_bytes( sizeof(T) * 9, this->data.bytes );
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
{ T* c = this->data.c;
  c[0] = cnst<T>::zero;   c[4] = cnst<T>::zero;   c[8] = cnst<T>::zero;   c[12] = cnst<T>::zero;
  c[1] = cnst<T>::zero;   c[5] = cnst<T>::zero;   c[9] = cnst<T>::zero;   c[13] = cnst<T>::zero;
  c[2] = cnst<T>::zero;   c[6] = cnst<T>::zero;   c[10] = cnst<T>::zero;  c[14] = cnst<T>::zero;
  c[3] = cnst<T>::zero;   c[7] = cnst<T>::zero;   c[11] = cnst<T>::zero;  c[15] = cnst<T>::zero; }

template< typename T > inline
mat4<T>::mat4( mat4<T> const& copy )
{ T const* cpy = copy.data.c;
  T* c = this->data.c;
  c[0] = cpy[0];   c[4] = cpy[4];   c[8] = cpy[8];    c[12] = cpy[12];
  c[1] = cpy[1];   c[5] = cpy[5];   c[9] = cpy[9];    c[13] = cpy[13];
  c[2] = cpy[2];   c[6] = cpy[6];   c[10] = cpy[10];  c[14] = cpy[14];
  c[3] = cpy[3];   c[7] = cpy[7];   c[11] = cpy[11];  c[15] = cpy[15]; }
  
template< typename T >
mat4<T>::mat4( T e00, T e10, T e20, T e30,
               T e01, T e11, T e21, T e31,
               T e02, T e12, T e22, T e32,
               T e03, T e13, T e23, T e33 )
{ T* c = this->data.c;
  c[0] = e00;   c[4] = e10;   c[8] = e20;   c[12] = e30;
  c[1] = e01;   c[5] = e11;   c[9] = e21;   c[13] = e31;
  c[2] = e02;   c[6] = e12;   c[10] = e22;  c[14] = e32;
  c[3] = e03;   c[7] = e13;   c[11] = e23;  c[15] = e33; }

template< typename T >
mat4<T>     mat4<T>::identity()
{ return mat4( cnst<T>::one,  cnst<T>::zero, cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, cnst<T>::one,  cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::one,  cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::zero, cnst<T>::one  ); }
  
template< typename T > inline
mat4<T>     mat4<T>::row_vectors( vec4_t<T> const& row0,
                                  vec4_t<T> const& row1,
                                  vec4_t<T> const& row2,
                                  vec4_t<T> const& row3 )
{ return mat4( row0(x), row0(y), row0(z), row0(w),
               row1(x), row1(y), row1(z), row1(w),
               row2(x), row2(y), row2(z), row2(w),
               row3(x), row3(y), row3(z), row3(w) ); }
               
template< typename T > inline
mat4<T>     mat4<T>::column_vectors( vec4_t<T> const& col0,
                                     vec4_t<T> const& col1,
                                     vec4_t<T> const& col2,
                                     vec4_t<T> const& col3 )
{ return mat4( col0(x), col1(x), col2(x), col3(x),
               col0(y), col1(y), col2(y), col3(y),
               col0(z), col1(z), col2(z), col3(z),
               col0(w), col1(w), col2(w), col3(w) ); }
               
template< typename T > inline
mat4<T>     mat4<T>::square( vec4_t<T> const& vec )
{ return mat4( vec[0] * vec[0], vec[0] * vec[1], vec[0] * vec[2], vec[0] * vec[3],
               vec[1] * vec[0], vec[1] * vec[1], vec[1] * vec[2], vec[1] * vec[3],
               vec[2] * vec[0], vec[2] * vec[1], vec[2] * vec[2], vec[2] * vec[3],
               vec[3] * vec[0], vec[3] * vec[1], vec[3] * vec[2], vec[3] * vec[3]  ); }
               
template< typename T > inline
mat4<T>     mat4<T>::homogenize( mat3<T> const& amat )
{ return mat4( amat(0,0),    amat(1,0),    amat(2,0),    cnst<T>::zero,
               amat(0,1),    amat(1,1),    amat(2,1),    cnst<T>::zero,
               amat(0,2),    amat(1,2),    amat(2,2),    cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::zero, cnst<T>::one  ); }

template< typename T > inline
mat4<T>     mat4<T>::scale( T sx, T sy, T sz )
{ return mat4( sx,           cnst<T>::zero, cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, sy,           cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, sz,           cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::zero, cnst<T>::one  ); }
               
template< typename T > inline
mat4<T>     mat4<T>::scale( vec3_t<T> const& svec )
{ return mat4( svec(x),      cnst<T>::zero, cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, svec(y),      cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, svec(z),      cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::zero, cnst<T>::one  ); }
               
template< typename T > inline
mat4<T>     mat4<T>::translate( T tx, T ty, T tz )
{ return mat4( cnst<T>::one,  cnst<T>::zero, cnst<T>::zero, tx,
               cnst<T>::zero, cnst<T>::one,  cnst<T>::zero, ty,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::one,  tz,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::zero, cnst<T>::one  ); }
               
template< typename T > inline
mat4<T>     mat4<T>::translate( vec3_t<T> const& tvec )
{ return mat4( cnst<T>::one,  cnst<T>::zero, cnst<T>::zero, tvec(x),
               cnst<T>::zero, cnst<T>::one,  cnst<T>::zero, tvec(y),
               cnst<T>::zero, cnst<T>::zero, cnst<T>::one,  tvec(z),
               cnst<T>::zero, cnst<T>::zero, cnst<T>::zero, cnst<T>::one  ); }
               
template< typename T > inline
mat4<T>     mat4<T>::cross_product( vec3_t<T> const& vec )
{ return mat4( cnst<T>::zero, vec(-z),      vec(y),       cnst<T>::zero,
               vec(z),       cnst<T>::zero, vec(-x),      cnst<T>::zero,
               vec(-y),      vec(x),       cnst<T>::zero, cnst<T>::zero,
               cnst<T>::zero, cnst<T>::zero, cnst<T>::zero, cnst<T>::one   ); }
               
template< typename T > inline
mat4<T>     mat4<T>::perspective( double fovY,
                                  double aspect,
                                  double near,
                                  double far     )
{
    double invTopTan = 1.0 / tan( fovY * 0.5);
    double invRightTan = invTopTan / aspect;
    double invFLessN = 1.0 / ( far - near );
    
    return mat4( (T) invRightTan, cnst<T>::zero,  cnst<T>::zero,                  cnst<T>::zero,
                 cnst<T>::zero,    (T) invTopTan, cnst<T>::zero,                  cnst<T>::zero,
                 cnst<T>::zero,    cnst<T>::zero,  (T) -(far + near) * invFLessN, (T) -(2.0*far*near) * invFLessN,
                 cnst<T>::zero,    cnst<T>::zero,  cnst<T>::neg_one,               cnst<T>::zero                    );
}

template< typename T > inline
mat4<T>     mat4<T>::rotation( vec3_t<T> const& axis,
                               d_angle const& ang     )
{
    double radians ( ang.to_rads() );
    double cos_t ( cos(radians) );
    double cm_cos_t = 1.0 - cos_t;
    double sin_t ( sin(radians) );
    mat4<T> trig_mat( cos_t,          axis(-z)*sin_t, axis(y)*sin_t,  cnst<T>::zero,
                      axis(z)*sin_t,  cos_t,          axis(-x)*sin_t, cnst<T>::zero,
                      axis(-y)*sin_t, axis(x)*sin_t,  cos_t,          cnst<T>::zero,
                      cnst<T>::zero,   cnst<T>::zero,   cnst<T>::zero,   cnst<T>::zero  );
    
    mat4<T> axis_mat( axis(x) * axis(x) * cm_cos_t, axis(x) * axis(y) * cm_cos_t, axis(x) * axis(z) * cm_cos_t, cnst<T>::zero,
                      axis(y) * axis(x) * cm_cos_t, axis(y) * axis(y) * cm_cos_t, axis(y) * axis(z) * cm_cos_t, cnst<T>::zero,
                      axis(z) * axis(x) * cm_cos_t, axis(z) * axis(y) * cm_cos_t, axis(z) * axis(z) * cm_cos_t, cnst<T>::zero,
                      cnst<T>::zero,      cnst<T>::zero,      cnst<T>::zero,      cnst<T>::one  );
    return trig_mat + axis_mat;
}

template< typename T > inline
mat4<T>     mat4<T>::rotation( d_angle const& angx,
                               d_angle const& angy,
                               d_angle const& angz )
{
    double radx ( angx.to_rads() );
    double rady ( angy.to_rads() );
    double radz ( angz.to_rads() );
    
    double sin_x = std::sin( radx );
    double cos_x = std::cos( radx );
    double sin_y = std::sin( rady );
    double cos_y = std::cos( rady );
    double sin_z = std::sin( radz );
    double cos_z = std::cos( radz );
    
    return mat4<T>(
        cos_y*cos_z,                     -cos_y*sin_z,                      sin_y,         cnst<T>::zero,
        cos_x*sin_z + sin_x*sin_y*cos_z,  cos_x*cos_z - sin_x*sin_y*sin_z, -sin_x*cos_y,   cnst<T>::zero,
        sin_x*sin_z - cos_x*sin_y*cos_z,  sin_x*cos_z + cos_x*sin_y*sin_z,  cos_x*cos_y,   cnst<T>::zero,
        cnst<T>::zero,                    cnst<T>::zero,                    cnst<T>::zero, cnst<T>::one
      );
    
}
template< typename T > inline
bool    mat4<T>::operator==( mat4<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    
    return     abs(lhs_c[0] - rhs_c[0]) < cnst<T>::delta
           and abs(lhs_c[1] - rhs_c[1]) < cnst<T>::delta
           and abs(lhs_c[2] - rhs_c[2]) < cnst<T>::delta
           and abs(lhs_c[3] - rhs_c[3]) < cnst<T>::delta
           and abs(lhs_c[4] - rhs_c[4]) < cnst<T>::delta
           and abs(lhs_c[5] - rhs_c[5]) < cnst<T>::delta
           and abs(lhs_c[6] - rhs_c[6]) < cnst<T>::delta
           and abs(lhs_c[7] - rhs_c[7]) < cnst<T>::delta
           and abs(lhs_c[8] - rhs_c[8]) < cnst<T>::delta
           and abs(lhs_c[9] - rhs_c[9]) < cnst<T>::delta
           and abs(lhs_c[10] - rhs_c[10]) < cnst<T>::delta
           and abs(lhs_c[11] - rhs_c[11]) < cnst<T>::delta
           and abs(lhs_c[12] - rhs_c[12]) < cnst<T>::delta
           and abs(lhs_c[13] - rhs_c[13]) < cnst<T>::delta
           and abs(lhs_c[14] - rhs_c[14]) < cnst<T>::delta
           and abs(lhs_c[15] - rhs_c[15]) < cnst<T>::delta;
}

template< typename T > inline
bool    mat4<T>::operator<( mat4<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
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
bool    mat4<T>::operator>( mat4<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
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
bool    mat4<T>::operator<=( mat4<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
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
bool    mat4<T>::operator>=( mat4<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
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
bool    mat4<T>::operator!=( mat4<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     lhs_c[0] != rhs_c[0]
           or lhs_c[1] != rhs_c[1]
           or lhs_c[2] != rhs_c[2]
           or lhs_c[3] != rhs_c[3]
           or lhs_c[4] != rhs_c[4]
           or lhs_c[5] != rhs_c[5]
           or lhs_c[6] != rhs_c[6]
           or lhs_c[7] != rhs_c[7]
           or lhs_c[8] != rhs_c[8]
           or lhs_c[9] != rhs_c[9]
           or lhs_c[10] != rhs_c[10]
           or lhs_c[11] != rhs_c[11]
           or lhs_c[12] != rhs_c[12]
           or lhs_c[13] != rhs_c[13]
           or lhs_c[14] != rhs_c[14]
           or lhs_c[15] != rhs_c[15];
}

template< typename T > inline
mat4<T>&    mat4<T>::operator=( mat4<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
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
col4<T>     mat4<T>::operator[]( size_t i )
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat4 out of range" );
    }
    
    return col4<T>( this->data.c + (4*i), true );
}

template< typename T > inline
col4<T>     mat4<T>::operator[]( size_t i ) const
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat4 out of range" );
    }
    
    T* col_cpy = new T[4];
    
    col_cpy[0] = this-data->c[ 4 * i ];
    col_cpy[1] = this-data->c[ 4 * i + 1 ];
    col_cpy[2] = this-data->c[ 4 * i + 2 ];
    col_cpy[3] = this-data->c[ 4 * i + 3 ];
    
    return col4<T>( col_cpy, false );
}
               
template< typename T > inline
T&     mat4<T>::operator()( size_t col,
                            size_t row )
{
    if ( col > 3 or row > 3 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat4 used out of bounds index");
    }
    
    return this->data.c[col * 4 + row];
}

template< typename T > inline
T      mat4<T>::operator()( size_t col,
                            size_t row ) const
{
    if ( col > 3 or row > 3 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat4 used out of bounds index");
    }
    
    return this->data.c[col * 4 + row];
}

template< typename T > inline
mat4<T>     mat4<T>::operator+( mat4<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    return mat4( lhs_c[0] + rhs_c[0], lhs_c[4] + rhs_c[4], lhs_c[8] + rhs_c[8],   lhs_c[12] + rhs_c[12],
                 lhs_c[1] + rhs_c[1], lhs_c[5] + rhs_c[5], lhs_c[9] + rhs_c[9],   lhs_c[13] + rhs_c[13],
                 lhs_c[2] + rhs_c[2], lhs_c[6] + rhs_c[6], lhs_c[10] + rhs_c[10], lhs_c[14] + rhs_c[14],
                 lhs_c[3] + rhs_c[3], lhs_c[7] + rhs_c[7], lhs_c[11] + rhs_c[11], lhs_c[15] + rhs_c[15] );
}

template< typename T > inline
mat4<T>     mat4<T>::operator-()
{
    T const* lhs_c = this->data.c;
    
    return mat4( -lhs_c[0], -lhs_c[4], -lhs_c[8],  -lhs_c[12],
                 -lhs_c[1], -lhs_c[5], -lhs_c[9],  -lhs_c[13],
                 -lhs_c[2], -lhs_c[6], -lhs_c[10], -lhs_c[14],
                 -lhs_c[3], -lhs_c[7], -lhs_c[11], -lhs_c[15] );
}

template< typename T > inline
mat4<T>     mat4<T>::operator-( mat4<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    return mat4( lhs_c[0] - rhs_c[0], lhs_c[4] - rhs_c[4], lhs_c[8] - rhs_c[8], lhs_c[12] - rhs_c[12],
                 lhs_c[1] - rhs_c[1], lhs_c[5] - rhs_c[5], lhs_c[9] - rhs_c[9], lhs_c[13] - rhs_c[13],
                 lhs_c[2] - rhs_c[2], lhs_c[6] - rhs_c[6], lhs_c[10] - rhs_c[10], lhs_c[14] - rhs_c[14],
                 lhs_c[3] - rhs_c[3], lhs_c[7] - rhs_c[7], lhs_c[11] - rhs_c[11], lhs_c[15] - rhs_c[15] );
}
               
template< typename T > inline
mat4<T>     mat4<T>::operator*( mat4<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[8] * rhs_c[2] + lhs_c[12] * rhs_c[3];
    T e10 = lhs_c[0] * rhs_c[4] + lhs_c[4] * rhs_c[5] + lhs_c[8] * rhs_c[6] + lhs_c[12] * rhs_c[7];
    T e20 = lhs_c[0] * rhs_c[8] + lhs_c[4] * rhs_c[9] + lhs_c[8] * rhs_c[10] + lhs_c[12] * rhs_c[11];
    T e30 = lhs_c[0] * rhs_c[12] + lhs_c[4] * rhs_c[13] + lhs_c[8] * rhs_c[14] + lhs_c[12] * rhs_c[15];
    
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[9] * rhs_c[2] + lhs_c[13] * rhs_c[3];
    T e11 = lhs_c[1] * rhs_c[4] + lhs_c[5] * rhs_c[5] + lhs_c[9] * rhs_c[6] + lhs_c[13] * rhs_c[7];
    T e21 = lhs_c[1] * rhs_c[8] + lhs_c[5] * rhs_c[9] + lhs_c[9] * rhs_c[10] + lhs_c[13] * rhs_c[11];
    T e31 = lhs_c[1] * rhs_c[12] + lhs_c[5] * rhs_c[13] + lhs_c[9] * rhs_c[14] + lhs_c[13] * rhs_c[15];
    
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[6] * rhs_c[1] + lhs_c[10] * rhs_c[2] + lhs_c[14] * rhs_c[3];
    T e12 = lhs_c[2] * rhs_c[4] + lhs_c[6] * rhs_c[5] + lhs_c[10] * rhs_c[6] + lhs_c[14] * rhs_c[7];
    T e22 = lhs_c[2] * rhs_c[8] + lhs_c[6] * rhs_c[9] + lhs_c[10] * rhs_c[10] + lhs_c[14] * rhs_c[11];
    T e32 = lhs_c[2] * rhs_c[12] + lhs_c[6] * rhs_c[13] + lhs_c[10] * rhs_c[14] + lhs_c[14] * rhs_c[15];
    
    T e03 = lhs_c[3] * rhs_c[0] + lhs_c[7] * rhs_c[1] + lhs_c[11] * rhs_c[2] + lhs_c[15] * rhs_c[3];
    T e13 = lhs_c[3] * rhs_c[4] + lhs_c[7] * rhs_c[5] + lhs_c[11] * rhs_c[6] + lhs_c[15] * rhs_c[7];
    T e23 = lhs_c[3] * rhs_c[8] + lhs_c[7] * rhs_c[9] + lhs_c[11] * rhs_c[10] + lhs_c[15] * rhs_c[11];
    T e33 = lhs_c[3] * rhs_c[12] + lhs_c[7] * rhs_c[13] + lhs_c[11] * rhs_c[14] + lhs_c[15] * rhs_c[15];
    
    return mat4( e00, e10, e20, e30,
                 e01, e11, e21, e31,
                 e02, e12, e22, e32,
                 e03, e13, e23, e33 );
}

template< typename T > inline
vec4_t<T>     mat4<T>::operator*( vec4_t<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T x0 =   lhs_c[0]  * rhs_c[0] + lhs_c[4]  * rhs_c[1]
           + lhs_c[8]  * rhs_c[2] + lhs_c[12] * rhs_c[3];
    T x1 =   lhs_c[1]  * rhs_c[0] + lhs_c[5]  * rhs_c[1]
           + lhs_c[9]  * rhs_c[2] + lhs_c[13] * rhs_c[3];
    T x2 =   lhs_c[2]  * rhs_c[0] + lhs_c[6]  * rhs_c[1]
           + lhs_c[10] * rhs_c[2] + lhs_c[14] * rhs_c[3];
    T x3 =   lhs_c[3]  * rhs_c[0] + lhs_c[7]  * rhs_c[1]
           + lhs_c[11] * rhs_c[2] + lhs_c[15] * rhs_c[3];
    
    return vec4_t<T>( x0, x1, x2, x3 );
}

template< typename T > inline
vec4_t<T>     operator*( vec4_t<T> const& lhs, mat4<T> const& rhs )
{
    T const* lhs_c = lhs.data.c;
    T const* rhs_c = rhs.data.c;
    
    T x0 =   lhs_c[0]  * rhs_c[0]  + lhs_c[1]  * rhs_c[1]
           + lhs_c[2]  * rhs_c[2]  + lhs_c[3]  * rhs_c[3];
    T x1 =   lhs_c[0]  * rhs_c[4]  + lhs_c[1]  * rhs_c[5]
           + lhs_c[2]  * rhs_c[6]  + lhs_c[3]  * rhs_c[7];
    T x2 =   lhs_c[0]  * rhs_c[8]  + lhs_c[1]  * rhs_c[9]
           + lhs_c[2]  * rhs_c[10] + lhs_c[3]  * rhs_c[11];
    T x3 =   lhs_c[0]  * rhs_c[12] + lhs_c[1]  * rhs_c[13]
           + lhs_c[2]  * rhs_c[14] + lhs_c[3]  * rhs_c[15];
    
    return vec4_t<T>( x0, x1, x2, x3 );
}

template< typename T >
mat4<T>     mat4<T>::operator*( T rhs )
{
    T const* rhs_c = this->data.c;
    
    return mat4( rhs_c[0] * rhs, rhs_c[4] * rhs, rhs_c[8] * rhs,  rhs_c[12] * rhs,
                 rhs_c[1] * rhs, rhs_c[5] * rhs, rhs_c[9] * rhs,  rhs_c[13] * rhs,
                 rhs_c[2] * rhs, rhs_c[6] * rhs, rhs_c[10] * rhs, rhs_c[14] * rhs,
                 rhs_c[3] * rhs, rhs_c[7] * rhs, rhs_c[11] * rhs, rhs_c[15] * rhs  );
}

template< typename D >
mat4<D>     operator*( D lhs, mat4<D> const& rhs )
{
    D const* rhs_c = rhs.data.c;
    
    return mat4<D>( rhs_c[0] * lhs, rhs_c[4] * lhs, rhs_c[8] * lhs,  rhs_c[12] * lhs,
                    rhs_c[1] * lhs, rhs_c[5] * lhs, rhs_c[9] * lhs,  rhs_c[13] * lhs,
                    rhs_c[2] * lhs, rhs_c[6] * lhs, rhs_c[10] * lhs, rhs_c[14] * lhs,
                    rhs_c[3] * lhs, rhs_c[7] * lhs, rhs_c[11] * lhs, rhs_c[15] * lhs );
}

template< typename T >
mat4<T>     mat4<T>::operator/( T rhs )
{
    T const* lhs_c = this->data.c;
    
    return mat4( lhs_c[0] / rhs, lhs_c[4] / rhs, lhs_c[8] / rhs,  lhs_c[12] / rhs,
                 lhs_c[1] / rhs, lhs_c[5] / rhs, lhs_c[9] / rhs,  lhs_c[13] / rhs,
                 lhs_c[2] / rhs, lhs_c[6] / rhs, lhs_c[10] / rhs, lhs_c[14] / rhs,
                 lhs_c[3] / rhs, lhs_c[7] / rhs, lhs_c[11] / rhs, lhs_c[15] / rhs );
}

template< typename T >
mat4<T>& mat4<T>::fill( T val )
{
    T* c = this->data.c;
    c[0] = val;     c[4] = val;     c[8] = val;     c[12] = val;
    c[1] = val;     c[5] = val;     c[9] = val;     c[13] = val;
    c[2] = val;     c[6] = val;     c[10] = val;    c[14] = val;
    c[3] = val;     c[7] = val;     c[11] = val;    c[15] = val;
 
    return *this;
}

template< typename T >
mat4<T>& mat4<T>::transpose()
{
    T* c = this->data.c;
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
                          vec4_t<T> const& val )
{
    switch( row ){
        case 0:
            this->data.c[0] = val(x);
            this->data.c[4] = val(y);
            this->data.c[8] = val(z);
            this->data.c[12] = val(w);
            break;
        case 1:
            this->data.c[1] = val(x);
            this->data.c[5] = val(y);
            this->data.c[9] = val(z);
            this->data.c[13] = val(w);
            break;
        case 2:
            this->data.c[2] = val(x);
            this->data.c[6] = val(y);
            this->data.c[10] = val(z);
            this->data.c[14] = val(w);
            break;
        case 3:
            this->data.c[3] = val(x);
            this->data.c[7] = val(y);
            this->data.c[11] = val(z);
            this->data.c[15] = val(w);
            break;
        default:
          throw std::out_of_range("Component index on mat4 out of range.");
    }
          
    return *this;
}

template< typename T > inline
vec4_t<T>     mat4<T>::row( size_t row ) const
{
    switch( row ){
        case 0:
            return vec4_t<T>(this->data.c[0],
                           this->data.c[4],
                           this->data.c[8],
                           this->data.c[12] );
        case 1:
            return vec4_t<T>(this->data.c[1],
                           this->data.c[5],
                           this->data.c[9],
                           this->data.c[13] );
        case 2:
            return vec4_t<T>(this->data.c[2],
                           this->data.c[6],
                           this->data.c[10],
                           this->data.c[14] );
        case 3:
            return vec4_t<T>(this->data.c[3],
                           this->data.c[7],
                           this->data.c[11],
                           this->data.c[15] );
        default:
          throw std::out_of_range("Component index on mat4 out of range.");
    }
}

template< typename T > inline
mat4<T>&    mat4<T>::column( size_t col,
                             vec4_t<T> const& val )
{
    switch( col ){
        case 0:
            this->data.c[0] = val(x);
            this->data.c[1] = val(y);
            this->data.c[2] = val(z);
            this->data.c[3] = val(w);
            break;
        case 1:
            this->data.c[4] = val(x);
            this->data.c[5] = val(y);
            this->data.c[6] = val(z);
            this->data.c[7] = val(w);
            break;
        case 2:
            this->data.c[8] = val(x);
            this->data.c[9] = val(y);
            this->data.c[10] = val(z);
            this->data.c[11] = val(w);
            break;
        case 3:
            this->data.c[12] = val(x);
            this->data.c[13] = val(y);
            this->data.c[14] = val(z);
            this->data.c[15] = val(w);
            break;
        default:
          throw std::out_of_range("Component index on mat4 out of range.");
    }
    return *this;
}

template< typename T > inline
vec4_t<T>     mat4<T>::column( size_t col ) const
{
    switch( col ){
        case 0:
            return vec4_t<T>(this->data.c[0],
                           this->data.c[1],
                           this->data.c[2],
                           this->data.c[3] );
        case 1:
            return vec4_t<T>(this->data.c[4],
                           this->data.c[5],
                           this->data.c[6],
                           this->data.c[7] );
        case 2:
            return vec4_t<T>(this->data.c[8],
                           this->data.c[9],
                           this->data.c[10],
                           this->data.c[11] );
        case 3:
            return vec4_t<T>(this->data.c[12],
                           this->data.c[13],
                           this->data.c[14],
                           this->data.c[15] );
        default:
          throw std::out_of_range("Component index on mat4 out of range.");
    }
}

template< typename T >
inline mat4<T>& mat4<T>::rows( vec4_t<T> const& row0,
                               vec4_t<T> const& row1,
                               vec4_t<T> const& row2,
                               vec4_t<T> const& row3 )
{
    T* c = this->data.c;
    
    c[0] = row0(x);
    c[4] = row0(y);
    c[8] = row0(z);
    c[12] = row0(w);
    c[1] = row1(x);
    c[5] = row1(y);
    c[9] = row1(z);
    c[13] = row1(w);
    c[2] = row2(x);
    c[6] = row2(y);
    c[10] = row2(z);
    c[14] = row2(w);
    c[3] = row3(x);
    c[7] = row3(y);
    c[11] = row3(z);
    c[15] = row3(w);
    
    return *this;
}

template< typename T > inline
mat4<T>&    mat4<T>::columns( vec4_t<T> const& col0,
                              vec4_t<T> const& col1,
                              vec4_t<T> const& col2,
                              vec4_t<T> const& col3 )
{
    T* c = this->data.c;
    
    c[0] = col0(x);
    c[1] = col0(y);
    c[2] = col0(z);
    c[3] = col0(w);
    c[4] = col1(x);
    c[5] = col1(y);
    c[6] = col1(z);
    c[7] = col1(w);
    c[8] = col2(x);
    c[9] = col2(y);
    c[10] = col2(z);
    c[11] = col2(w);
    c[12] = col3(x);
    c[13] = col3(y);
    c[14] = col3(z);
    c[15] = col3(w);
    
    return *this;
}

template< typename T > inline
raw_map const   mat4<T>::to_map() const
{
    return map_bytes( sizeof(T) * 16, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat4<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0);
    stream << " " << src(2,0) << " " << src(3,0) << " ]" << '\n';
    
    stream << "[ " << src(0,1) << " " << src(1,1);
    stream << " " << src(2,1) << " " << src(3,1) << " ]" << '\n';
    
    stream << "[ " << src(0,2) << " " << src(1,2);
    stream << " " << src(2,2) << " " << src(3,2) << " ]" << '\n';
    
    stream << "[ " << src(0,3) << " " << src(1,3);
    stream << " " << src(2,3) << " " << src(3,3) << " ]" << std::endl;
    return stream;
}

}

#endif
