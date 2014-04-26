#include "utility.hpp"

namespace gfx {

namespace type {

class TypeFactory {
public:
    static Layout make_type_sig( std::string const& new_name,
                               GLint new_n_components,
                               GLsizeiptr new_n_bytes,
                               GLenum new_component_type );
};

inline Layout TypeFactory::make_type_sig( std::string const& new_name,
                                 GLint new_n_components,
                                 GLsizeiptr new_n_bytes,
                                 GLenum new_component_type )
{
    return Layout( new_name, new_n_components, new_n_bytes, new_component_type );
}

Layout const Vec2 = TypeFactory::make_type_sig( "gfx::Vec2", 2, sizeof(float) * 2, gl::FLOAT );
Layout const Vec3 = TypeFactory::make_type_sig( "gfx::Vec3", 3, sizeof(float) * 3, gl::FLOAT );
Layout const Vec4 = TypeFactory::make_type_sig( "gfx::Vec4", 4, sizeof(float) * 4, gl::FLOAT );

Layout const Byte = TypeFactory::make_type_sig( "gfx::Byte", 1, sizeof(char), gl::BYTE );
Layout const UByte = TypeFactory::make_type_sig( "gfx::UByte", 1, sizeof(char), gl::UNSIGNED_BYTE );
Layout const Short = TypeFactory::make_type_sig( "gfx::Short", 1, sizeof(short), gl::SHORT );
Layout const UShort = TypeFactory::make_type_sig( "gfx::UShort", 1, sizeof(short), gl::UNSIGNED_SHORT );
Layout const Int = TypeFactory::make_type_sig( "gfx::Int", 1, sizeof(int), gl::INT );
Layout const UInt = TypeFactory::make_type_sig( "gfx::UInt", 1, sizeof(int), gl::UNSIGNED_INT );

Layout const HFloat = TypeFactory::make_type_sig( "gfx::HFloat", 1, 16, gl::HALF_FLOAT );
Layout const Float = TypeFactory::make_type_sig( "gfx::Float", 1, sizeof(float), gl::FLOAT );
Layout const Double = TypeFactory::make_type_sig( "gfx::Double", 1, sizeof(double), gl::DOUBLE );

}

}
