#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <stdexcept>

#include "gl_core_3_3.hpp"
#include "../gMath/datatype.hpp"
#include "../gVideo/video_manager.hpp"

namespace gfx {

    /**
     * This is weird, I know. Similar to swizzles over in datatype.hpp,
     * the bit_t class and the rat's nest of multiply inherited
     * subclasses serve to make it so the texture::settings
     * functions that deal with image format can only accept
     * bit depths that are legal while producing comprehensible
     * error messages.
     */
    
    class bit_t { virtual size_t      n() const = 0; };
    
    class R    : public virtual bit_t { virtual size_t      n() const = 0; };
    class RG   : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGB  : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGBA : public virtual bit_t { virtual size_t      n() const = 0; };
    
    class Rsn    : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGsn   : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGBsn  : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGBAsn : public virtual bit_t { virtual size_t      n() const = 0; };
    
    class Rf    : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGf   : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGBf  : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGBAf : public virtual bit_t { virtual size_t      n() const = 0; };
    
    class Ri    : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGi   : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGBi  : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGBAi : public virtual bit_t { virtual size_t      n() const = 0; };
    
    class Rui    : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGui   : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGBui  : public virtual bit_t { virtual size_t      n() const = 0; };
    class RGBAui : public virtual bit_t { virtual size_t      n() const = 0; };
    
    class two_bit : public RGBA {
        virtual size_t      n() const { return 2; }
    };
    
    class four_bit : public RGBA, public RGB {
        virtual size_t      n() const { return 4; }
    };
    
    class five_bit : public RGBA, public RGB {
        virtual size_t      n() const { return 5; }
    };
    
    class eight_bit : public RGBA,   public RGB,   public RG,   public R,
                      public RGBAsn, public RGBsn, public RGsn, public Rsn,
                      public RGBAui, public RGBui, public RGui, public Rui,
                      public RGBAi,  public RGBi,  public RGi,  public Ri {
        virtual size_t      n() const { return 8; }
    };
    
    class ten_bit : public RGB {
        virtual size_t      n() const { return 10; }
    };
    
    class twelve_bit : public RGBA, public RGB {
        virtual size_t      n() const { return 12; }
    };
    
    class sixteen_bit : public RGBA,   public RGB,   public RG,   public R,
                        public RGBAsn, public RGBsn, public RGsn, public Rsn,
                        public RGBAui, public RGBui, public RGui, public Rui,
                        public RGBAi,  public RGBi,  public RGi,  public Ri,
                        public RGBAf,  public RGBf,  public RGf,  public Rf {
        virtual size_t      n() const { return 16; }
    };
    
    class thirty_two_bit : public RGBAui, public RGBui, public RGui, public Rui,
                           public RGBAi,  public RGBi,  public RGi,  public Ri,
                           public RGBAf,  public RGBf,  public RGf,  public Rf  {
        virtual size_t      n() const { return 32; }
    };
    
    class texture {
    public:
        
        class settings {
        public:
            settings();
            settings&       one_dimensional( size_t const dw );
            settings&       two_dimensional( size_t const dw,
                                             size_t const dh );
            settings&       three_dimensional( size_t const dw,
                                               size_t const dh,
                                               size_t const dd );
            settings&       cube_map( size_t const de );
            settings&       multisampled();
            settings&       from_buffer();
            settings&       array( size_t const layers );
            settings&       unsigned_norm_1( R const& depth );
            settings&       unsigned_norm_2( RG const& depth );
            settings&       unsigned_norm_3( RGB const& depth );
            settings&       unsigned_norm_4( RGBA const& depth );
            settings&       signed_norm_1( Rsn const& depth );
            settings&       signed_norm_2( RGsn const& depth );
            settings&       signed_norm_3( RGBsn const& depth );
            settings&       signed_norm_4( RGBAsn const& depth );
            settings&       unsigned_int_1( Rui const& depth );
            settings&       unsigned_int_2( RGui const& depth );
            settings&       unsigned_int_3( RGBui const& depth );
            settings&       unsigned_int_4( RGBAui const& depth );
            settings&       signed_int_1( Ri const& depth );
            settings&       signed_int_2( RGi const& depth );
            settings&       signed_int_3( RGBi const& depth );
            settings&       signed_int_4( RGBAi const& depth );
            settings&       floating_point_1( Rf const& depth );
            settings&       floating_point_2( RGf const& depth );
            settings&       floating_point_3( RGBf const& depth );
            settings&       floating_point_4( RGBAf const& depth );
            settings&       packed_3channel_8bit();
            settings&       packed_4channel_16bit();
            settings&       packed_4channel_32bit();
            settings&       packed_4channel_32bit_unsigned();
            settings&       packed_3channel_32bit_float();
            settings&       if_you_find_a_use_for_this_image_format_you_get_a_cookie(); //No, seriously
            settings&       sRGB_8bit();
            settings&       sRGBA_8bit();            
        private:
            size_t      dw_v;
            size_t      dh_v;
            size_t      dd_v;
            bool        as_cube_v;
            bool        as_array;
            size_t      layers_v;
            bool        from_buffer_v;
            bool        multisampled_v;
            GLuint      image_format_v;
        };
        
    private:
        GLuint      target;
        uvec3       dim;
        GLuint      image_format;
    };

texture::settings::settings() :
                    dw_v ( 1 ),
                    dh_v ( 0 ),
                    dd_v ( 0 ),
                    as_cube_v ( false ),
                    as_array_v ( false ),
                    layers_v ( 0 ),
                    from_buffer_v ( false ) {}
                    
inline  texture::settings&  texture::settings::one_dimensional( size_t const dw )
{
    dw_v = dw;
    dh_v = 0;
    dd_v = 0;
    return *this; }

inline  texture::settings&  texture::settings::two_dimensional( size_t const dw,
                                                                size_t const dh )
{
    dw_v = dw;
    dh_v = dh;
    return *this;
}

inline  texture::settings&  texture::settings::three_dimensional( size_t const dw,
                                                                  size_t const dh,
                                                                  size_t const dd )
{
    dw_v = dw;
    dh_v = dh;
    dd_v = dd;
    return *this;
}
                    
inline  texture::settings&  texture::settings::cube_map( size_t const de )
{
    as_cube_v = true;
    dw_v = de;
    dh_v = 0;
    dd_v = 0;
    return *this;
}

inline  texture::settings&  texture::settings::multisampled()
{
    multisampled_v = true;
    return *this;
}

inline  texture::settings&  texture::settings::from_buffer()
{
    from_buffer_v = true;
    return *this;
}

inline  texture::settings&  texture::settings::array( size_t const layers )
{
    as_array_v = true;
    layers_v = layers;
    return *this;
}

inline  texture::settings&       texture::settings::unsigned_norm_1( R const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::R8;
        case 16:
            image_format_v = gl::R16;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for single channel normalized unsigned integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::unsigned_norm_2( RG const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RG8;
        case 16:
            image_format_v = gl::RG16;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for dual channel normalized unsigned integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::unsigned_norm_3( RGB const& depth )
{
    switch ( depth.n() ) {
        case 4:
            image_format_v = gl::RGB4;
        case 5:
            image_format_v = gl::RGB5;
        case 8:
            image_format_v = gl::RGB8;
        case 10:
            image_format_v = gl::RGB10;
        case 12:
            image_format_v = gl::RGB12;
        case 16:
            image_format_v = gl::RGB16;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for triple channel normalized unsigned integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::unsigned_norm_4( RGBA const& depth )
{
    switch ( depth.n() ) {
        case 2:
            image_format_v = gl::RGBA2;
        case 4:
            image_format_v = gl::RGBA4;
        case 5:
            image_format_v = gl::RGBA5;
        case 8:
            image_format_v = gl::RGBA8;
        case 12:
            image_format_v = gl::RGBA12;
        case 16:
            image_format_v = gl::RGBA16;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for quad channel normalized unsigned integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::signed_norm_1( Rsn const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::R8_SNORM;
        case 16:
            image_format_v = gl::R16_SNORM;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for single channel normalized signed integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::signed_norm_2( RGsn const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RG8_SNORM;
        case 16:
            image_format_v = gl::RG16_SNORM;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for dual channel normalized signed integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::signed_norm_3( RGBsn const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RGB8_SNORM;
        case 16:
            image_format_v = gl::RGB16_SNORM;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for triple channel normalized signed integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::signed_norm_4( RGBAsn const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RGBA8_SNORM;
        case 16:
            image_format_v = gl::RGBA16_SNORM;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for quad channel normalized signed integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::unsigned_int_1( Ru const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::R8UI;
        case 16:
            image_format_v = gl::R16UI;
        case 32:
            image_format_v = gl::R32UI;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for single channel unsigned integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::unsigned_int_2( RGu const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RG8UI;
        case 16:
            image_format_v = gl::RG16UI;
        case 32:
            image_format_v = gl::RG32UI;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for dual channel unsigned integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::unsigned_int_3( RGBu const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RGB8UI;
        case 16:
            image_format_v = gl::RGB16UI;
        case 32:
            image_format_v = gl::RGB32UI;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for triple channel unsigned integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::unsigned_int_4( RGBAu const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RGBA8UI;
        case 16:
            image_format_v = gl::RGBA16UI;
        case 32:
            image_format_v = gl::RGBA32UI;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for quad channel unsigned integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::signed_int_1( Ri const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::R8I;
        case 16:
            image_format_v = gl::R16I;
        case 32:
            image_format_v = gl::R32I;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for single channel signed integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::signed_int_2( RGi const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RG8I;
        case 16:
            image_format_v = gl::RG16I;
        case 32:
            image_format_v = gl::RG32I;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for dual channel signed integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::signed_int_3( RGBi const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RGB8I;
        case 16:
            image_format_v = gl::RGB16I;
        case 32:
            image_format_v = gl::RGB32I;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for triple channel signed integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::signed_int_4( RGBAi const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RGBA8I;
        case 16:
            image_format_v = gl::RGBA16I;
        case 32:
            image_format_v = gl::RGBA32I;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for quad channel signed integer image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::floating_point_1( Rf const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::R8F;
        case 16:
            image_format_v = gl::R16F;
        case 32:
            image_format_v = gl::R32F;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for single channel floating point image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::floating_point_2( RGf const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RG8F;
        case 16:
            image_format_v = gl::RG16F;
        case 32:
            image_format_v = gl::RG32F;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for dual channel floating point image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::floating_point_3( RGBf const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RGB8F;
        case 16:
            image_format_v = gl::RGB16F;
        case 32:
            image_format_v = gl::RGB32F;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for triple channel floating point image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&       texture::settings::floating_point_4( RGBAf const& depth )
{
    switch ( depth.n() ) {
        case 8:
            image_format_v = gl::RGBA8F;
        case 16:
            image_format_v = gl::RGBA16F;
        case 32:
            image_format_v = gl::RGBA32F;
        default:
            std::string msg ( "Bit depth " );
            msg += depth.n();
            msg += " is illegal for quad channel floating point image formats.";
            throw std::invalid_argument( msg );
    }
    return *this;
}

inline  texture::settings&  texture::settings::packed_3channel_8bit()
{ image_format_v = gl::R3_G3_B2; return *this; }

inline  texture::settings&  texture::settings::packed_4channel_16bit()
{ image_format_v = gl::RGB5_A1; return *this; }

inline  texture::settings&  texture::settings::packed_4channel_32bit()
{ image_format_v = gl::RGB10_A2; return *this; }

inline  texture::settings&  texture::settings::packed_4channel_32bit_unsigned()
{ image_format_v = gl::RGB10_A2UI; return *this; }

inline  texture::settings&  texture::settings::packed_4channel_32bit_float()
{ image_format_v = gl::R11F_G11F_B10F; return *this; }
    
inline texture::settings&
texture::settings::if_you_find_a_use_for_this_image_format_you_get_a_cookie()
{ image_format_v = gl::RGB9_E5; return *this; }

inline  texture::settings&  texture::settings::sRGB_8bit()
{ image_format_v = gl::SRGB8; return *this; }

inline  texture::settings&  texture::settings::sRGBA_8bit()
{ image_format_v = gl::SRGB8_ALPHA8; return *this; }

}
#endif