#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstddef>
#include <string>
#include "../gVideo/gl_core_3_3.hpp"

#define gfx_xstr(x) gfx_str(x)
#define gfx_str(x) #x

namespace gfx {

template< typename T >
class Out {
    typedef typename T InType;
    
    public:
    Out( InType& ref ) : ref( mRef ) {}
    
    
    
    
    private:
    InType& mRef;
    
}


/**
 * Never ever ever dump the 'type' namespace into 'gfx'!
 *
 * If you are dumb enough to do that, you'll get a name
 * collision like "identifier 'Vec4' on line 563 names a type"
 * or "unexpected token on line 4328; expected ';'"
 * and then you'll call me up and be all "Dude, wtf?" and
 * I'll be all "well you didn't read the comments, now did you?"
 * and then your significant other will leave because of the
 * SHAME. */
namespace type {

class TypeFactory;

class Layout {
public:
    Layout() :
        n_components( 0 ),
        component_type( gl::NONE ),
        n_bytes( 0 ),
        name( "NO TYPE" ) {};
    std::string const& get_name() const;
    /* Gotta check if this reads as the correct type conversion. */
    inline operator std::string const&() const { return name; }
    /* I find the need for this function dubious and dangerous,
     * so until I need it I will leave it commented out. */
    //inline operator char*() const { return name.c_str(); }
    GLenum get_comp_type() const;
    GLint get_n_comp() const;
    GLsizeiptr get_bytes() const;
    friend bool operator==( Layout const& rhs,
                            Layout const& lhs );
private:
    friend class TypeFactory;

    Layout( std::string const& new_name,
            GLint new_n_components,
            GLsizeiptr new_n_bytes,
            GLenum new_component_type ) :
              n_components( new_n_components ),
              component_type( new_component_type ),
              n_bytes( new_n_bytes ),
              name( new_name ) {};

    GLint n_components;
    GLenum component_type;
    GLsizeiptr n_bytes;
    std::string name;

};

inline std::string const& Layout::get_name() const
{
    return name;
}

inline GLint Layout::get_n_comp() const
{
    return n_components;
}

inline GLenum Layout::get_comp_type() const
{
    return component_type;
}

inline GLsizeiptr Layout::get_bytes() const
{
    return n_bytes;
}

extern Layout const Vec2;
extern Layout const Vec3;
extern Layout const Vec4;

extern Layout const Byte;
extern Layout const UByte;
extern Layout const Short;
extern Layout const UShort;
extern Layout const Int;
extern Layout const UInt;

extern Layout const HFloat;
extern Layout const Float;
extern Layout const Double;


inline bool operator ==( Layout const& rhs, Layout const& lhs )
{
    /* It IS possible that two data types would have the same GL
     * mapping signature; for instance, if a Color4 class was
     * created, then without the (slow) name compare Vec4 == Color4
     * is true.  I may opt to enforce GL mapping comparisons to
     * always be distinct and thus drop the name compare.  An
     * alternative is to install a numerical type ID system in
     * all gEngine data classes.*/
    return (rhs.component_type == lhs.component_type)
           && (rhs.n_components == lhs.n_components)
           && (rhs.name == lhs.name);
}

template< typename DATA_T >
inline Layout const& info()
{
    return DATA_T::layout;
}

template<>
inline Layout const& info<float>()
{
    return Float;
}

template<>
inline Layout const& info<int>()
{
    return Int;
}

template<>
inline Layout const& info<unsigned int>()
{
    return UInt;
}

template<>
inline Layout const& info<short>()
{
    return Short;
}

template<>
inline Layout const& info<unsigned short>()
{
    return UShort;
}

template<>
inline Layout const& info<char>()
{
    return Byte;
}

template<>
inline Layout const& info<unsigned char>()
{
    return UByte;
}

template<>
inline Layout const& info<double>()
{
    return Double;
}

}

}

#endif
