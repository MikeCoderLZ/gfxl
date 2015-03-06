#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <exception>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <climits>
#include <cstdint>
#include "../gUtility/datatypeinfo.hpp"
#include "../gVideo/gl_core_3_3.hpp"
#include "constant.hpp"

namespace gfx {
  
// Five vector primitives
template< typename T > class scalar;
template< typename T > class vec2_t;
template< typename T > class vec3_t;
template< typename T > class vec4_t;
template< typename T > class qutn_t;

// Ten matrix primitives
template< typename T > class mat_t;
template< typename T > class mat2_t;
template< typename T > class mat3_t;
template< typename T > class mat4_t;
template< typename T > class mat2x3_t;
template< typename T > class mat2x4_t;
template< typename T > class mat3x2_t;
template< typename T > class mat3x4_t;
template< typename T > class mat4x2_t;
template< typename T > class mat4x3_t;

// Component swizzles
class swizz4;
class swizz3;
class swizz2;
class swizz1;

#ifndef PROGRAM_HPP
class program;
#endif

// An ABC that graphics primitives use to deal with mapping
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
    friend class            program;
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
    //map_bytes() is an internal utility used for cloning bytes.
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
  // WARNING DANGER Because these types are using an array and invoke the
  // sizeof() operator, it is ESPECIALLY DANGEROUS if you put a base class in
  // the template parameter. Doing that will inevitably cause object slicing
  // and BOOM, it will explode.
    union {
        comp_t          value;
        unsigned char   bytes[sizeof(comp_t)];
    } data;
};

// This macro is defined in datatypeinfo.hpp; it expands to a template
// specialization of the typeinfo class with a further template param.
// Type information for library classes is only generated when code
// actually uses it. Because this partiuclar file uses this system
// for standard GLSL types, the type information is in fact generated,
// but that is okay since it is necessary for sending information over
// to OpenGL.
//
// For user created linear algebra types using these templates, it will
// NOT be generated unless it is in fact used.
//
// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is extremely spooky stuff.
template< typename T >
G_TYPE( scalar<T>, type<T>().n_components(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

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
    template< typename U > friend   class mat2_t;
    template<typename D > friend
    vec2_t<D>               operator*( vec2_t<D> const& lhs,
                                       mat2_t<D> const& rhs );
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

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( vec2_t<T>, 2 * type<T>().n_components(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

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
    vec3_t<T>               operator-() const;
    vec3_t<T>               operator*( vec3_t<T> const& rhs ) const;
    vec3_t<T>               operator*( comp_t rhs ) const;
    vec3_t<T>               operator/( vec3_t<T> const& rhs ) const;

    template< typename U > friend
    std::ostream&           operator<<( std::ostream& out,
                                        vec3_t<U> const& src );
    virtual raw_map const   to_map() const;
    template< typename D > friend class mat3_t;
    template< typename D > friend
    vec3_t<D>               operator*( vec3_t<D> const& lhs,
                                       mat3_t<D> const& rhs );
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

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( vec3_t<T>, 3 * type<T>().n_components(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

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
                            vec4_t( vec3_t<T> const& xyz,
                                    T cw                  );
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
    template< typename D > friend class mat4_t;
    template< typename D > friend
    vec4_t<D>               operator*( vec4_t<D> const& lhs,
                                       mat4_t<D> const& rhs );
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

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( vec4_t<T>, 4 * type<T>().n_components(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

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
    static qutn_t<T>        rotation( mat3_t<T> const& rmat );
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
    vec3_t<T>               rotate( vec3_t<T> const& avec ) const;
    
    template< typename U >
    friend std::ostream&    operator<<( std::ostream& out, qutn_t<U> const& src );
    virtual raw_map const   to_map() const;
protected:
    union {
        comp_t          c[4];
        unsigned char   bytes[sizeof(T) * 4];
    } data;
};

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( qutn_t<T>, 4 * type<T>().n_components(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

// Here we instantiate all the datatypes that GLSL supports
// and provide typedef names.

typedef     vec4_t<float>       vec4;
typedef     vec3_t<float>       vec3;
typedef     vec2_t<float>       vec2;
typedef     scalar<float>       float32;
typedef     qutn_t<float>       qutn;

typedef     vec4_t<double>      dvec4;
typedef     vec3_t<double>      dvec3;
typedef     vec2_t<double>      dvec2;
typedef     scalar<double>      double64;
typedef     qutn_t<double>      dqutn;

typedef     vec4_t<int32_t>     ivec4;
typedef     vec3_t<int32_t>     ivec3;
typedef     vec2_t<int32_t>     ivec2;
typedef     scalar<int32_t>     int32;

typedef     vec4_t<int16_t>     svec4;
typedef     vec3_t<int16_t>     svec3;
typedef     vec2_t<int16_t>     svec2;
typedef     scalar<int16_t>     short16;

typedef     vec4_t<int8_t>      cvec4;
typedef     vec3_t<int8_t>      cvec3;
typedef     vec2_t<int8_t>      cvec2;
typedef     scalar<int8_t>      char8;

typedef     vec4_t<uint32_t>    uvec4;
typedef     vec3_t<uint32_t>    uvec3;
typedef     vec2_t<uint32_t>    uvec2;
typedef     scalar<uint32_t>    uint32;

typedef     vec4_t<uint16_t>    usvec4;
typedef     vec3_t<uint16_t>    usvec3;
typedef     vec2_t<uint16_t>    usvec2;
typedef     scalar<uint16_t>    ushort16;

typedef     vec4_t<uint8_t>     ucvec4;
typedef     vec3_t<uint8_t>     ucvec3;
typedef     vec2_t<uint8_t>     ucvec2;
typedef     scalar<uint8_t>     uchar8;

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
    template< typename U > friend class mat2_t;
    template< typename U > friend class mat3x2_t;
    template< typename U > friend class mat4x2_t;
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
class row2 {
public:
    typedef T   comp_t;
    
                row2( row2<comp_t> const& arow );
    row2&       operator=( row2<comp_t> const& arow );
    row2&       operator=( vec2_t<comp_t> const& avec );
    comp_t&     operator[]( size_t i );
    comp_t      operator[]( size_t i ) const;
                operator vec2_t<comp_t>() const;
    template< typename U > friend class mat2_t;
    template< typename U > friend class mat2x3_t;
    template< typename U > friend class mat2x4_t;
                ~row2();
    template< typename U > friend
    std::ostream&   operator<<( std::ostream& out,
                                row2<U> const& rhs );
private:
    row2( comp_t* c0_adr,
          comp_t* c1_adr,
          bool liveness );
    row2( vec2_t<comp_t> const& avec );
    row2( comp_t c0_val,
          comp_t c1_val );
    bool        live_handle;
    comp_t*     c0;
    comp_t*     c1;
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
    template< typename U > friend class mat3_t;
    template< typename U > friend class mat2x3_t;
    template< typename U > friend class mat4x3_t;
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
class row3 {
public:
    typedef T   comp_t;
    
                row3( row3<comp_t> const& acol );
    row3&       operator=( row3<comp_t> const& acol );
    row3&       operator=( vec3_t<comp_t> const& avec );
    comp_t&     operator[]( size_t i );
    comp_t      operator[]( size_t i ) const;
                operator vec3_t<comp_t>() const;
    template< typename U > friend class mat3_t;
    template< typename U > friend class mat3x2_t;
    template< typename U > friend class mat3x4_t;
                ~row3();
    template< typename U > friend
    std::ostream&   operator<<( std::ostream& out,
                                row3<U> const& rhs );
private:
    row3( comp_t* c0_adr,
          comp_t* c1_adr,
          comp_t* c2_adr,
          bool liveness );
    row3( vec3_t<comp_t> const& avec );
    row3( comp_t c0_val,
          comp_t c1_val,
          comp_t c2_val );
    bool        live_handle;
    comp_t*     c0;
    comp_t*     c1;
    comp_t*     c2;
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
    template< typename U > friend class mat4_t;
    template< typename U > friend class mat2x4_t;
    template< typename U > friend class mat3x4_t;
                ~col4();
    template< typename U > friend
    std::ostream&   operator<<( std::ostream& out,
                                col4<U> const& rhs );
private:
    col4( comp_t* col_adr, bool liveness );
    bool        live_handle;
    comp_t*     column;
};

template< typename T >
class row4 {
public:
    typedef T   comp_t;
    
                row4( row4<comp_t> const& acol );
    row4&       operator=( vec4_t<comp_t> const& avec );
    row4&       operator=( row4<comp_t> const& acol );
    comp_t&     operator[]( size_t i );
    comp_t      operator[]( size_t i ) const;
                operator vec4_t<comp_t>() const;
    template< typename U > friend class mat4_t;
    template< typename U > friend class mat4x2_t;
    template< typename U > friend class mat4x3_t;
                ~row4();
    template< typename U > friend
    std::ostream&   operator<<( std::ostream& out,
                                row4<U> const& rhs );
private:
    row4( comp_t* c0_adr,
          comp_t* c1_adr,
          comp_t* c2_adr,
          comp_t* c3_adr,
          bool liveness );
    row4( vec4_t<comp_t> const& avec );
    row4( comp_t c0_val,
          comp_t c1_val,
          comp_t c2_val,
          comp_t c3_val );
    bool        live_handle;
    comp_t*     c0;
    comp_t*     c1;
    comp_t*     c2;
    comp_t*     c3;
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
class mat_t : public raw_mappable {
public:
    typedef T               comp_t;

                            mat_t();
                            mat_t( mat_t<T> const& copy );
                            mat_t( size_t new_n_cols,
                                   size_t new_n_rows );
    static mat_t<T>         fill( size_t new_n_cols,
                                  size_t new_n_rows,
                                  comp_t const val );
    static mat_t<T>         identity( size_t new_dim );
    virtual                 ~mat_t();
    size_t                  n_cols() const;
    size_t                  n_rows() const;
    size_t                  n_comp() const;
    bool                    operator==( mat_t<T> const& rhs ) const;
    bool                    operator!=( mat_t<T> const& rhs ) const;
    mat_t<T>&               operator=( mat_t<T> const& rhs );
    comp_t&                 operator()( size_t col, size_t row );
    comp_t                  operator()( size_t col, size_t row ) const;
    mat_t<T>                operator+( mat_t<T> const& rhs ) const;
    mat_t<T>                operator-( mat_t<T> const& rhs ) const;
    mat_t<T>                operator*( mat_t<T> const& rhs ) const;
    mat_t<T>                operator*( comp_t rhs );
    template< typename D > friend
    mat_t<D>                operator*( D lhs, mat_t<D> const& rhs );
    mat_t<T>                operator*( scalar<comp_t> rhs );
    template< typename D > friend
    mat_t<D>                operator*( scalar<D> lhs, mat_t<D> const& rhs );
    mat_t<T>                operator/( comp_t rhs );
    mat_t<T>                operator/( scalar<comp_t> rhs );
    mat_t<T>&               fill( comp_t const val );
    mat_t<T>&               transpose();
    virtual raw_map const   to_map() const;
protected:
    class mat_data {
    public:
        mat_t<T>*                  owner;
        comp_t*                 c;
                                mat_data( mat_t<T>* new_owner );
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
class mat2_t : public raw_mappable {
public:
    typedef T                       comp_t;
    constexpr static size_t const   n_cols = 2;
    constexpr static size_t const   n_rows = 2;
    constexpr static size_t const   n_comp = 4;
    // Construction
                            mat2_t();
                            mat2_t( mat2_t const& copy );
                            mat2_t( comp_t e00, comp_t e10,
                                  comp_t e01, comp_t e11 );
    // Named Construction
    static mat2_t<T>        column_vectors( vec2_t<comp_t> const& col0,
                                            vec2_t<comp_t> const& col1 );
    static mat2_t<T>        identity();
    static mat2_t<T>        row_vectors( vec2_t<comp_t> const& row0,
                                         vec2_t<comp_t> const& row1 );
    static mat2_t<T>        scale( comp_t sx,                            
                                   comp_t sy );
    static mat2_t<T>        scale( vec2_t<comp_t> const& svec );
    static mat2_t<T>        rotation( d_angle const& ang );
    // Comparison
    bool                    operator==( mat2_t<T> const& rhs ) const;
    bool                    operator<( mat2_t<T> const& rhs ) const;
    bool                    operator>( mat2_t<T> const& rhs ) const;
    bool                    operator<=( mat2_t<T> const& rhs ) const;
    bool                    operator>=( mat2_t<T> const& rhs ) const;
    bool                    operator!=( mat2_t<T> const& rhs ) const;
    // Arithmetic
    mat2_t<T>               operator+( mat2_t<T> const& rhs );
    mat2_t<T>               operator-();
    mat2_t<T>               operator-( mat2_t<T> const& rhs );
    mat2_t<T>               operator*( mat2_t<T> const& rhs ) const;
    mat3x2_t<T>             operator*( mat3x2_t<T> const& rhs ) const;
    mat4x2_t<T>             operator*( mat4x2_t<T> const& rhs ) const;
    vec2_t<comp_t>          operator*( vec2_t<comp_t> const& rhs );
    template<typename D > friend
    vec2_t<D>               operator*( vec2_t<D> const& lhs, mat2_t<D> const& rhs );
    mat2_t<T>               operator*( comp_t rhs );
    template< typename D > friend
    mat2_t<D>               operator*( D lhs, mat2_t<D> const& rhs );
    mat2_t<T>               operator/( comp_t rhs );
    // Mutatative Operators
    mat2_t<T>&              operator=( mat2_t<T> const& rhs );
    col2<comp_t>            operator[]( size_t i );
    col2<comp_t>            operator[]( size_t i ) const;
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
    // Mutative Functions
    mat2_t<T>&              column( size_t col,
                                    vec2_t<comp_t> const& val );
    vec2_t<T>               column( size_t col ) const;
    mat2_t<T>&              columns( vec2_t<comp_t> const& col0,
                                     vec2_t<comp_t> const& col1 );
    mat2_t<T>&              fill( comp_t val );
    mat2_t<T>&              row( size_t row,
                                 vec2_t<comp_t> const& val );
    vec2_t<T>               row( size_t row ) const;
    mat2_t<T>&              rows( vec2_t<comp_t> const& row0,
                                  vec2_t<comp_t> const& row1 );
    mat2_t<T>&              transpose();
    // Utility
    virtual raw_map const   to_map() const;
    
    template< typename U > friend class mat2x4_t;
    template< typename U > friend class mat2x3_t;
protected:
    union {
        comp_t          c[4];
        unsigned char   bytes[sizeof(comp_t) * 4];
    } data;
};

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( mat2_t<T>, 4 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class mat3_t : public raw_mappable {
public:
    typedef T                       comp_t;
    constexpr static size_t const   n_cols = 3;
    constexpr static size_t const   n_rows = 3;
    constexpr static size_t const   n_comp = 9;
    // Construction
                               mat3_t();
                               mat3_t( mat3_t const& copy );
                               mat3_t( comp_t e00, comp_t e10, comp_t e20,
                                       comp_t e01, comp_t e11, comp_t e21,
                                       comp_t e02, comp_t e12, comp_t e22 );
    // Named Construction
    static mat3_t<T>           column_vectors( vec3_t<comp_t> const& col0,
                                               vec3_t<comp_t> const& col1,
                                               vec3_t<comp_t> const& col2 );
    static mat3_t<T>           cross_product( vec3_t<comp_t> const& vec );
    static mat3_t<T>           homogenize( mat2_t<comp_t> const& amat );
    static mat3_t<T>           identity();
    static mat3_t<T>           row_vectors( vec3_t<comp_t> const& row0,
                                            vec3_t<comp_t> const& row1,
                                            vec3_t<comp_t> const& row2 );
    static mat3_t<T>           rotation( vec3_t<comp_t> const& axis,
                                         d_angle const& ang );
    static mat3_t<T>           rotation( d_angle const& angx,
                                         d_angle const& angy,
                                         d_angle const& angz );
    static mat3_t<T>           rotation( qutn_t<comp_t> const& qrot );
    static mat3_t<T>           scale( comp_t sx,
                                      comp_t sy,
                                      comp_t sz );
    static mat3_t<T>           scale( vec3_t<comp_t> const& svec );
    static mat3_t<T>           scale( vec2_t<comp_t> const& svec );
    static mat3_t<T>           square( vec3_t<comp_t> const& vec );
    static mat3_t<T>           translate( comp_t tx,
                                          comp_t ty );
    static mat3_t<T>           translate( vec2_t<comp_t> const& tvec );
    // Comparison
    bool                       operator==( mat3_t<T> const& rhs ) const;
    bool                       operator<( mat3_t<T> const& rhs ) const;
    bool                       operator>( mat3_t<T> const& rhs ) const;
    bool                       operator<=( mat3_t<T> const& rhs ) const;
    bool                       operator>=( mat3_t<T> const& rhs ) const;
    bool                       operator!=( mat3_t<T> const& rhs ) const;
    // Arithmetic
    mat3_t<T>                  operator+( mat3_t<T> const& rhs );
    mat3_t<T>                  operator-();
    mat3_t<T>                  operator-( mat3_t<T> const& rhs );
    mat3_t<T>                  operator*( mat3_t<T> const& rhs ) const;
    mat2x3_t<T>                operator*( mat2x3_t<T> const& rhs ) const;
    mat4x3_t<T>                operator*( mat4x3_t<T> const& rhs ) const;
    vec3_t<comp_t>             operator*( vec3_t<comp_t> const& rhs );
    template< typename D > friend
    vec3_t<D>                  operator*( vec3_t<D> const& lhs, mat3_t<D> const& rhs );
    mat3_t<T>                  operator*( comp_t rhs );
    template< typename D > friend
    mat3_t<D>                  operator*( D lhs, mat3_t<D> const& rhs );
    mat3_t<T>                  operator/( comp_t rhs );
    // Mutative Operators
    mat3_t<T>&                 operator=( mat3_t<T> const& rhs );
    col3<comp_t>               operator[]( size_t i );
    col3<comp_t>               operator[]( size_t i ) const;
    comp_t&                    operator()( size_t col,
                                           size_t row );
    comp_t                     operator()( size_t col,
                                           size_t row ) const;
    // Mutative Functions
    mat3_t<T>&                 column( size_t col,
                                       vec3_t<comp_t> const& val );
    vec3_t<T>                  column( size_t col ) const;
    mat3_t<T>&                 columns( vec3_t<comp_t> const& col0,
                                        vec3_t<comp_t> const& col1,
                                        vec3_t<comp_t> const& col2 );
    mat3_t<T>&                 fill( comp_t val );
    mat3_t<T>&                 norm();
    mat3_t<T>&                 row( size_t row,
                                    vec3_t<comp_t> const& val );
    vec3_t<T>                  row( size_t row ) const;
    mat3_t<T>&                 rows( vec3_t<comp_t> const& row0,
                                     vec3_t<comp_t> const& row1,
                                     vec3_t<comp_t> const& row2 );
    mat3_t<T>&                 transpose();
    mat3_t<T>&                 invert();
    // Utility
    virtual raw_map const   to_map() const;
    
    template< typename U > friend class mat3x4_t;
    template< typename U > friend class mat3x2_t;
protected:
    union {
        comp_t          c[9];
        unsigned char   bytes[sizeof(comp_t) * 9];
    } data;
};

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( mat3_t<T>, 9 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class mat4_t : public raw_mappable {
public:
    typedef T                       comp_t;
    constexpr static size_t const   n_cols = 4;
    constexpr static size_t const   n_rows = 4;
    constexpr static size_t const   n_comp = 16;
     
                               mat4_t();
                               mat4_t( mat4_t const& copy );
                               mat4_t( comp_t e00, comp_t e10, comp_t e20, comp_t e30,
                                       comp_t e01, comp_t e11, comp_t e21, comp_t e31,
                                       comp_t e02, comp_t e12, comp_t e22, comp_t e32,
                                       comp_t e03, comp_t e13, comp_t e23, comp_t e33 );
    static mat4_t<T>           identity();
    static mat4_t<T>           row_vectors( vec4_t<comp_t> const& row0,
                                            vec4_t<comp_t> const& row1,
                                            vec4_t<comp_t> const& row2,
                                            vec4_t<comp_t> const& row3 );
    static mat4_t<T>           column_vectors( vec4_t<comp_t> const& col0,
                                               vec4_t<comp_t> const& col1,
                                               vec4_t<comp_t> const& col2,
                                               vec4_t<comp_t> const& col3 );
    static mat4_t<T>           square( vec4_t<comp_t> const& vec );
    static mat4_t<T>           homogenize( mat3_t<comp_t> const& amat );
    static mat4_t<T>           scale( comp_t sx,
                                      comp_t sy,
                                      comp_t sz );
    static mat4_t<T>           scale( vec3_t<comp_t> const& svec );
    static mat4_t<T>           translate( comp_t tx,
                                          comp_t ty,
                                          comp_t tz );          
    static mat4_t<T>           translate( vec3_t<comp_t> const& tvec ); 
    static mat4_t<T>           cross_product( vec3_t<comp_t> const& vec );
    static mat4_t<T>           perspective( d_angle const& fovY,
                                            double aspect,
                                            double near,
                                            double far );
    static mat4_t<T>           rotation( vec3_t<comp_t> const& axis,
                                         d_angle const& ang );
    static mat4_t<T>           rotation( d_angle const& angx,
                                         d_angle const& angy,
                                         d_angle const& angz );
    static mat4_t<T>           rotation( qutn_t<comp_t> const& qrot );
    bool                       operator==( mat4_t<T> const& rhs ) const;
    bool                       operator<( mat4_t<T> const& rhs ) const;
    bool                       operator>( mat4_t<T> const& rhs ) const;
    bool                       operator<=( mat4_t<T> const& rhs ) const;
    bool                       operator>=( mat4_t<T> const& rhs ) const;
    bool                       operator!=( mat4_t<T> const& rhs ) const;
    mat4_t<T>&                 operator=( mat4_t<T> const& rhs );
    col4<comp_t>               operator[]( size_t i );
    col4<comp_t>               operator[]( size_t i ) const;
    comp_t&                    operator()( size_t col,
                                           size_t row );
    comp_t                     operator()( size_t col,
                                           size_t row ) const;
    mat4_t<T>                  operator+( mat4_t<T> const& rhs );
    mat4_t<T>                  operator-();
    mat4_t<T>                  operator-( mat4_t<T> const& rhs );
    mat4_t<T>                  operator*( mat4_t<T> const& rhs ) const;
    mat2x4_t<T>                operator*( mat2x4_t<T> const& rhs ) const;
    mat3x4_t<T>                operator*( mat3x4_t<T> const& rhs ) const;
    vec4_t<comp_t>             operator*( vec4_t<comp_t> const& rhs );
    template< typename D > friend
    vec4_t<D>                  operator*( vec4_t<D> const& lhs, mat4_t<D> const& rhs );
    mat4_t<T>                  operator*( comp_t rhs );
    template< typename D > friend
    mat4_t<D>                  operator*( D lhs, mat4_t<D> const& rhs );
    mat4_t<T>                  operator/( comp_t rhs );
    mat4_t<T>&                 fill( comp_t val );
    mat4_t<T>&                 row( size_t row,
                                    vec4_t<comp_t> const& val );
    vec4_t<T>                  row( size_t row ) const;
    mat4_t<T>&                 column( size_t col,
                                       vec4_t<comp_t> const& val );
    vec4_t<T>                  column( size_t col ) const;
    mat4_t<T>&                 rows( vec4_t<comp_t> const& row0,
                                     vec4_t<comp_t> const& row1,
                                     vec4_t<comp_t> const& row2,
                                     vec4_t<comp_t> const& row3 );
    mat4_t<T>&                 columns( vec4_t<comp_t> const& col0,
                                        vec4_t<comp_t> const& col1,
                                        vec4_t<comp_t> const& col2,
                                        vec4_t<comp_t> const& col3 );
    mat4_t<T>&                 components( comp_t e00, comp_t e10, comp_t e20, comp_t e30,
                                           comp_t e01, comp_t e11, comp_t e21, comp_t e31,
                                           comp_t e02, comp_t e12, comp_t e22, comp_t e32,
                                           comp_t e03, comp_t e13, comp_t e23, comp_t e33 );
    mat4_t<T>&                 transpose();
    mat4_t<T>&                 norm();
    mat4_t<T>&                 ortho();
    virtual raw_map const   to_map() const;
    
    template< typename U > friend class mat4x3_t;
    template< typename U > friend class mat4x2_t;
protected:
    union {
        comp_t          c[16];
        unsigned char   bytes[sizeof(comp_t) * 16];
    } data;
};

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( mat4_t<T>, 16 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class mat2x3_t : public raw_mappable {
public:
    typedef T               comp_t;
    size_t const            n_cols = 2;
    size_t const            n_rows = 3;
    size_t const            n_comp = 6;
    // Construction
                            mat2x3_t();
                            mat2x3_t( mat2x3_t const& copy );
                            mat2x3_t( comp_t e00, comp_t e10,
                                      comp_t e01, comp_t e11,
                                      comp_t e02, comp_t e12 );
                            mat2x3_t( comp_t fill );
                            mat2x3_t( vec3_t<comp_t> const& col0,
                                      vec3_t<comp_t> const& col1 );
    // Named Construction
    static mat2x3_t<T>      upper_identity();
    
    static mat2x3_t<T>      row_vectors( vec2_t<comp_t> const& row0,
                                         vec2_t<comp_t> const& row1,
                                         vec2_t<comp_t> const& row2 );
    // Comparison

    bool                    operator==( mat2x3_t<comp_t> const& rhs ) const;
    
    bool                    operator<( mat2x3_t<comp_t> const& rhs ) const;
    bool                    operator>( mat2x3_t<comp_t> const& rhs ) const;
    bool                    operator<=( mat2x3_t<comp_t> const& rhs ) const;
    bool                    operator>=( mat2x3_t<comp_t> const& rhs ) const;
    bool                    operator!=( mat2x3_t<comp_t> const& rhs ) const;
    // Arithmetic
    
    mat2x3_t<comp_t>        operator+( mat2x3_t<comp_t> const& rhs ) const;
    mat2x3_t<comp_t>        operator-() const;
    mat2x3_t<comp_t>        operator-( mat2x3_t<comp_t> const& rhs ) const;
    mat3_t<comp_t>          operator*( mat3x2_t<comp_t> const& rhs ) const;
    mat4x3_t<comp_t>        operator*( mat4x2_t<comp_t> const& rhs ) const;
    mat2x3_t<comp_t>        operator*( mat2_t<comp_t> const& rhs ) const;
    vec3_t<comp_t>          operator*( vec2_t<comp_t> const& rhs ) const;
    template<typename D > friend
    vec2_t<D>               operator*( vec3_t<D> const& lhs, mat2x3_t<D> const& rhs );
    mat2x3_t<comp_t>        operator*( comp_t rhs ) const;
    template< typename D > friend
    mat2x3_t<D>             operator*( D lhs, mat2x3_t<D> const& rhs );
    mat2x3_t<comp_t>        operator/( comp_t rhs ) const;
    // Mutatative Operators
    mat2x3_t<comp_t>&       operator=( mat2x3_t<comp_t> const& rhs );
    col3<comp_t>            operator[]( size_t i );
    col3<comp_t>            operator[]( size_t i ) const;
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
    // Mutative Functions
    col3<comp_t>            column( size_t col );
    col3<comp_t>            column( size_t col ) const;
    mat2x3_t<T>&            columns( vec3_t<comp_t> const& col0,
                                     vec3_t<comp_t> const& col1 );
    mat2x3_t<T>&            fill( comp_t val ); 
    row2<comp_t>            row( size_t row );
    row2<comp_t>            row( size_t row ) const;
    mat2x3_t<T>&            rows( vec2_t<comp_t> const& row0,
                                  vec2_t<comp_t> const& row1,
                                  vec2_t<comp_t> const& row2 );
    // Utility
    virtual raw_map const   to_map() const;
    
    template< typename U > friend class mat3_t;
    template< typename U > friend class mat3x2_t;
    template< typename U > friend class mat3x4_t;
protected:
    union {
        comp_t          c[6];
        unsigned char   bytes[sizeof(comp_t) * 6];
    } data;
};

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( mat2x3_t<T>, 6 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class mat3x2_t : public raw_mappable {
public:
    typedef T               comp_t;
    size_t const            n_cols = 3;
    size_t const            n_rows = 2;
    size_t const            n_comp = 6;
    // Construction
                            mat3x2_t();
                            mat3x2_t( mat3x2_t const& copy );
                            mat3x2_t( comp_t e00, comp_t e10, comp_t e20,
                                      comp_t e01, comp_t e11, comp_t e21 );
                            mat3x2_t( comp_t fill );
                            mat3x2_t( vec2_t<comp_t> const& col0,
                                      vec2_t<comp_t> const& col1,
                                      vec2_t<comp_t> const& col2 );
    // Named Construction
    static mat3x2_t<T>      left_identity();
    
    static mat3x2_t<T>      row_vectors( vec3_t<comp_t> const& row0,
                                         vec3_t<comp_t> const& row1 );
    // Comparison
    bool                    operator==( mat3x2_t<comp_t> const& rhs ) const;
    
    bool                    operator<( mat3x2_t<comp_t> const& rhs ) const;
    bool                    operator>( mat3x2_t<comp_t> const& rhs ) const;
    bool                    operator<=( mat3x2_t<comp_t> const& rhs ) const;
    bool                    operator>=( mat3x2_t<comp_t> const& rhs ) const;
    
    bool                    operator!=( mat3x2_t<comp_t> const& rhs ) const;
    // Arithmetic
    
    mat3x2_t<comp_t>        operator+( mat3x2_t<comp_t> const& rhs ) const;
    mat3x2_t<comp_t>        operator-() const;
    mat3x2_t<comp_t>        operator-( mat3x2_t<comp_t> const& rhs ) const;
    mat2_t<comp_t>          operator*( mat2x3_t<comp_t> const& rhs ) const;
    mat4x2_t<comp_t>        operator*( mat4x3_t<comp_t> const& rhs ) const;
    mat3x2_t<comp_t>        operator*( mat3_t<comp_t> const& rhs ) const;
    vec2_t<comp_t>          operator*( vec3_t<comp_t> const& rhs ) const;
    template<typename D > friend
    vec3_t<D>               operator*( vec2_t<D> const& lhs, mat3x2_t<D> const& rhs );
    mat3x2_t<comp_t>        operator*( comp_t rhs ) const;
    template< typename D > friend
    mat3x2_t<D>             operator*( D lhs, mat3x2_t<D> const& rhs );
    mat3x2_t<comp_t>        operator/( comp_t rhs ) const;
    // Mutatative Operators */
    mat3x2_t<comp_t>&       operator=( mat3x2_t<comp_t> const& rhs );
    col2<comp_t>            operator[]( size_t i );
    col2<comp_t>            operator[]( size_t i ) const;
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
    // Mutative Functions
    col2<comp_t>            column( size_t col );
    col2<comp_t>            column( size_t col ) const; 
    mat3x2_t<T>&            columns( vec2_t<comp_t> const& col0,
                                     vec2_t<comp_t> const& col1,
                                     vec2_t<comp_t> const& col2 );
    mat3x2_t<T>&            fill( comp_t val );
    row3<comp_t>            row( size_t row );
    row3<comp_t>            row( size_t row ) const;
    mat3x2_t<T>&            rows( vec3_t<comp_t> const& row0,
                                  vec3_t<comp_t> const& row1);
    // Utility
    virtual raw_map const   to_map() const;
    
    template< typename U > friend class mat2x4_t;
    template< typename U > friend class mat2x3_t;
    template< typename U > friend class mat2_t;
protected:
    union {
        comp_t          c[6];
        unsigned char   bytes[sizeof(comp_t) * 6];
    } data;
};

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( mat3x2_t<T>, 6 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class mat2x4_t : public raw_mappable {
public:
    typedef T               comp_t;
    size_t const            n_cols = 2;
    size_t const            n_rows = 4;
    size_t const            n_comp = 8;
    // Construction
                            mat2x4_t();
                            mat2x4_t( mat2x4_t const& copy );
                            mat2x4_t( comp_t e00, comp_t e10,
                                      comp_t e01, comp_t e11,
                                      comp_t e02, comp_t e12,
                                      comp_t e03, comp_t e13 );
                            mat2x4_t( comp_t fill );
                            mat2x4_t( vec4_t<comp_t> const& col0,
                                      vec4_t<comp_t> const& col1 );
    // Named Construction
    static mat2x4_t<T>      upper_identity();
    
    static mat2x4_t<T>      row_vectors( vec2_t<comp_t> const& row0,
                                         vec2_t<comp_t> const& row1,
                                         vec2_t<comp_t> const& row2,
                                         vec2_t<comp_t> const& row3 );
    // Comparison

    bool                    operator==( mat2x4_t<comp_t> const& rhs ) const;
    
    bool                    operator<( mat2x4_t<comp_t> const& rhs ) const;
    bool                    operator>( mat2x4_t<comp_t> const& rhs ) const;
    bool                    operator<=( mat2x4_t<comp_t> const& rhs ) const;
    bool                    operator>=( mat2x4_t<comp_t> const& rhs ) const;
    bool                    operator!=( mat2x4_t<comp_t> const& rhs ) const;
    // Arithmetic
    
    mat2x4_t<comp_t>        operator+( mat2x4_t<comp_t> const& rhs ) const;
    mat2x4_t<comp_t>        operator-() const;
    mat2x4_t<comp_t>        operator-( mat2x4_t<comp_t> const& rhs ) const;
    mat4_t<comp_t>          operator*( mat4x2_t<comp_t> const& rhs ) const;
    mat3x4_t<comp_t>        operator*( mat3x2_t<comp_t> const& rhs ) const;
    mat2x4_t<comp_t>        operator*( mat2_t<comp_t> const& rhs ) const;
    vec4_t<comp_t>          operator*( vec2_t<comp_t> const& rhs ) const;
    template<typename D > friend
    vec2_t<D>               operator*( vec4_t<D> const& lhs, mat2x4_t<D> const& rhs );
    mat2x4_t<comp_t>        operator*( comp_t rhs ) const;
    template< typename D > friend
    mat2x4_t<D>             operator*( D lhs, mat2x4_t<D> const& rhs );
    mat2x4_t<comp_t>        operator/( comp_t rhs ) const;
//     // Mutatative Operators
     mat2x4_t<comp_t>&       operator=( mat2x4_t<comp_t> const& rhs );
    col4<comp_t>            operator[]( size_t i );
    col4<comp_t>            operator[]( size_t i ) const;
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
//     // Mutative Functions
    col4<comp_t>            column( size_t col );
    col4<comp_t>            column( size_t col ) const;
    mat2x4_t<T>&            columns( vec4_t<comp_t> const& col0,
                                     vec4_t<comp_t> const& col1 );
    mat2x4_t<T>&            fill( comp_t val ); 
    row2<comp_t>            row( size_t row );
    row2<comp_t>            row( size_t row ) const;
    mat2x4_t<T>&            rows( vec2_t<comp_t> const& row0,
                                  vec2_t<comp_t> const& row1,
                                  vec2_t<comp_t> const& row2,
                                  vec2_t<comp_t> const& row3 );
    // Utility
    virtual raw_map const   to_map() const;
    
    template< typename U > friend class mat4_t;
    template< typename U > friend class mat4x2_t;
    template< typename U > friend class mat4x3_t;
protected:
    union {
        comp_t          c[8];
        unsigned char   bytes[sizeof(comp_t) * 8];
    } data;
};

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( mat2x4_t<T>, 8 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class mat4x2_t : public raw_mappable {
public:
    typedef T               comp_t;
    size_t const            n_cols = 4;
    size_t const            n_rows = 2;
    size_t const            n_comp = 8;
    // Construction
                            mat4x2_t();
                            mat4x2_t( mat4x2_t const& copy );
                            mat4x2_t( comp_t e00, comp_t e10, comp_t e20, comp_t e30,
                                      comp_t e01, comp_t e11, comp_t e21, comp_t e31 );
                            mat4x2_t( comp_t fill );
                            mat4x2_t( vec2_t<comp_t> const& col0,
                                      vec2_t<comp_t> const& col1,
                                      vec2_t<comp_t> const& col2,
                                      vec2_t<comp_t> const& col3 );
    // Named Construction
    static mat4x2_t<T>      left_identity();
    
    static mat4x2_t<T>      row_vectors( vec4_t<comp_t> const& row0,
                                         vec4_t<comp_t> const& row1 );
    // Comparison
    bool                    operator==( mat4x2_t<comp_t> const& rhs ) const;
    
    bool                    operator<( mat4x2_t<comp_t> const& rhs ) const;
    bool                    operator>( mat4x2_t<comp_t> const& rhs ) const;
    bool                    operator<=( mat4x2_t<comp_t> const& rhs ) const;
    bool                    operator>=( mat4x2_t<comp_t> const& rhs ) const;
    
    bool                    operator!=( mat4x2_t<comp_t> const& rhs ) const;
    // Arithmetic
    
    mat4x2_t<comp_t>        operator+( mat4x2_t<comp_t> const& rhs ) const;
    mat4x2_t<comp_t>        operator-() const;
    mat4x2_t<comp_t>        operator-( mat4x2_t<comp_t> const& rhs ) const;
    mat2_t<comp_t>          operator*( mat2x4_t<comp_t> const& rhs ) const;
    mat3x2_t<comp_t>        operator*( mat3x4_t<comp_t> const& rhs ) const;
    mat4x2_t<comp_t>        operator*( mat4_t<comp_t> const& rhs ) const;
    vec2_t<comp_t>          operator*( vec4_t<comp_t> const& rhs ) const;
    template<typename D > friend
    vec4_t<D>               operator*( vec2_t<D> const& lhs, mat4x2_t<D> const& rhs );
    mat4x2_t<comp_t>        operator*( comp_t rhs ) const;
    template< typename D > friend
    mat4x2_t<D>             operator*( D lhs, mat4x2_t<D> const& rhs );
    mat4x2_t<comp_t>        operator/( comp_t rhs ) const;
    // Mutatative Operators */
    mat4x2_t<comp_t>&       operator=( mat4x2_t<comp_t> const& rhs );
    col2<comp_t>            operator[]( size_t i );
    col2<comp_t>            operator[]( size_t i ) const;
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
    // Mutative Functions
    col2<comp_t>            column( size_t col );
    col2<comp_t>            column( size_t col ) const; 
    mat4x2_t<T>&            columns( vec2_t<comp_t> const& col0,
                                     vec2_t<comp_t> const& col1,
                                     vec2_t<comp_t> const& col2,
                                     vec2_t<comp_t> const& col3 );
    mat4x2_t<T>&            fill( comp_t val );
    row4<comp_t>            row( size_t row );
    row4<comp_t>            row( size_t row ) const;
    mat4x2_t<T>&            rows( vec4_t<comp_t> const& row0,
                                  vec4_t<comp_t> const& row1);
    // Utility
    virtual raw_map const   to_map() const;
    
    template< typename U > friend class mat2x4_t;
    template< typename U > friend class mat2x3_t;
    template< typename U > friend class mat2_t;
protected:
    union {
        comp_t          c[8];
        unsigned char   bytes[sizeof(comp_t) * 8];
    } data;
};

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( mat4x2_t<T>, 8 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class mat3x4_t : public raw_mappable {
public:
    typedef T               comp_t;
    size_t const            n_cols = 3;
    size_t const            n_rows = 4;
    size_t const            n_comp = 12;
    // Construction
                            mat3x4_t();
                            mat3x4_t( mat3x4_t const& copy );
                            mat3x4_t( comp_t e00, comp_t e10, comp_t e20,
                                      comp_t e01, comp_t e11, comp_t e21,
                                      comp_t e02, comp_t e12, comp_t e22,
                                      comp_t e03, comp_t e13, comp_t e23 );
                            mat3x4_t( comp_t fill );
                            mat3x4_t( vec4_t<comp_t> const& col0,
                                      vec4_t<comp_t> const& col1,
                                      vec4_t<comp_t> const& col2 );
    // Named Construction
    static mat3x4_t<T>      upper_identity();
    
    static mat3x4_t<T>      row_vectors( vec3_t<comp_t> const& row0,
                                         vec3_t<comp_t> const& row1,
                                         vec3_t<comp_t> const& row2,
                                         vec3_t<comp_t> const& row3 );
    // Comparison

    bool                    operator==( mat3x4_t<comp_t> const& rhs ) const;
    
    bool                    operator<( mat3x4_t<comp_t> const& rhs ) const;
    bool                    operator>( mat3x4_t<comp_t> const& rhs ) const;
    bool                    operator<=( mat3x4_t<comp_t> const& rhs ) const;
    bool                    operator>=( mat3x4_t<comp_t> const& rhs ) const;
    bool                    operator!=( mat3x4_t<comp_t> const& rhs ) const;
    // Arithmetic
    
    mat3x4_t<comp_t>        operator+( mat3x4_t<comp_t> const& rhs ) const;
    mat3x4_t<comp_t>        operator-() const;
    mat3x4_t<comp_t>        operator-( mat3x4_t<comp_t> const& rhs ) const;
    mat4_t<comp_t>          operator*( mat4x3_t<comp_t> const& rhs ) const;
    mat2x4_t<comp_t>        operator*( mat2x3_t<comp_t> const& rhs ) const;
    mat3x4_t<comp_t>        operator*( mat3_t<comp_t> const& rhs ) const;
    vec4_t<comp_t>          operator*( vec3_t<comp_t> const& rhs ) const;
    template<typename D > friend
    vec3_t<D>               operator*( vec4_t<D> const& lhs, mat3x4_t<D> const& rhs );
    mat3x4_t<comp_t>        operator*( comp_t rhs ) const;
    template< typename D > friend
    mat3x4_t<D>             operator*( D lhs, mat3x4_t<D> const& rhs );
    mat3x4_t<comp_t>        operator/( comp_t rhs ) const;
//     // Mutatative Operators
    mat3x4_t<comp_t>&       operator=( mat3x4_t<comp_t> const& rhs );
    col4<comp_t>            operator[]( size_t i );
    col4<comp_t>            operator[]( size_t i ) const;
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
//     // Mutative Functions
    col4<comp_t>            column( size_t col );
    col4<comp_t>            column( size_t col ) const;
    mat3x4_t<T>&            columns( vec4_t<comp_t> const& col0,
                                     vec4_t<comp_t> const& col1,
                                     vec4_t<comp_t> const& col2 );
    mat3x4_t<T>&            fill( comp_t val ); 
    row3<comp_t>            row( size_t row );
    row3<comp_t>            row( size_t row ) const;
    mat3x4_t<T>&            rows( vec3_t<comp_t> const& row0,
                                  vec3_t<comp_t> const& row1,
                                  vec3_t<comp_t> const& row2,
                                  vec3_t<comp_t> const& row3 );
    // Utility
    virtual raw_map const   to_map() const;
    
    template< typename U > friend class mat4_t;
    template< typename U > friend class mat4x3_t;
    template< typename U > friend class mat4x2_t;
protected:
    union {
        comp_t          c[12];
        unsigned char   bytes[sizeof(comp_t) * 12];
    } data;
};

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( mat3x4_t<T>, 12 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

template< typename T >
class mat4x3_t : public raw_mappable {
public:
    typedef T               comp_t;
    size_t const            n_cols = 4;
    size_t const            n_rows = 3;
    size_t const            n_comp = 12;
    // Construction
                            mat4x3_t();
                            mat4x3_t( mat4x3_t const& copy );
                            mat4x3_t( comp_t e00, comp_t e10, comp_t e20, comp_t e30,
                                      comp_t e01, comp_t e11, comp_t e21, comp_t e31,
                                      comp_t e02, comp_t e12, comp_t e22, comp_t e32 );
                            mat4x3_t( comp_t fill );
                            mat4x3_t( vec3_t<comp_t> const& col0,
                                      vec3_t<comp_t> const& col1,
                                      vec3_t<comp_t> const& col2,
                                      vec3_t<comp_t> const& col3 );
    // Named Construction
    static mat4x3_t<T>      left_identity();
    static mat4x3_t<T>      row_vectors( vec4_t<comp_t> const& row0,
                                         vec4_t<comp_t> const& row1,
                                         vec4_t<comp_t> const& row2 );
    // Comparison

    bool                    operator==( mat4x3_t<comp_t> const& rhs ) const;
    
    bool                    operator<( mat4x3_t<comp_t> const& rhs ) const;
    bool                    operator>( mat4x3_t<comp_t> const& rhs ) const;
    bool                    operator<=( mat4x3_t<comp_t> const& rhs ) const;
    bool                    operator>=( mat4x3_t<comp_t> const& rhs ) const;
    bool                    operator!=( mat4x3_t<comp_t> const& rhs ) const;
    // Arithmetic
    
    mat4x3_t<comp_t>        operator+( mat4x3_t<comp_t> const& rhs ) const;
    mat4x3_t<comp_t>        operator-() const;
    mat4x3_t<comp_t>        operator-( mat4x3_t<comp_t> const& rhs ) const;
    mat3_t<comp_t>          operator*( mat3x4_t<comp_t> const& rhs ) const;
    mat2x3_t<comp_t>        operator*( mat2x4_t<comp_t> const& rhs ) const;
    mat4x3_t<comp_t>        operator*( mat4_t<comp_t> const& rhs ) const;
    vec3_t<comp_t>          operator*( vec4_t<comp_t> const& rhs ) const;
    template<typename D > friend
    vec4_t<D>               operator*( vec3_t<D> const& lhs, mat4x3_t<D> const& rhs );
    mat4x3_t<comp_t>        operator*( comp_t rhs ) const;
    template< typename D > friend
    mat4x3_t<D>             operator*( D lhs, mat4x3_t<D> const& rhs );
    mat4x3_t<comp_t>        operator/( comp_t rhs ) const;
    // Mutatative Operators
    mat4x3_t<comp_t>&       operator=( mat4x3_t<comp_t> const& rhs );
    col3<comp_t>            operator[]( size_t i );
    col3<comp_t>            operator[]( size_t i ) const;
    comp_t&                 operator()( size_t col,
                                        size_t row );
    comp_t                  operator()( size_t col,
                                        size_t row ) const;
    // Mutative Functions
    col3<comp_t>            column( size_t col );
    col3<comp_t>            column( size_t col ) const;
    mat4x3_t<T>&            columns( vec3_t<comp_t> const& col0,
                                     vec3_t<comp_t> const& col1,
                                     vec3_t<comp_t> const& col2,
                                     vec3_t<comp_t> const& col3 );
    mat4x3_t<T>&            fill( comp_t val ); 
    row4<comp_t>            row( size_t row );
    row4<comp_t>            row( size_t row ) const;
    mat4x3_t<T>&            rows( vec4_t<comp_t> const& row0,
                                  vec4_t<comp_t> const& row1,
                                  vec4_t<comp_t> const& row2 );
    // Utility
    virtual raw_map const   to_map() const;
    
    template< typename U > friend class mat3_t;
    template< typename U > friend class mat3x4_t;
    template< typename U > friend class mat3x2_t;
protected:
    union {
        comp_t          c[12];
        unsigned char   bytes[sizeof(comp_t) * 12];
    } data;
};

// WARNING This is dangerous dark magics. DO NOT touch anything to do with
// this typeinfo system unless you know PRECISELY what you are doing.
// Mixing macros and templates is spooky stuff.
template< typename T >
G_TYPE( mat4x3_t<T>, 12 * type<T>().n_c(), type<T>().component_size(), type<T>().component_to_GL(), type<T>().mapping() );

typedef     mat_t<float>            mat;
typedef     mat2_t<float>           mat2;
typedef     mat3_t<float>           mat3;
typedef     mat4_t<float>           mat4;
typedef     mat2x3_t<float>         mat2x3;
typedef     mat3x2_t<float>         mat3x2;
typedef     mat2x4_t<float>         mat2x4;
typedef     mat4x2_t<float>         mat4x2;
typedef     mat3x4_t<float>         mat3x4;
typedef     mat4x3_t<float>         mat4x3;

typedef     mat_t<double>           dmat;
typedef     mat2_t<double>          dmat2;
typedef     mat3_t<double>          dmat3;
typedef     mat4_t<double>          dmat4;
typedef     mat2x3_t<double>        dmat2x3;
typedef     mat3x2_t<double>        dmat3x2;
typedef     mat2x4_t<double>        dmat2x4;
typedef     mat4x2_t<double>        dmat4x2;
typedef     mat3x4_t<double>        dmat3x4;
typedef     mat4x3_t<double>        dmat4x3;


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
scalar<T>::scalar() : data( {lit<T>::zero} ) {}

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
    return     std::abs(data.c[0] - rhs.data.c[0]) < lit<T>::delta
           and std::abs(data.c[1] - rhs.data.c[1]) < lit<T>::delta;
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
inline vec3_t<T> vec3_t<T>::operator-() const
{
    return vec3_t<T>( -data.c[0],
                      -data.c[1],
                      -data.c[2] );
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
    return     std::abs(data.c[0] - rhs.data.c[0]) < lit<T>::delta
           and std::abs(data.c[1] - rhs.data.c[1]) < lit<T>::delta
           and std::abs(data.c[2] - rhs.data.c[2]) < lit<T>::delta;
}

template<typename T> inline
bool    vec3_t<T>::operator!=( vec3_t<T> const& rhs ) const
{
    return     std::abs(data.c[0] - rhs.data.c[0]) >= lit<T>::delta
           or  std::abs(data.c[1] - rhs.data.c[1]) >= lit<T>::delta
           or  std::abs(data.c[2] - rhs.data.c[2]) >= lit<T>::delta;
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
                    
template< typename T > inline
vec4_t<T>::vec4_t( vec3_t<T> const& xyz,
                   T cw                 ) :
            data( {{ xyz(x),
                     xyz(y),
                     xyz(z),
                     cw }} ) {}

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
    return     std::abs(data.c[0] - rhs.data.c[0]) < lit<T>::delta
           and std::abs(data.c[1] - rhs.data.c[1]) < lit<T>::delta
           and std::abs(data.c[2] - rhs.data.c[2]) < lit<T>::delta
           and std::abs(data.c[3] - rhs.data.c[3]) < lit<T>::delta;
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
    this->data.c[0] = lit<T>::zero;
    this->data.c[1] = lit<T>::zero;
    this->data.c[2] = lit<T>::zero;
    this->data.c[3] = lit<T>::one;
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
    return qutn_t( point[0], point[1], point[2], lit<T>::zero );
}

template< typename T > inline
qutn_t<T>     qutn_t<T>::rotation( mat3_t<T> const& rmat )
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
    return     std::abs(data.c[0] - rhs.data.c[0]) < lit<T>::delta
           and std::abs(data.c[1] - rhs.data.c[1]) < lit<T>::delta
           and std::abs(data.c[2] - rhs.data.c[2]) < lit<T>::delta
           and std::abs(data.c[3] - rhs.data.c[3]) < lit<T>::delta;
}

template< typename T > inline
bool    qutn_t<T>::operator!=( qutn_t<T> const& rhs ) const
{
    return    std::abs(data.c[0] - rhs.data.c[0]) >= lit<T>::delta
           or std::abs(data.c[1] - rhs.data.c[1]) >= lit<T>::delta
           or std::abs(data.c[2] - rhs.data.c[2]) >= lit<T>::delta
           or std::abs(data.c[3] - rhs.data.c[3]) >= lit<T>::delta;
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

template< typename T > inline
vec3_t<T>   qutn_t<T>::rotate( vec3_t<T> const& avec ) const
{
    qutn_t<T> pure_q = qutn_t<T>::pure( avec );
    pure_q = (*this) * pure_q * -(*this);
    return vec3_t<T>( pure_q(i), pure_q(j), pure_q(k) );
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
inline mat_t<T> mat_t<T>::rows( T rows[R][C] )
{
    mat_t<C,R,T> a_mat;
    
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
inline mat_t<C,R,T> mat_t<C,R,T>::columns( T cols[C][R] )
{
    mat_t<C,R,T> a_mat;
    
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
row2<T>::row2( row2<T> const& arow )
{
    this->c0 = new T;
    this->c1 = new T;
    *this->c0 = arow[0];
    *this->c1 = arow[1];
    live_handle = false;
}

template< typename T > inline
row2<T>&    row2<T>::operator=( vec2_t<T> const& avec )
{
    *this->c0 = avec[0];
    *this->c1 = avec[1];
    return *this;
}

template< typename T > inline
row2<T>&    row2<T>::operator=( row2<T> const& arow )
{
    *this->c0 = arow[0];
    *this->c1 = arow[1];
    return *this;
}

template< typename T > inline
T&      row2<T>::operator[]( size_t i )
{
    switch( i ) {
        case 0:
            return *c0;
        case 1:
            return *c1;
        default:
        throw std::out_of_range( "index on lookup of row2 vector out of range." );
    }
}

template< typename T > inline
T       row2<T>::operator[]( size_t i ) const
{
    switch( i ) {
        case 0:
            return *c0;
        case 1:
            return *c1;
        default:
        throw std::out_of_range( "index on lookup of row2 vector out of range." );
    }
}

template< typename T > inline
row2<T>::operator vec2_t<T>() const
{
    return vec2_t<T>( *this->c0, *this->c1 );
}

template< typename T > inline
row2<T>::~row2()
{
    if ( !live_handle ) { delete c0; delete c1; }
}

template< typename T > inline
row2<T>::row2( comp_t* c0_adr,
               comp_t* c1_adr,
               bool liveness )
{
    this->c0 = c0_adr;
    this->c1 = c1_adr;
    this->live_handle = liveness;
}

template< typename T > inline
row2<T>::row2( vec2_t<T> const& avec )
{
    this->c0 = new T;
    this->c1 = new T;
    this->*c0 = avec[0];
    this->*c1 = avec[1];
    live_handle = false;
}

template< typename T > inline
row2<T>::row2( T c0_val,
               T c1_val )
{
    this->c0 = new T;
    this->c1 = new T;
    this->*c0 = c0_val;
    this->*c1 = c1_val;
    live_handle = false;
}

template< typename T > inline
std::ostream&   operator<<( std::ostream& out,
                            row2<T> const& rhs )
{
    out << "[ " << rhs[0] << " " << rhs[1] << " ]" << std::endl;
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
row3<T>::row3( row3<T> const& acol )
{
    this->c0 = new T;
    this->c1 = new T;
    this->c2 = new T;
    *this->c0 = acol[0];
    *this->c1 = acol[1];
    *this->c2 = acol[2];
    this->live_handle = false;
}

template< typename T > inline
row3<T>&    row3<T>::operator=( vec3_t<T> const& avec )
{
    *this->c0 = avec[0];
    *this->c1 = avec[1];
    *this->c2 = avec[2];
    return *this;
}

template< typename T > inline
row3<T>&    row3<T>::operator=( row3<T> const& acol )
{
    *this->c0 = acol[0];
    *this->c1 = acol[1];
    *this->c2 = acol[2];
    return *this;
}

template< typename T > inline
T&      row3<T>::operator[]( size_t i )
{
    switch ( i ) {
        case 0:
            return *c0;
        case 1:
            return *c1;
        case 2:
            return *c2;
        default:
            throw std::out_of_range( "index on lookup of row vector out of range." );
    }
}

template< typename T > inline
T       row3<T>::operator[]( size_t i ) const
{
    switch ( i ) {
        case 0:
            return *c0;
        case 1:
            return *c1;
        case 2:
            return *c2;
        default:
            throw std::out_of_range( "index on lookup of row vector out of range." );
    }
}

template< typename T > inline
row3<T>::operator vec3_t<T>() const
{
    return vec3_t<T>( *c0, *c1, *c2 );
}

template< typename T > inline
row3<T>::~row3()
{
    if ( !live_handle ) {
        delete c0;
        delete c1;
        delete c2;        
    }
}

template< typename T > inline
row3<T>::row3( T* c0_adr,
               T* c1_adr,
               T* c2_adr,
               bool liveness )
{
    this->c0 = c0_adr;
    this->c1 = c1_adr;
    this->c2 = c2_adr;
    this->live_handle = liveness;
}

template< typename T > inline
std::ostream&   operator<<( std::ostream& out,
                            row3<T> const& rhs )
{
    out << "[ " << rhs[0] << " " << rhs[1];
    out << " " << rhs[2] << " ]" << std::endl;
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
row4<T>::row4( row4<T> const& acol )
{
    this->c0 = new T;
    this->c1 = new T;
    this->c2 = new T;
    this->c3 = new T;
    *this->c0 = acol[0];
    *this->c1 = acol[1];
    *this->c2 = acol[2];
    *this->c3 = acol[3];
    this->live_handle = false;
}

template< typename T > inline
row4<T>&    row4<T>::operator=( vec4_t<T> const& avec )
{
    *this->c0 = avec[0];
    *this->c1 = avec[1];
    *this->c2 = avec[2];
    *this->c3 = avec[3];
    return *this;
}

template< typename T > inline
row4<T>&    row4<T>::operator=( row4<T> const& acol )
{
    *this->c0 = acol[0];
    *this->c1 = acol[1];
    *this->c2 = acol[2];
    *this->c3 = acol[3];
    return *this;
}

template< typename T > inline
T&      row4<T>::operator[]( size_t i )
{
    switch ( i ) {
        case 0:
            return *c0;
        case 1:
            return *c1;
        case 2:
            return *c2;
        case 3:
            return *c3;
        default:
            throw std::out_of_range( "index on lookup of row vector out of range." );
    }
}

template< typename T > inline
T       row4<T>::operator[]( size_t i ) const
{
    switch ( i ) {
        case 0:
            return *c0;
        case 1:
            return *c1;
        case 2:
            return *c2;
        case 3:
            return *c3;
        default:
            throw std::out_of_range( "index on lookup of row vector out of range." );
    }
}

template< typename T > inline
row4<T>::operator vec4_t<T>() const
{
    return vec4_t<T>( *c0, *c1, *c2, *c3 );
}

template< typename T > inline
row4<T>::~row4()
{
    if ( !live_handle ) {
        delete c0;
        delete c1;
        delete c2;
        delete c3;
    }
}

template< typename T > inline
row4<T>::row4( T* c0_adr,
               T* c1_adr,
               T* c2_adr,
               T* c3_adr,
               bool liveness )
{
    this->c0 = c0_adr;
    this->c1 = c1_adr;
    this->c2 = c2_adr;
    this->c3 = c3_adr;
    this->live_handle = liveness;
}

template< typename T > inline
std::ostream&   operator<<( std::ostream& out,
                            row4<T> const& rhs )
{
    out << "[ " << rhs[0] << " " << rhs[1];
    out << " " << rhs[2] << " " << rhs[3] << " ]" << std::endl;
    return out;
}






template< typename T > inline
mat_t<T>::mat_t() : cols( 1 ), rows( 1 ), comp( 1 )
{
    data = new mat_data( this );
    data->c[0] = lit<T>::zero;
}

template< typename T > inline
mat_t<T>::mat_t( mat_t<T> const& copy)
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
mat_t<T>::mat_t( size_t new_n_cols, size_t new_n_rows )
           : cols( new_n_cols ), rows( new_n_rows ),
             comp( cols * rows )
{ // TODO Need to throw an exception when dimensions are zero
    data = new mat_data( this );
    size_t i = comp;
    while( i ){ data->c[--i] = lit<T>::zero; }
}

template< typename T >
inline mat_t<T> mat_t<T>::fill( size_t new_n_cols, size_t new_n_rows,
                    comp_t const val )
{
    mat_t<T> out( new_n_cols, new_n_rows );
    
    size_t i = out.comp;
    T* out_cm = out.data->c;
    
    while(i) { out_cm[--i] = val; }
    
    return out;
}

template< typename T >
inline mat_t<T> mat_t<T>::identity( size_t new_dim )
{
    mat_t<T> a_mat( new_dim, new_dim );
    
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
    while(i) { a_mat.data->c[ --i * new_dim ] = lit<T>::one; }
    
    return a_mat;
}

template< typename T >
mat_t<T>::~mat_t() { delete data; }

template< typename T > inline
size_t      mat_t<T>::n_cols() const
{ return this->cols; }

template< typename T > inline
size_t      mat_t<T>::n_rows() const
{ return this->rows; }

template< typename T > inline
size_t      mat_t<T>::n_comp() const
{ return this->comp; }

template< typename T > inline
bool    mat_t<T>::operator==( mat_t<T> const& rhs ) const
{
    size_t i = comp;
    bool equal = true;
    if ( rows == rhs.rows and cols == rhs.cols ) {
        while (i) {
            --i;
            equal =     equal
                    and abs(data->c[i] - rhs.data->c[i]) < lit<T>::delta;
        }
    } else {
        equal = false;
    }
    return equal;
}

template< typename T > inline
bool    mat_t<T>::operator!=( mat_t<T> const& rhs ) const
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
mat_t<T>&     mat_t<T>::operator=( mat_t<T> const& rhs)
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
inline T& mat_t<T>::operator()( size_t col, size_t row )
{ return data->c[col * rows + row]; }

template< typename T >
inline T mat_t<T>::operator()( size_t col, size_t row ) const
{ return data->c[col * rows + row]; }

template< typename T >
inline mat_t<T> mat_t<T>::operator+( mat_t<T> const& rhs ) const
{
    if( cols != rhs.cols || rows != rhs.rows ){
        throw std::invalid_argument("matrices not dimensionally similar on addition.");
    }
    
    mat_t<T> out( cols, rows );
    
    size_t i = comp;
    
    T const* lhs_c = data->c;
    T const* rhs_c = rhs.data->c;
    T* out_c = out.data->c;
    
    while(i) { --i; out_c[i] = lhs_c[i] + rhs_c[i]; }
    
    return out;
}

template< typename T >
inline mat_t<T> mat_t<T>::operator-( mat_t<T> const& rhs ) const
{
    if( cols != rhs.cols || rows != rhs.rows ){
        throw std::invalid_argument("matrices not dimensionally similar on addition.");
    }
    
    mat_t<T> out( cols, rows );
    
    size_t i = comp;
    
    T const* lhs_cm = data->c;
    T const* rhs_cm = rhs.data->c;
    T* out_cm = out.data->c;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] - rhs_cm[i]; }
    
    return out;
}

template< typename T >
inline mat_t<T> mat_t<T>::operator*( mat_t<T> const& rhs ) const
{   
    if( cols != rhs.rows ){
        throw std::invalid_argument("row, column mismatch on multiplication.");
    }
    
    size_t element = 0;
    size_t addend = 0;

    T val = lit<T>::zero;

    mat_t<T> out( rhs.cols, rows );
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
        val = lit<T>::zero;
    }

    return out;
}

template< typename T >
inline mat_t<T> mat_t<T>::operator*( T rhs )
{
    mat_t<T> out( cols, rows );
    size_t i = comp;
    
    T* out_cm = out.data->c;
    T const* lhs_cm = data->c;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] * rhs; }
    
    return out;
}

template< typename T >
inline mat_t<T> operator*( T lhs, mat_t<T> const& rhs )
{
    mat_t<T> out( rhs.cols, rhs.rows );
    size_t i = rhs.comp;
    
    T* out_cm = out.data->c;
    T const* rhs_cm = rhs.data->c;
    
    while(i) { --i; out_cm[i] = rhs_cm[i] * lhs; }
    
    return out;
}

template< typename T >
inline mat_t<T> mat_t<T>::operator*( scalar<T> rhs )
{
    mat_t<T> out( cols, rows );
    size_t i = comp;
    
    T* out_cm = out.data->c;
    T const* lhs_cm = data->c;
    T factor = rhs;
    while(i) { --i; out_cm[i] = lhs_cm[i] * factor; }
    
    return out;
}

template< typename T >
inline mat_t<T> operator*( scalar<T> lhs, mat_t<T> const& rhs )
{
    mat_t<T> out( rhs.cols, rhs.rows );
    size_t i = rhs.comp;
    
    T* out_cm = out.data->c;
    T const* rhs_cm = rhs.data->c;
    T factor = lhs;
    
    while(i) { --i; out_cm[i] = rhs_cm[i] * factor; }
    
    return out;
}

template< typename T >
inline mat_t<T> mat_t<T>::operator/( T rhs )
{
    mat_t<T> out( cols, rows );
    size_t i = comp;
    
    T* out_cm = out.data->c;
    T const* lhs_cm = data->c;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] / rhs; }
    
    return out;
}

template< typename T >
inline mat_t<T> mat_t<T>::operator/( scalar<T> rhs )
{
    mat_t<T> out( cols, rows );
    size_t i = comp;
    
    T* out_cm = out.data->c;
    T const* lhs_cm = data->c;
    T factor = rhs;
    
    while(i) { --i; out_cm[i] = lhs_cm[i] / factor; }
    
    return out;
}

template< typename T >
inline mat_t<T>& mat_t<T>::fill( comp_t const val )
{    
    size_t i = comp;
    T* cm = data->c;
    
    while(i) { cm[--i] = val; }
    
    return *this;
}

template< typename T >
mat_t<T>& mat_t<T>::transpose()
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
raw_map const mat_t<T>::to_map() const
{ return map_bytes( data->n_bytes(), data->bytes() ); }

template< typename T >
inline mat_t<T>::mat_data::mat_data( mat_t<T>* new_owner )
{
    this->owner = new_owner;
    if ( owner->comp > 0 ) {
        c = new comp_t[owner->comp];
    } else {
        c = 0;
    }
}

template< typename T >
inline mat_t<T>::mat_data::~mat_data()
{ 
    if( owner->comp > 0 ) { delete[] c; }
}

template< typename T >
typename mat_t<T>::mat_data* mat_t<T>::mat_data::clone()
{
    mat_t<T>::mat_data* new_clone;
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
inline size_t mat_t<T>::mat_data::n_bytes()
{ return owner->comp * sizeof( comp_t ); }

template< typename T >
inline unsigned char const* mat_t<T>::mat_data::bytes()
{ return (unsigned char*) c; }

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat_t<T> const& src )
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
inline mat_t<C,R,T>& mat_t<C,R,T>::norm( bool ignore_translate = false )
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
mat2_t<T>::mat2_t()
{ T* c = this->data.c;
  // As much as I think this formatting aids in comprehension,
  // I have a sneaking suspicion that it may in fact
  // sabotage optimization efforts by the compiler and
  // prediction efforts by the processor. It must be
  // profiled and tested at some point.
  c[0] = lit<T>::zero;   c[2] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[3] = lit<T>::zero; }

template< typename T > inline
mat2_t<T>::mat2_t( mat2_t<T> const& copy )
{ T* c = this->data.c;
  c[0] = copy.data.c[0];
  c[1] = copy.data.c[1];
  c[2] = copy.data.c[2];
  c[3] = copy.data.c[3]; }
  
template< typename T >
mat2_t<T>::mat2_t( T e00, T e10,
               T e01, T e11 )
{ T* c = this->data.c;
  c[0] = e00;   c[2] = e10;
  c[1] = e01;   c[3] = e11; }

// Named Construction

template< typename T > inline
mat2_t<T>     mat2_t<T>::column_vectors( vec2_t<T> const& col0,
                                     vec2_t<T> const& col1 )
{ return mat2_t( col0(x), col1(x),
               col0(y), col1(y) ); }

template< typename T >
mat2_t<T>     mat2_t<T>::identity()
{ return mat2_t<T>( lit<T>::one,  lit<T>::zero,
                  lit<T>::zero, lit<T>::one   ); }

template< typename T > inline
mat2_t<T>     mat2_t<T>::row_vectors( vec2_t<T> const& row0,
                                  vec2_t<T> const& row1 )
{ return mat2_t( row0(x), row0(y),
               row1(x), row1(y) ); }

template< typename T > inline
mat2_t<T>     mat2_t<T>::scale( T sx, T sy )
{ return mat2_t( sx,           lit<T>::zero,
               lit<T>::zero, sy            ); }
               
template< typename T > inline
mat2_t<T>     mat2_t<T>::scale( vec2_t<T> const& svec )
{ return mat2_t( svec(x),      lit<T>::zero,
               lit<T>::zero, svec(y)       ); }

template< typename T > inline
mat2_t<T>   mat2_t<T>::rotation( d_angle const& ang )
{
     double radians ( ang.to_rads() );
     float cos_rad = std::cos( radians );
     float sin_rad = std::sin( radians );
     
     return mat2_t<T>( cos_rad, -sin_rad,
                     sin_rad, cos_rad );
}
               
// Comparison
               
template< typename T > inline
bool    mat2_t<T>::operator==( mat2_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs(lhs_c[0] - rhs_c[0]) < lit<T>::delta
           and std::abs(lhs_c[1] - rhs_c[1]) < lit<T>::delta
           and std::abs(lhs_c[2] - rhs_c[2]) < lit<T>::delta
           and std::abs(lhs_c[3] - rhs_c[3]) < lit<T>::delta;
}

template< typename T > inline
bool    mat2_t<T>::operator<( mat2_t<T> const& rhs ) const
{
    T* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    return     lhs_c[0] < rhs_c[0]
           and lhs_c[1] < rhs_c[1]
           and lhs_c[2] < rhs_c[2]
           and lhs_c[3] < rhs_c[3];
}

template< typename T > inline
bool    mat2_t<T>::operator>( mat2_t<T> const& rhs ) const
{
    T* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    return     lhs_c[0] > rhs_c[0]
           and lhs_c[1] > rhs_c[1]
           and lhs_c[2] > rhs_c[2]
           and lhs_c[3] > rhs_c[3];
}

template< typename T > inline
bool    mat2_t<T>::operator<=( mat2_t<T> const& rhs ) const
{
    T* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    return     lhs_c[0] <= rhs_c[0]
           and lhs_c[1] <= rhs_c[1]
           and lhs_c[2] <= rhs_c[2]
           and lhs_c[3] <= rhs_c[3];
}

template< typename T > inline
bool    mat2_t<T>::operator>=( mat2_t<T> const& rhs ) const
{
    T* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    return     lhs_c[0] >= rhs_c[0]
           and lhs_c[1] >= rhs_c[1]
           and lhs_c[2] >= rhs_c[2]
           and lhs_c[3] >= rhs_c[3];
}

template< typename T > inline
bool    mat2_t<T>::operator!=( mat2_t<T> const& rhs ) const
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
mat2_t<T>     mat2_t<T>::operator+( mat2_t<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] + rhs_c[0];
    T e01 = lhs_c[1] + rhs_c[1];
    T e10 = lhs_c[2] + rhs_c[2];
    T e11 = lhs_c[3] + rhs_c[3];
    
    return mat2_t( e00, e10,
                 e01, e11 );
}

template< typename T > inline
mat2_t<T>     mat2_t<T>::operator-()
{
    T const* lhs_c = this->data.c;
    
    T e00 = -lhs_c[0];
    T e01 = -lhs_c[1];
    T e10 = -lhs_c[2];
    T e11 = -lhs_c[3];
    
    return mat2_t( e00, e10,
                 e01, e11 );
}

template< typename T > inline
mat2_t<T>     mat2_t<T>::operator-( mat2_t<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] - rhs_c[0];
    T e01 = lhs_c[1] - rhs_c[1];
    T e10 = lhs_c[2] - rhs_c[2];
    T e11 = lhs_c[3] - rhs_c[3];
    
    return mat2_t( e00, e10,
                 e01, e11 );
}
               
template< typename T > inline
mat2_t<T>     mat2_t<T>::operator*( mat2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1];
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[2] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[3] * rhs_c[3];
    
    return mat2_t( e00, e10,
                 e01, e11 );
}

template< typename T > inline
mat3x2_t<T>     mat2_t<T>::operator*( mat3x2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1];
    
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[2] * rhs_c[3];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[3] * rhs_c[3];
    
    T e20 = lhs_c[0] * rhs_c[4] + lhs_c[2] * rhs_c[5];
    T e21 = lhs_c[1] * rhs_c[4] + lhs_c[3] * rhs_c[5];
    
    return mat3x2_t<T>( e00, e10, e20,
                        e01, e11, e21 );
}

template< typename T > inline
mat4x2_t<T>     mat2_t<T>::operator*( mat4x2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1];
    
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[2] * rhs_c[3];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[3] * rhs_c[3];
    
    T e20 = lhs_c[0] * rhs_c[4] + lhs_c[2] * rhs_c[5];
    T e21 = lhs_c[1] * rhs_c[4] + lhs_c[3] * rhs_c[5];
    
    T e30 = lhs_c[0] * rhs_c[6] + lhs_c[2] * rhs_c[7];
    T e31 = lhs_c[1] * rhs_c[6] + lhs_c[3] * rhs_c[7];
    
    return mat4x2_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31 );
}

template< typename T > inline
vec2_t<T>     mat2_t<T>::operator*( vec2_t<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T x0 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1];
    T x1 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1];
    
    return vec2_t<T>( x0, x1 );
}

template< typename T > inline
vec2_t<T>     operator*( vec2_t<T> const& lhs,
                       mat2_t<T> const& rhs )
{
    T const* lhs_c = lhs.data.c;
    T const* rhs_c = rhs.data.c;
    
    T x0 = lhs_c[0] * rhs_c[0] + lhs_c[1] * rhs_c[1];
    T x1 = lhs_c[0] * rhs_c[2] + lhs_c[1] * rhs_c[3];
    
    return vec2_t<T>( x0, x1 );
}
template< typename T >
mat2_t<T>     mat2_t<T>::operator*( T rhs )
{
    T const* rhs_c = this->data.c;
    
    T e00 = rhs_c[0] * rhs;
    T e01 = rhs_c[1] * rhs;
    T e10 = rhs_c[2] * rhs;
    T e11 = rhs_c[3] * rhs;
    
    return mat2_t( e00, e10,
                 e01, e11 );
}

template< typename D >
mat2_t<D>     operator*( D lhs, mat2_t<D> const& rhs )
{
    D const* rhs_c = rhs.data.c;
    
    D e00 = rhs_c[0] * lhs;
    D e01 = rhs_c[1] * lhs;
    D e10 = rhs_c[2] * lhs;
    D e11 = rhs_c[3] * lhs;
    
    return mat2_t<D>( e00, e10,
                    e01, e11 );
}

template< typename T >
mat2_t<T>     mat2_t<T>::operator/( T rhs )
{
    T const* rhs_c = this->data.c;
    
    T e00 = rhs_c[0] / rhs;
    T e01 = rhs_c[1] / rhs;
    T e10 = rhs_c[2] / rhs;
    T e11 = rhs_c[3] / rhs;
    
    return mat2_t( e00, e10,
                 e01, e11 );
}

// Mutative Operatores

template< typename T > inline
mat2_t<T>&    mat2_t<T>::operator=( mat2_t<T> const& rhs )
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
col2<T>     mat2_t<T>::operator[]( size_t i )
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat2_t out of range" );
    }
    
    return col2<T>( this->data.c + (2*i), true );
}

template< typename T > inline
col2<T>     mat2_t<T>::operator[]( size_t i ) const
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat2_t out of range" );
    }
    
    T* col_cpy = new T[2];
    
    col_cpy[0] = this-data->c[ 2 * i ];
    col_cpy[1] = this-data->c[ 2 * i + 1 ];
    
    return col2<T>( col_cpy, false );
}

template< typename T > inline
T&     mat2_t<T>::operator()( size_t col,
                            size_t row )
{
    if ( col > 1 or row > 1 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat2_t used out of bounds index");
    }
    
    return this->data.c[col * 2 + row];
}

template< typename T > inline
T      mat2_t<T>::operator()( size_t col,
                            size_t row ) const
{
    if ( col > 1 or row > 1 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat2_t used out of bounds index");
    }
    
    return this->data.c[col * 2 + row];
}

// Mutative Functions

template< typename T > inline
mat2_t<T>&    mat2_t<T>::column( size_t col,
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
          throw std::out_of_range("Component index on mat2_t out of range.");
    }
    return *this;
}

template< typename T > inline
vec2_t<T>     mat2_t<T>::column( size_t col ) const
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
          throw std::out_of_range("Component index on mat2_t out of range.");
    }
    return vec2_t<T>(out_x, out_y);
}

template< typename T > inline
mat2_t<T>&    mat2_t<T>::columns( vec2_t<T> const& col0,
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
mat2_t<T>& mat2_t<T>::fill( T val )
{
    T* c = this->data.c;
    c[0] = val;
    c[1] = val;
    c[2] = val;
    c[3] = val;
    return *this;
}

template< typename T > inline
mat2_t<T>&    mat2_t<T>::row( size_t row,
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
          throw std::out_of_range("Component index on mat2_t out of range.");
    }
          
    return *this;
}

template< typename T > inline
vec2_t<T>     mat2_t<T>::row( size_t row ) const
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
          throw std::out_of_range("Component index on mat2_t out of range.");
    }
    return vec2_t<T>(out_x, out_y);
}

template< typename T >
inline mat2_t<T>& mat2_t<T>::rows( vec2_t<T> const& row0,
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
mat2_t<T>& mat2_t<T>::transpose()
{
    T* c = this->data.c;
    T swap = c[2];
    c[2] = c[1];
    c[1] = swap;
    return *this;
}

// Utility

template< typename T > inline
raw_map const   mat2_t<T>::to_map() const
{
    return map_bytes( sizeof(T) * 4, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat2_t<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " ]" << std::endl;
    return stream;
}

// --------- MAT 3X3 -------------

// Construction
template< typename T > inline
mat3_t<T>::mat3_t()
{ T* c = this->data.c;
  c[0] = lit<T>::zero;   c[3] = lit<T>::zero; c[6] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[4] = lit<T>::zero; c[7] = lit<T>::zero;
  c[2] = lit<T>::zero;   c[5] = lit<T>::zero; c[8] = lit<T>::zero; }

template< typename T > inline
mat3_t<T>::mat3_t( mat3_t<T> const& copy )
{ T const* cpy = copy.data.c;
  T* c = this->data.c;
  c[0] = cpy[0];   c[3] = cpy[3]; c[6] = cpy[6];
  c[1] = cpy[1];   c[4] = cpy[4]; c[7] = cpy[7];
  c[2] = cpy[2];   c[5] = cpy[5]; c[8] = cpy[8]; }
  
template< typename T >
mat3_t<T>::mat3_t( T e00, T e10, T e20, 
               T e01, T e11, T e21,
               T e02, T e12, T e22 )
{ T* c = this->data.c;
  c[0] = e00;   c[3] = e10;   c[6] = e20;
  c[1] = e01;   c[4] = e11;   c[7] = e21;
  c[2] = e02;   c[5] = e12;   c[8] = e22; }

// Named Construction
  
template< typename T > inline
mat3_t<T>     mat3_t<T>::column_vectors( vec3_t<T> const& col0,
                                     vec3_t<T> const& col1,
                                     vec3_t<T> const& col2 )
{ return mat3_t( col0(x), col1(x), col2(x),
               col0(y), col1(y), col2(y),
               col0(z), col1(z), col2(z) ); }
               
template< typename T > inline
mat3_t<T>     mat3_t<T>::cross_product( vec3_t<T> const& vec )
{ return mat3_t<T>( lit<T>::zero, vec(-z),      vec(y),
                  vec(z),       lit<T>::zero, vec(-x),
                  vec(-y),      vec(x),       lit<T>::zero ); }
                  
template< typename T > inline
mat3_t<T>     mat3_t<T>::homogenize( mat2_t<T> const& amat )
{ return mat3_t( amat(0,0),    amat(1,0),    lit<T>::zero,
               amat(0,1),    amat(1,1),    lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::one  ); }

template< typename T >
mat3_t<T>     mat3_t<T>::identity()
{ return mat3_t( lit<T>::one,  lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::one,  lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::one ); }
  
template< typename T > inline
mat3_t<T>     mat3_t<T>::row_vectors( vec3_t<T> const& row0,
                                  vec3_t<T> const& row1,
                                  vec3_t<T> const& row2 )
{ return mat3_t( row0(x), row0(y), row0(z),
               row1(x), row1(y), row1(z),
               row2(x), row2(y), row2(z) ); }
               
template< typename T > inline
mat3_t<T>     mat3_t<T>::rotation( vec3_t<T> const& axis,
                               d_angle const& ang )
{
    double radians = ang.to_rads();
    double cos_t ( cos( radians ) );
    double cm_cos_t ( 1.0 - cos_t );
    return   mat3_t<T>::identity() * cos_t
           + mat3_t<T>::square( axis ) * cm_cos_t
           + mat3_t<T>::cross_product( axis ) * sin( radians );
}

template< typename T > inline
mat3_t<T>     mat3_t<T>::rotation( d_angle const& angx,
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
    
    return mat3_t<T>(
        cos_y*cos_z,                     -cos_y*sin_z,                      sin_y,
        cos_x*sin_z + sin_x*sin_y*cos_z,  cos_x*cos_z - sin_x*sin_y*sin_z, -sin_x*cos_y,
        sin_x*sin_z - cos_x*sin_y*cos_z,  sin_x*cos_z + cos_x*sin_y*sin_z,  cos_x*cos_y
      );
    
}

template< typename T > inline
mat3_t<T>     mat3_t<T>::rotation( qutn_t<T> const& qrot )
{
    double ii = qrot(i) * qrot(i) * lit<T>::two;
    double ij = qrot(i) * qrot(j) * lit<T>::two;
    double ik = qrot(i) * qrot(k) * lit<T>::two;
    double im = qrot(i) * qrot(m) * lit<T>::two;

    double jj = qrot(j) * qrot(j) * lit<T>::two;
    double jk = qrot(j) * qrot(k) * lit<T>::two;
    double jm = qrot(j) * qrot(m) * lit<T>::two;

    double kk = qrot(k) * qrot(k) * lit<T>::two;
    double km = qrot(k) * qrot(m) * lit<T>::two;
    
    return mat3_t<T>( lit<T>::one - (jj + kk), ij - km,                   ik + jm,
                    ij + km,                   lit<T>::one - (ii + kk), jk - im,
                    ik - jm,                   jk + im,                   lit<T>::one - (ii + jj) );
}

template< typename T > inline
mat3_t<T>     mat3_t<T>::scale( T sx, T sy, T sz = 1.0f )
{ return mat3_t( sx,           lit<T>::zero, lit<T>::zero,
               lit<T>::zero, sy,           lit<T>::zero,
               lit<T>::zero, lit<T>::zero, sz            ); }
               
template< typename T > inline
mat3_t<T>     mat3_t<T>::scale( vec3_t<T> const& svec )
{ return mat3_t( svec(x),      lit<T>::zero, lit<T>::zero,
               lit<T>::zero, svec(y),      lit<T>::zero,
               lit<T>::zero, lit<T>::zero, svec(z)       ); }
               
template< typename T > inline
mat3_t<T>     mat3_t<T>::scale( vec2_t<T> const& svec )
{ return mat3_t( svec(x),      lit<T>::zero, lit<T>::zero,
               lit<T>::zero, svec(y),      lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::one  ); }
               
template< typename T > inline
mat3_t<T>     mat3_t<T>::square( vec3_t<T> const& vec )
{ return mat3_t( vec[0] * vec[0], vec[0] * vec[1], vec[0] * vec[2],
               vec[1] * vec[0], vec[1] * vec[1], vec[1] * vec[2],
               vec[2] * vec[0], vec[2] * vec[1], vec[2] * vec[2]  ); }
               
template< typename T > inline
mat3_t<T>     mat3_t<T>::translate( T tx, T ty )
{ return mat3_t( lit<T>::one,  lit<T>::zero, tx,
               lit<T>::zero, lit<T>::one,  ty,
               lit<T>::zero, lit<T>::zero, lit<T>::one ); }
               
template< typename T > inline
mat3_t<T>     mat3_t<T>::translate( vec2_t<T> const& tvec )
{ return mat3_t( lit<T>::one,  lit<T>::zero, tvec(x),
               lit<T>::zero, lit<T>::one,  tvec(y),
               lit<T>::zero, lit<T>::zero, lit<T>::one ); }
               
// Comparison

template< typename T > inline
bool    mat3_t<T>::operator==( mat3_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs(lhs_c[0] - rhs_c[0]) < lit<T>::delta
           and std::abs(lhs_c[1] - rhs_c[1]) < lit<T>::delta
           and std::abs(lhs_c[2] - rhs_c[2]) < lit<T>::delta
           and std::abs(lhs_c[3] - rhs_c[3]) < lit<T>::delta
           and std::abs(lhs_c[4] - rhs_c[4]) < lit<T>::delta
           and std::abs(lhs_c[5] - rhs_c[5]) < lit<T>::delta
           and std::abs(lhs_c[6] - rhs_c[6]) < lit<T>::delta
           and std::abs(lhs_c[7] - rhs_c[7]) < lit<T>::delta
           and std::abs(lhs_c[8] - rhs_c[8]) < lit<T>::delta;
}

template< typename T > inline
bool    mat3_t<T>::operator<( mat3_t<T> const& rhs ) const
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
bool    mat3_t<T>::operator>( mat3_t<T> const& rhs ) const
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
bool    mat3_t<T>::operator<=( mat3_t<T> const& rhs ) const
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
bool    mat3_t<T>::operator>=( mat3_t<T> const& rhs ) const
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
bool    mat3_t<T>::operator!=( mat3_t<T> const& rhs ) const
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
mat3_t<T>     mat3_t<T>::operator+( mat3_t<T> const& rhs )
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
    
    return mat3_t( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

template< typename T > inline
mat3_t<T>     mat3_t<T>::operator-()
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
    
    return mat3_t( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

template< typename T > inline
mat3_t<T>     mat3_t<T>::operator-( mat3_t<T> const& rhs )
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
    
    return mat3_t( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}
               
template< typename T > inline
mat3_t<T>     mat3_t<T>::operator*( mat3_t<T> const& rhs ) const
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
    
    return mat3_t( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

template< typename T > inline
mat2x3_t<T>     mat3_t<T>::operator*( mat2x3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[6] * rhs_c[2];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[7] * rhs_c[2];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[8] * rhs_c[2];
    
    T e10 = lhs_c[0] * rhs_c[3] + lhs_c[3] * rhs_c[4] + lhs_c[6] * rhs_c[5];
    T e11 = lhs_c[1] * rhs_c[3] + lhs_c[4] * rhs_c[4] + lhs_c[7] * rhs_c[5];
    T e12 = lhs_c[2] * rhs_c[3] + lhs_c[5] * rhs_c[4] + lhs_c[8] * rhs_c[5];
    
    return mat2x3_t<T>( e00, e10,
                        e01, e11,
                        e02, e12 );
}

template< typename T > inline
mat4x3_t<T>     mat3_t<T>::operator*( mat4x3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[6] * rhs_c[2];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[7] * rhs_c[2];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[8] * rhs_c[2];
    
    T e10 = lhs_c[0] * rhs_c[3] + lhs_c[3] * rhs_c[4] + lhs_c[6] * rhs_c[5];
    T e11 = lhs_c[1] * rhs_c[3] + lhs_c[4] * rhs_c[4] + lhs_c[7] * rhs_c[5];
    T e12 = lhs_c[2] * rhs_c[3] + lhs_c[5] * rhs_c[4] + lhs_c[8] * rhs_c[5];
    
    T e20 = lhs_c[0] * rhs_c[6] + lhs_c[3] * rhs_c[7] + lhs_c[6] * rhs_c[8];
    T e21 = lhs_c[1] * rhs_c[6] + lhs_c[4] * rhs_c[7] + lhs_c[7] * rhs_c[8];
    T e22 = lhs_c[2] * rhs_c[6] + lhs_c[5] * rhs_c[7] + lhs_c[8] * rhs_c[8];
    
    T e30 = lhs_c[0] * rhs_c[9] + lhs_c[3] * rhs_c[10] + lhs_c[6] * rhs_c[11];
    T e31 = lhs_c[1] * rhs_c[9] + lhs_c[4] * rhs_c[10] + lhs_c[7] * rhs_c[11];
    T e32 = lhs_c[2] * rhs_c[9] + lhs_c[5] * rhs_c[10] + lhs_c[8] * rhs_c[11];
    
    return mat4x3_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31,
                        e02, e12, e22, e32 );
}

template< typename T >
mat3_t<T>     mat3_t<T>::operator*( T rhs )
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
    
    return mat3_t( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

template< typename D >
mat3_t<D>     operator*( D lhs, mat3_t<D> const& rhs )
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
    
    return mat3_t<D>( e00, e10, e20,
                    e01, e11, e21,
                    e02, e12, e22 );
}

template< typename T > inline
vec3_t<T>     mat3_t<T>::operator*( vec3_t<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T x0 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[6] * rhs_c[2];
    T x1 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[7] * rhs_c[2];
    T x2 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[8] * rhs_c[2];
    
    return vec3_t<T>( x0, x1, x2 );
}

template< typename T > inline
vec3_t<T>     operator*( vec3_t<T> const& lhs, mat3_t<T> const& rhs )
{
    T const* lhs_c = lhs.data.c;
    T const* rhs_c = rhs.data.c;
    
    T x0 = lhs_c[0] * rhs_c[0] + lhs_c[1] * rhs_c[1] + lhs_c[2] * rhs_c[2];
    T x1 = lhs_c[0] * rhs_c[3] + lhs_c[1] * rhs_c[4] + lhs_c[2] * rhs_c[5];
    T x2 = lhs_c[0] * rhs_c[6] + lhs_c[1] * rhs_c[7] + lhs_c[2] * rhs_c[8];
    
    return vec3_t<T>( x0, x1, x2 );
}

template< typename T >
mat3_t<T>     mat3_t<T>::operator/( T rhs )
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
    
    return mat3_t( e00, e10, e20,
                 e01, e11, e21,
                 e02, e12, e22 );
}

// Mutative Operators

template< typename T > inline
mat3_t<T>&    mat3_t<T>::operator=( mat3_t<T> const& rhs )
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
col3<T>     mat3_t<T>::operator[]( size_t i )
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat3_t out of range" );
    }
    
    return col3<T>( this->data.c + (3*i), true );
}

template< typename T > inline
col3<T>     mat3_t<T>::operator[]( size_t i ) const
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat3_t out of range" );
    }
    
    T* col_cpy = new T[3];
    
    col_cpy[0] = this-data->c[ 3 * i ];
    col_cpy[1] = this-data->c[ 3 * i + 1 ];
    col_cpy[2] = this-data->c[ 3 * i + 2 ];
    
    return col3<T>( col_cpy, false );
}
               
template< typename T > inline
T&     mat3_t<T>::operator()( size_t col,
                            size_t row )
{
    if ( col > 2 or row > 2 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat3_t used out of bounds index");
    }
    
    return this->data.c[col * 3 + row];
}

template< typename T > inline
T      mat3_t<T>::operator()( size_t col,
                            size_t row ) const
{
    if ( col > 2 or row > 2 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat3_t used out of bounds index");
    }
    
    return this->data.c[col * 3 + row];
}

// Mutative Functions

template< typename T > inline
mat3_t<T>&    mat3_t<T>::column( size_t col,
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
          throw std::out_of_range("Component index on mat3_t out of range.");
    }
    return *this;
}

template< typename T > inline
vec3_t<T>     mat3_t<T>::column( size_t col ) const
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
          throw std::out_of_range("Component index on mat3_t out of range.");
    }
    return vec3_t<T>(out_x, out_y, out_z);
}

template< typename T > inline
mat3_t<T>&    mat3_t<T>::columns( vec3_t<T> const& col0,
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
mat3_t<T>& mat3_t<T>::fill( T val )
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
mat3_t<T>& mat3_t<T>::norm()
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
mat3_t<T>&    mat3_t<T>::row( size_t row,
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
          throw std::out_of_range("Component index on mat3_t out of range.");
    }
          
    return *this;
}

template< typename T > inline
vec3_t<T>     mat3_t<T>::row( size_t row ) const
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
          throw std::out_of_range("Component index on mat3_t out of range.");
    }
    return vec3_t<T>(out_x, out_y, out_z);
}



template< typename T >
inline mat3_t<T>& mat3_t<T>::rows( vec3_t<T> const& row0,
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
mat3_t<T>& mat3_t<T>::transpose()
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

template< typename T >
mat3_t<T>& mat3_t<T>::invert()
{
    T* cm = data.c;
    T det =   cm[0] * (cm[4]*cm[8] - cm[7]*cm[5])
            - cm[3] * (cm[8]*cm[1] - cm[7]*cm[2])
            + cm[6] * (cm[1]*cm[5] - cm[4]*cm[2]);
    det = 1.0f / det;
    this->transpose();
    
    cm[0] = cm[0] * det;
    cm[1] = cm[1] * det;
    cm[2] = cm[2] * det;
    
    cm[3] = cm[3] * det;
    cm[4] = cm[4] * det;
    cm[5] = cm[5] * det;
    
    cm[6] = cm[6] * det;
    cm[7] = cm[7] * det;
    cm[8] = cm[8] * det;
    
    return *this;
}

// Utilities

template< typename T > inline
raw_map const   mat3_t<T>::to_map() const
{
    return map_bytes( sizeof(T) * 9, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat3_t<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " " << src(2,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " " << src(2,1) << " ]" << '\n';
    stream << "[ " << src(0,2) << " " << src(1,2) << " " << src(2,2) << " ]" << std::endl;
    return stream;
}

// --------- MAT 4X4 -------------

template< typename T > inline
mat4_t<T>::mat4_t()
{ T* c = this->data.c;
  c[0] = lit<T>::zero;   c[4] = lit<T>::zero;   c[8] = lit<T>::zero;   c[12] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[5] = lit<T>::zero;   c[9] = lit<T>::zero;   c[13] = lit<T>::zero;
  c[2] = lit<T>::zero;   c[6] = lit<T>::zero;   c[10] = lit<T>::zero;  c[14] = lit<T>::zero;
  c[3] = lit<T>::zero;   c[7] = lit<T>::zero;   c[11] = lit<T>::zero;  c[15] = lit<T>::zero; }

template< typename T > inline
mat4_t<T>::mat4_t( mat4_t<T> const& copy )
{ T const* cpy = copy.data.c;
  T* c = this->data.c;
  c[0] = cpy[0];   c[4] = cpy[4];   c[8] = cpy[8];    c[12] = cpy[12];
  c[1] = cpy[1];   c[5] = cpy[5];   c[9] = cpy[9];    c[13] = cpy[13];
  c[2] = cpy[2];   c[6] = cpy[6];   c[10] = cpy[10];  c[14] = cpy[14];
  c[3] = cpy[3];   c[7] = cpy[7];   c[11] = cpy[11];  c[15] = cpy[15]; }
  
template< typename T >
mat4_t<T>::mat4_t( T e00, T e10, T e20, T e30,
               T e01, T e11, T e21, T e31,
               T e02, T e12, T e22, T e32,
               T e03, T e13, T e23, T e33 )
{ T* c = this->data.c;
  c[0] = e00;   c[4] = e10;   c[8] = e20;   c[12] = e30;
  c[1] = e01;   c[5] = e11;   c[9] = e21;   c[13] = e31;
  c[2] = e02;   c[6] = e12;   c[10] = e22;  c[14] = e32;
  c[3] = e03;   c[7] = e13;   c[11] = e23;  c[15] = e33; }

template< typename T >
mat4_t<T>     mat4_t<T>::identity()
{ return mat4_t( lit<T>::one,  lit<T>::zero, lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::one,  lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::one,  lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::zero, lit<T>::one  ); }
  
template< typename T > inline
mat4_t<T>     mat4_t<T>::row_vectors( vec4_t<T> const& row0,
                                  vec4_t<T> const& row1,
                                  vec4_t<T> const& row2,
                                  vec4_t<T> const& row3 )
{ return mat4_t( row0(x), row0(y), row0(z), row0(w),
               row1(x), row1(y), row1(z), row1(w),
               row2(x), row2(y), row2(z), row2(w),
               row3(x), row3(y), row3(z), row3(w) ); }
               
template< typename T > inline
mat4_t<T>     mat4_t<T>::column_vectors( vec4_t<T> const& col0,
                                     vec4_t<T> const& col1,
                                     vec4_t<T> const& col2,
                                     vec4_t<T> const& col3 )
{ return mat4_t( col0(x), col1(x), col2(x), col3(x),
               col0(y), col1(y), col2(y), col3(y),
               col0(z), col1(z), col2(z), col3(z),
               col0(w), col1(w), col2(w), col3(w) ); }
               
template< typename T > inline
mat4_t<T>     mat4_t<T>::square( vec4_t<T> const& vec )
{ return mat4_t( vec[0] * vec[0], vec[0] * vec[1], vec[0] * vec[2], vec[0] * vec[3],
               vec[1] * vec[0], vec[1] * vec[1], vec[1] * vec[2], vec[1] * vec[3],
               vec[2] * vec[0], vec[2] * vec[1], vec[2] * vec[2], vec[2] * vec[3],
               vec[3] * vec[0], vec[3] * vec[1], vec[3] * vec[2], vec[3] * vec[3]  ); }
               
template< typename T > inline
mat4_t<T>     mat4_t<T>::homogenize( mat3_t<T> const& amat )
{ return mat4_t( amat(0,0),    amat(1,0),    amat(2,0),    lit<T>::zero,
               amat(0,1),    amat(1,1),    amat(2,1),    lit<T>::zero,
               amat(0,2),    amat(1,2),    amat(2,2),    lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::zero, lit<T>::one  ); }

template< typename T > inline
mat4_t<T>     mat4_t<T>::scale( T sx, T sy, T sz )
{ return mat4_t( sx,           lit<T>::zero, lit<T>::zero, lit<T>::zero,
               lit<T>::zero, sy,           lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::zero, sz,           lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::zero, lit<T>::one  ); }
               
template< typename T > inline
mat4_t<T>     mat4_t<T>::scale( vec3_t<T> const& svec )
{ return mat4_t( svec(x),      lit<T>::zero, lit<T>::zero, lit<T>::zero,
               lit<T>::zero, svec(y),      lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::zero, svec(z),      lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::zero, lit<T>::one  ); }
               
template< typename T > inline
mat4_t<T>     mat4_t<T>::translate( T tx, T ty, T tz )
{ return mat4_t( lit<T>::one,  lit<T>::zero, lit<T>::zero, tx,
               lit<T>::zero, lit<T>::one,  lit<T>::zero, ty,
               lit<T>::zero, lit<T>::zero, lit<T>::one,  tz,
               lit<T>::zero, lit<T>::zero, lit<T>::zero, lit<T>::one  ); }
               
template< typename T > inline
mat4_t<T>     mat4_t<T>::translate( vec3_t<T> const& tvec )
{ return mat4_t( lit<T>::one,  lit<T>::zero, lit<T>::zero, tvec(x),
               lit<T>::zero, lit<T>::one,  lit<T>::zero, tvec(y),
               lit<T>::zero, lit<T>::zero, lit<T>::one,  tvec(z),
               lit<T>::zero, lit<T>::zero, lit<T>::zero, lit<T>::one  ); }
               
template< typename T > inline
mat4_t<T>     mat4_t<T>::cross_product( vec3_t<T> const& vec )
{ return mat4_t( lit<T>::zero, vec(-z),      vec(y),       lit<T>::zero,
               vec(z),       lit<T>::zero, vec(-x),      lit<T>::zero,
               vec(-y),      vec(x),       lit<T>::zero, lit<T>::zero,
               lit<T>::zero, lit<T>::zero, lit<T>::zero, lit<T>::one   ); }
               
template< typename T > inline
mat4_t<T>     mat4_t<T>::perspective( d_angle const& fovY,
                                      double aspect,
                                      double near,
                                      double far     )
{
    double invTopTan = 1.0 / tan( fovY.to_rads() * 0.5);
    double invRightTan = invTopTan / aspect;
    double invFLessN = 1.0 / ( far - near );
    
    return mat4_t( (T) invRightTan, lit<T>::zero,  lit<T>::zero,                  lit<T>::zero,
                   lit<T>::zero,    (T) invTopTan, lit<T>::zero,                  lit<T>::zero,
                   lit<T>::zero,    lit<T>::zero,  (T) -(far + near) * invFLessN, (T) -(2.0*far*near) * invFLessN,
                   lit<T>::zero,    lit<T>::zero,  lit<T>::neg_one,               lit<T>::zero                    );
}

template< typename T > inline
mat4_t<T>     mat4_t<T>::rotation( vec3_t<T> const& axis,
                               d_angle const& ang     )
{
    double radians ( ang.to_rads() );
    double cos_t ( cos(radians) );
    double cm_cos_t = 1.0 - cos_t;
    double sin_t ( sin(radians) );
    mat4_t<T> trig_mat( cos_t,          axis(-z)*sin_t, axis(y)*sin_t,  lit<T>::zero,
                      axis(z)*sin_t,  cos_t,          axis(-x)*sin_t, lit<T>::zero,
                      axis(-y)*sin_t, axis(x)*sin_t,  cos_t,          lit<T>::zero,
                      lit<T>::zero,   lit<T>::zero,   lit<T>::zero,   lit<T>::zero  );
    
    mat4_t<T> axis_mat( axis(x) * axis(x) * cm_cos_t, axis(x) * axis(y) * cm_cos_t, axis(x) * axis(z) * cm_cos_t, lit<T>::zero,
                      axis(y) * axis(x) * cm_cos_t, axis(y) * axis(y) * cm_cos_t, axis(y) * axis(z) * cm_cos_t, lit<T>::zero,
                      axis(z) * axis(x) * cm_cos_t, axis(z) * axis(y) * cm_cos_t, axis(z) * axis(z) * cm_cos_t, lit<T>::zero,
                      lit<T>::zero,      lit<T>::zero,      lit<T>::zero,      lit<T>::one  );
    return trig_mat + axis_mat;
}

template< typename T > inline
mat4_t<T>     mat4_t<T>::rotation( d_angle const& angx,
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
    
    return mat4_t<T>(
        cos_y*cos_z,                     -cos_y*sin_z,                      sin_y,         lit<T>::zero,
        cos_x*sin_z + sin_x*sin_y*cos_z,  cos_x*cos_z - sin_x*sin_y*sin_z, -sin_x*cos_y,   lit<T>::zero,
        sin_x*sin_z - cos_x*sin_y*cos_z,  sin_x*cos_z + cos_x*sin_y*sin_z,  cos_x*cos_y,   lit<T>::zero,
        lit<T>::zero,                    lit<T>::zero,                    lit<T>::zero, lit<T>::one
      );
    
}

template< typename T > inline
mat4_t<T>     mat4_t<T>::rotation( qutn_t<T> const& qrot )
{
    double ii = qrot(i) * qrot(i) * lit<T>::two;
    double ij = qrot(i) * qrot(j) * lit<T>::two;
    double ik = qrot(i) * qrot(k) * lit<T>::two;
    double im = qrot(i) * qrot(m) * lit<T>::two;

    double jj = qrot(j) * qrot(j) * lit<T>::two;
    double jk = qrot(j) * qrot(k) * lit<T>::two;
    double jm = qrot(j) * qrot(m) * lit<T>::two;

    double kk = qrot(k) * qrot(k) * lit<T>::two;
    double km = qrot(k) * qrot(m) * lit<T>::two;
    
    return mat4_t<T>( lit<T>::one
                   -(jj + kk),     ij - km,       ik + jm,       lit<T>::zero,
                    ij + km,       lit<T>::one
                                  -(ii + kk),     jk - im,       lit<T>::zero,
                    ik - jm,       jk + im,       lit<T>::one
                                                 -(ii + jj),     lit<T>::zero,
                    lit<T>::zero, lit<T>::zero, lit<T>::zero, lit<T>::one  );
}

template< typename T > inline
bool    mat4_t<T>::operator==( mat4_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    
    return     std::abs(lhs_c[0] - rhs_c[0]) < lit<T>::delta
           and std::abs(lhs_c[1] - rhs_c[1]) < lit<T>::delta
           and std::abs(lhs_c[2] - rhs_c[2]) < lit<T>::delta
           and std::abs(lhs_c[3] - rhs_c[3]) < lit<T>::delta
           and std::abs(lhs_c[4] - rhs_c[4]) < lit<T>::delta
           and std::abs(lhs_c[5] - rhs_c[5]) < lit<T>::delta
           and std::abs(lhs_c[6] - rhs_c[6]) < lit<T>::delta
           and std::abs(lhs_c[7] - rhs_c[7]) < lit<T>::delta
           and std::abs(lhs_c[8] - rhs_c[8]) < lit<T>::delta
           and std::abs(lhs_c[9] - rhs_c[9]) < lit<T>::delta
           and std::abs(lhs_c[10] - rhs_c[10]) < lit<T>::delta
           and std::abs(lhs_c[11] - rhs_c[11]) < lit<T>::delta
           and std::abs(lhs_c[12] - rhs_c[12]) < lit<T>::delta
           and std::abs(lhs_c[13] - rhs_c[13]) < lit<T>::delta
           and std::abs(lhs_c[14] - rhs_c[14]) < lit<T>::delta
           and std::abs(lhs_c[15] - rhs_c[15]) < lit<T>::delta;
}

template< typename T > inline
bool    mat4_t<T>::operator<( mat4_t<T> const& rhs ) const
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
bool    mat4_t<T>::operator>( mat4_t<T> const& rhs ) const
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
bool    mat4_t<T>::operator<=( mat4_t<T> const& rhs ) const
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
bool    mat4_t<T>::operator>=( mat4_t<T> const& rhs ) const
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
bool    mat4_t<T>::operator!=( mat4_t<T> const& rhs ) const
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
mat4_t<T>&    mat4_t<T>::operator=( mat4_t<T> const& rhs )
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
col4<T>     mat4_t<T>::operator[]( size_t i )
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat4_t out of range" );
    }
    
    return col4<T>( this->data.c + (4*i), true );
}

template< typename T > inline
col4<T>     mat4_t<T>::operator[]( size_t i ) const
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat4_t out of range" );
    }
    
    T* col_cpy = new T[4];
    
    col_cpy[0] = this->data.c[ 4 * i ];
    col_cpy[1] = this->data.c[ 4 * i + 1 ];
    col_cpy[2] = this->data.c[ 4 * i + 2 ];
    col_cpy[3] = this->data.c[ 4 * i + 3 ];
    
    return col4<T>( col_cpy, false );
}
               
template< typename T > inline
T&     mat4_t<T>::operator()( size_t col,
                            size_t row )
{
    if ( col > 3 or row > 3 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat4_t used out of bounds index");
    }
    
    return this->data.c[col * 4 + row];
}

template< typename T > inline
T      mat4_t<T>::operator()( size_t col,
                            size_t row ) const
{
    if ( col > 3 or row > 3 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat4_t used out of bounds index");
    }
    
    return this->data.c[col * 4 + row];
}

template< typename T > inline
mat4_t<T>     mat4_t<T>::operator+( mat4_t<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    return mat4_t( lhs_c[0] + rhs_c[0], lhs_c[4] + rhs_c[4], lhs_c[8] + rhs_c[8],   lhs_c[12] + rhs_c[12],
                 lhs_c[1] + rhs_c[1], lhs_c[5] + rhs_c[5], lhs_c[9] + rhs_c[9],   lhs_c[13] + rhs_c[13],
                 lhs_c[2] + rhs_c[2], lhs_c[6] + rhs_c[6], lhs_c[10] + rhs_c[10], lhs_c[14] + rhs_c[14],
                 lhs_c[3] + rhs_c[3], lhs_c[7] + rhs_c[7], lhs_c[11] + rhs_c[11], lhs_c[15] + rhs_c[15] );
}

template< typename T > inline
mat4_t<T>     mat4_t<T>::operator-()
{
    T const* lhs_c = this->data.c;
    
    return mat4_t( -lhs_c[0], -lhs_c[4], -lhs_c[8],  -lhs_c[12],
                 -lhs_c[1], -lhs_c[5], -lhs_c[9],  -lhs_c[13],
                 -lhs_c[2], -lhs_c[6], -lhs_c[10], -lhs_c[14],
                 -lhs_c[3], -lhs_c[7], -lhs_c[11], -lhs_c[15] );
}

template< typename T > inline
mat4_t<T>     mat4_t<T>::operator-( mat4_t<T> const& rhs )
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    return mat4_t( lhs_c[0] - rhs_c[0], lhs_c[4] - rhs_c[4], lhs_c[8] - rhs_c[8], lhs_c[12] - rhs_c[12],
                 lhs_c[1] - rhs_c[1], lhs_c[5] - rhs_c[5], lhs_c[9] - rhs_c[9], lhs_c[13] - rhs_c[13],
                 lhs_c[2] - rhs_c[2], lhs_c[6] - rhs_c[6], lhs_c[10] - rhs_c[10], lhs_c[14] - rhs_c[14],
                 lhs_c[3] - rhs_c[3], lhs_c[7] - rhs_c[7], lhs_c[11] - rhs_c[11], lhs_c[15] - rhs_c[15] );
}
               
template< typename T > inline
mat4_t<T>     mat4_t<T>::operator*( mat4_t<T> const& rhs ) const
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
    
    return mat4_t( e00, e10, e20, e30,
                 e01, e11, e21, e31,
                 e02, e12, e22, e32,
                 e03, e13, e23, e33 );
}

template< typename T > inline
mat2x4_t<T>     mat4_t<T>::operator*( mat2x4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[8] * rhs_c[2] + lhs_c[12] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[9] * rhs_c[2] + lhs_c[13] * rhs_c[3];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[6] * rhs_c[1] + lhs_c[10] * rhs_c[2] + lhs_c[14] * rhs_c[3];
    T e03 = lhs_c[3] * rhs_c[0] + lhs_c[7] * rhs_c[1] + lhs_c[11] * rhs_c[2] + lhs_c[15] * rhs_c[3];
    
    T e10 = lhs_c[0] * rhs_c[4] + lhs_c[4] * rhs_c[5] + lhs_c[8] * rhs_c[6] + lhs_c[12] * rhs_c[7];
    T e11 = lhs_c[1] * rhs_c[4] + lhs_c[5] * rhs_c[5] + lhs_c[9] * rhs_c[6] + lhs_c[13] * rhs_c[7];
    T e12 = lhs_c[2] * rhs_c[4] + lhs_c[6] * rhs_c[5] + lhs_c[10] * rhs_c[6] + lhs_c[14] * rhs_c[7];
    T e13 = lhs_c[3] * rhs_c[4] + lhs_c[7] * rhs_c[5] + lhs_c[11] * rhs_c[6] + lhs_c[15] * rhs_c[7];
    
    return mat2x4_t<T>( e00, e10,
                        e01, e11,
                        e02, e12,
                        e03, e13 );
}

template< typename T > inline
mat3x4_t<T>     mat4_t<T>::operator*( mat3x4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[8] * rhs_c[2] + lhs_c[12] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[9] * rhs_c[2] + lhs_c[13] * rhs_c[3];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[6] * rhs_c[1] + lhs_c[10] * rhs_c[2] + lhs_c[14] * rhs_c[3];
    T e03 = lhs_c[3] * rhs_c[0] + lhs_c[7] * rhs_c[1] + lhs_c[11] * rhs_c[2] + lhs_c[15] * rhs_c[3];
    
    T e10 = lhs_c[0] * rhs_c[4] + lhs_c[4] * rhs_c[5] + lhs_c[8] * rhs_c[6] + lhs_c[12] * rhs_c[7];
    T e11 = lhs_c[1] * rhs_c[4] + lhs_c[5] * rhs_c[5] + lhs_c[9] * rhs_c[6] + lhs_c[13] * rhs_c[7];
    T e12 = lhs_c[2] * rhs_c[4] + lhs_c[6] * rhs_c[5] + lhs_c[10] * rhs_c[6] + lhs_c[14] * rhs_c[7];
    T e13 = lhs_c[3] * rhs_c[4] + lhs_c[7] * rhs_c[5] + lhs_c[11] * rhs_c[6] + lhs_c[15] * rhs_c[7];
    
    T e20 = lhs_c[0] * rhs_c[8] + lhs_c[4] * rhs_c[9] + lhs_c[8] * rhs_c[10] + lhs_c[12] * rhs_c[11];
    T e21 = lhs_c[1] * rhs_c[8] + lhs_c[5] * rhs_c[9] + lhs_c[9] * rhs_c[10] + lhs_c[13] * rhs_c[11];
    T e22 = lhs_c[2] * rhs_c[8] + lhs_c[6] * rhs_c[9] + lhs_c[10] * rhs_c[10] + lhs_c[14] * rhs_c[11];
    T e23 = lhs_c[3] * rhs_c[8] + lhs_c[7] * rhs_c[9] + lhs_c[11] * rhs_c[10] + lhs_c[15] * rhs_c[11];
    
    return mat3x4_t<T>( e00, e10, e20,
                        e01, e11, e21,
                        e02, e12, e22,
                        e03, e13, e23 );
}

template< typename T > inline
vec4_t<T>     mat4_t<T>::operator*( vec4_t<T> const& rhs )
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
vec4_t<T>     operator*( vec4_t<T> const& lhs, mat4_t<T> const& rhs )
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
mat4_t<T>     mat4_t<T>::operator*( T rhs )
{
    T const* rhs_c = this->data.c;
    
    return mat4_t( rhs_c[0] * rhs, rhs_c[4] * rhs, rhs_c[8] * rhs,  rhs_c[12] * rhs,
                 rhs_c[1] * rhs, rhs_c[5] * rhs, rhs_c[9] * rhs,  rhs_c[13] * rhs,
                 rhs_c[2] * rhs, rhs_c[6] * rhs, rhs_c[10] * rhs, rhs_c[14] * rhs,
                 rhs_c[3] * rhs, rhs_c[7] * rhs, rhs_c[11] * rhs, rhs_c[15] * rhs  );
}

template< typename D >
mat4_t<D>     operator*( D lhs, mat4_t<D> const& rhs )
{
    D const* rhs_c = rhs.data.c;
    
    return mat4_t<D>( rhs_c[0] * lhs, rhs_c[4] * lhs, rhs_c[8] * lhs,  rhs_c[12] * lhs,
                    rhs_c[1] * lhs, rhs_c[5] * lhs, rhs_c[9] * lhs,  rhs_c[13] * lhs,
                    rhs_c[2] * lhs, rhs_c[6] * lhs, rhs_c[10] * lhs, rhs_c[14] * lhs,
                    rhs_c[3] * lhs, rhs_c[7] * lhs, rhs_c[11] * lhs, rhs_c[15] * lhs );
}

template< typename T >
mat4_t<T>     mat4_t<T>::operator/( T rhs )
{
    T const* lhs_c = this->data.c;
    
    return mat4_t( lhs_c[0] / rhs, lhs_c[4] / rhs, lhs_c[8] / rhs,  lhs_c[12] / rhs,
                 lhs_c[1] / rhs, lhs_c[5] / rhs, lhs_c[9] / rhs,  lhs_c[13] / rhs,
                 lhs_c[2] / rhs, lhs_c[6] / rhs, lhs_c[10] / rhs, lhs_c[14] / rhs,
                 lhs_c[3] / rhs, lhs_c[7] / rhs, lhs_c[11] / rhs, lhs_c[15] / rhs );
}

template< typename T >
mat4_t<T>& mat4_t<T>::fill( T val )
{
    T* c = this->data.c;
    c[0] = val;     c[4] = val;     c[8] = val;     c[12] = val;
    c[1] = val;     c[5] = val;     c[9] = val;     c[13] = val;
    c[2] = val;     c[6] = val;     c[10] = val;    c[14] = val;
    c[3] = val;     c[7] = val;     c[11] = val;    c[15] = val;
 
    return *this;
}

template< typename T > inline
mat4_t<T>&    mat4_t<T>::row( size_t row,
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
          throw std::out_of_range("Component index on mat4_t out of range.");
    }
          
    return *this;
}

template< typename T > inline
vec4_t<T>     mat4_t<T>::row( size_t row ) const
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
          throw std::out_of_range("Component index on mat4_t out of range.");
    }
}

template< typename T > inline
mat4_t<T>&    mat4_t<T>::column( size_t col,
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
          throw std::out_of_range("Component index on mat4_t out of range.");
    }
    return *this;
}

template< typename T > inline
vec4_t<T>     mat4_t<T>::column( size_t col ) const
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
          throw std::out_of_range("Component index on mat4_t out of range.");
    }
}

template< typename T >
inline mat4_t<T>& mat4_t<T>::rows( vec4_t<T> const& row0,
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
mat4_t<T>&    mat4_t<T>::columns( vec4_t<T> const& col0,
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


template< typename T >
mat4_t<T>&  mat4_t<T>::components( T e00, T e10, T e20, T e30,
                                   T e01, T e11, T e21, T e31,
                                   T e02, T e12, T e22, T e32,
                                   T e03, T e13, T e23, T e33 )
{
    T* c = this->data.c;
    c[0] = e00;   c[4] = e10;   c[8] = e20;   c[12] = e30;
    c[1] = e01;   c[5] = e11;   c[9] = e21;   c[13] = e31;
    c[2] = e02;   c[6] = e12;   c[10] = e22;  c[14] = e32;
    c[3] = e03;   c[7] = e13;   c[11] = e23;  c[15] = e33;
    return *this;
}

template< typename T >
mat4_t<T>& mat4_t<T>::transpose()
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
mat4_t<T>&  mat4_t<T>::norm()
{
    this->column( 0,
                  vec4( this->column(0)(x,y,z).norm(),
                        (*this)[0][3]                 ) );
    this->column( 1,
                  vec4( this->column(1)(x,y,z).norm(),
                        (*this)[1][3]                 ) );
    this->column( 2,
                  vec4( this->column(2)(x,y,z).norm(),
                        (*this)[2][3]                 ) );
    return *this;
}

template< typename T > inline
mat4_t<T>&  mat4_t<T>::ortho()
{
    T* cm = data.c;
    T x_xs = cm[0]*cm[0];
    T x_ys = cm[1]*cm[1];
    T x_zs = cm[2]*cm[2];
    
    T xy_xx = cm[0]*cm[4];
    T xy_yy = cm[1]*cm[5];
    T xy_zz = cm[2]*cm[6];
    
    T xz_xx = cm[0]*cm[8];
    T xz_yy = cm[1]*cm[9];
    T xz_zz = cm[2]*cm[10];
    
    cm[4] = cm[4]*(x_ys + x_zs) - cm[0]*(xy_yy + xy_zz);
    cm[5] = cm[5]*(x_zs + x_xs) - cm[1]*(xy_zz + xy_xx);
    cm[6] = cm[6]*(x_xs + x_ys) - cm[2]*(xy_xx + xy_yy);
    
    cm[8]  = cm[8] *(x_ys + x_zs) - cm[0]*(xz_yy + xz_zz);
    cm[9]  = cm[9] *(x_zs + x_xs) - cm[1]*(xz_zz + xz_xx);
    cm[10] = cm[10]*(x_xs + x_ys) - cm[2]*(xz_xx + xz_yy);
    
    return *this;
}

template< typename T > inline
raw_map const   mat4_t<T>::to_map() const
{
    return map_bytes( sizeof(T) * 16, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat4_t<T> const& src )
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

// --------------- Matrix 2x3 --------------


template< typename T > inline
mat2x3_t<T>::mat2x3_t()
{ T* c = this->data.c;
  c[0] = lit<T>::zero;   c[3] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[4] = lit<T>::zero;
  c[2] = lit<T>::zero;   c[5] = lit<T>::zero; }

template< typename T > inline
mat2x3_t<T>::mat2x3_t( mat2x3_t<T> const& copy )
{ T* c = this->data.c;
  c[0] = copy.data.c[0];
  c[1] = copy.data.c[1];
  c[2] = copy.data.c[2];
  c[3] = copy.data.c[3];
  c[4] = copy.data.c[4];
  c[5] = copy.data.c[5]; }
  
template< typename T >
mat2x3_t<T>::mat2x3_t( T e00, T e10,
                       T e01, T e11,
                       T e02, T e12 )
{ T* c = this->data.c;
  c[0] = e00;   c[3] = e10;
  c[1] = e01;   c[4] = e11;
  c[2] = e02;   c[5] = e12; }

template< typename T >
mat2x3_t<T>::mat2x3_t( T fill )
{ T* c = this->data.c;
  c[0] = fill;   c[3] = fill;
  c[1] = fill;   c[4] = fill;
  c[2] = fill;   c[5] = fill; }
// Named Construction

template< typename T > inline
mat2x3_t<T>::mat2x3_t( vec3_t<T> const& col0,
                       vec3_t<T> const& col1 )
{ T* c = this->data.c;
  c[0] = col0[0];   c[3] = col1[0];
  c[1] = col0[1];   c[4] = col1[1];
  c[2] = col0[2];   c[5] = col1[2]; }


template< typename T >
mat2x3_t<T>     mat2x3_t<T>::upper_identity()
{ return mat2x3_t<T>( lit<T>::one,  lit<T>::zero,
                      lit<T>::zero, lit<T>::one,
                      lit<T>::zero, lit<T>::zero ); }

template< typename T > inline
mat2x3_t<T>     mat2x3_t<T>::row_vectors( vec2_t<T> const& row0,
                                          vec2_t<T> const& row1,
                                          vec2_t<T> const& row2 )
{ return mat2x3_t( row0[0], row0[1],
                   row1[0], row1[1],
                   row2[0], row2[1] ); }

// Comparison
               
template< typename T > inline
bool    mat2x3_t<T>::operator==( mat2x3_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs(lhs_c[0] - rhs_c[0]) < lit<T>::delta
           and std::abs(lhs_c[1] - rhs_c[1]) < lit<T>::delta
           and std::abs(lhs_c[2] - rhs_c[2]) < lit<T>::delta
           and std::abs(lhs_c[3] - rhs_c[3]) < lit<T>::delta
           and std::abs(lhs_c[4] - rhs_c[4]) < lit<T>::delta
           and std::abs(lhs_c[5] - rhs_c[5]) < lit<T>::delta;
}

template< typename T > inline
bool    mat2x3_t<T>::operator<( mat2x3_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool less = true;
    
    if ( (*this) != rhs ) {
        less =     lhs_c[0] < rhs_c[0]
               and lhs_c[1] < rhs_c[1]
               and lhs_c[2] < rhs_c[2]
               and lhs_c[3] < rhs_c[3]
               and lhs_c[4] < rhs_c[4]
               and lhs_c[5] < rhs_c[5];
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat2x3_t<T>::operator>( mat2x3_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool greater = true;
    
    if ( (*this) != rhs ) {
        greater =     lhs_c[0] > rhs_c[0]
                  and lhs_c[1] > rhs_c[1]
                  and lhs_c[2] > rhs_c[2]
                  and lhs_c[3] > rhs_c[3]
                  and lhs_c[4] > rhs_c[4]
                  and lhs_c[5] > rhs_c[5];
    } else {
        greater = false;
    }

    return greater;
}

template< typename T > inline
bool    mat2x3_t<T>::operator<=( mat2x3_t<T> const& rhs ) const
{
    bool less = true;
    
    if ( not ((*this) > rhs) ) {
        less = true;
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat2x3_t<T>::operator>=( mat2x3_t<T> const& rhs ) const
{
    bool greater = true;
    
    if ( not ((*this) < rhs) ) {
        greater = true;
    } else {
        greater = false;
    }

    return greater;
}

template< typename T > inline
bool    mat2x3_t<T>::operator!=( mat2x3_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs( lhs_c[0] - rhs_c[0] ) >= lit<T>::delta
            or std::abs( lhs_c[1] - rhs_c[1] ) >= lit<T>::delta
            or std::abs( lhs_c[2] - rhs_c[2] ) >= lit<T>::delta
            or std::abs( lhs_c[3] - rhs_c[3] ) >= lit<T>::delta
            or std::abs( lhs_c[4] - rhs_c[4] ) >= lit<T>::delta
            or std::abs( lhs_c[5] - rhs_c[5] ) >= lit<T>::delta;
}

// Arithmetic

template< typename T > inline
mat2x3_t<T>     mat2x3_t<T>::operator+( mat2x3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] + rhs_c[0];
    T e01 = lhs_c[1] + rhs_c[1];
    T e02 = lhs_c[2] + rhs_c[2];
    T e10 = lhs_c[3] + rhs_c[3];
    T e11 = lhs_c[4] + rhs_c[4];
    T e12 = lhs_c[5] + rhs_c[5];
    
    return mat2x3_t<T>( e00, e10,
                        e01, e11,
                        e02, e12 );
}

template< typename T > inline
mat2x3_t<T>     mat2x3_t<T>::operator-() const
{
    T const* lhs_c = this->data.c;
    
    T e00 = -lhs_c[0];
    T e01 = -lhs_c[1];
    T e02 = -lhs_c[2];
    T e10 = -lhs_c[3];
    T e11 = -lhs_c[4];
    T e12 = -lhs_c[5];
    
    return mat2x3_t( e00, e10,
                     e01, e11,
                     e02, e12 );
}

template< typename T > inline
mat2x3_t<T>     mat2x3_t<T>::operator-( mat2x3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] - rhs_c[0];
    T e01 = lhs_c[1] - rhs_c[1];
    T e02 = lhs_c[2] - rhs_c[2];
    T e10 = lhs_c[3] - rhs_c[3];
    T e11 = lhs_c[4] - rhs_c[4];
    T e12 = lhs_c[5] - rhs_c[5];
    
    return mat2x3_t<T>( e00, e10,
                        e01, e11,
                        e02, e12 );
}

template< typename T > inline
mat3_t<T>   mat2x3_t<T>::operator*( mat3x2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1];
    
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[3] * rhs_c[3];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[4] * rhs_c[3];
    T e12 = lhs_c[2] * rhs_c[2] + lhs_c[5] * rhs_c[3];
    
    T e20 = lhs_c[0] * rhs_c[4] + lhs_c[3] * rhs_c[5];
    T e21 = lhs_c[1] * rhs_c[4] + lhs_c[4] * rhs_c[5];
    T e22 = lhs_c[2] * rhs_c[4] + lhs_c[5] * rhs_c[5];
    
    return mat3_t<T>( e00, e10, e20,
                      e01, e11, e21,
                      e02, e12, e22 );
}

template< typename T > inline
mat4x3_t<T>   mat2x3_t<T>::operator*( mat4x2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1];
    
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[3] * rhs_c[3];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[4] * rhs_c[3];
    T e12 = lhs_c[2] * rhs_c[2] + lhs_c[5] * rhs_c[3];
    
    T e20 = lhs_c[0] * rhs_c[4] + lhs_c[3] * rhs_c[5];
    T e21 = lhs_c[1] * rhs_c[4] + lhs_c[4] * rhs_c[5];
    T e22 = lhs_c[2] * rhs_c[4] + lhs_c[5] * rhs_c[5];
    
    T e30 = lhs_c[0] * rhs_c[6] + lhs_c[3] * rhs_c[7];
    T e31 = lhs_c[1] * rhs_c[6] + lhs_c[4] * rhs_c[7];
    T e32 = lhs_c[2] * rhs_c[6] + lhs_c[5] * rhs_c[7];
    
    return mat4x3_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31,
                        e02, e12, e22, e32 );
}

template< typename T > inline
mat2x3_t<T>   mat2x3_t<T>::operator*( mat2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1];
    
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[3] * rhs_c[3];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[4] * rhs_c[3];
    T e12 = lhs_c[2] * rhs_c[2] + lhs_c[5] * rhs_c[3];
    
    return mat2x3_t<T>( e00, e10,
                        e01, e11,
                        e02, e12 );
}

template< typename T > inline
vec3_t<T>     mat2x3_t<T>::operator*( vec2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T x0 = lhs_c[0] * rhs[0] + lhs_c[3] * rhs[1];
    T x1 = lhs_c[1] * rhs[0] + lhs_c[4] * rhs[1];
    T x2 = lhs_c[2] * rhs[0] + lhs_c[5] * rhs[1];
    
    return vec3_t<T>( x0, x1, x2 );
}

template< typename T > inline
vec2_t<T>     operator*( vec3_t<T> const& lhs,
                         mat2x3_t<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    
    T x0 = rhs_c[0] * lhs[0] + rhs_c[1] * lhs[1] + rhs_c[2] * lhs[2];
    T x1 = rhs_c[3] * lhs[0] + rhs_c[4] * lhs[1] + rhs_c[5] * lhs[2];
    
    return vec2_t<T>( x0, x1 );
}

template< typename T >
mat2x3_t<T>     mat2x3_t<T>::operator*( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] * rhs;
    T e01 = lhs_c[1] * rhs;
    T e02 = lhs_c[2] * rhs;
    T e10 = lhs_c[3] * rhs;
    T e11 = lhs_c[4] * rhs;
    T e12 = lhs_c[5] * rhs;
    
    return mat2x3_t( e00, e10,
                     e01, e11,
                     e02, e12 );
}

template< typename D >
mat2x3_t<D>     operator*( D lhs, mat2x3_t<D> const& rhs )
{
    D const* rhs_c = rhs.data.c;
    
    D e00 = rhs_c[0] * lhs;
    D e01 = rhs_c[1] * lhs;
    D e02 = rhs_c[2] * lhs;
    D e10 = rhs_c[3] * lhs;
    D e11 = rhs_c[4] * lhs;
    D e12 = rhs_c[5] * lhs;
    
    return mat2x3_t<D>( e00, e10,
                     e01, e11,
                     e02, e12 );
}

template< typename T >
mat2x3_t<T>     mat2x3_t<T>::operator/( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] / rhs;
    T e01 = lhs_c[1] / rhs;
    T e02 = lhs_c[2] / rhs;
    T e10 = lhs_c[3] / rhs;
    T e11 = lhs_c[4] / rhs;
    T e12 = lhs_c[5] / rhs;
    
    return mat2x3_t<T>( e00, e10,
                        e01, e11,
                        e02, e12 );
}

// Mutative Operators

template< typename T > inline
mat2x3_t<T>&    mat2x3_t<T>::operator=( mat2x3_t<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    lhs_c[0] = rhs_c[0];
    lhs_c[1] = rhs_c[1];
    lhs_c[2] = rhs_c[2];
    lhs_c[3] = rhs_c[3];
    lhs_c[4] = rhs_c[4];
    lhs_c[5] = rhs_c[5];
    return *this;
}

template< typename T > inline
col3<T>     mat2x3_t<T>::operator[]( size_t i )
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat2x3_t out of range" );
    }
    
    return col3<T>( this->data.c + (3*i), true );
}

template< typename T > inline
col3<T>     mat2x3_t<T>::operator[]( size_t i ) const
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat2x3_t out of range" );
    }
    
    T* col_cpy = new T[3];
    
    col_cpy[0] = this-data->c[ 3 * i ];
    col_cpy[1] = this-data->c[ 3 * i + 1 ];
    col_cpy[2] = this-data->c[ 3 * i + 2 ];
    
    return col3<T>( col_cpy, false );
}

template< typename T > inline
T&     mat2x3_t<T>::operator()( size_t col,
                                size_t row )
{
    if ( col > 1 or row > 2 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat2x3_t used out of bounds index");
    }
    
    return this->data.c[col * 3 + row];
}

template< typename T > inline
T      mat2x3_t<T>::operator()( size_t col,
                                size_t row ) const
{
    if ( col > 1 or row > 2 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat2x3_t used out of bounds index");
    }
    
    return this->data.c[col * 3 + row];
}

// Mutative Functions

template< typename T > inline
col3<T>    mat2x3_t<T>::column( size_t col )
{ return (*this)[col]; }

template< typename T > inline
col3<T>     mat2x3_t<T>::column( size_t col ) const
{ return (*this)[col]; }

template< typename T > inline
mat2x3_t<T>&    mat2x3_t<T>::columns( vec3_t<T> const& col0,
                                      vec3_t<T> const& col1 )
{
    T* cm = this->data.c;
    
    cm[0] = col0[0];
    cm[1] = col0[1];
    cm[2] = col0[2];
    cm[3] = col1[0];
    cm[4] = col1[1];
    cm[5] = col1[2];
    
    return *this;
}

template< typename T >
mat2x3_t<T>& mat2x3_t<T>::fill( T val )
{
    T* c = this->data.c;
    c[0] = val;
    c[1] = val;
    c[2] = val;
    c[3] = val;
    c[4] = val;
    c[5] = val;
    return *this;
}

template< typename T > inline
row2<T>    mat2x3_t<T>::row( size_t row )
{
    if ( row > 2 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat2x3_t out of range" );
    }
    
    return row2<T>( this->data.c + row,
                    this->data.c + 3 + row,
                    true );
}

template< typename T > inline
row2<T>     mat2x3_t<T>::row( size_t row ) const
{
    if ( row > 2 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat2x3_t out of range" );
    }
    
    return row2<T>( this->data.c[row],
                    this->data.c[3 + row] );
}

template< typename T > inline
mat2x3_t<T>& mat2x3_t<T>::rows( vec2_t<T> const& row0,
                                vec2_t<T> const& row1,
                                vec2_t<T> const& row2 )
{
    T* cm = this->data.c;
    
    cm[0] = row0[0];
    cm[3] = row0[1];
    cm[1] = row1[0];
    cm[4] = row1[1];
    cm[2] = row2[0];
    cm[5] = row2[1];
    
    return *this;
}

// Utility

template< typename T > inline
raw_map const   mat2x3_t<T>::to_map() const
{
    return map_bytes( sizeof(T) * 6, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat2x3_t<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " ]" << '\n';
    stream << "[ " << src(0,2) << " " << src(1,2) << " ]" << std::endl;
    return stream;
}

// ---------------- Matrix 3x2 -----------------

template< typename T > inline
mat3x2_t<T>::mat3x2_t()
{ T* c = this->data.c;
  c[0] = lit<T>::zero;   c[2] = lit<T>::zero;   c[4] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[3] = lit<T>::zero;   c[5] = lit<T>::zero; }
  
template< typename T > inline
mat3x2_t<T>::mat3x2_t( mat3x2_t<T> const& copy )
{ T* c = this->data.c;
  c[0] = copy.data.c[0];
  c[1] = copy.data.c[1];
  c[2] = copy.data.c[2];
  c[3] = copy.data.c[3];
  c[4] = copy.data.c[4];
  c[5] = copy.data.c[5]; }

template< typename T >
mat3x2_t<T>::mat3x2_t( T e00, T e10, T e20,
                       T e01, T e11, T e21 )
{ T* c = this->data.c;
  c[0] = e00;   c[2] = e10;   c[4] = e20;
  c[1] = e01;   c[3] = e11;   c[5] = e21; }

template< typename T >
mat3x2_t<T>::mat3x2_t( T fill )
{ T* c = this->data.c;
  c[0] = fill;   c[2] = fill;   c[4] = fill;
  c[1] = fill;   c[3] = fill;   c[5] = fill; }
  
template< typename T > inline
mat3x2_t<T>::mat3x2_t( vec2_t<T> const& col0,
                       vec2_t<T> const& col1,
                       vec2_t<T> const& col2 )
{ T* c = this->data.c;
  c[0] = col0[0];   c[2] = col1[0];   c[4] = col2[0];
  c[1] = col0[1];   c[3] = col1[1];   c[5] = col2[1]; }
  
template< typename T >
mat3x2_t<T>     mat3x2_t<T>::left_identity()
{ return mat3x2_t<T>( lit<T>::one,  lit<T>::zero, lit<T>::zero,
                      lit<T>::zero, lit<T>::one,  lit<T>::zero ); }
                      
template< typename T > inline
mat3x2_t<T>     mat3x2_t<T>::row_vectors( vec3_t<T> const& row0,
                                          vec3_t<T> const& row1 )
{ return mat3x2_t( row0[0], row0[1], row0[2],
                   row1[0], row1[1], row1[2] ); }

template< typename T > inline
bool    mat3x2_t<T>::operator==( mat3x2_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs(lhs_c[0] - rhs_c[0]) < lit<T>::delta
           and std::abs(lhs_c[1] - rhs_c[1]) < lit<T>::delta
           and std::abs(lhs_c[2] - rhs_c[2]) < lit<T>::delta
           and std::abs(lhs_c[3] - rhs_c[3]) < lit<T>::delta
           and std::abs(lhs_c[4] - rhs_c[4]) < lit<T>::delta
           and std::abs(lhs_c[5] - rhs_c[5]) < lit<T>::delta;
}

template< typename T > inline
bool    mat3x2_t<T>::operator<( mat3x2_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool less = true;
    
    if ( (*this) != rhs ) {
        less =     lhs_c[0] < rhs_c[0]
               and lhs_c[1] < rhs_c[1]
               and lhs_c[2] < rhs_c[2]
               and lhs_c[3] < rhs_c[3]
               and lhs_c[4] < rhs_c[4]
               and lhs_c[5] < rhs_c[5];
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat3x2_t<T>::operator>( mat3x2_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool greater = true;
    
    if ( (*this) != rhs ) {
        greater =     lhs_c[0] > rhs_c[0]
                  and lhs_c[1] > rhs_c[1]
                  and lhs_c[2] > rhs_c[2]
                  and lhs_c[3] > rhs_c[3]
                  and lhs_c[4] > rhs_c[4]
                  and lhs_c[5] > rhs_c[5];
    } else {
        greater = false;
    }

    return greater;
}

template< typename T > inline
bool    mat3x2_t<T>::operator<=( mat3x2_t<T> const& rhs ) const
{
    bool less = true;
    
    if ( not ((*this) > rhs) ) {
        less = true;
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat3x2_t<T>::operator>=( mat3x2_t<T> const& rhs ) const
{
    bool greater = true;
    
    if ( not ((*this) < rhs) ) {
        greater = true;
    } else {
        greater = false;
    }

    return greater;
}

template< typename T > inline
bool    mat3x2_t<T>::operator!=( mat3x2_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs( lhs_c[0] - rhs_c[0] ) >= lit<T>::delta
            or std::abs( lhs_c[1] - rhs_c[1] ) >= lit<T>::delta
            or std::abs( lhs_c[2] - rhs_c[2] ) >= lit<T>::delta
            or std::abs( lhs_c[3] - rhs_c[3] ) >= lit<T>::delta
            or std::abs( lhs_c[4] - rhs_c[4] ) >= lit<T>::delta
            or std::abs( lhs_c[5] - rhs_c[5] ) >= lit<T>::delta;
}
  
  template< typename T > inline
mat3x2_t<T>     mat3x2_t<T>::operator+( mat3x2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] + rhs_c[0];
    T e01 = lhs_c[1] + rhs_c[1];
    T e10 = lhs_c[2] + rhs_c[2];
    T e11 = lhs_c[3] + rhs_c[3];
    T e20 = lhs_c[4] + rhs_c[4];
    T e21 = lhs_c[5] + rhs_c[5];
    
    return mat3x2_t<T>( e00, e10, e20,
                        e01, e11, e21 );
}

template< typename T > inline
mat3x2_t<T>     mat3x2_t<T>::operator-() const
{
    T const* lhs_c = this->data.c;
    
    T e00 = -lhs_c[0];
    T e01 = -lhs_c[1];
    T e10 = -lhs_c[2];
    T e11 = -lhs_c[3];
    T e20 = -lhs_c[4];
    T e21 = -lhs_c[5];
    
    return mat3x2_t( e00, e10, e20,
                     e01, e11, e21 );
}

template< typename T > inline
mat3x2_t<T>     mat3x2_t<T>::operator-( mat3x2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] - rhs_c[0];
    T e01 = lhs_c[1] - rhs_c[1];
    T e10 = lhs_c[2] - rhs_c[2];
    T e11 = lhs_c[3] - rhs_c[3];
    T e20 = lhs_c[4] - rhs_c[4];
    T e21 = lhs_c[5] - rhs_c[5];
    
    return mat3x2_t<T>( e00, e10, e20,
                        e01, e11, e21 );
}  

template< typename T > inline
mat2_t<T>     mat3x2_t<T>::operator*( mat2x3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1] + lhs_c[4] * rhs_c[2];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[5] * rhs_c[2];
    T e10 = lhs_c[0] * rhs_c[3] + lhs_c[2] * rhs_c[4] + lhs_c[4] * rhs_c[5];
    T e11 = lhs_c[1] * rhs_c[3] + lhs_c[3] * rhs_c[4] + lhs_c[5] * rhs_c[5];
    
    return mat2_t<T>( e00, e10,
                      e01, e11 );
}

template< typename T > inline
mat4x2_t<T>     mat3x2_t<T>::operator*( mat4x3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1] + lhs_c[4] * rhs_c[2];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[5] * rhs_c[2];
    
    T e10 = lhs_c[0] * rhs_c[3] + lhs_c[2] * rhs_c[4] + lhs_c[4] * rhs_c[5];
    T e11 = lhs_c[1] * rhs_c[3] + lhs_c[3] * rhs_c[4] + lhs_c[5] * rhs_c[5];
    
    T e20 = lhs_c[0] * rhs_c[6] + lhs_c[2] * rhs_c[7] + lhs_c[4] * rhs_c[8];
    T e21 = lhs_c[1] * rhs_c[6] + lhs_c[3] * rhs_c[7] + lhs_c[5] * rhs_c[8];
    
    T e30 = lhs_c[0] * rhs_c[9] + lhs_c[2] * rhs_c[10] + lhs_c[4] * rhs_c[11];
    T e31 = lhs_c[1] * rhs_c[9] + lhs_c[3] * rhs_c[10] + lhs_c[5] * rhs_c[11];
    
    return mat4x2_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31 );
}

template< typename T > inline
mat3x2_t<T>     mat3x2_t<T>::operator*( mat3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1] + lhs_c[4] * rhs_c[2];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[5] * rhs_c[2];
    
    T e10 = lhs_c[0] * rhs_c[3] + lhs_c[2] * rhs_c[4] + lhs_c[4] * rhs_c[5];
    T e11 = lhs_c[1] * rhs_c[3] + lhs_c[3] * rhs_c[4] + lhs_c[5] * rhs_c[5];
    
    T e20 = lhs_c[0] * rhs_c[6] + lhs_c[2] * rhs_c[7] + lhs_c[4] * rhs_c[8];
    T e21 = lhs_c[1] * rhs_c[6] + lhs_c[3] * rhs_c[7] + lhs_c[5] * rhs_c[8];
    
    return mat3x2_t<T>( e00, e10, e20,
                        e01, e11, e21 );
}

template< typename T > inline
vec2_t<T>     mat3x2_t<T>::operator*( vec3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T x0 = lhs_c[0] * rhs[0] + lhs_c[2] * rhs[1] + lhs_c[4] * rhs[2];
    T x1 = lhs_c[1] * rhs[0] + lhs_c[3] * rhs[1] + lhs_c[5] * rhs[2];
    
    return vec2_t<T>( x0, x1 );
}

template< typename T > inline
vec3_t<T>     operator*( vec2_t<T> const& lhs,
                         mat3x2_t<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    
    T x0 = rhs_c[0] * lhs[0] + rhs_c[1] * lhs[1];
    T x1 = rhs_c[2] * lhs[0] + rhs_c[3] * lhs[1];
    T x2 = rhs_c[4] * lhs[0] + rhs_c[5] * lhs[1];
    
    return vec3_t<T>( x0, x1, x2 );
}

template< typename T >
mat3x2_t<T>     mat3x2_t<T>::operator*( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] * rhs;
    T e01 = lhs_c[1] * rhs;
    T e10 = lhs_c[2] * rhs;
    T e11 = lhs_c[3] * rhs;
    T e20 = lhs_c[4] * rhs;
    T e21 = lhs_c[5] * rhs;
    
    return mat3x2_t<T>( e00, e10, e20,
                        e01, e11, e21 );
}

template< typename D >
mat3x2_t<D>     operator*( D lhs, mat3x2_t<D> const& rhs )
{
    D const* rhs_c = rhs.data.c;
    
    D e00 = rhs_c[0] * lhs;
    D e01 = rhs_c[1] * lhs;
    D e10 = rhs_c[2] * lhs;
    D e11 = rhs_c[3] * lhs;
    D e20 = rhs_c[4] * lhs;
    D e21 = rhs_c[5] * lhs;
    
    return mat3x2_t<D>( e00, e10, e20,
                        e01, e11, e21 );
}

template< typename T >
mat3x2_t<T>     mat3x2_t<T>::operator/( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] / rhs;
    T e01 = lhs_c[1] / rhs;
    T e10 = lhs_c[2] / rhs;
    T e11 = lhs_c[3] / rhs;
    T e20 = lhs_c[4] / rhs;
    T e21 = lhs_c[5] / rhs;
    
    return mat3x2_t<T>( e00, e10, e20,
                        e01, e11, e21 );
}

template< typename T > inline
mat3x2_t<T>&    mat3x2_t<T>::operator=( mat3x2_t<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    T* lhs_c = this->data.c;
    lhs_c[0] = rhs_c[0];
    lhs_c[1] = rhs_c[1];
    lhs_c[2] = rhs_c[2];
    lhs_c[3] = rhs_c[3];
    lhs_c[4] = rhs_c[4];
    lhs_c[5] = rhs_c[5];
    return *this;
}

template< typename T > inline
col2<T>     mat3x2_t<T>::operator[]( size_t i )
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat3x2_t out of range" );
    }
    
    return col2<T>( this->data.c + (2*i), true );
}

template< typename T > inline
col2<T>     mat3x2_t<T>::operator[]( size_t i ) const
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat3x2_t out of range" );
    }
    
    T* col_cpy = new T[2];
    
    col_cpy[0] = this-data->c[ 2 * i ];
    col_cpy[1] = this-data->c[ 2 * i + 1 ];
    
    return col2<T>( col_cpy, false );
}
  
template< typename T > inline
T&     mat3x2_t<T>::operator()( size_t col,
                                size_t row )
{
    if ( col > 2 or row > 1 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat3x2_t used out of bounds index");
    }
    
    return this->data.c[col * 2 + row];
}

template< typename T > inline
T      mat3x2_t<T>::operator()( size_t col,
                                size_t row ) const
{
    if ( col > 2 or row > 1 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat3x2_t used out of bounds index");
    }
    
    return this->data.c[col * 2 + row];
}

template< typename T > inline
col2<T>    mat3x2_t<T>::column( size_t col )
{ return (*this)[col]; }

template< typename T > inline
col2<T>     mat3x2_t<T>::column( size_t col ) const
{ return (*this)[col]; }

template< typename T > inline
mat3x2_t<T>&    mat3x2_t<T>::columns( vec2_t<T> const& col0,
                                      vec2_t<T> const& col1,
                                      vec2_t<T> const& col2 )
{
    T* cm = this->data.c;
    
    cm[0] = col0[0];
    cm[1] = col0[1];
    cm[2] = col1[0];
    cm[3] = col1[1];
    cm[4] = col2[0];
    cm[5] = col2[1];
    
    return *this;
}

template< typename T >
mat3x2_t<T>& mat3x2_t<T>::fill( T val )
{
    T* c = this->data.c;
    c[0] = val;
    c[1] = val;
    c[2] = val;
    c[3] = val;
    c[4] = val;
    c[5] = val;
    return *this;
}

template< typename T > inline
row3<T>    mat3x2_t<T>::row( size_t row )
{
    if ( row > 1 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat3x2_t out of range" );
    }
    
    return row3<T>( this->data.c + row,
                    this->data.c + 2 + row,
                    this->data.c + 4 + row,
                    true );
}

template< typename T > inline
row3<T>     mat3x2_t<T>::row( size_t row ) const
{
    if ( row > 1 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat3x2_t out of range" );
    }
    
    return row3<T>( this->data.c[row],
                    this->data.c[2 + row],
                    this->data.c[4 + row] );
}

template< typename T > inline
mat3x2_t<T>& mat3x2_t<T>::rows( vec3_t<T> const& row0,
                                vec3_t<T> const& row1 )
{
    T* cm = this->data.c;
    
    cm[0] = row0[0];
    cm[2] = row0[1];
    cm[4] = row0[2];
    cm[1] = row1[0];
    cm[3] = row1[1];
    cm[5] = row1[2];
    
    return *this;
}

template< typename T > inline
raw_map const   mat3x2_t<T>::to_map() const
{
    return map_bytes( sizeof(T) * 6, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat3x2_t<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " " << src(2,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " " << src(2,1) << " ]" << std::endl;
    return stream;
}


// -------------- Matrix 2x4 -----------------

template< typename T > inline
mat2x4_t<T>::mat2x4_t()
{ T* c = this->data.c;
  c[0] = lit<T>::zero;   c[4] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[5] = lit<T>::zero;
  c[2] = lit<T>::zero;   c[6] = lit<T>::zero;
  c[3] = lit<T>::zero;   c[7] = lit<T>::zero; }
  
template< typename T > inline
mat2x4_t<T>::mat2x4_t( mat2x4_t<T> const& copy )
{ T* c = this->data.c;
  c[0] = copy.data.c[0];
  c[1] = copy.data.c[1];
  c[2] = copy.data.c[2];
  c[3] = copy.data.c[3];
  c[4] = copy.data.c[4];
  c[5] = copy.data.c[5];
  c[6] = copy.data.c[6];
  c[7] = copy.data.c[7]; }

template< typename T >
mat2x4_t<T>::mat2x4_t( T e00, T e10,
                       T e01, T e11,
                       T e02, T e12,
                       T e03, T e13 )
{ T* c = this->data.c;
  c[0] = e00;   c[4] = e10;
  c[1] = e01;   c[5] = e11;
  c[2] = e02;   c[6] = e12;
  c[3] = e03;   c[7] = e13; }
  
template< typename T >
mat2x4_t<T>::mat2x4_t( T fill )
{ T* c = this->data.c;
  c[0] = fill;   c[4] = fill;
  c[1] = fill;   c[5] = fill;
  c[2] = fill;   c[6] = fill;
  c[3] = fill;   c[7] = fill; }
  
template< typename T > inline
mat2x4_t<T>::mat2x4_t( vec4_t<T> const& col0,
                       vec4_t<T> const& col1 )
{ T* c = this->data.c;
  c[0] = col0[0];   c[4] = col1[0];
  c[1] = col0[1];   c[5] = col1[1];
  c[2] = col0[2];   c[6] = col1[2];
  c[3] = col0[3];   c[7] = col1[3]; }
  
template< typename T >
mat2x4_t<T>     mat2x4_t<T>::upper_identity()
{ return mat2x4_t<T>( lit<T>::one,  lit<T>::zero,
                      lit<T>::zero, lit<T>::one,
                      lit<T>::zero, lit<T>::zero,
                      lit<T>::zero, lit<T>::zero ); }
                      
template< typename T > inline
mat2x4_t<T>     mat2x4_t<T>::row_vectors( vec2_t<T> const& row0,
                                          vec2_t<T> const& row1,
                                          vec2_t<T> const& row2,
                                          vec2_t<T> const& row3 )
{ return mat2x4_t( row0[0], row0[1],
                   row1[0], row1[1],
                   row2[0], row2[1],
                   row3[0], row3[1] ); }

template< typename T > inline
bool    mat2x4_t<T>::operator==( mat2x4_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs(lhs_c[0] - rhs_c[0]) < lit<T>::delta
           and std::abs(lhs_c[1] - rhs_c[1]) < lit<T>::delta
           and std::abs(lhs_c[2] - rhs_c[2]) < lit<T>::delta
           and std::abs(lhs_c[3] - rhs_c[3]) < lit<T>::delta
           and std::abs(lhs_c[4] - rhs_c[4]) < lit<T>::delta
           and std::abs(lhs_c[5] - rhs_c[5]) < lit<T>::delta
           and std::abs(lhs_c[6] - rhs_c[6]) < lit<T>::delta
           and std::abs(lhs_c[7] - rhs_c[7]) < lit<T>::delta;
}

template< typename T > inline
bool    mat2x4_t<T>::operator<( mat2x4_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool less = true;
    
    if ( (*this) != rhs ) {
        less =     lhs_c[0] < rhs_c[0]
               and lhs_c[1] < rhs_c[1]
               and lhs_c[2] < rhs_c[2]
               and lhs_c[3] < rhs_c[3]
               and lhs_c[4] < rhs_c[4]
               and lhs_c[5] < rhs_c[5]
               and lhs_c[6] < rhs_c[6]
               and lhs_c[7] < rhs_c[7];
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat2x4_t<T>::operator>( mat2x4_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool greater = true;
    
    if ( (*this) != rhs ) {
        greater =     lhs_c[0] > rhs_c[0]
                  and lhs_c[1] > rhs_c[1]
                  and lhs_c[2] > rhs_c[2]
                  and lhs_c[3] > rhs_c[3]
                  and lhs_c[4] > rhs_c[4]
                  and lhs_c[5] > rhs_c[5]
                  and lhs_c[6] > rhs_c[6]
                  and lhs_c[7] > rhs_c[7];
    } else {
        greater = false;
    }

    return greater;
}


template< typename T > inline
bool    mat2x4_t<T>::operator<=( mat2x4_t<T> const& rhs ) const
{
    bool less = true;
    
    if ( not ((*this) > rhs) ) {
        less = true;
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat2x4_t<T>::operator>=( mat2x4_t<T> const& rhs ) const
{
    bool greater = true;
    
    if ( not ((*this) < rhs) ) {
        greater = true;
    } else {
        greater = false;
    }

    return greater;
}


template< typename T > inline
bool    mat2x4_t<T>::operator!=( mat2x4_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs( lhs_c[0] - rhs_c[0] ) >= lit<T>::delta
            or std::abs( lhs_c[1] - rhs_c[1] ) >= lit<T>::delta
            or std::abs( lhs_c[2] - rhs_c[2] ) >= lit<T>::delta
            or std::abs( lhs_c[3] - rhs_c[3] ) >= lit<T>::delta
            or std::abs( lhs_c[4] - rhs_c[4] ) >= lit<T>::delta
            or std::abs( lhs_c[5] - rhs_c[5] ) >= lit<T>::delta
            or std::abs( lhs_c[6] - rhs_c[6] ) >= lit<T>::delta
            or std::abs( lhs_c[7] - rhs_c[7] ) >= lit<T>::delta;
}

template< typename T > inline
mat2x4_t<T>     mat2x4_t<T>::operator+( mat2x4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] + rhs_c[0];
    T e01 = lhs_c[1] + rhs_c[1];
    T e02 = lhs_c[2] + rhs_c[2];
    T e03 = lhs_c[3] + rhs_c[3];
    T e10 = lhs_c[4] + rhs_c[4];
    T e11 = lhs_c[5] + rhs_c[5];
    T e12 = lhs_c[6] + rhs_c[6];
    T e13 = lhs_c[7] + rhs_c[7];
    
    return mat2x4_t<T>( e00, e10,
                        e01, e11,
                        e02, e12,
                        e03, e13 );
}

template< typename T > inline
mat2x4_t<T>     mat2x4_t<T>::operator-() const
{
    T const* lhs_c = this->data.c;
    
    T e00 = -lhs_c[0];
    T e01 = -lhs_c[1];
    T e02 = -lhs_c[2];
    T e03 = -lhs_c[3];
    T e10 = -lhs_c[4];
    T e11 = -lhs_c[5];
    T e12 = -lhs_c[6];
    T e13 = -lhs_c[7];
    
    return mat2x4_t( e00, e10,
                     e01, e11,
                     e02, e12,
                     e03, e13 );
}

template< typename T > inline
mat2x4_t<T>     mat2x4_t<T>::operator-( mat2x4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] - rhs_c[0];
    T e01 = lhs_c[1] - rhs_c[1];
    T e02 = lhs_c[2] - rhs_c[2];
    T e03 = lhs_c[3] - rhs_c[3];
    T e10 = lhs_c[4] - rhs_c[4];
    T e11 = lhs_c[5] - rhs_c[5];
    T e12 = lhs_c[6] - rhs_c[6];
    T e13 = lhs_c[7] - rhs_c[7];
    
    return mat2x4_t<T>( e00, e10,
                        e01, e11,
                        e02, e12,
                        e03, e13 );
}

template< typename T > inline
mat4_t<T>     mat2x4_t<T>::operator*( mat4x2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[4] * rhs_c[1];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[5] * rhs_c[1];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[6] * rhs_c[1];
    T e03 = lhs_c[3] * rhs_c[0] + lhs_c[7] * rhs_c[1];
    
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[4] * rhs_c[3];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[5] * rhs_c[3];
    T e12 = lhs_c[2] * rhs_c[2] + lhs_c[6] * rhs_c[3];
    T e13 = lhs_c[3] * rhs_c[2] + lhs_c[7] * rhs_c[3];
    
    T e20 = lhs_c[0] * rhs_c[4] + lhs_c[4] * rhs_c[5];
    T e21 = lhs_c[1] * rhs_c[4] + lhs_c[5] * rhs_c[5];
    T e22 = lhs_c[2] * rhs_c[4] + lhs_c[6] * rhs_c[5];
    T e23 = lhs_c[3] * rhs_c[4] + lhs_c[7] * rhs_c[5];
    
    T e30 = lhs_c[0] * rhs_c[6] + lhs_c[4] * rhs_c[7];
    T e31 = lhs_c[1] * rhs_c[6] + lhs_c[5] * rhs_c[7];
    T e32 = lhs_c[2] * rhs_c[6] + lhs_c[6] * rhs_c[7];
    T e33 = lhs_c[3] * rhs_c[6] + lhs_c[7] * rhs_c[7];
    
    return mat4_t<T>( e00, e10, e20, e30,
                      e01, e11, e21, e31,
                      e02, e12, e22, e32,
                      e03, e13, e23, e33 );
}

template< typename T > inline
mat3x4_t<T>     mat2x4_t<T>::operator*( mat3x2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[4] * rhs_c[1];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[5] * rhs_c[1];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[6] * rhs_c[1];
    T e03 = lhs_c[3] * rhs_c[0] + lhs_c[7] * rhs_c[1];
    
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[4] * rhs_c[3];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[5] * rhs_c[3];
    T e12 = lhs_c[2] * rhs_c[2] + lhs_c[6] * rhs_c[3];
    T e13 = lhs_c[3] * rhs_c[2] + lhs_c[7] * rhs_c[3];
    
    T e20 = lhs_c[0] * rhs_c[4] + lhs_c[4] * rhs_c[5];
    T e21 = lhs_c[1] * rhs_c[4] + lhs_c[5] * rhs_c[5];
    T e22 = lhs_c[2] * rhs_c[4] + lhs_c[6] * rhs_c[5];
    T e23 = lhs_c[3] * rhs_c[4] + lhs_c[7] * rhs_c[5];
    
    return mat3x4_t<T>( e00, e10, e20,
                        e01, e11, e21,
                        e02, e12, e22,
                        e03, e13, e23 );
}

template< typename T > inline
mat2x4_t<T>     mat2x4_t<T>::operator*( mat2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[4] * rhs_c[1];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[5] * rhs_c[1];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[6] * rhs_c[1];
    T e03 = lhs_c[3] * rhs_c[0] + lhs_c[7] * rhs_c[1];
    
    T e10 = lhs_c[0] * rhs_c[2] + lhs_c[4] * rhs_c[3];
    T e11 = lhs_c[1] * rhs_c[2] + lhs_c[5] * rhs_c[3];
    T e12 = lhs_c[2] * rhs_c[2] + lhs_c[6] * rhs_c[3];
    T e13 = lhs_c[3] * rhs_c[2] + lhs_c[7] * rhs_c[3];
    
    return mat2x4_t<T>( e00, e10,
                        e01, e11,
                        e02, e12,
                        e03, e13 );
}


template< typename T > inline
vec4_t<T>     mat2x4_t<T>::operator*( vec2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T x0 = lhs_c[0] * rhs[0] + lhs_c[4] * rhs[1];
    T x1 = lhs_c[1] * rhs[0] + lhs_c[5] * rhs[1];
    T x2 = lhs_c[2] * rhs[0] + lhs_c[6] * rhs[1];
    T x3 = lhs_c[3] * rhs[0] + lhs_c[7] * rhs[1];
    
    return vec4_t<T>( x0, x1, x2, x3 );
}

template< typename T > inline
vec2_t<T>     operator*( vec4_t<T> const& lhs,
                         mat2x4_t<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    
    T x0 = rhs_c[0] * lhs[0] + rhs_c[1] * lhs[1] + rhs_c[2] * lhs[2] + rhs_c[3] * lhs[3];
    T x1 = rhs_c[4] * lhs[0] + rhs_c[5] * lhs[1] + rhs_c[6] * lhs[2] + rhs_c[7] * lhs[3];
    
    return vec2_t<T>( x0, x1 );
}

template< typename T >
mat2x4_t<T>     mat2x4_t<T>::operator*( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] * rhs;
    T e01 = lhs_c[1] * rhs;
    T e02 = lhs_c[2] * rhs;
    T e03 = lhs_c[3] * rhs;
    T e10 = lhs_c[4] * rhs;
    T e11 = lhs_c[5] * rhs;
    T e12 = lhs_c[6] * rhs;
    T e13 = lhs_c[7] * rhs;
    
    return mat2x4_t( e00, e10,
                     e01, e11,
                     e02, e12,
                     e03, e13 );
}

template< typename D >
mat2x4_t<D>     operator*( D lhs, mat2x4_t<D> const& rhs )
{
    D const* rhs_c = rhs.data.c;
    
    D e00 = rhs_c[0] * lhs;
    D e01 = rhs_c[1] * lhs;
    D e02 = rhs_c[2] * lhs;
    D e03 = rhs_c[3] * lhs;
    D e10 = rhs_c[4] * lhs;
    D e11 = rhs_c[5] * lhs;
    D e12 = rhs_c[6] * lhs;
    D e13 = rhs_c[7] * lhs;
    
    return mat2x4_t<D>( e00, e10,
                        e01, e11,
                        e02, e12,
                        e03, e13 );
}

template< typename T >
mat2x4_t<T>     mat2x4_t<T>::operator/( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] / rhs;
    T e01 = lhs_c[1] / rhs;
    T e02 = lhs_c[2] / rhs;
    T e03 = lhs_c[3] / rhs;
    T e10 = lhs_c[4] / rhs;
    T e11 = lhs_c[5] / rhs;
    T e12 = lhs_c[6] / rhs;
    T e13 = lhs_c[7] / rhs;
    
    return mat2x4_t<T>( e00, e10,
                        e01, e11,
                        e02, e12,
                        e03, e13 );
}


template< typename T > inline
mat2x4_t<T>&    mat2x4_t<T>::operator=( mat2x4_t<T> const& rhs )
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
    return *this;
}


template< typename T > inline
col4<T>     mat2x4_t<T>::operator[]( size_t i )
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat2x4_t out of range" );
    }
    
    return col4<T>( this->data.c + (4*i), true );
}

template< typename T > inline
col4<T>     mat2x4_t<T>::operator[]( size_t i ) const
{
    if ( i > 1 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat2x4_t out of range" );
    }
    
    T* col_cpy = new T[4];
    
    col_cpy[0] = this-data->c[ 4 * i ];
    col_cpy[1] = this-data->c[ 4 * i + 1 ];
    col_cpy[2] = this-data->c[ 4 * i + 2 ];
    col_cpy[3] = this-data->c[ 4 * i + 3 ];
    
    return col4<T>( col_cpy, false );
}


template< typename T > inline
T&     mat2x4_t<T>::operator()( size_t col,
                                size_t row )
{
    if ( col > 1 or row > 3 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat2x4_t used out of bounds index");
    }
    
    return this->data.c[col * 4 + row];
}

template< typename T > inline
T      mat2x4_t<T>::operator()( size_t col,
                                size_t row ) const
{
    if ( col > 1 or row > 3 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat2x4_t used out of bounds index");
    }
    
    return this->data.c[col * 4 + row];
}


template< typename T > inline
col4<T>    mat2x4_t<T>::column( size_t col )
{ return (*this)[col]; }

template< typename T > inline
col4<T>     mat2x4_t<T>::column( size_t col ) const
{ return (*this)[col]; }

template< typename T > inline
mat2x4_t<T>&    mat2x4_t<T>::columns( vec4_t<T> const& col0,
                                      vec4_t<T> const& col1 )
{
    T* cm = this->data.c;
    
    cm[0] = col0[0];
    cm[1] = col0[1];
    cm[2] = col0[2];
    cm[3] = col0[3];
    cm[4] = col1[0];
    cm[5] = col1[1];
    cm[6] = col1[2];
    cm[7] = col1[3];
    
    return *this;
}


template< typename T >
mat2x4_t<T>& mat2x4_t<T>::fill( T val )
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
    return *this;
}


template< typename T > inline
row2<T>    mat2x4_t<T>::row( size_t row )
{
    if ( row > 3 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat2x4_t out of range" );
    }
    
    return row2<T>( this->data.c + row,
                    this->data.c + 4 + row,
                    true );
}

template< typename T > inline
row2<T>     mat2x4_t<T>::row( size_t row ) const
{
    if ( row > 3 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat2x4_t out of range" );
    }
    
    return row2<T>( this->data.c[row],
                    this->data.c[4 + row] );
}


template< typename T > inline
mat2x4_t<T>& mat2x4_t<T>::rows( vec2_t<T> const& row0,
                                vec2_t<T> const& row1,
                                vec2_t<T> const& row2,
                                vec2_t<T> const& row3 )
{
    T* cm = this->data.c;
    
    cm[0] = row0[0];
    cm[4] = row0[1];
    cm[1] = row1[0];
    cm[5] = row1[1];
    cm[2] = row2[0];
    cm[6] = row2[1];
    cm[3] = row3[0];
    cm[7] = row3[1];
    
    return *this;
}


template< typename T > inline
raw_map const   mat2x4_t<T>::to_map() const
{
    return map_bytes( sizeof(T) * 8, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat2x4_t<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " ]" << '\n';
    stream << "[ " << src(0,2) << " " << src(1,2) << " ]" << '\n';
    stream << "[ " << src(0,3) << " " << src(1,3) << " ]" << std::endl;
    return stream;
}

// ---------- Matrix 4x2 -----------


template< typename T > inline
mat4x2_t<T>::mat4x2_t()
{ T* c = this->data.c;
  c[0] = lit<T>::zero;   c[2] = lit<T>::zero;   c[4] = lit<T>::zero;   c[6] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[3] = lit<T>::zero;   c[5] = lit<T>::zero;   c[7] = lit<T>::zero; }
  
template< typename T > inline
mat4x2_t<T>::mat4x2_t( mat4x2_t<T> const& copy )
{ T* c = this->data.c;
  c[0] = copy.data.c[0];
  c[1] = copy.data.c[1];
  c[2] = copy.data.c[2];
  c[3] = copy.data.c[3];
  c[4] = copy.data.c[4];
  c[5] = copy.data.c[5];
  c[6] = copy.data.c[6];
  c[7] = copy.data.c[7];
}
  
template< typename T >
mat4x2_t<T>::mat4x2_t( T e00, T e10, T e20, T e30,
                       T e01, T e11, T e21, T e31 )
{ T* c = this->data.c;
  c[0] = e00;   c[2] = e10;   c[4] = e20;   c[6] = e30;
  c[1] = e01;   c[3] = e11;   c[5] = e21;   c[7] = e31; }
  
template< typename T >
mat4x2_t<T>::mat4x2_t( T fill )
{ T* c = this->data.c;
  c[0] = fill;   c[2] = fill;   c[4] = fill;   c[6] = fill;
  c[1] = fill;   c[3] = fill;   c[5] = fill;   c[7] = fill; }
  
template< typename T > inline
mat4x2_t<T>::mat4x2_t( vec2_t<T> const& col0,
                       vec2_t<T> const& col1,
                       vec2_t<T> const& col2,
                       vec2_t<T> const& col3 )
{ T* c = this->data.c;
  c[0] = col0[0];   c[2] = col1[0];
  c[4] = col2[0];   c[6] = col3[0];
  
  c[1] = col0[1];   c[3] = col1[1];
  c[5] = col2[1];   c[7] = col3[1]; }
  
template< typename T >
mat4x2_t<T>     mat4x2_t<T>::left_identity()
{ return mat4x2_t<T>( lit<T>::one,  lit<T>::zero, lit<T>::zero, lit<T>::zero,
                      lit<T>::zero, lit<T>::one,  lit<T>::zero, lit<T>::zero ); }
  
template< typename T > inline
mat4x2_t<T>     mat4x2_t<T>::row_vectors( vec4_t<T> const& row0,
                                          vec4_t<T> const& row1 )
{ return mat4x2_t( row0[0], row0[1], row0[2], row0[3],
                   row1[0], row1[1], row1[2], row1[3] ); }
  
template< typename T > inline
bool    mat4x2_t<T>::operator==( mat4x2_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs(lhs_c[0] - rhs_c[0]) < lit<T>::delta
           and std::abs(lhs_c[1] - rhs_c[1]) < lit<T>::delta
           and std::abs(lhs_c[2] - rhs_c[2]) < lit<T>::delta
           and std::abs(lhs_c[3] - rhs_c[3]) < lit<T>::delta
           and std::abs(lhs_c[4] - rhs_c[4]) < lit<T>::delta
           and std::abs(lhs_c[5] - rhs_c[5]) < lit<T>::delta
           and std::abs(lhs_c[6] - rhs_c[6]) < lit<T>::delta
           and std::abs(lhs_c[7] - rhs_c[7]) < lit<T>::delta;
}  


template< typename T > inline
bool    mat4x2_t<T>::operator<( mat4x2_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool less = true;
    
    if ( (*this) != rhs ) {
        less =     lhs_c[0] < rhs_c[0]
               and lhs_c[1] < rhs_c[1]
               and lhs_c[2] < rhs_c[2]
               and lhs_c[3] < rhs_c[3]
               and lhs_c[4] < rhs_c[4]
               and lhs_c[5] < rhs_c[5]
               and lhs_c[6] < rhs_c[6]
               and lhs_c[7] < rhs_c[7];
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat4x2_t<T>::operator>( mat4x2_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool greater = true;
    
    if ( (*this) != rhs ) {
        greater =     lhs_c[0] > rhs_c[0]
                  and lhs_c[1] > rhs_c[1]
                  and lhs_c[2] > rhs_c[2]
                  and lhs_c[3] > rhs_c[3]
                  and lhs_c[4] > rhs_c[4]
                  and lhs_c[5] > rhs_c[5]
                  and lhs_c[6] > rhs_c[6]
                  and lhs_c[7] > rhs_c[7];
    } else {
        greater = false;
    }

    return greater;
}

template< typename T > inline
bool    mat4x2_t<T>::operator<=( mat4x2_t<T> const& rhs ) const
{
    bool less = true;
    
    if ( not ((*this) > rhs) ) {
        less = true;
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat4x2_t<T>::operator>=( mat4x2_t<T> const& rhs ) const
{
    bool greater = true;
    
    if ( not ((*this) < rhs) ) {
        greater = true;
    } else {
        greater = false;
    }

    return greater;
}

template< typename T > inline
bool    mat4x2_t<T>::operator!=( mat4x2_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs( lhs_c[0] - rhs_c[0] ) >= lit<T>::delta
            or std::abs( lhs_c[1] - rhs_c[1] ) >= lit<T>::delta
            or std::abs( lhs_c[2] - rhs_c[2] ) >= lit<T>::delta
            or std::abs( lhs_c[3] - rhs_c[3] ) >= lit<T>::delta
            or std::abs( lhs_c[4] - rhs_c[4] ) >= lit<T>::delta
            or std::abs( lhs_c[5] - rhs_c[5] ) >= lit<T>::delta
            or std::abs( lhs_c[6] - rhs_c[6] ) >= lit<T>::delta
            or std::abs( lhs_c[7] - rhs_c[7] ) >= lit<T>::delta;
}
  
  template< typename T > inline
mat4x2_t<T>     mat4x2_t<T>::operator+( mat4x2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] + rhs_c[0];
    T e01 = lhs_c[1] + rhs_c[1];
    T e10 = lhs_c[2] + rhs_c[2];
    T e11 = lhs_c[3] + rhs_c[3];
    T e20 = lhs_c[4] + rhs_c[4];
    T e21 = lhs_c[5] + rhs_c[5];
    T e30 = lhs_c[6] + rhs_c[6];
    T e31 = lhs_c[7] + rhs_c[7];
    
    return mat4x2_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31 );
}

template< typename T > inline
mat4x2_t<T>     mat4x2_t<T>::operator-() const
{
    T const* lhs_c = this->data.c;
    
    T e00 = -lhs_c[0];
    T e01 = -lhs_c[1];
    T e10 = -lhs_c[2];
    T e11 = -lhs_c[3];
    T e20 = -lhs_c[4];
    T e21 = -lhs_c[5];
    T e30 = -lhs_c[6];
    T e31 = -lhs_c[7];
    
    return mat4x2_t( e00, e10, e20, e30,
                     e01, e11, e21, e31 );
}

template< typename T > inline
mat4x2_t<T>     mat4x2_t<T>::operator-( mat4x2_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] - rhs_c[0];
    T e01 = lhs_c[1] - rhs_c[1];
    T e10 = lhs_c[2] - rhs_c[2];
    T e11 = lhs_c[3] - rhs_c[3];
    T e20 = lhs_c[4] - rhs_c[4];
    T e21 = lhs_c[5] - rhs_c[5];
    T e30 = lhs_c[6] - rhs_c[6];
    T e31 = lhs_c[7] - rhs_c[7];
    
    return mat4x2_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31 );
}  

template< typename T > inline
mat2_t<T>     mat4x2_t<T>::operator*( mat2x4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1] + lhs_c[4] * rhs_c[2] + lhs_c[6] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[5] * rhs_c[2] + lhs_c[7] * rhs_c[3];
    T e10 = lhs_c[0] * rhs_c[4] + lhs_c[2] * rhs_c[5] + lhs_c[4] * rhs_c[6] + lhs_c[6] * rhs_c[7];
    T e11 = lhs_c[1] * rhs_c[4] + lhs_c[3] * rhs_c[5] + lhs_c[5] * rhs_c[6] + lhs_c[7] * rhs_c[7];
    
    return mat2_t<T>( e00, e10,
                      e01, e11 );
}

template< typename T > inline
mat3x2_t<T>     mat4x2_t<T>::operator*( mat3x4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1] + lhs_c[4] * rhs_c[2] + lhs_c[6] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[5] * rhs_c[2] + lhs_c[7] * rhs_c[3];
    T e10 = lhs_c[0] * rhs_c[4] + lhs_c[2] * rhs_c[5] + lhs_c[4] * rhs_c[6] + lhs_c[6] * rhs_c[7];
    T e11 = lhs_c[1] * rhs_c[4] + lhs_c[3] * rhs_c[5] + lhs_c[5] * rhs_c[6] + lhs_c[7] * rhs_c[7];
    T e20 = lhs_c[0] * rhs_c[8] + lhs_c[2] * rhs_c[9] + lhs_c[4] * rhs_c[10] + lhs_c[6] * rhs_c[11];
    T e21 = lhs_c[1] * rhs_c[8] + lhs_c[3] * rhs_c[9] + lhs_c[5] * rhs_c[10] + lhs_c[7] * rhs_c[11];
    
    return mat3x2_t<T>( e00, e10, e20,
                        e01, e11, e21 );
}

template< typename T > inline
mat4x2_t<T>     mat4x2_t<T>::operator*( mat4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[2] * rhs_c[1] + lhs_c[4] * rhs_c[2] + lhs_c[6] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[5] * rhs_c[2] + lhs_c[7] * rhs_c[3];
    T e10 = lhs_c[0] * rhs_c[4] + lhs_c[2] * rhs_c[5] + lhs_c[4] * rhs_c[6] + lhs_c[6] * rhs_c[7];
    T e11 = lhs_c[1] * rhs_c[4] + lhs_c[3] * rhs_c[5] + lhs_c[5] * rhs_c[6] + lhs_c[7] * rhs_c[7];
    T e20 = lhs_c[0] * rhs_c[8] + lhs_c[2] * rhs_c[9] + lhs_c[4] * rhs_c[10] + lhs_c[6] * rhs_c[11];
    T e21 = lhs_c[1] * rhs_c[8] + lhs_c[3] * rhs_c[9] + lhs_c[5] * rhs_c[10] + lhs_c[7] * rhs_c[11];
    T e30 = lhs_c[0] * rhs_c[12] + lhs_c[2] * rhs_c[13] + lhs_c[4] * rhs_c[14] + lhs_c[6] * rhs_c[15];
    T e31 = lhs_c[1] * rhs_c[12] + lhs_c[3] * rhs_c[13] + lhs_c[5] * rhs_c[14] + lhs_c[7] * rhs_c[15];
    
    return mat4x2_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31 );
}


template< typename T > inline
vec2_t<T>     mat4x2_t<T>::operator*( vec4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T x0 = lhs_c[0] * rhs[0] + lhs_c[2] * rhs[1] + lhs_c[4] * rhs[2] + lhs_c[6] * rhs[3];
    T x1 = lhs_c[1] * rhs[0] + lhs_c[3] * rhs[1] + lhs_c[5] * rhs[2] + lhs_c[7] * rhs[3];
    
    return vec2_t<T>( x0, x1 );
}

template< typename T > inline
vec4_t<T>     operator*( vec2_t<T> const& lhs,
                         mat4x2_t<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    
    T x0 = rhs_c[0] * lhs[0] + rhs_c[1] * lhs[1];
    T x1 = rhs_c[2] * lhs[0] + rhs_c[3] * lhs[1];
    T x2 = rhs_c[4] * lhs[0] + rhs_c[5] * lhs[1];
    T x3 = rhs_c[6] * lhs[0] + rhs_c[7] * lhs[1];
    
    return vec4_t<T>( x0, x1, x2, x3 );
}

template< typename T >
mat4x2_t<T>     mat4x2_t<T>::operator*( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] * rhs;
    T e01 = lhs_c[1] * rhs;
    T e10 = lhs_c[2] * rhs;
    T e11 = lhs_c[3] * rhs;
    T e20 = lhs_c[4] * rhs;
    T e21 = lhs_c[5] * rhs;
    T e30 = lhs_c[6] * rhs;
    T e31 = lhs_c[7] * rhs;
    
    return mat4x2_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31 );
}

template< typename D >
mat4x2_t<D>     operator*( D lhs, mat4x2_t<D> const& rhs )
{
    D const* rhs_c = rhs.data.c;
    
    D e00 = rhs_c[0] * lhs;
    D e01 = rhs_c[1] * lhs;
    D e10 = rhs_c[2] * lhs;
    D e11 = rhs_c[3] * lhs;
    D e20 = rhs_c[4] * lhs;
    D e21 = rhs_c[5] * lhs;
    D e30 = rhs_c[6] * lhs;
    D e31 = rhs_c[7] * lhs;
    
    return mat4x2_t<D>( e00, e10, e20, e30,
                        e01, e11, e21, e31 );
}

template< typename T >
mat4x2_t<T>     mat4x2_t<T>::operator/( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] / rhs;
    T e01 = lhs_c[1] / rhs;
    T e10 = lhs_c[2] / rhs;
    T e11 = lhs_c[3] / rhs;
    T e20 = lhs_c[4] / rhs;
    T e21 = lhs_c[5] / rhs;
    T e30 = lhs_c[6] / rhs;
    T e31 = lhs_c[7] / rhs;
    
    return mat4x2_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31 );
}

template< typename T > inline
mat4x2_t<T>&    mat4x2_t<T>::operator=( mat4x2_t<T> const& rhs )
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
    return *this;
}

template< typename T > inline
col2<T>     mat4x2_t<T>::operator[]( size_t i )
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat4x2_t out of range" );
    }
    
    return col2<T>( this->data.c + (2*i), true );
}

template< typename T > inline
col2<T>     mat4x2_t<T>::operator[]( size_t i ) const
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat4x2_t out of range" );
    }
    
    T* col_cpy = new T[2];
    
    col_cpy[0] = this-data->c[ 2 * i ];
    col_cpy[1] = this-data->c[ 2 * i + 1 ];
    
    return col2<T>( col_cpy, false );
}
  
template< typename T > inline
T&     mat4x2_t<T>::operator()( size_t col,
                                size_t row )
{
    if ( col > 3 or row > 1 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat4x2_t used out of bounds index");
    }
    
    return this->data.c[col * 2 + row];
}

template< typename T > inline
T      mat4x2_t<T>::operator()( size_t col,
                                size_t row ) const
{
    if ( col > 3 or row > 1 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat4x2_t used out of bounds index");
    }
    
    return this->data.c[col * 2 + row];
}

template< typename T > inline
col2<T>    mat4x2_t<T>::column( size_t col )
{ return (*this)[col]; }

template< typename T > inline
col2<T>     mat4x2_t<T>::column( size_t col ) const
{ return (*this)[col]; }

template< typename T > inline
mat4x2_t<T>&    mat4x2_t<T>::columns( vec2_t<T> const& col0,
                                      vec2_t<T> const& col1,
                                      vec2_t<T> const& col2,
                                      vec2_t<T> const& col3 )
{
    T* cm = this->data.c;
    
    cm[0] = col0[0];
    cm[1] = col0[1];
    cm[2] = col1[0];
    cm[3] = col1[1];
    cm[4] = col2[0];
    cm[5] = col2[1];
    cm[6] = col3[0];
    cm[7] = col3[1];
    
    return *this;
}

template< typename T >
mat4x2_t<T>& mat4x2_t<T>::fill( T val )
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
    return *this;
}

template< typename T > inline
row4<T>    mat4x2_t<T>::row( size_t row )
{
    if ( row > 1 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat4x2_t out of range" );
    }
    
    return row4<T>( this->data.c + row,
                    this->data.c + 2 + row,
                    this->data.c + 4 + row,
                    this->data.c + 6 + row,
                    true );
}

template< typename T > inline
row4<T>     mat4x2_t<T>::row( size_t row ) const
{
    if ( row > 1 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat4x2_t out of range" );
    }
    
    return row3<T>( this->data.c[row],
                    this->data.c[2 + row],
                    this->data.c[4 + row],
                    this->data.c[6 + row] );
}

template< typename T > inline
mat4x2_t<T>& mat4x2_t<T>::rows( vec4_t<T> const& row0,
                                vec4_t<T> const& row1 )
{
    T* cm = this->data.c;
    
    cm[0] = row0[0];
    cm[2] = row0[1];
    cm[4] = row0[2];
    cm[6] = row0[3];
    cm[1] = row1[0];
    cm[3] = row1[1];
    cm[5] = row1[2];
    cm[7] = row1[3];
    
    return *this;
}

template< typename T > inline
raw_map const   mat4x2_t<T>::to_map() const
{
    return map_bytes( sizeof(T) * 8, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat4x2_t<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " " << src(2,0) << " " << src(3,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " " << src(2,1) << " " << src(3,1) << " ]" << std::endl;
    return stream;
}



// -------------- Matrix 3x4 -----------------

template< typename T > inline
mat3x4_t<T>::mat3x4_t()
{ T* c = this->data.c;
  c[0] = lit<T>::zero;   c[4] = lit<T>::zero;   c[8] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[5] = lit<T>::zero;   c[9] = lit<T>::zero;
  c[2] = lit<T>::zero;   c[6] = lit<T>::zero;   c[10] = lit<T>::zero;
  c[3] = lit<T>::zero;   c[7] = lit<T>::zero;   c[11] = lit<T>::zero; }
  
template< typename T > inline
mat3x4_t<T>::mat3x4_t( mat3x4_t<T> const& copy )
{ T* c = this->data.c;
  c[0] = copy.data.c[0];
  c[1] = copy.data.c[1];
  c[2] = copy.data.c[2];
  c[3] = copy.data.c[3];
  c[4] = copy.data.c[4];
  c[5] = copy.data.c[5];
  c[6] = copy.data.c[6];
  c[7] = copy.data.c[7];
  c[8] = copy.data.c[8];
  c[9] = copy.data.c[9];
  c[10] = copy.data.c[10];
  c[11] = copy.data.c[11];
}

template< typename T >
mat3x4_t<T>::mat3x4_t( T e00, T e10, T e20,
                       T e01, T e11, T e21,
                       T e02, T e12, T e22,
                       T e03, T e13, T e23 )
{ T* c = this->data.c;
  c[0] = e00;   c[4] = e10;   c[8]  = e20;
  c[1] = e01;   c[5] = e11;   c[9]  = e21;
  c[2] = e02;   c[6] = e12;   c[10] = e22;
  c[3] = e03;   c[7] = e13;   c[11] = e23; }
  
template< typename T >
mat3x4_t<T>::mat3x4_t( T fill )
{ T* c = this->data.c;
  c[0] = fill;   c[4] = fill;   c[8]  = fill;
  c[1] = fill;   c[5] = fill;   c[9]  = fill;
  c[2] = fill;   c[6] = fill;   c[10] = fill;
  c[3] = fill;   c[7] = fill;   c[11] = fill; }
  
template< typename T > inline
mat3x4_t<T>::mat3x4_t( vec4_t<T> const& col0,
                       vec4_t<T> const& col1,
                       vec4_t<T> const& col2 )
{ T* c = this->data.c;
  c[0] = col0[0];   c[4] = col1[0];   c[8]  = col2[0];
  c[1] = col0[1];   c[5] = col1[1];   c[9]  = col2[1];
  c[2] = col0[2];   c[6] = col1[2];   c[10] = col2[2];
  c[3] = col0[3];   c[7] = col1[3];   c[11] = col2[3]; }
  
template< typename T >
mat3x4_t<T>     mat3x4_t<T>::upper_identity()
{ return mat3x4_t<T>( lit<T>::one,  lit<T>::zero, lit<T>::zero,
                      lit<T>::zero, lit<T>::one,  lit<T>::zero,
                      lit<T>::zero, lit<T>::zero, lit<T>::one,
                      lit<T>::zero, lit<T>::zero, lit<T>::zero ); }
                      
template< typename T > inline
mat3x4_t<T>     mat3x4_t<T>::row_vectors( vec3_t<T> const& row0,
                                          vec3_t<T> const& row1,
                                          vec3_t<T> const& row2,
                                          vec3_t<T> const& row3 )
{ return mat3x4_t( row0[0], row0[1], row0[2],
                   row1[0], row1[1], row1[2],
                   row2[0], row2[1], row2[2],
                   row3[0], row3[1], row3[2] ); }

template< typename T > inline
bool    mat3x4_t<T>::operator==( mat3x4_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs(lhs_c[0] - rhs_c[0]) < lit<T>::delta
           and std::abs(lhs_c[1] - rhs_c[1]) < lit<T>::delta
           and std::abs(lhs_c[2] - rhs_c[2]) < lit<T>::delta
           and std::abs(lhs_c[3] - rhs_c[3]) < lit<T>::delta
           and std::abs(lhs_c[4] - rhs_c[4]) < lit<T>::delta
           and std::abs(lhs_c[5] - rhs_c[5]) < lit<T>::delta
           and std::abs(lhs_c[6] - rhs_c[6]) < lit<T>::delta
           and std::abs(lhs_c[7] - rhs_c[7]) < lit<T>::delta
           and std::abs(lhs_c[8] - rhs_c[8]) < lit<T>::delta
           and std::abs(lhs_c[9] - rhs_c[9]) < lit<T>::delta
           and std::abs(lhs_c[10] - rhs_c[10]) < lit<T>::delta
           and std::abs(lhs_c[11] - rhs_c[11]) < lit<T>::delta;
}

template< typename T > inline
bool    mat3x4_t<T>::operator<( mat3x4_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool less = true;
    
    if ( (*this) != rhs ) {
        less =     lhs_c[0] < rhs_c[0]
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
               and lhs_c[11] < rhs_c[11];
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat3x4_t<T>::operator>( mat3x4_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool greater = true;
    
    if ( (*this) != rhs ) {
        greater =     lhs_c[0] > rhs_c[0]
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
                  and lhs_c[11] > rhs_c[11];
    } else {
        greater = false;
    }

    return greater;
}


template< typename T > inline
bool    mat3x4_t<T>::operator<=( mat3x4_t<T> const& rhs ) const
{
    bool less = true;
    
    if ( not ((*this) > rhs) ) {
        less = true;
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat3x4_t<T>::operator>=( mat3x4_t<T> const& rhs ) const
{
    bool greater = true;
    
    if ( not ((*this) < rhs) ) {
        greater = true;
    } else {
        greater = false;
    }

    return greater;
}


template< typename T > inline
bool    mat3x4_t<T>::operator!=( mat3x4_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs( lhs_c[0] - rhs_c[0] ) >= lit<T>::delta
            or std::abs( lhs_c[1] - rhs_c[1] ) >= lit<T>::delta
            or std::abs( lhs_c[2] - rhs_c[2] ) >= lit<T>::delta
            or std::abs( lhs_c[3] - rhs_c[3] ) >= lit<T>::delta
            or std::abs( lhs_c[4] - rhs_c[4] ) >= lit<T>::delta
            or std::abs( lhs_c[5] - rhs_c[5] ) >= lit<T>::delta
            or std::abs( lhs_c[6] - rhs_c[6] ) >= lit<T>::delta
            or std::abs( lhs_c[7] - rhs_c[7] ) >= lit<T>::delta
            or std::abs( lhs_c[8] - rhs_c[8] ) >= lit<T>::delta
            or std::abs( lhs_c[9] - rhs_c[9] ) >= lit<T>::delta
            or std::abs( lhs_c[10] - rhs_c[10] ) >= lit<T>::delta
            or std::abs( lhs_c[11] - rhs_c[11] ) >= lit<T>::delta;
}

template< typename T > inline
mat3x4_t<T>     mat3x4_t<T>::operator+( mat3x4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] + rhs_c[0];
    T e01 = lhs_c[1] + rhs_c[1];
    T e02 = lhs_c[2] + rhs_c[2];
    T e03 = lhs_c[3] + rhs_c[3];
    
    T e10 = lhs_c[4] + rhs_c[4];
    T e11 = lhs_c[5] + rhs_c[5];
    T e12 = lhs_c[6] + rhs_c[6];
    T e13 = lhs_c[7] + rhs_c[7];
    
    T e20 = lhs_c[8] + rhs_c[8];
    T e21 = lhs_c[9] + rhs_c[9];
    T e22 = lhs_c[10] + rhs_c[10];
    T e23 = lhs_c[11] + rhs_c[11];
    
    return mat3x4_t<T>( e00, e10, e20,
                        e01, e11, e21,
                        e02, e12, e22,
                        e03, e13, e23 );
}

template< typename T > inline
mat3x4_t<T>     mat3x4_t<T>::operator-() const
{
    T const* lhs_c = this->data.c;
    
    T e00 = -lhs_c[0];
    T e01 = -lhs_c[1];
    T e02 = -lhs_c[2];
    T e03 = -lhs_c[3];
    
    T e10 = -lhs_c[4];
    T e11 = -lhs_c[5];
    T e12 = -lhs_c[6];
    T e13 = -lhs_c[7];
    
    T e20 = -lhs_c[8];
    T e21 = -lhs_c[9];
    T e22 = -lhs_c[10];
    T e23 = -lhs_c[11];
    
    return mat3x4_t( e00, e10, e20,
                     e01, e11, e21,
                     e02, e12, e22,
                     e03, e13, e23 );
}

template< typename T > inline
mat3x4_t<T>     mat3x4_t<T>::operator-( mat3x4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] - rhs_c[0];
    T e01 = lhs_c[1] - rhs_c[1];
    T e02 = lhs_c[2] - rhs_c[2];
    T e03 = lhs_c[3] - rhs_c[3];
    
    T e10 = lhs_c[4] - rhs_c[4];
    T e11 = lhs_c[5] - rhs_c[5];
    T e12 = lhs_c[6] - rhs_c[6];
    T e13 = lhs_c[7] - rhs_c[7];
    
    T e20 = lhs_c[8] - rhs_c[8];
    T e21 = lhs_c[9] - rhs_c[9];
    T e22 = lhs_c[10] - rhs_c[10];
    T e23 = lhs_c[11] - rhs_c[11];
    
    return mat3x4_t<T>( e00, e10, e20,
                        e01, e11, e21,
                        e02, e12, e22,
                        e03, e13, e23 );
}

template< typename T > inline
mat4_t<T>     mat3x4_t<T>::operator*( mat4x3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[8] * rhs_c[2];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[9] * rhs_c[2];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[6] * rhs_c[1] + lhs_c[10] * rhs_c[2];
    T e03 = lhs_c[3] * rhs_c[0] + lhs_c[7] * rhs_c[1] + lhs_c[11] * rhs_c[2];
    
    T e10 = lhs_c[0] * rhs_c[3] + lhs_c[4] * rhs_c[4] + lhs_c[8] * rhs_c[5];
    T e11 = lhs_c[1] * rhs_c[3] + lhs_c[5] * rhs_c[4] + lhs_c[9] * rhs_c[5];
    T e12 = lhs_c[2] * rhs_c[3] + lhs_c[6] * rhs_c[4] + lhs_c[10] * rhs_c[5];
    T e13 = lhs_c[3] * rhs_c[3] + lhs_c[7] * rhs_c[4] + lhs_c[11] * rhs_c[5];
    
    T e20 = lhs_c[0] * rhs_c[6] + lhs_c[4] * rhs_c[7] + lhs_c[8] * rhs_c[8];
    T e21 = lhs_c[1] * rhs_c[6] + lhs_c[5] * rhs_c[7] + lhs_c[9] * rhs_c[8];
    T e22 = lhs_c[2] * rhs_c[6] + lhs_c[6] * rhs_c[7] + lhs_c[10] * rhs_c[8];
    T e23 = lhs_c[3] * rhs_c[6] + lhs_c[7] * rhs_c[7] + lhs_c[11] * rhs_c[8];
    
    T e30 = lhs_c[0] * rhs_c[9] + lhs_c[4] * rhs_c[10] + lhs_c[8] * rhs_c[11];
    T e31 = lhs_c[1] * rhs_c[9] + lhs_c[5] * rhs_c[10] + lhs_c[9] * rhs_c[11];
    T e32 = lhs_c[2] * rhs_c[9] + lhs_c[6] * rhs_c[10] + lhs_c[10] * rhs_c[11];
    T e33 = lhs_c[3] * rhs_c[9] + lhs_c[7] * rhs_c[10] + lhs_c[11] * rhs_c[11];
    
    return mat4_t<T>( e00, e10, e20, e30,
                      e01, e11, e21, e31,
                      e02, e12, e22, e32,
                      e03, e13, e23, e33 );
}

template< typename T > inline
mat2x4_t<T>     mat3x4_t<T>::operator*( mat2x3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[8] * rhs_c[2];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[9] * rhs_c[2];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[6] * rhs_c[1] + lhs_c[10] * rhs_c[2];
    T e03 = lhs_c[3] * rhs_c[0] + lhs_c[7] * rhs_c[1] + lhs_c[11] * rhs_c[2];
    
    T e10 = lhs_c[0] * rhs_c[3] + lhs_c[4] * rhs_c[4] + lhs_c[8] * rhs_c[5];
    T e11 = lhs_c[1] * rhs_c[3] + lhs_c[5] * rhs_c[4] + lhs_c[9] * rhs_c[5];
    T e12 = lhs_c[2] * rhs_c[3] + lhs_c[6] * rhs_c[4] + lhs_c[10] * rhs_c[5];
    T e13 = lhs_c[3] * rhs_c[3] + lhs_c[7] * rhs_c[4] + lhs_c[11] * rhs_c[5];
    
    return mat2x4_t<T>( e00, e10,
                        e01, e11,
                        e02, e12,
                        e03, e13 );
}

template< typename T > inline
mat3x4_t<T>     mat3x4_t<T>::operator*( mat3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[8] * rhs_c[2];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[9] * rhs_c[2];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[6] * rhs_c[1] + lhs_c[10] * rhs_c[2];
    T e03 = lhs_c[3] * rhs_c[0] + lhs_c[7] * rhs_c[1] + lhs_c[11] * rhs_c[2];
    
    T e10 = lhs_c[0] * rhs_c[3] + lhs_c[4] * rhs_c[4] + lhs_c[8] * rhs_c[5];
    T e11 = lhs_c[1] * rhs_c[3] + lhs_c[5] * rhs_c[4] + lhs_c[9] * rhs_c[5];
    T e12 = lhs_c[2] * rhs_c[3] + lhs_c[6] * rhs_c[4] + lhs_c[10] * rhs_c[5];
    T e13 = lhs_c[3] * rhs_c[3] + lhs_c[7] * rhs_c[4] + lhs_c[11] * rhs_c[5];
    
    T e20 = lhs_c[0] * rhs_c[6] + lhs_c[4] * rhs_c[7] + lhs_c[8] * rhs_c[8];
    T e21 = lhs_c[1] * rhs_c[6] + lhs_c[5] * rhs_c[7] + lhs_c[9] * rhs_c[8];
    T e22 = lhs_c[2] * rhs_c[6] + lhs_c[6] * rhs_c[7] + lhs_c[10] * rhs_c[8];
    T e23 = lhs_c[3] * rhs_c[6] + lhs_c[7] * rhs_c[7] + lhs_c[11] * rhs_c[8];
    
    return mat3x4_t<T>( e00, e10, e20,
                        e01, e11, e21,
                        e02, e12, e22,
                        e03, e13, e23 );
}

template< typename T > inline
vec4_t<T>     mat3x4_t<T>::operator*( vec3_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T x0 = lhs_c[0] * rhs[0] + lhs_c[4] * rhs[1] + lhs_c[8] * rhs[2];
    T x1 = lhs_c[1] * rhs[0] + lhs_c[5] * rhs[1] + lhs_c[9] * rhs[2];
    T x2 = lhs_c[2] * rhs[0] + lhs_c[6] * rhs[1] + lhs_c[10] * rhs[2];
    T x3 = lhs_c[3] * rhs[0] + lhs_c[7] * rhs[1] + lhs_c[11] * rhs[2];
    
    return vec4_t<T>( x0, x1, x2, x3 );
}

template< typename T > inline
vec3_t<T>     operator*( vec4_t<T> const& lhs,
                         mat3x4_t<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    
    T x0 = rhs_c[0] * lhs[0] + rhs_c[1] * lhs[1] + rhs_c[2] * lhs[2] + rhs_c[3] * lhs[3];
    T x1 = rhs_c[4] * lhs[0] + rhs_c[5] * lhs[1] + rhs_c[6] * lhs[2] + rhs_c[7] * lhs[3];
    T x2 = rhs_c[8] * lhs[0] + rhs_c[9] * lhs[1] + rhs_c[10] * lhs[2] + rhs_c[11] * lhs[3];
    
    return vec3_t<T>( x0, x1, x2 );
}

template< typename T >
mat3x4_t<T>     mat3x4_t<T>::operator*( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] * rhs;
    T e01 = lhs_c[1] * rhs;
    T e02 = lhs_c[2] * rhs;
    T e03 = lhs_c[3] * rhs;
    
    T e10 = lhs_c[4] * rhs;
    T e11 = lhs_c[5] * rhs;
    T e12 = lhs_c[6] * rhs;
    T e13 = lhs_c[7] * rhs;
    
    T e20 = lhs_c[8] * rhs;
    T e21 = lhs_c[9] * rhs;
    T e22 = lhs_c[10] * rhs;
    T e23 = lhs_c[11] * rhs;
    
    return mat3x4_t( e00, e10, e20,
                     e01, e11, e21,
                     e02, e12, e22,
                     e03, e13, e23 );
}

template< typename D >
mat3x4_t<D>     operator*( D lhs, mat3x4_t<D> const& rhs )
{
    D const* rhs_c = rhs.data.c;
    
    D e00 = rhs_c[0] * lhs;
    D e01 = rhs_c[1] * lhs;
    D e02 = rhs_c[2] * lhs;
    D e03 = rhs_c[3] * lhs;
    
    D e10 = rhs_c[4] * lhs;
    D e11 = rhs_c[5] * lhs;
    D e12 = rhs_c[6] * lhs;
    D e13 = rhs_c[7] * lhs;
    
    D e20 = rhs_c[8] * lhs;
    D e21 = rhs_c[9] * lhs;
    D e22 = rhs_c[10] * lhs;
    D e23 = rhs_c[11] * lhs;
    
    return mat3x4_t<D>( e00, e10, e20,
                        e01, e11, e21,
                        e02, e12, e22,
                        e03, e13, e23 );
}

template< typename T >
mat3x4_t<T>     mat3x4_t<T>::operator/( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] / rhs;
    T e01 = lhs_c[1] / rhs;
    T e02 = lhs_c[2] / rhs;
    T e03 = lhs_c[3] / rhs;
    
    T e10 = lhs_c[4] / rhs;
    T e11 = lhs_c[5] / rhs;
    T e12 = lhs_c[6] / rhs;
    T e13 = lhs_c[7] / rhs;
    
    T e20 = lhs_c[8] / rhs;
    T e21 = lhs_c[9] / rhs;
    T e22 = lhs_c[10] / rhs;
    T e23 = lhs_c[11] / rhs;
    
    return mat3x4_t<T>( e00, e10, e20,
                        e01, e11, e21,
                        e02, e12, e22,
                        e03, e13, e23 );
}


template< typename T > inline
mat3x4_t<T>&    mat3x4_t<T>::operator=( mat3x4_t<T> const& rhs )
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
    return *this;
}


template< typename T > inline
col4<T>     mat3x4_t<T>::operator[]( size_t i )
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat3x4_t out of range" );
    }
    
    return col4<T>( this->data.c + (4*i), true );
}

template< typename T > inline
col4<T>     mat3x4_t<T>::operator[]( size_t i ) const
{
    if ( i > 2 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat3x4_t out of range" );
    }
    
    T* col_cpy = new T[4];
    
    col_cpy[0] = this-data->c[ 4 * i ];
    col_cpy[1] = this-data->c[ 4 * i + 1 ];
    col_cpy[2] = this-data->c[ 4 * i + 2 ];
    col_cpy[3] = this-data->c[ 4 * i + 3 ];
    
    return col4<T>( col_cpy, false );
}


template< typename T > inline
T&     mat3x4_t<T>::operator()( size_t col,
                                size_t row )
{
    if ( col > 2 or row > 3 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat3x4_t used out of bounds index");
    }
    
    return this->data.c[col * 4 + row];
}

template< typename T > inline
T      mat3x4_t<T>::operator()( size_t col,
                                size_t row ) const
{
    if ( col > 2 or row > 3 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat3x4_t used out of bounds index");
    }
    
    return this->data.c[col * 4 + row];
}


template< typename T > inline
col4<T>    mat3x4_t<T>::column( size_t col )
{ return (*this)[col]; }

template< typename T > inline
col4<T>     mat3x4_t<T>::column( size_t col ) const
{ return (*this)[col]; }

template< typename T > inline
mat3x4_t<T>&    mat3x4_t<T>::columns( vec4_t<T> const& col0,
                                      vec4_t<T> const& col1,
                                      vec4_t<T> const& col2 )
{
    T* cm = this->data.c;
    
    cm[0] = col0[0];
    cm[1] = col0[1];
    cm[2] = col0[2];
    cm[3] = col0[3];
    
    cm[4] = col1[0];
    cm[5] = col1[1];
    cm[6] = col1[2];
    cm[7] = col1[3];
    
    cm[8] = col2[0];
    cm[9] = col2[1];
    cm[10] = col2[2];
    cm[11] = col2[3];
    
    return *this;
}


template< typename T >
mat3x4_t<T>& mat3x4_t<T>::fill( T val )
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
    c[9] = val;
    c[10] = val;
    c[11] = val;
    return *this;
}


template< typename T > inline
row3<T>    mat3x4_t<T>::row( size_t row )
{
    if ( row > 3 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat3x4_t out of range" );
    }
    
    return row3<T>( this->data.c + row,
                    this->data.c + 4 + row,
                    this->data.c + 8 + row,
                    true );
}

template< typename T > inline
row3<T>     mat3x4_t<T>::row( size_t row ) const
{
    if ( row > 3 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat3x4_t out of range" );
    }
    
    return row3<T>( this->data.c[row],
                    this->data.c[4 + row],
                    this->data.c[4 + row] );
}


template< typename T > inline
mat3x4_t<T>& mat3x4_t<T>::rows( vec3_t<T> const& row0,
                                vec3_t<T> const& row1,
                                vec3_t<T> const& row2,
                                vec3_t<T> const& row3 )
{
    T* cm = this->data.c;
    
    cm[0] = row0[0];
    cm[4] = row0[1];
    cm[8] = row0[2];
    
    cm[1] = row1[0];
    cm[5] = row1[1];
    cm[9] = row1[2];
    
    cm[2] = row2[0];
    cm[6] = row2[1];
    cm[10] = row2[2];
    
    cm[3] = row3[0];
    cm[7] = row3[1];
    cm[11] = row3[2];
    
    return *this;
}


template< typename T > inline
raw_map const   mat3x4_t<T>::to_map() const
{
    return map_bytes( sizeof(T) * 12, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat3x4_t<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " " << src(2,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " " << src(2,1) << " ]" << '\n';
    stream << "[ " << src(0,2) << " " << src(1,2) << " " << src(2,2) << " ]" << '\n';
    stream << "[ " << src(0,3) << " " << src(1,3) << " " << src(2,3) << " ]" << std::endl;
    return stream;
}




// --------------- Matrix 4x3 --------------


template< typename T > inline
mat4x3_t<T>::mat4x3_t()
{ T* c = this->data.c;
  c[0] = lit<T>::zero;   c[3] = lit<T>::zero;   c[6] = lit<T>::zero;   c[9] = lit<T>::zero;
  c[1] = lit<T>::zero;   c[4] = lit<T>::zero;   c[7] = lit<T>::zero;   c[10] = lit<T>::zero;
  c[2] = lit<T>::zero;   c[5] = lit<T>::zero;   c[8] = lit<T>::zero;   c[11] = lit<T>::zero; }

template< typename T > inline
mat4x3_t<T>::mat4x3_t( mat4x3_t<T> const& copy )
{ T* c = this->data.c;
  c[0] = copy.data.c[0];
  c[1] = copy.data.c[1];
  c[2] = copy.data.c[2];
  c[3] = copy.data.c[3];
  c[4] = copy.data.c[4];
  c[5] = copy.data.c[5];
  c[6] = copy.data.c[6];
  c[7] = copy.data.c[7];
  c[8] = copy.data.c[8];
  c[9] = copy.data.c[9];
  c[10] = copy.data.c[10];
  c[11] = copy.data.c[11];
}
  
template< typename T >
mat4x3_t<T>::mat4x3_t( T e00, T e10, T e20, T e30,
                       T e01, T e11, T e21, T e31,
                       T e02, T e12, T e22, T e32 )
{ T* c = this->data.c;
  c[0] = e00;   c[3] = e10;   c[6] = e20;   c[9]  = e30;
  c[1] = e01;   c[4] = e11;   c[7] = e21;   c[10] = e31;
  c[2] = e02;   c[5] = e12;   c[8] = e22;   c[11] = e32; }

template< typename T >
mat4x3_t<T>::mat4x3_t( T fill )
{ T* c = this->data.c;
  c[0] = fill;   c[3] = fill;   c[6] = fill;   c[9] = fill;
  c[1] = fill;   c[4] = fill;   c[7] = fill;   c[10] = fill;
  c[2] = fill;   c[5] = fill;   c[8] = fill;   c[11] = fill; }


template< typename T > inline
mat4x3_t<T>::mat4x3_t( vec3_t<T> const& col0,
                       vec3_t<T> const& col1,
                       vec3_t<T> const& col2,
                       vec3_t<T> const& col3 )
{ T* c = this->data.c;
  c[0] = col0[0];   c[3] = col1[0];   c[6] = col2[0];   c[9]  = col3[0];
  c[1] = col0[1];   c[4] = col1[1];   c[7] = col2[1];   c[10] = col3[1];
  c[2] = col0[2];   c[5] = col1[2];   c[8] = col2[2];   c[11] = col3[2]; }

// Named Construction
template< typename T >
mat4x3_t<T>     mat4x3_t<T>::left_identity()
{ return mat4x3_t<T>( lit<T>::one,  lit<T>::zero, lit<T>::zero, lit<T>::zero,
                      lit<T>::zero, lit<T>::one, lit<T>::zero, lit<T>::zero,
                      lit<T>::zero, lit<T>::zero, lit<T>::one, lit<T>::zero ); }

template< typename T > inline
mat4x3_t<T>     mat4x3_t<T>::row_vectors( vec4_t<T> const& row0,
                                          vec4_t<T> const& row1,
                                          vec4_t<T> const& row2 )
{ return mat4x3_t( row0[0], row0[1], row0[2], row0[3],
                   row1[0], row1[1], row1[2], row1[3],
                   row2[0], row2[1], row2[2], row2[3] ); }

// Comparison
               
template< typename T > inline
bool    mat4x3_t<T>::operator==( mat4x3_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs(lhs_c[0] - rhs_c[0]) < lit<T>::delta
           and std::abs(lhs_c[1] - rhs_c[1]) < lit<T>::delta
           and std::abs(lhs_c[2] - rhs_c[2]) < lit<T>::delta
           and std::abs(lhs_c[3] - rhs_c[3]) < lit<T>::delta
           and std::abs(lhs_c[4] - rhs_c[4]) < lit<T>::delta
           and std::abs(lhs_c[5] - rhs_c[5]) < lit<T>::delta
           and std::abs(lhs_c[6] - rhs_c[6]) < lit<T>::delta
           and std::abs(lhs_c[7] - rhs_c[7]) < lit<T>::delta
           and std::abs(lhs_c[8] - rhs_c[8]) < lit<T>::delta
           and std::abs(lhs_c[9] - rhs_c[9]) < lit<T>::delta
           and std::abs(lhs_c[10] - rhs_c[10]) < lit<T>::delta
           and std::abs(lhs_c[11] - rhs_c[11]) < lit<T>::delta;
}

template< typename T > inline
bool    mat4x3_t<T>::operator<( mat4x3_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool less = true;
    
    if ( (*this) != rhs ) {
        less =     lhs_c[0] < rhs_c[0]
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
               and lhs_c[11] < rhs_c[11];
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat4x3_t<T>::operator>( mat4x3_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    bool greater = true;
    
    if ( (*this) != rhs ) {
        greater =     lhs_c[0] > rhs_c[0]
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
                  and lhs_c[11] > rhs_c[11];
    } else {
        greater = false;
    }

    return greater;
}

template< typename T > inline
bool    mat4x3_t<T>::operator<=( mat4x3_t<T> const& rhs ) const
{
    bool less = true;
    
    if ( not ((*this) > rhs) ) {
        less = true;
    } else {
        less = false;
    }

    return less;
}

template< typename T > inline
bool    mat4x3_t<T>::operator>=( mat4x3_t<T> const& rhs ) const
{
    bool greater = true;
    
    if ( not ((*this) < rhs) ) {
        greater = true;
    } else {
        greater = false;
    }

    return greater;
}

template< typename T > inline
bool    mat4x3_t<T>::operator!=( mat4x3_t<T> const& rhs ) const
{
    T const* rhs_c = rhs.data.c;
    T const* lhs_c = this->data.c;
    return     std::abs( lhs_c[0] - rhs_c[0] ) >= lit<T>::delta
            or std::abs( lhs_c[1] - rhs_c[1] ) >= lit<T>::delta
            or std::abs( lhs_c[2] - rhs_c[2] ) >= lit<T>::delta
            or std::abs( lhs_c[3] - rhs_c[3] ) >= lit<T>::delta
            or std::abs( lhs_c[4] - rhs_c[4] ) >= lit<T>::delta
            or std::abs( lhs_c[5] - rhs_c[5] ) >= lit<T>::delta
            or std::abs( lhs_c[6] - rhs_c[6] ) >= lit<T>::delta
            or std::abs( lhs_c[7] - rhs_c[7] ) >= lit<T>::delta
            or std::abs( lhs_c[8] - rhs_c[8] ) >= lit<T>::delta
            or std::abs( lhs_c[9] - rhs_c[9] ) >= lit<T>::delta
            or std::abs( lhs_c[10] - rhs_c[10] ) >= lit<T>::delta
            or std::abs( lhs_c[11] - rhs_c[11] ) >= lit<T>::delta;
}

// Arithmetic

template< typename T > inline
mat4x3_t<T>     mat4x3_t<T>::operator+( mat4x3_t<T> const& rhs ) const
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
    
    T e30 = lhs_c[9] + rhs_c[9];
    T e31 = lhs_c[10] + rhs_c[10];
    T e32 = lhs_c[11] + rhs_c[11];
    
    return mat4x3_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31,
                        e02, e12, e22, e32 );
}

template< typename T > inline
mat4x3_t<T>     mat4x3_t<T>::operator-() const
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
   
    T e30 = -lhs_c[9];
    T e31 = -lhs_c[10];
    T e32 = -lhs_c[11];
    
    return mat4x3_t( e00, e10, e20, e30,
                     e01, e11, e21, e31,
                     e02, e12, e22, e32 );
}

template< typename T > inline
mat4x3_t<T>     mat4x3_t<T>::operator-( mat4x3_t<T> const& rhs ) const
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
    
    T e30 = lhs_c[9] - rhs_c[9];
    T e31 = lhs_c[10] - rhs_c[10];
    T e32 = lhs_c[11] - rhs_c[11];
    
    return mat4x3_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31,
                        e02, e12, e22, e32 );
}

template< typename T > inline
mat3_t<T>   mat4x3_t<T>::operator*( mat3x4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[6] * rhs_c[2] + lhs_c[9] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[7] * rhs_c[2] + lhs_c[10] * rhs_c[3];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[8] * rhs_c[2] + lhs_c[11] * rhs_c[3];
    
    T e10 = lhs_c[0] * rhs_c[4] + lhs_c[3] * rhs_c[5] + lhs_c[6] * rhs_c[6] + lhs_c[9] * rhs_c[7];
    T e11 = lhs_c[1] * rhs_c[4] + lhs_c[4] * rhs_c[5] + lhs_c[7] * rhs_c[6] + lhs_c[10] * rhs_c[7];
    T e12 = lhs_c[2] * rhs_c[4] + lhs_c[5] * rhs_c[5] + lhs_c[8] * rhs_c[6] + lhs_c[11] * rhs_c[7];
    
    T e20 = lhs_c[0] * rhs_c[8] + lhs_c[3] * rhs_c[9] + lhs_c[6] * rhs_c[10] + lhs_c[9] * rhs_c[11];
    T e21 = lhs_c[1] * rhs_c[8] + lhs_c[4] * rhs_c[9] + lhs_c[7] * rhs_c[10] + lhs_c[10] * rhs_c[11];
    T e22 = lhs_c[2] * rhs_c[8] + lhs_c[5] * rhs_c[9] + lhs_c[8] * rhs_c[10] + lhs_c[11] * rhs_c[11];
    
    return mat3_t<T>( e00, e10, e20,
                      e01, e11, e21,
                      e02, e12, e22 );
}

template< typename T > inline
mat2x3_t<T>   mat4x3_t<T>::operator*( mat2x4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[6] * rhs_c[2] + lhs_c[9] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[7] * rhs_c[2] + lhs_c[10] * rhs_c[3];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[8] * rhs_c[2] + lhs_c[11] * rhs_c[3];
    
    T e10 = lhs_c[0] * rhs_c[4] + lhs_c[3] * rhs_c[5] + lhs_c[6] * rhs_c[6] + lhs_c[9] * rhs_c[7];
    T e11 = lhs_c[1] * rhs_c[4] + lhs_c[4] * rhs_c[5] + lhs_c[7] * rhs_c[6] + lhs_c[10] * rhs_c[7];
    T e12 = lhs_c[2] * rhs_c[4] + lhs_c[5] * rhs_c[5] + lhs_c[8] * rhs_c[6] + lhs_c[11] * rhs_c[7];

    return mat2x3_t<T>( e00, e10,
                        e01, e11,
                        e02, e12 );
}

template< typename T > inline
mat4x3_t<T>   mat4x3_t<T>::operator*( mat4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    T const* rhs_c = rhs.data.c;
    
    T e00 = lhs_c[0] * rhs_c[0] + lhs_c[3] * rhs_c[1] + lhs_c[6] * rhs_c[2] + lhs_c[9] * rhs_c[3];
    T e01 = lhs_c[1] * rhs_c[0] + lhs_c[4] * rhs_c[1] + lhs_c[7] * rhs_c[2] + lhs_c[10] * rhs_c[3];
    T e02 = lhs_c[2] * rhs_c[0] + lhs_c[5] * rhs_c[1] + lhs_c[8] * rhs_c[2] + lhs_c[11] * rhs_c[3];
    
    T e10 = lhs_c[0] * rhs_c[4] + lhs_c[3] * rhs_c[5] + lhs_c[6] * rhs_c[6] + lhs_c[9] * rhs_c[7];
    T e11 = lhs_c[1] * rhs_c[4] + lhs_c[4] * rhs_c[5] + lhs_c[7] * rhs_c[6] + lhs_c[10] * rhs_c[7];
    T e12 = lhs_c[2] * rhs_c[4] + lhs_c[5] * rhs_c[5] + lhs_c[8] * rhs_c[6] + lhs_c[11] * rhs_c[7];
    
    T e20 = lhs_c[0] * rhs_c[8] + lhs_c[3] * rhs_c[9] + lhs_c[6] * rhs_c[10] + lhs_c[9] * rhs_c[11];
    T e21 = lhs_c[1] * rhs_c[8] + lhs_c[4] * rhs_c[9] + lhs_c[7] * rhs_c[10] + lhs_c[10] * rhs_c[11];
    T e22 = lhs_c[2] * rhs_c[8] + lhs_c[5] * rhs_c[9] + lhs_c[8] * rhs_c[10] + lhs_c[11] * rhs_c[11];
    
    T e30 = lhs_c[0] * rhs_c[12] + lhs_c[3] * rhs_c[13] + lhs_c[6] * rhs_c[14] + lhs_c[9] * rhs_c[15];
    T e31 = lhs_c[1] * rhs_c[12] + lhs_c[4] * rhs_c[13] + lhs_c[7] * rhs_c[14] + lhs_c[10] * rhs_c[15];
    T e32 = lhs_c[2] * rhs_c[12] + lhs_c[5] * rhs_c[13] + lhs_c[8] * rhs_c[14] + lhs_c[11] * rhs_c[15];
    
    return mat4x3_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31,
                        e02, e12, e22, e32 );
}

template< typename T > inline
vec3_t<T>     mat4x3_t<T>::operator*( vec4_t<T> const& rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T x0 = lhs_c[0] * rhs[0] + lhs_c[3] * rhs[1] + lhs_c[6] * rhs[2] + lhs_c[9] * rhs[3];
    T x1 = lhs_c[1] * rhs[0] + lhs_c[4] * rhs[1] + lhs_c[7] * rhs[2] + lhs_c[10] * rhs[3];;
    T x2 = lhs_c[2] * rhs[0] + lhs_c[5] * rhs[1] + lhs_c[8] * rhs[2] + lhs_c[11] * rhs[3];;
    
    return vec3_t<T>( x0, x1, x2 );
}

template< typename T > inline
vec4_t<T>     operator*( vec3_t<T> const& lhs,
                         mat4x3_t<T> const& rhs )
{
    T const* rhs_c = rhs.data.c;
    
    T x0 = rhs_c[0] * lhs[0] + rhs_c[1] * lhs[1] + rhs_c[2] * lhs[2];
    T x1 = rhs_c[3] * lhs[0] + rhs_c[4] * lhs[1] + rhs_c[5] * lhs[2];
    T x2 = rhs_c[6] * lhs[0] + rhs_c[7] * lhs[1] + rhs_c[8] * lhs[2];
    T x3 = rhs_c[9] * lhs[0] + rhs_c[10] * lhs[1] + rhs_c[11] * lhs[2];
    
    return vec4_t<T>( x0, x1, x2, x3 );
}

template< typename T >
mat4x3_t<T>     mat4x3_t<T>::operator*( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] * rhs;
    T e01 = lhs_c[1] * rhs;
    T e02 = lhs_c[2] * rhs;
    
    T e10 = lhs_c[3] * rhs;
    T e11 = lhs_c[4] * rhs;
    T e12 = lhs_c[5] * rhs;
    
    T e20 = lhs_c[6] * rhs;
    T e21 = lhs_c[7] * rhs;
    T e22 = lhs_c[8] * rhs;
    
    T e30 = lhs_c[9] * rhs;
    T e31 = lhs_c[10] * rhs;
    T e32 = lhs_c[11] * rhs;
    
    return mat4x3_t( e00, e10, e20, e30,
                     e01, e11, e21, e31,
                     e02, e12, e22, e32 );
}

template< typename D >
mat4x3_t<D>     operator*( D lhs, mat4x3_t<D> const& rhs )
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
    
    D e30 = rhs_c[9] * lhs;
    D e31 = rhs_c[10] * lhs;
    D e32 = rhs_c[11] * lhs;
    
    return mat4x3_t<D>( e00, e10, e20, e30,
                        e01, e11, e21, e31,
                        e02, e12, e22, e32 );
}

template< typename T >
mat4x3_t<T>     mat4x3_t<T>::operator/( T rhs ) const
{
    T const* lhs_c = this->data.c;
    
    T e00 = lhs_c[0] / rhs;
    T e01 = lhs_c[1] / rhs;
    T e02 = lhs_c[2] / rhs;
    
    T e10 = lhs_c[3] / rhs;
    T e11 = lhs_c[4] / rhs;
    T e12 = lhs_c[5] / rhs;
    
    T e20 = lhs_c[6] / rhs;
    T e21 = lhs_c[7] / rhs;
    T e22 = lhs_c[8] / rhs;
    
    T e30 = lhs_c[9] / rhs;
    T e31 = lhs_c[10] / rhs;
    T e32 = lhs_c[11] / rhs;
    
    return mat4x3_t<T>( e00, e10, e20, e30,
                        e01, e11, e21, e31,
                        e02, e12, e22, e32 );
}

// Mutative Operators

template< typename T > inline
mat4x3_t<T>&    mat4x3_t<T>::operator=( mat4x3_t<T> const& rhs )
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
    return *this;
}

template< typename T > inline
col3<T>     mat4x3_t<T>::operator[]( size_t i )
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat4x3_t out of range" );
    }
    
    return col3<T>( this->data.c + (3*i), true );
}

template< typename T > inline
col3<T>     mat4x3_t<T>::operator[]( size_t i ) const
{
    if ( i > 3 or i < 0 ) {
        throw std::out_of_range( "index to column vector lookup on mat4x3_t out of range" );
    }
    
    T* col_cpy = new T[3];
    
    col_cpy[0] = this-data->c[ 3 * i ];
    col_cpy[1] = this-data->c[ 3 * i + 1 ];
    col_cpy[2] = this-data->c[ 3 * i + 2 ];
    
    return col3<T>( col_cpy, false );
}

template< typename T > inline
T&     mat4x3_t<T>::operator()( size_t col,
                                size_t row )
{
    if ( col > 3 or row > 2 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat4x3_t used out of bounds index");
    }
    
    return this->data.c[col * 3 + row];
}

template< typename T > inline
T      mat4x3_t<T>::operator()( size_t col,
                                size_t row ) const
{
    if ( col > 3 or row > 2 or col < 0 or row < 0 ) {
        throw std::out_of_range("Indexing of mat4x3_t used out of bounds index");
    }
    
    return this->data.c[col * 3 + row];
}

// Mutative Functions

template< typename T > inline
col3<T>    mat4x3_t<T>::column( size_t col )
{ return (*this)[col]; }

template< typename T > inline
col3<T>     mat4x3_t<T>::column( size_t col ) const
{ return (*this)[col]; }

template< typename T > inline
mat4x3_t<T>&    mat4x3_t<T>::columns( vec3_t<T> const& col0,
                                      vec3_t<T> const& col1,
                                      vec3_t<T> const& col2,
                                      vec3_t<T> const& col3 )
{
    T* cm = this->data.c;
    
    cm[0] = col0[0];
    cm[1] = col0[1];
    cm[2] = col0[2];
    
    cm[3] = col1[0];
    cm[4] = col1[1];
    cm[5] = col1[2];
    
    cm[6] = col2[0];
    cm[7] = col2[1];
    cm[8] = col2[2];
    
    cm[9]  = col3[0];
    cm[10] = col3[1];
    cm[11] = col3[2];
    
    return *this;
}

template< typename T >
mat4x3_t<T>& mat4x3_t<T>::fill( T val )
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
    c[9] = val;
    c[10] = val;
    c[11] = val;
    return *this;
}

template< typename T > inline
row4<T>    mat4x3_t<T>::row( size_t row )
{
    if ( row > 2 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat4x3_t out of range" );
    }
    
    return row4<T>( this->data.c + row,
                    this->data.c + 3 + row,
                    this->data.c + 6 + row,
                    this->data.c + 9 + row,
                    true );
}

template< typename T > inline
row4<T>     mat4x3_t<T>::row( size_t row ) const
{
    if ( row > 2 or row < 0 ) {
        throw std::out_of_range( "index to row vector lookup on mat4x3_t out of range" );
    }
    
    return row4<T>( this->data.c[row],
                    this->data.c[3 + row],
                    this->data.c[6 + row],
                    this->data.c[9 + row] );
}

template< typename T > inline
mat4x3_t<T>& mat4x3_t<T>::rows( vec4_t<T> const& row0,
                                vec4_t<T> const& row1,
                                vec4_t<T> const& row2 )
{
    T* cm = this->data.c;
    
    cm[0] = row0[0];
    cm[3] = row0[1];
    cm[6] = row0[2];
    cm[9] = row0[3];
    
    cm[1] = row1[0];
    cm[4] = row1[1];
    cm[7] = row1[2];
    cm[10] = row1[3];
    
    cm[2] = row2[0];
    cm[5] = row2[1];
    cm[8] = row2[2];
    cm[11] = row2[3];
    
    return *this;
}

// Utility

template< typename T > inline
raw_map const   mat4x3_t<T>::to_map() const
{
    return map_bytes( sizeof(T) * 12, this->data.bytes );
}

template<typename T>
std::ostream& operator<<( std::ostream& stream, mat4x3_t<T> const& src )
{
    stream << "[ " << src(0,0) << " " << src(1,0) << " " << src(2,0) << " " << src(3,0) << " ]" << '\n';
    stream << "[ " << src(0,1) << " " << src(1,1) << " " << src(2,1) << " " << src(3,1) << " ]" << '\n';
    stream << "[ " << src(0,2) << " " << src(1,2) << " " << src(2,2) << " " << src(3,2) << " ]" << std::endl;
    return stream;
}



}

#endif
