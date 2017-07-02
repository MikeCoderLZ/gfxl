#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <stdexcept>
#include <cstdint>
#include <iostream>

#include "../gVideo/gl_core_3_3.hpp"
#include "../gMath/datatype.hpp"
#include "../gVideo/video.hpp"

namespace gfx {
    /**
     * \class gfx::bit_t texture.hpp "gCore/gScene/texture.hpp"
     * \brief The base class for channel format selectors.
     * Channel format selectors are a utility class used in the configuration
     * of \ref gfx::texture "textures". Functionally, there are an enum with
     * special type charactersitics to make formatting errors cause compilation
     * errors.
     * 
     * They consist of a multiply inheritted class hierarchy; the derived
     * classes at the end of the hierarchy inherit from the directly derived
     * classes of bit_t. The instances of these terminal classes which are
     * provided are used to select the bit depth of the chanels in the texture,
     * being passed to the number format and chanel multplicity selectors in
     * the \ref gfx::texture::settings "settings" class.
     * 
     * Using multiple inheritance here means that only combinations of channel
     * bit depth, number format, and chanel mulplicity which are legal in
     * OpenGL are allowed. Illegal combinations cause compilation errors,
     * stopping a developer from making a mistake and causing error messages
     * that more or less actually mean what they say.
     */
    class bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::R texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for single channel formats.
     */
    class R    : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RG texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for dual channel formats.
     */
    class RG   : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGB texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for three channel formats.
     */
    class RGB  : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGBA texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for four channel formats.
     */
    class RGBA : public virtual bit_t { public: virtual size_t      n() const = 0; };
    
    /**
     * \class gfx::Rsn texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for single channel signed integer formats.
     */
    class Rsn    : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGsn texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for dual channel signed integer formats.
     */
    class RGsn   : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGBsn texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for four channel signed integer formats.
     */
    class RGBsn  : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGBAsn texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for four channel signed integer formats.
     */
    class RGBAsn : public virtual bit_t { public: virtual size_t      n() const = 0; };
    
    /**
     * \class gfx::Rf texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for single channel floating point formats.
     */
    class Rf    : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGf texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for dual channel floating point formats.
     */
    class RGf   : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGBf texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for four channel floating point formats.
     */
    class RGBf  : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGBAf texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for four channel floating point formats.
     */
    class RGBAf : public virtual bit_t { public: virtual size_t      n() const = 0; };
    
    /**
     * \class gfx::Ri texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for single channel integer formats.
     */
    class Ri    : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGi texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for dual channel integer formats.
     */
    class RGi   : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGBi texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for four channel integer formats.
     */
    class RGBi  : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGBAi texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for four channel integer formats.
     */
    class RGBAi : public virtual bit_t { public: virtual size_t      n() const = 0; };
    
    /**
     * \class gfx::Rui texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for single channel unsigned integer formats.
     */
    class Rui    : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGui texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for dual channel unsigned integer formats.
     */
    class RGui   : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGBui texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for four channel unsigned integer formats.
     */
    class RGBui  : public virtual bit_t { public: virtual size_t      n() const = 0; };
    /**
     * \class gfx::RGBAui texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for four channel unsigned integer formats.
     */
    class RGBAui : public virtual bit_t { public: virtual size_t      n() const = 0; };
    
    /**
     * \class gfx::two_bit_t texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for two bit channel formats.
     */
    class two_bit_t : public RGBA {
        public: virtual size_t      n() const { return 2; }
    };
    /**
     * \var gfx::two_bit_t const gfx::two_bit
     * \brief The instance of the two bit channel format selector.
     */
    two_bit_t const two_bit;
    /**
     * \class gfx::four_bit_t texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for tour bit channel formats.
     */
    class four_bit_t : public RGBA, public RGB {
        public: virtual size_t      n() const { return 4; }
    };
    /**
     * \var gfx::four_bit_t const gfx::four_bit
     * \brief The instance of the four bit channel format selector.
     */
    four_bit_t const four_bit;
    /**
     * \class gfx::five_bit_t texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for five bit channel formats.
     */
    class five_bit_t : /*public RGBA,*/ public RGB {
        public: virtual size_t      n() const { return 5; }
    };
    /**
     * \var gfx::five_bit_t const gfx::five_bit
     * \brief The instance of the five bit channel format selector.
     */
    five_bit_t const five_bit;
    /**
     * \class gfx::eight_bit_t texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for eight bit channel formats.
     */
    class eight_bit_t : public RGBA,   public RGB,   public RG,   public R,
                        public RGBAsn, public RGBsn, public RGsn, public Rsn,
                        public RGBAui, public RGBui, public RGui, public Rui,
                        public RGBAi,  public RGBi,  public RGi,  public Ri {
        public: virtual size_t      n() const { return 8; }
    };
    /**
     * \var gfx::eight_bit_t const gfx::eight_bit
     * \brief The instance of the eight bit channel format selector.
     */
    eight_bit_t const eight_bit;
    /**
     * \class gfx::ten_bit_t texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for ten bit channel formats.
     */
    class ten_bit_t : public RGB {
        public: virtual size_t      n() const { return 10; }
    };
    /**
     * \var gfx::ten_bit_t const gfx::ten_bit
     * \brief The instance of the two bit channel format selector.
     */
    ten_bit_t const ten_bit;
    /**
     * \class gfx::twelve_bit_t texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for 12 bit channel formats.
     */
    class twelve_bit_t : public RGBA, public RGB {
        public: virtual size_t      n() const { return 12; }
    };
    /**
     * \var gfx::twelve_bit_t const gfx::twelve_bit
     * \brief The instance of the 12 bit channel format selector.
     */
    twelve_bit_t const twelve_bit;
    /**
     * \class gfx::sixteen_bit_t texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for 16 bit channel formats.
     */
    class sixteen_bit_t : public RGBA,   public RGB,   public RG,   public R,
                          public RGBAsn, public RGBsn, public RGsn, public Rsn,
                          public RGBAui, public RGBui, public RGui, public Rui,
                          public RGBAi,  public RGBi,  public RGi,  public Ri,
                          public RGBAf,  public RGBf,  public RGf,  public Rf {
        public: virtual size_t      n() const { return 16; }
    };
    /**
     * \var gfx::sixteen_bit_t const gfx::sixteen_bit
     * \brief The instance of the 16 bit channel format selector.
     */
    sixteen_bit_t const sixteen_bit;
    /**
     * \class gfx::thirty_two_bit_t texture.hpp "gCore/gScene/texture.hpp"
     * \brief Selects for 32 bit channel formats.
     */
    class thirty_two_bit_t : public RGBAui, public RGBui, public RGui, public Rui,
                             public RGBAi,  public RGBi,  public RGi,  public Ri,
                             public RGBAf,  public RGBf,  public RGf,  public Rf  {
        public: virtual size_t      n() const { return 32; }
    };
    /**
     * \var gfx::thirty_two_bit_t const gfx::thirty_two_bit
     * \brief The instance of the 32 bit channel format selector.
     */
    thirty_two_bit_t const thrity_two_bit;
    
    /**
     * \class gfx::filter_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Base class for interpolation filter selectors.
     * Interpolation selectors are used in the configuration of
     * \ref gfx::texture "textures". Immediate derived classes of filter_t
     * are a family of classes that provide the terminal classes of the
     * inheritance hierarchy with type signatures that ensure only legal
     * filter types can be used for configuring a particular filter mode.
     */
    class filter_t {
        protected: virtual GLint   val() const = 0;
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \class gfx::min_filter_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for minification filtering.
     */
    class min_filter_t : public virtual filter_t {
        protected: virtual GLint   val() const = 0;
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \class gfx::mag_filter_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for magnification filtering.
     */
    class mag_filter_t : public virtual filter_t {
        protected: virtual GLint   val() const = 0;
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \class gfx::nearest_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for nearest filtering.
     */
    class nearest_t : public min_filter_t, public mag_filter_t {
        protected: virtual GLint   val() const { return gl::NEAREST; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::nearest_t const gfx::nearest
     * \brief Instance of the nearest filter selector.
     */
    nearest_t const nearest;
    
    /**
     * \class gfx::linear_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for linear filtering.
     */
    class linear_t : public min_filter_t, public mag_filter_t {
        protected: virtual GLint   val() const { return gl::LINEAR; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::linear_t const gfx::linear
     * \brief Instance of the linear filter selector.
     */
    linear_t const linear;
    
    /**
     * \class gfx::nearest_mipmap_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for nearest mipmap filtering.
     */
    class nearest_mipmap_t : public min_filter_t {
        protected: virtual GLint   val() const { return gl::NEAREST_MIPMAP_NEAREST; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::nearest_mipmap_t const gfx::nearest_mipmap_t
     * \brief Instance of the nearest image filtering and mipmapping.
     */
    nearest_mipmap_t const nearest_mipmap;
    
    /**
     * \class gfx::linear_mipmap_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for linear image filtering and mipmapping.
     */
    class linear_mipmap_t : public min_filter_t {
        protected: virtual GLint   val() const { return gl::LINEAR_MIPMAP_LINEAR; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::linear_mipmap_t const gfx::linear_mipmap_t
     * \brief Instance of the linear mipmap filter selector.
     */
    linear_mipmap_t const linear_mipmap;
    
    /**
     * \class gfx::linear_mipmap_nearest_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for linear image and nearest mipmap filtering.
     */
    class linear_mipmap_nearest_t : public min_filter_t {
        protected: virtual GLint   val() const { return gl::LINEAR_MIPMAP_NEAREST; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::linear_mipmap_nearest_t const gfx::linear_mipmap_nearest_t
     * \brief Instance of the linear image and mipmap nearest filter selector.
     */
    linear_mipmap_nearest_t const linear_mipmap_nearest;
    
    /**
     * \class gfx::nearest_mipmap_linear_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for nearest image and linear mipmap filtering.
     */
    class nearest_mipmap_linear_t : public min_filter_t {
        protected: virtual GLint   val() const { return gl::NEAREST_MIPMAP_LINEAR; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::nearest_mipmap_linear_t const gfx::nearest_mipmap_linear_t
     * \brief Instance of the nearest image and mipmap linear filter selector.
     */
    nearest_mipmap_linear_t const nearest_mipmap_linear;
    
    /**
     * \class gfx::wrap_mode_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Base class for wrapping mode selectors.
     * An interface for wrap mode selectors; there is no multiple inheritance
     * in this class hierarachy, the derived classes are also the terminal ones.
     */
    class wrap_mode_t {
        protected: virtual GLint   val() const = 0;
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \class gfx::clamp_to_border_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for clamp to border sampling.
     */
    class clamp_to_border_t : public wrap_mode_t {
        protected: virtual GLint   val() const { return gl::CLAMP_TO_BORDER; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::clamp_to_border_t const gfx::clamp_to_border_t
     * \brief Instance of the clamp to border sampling selector.
     */
    clamp_to_border_t const clamp_to_border;
    
    /**
     * \class gfx::clamp_to_edge_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for clamp to edge sampling.
     */
    class clamp_to_edge_t : public wrap_mode_t {
        protected: virtual GLint   val() const { return gl::CLAMP_TO_EDGE; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::clamp_to_edge_t const gfx::clamp_to_edge_t
     * \brief Instance of the clamp to edge sampling selector.
     */
    clamp_to_edge_t const clamp_to_edge;
    
//     class mirror_clamp_to_edge_t : public wrap_mode_t {
//         protected: virtual GLint   val() { return gl::MIRROR_CLAMP_TO_EDGE; };
//         friend                      class texture_1D;
//     };
//     mirror_clamp_to_edge_t const mirror_clamp_to_edge;
    
    /**
     * \class gfx::mirrored_repeat_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for mirrored repeat sampling.
     */
    class mirrored_repeat_t : public wrap_mode_t {
        protected: virtual GLint   val() const { return gl::MIRRORED_REPEAT; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::mirrored_repeat_t const gfx::mirrored_repeat_t
     * \brief Instance of the mirrored repeating sampling selector.
     */
    mirrored_repeat_t const mirrored_repeat;
    
    /**
     * \class gfx::repeat_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for repeat sampling.
     */
    class repeat_t : public wrap_mode_t {
        protected: virtual GLint   val() const { return gl::REPEAT; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::repeat_t const gfx::repeat_t
     * \brief Instance of the repeat sampling selector.
     */
    repeat_t const repeat;
    
    /**
     * \class gfx::comparison_function_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Base class for comparison function selectors.
     * An interface for comparison function selectors; there is no multiple inheritance
     * in this class hierarachy, the derived classes are also the terminal ones.
     */
    class comparison_function_t {
        protected: virtual GLint   val() const = 0;
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    
    /**
     * \class gfx::less_or_equal_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for the less than or equal to comparison function.
     */
    class less_or_equal_t : public comparison_function_t {
        protected: virtual GLint   val() const { return gl::LEQUAL; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::less_or_equal_t const gfx::less_or_equal_t
     * \brief Instance of the less than or equal to function selector.
     */
    less_or_equal_t const less_or_equal;
    
    /**
     * \class gfx::greater_or_equal_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for the greater than or equal to comparison function.
     */
    class greater_or_equal_t : public comparison_function_t {
        protected: virtual GLint   val() const { return gl::GEQUAL; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::greater_or_equal_t const gfx::greater_or_equal_t
     * \brief Instance of the greater than or equal to function selector.
     */
    greater_or_equal_t const greater_or_equal;
    
    /**
     * \class gfx::less_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for the less than comparison function.
     */
    class less_t : public comparison_function_t {
        protected: virtual GLint   val() const { return gl::LESS; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx::less_t const gfx::less_equal_t
     * \brief Instance of the less than function selector.
     */
    less_t const less;
    
    /**
     * \class gfx::greater_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for the greater than comparison function.
     */
    class greater_t : public comparison_function_t {
        protected: virtual GLint   val() const { return gl::GREATER; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx:greater_t const gfx::greater_equal_t
     * \brief Instance of the greater than function selector.
     */
    greater_t const greater;
    
    /**
     * \class gfx::equal_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for the equal to comparison function.
     */
    class equal_t : public comparison_function_t {
        protected: virtual GLint   val() const { return gl::EQUAL; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx:equal_t const gfx::equal_t
     * \brief Instance of the equal to function selector.
     */
    equal_t const equal;
    
    /**
     * \class gfx::not_equal_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for the not equal to comparison function.
     */
    class not_equal_t : public comparison_function_t {
        protected: virtual GLint   val() const { return gl::NOTEQUAL; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx:not_equal_t const gfx::not_equal_t
     * \brief Instance of the not equal to function selector.
     */
    not_equal_t const not_equal;
    
    /**
     * \class gfx::always_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for the always comparison function.
     */
    class always_t : public comparison_function_t {
        protected: virtual GLint   val() const { return gl::ALWAYS; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx:always_t const gfx::always_t
     * \brief Instance of the always to function selector.
     */
    always_t const always;
    
    /**
     * \class gfx::never_t texture.hpp "gCore/gVideo/texture.hpp"
     * \brief Selector for the never comparison function.
     */
    class never_t : public comparison_function_t {
        protected: virtual GLint   val() const { return gl::NEVER; };
        friend                      class texture_1D;
        friend                      class texture_2D;
    };
    /**
     * \var gfx:never_t const gfx::never_t
     * \brief Instance of the never to function selector.
     */
    never_t const never;
    
    /**
     * \class gfx::texture_1D texture.hpp "gCore/gScene/texture.hpp"
     * \brief Represents a one dimenstional texture.
     * One dimensional textures are configured with the member class
     * \ref gfx::texture_1D::settings "settings". They consist of a single
     * row of color information, which can be formatted in a large number
     * of ways.
     * 
     */
    class texture_1D {
    public:
        
        class settings {
        public:
            settings();
            settings&       dimension( size_t const dw );
            settings&       from_buffer();
            settings&       array( size_t const layers );
            settings&       unsigned_norm_1( R const& depth );
            settings&       unsigned_norm_2( RG const& depth,
                                             swizz2 const& r_src = r,
                                             swizz2 const& g_src = g );
            settings&       unsigned_norm_3( RGB const& depth,
                                             swizz3 const& r_src = r,
                                             swizz3 const& g_src = g,
                                             swizz3 const& b_src = b  );
            settings&       unsigned_norm_4( RGBA const& depth,
                                             swizz4 const& r_src = r,
                                             swizz4 const& g_src = g,
                                             swizz4 const& b_src = b,
                                             swizz4 const& a_src = a );
            settings&       signed_norm_1( Rsn const& depth );
            settings&       signed_norm_2( RGsn const& depth,
                                             swizz2 const& r_src = r,
                                             swizz2 const& g_src = g  );
            settings&       signed_norm_3( RGBsn const& depth,
                                             swizz3 const& r_src = r,
                                             swizz3 const& g_src = g,
                                             swizz3 const& b_src = b );
            settings&       signed_norm_4( RGBAsn const& depth,
                                             swizz4 const& r_src = r,
                                             swizz4 const& g_src = g,
                                             swizz4 const& b_src = b,
                                             swizz4 const& a_src = a );
            settings&       unsigned_int_1( Rui const& depth );
            settings&       unsigned_int_2( RGui const& depth,
                                             swizz2 const& r_src = r,
                                             swizz2 const& g_src = g  );
            settings&       unsigned_int_3( RGBui const& depth,
                                             swizz3 const& r_src = r,
                                             swizz3 const& g_src = g,
                                             swizz3 const& b_src = b );
            settings&       unsigned_int_4( RGBAui const& depth,
                                             swizz4 const& r_src = r,
                                             swizz4 const& g_src = g,
                                             swizz4 const& b_src = b,
                                             swizz4 const& a_src = a );
            settings&       signed_int_1( Ri const& depth );
            settings&       signed_int_2( RGi const& depth,
                                             swizz2 const& r_src = r,
                                             swizz2 const& g_src = g  );
            settings&       signed_int_3( RGBi const& depth,
                                             swizz3 const& r_src = r,
                                             swizz3 const& g_src = g,
                                             swizz3 const& b_src = b );
            settings&       signed_int_4( RGBAi const& depth,
                                             swizz4 const& r_src = r,
                                             swizz4 const& g_src = g,
                                             swizz4 const& b_src = b,
                                             swizz4 const& a_src = a );
            settings&       floating_point_1( Rf const& depth );
            settings&       floating_point_2( RGf const& depth,
                                             swizz2 const& r_src = r,
                                             swizz2 const& g_src = g  );
            settings&       floating_point_3( RGBf const& depth,
                                             swizz3 const& r_src = r,
                                             swizz3 const& g_src = g,
                                             swizz3 const& b_src = b );
            settings&       floating_point_4( RGBAf const& depth,
                                             swizz4 const& r_src = r,
                                             swizz4 const& g_src = g,
                                             swizz4 const& b_src = b,
                                             swizz4 const& a_src = a );
            settings&       packed_3channel_8bit();
            settings&       packed_4channel_16bit();
            settings&       packed_4channel_32bit();
            settings&       packed_4channel_32bit_unsigned();
            settings&       packed_3channel_32bit_float();
            settings&       if_you_find_a_use_for_this_image_format_you_get_a_cookie(); //No, seriously
            settings&       sRGB_8bit();
            settings&       sRGBA_8bit();
            settings&       mipmap_range( size_t const base,
                                          size_t const max );
            settings&       sample_range( float const base,
                                          float const max );
            settings&       sample_bias( float const bias );
            settings&       sample_minification( min_filter_t const& min );
            settings&       sample_magnification( mag_filter_t const& mag );
            settings&       wrap_s( wrap_mode_t const& mode );
            settings&       wrap_t( wrap_mode_t const& mode );
            settings&       comparison_function( comparison_function_t const& func );
            settings&       file( std::string const& path );
        private:
            size_t          dw_v;
            bool            as_cube_v;
            bool            as_array_v;
            size_t          layers_v;
            bool            from_buffer_v;
            GLuint          image_format_v;
            size_t          pixels_v;
            size_t          pixel_size_v;
            size_t          channels_v;
            size_t          base_level_v;
            size_t          max_level_v;
            float           base_lod_v;
            float           max_lod_v;
            float           lod_bias_v;
            GLint           min_filter_v;
            GLint           mag_filter_v;
            GLint           wrap_s_v;
            GLint           wrap_t_v;
            GLint           compare_func_v;
            GLint           r_src_v;
            GLint           g_src_v;
            GLint           b_src_v;
            GLint           a_src_v;
            std::string     path_v;
            friend          class texture_1D;
        };
                            texture_1D( settings const& set = settings() );
                            ~texture_1D();
        size_t              width() const;
        size_t              pixels() const;
        size_t              pixel_bits() const;
        void                file( std::string const& path );
        void                decode_file();
        void                load_data();
        void                use();
//         sub_tex_1D          get_sub_texture( size_t const w_start = 0,
//                                              size_t const w_end   = 0 );
    private:    
        
        GLuint              tex_ID;
        GLuint              target;
        size_t              width_v;
        size_t              pixels_v;
        size_t              pixel_bits_v;
        GLuint              image_format;
        std::string         path;
        
        unsigned char*      data;
        
        size_t              bytes();
    };
    
    /**
     * \brief Construct a new default one dimensional texture settings object.
     * The default settings for a one dimenstional texture are to have a
     * width of zero, no extra multi-texturing features, standard channel
     * soruces, and the cheapest interpolation and sampling filters. The
     * path is also empty.
     */
    inline texture_1D::settings::settings() :
                                    dw_v ( 0 ),
                                    as_cube_v ( false ),
                                    as_array_v ( false ),
                                    layers_v ( 0 ),
                                    from_buffer_v ( false ),
                                    image_format_v ( 0 ),
                                    pixels_v ( 0 ),
                                    pixel_size_v ( 0 ),
                                    channels_v ( 1 ),
                                    base_level_v ( 0 ),
                                    max_level_v ( 0 ),
                                    base_lod_v ( 0.0f ),
                                    max_lod_v ( 0.0f ),
                                    lod_bias_v ( 0.0f ),
                                    min_filter_v ( gl::NEAREST ),
                                    mag_filter_v ( gl::NEAREST ),
                                    wrap_s_v ( gl::CLAMP_TO_EDGE ),
                                    wrap_t_v ( gl::CLAMP_TO_EDGE ),
                                    compare_func_v ( 0 ),
                                    r_src_v ( gl::RED ),
                                    g_src_v ( gl::GREEN ),
                                    b_src_v ( gl::BLUE ),
                                    a_src_v ( gl::ALPHA ),
                                    path_v ( "" ) {}
    /**
     * \brief Set the new one dimensional texture's dimension.
     * \param dw The new dimension of the one dimensional texture.
     */
    inline  texture_1D::settings&  texture_1D::settings::dimension( size_t const dw )
    { dw_v = dw; pixels_v = dw; return *this; }
    /**
     * \brief Set the new one dimensional texture to be sourced from a buffer.
     */
    inline  texture_1D::settings&  texture_1D::settings::from_buffer()
    { from_buffer_v = true; return *this; }
    /**
     * \brief Set the new one dimensional texture ot be an array of textures.
     * \param layers The number of one dimensional textures in the array.
     */
    inline  texture_1D::settings&  texture_1D::settings::array( size_t const layers )
    {
        as_array_v = true;
        layers_v = layers;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have one unsigned
     * normalized chanel at the given bit depth.
     * \param depth The bit depth of the chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::unsigned_norm_1( R const& depth )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::R8;
                pixel_size_v = 8u;
                break;
            case 16:
                image_format_v = gl::R16;
                pixel_size_v = 16u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for single channel normalized unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        channels_v = 1;
        
        return *this;
    }

    /**
     * \brief Set the new one dimensional texture to have two unsigned
     * normalized chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::unsigned_norm_2( RG const& depth,
                                           swizz2 const& r_src,
                                           swizz2 const& g_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RG8;
                pixel_size_v = 16u;
                break;
            case 16:
                image_format_v = gl::RG16;
                pixel_size_v = 32u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for dual channel normalized unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec2 mask ( 0, 1 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
        }
        channels_v = 2;
        
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have three unsigned
     * normalized chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::unsigned_norm_3( RGB const& depth,
                                           swizz3 const& r_src,
                                           swizz3 const& g_src,
                                           swizz3 const& b_src )
    {
        switch ( depth.n() ) {
            case 4:
                image_format_v = gl::RGB4;
                pixel_size_v = 12u;
                break;
            case 5:
                image_format_v = gl::RGB5;
                pixel_size_v = 15u;
                break;
            case 8:
                image_format_v = gl::RGB8;
                pixel_size_v = 24u;
                break;
            case 10:
                image_format_v = gl::RGB10;
                pixel_size_v = 30u;
                break;
            case 12:
                image_format_v = gl::RGB12;
                pixel_size_v = 36u;
                break;
            case 16:
                image_format_v = gl::RGB16;
                pixel_size_v = 48u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for triple channel normalized unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        
        uvec3 mask ( 0, 1, 2 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
        }
        channels_v = 3;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have four unsigned
     * normalized chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the green chanel.
     * \param a_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::unsigned_norm_4( RGBA const& depth,
                                           swizz4 const& r_src,
                                           swizz4 const& g_src,
                                           swizz4 const& b_src,
                                           swizz4 const& a_src )
    {
        switch ( depth.n() ) {
            case 2:
                image_format_v = gl::RGBA2;
                pixel_size_v = 8u;
                break;
            case 4:
                image_format_v = gl::RGBA4;
                pixel_size_v = 16u;
                break;
//             case 5:
//                 image_format_v = gl::RGBA5;
//                 pixel_size_v = 20u;
            case 8:
                image_format_v = gl::RGBA8;
                pixel_size_v = 32u;
                break;
            case 12:
                image_format_v = gl::RGBA12;
                pixel_size_v = 48u;
                break;
            case 16:
                image_format_v = gl::RGBA16;
                pixel_size_v = 64u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for quad channel normalized unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec4 mask ( 0, 1, 2, 3 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
            case 3:
                r_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
            case 3:
                g_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
            case 3:
                b_src_v = gl::ALPHA;
                break;
        }
        switch ( mask( a_src ) ) {
            case 0:
                a_src_v = gl::RED;
                break;
            case 1:
                a_src_v = gl::GREEN;
                break;
            case 2:
                a_src_v = gl::BLUE;
                break;
            case 3:
                a_src_v = gl::ALPHA;
                break;
        }
        channels_v = 4;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have one normalized
     * chanel at the given bit depth.
     * \param depth The bit depth of the chanel.
     */
    inline  texture_1D::settings&   texture_1D::settings::signed_norm_1( Rsn const& depth )
        {
            switch ( depth.n() ) {
                case 8:
                    image_format_v = gl::R8_SNORM;
                    pixel_size_v = 8u;
                    break;
                case 16:
                    image_format_v = gl::R16_SNORM;
                    pixel_size_v = 16u;
                    break;
                default:
                    std::string msg ( "Bit depth " );
                    msg += depth.n();
                    msg += " is illegal for single channel normalized signed integer image formats.";
                    throw std::invalid_argument( msg );
            }
            channels_v = 1;
            return *this;
        }
    /**
     * \brief Set the new one dimensional texture to have two normalized
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::signed_norm_2( RGsn const& depth,
                                           swizz2 const& r_src,
                                           swizz2 const& g_src  )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RG8_SNORM;
                pixel_size_v = 16u;
                break;
            case 16:
                image_format_v = gl::RG16_SNORM;
                pixel_size_v = 32u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for dual channel normalized signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        
        uvec2 mask ( 0, 1 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
        }
        channels_v = 2;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have three normalized
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::signed_norm_3( RGBsn const& depth,
                                         swizz3 const& r_src,
                                         swizz3 const& g_src,
                                         swizz3 const& b_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGB8_SNORM;
                pixel_size_v = 24u;
                break;
            case 16:
                image_format_v = gl::RGB16_SNORM;
                pixel_size_v = 48u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for triple channel normalized signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        
        uvec3 mask ( 0, 1, 2 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
        }
        channels_v = 3;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have four normalized
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     * \param a_src The source of the alpha chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::signed_norm_4( RGBAsn const& depth,
                                         swizz4 const& r_src,
                                         swizz4 const& g_src,
                                         swizz4 const& b_src,
                                         swizz4 const& a_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGBA8_SNORM;
                pixel_size_v = 32u;
                break;
            case 16:
                image_format_v = gl::RGBA16_SNORM;
                pixel_size_v = 64u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for quad channel normalized signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec4 mask ( 0, 1, 2, 3 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
            case 3:
                r_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
            case 3:
                g_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
            case 3:
                b_src_v = gl::ALPHA;
                break;
        }
        switch ( mask( a_src ) ) {
            case 0:
                a_src_v = gl::RED;
                break;
            case 1:
                a_src_v = gl::GREEN;
                break;
            case 2:
                a_src_v = gl::BLUE;
                break;
            case 3:
                a_src_v = gl::ALPHA;
                break;
        }
        channels_v = 4;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have one unsigned integer
     * chanel at the given bit depth.
     * \param depth The bit depth of the chanel.
     */
    inline  texture_1D::settings&   texture_1D::settings::unsigned_int_1( Rui const& depth )
        {
            switch ( depth.n() ) {
                case 8:
                    image_format_v = gl::R8UI;
                    pixel_size_v = 8u;
                    break;
                case 16:
                    image_format_v = gl::R16UI;
                    pixel_size_v = 16u;
                    break;
                case 32:
                    image_format_v = gl::R32UI;
                    pixel_size_v = 32u;
                    break;
                default:
                    std::string msg ( "Bit depth " );
                    msg += depth.n();
                    msg += " is illegal for single channel unsigned integer image formats.";
                    throw std::invalid_argument( msg );
            }
            channels_v = 1;
            return *this;
        }

    /**
     * \brief Set the new one dimensional texture to have two unsigned integer
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::unsigned_int_2( RGui const& depth,
                                           swizz2 const& r_src,
                                           swizz2 const& g_src  )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RG8UI;
                pixel_size_v = 16u;
                break;
            case 16:
                image_format_v = gl::RG16UI;
                pixel_size_v = 32u;
                break;
            case 32:
                image_format_v = gl::RG32UI;
                pixel_size_v = 64u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for dual channel unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec2 mask ( 0, 1 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
        }
        channels_v = 2;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have three unsigned
     * integer chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::unsigned_int_3( RGBui const& depth,
                                          swizz3 const& r_src,
                                          swizz3 const& g_src,
                                          swizz3 const& b_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGB8UI;
                pixel_size_v = 24u;
                break;
            case 16:
                image_format_v = gl::RGB16UI;
                pixel_size_v = 48u;
                break;
            case 32:
                image_format_v = gl::RGB32UI;
                pixel_size_v = 96u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for triple channel unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec3 mask ( 0, 1, 2 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
        }
        channels_v = 3;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have four unsigned integer
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the green chanel.
     * \param a_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::unsigned_int_4( RGBAui const& depth,
                                          swizz4 const& r_src,
                                          swizz4 const& g_src,
                                          swizz4 const& b_src,
                                          swizz4 const& a_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGBA8UI;
                pixel_size_v = 32u;
                break;
            case 16:
                image_format_v = gl::RGBA16UI;
                pixel_size_v = 64u;
                break;
            case 32:
                image_format_v = gl::RGBA32UI;
                pixel_size_v = 128u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for quad channel unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec4 mask ( 0, 1, 2, 3 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
            case 3:
                r_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
            case 3:
                g_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
            case 3:
                b_src_v = gl::ALPHA;
                break;
        }
        switch ( mask( a_src ) ) {
            case 0:
                a_src_v = gl::RED;
                break;
            case 1:
                a_src_v = gl::GREEN;
                break;
            case 2:
                a_src_v = gl::BLUE;
                break;
            case 3:
                a_src_v = gl::ALPHA;
                break;
        }
        channels_v = 4;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have one signed integer
     * chanel at the given bit depth.
     * \param depth The bit depth of the chanel.
     */
    inline  texture_1D::settings&   texture_1D::settings::signed_int_1( Ri const& depth )
        {
            switch ( depth.n() ) {
                case 8:
                    image_format_v = gl::R8I;
                    pixel_size_v = 8u;
                    break;
                case 16:
                    image_format_v = gl::R16I;
                    pixel_size_v = 16u;
                    break;
                case 32:
                    image_format_v = gl::R32I;
                    pixel_size_v = 32u;
                    break;
                default:
                    std::string msg ( "Bit depth " );
                    msg += depth.n();
                    msg += " is illegal for single channel signed integer image formats.";
                    throw std::invalid_argument( msg );
            }
            channels_v = 1;
            return *this;
        }
    /**
     * \brief Set the new one dimensional texture to have two signed integers
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::signed_int_2( RGi const& depth,
                                           swizz2 const& r_src,
                                           swizz2 const& g_src  )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RG8I;
                pixel_size_v = 16u;
                break;
            case 16:
                image_format_v = gl::RG16I;
                pixel_size_v = 32u;
                break;
            case 32:
                image_format_v = gl::RG32I;
                pixel_size_v = 64u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for dual channel signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec2 mask ( 0, 1 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
        }
        channels_v = 2;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have three signed integers
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::signed_int_3( RGBi const& depth,
                                        swizz3 const& r_src,
                                        swizz3 const& g_src,
                                        swizz3 const& b_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGB8I;
                pixel_size_v = 24u;
                break;
            case 16:
                image_format_v = gl::RGB16I;
                pixel_size_v = 48u;
                break;
            case 32:
                image_format_v = gl::RGB32I;
                pixel_size_v = 96u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for triple channel signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec3 mask ( 0, 1, 2 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
        }
        channels_v = 3;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have four signed integers
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the green chanel.
     * \param a_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::signed_int_4( RGBAi const& depth,
                                        swizz4 const& r_src,
                                        swizz4 const& g_src,
                                        swizz4 const& b_src,
                                        swizz4 const& a_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGBA8I;
                pixel_size_v = 32u;
                break;
            case 16:
                image_format_v = gl::RGBA16I;
                pixel_size_v = 64u;
                break;
            case 32:
                image_format_v = gl::RGBA32I;
                pixel_size_v = 128u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for quad channel signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec4 mask ( 0, 1, 2, 3 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
            case 3:
                r_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
            case 3:
                g_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
            case 3:
                b_src_v = gl::ALPHA;
                break;
        }
        switch ( mask( a_src ) ) {
            case 0:
                a_src_v = gl::RED;
                break;
            case 1:
                a_src_v = gl::GREEN;
                break;
            case 2:
                a_src_v = gl::BLUE;
                break;
            case 3:
                a_src_v = gl::ALPHA;
                break;
        }
        channels_v = 4;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have one floating point
     * chanel at the given bit depth.
     * \param depth The bit depth of the chanel.
     */
    inline  texture_1D::settings&   texture_1D::settings::floating_point_1( Rf const& depth )
        {
            switch ( depth.n() ) {
                case 16:
                    image_format_v = gl::R16F;
                    pixel_size_v = 16u;
                    break;
                case 32:
                    image_format_v = gl::R32F;
                    pixel_size_v = 32u;
                    break;
                default:
                    std::string msg ( "Bit depth " );
                    msg += depth.n();
                    msg += " is illegal for single channel floating point image formats.";
                    throw std::invalid_argument( msg );
            }
            channels_v = 1;
            return *this;
        }
    /**
     * \brief Set the new one dimensional texture to have two floating point
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::floating_point_2( RGf const& depth,
                                           swizz2 const& r_src,
                                           swizz2 const& g_src  )
    {
        switch ( depth.n() ) {
            case 16:
                image_format_v = gl::RG16F;
                pixel_size_v = 32u;
                break;
            case 32:
                image_format_v = gl::RG32F;
                pixel_size_v = 64u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for dual channel floating point image formats.";
                throw std::invalid_argument( msg );
        }
        uvec2 mask ( 0, 1 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
        }
        channels_v = 2;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have three floating point
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::floating_point_3( RGBf const& depth,
                                            swizz3 const& r_src,
                                            swizz3 const& g_src,
                                            swizz3 const& b_src  )
    {
        switch ( depth.n() ) {
            case 16:
                image_format_v = gl::RGB16F;
                pixel_size_v = 48u;
                break;
            case 32:
                image_format_v = gl::RGB32F;
                pixel_size_v = 96u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for triple channel floating point image formats.";
                throw std::invalid_argument( msg );
        }
        uvec3 mask ( 0, 1, 2 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
        }
        channels_v = 3;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have four floating point
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the green chanel.
     * \param a_src The source of the green chanel.
     */
    inline  texture_1D::settings&
    texture_1D::settings::floating_point_4( RGBAf const& depth,
                                            swizz4 const& r_src,
                                            swizz4 const& g_src,
                                            swizz4 const& b_src,
                                            swizz4 const& a_src )
    {
        switch ( depth.n() ) {
            case 16:
                image_format_v = gl::RGBA16F;
                pixel_size_v = 64u;
                break;
            case 32:
                image_format_v = gl::RGBA32F;
                pixel_size_v = 128u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for quad channel floating point image formats.";
                throw std::invalid_argument( msg );
        }
        uvec4 mask ( 0, 1, 2, 3 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
            case 3:
                r_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
            case 3:
                g_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
            case 3:
                b_src_v = gl::ALPHA;
                break;
        }
        switch ( mask( a_src ) ) {
            case 0:
                a_src_v = gl::RED;
                break;
            case 1:
                a_src_v = gl::GREEN;
                break;
            case 2:
                a_src_v = gl::BLUE;
                break;
            case 3:
                a_src_v = gl::ALPHA;
                break;
        }
        channels_v = 4;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have three chanels packed
     * into 8 bits.
     * 3 bits for Red and Green, and 2 bits for Blue.
     */
    inline  texture_1D::settings&  texture_1D::settings::packed_3channel_8bit()
    { image_format_v = gl::R3_G3_B2; pixel_size_v = 8u; return *this; }
    /**
     * \brief Set the new one dimensional texture to have four chanels packed
     * into 16 bits.
     * Five bits for Red, Green, and Blue, and one bit for Alpha.
     */
    inline  texture_1D::settings&  texture_1D::settings::packed_4channel_16bit()
    { image_format_v = gl::RGB5_A1; pixel_size_v = 16u; return *this; }
    /**
     * \brief Set the new one dimensional texture to have four chanels packed
     * into 32 bits.
     * Ten bits for Red, Green, and Blue, and two for Alpha.
     */
    inline  texture_1D::settings&  texture_1D::settings::packed_4channel_32bit()
    { image_format_v = gl::RGB10_A2; pixel_size_v = 32u; return *this; }
    /**
     * \brief Set the new one dimensional texture to have four chanels packed
     * into 32 bits.
     * Ten bits for Red, Green, and Blue, and two for Alpha. Unsigned.
     */
    inline  texture_1D::settings&  texture_1D::settings::packed_4channel_32bit_unsigned()
    { image_format_v = gl::RGB10_A2UI; pixel_size_v = 32u; return *this; }
    /**
     * \brief Set the new one dimensional texture to have three floating point
     * chanels packed into 32 bits.
     * Eleven bits for Red and Green, and ten for Blue.
     */
    inline  texture_1D::settings&  texture_1D::settings::packed_3channel_32bit_float()
    { image_format_v = gl::R11F_G11F_B10F; pixel_size_v = 32u; return *this; }
    /**
     * \brief Set the new one dimensional texture to have three floating point
     * chanels packed into 32 bits with a shared exponent.
     * Nine bits for Red, Green, Blue mantissa, then five bits for their shared
     * exponent. May not be supported as a renderable format, because WAT!?!
     * There amy be an approrpiate use for this (the OpenGL wiki mentions images
     * whose color channels all have, more or less, the same order of (binary)
     * magnitude when expressed as 9 bit floating point), but it is going to be
     * extremely specific and worse will need to be generated offline.
     */
    inline texture_1D::settings&
    texture_1D::settings::if_you_find_a_use_for_this_image_format_you_get_a_cookie()
    { image_format_v = gl::RGB9_E5; pixel_size_v = 32u; return *this; }
    /**
     * \brief Set the new one dimensional texture to use the sRGB
     * with eight bit chanels.
     * Eight bits for Red, Green, and Blue. Unsigned.
     */
    inline  texture_1D::settings&  texture_1D::settings::sRGB_8bit()
    { image_format_v = gl::SRGB8; pixel_size_v = 24u; return *this; }
    /**
     * \brief Set the new one dimensional texture to use the sRGB
     * with eight bit chanels.
     * Eight bits for Red, Green, and Blue, plus Alpha. Unsigned.
     */
    inline  texture_1D::settings&  texture_1D::settings::sRGBA_8bit()
    { image_format_v = gl::SRGB8_ALPHA8; pixel_size_v = 32u; return *this; }
    /**
     * \brief Set the new one dimensional texture's mipmapping range.
     * \param base The lowest level of mipmap
     * \param max The highest level of mipmap
     */
    inline  texture_1D::settings&
    texture_1D::settings::mipmap_range( size_t const base,
                                        size_t const max )
    {
        base_level_v = base;
        max_level_v = max;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture's sampling range.
     * \param base The lowest level of sampling
     * \param max The highest level of sampling
     */
    inline  texture_1D::settings&
    texture_1D::settings::sample_range( float const base,
                                        float const max )
    {
        base_lod_v = base;
        max_lod_v = max;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture's sampling bias.
     * The sampling bias is added to the calculated sample depth.
     * \param bias The sampling bias
     */
    inline  texture_1D::settings&
    texture_1D::settings::sample_bias( float const bias )
    {
        lod_bias_v = bias;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture's sample mimification filter.
     * \param min The minification filter
     */
    inline  texture_1D::settings&
    texture_1D::settings::sample_minification( min_filter_t const& min )
    { min_filter_v = min.val(); return *this; }
    /**
     * \brief Set the new one dimensional texture's sample magnification filter.
     * \param min The maggnification filter
     */
    inline  texture_1D::settings&
    texture_1D::settings::sample_magnification( mag_filter_t const& mag )
    { mag_filter_v = mag.val(); return *this; }
    /**
     * \brief Set the new one dimensional texture's wrap mode along the s-axis.
     * \param mode The wrap mode
     */
    inline  texture_1D::settings&
    texture_1D::settings::wrap_s( wrap_mode_t const& mode )
    { wrap_s_v = mode.val(); return *this; }
    /**
     * \brief Set the new one dimensional texture's wrap mode along the t-axis.
     * \param mode The wrap mode
     */
    inline  texture_1D::settings&
    texture_1D::settings::wrap_t( wrap_mode_t const& mode )
    { wrap_t_v = mode.val(); return *this; }
    /**
     * \brief Set the new one dimensional texture's comparison function for
     * accumulation.
     * \param func The comparison function
     */
    inline  texture_1D::settings&
    texture_1D::settings::comparison_function( comparison_function_t const& func )
    { compare_func_v = func.val(); return *this; }
    /**
     * \brief Set the new one dimensional texture's source file.
     * \param path The file path
     */
    inline texture_1D::settings&    texture_1D::settings::file( std::string const& path )
    { path_v = path; return *this; }
    /**
     * \class gfx::texture_2D texture.hpp "gCore/gScene/texture.hpp"
     * \brief Represents a two dimenstional texture.
     * Two dimensional textures are configured with the member class
     * \ref gfx::texture_2D::settings "settings". They consist of a two
     * dimensional grid of color information, which can be formatted in a large
     * number of ways.
     */
    class texture_2D {
    public:
        
        class settings {
        public:
            settings();
            settings&       dimensions( size_t const dw,
                                        size_t const dh );
            settings&       array( size_t const layers );
            settings&       unsigned_norm_1( R const& depth );
            settings&       unsigned_norm_2( RG const& depth,
                                             swizz2 const& r_src = r,
                                             swizz2 const& g_src = g );
            settings&       unsigned_norm_3( RGB const& depth,
                                             swizz3 const& r_src = r,
                                             swizz3 const& g_src = g,
                                             swizz3 const& b_src = b  );
            settings&       unsigned_norm_4( RGBA const& depth,
                                             swizz4 const& r_src = r,
                                             swizz4 const& g_src = g,
                                             swizz4 const& b_src = b,
                                             swizz4 const& a_src = a );
            settings&       signed_norm_1( Rsn const& depth );
            settings&       signed_norm_2( RGsn const& depth,
                                             swizz2 const& r_src = r,
                                             swizz2 const& g_src = g  );
            settings&       signed_norm_3( RGBsn const& depth,
                                             swizz3 const& r_src = r,
                                             swizz3 const& g_src = g,
                                             swizz3 const& b_src = b );
            settings&       signed_norm_4( RGBAsn const& depth,
                                             swizz4 const& r_src = r,
                                             swizz4 const& g_src = g,
                                             swizz4 const& b_src = b,
                                             swizz4 const& a_src = a );
            settings&       unsigned_int_1( Rui const& depth );
            settings&       unsigned_int_2( RGui const& depth,
                                             swizz2 const& r_src = r,
                                             swizz2 const& g_src = g  );
            settings&       unsigned_int_3( RGBui const& depth,
                                             swizz3 const& r_src = r,
                                             swizz3 const& g_src = g,
                                             swizz3 const& b_src = b );
            settings&       unsigned_int_4( RGBAui const& depth,
                                             swizz4 const& r_src = r,
                                             swizz4 const& g_src = g,
                                             swizz4 const& b_src = b,
                                             swizz4 const& a_src = a );
            settings&       signed_int_1( Ri const& depth );
            settings&       signed_int_2( RGi const& depth,
                                             swizz2 const& r_src = r,
                                             swizz2 const& g_src = g  );
            settings&       signed_int_3( RGBi const& depth,
                                             swizz3 const& r_src = r,
                                             swizz3 const& g_src = g,
                                             swizz3 const& b_src = b );
            settings&       signed_int_4( RGBAi const& depth,
                                             swizz4 const& r_src = r,
                                             swizz4 const& g_src = g,
                                             swizz4 const& b_src = b,
                                             swizz4 const& a_src = a );
            settings&       floating_point_1( Rf const& depth );
            settings&       floating_point_2( RGf const& depth,
                                             swizz2 const& r_src = r,
                                             swizz2 const& g_src = g  );
            settings&       floating_point_3( RGBf const& depth,
                                             swizz3 const& r_src = r,
                                             swizz3 const& g_src = g,
                                             swizz3 const& b_src = b );
            settings&       floating_point_4( RGBAf const& depth,
                                             swizz4 const& r_src = r,
                                             swizz4 const& g_src = g,
                                             swizz4 const& b_src = b,
                                             swizz4 const& a_src = a );
            settings&       packed_3channel_8bit();
            settings&       packed_4channel_16bit();
            settings&       packed_4channel_32bit();
            settings&       packed_4channel_32bit_unsigned();
            settings&       packed_3channel_32bit_float();
            settings&       if_you_find_a_use_for_this_image_format_you_get_a_cookie(); //No, seriously
            settings&       sRGB_8bit();
            settings&       sRGBA_8bit();
            settings&       mipmap_range( size_t const base,
                                          size_t const max );
            settings&       sample_range( float const base,
                                          float const max );
            settings&       sample_bias( float const bias );
            settings&       sample_minification( min_filter_t const& min );
            settings&       sample_magnification( mag_filter_t const& mag );
            settings&       wrap_s( wrap_mode_t const& mode );
            settings&       wrap_t( wrap_mode_t const& mode );
            settings&       comparison_function( comparison_function_t const& func );
            settings&       file( std::string const& path );
        private:
            size_t          dw_v;
            size_t          dh_v;
            bool            as_cube_v;
            bool            as_array_v;
            size_t          layers_v;
            GLuint          image_format_v;
            size_t          pixels_v;
            size_t          pixel_size_v;
            size_t          channels_v;
            size_t          base_level_v;
            size_t          max_level_v;
            float           base_lod_v;
            float           max_lod_v;
            float           lod_bias_v;
            GLint           min_filter_v;
            GLint           mag_filter_v;
            GLint           wrap_s_v;
            GLint           wrap_t_v;
            GLint           compare_func_v;
            GLint           r_src_v;
            GLint           g_src_v;
            GLint           b_src_v;
            GLint           a_src_v;
            std::string     path_v;
            friend          class texture_2D;
        };
                            texture_2D( settings const& set = settings() );
                            ~texture_2D();
        size_t              width() const;
        size_t              height() const;
        size_t              pixels() const;
        size_t              pixel_bits() const;
        void                file( std::string const& path );
        void                decode_file();
        void                load_data();
        void                use();
//         sub_tex_1D          get_sub_texture( size_t const w_start = 0,
//                                              size_t const w_end   = 0 );
    private:    
        
        GLuint              tex_ID;
        GLuint              target;
        size_t              width_v;
        size_t              height_v;
        size_t              pixels_v;
        size_t              pixel_bits_v;
        GLuint              image_format;
        std::string         path;
        
        unsigned char*      data;
        
        size_t              bytes();
    };
    /**
     * \brief Construct a new default two dimensional texture settings object.
     * The default settings for a one dimenstional texture are to have a
     * width of zero, no extra multi-texturing features, standard channel
     * soruces, and the cheapest interpolation and sampling filters. The
     * path is also empty.
     */
    inline texture_2D::settings::settings() :
                                    dw_v ( 0 ),
                                    dh_v ( 0 ),
                                    as_cube_v ( false ),
                                    as_array_v ( false ),
                                    layers_v ( 0 ),
                                    image_format_v ( 0 ),
                                    pixels_v ( 0 ),
                                    pixel_size_v ( 0 ),
                                    channels_v ( 1 ),
                                    base_level_v ( 0 ),
                                    max_level_v ( 0 ),
                                    base_lod_v ( 0.0f ),
                                    max_lod_v ( 0.0f ),
                                    lod_bias_v ( 0.0f ),
                                    min_filter_v ( gl::NEAREST ),
                                    mag_filter_v ( gl::NEAREST ),
                                    wrap_s_v ( gl::CLAMP_TO_EDGE ),
                                    wrap_t_v ( gl::CLAMP_TO_EDGE ),
                                    compare_func_v ( 0 ),
                                    r_src_v ( gl::RED ),
                                    g_src_v ( gl::GREEN ),
                                    b_src_v ( gl::BLUE ),
                                    a_src_v ( gl::ALPHA ),
                                    path_v ( "" ) {}
    /**
     * \brief Set the new two dimensional texture's dimension.
     * \param dw The new width of the two dimensional texture.
     * \param dh The new height of the two dimensional texture.
     */
    inline  texture_2D::settings&  texture_2D::settings::dimensions( size_t const dw,
                                                                     size_t const dh )
    {
        dw_v = dw;
        dh_v = dh;
        pixels_v = dw * dh; return *this; }
    /**
     * \brief Set the new two dimensional texture ot be an array of textures.
     * \param layers The number of one dimensional textures in the array.
     */
    inline  texture_2D::settings&  texture_2D::settings::array( size_t const layers )
    {
        as_array_v = true;
        layers_v = layers;
        return *this;
    }
     /**
     * \brief Set the new two dimensional texture to have one unsigned
     * normalized chanel at the given bit depth.
     * \param depth The bit depth of the chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::unsigned_norm_1( R const& depth )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::R8;
                pixel_size_v = 8u;
                break;
            case 16:
                image_format_v = gl::R16;
                pixel_size_v = 16u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for single channel normalized unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        channels_v = 1;
        
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have two unsigned
     * normalized chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::unsigned_norm_2( RG const& depth,
                                           swizz2 const& r_src,
                                           swizz2 const& g_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RG8;
                pixel_size_v = 16u;
                break;
            case 16:
                image_format_v = gl::RG16;
                pixel_size_v = 32u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for dual channel normalized unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec2 mask ( 0, 1 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
        }
        channels_v = 2;
        
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have three unsigned
     * normalized chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::unsigned_norm_3( RGB const& depth,
                                           swizz3 const& r_src,
                                           swizz3 const& g_src,
                                           swizz3 const& b_src )
    {
        switch ( depth.n() ) {
            case 4:
                image_format_v = gl::RGB4;
                pixel_size_v = 12u;
                break;
            case 5:
                image_format_v = gl::RGB5;
                pixel_size_v = 15u;
                break;
            case 8:
                image_format_v = gl::RGB8;
                pixel_size_v = 24u;
                break;
            case 10:
                image_format_v = gl::RGB10;
                pixel_size_v = 30u;
                break;
            case 12:
                image_format_v = gl::RGB12;
                pixel_size_v = 36u;
                break;
            case 16:
                image_format_v = gl::RGB16;
                pixel_size_v = 48u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for triple channel normalized unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        
        uvec3 mask ( 0, 1, 2 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
        }
        channels_v = 3;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have four unsigned
     * normalized chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     * \param a_src The source of the alpha chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::unsigned_norm_4( RGBA const& depth,
                                           swizz4 const& r_src,
                                           swizz4 const& g_src,
                                           swizz4 const& b_src,
                                           swizz4 const& a_src )
    {
        switch ( depth.n() ) {
            case 2:
                image_format_v = gl::RGBA2;
                pixel_size_v = 8u;
                break;
            case 4:
                image_format_v = gl::RGBA4;
                pixel_size_v = 16u;
                break;
//             case 5:
//                 image_format_v = gl::RGBA5;
//                 pixel_size_v = 20u;
            case 8:
                image_format_v = gl::RGBA8;
                pixel_size_v = 32u;
                break;
            case 12:
                image_format_v = gl::RGBA12;
                pixel_size_v = 48u;
                break;
            case 16:
                image_format_v = gl::RGBA16;
                pixel_size_v = 64u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for quad channel normalized unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec4 mask ( 0, 1, 2, 3 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
            case 3:
                r_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
            case 3:
                g_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
            case 3:
                b_src_v = gl::ALPHA;
                break;
        }
        switch ( mask( a_src ) ) {
            case 0:
                a_src_v = gl::RED;
                break;
            case 1:
                a_src_v = gl::GREEN;
                break;
            case 2:
                a_src_v = gl::BLUE;
                break;
            case 3:
                a_src_v = gl::ALPHA;
                break;
        }
        channels_v = 4;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have one normalized
     * chanel at the given bit depth.
     * \param depth The bit depth of the chanel.
     */
    inline  texture_2D::settings&   texture_2D::settings::signed_norm_1( Rsn const& depth )
        {
            switch ( depth.n() ) {
                case 8:
                    image_format_v = gl::R8_SNORM;
                    pixel_size_v = 8u;
                    break;
                case 16:
                    image_format_v = gl::R16_SNORM;
                    pixel_size_v = 16u;
                    break;
                default:
                    std::string msg ( "Bit depth " );
                    msg += depth.n();
                    msg += " is illegal for single channel normalized signed integer image formats.";
                    throw std::invalid_argument( msg );
            }
            channels_v = 1;
            return *this;
        }
    /**
     * \brief Set the new two dimensional texture to have two normalized
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::signed_norm_2( RGsn const& depth,
                                           swizz2 const& r_src,
                                           swizz2 const& g_src  )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RG8_SNORM;
                pixel_size_v = 16u;
                break;
            case 16:
                image_format_v = gl::RG16_SNORM;
                pixel_size_v = 32u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for dual channel normalized signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        
        uvec2 mask ( 0, 1 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
        }
        channels_v = 2;
        return *this;
    }
    /**
     * \brief Set the new one dimensional texture to have three normalized
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::signed_norm_3( RGBsn const& depth,
                                         swizz3 const& r_src,
                                         swizz3 const& g_src,
                                         swizz3 const& b_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGB8_SNORM;
                pixel_size_v = 24u;
                break;
            case 16:
                image_format_v = gl::RGB16_SNORM;
                pixel_size_v = 48u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for triple channel normalized signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        
        uvec3 mask ( 0, 1, 2 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
        }
        channels_v = 3;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have four normalized
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     * \param a_src The source of the alpha chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::signed_norm_4( RGBAsn const& depth,
                                         swizz4 const& r_src,
                                         swizz4 const& g_src,
                                         swizz4 const& b_src,
                                         swizz4 const& a_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGBA8_SNORM;
                pixel_size_v = 32u;
                break;
            case 16:
                image_format_v = gl::RGBA16_SNORM;
                pixel_size_v = 64u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for quad channel normalized signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec4 mask ( 0, 1, 2, 3 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
            case 3:
                r_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
            case 3:
                g_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
            case 3:
                b_src_v = gl::ALPHA;
                break;
        }
        switch ( mask( a_src ) ) {
            case 0:
                a_src_v = gl::RED;
                break;
            case 1:
                a_src_v = gl::GREEN;
                break;
            case 2:
                a_src_v = gl::BLUE;
                break;
            case 3:
                a_src_v = gl::ALPHA;
                break;
        }
        channels_v = 4;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have one unsigned integer
     * chanel at the given bit depth.
     * \param depth The bit depth of the chanel.
     */
    inline  texture_2D::settings&   texture_2D::settings::unsigned_int_1( Rui const& depth )
        {
            switch ( depth.n() ) {
                case 8:
                    image_format_v = gl::R8UI;
                    pixel_size_v = 8u;
                    break;
                case 16:
                    image_format_v = gl::R16UI;
                    pixel_size_v = 16u;
                    break;
                case 32:
                    image_format_v = gl::R32UI;
                    pixel_size_v = 32u;
                    break;
                default:
                    std::string msg ( "Bit depth " );
                    msg += depth.n();
                    msg += " is illegal for single channel unsigned integer image formats.";
                    throw std::invalid_argument( msg );
            }
            channels_v = 1;
            return *this;
        }
    /**
     * \brief Set the new two dimensional texture to have two unsigned integer
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::unsigned_int_2( RGui const& depth,
                                           swizz2 const& r_src,
                                           swizz2 const& g_src  )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RG8UI;
                pixel_size_v = 16u;
                break;
            case 16:
                image_format_v = gl::RG16UI;
                pixel_size_v = 32u;
                break;
            case 32:
                image_format_v = gl::RG32UI;
                pixel_size_v = 64u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for dual channel unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec2 mask ( 0, 1 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
        }
        channels_v = 2;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have three unsigned
     * integer chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::unsigned_int_3( RGBui const& depth,
                                          swizz3 const& r_src,
                                          swizz3 const& g_src,
                                          swizz3 const& b_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGB8UI;
                pixel_size_v = 24u;
                break;
            case 16:
                image_format_v = gl::RGB16UI;
                pixel_size_v = 48u;
                break;
            case 32:
                image_format_v = gl::RGB32UI;
                pixel_size_v = 96u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for triple channel unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec3 mask ( 0, 1, 2 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
        }
        channels_v = 3;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have four unsigned integer
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     * \param a_src The source of the alpha chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::unsigned_int_4( RGBAui const& depth,
                                          swizz4 const& r_src,
                                          swizz4 const& g_src,
                                          swizz4 const& b_src,
                                          swizz4 const& a_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGBA8UI;
                pixel_size_v = 32u;
                break;
            case 16:
                image_format_v = gl::RGBA16UI;
                pixel_size_v = 64u;
                break;
            case 32:
                image_format_v = gl::RGBA32UI;
                pixel_size_v = 128u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for quad channel unsigned integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec4 mask ( 0, 1, 2, 3 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
            case 3:
                r_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
            case 3:
                g_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
            case 3:
                b_src_v = gl::ALPHA;
                break;
        }
        switch ( mask( a_src ) ) {
            case 0:
                a_src_v = gl::RED;
                break;
            case 1:
                a_src_v = gl::GREEN;
                break;
            case 2:
                a_src_v = gl::BLUE;
                break;
            case 3:
                a_src_v = gl::ALPHA;
                break;
        }
        channels_v = 4;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have one signed integer
     * chanel at the given bit depth.
     * \param depth The bit depth of the chanel.
     */
    inline  texture_2D::settings&   texture_2D::settings::signed_int_1( Ri const& depth )
        {
            switch ( depth.n() ) {
                case 8:
                    image_format_v = gl::R8I;
                    pixel_size_v = 8u;
                    break;
                case 16:
                    image_format_v = gl::R16I;
                    pixel_size_v = 16u;
                    break;
                case 32:
                    image_format_v = gl::R32I;
                    pixel_size_v = 32u;
                    break;
                default:
                    std::string msg ( "Bit depth " );
                    msg += depth.n();
                    msg += " is illegal for single channel signed integer image formats.";
                    throw std::invalid_argument( msg );
            }
            channels_v = 1;
            return *this;
        }
    /**
     * \brief Set the new two dimensional texture to have two signed integers
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::signed_int_2( RGi const& depth,
                                           swizz2 const& r_src,
                                           swizz2 const& g_src  )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RG8I;
                pixel_size_v = 16u;
                break;
            case 16:
                image_format_v = gl::RG16I;
                pixel_size_v = 32u;
                break;
            case 32:
                image_format_v = gl::RG32I;
                pixel_size_v = 64u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for dual channel signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec2 mask ( 0, 1 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
        }
        channels_v = 2;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have three signed integers
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::signed_int_3( RGBi const& depth,
                                        swizz3 const& r_src,
                                        swizz3 const& g_src,
                                        swizz3 const& b_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGB8I;
                pixel_size_v = 24u;
                break;
            case 16:
                image_format_v = gl::RGB16I;
                pixel_size_v = 48u;
                break;
            case 32:
                image_format_v = gl::RGB32I;
                pixel_size_v = 96u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for triple channel signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec3 mask ( 0, 1, 2 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
        }
        channels_v = 3;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have four signed integers
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     * \param a_src The source of the alpha chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::signed_int_4( RGBAi const& depth,
                                        swizz4 const& r_src,
                                        swizz4 const& g_src,
                                        swizz4 const& b_src,
                                        swizz4 const& a_src )
    {
        switch ( depth.n() ) {
            case 8:
                image_format_v = gl::RGBA8I;
                pixel_size_v = 32u;
                break;
            case 16:
                image_format_v = gl::RGBA16I;
                pixel_size_v = 64u;
                break;
            case 32:
                image_format_v = gl::RGBA32I;
                pixel_size_v = 128u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for quad channel signed integer image formats.";
                throw std::invalid_argument( msg );
        }
        uvec4 mask ( 0, 1, 2, 3 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
            case 3:
                r_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
            case 3:
                g_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
            case 3:
                b_src_v = gl::ALPHA;
                break;
        }
        switch ( mask( a_src ) ) {
            case 0:
                a_src_v = gl::RED;
                break;
            case 1:
                a_src_v = gl::GREEN;
                break;
            case 2:
                a_src_v = gl::BLUE;
                break;
            case 3:
                a_src_v = gl::ALPHA;
                break;
        }
        channels_v = 4;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have one floating point
     * chanel at the given bit depth.
     * \param depth The bit depth of the chanel.
     */
    inline  texture_2D::settings&   texture_2D::settings::floating_point_1( Rf const& depth )
        {
            switch ( depth.n() ) {
                case 16:
                    image_format_v = gl::R16F;
                    pixel_size_v = 16u;
                    break;
                case 32:
                    image_format_v = gl::R32F;
                    pixel_size_v = 32u;
                    break;
                default:
                    std::string msg ( "Bit depth " );
                    msg += depth.n();
                    msg += " is illegal for single channel floating point image formats.";
                    throw std::invalid_argument( msg );
            }
            channels_v = 1;
            return *this;
        }
    /**
     * \brief Set the new two dimensional texture to have two floating point
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::floating_point_2( RGf const& depth,
                                           swizz2 const& r_src,
                                           swizz2 const& g_src  )
    {
        switch ( depth.n() ) {
            case 16:
                image_format_v = gl::RG16F;
                pixel_size_v = 32u;
                break;
            case 32:
                image_format_v = gl::RG32F;
                pixel_size_v = 64u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for dual channel floating point image formats.";
                throw std::invalid_argument( msg );
        }
        uvec2 mask ( 0, 1 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
        }
        channels_v = 2;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have three floating point
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::floating_point_3( RGBf const& depth,
                                            swizz3 const& r_src,
                                            swizz3 const& g_src,
                                            swizz3 const& b_src  )
    {
        switch ( depth.n() ) {
            case 16:
                image_format_v = gl::RGB16F;
                pixel_size_v = 48u;
                break;
            case 32:
                image_format_v = gl::RGB32F;
                pixel_size_v = 96u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for triple channel floating point image formats.";
                throw std::invalid_argument( msg );
        }
        uvec3 mask ( 0, 1, 2 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
        }
        channels_v = 3;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have four floating point
     * chanels at the given bit depth.
     * \param depth The bit depth of the chanel.
     * \param r_src The source of the red chanel.
     * \param g_src The source of the green chanel.
     * \param b_src The source of the blue chanel.
     * \param a_src The source of the alpha chanel.
     */
    inline  texture_2D::settings&
    texture_2D::settings::floating_point_4( RGBAf const& depth,
                                            swizz4 const& r_src,
                                            swizz4 const& g_src,
                                            swizz4 const& b_src,
                                            swizz4 const& a_src )
    {
        switch ( depth.n() ) {
            case 16:
                image_format_v = gl::RGBA16F;
                pixel_size_v = 64u;
                break;
            case 32:
                image_format_v = gl::RGBA32F;
                pixel_size_v = 128u;
                break;
            default:
                std::string msg ( "Bit depth " );
                msg += depth.n();
                msg += " is illegal for quad channel floating point image formats.";
                throw std::invalid_argument( msg );
        }
        uvec4 mask ( 0, 1, 2, 3 );
        switch ( mask( r_src ) ) {
            case 0:
                r_src_v = gl::RED;
                break;
            case 1:
                r_src_v = gl::GREEN;
                break;
            case 2:
                r_src_v = gl::BLUE;
                break;
            case 3:
                r_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( g_src ) ) {
            case 0:
                g_src_v = gl::RED;
                break;
            case 1:
                g_src_v = gl::GREEN;
                break;
            case 2:
                g_src_v = gl::BLUE;
                break;
            case 3:
                g_src_v = gl::ALPHA;
                break;
        }
        
        switch ( mask( b_src ) ) {
            case 0:
                b_src_v = gl::RED;
                break;
            case 1:
                b_src_v = gl::GREEN;
                break;
            case 2:
                b_src_v = gl::BLUE;
                break;
            case 3:
                b_src_v = gl::ALPHA;
                break;
        }
        switch ( mask( a_src ) ) {
            case 0:
                a_src_v = gl::RED;
                break;
            case 1:
                a_src_v = gl::GREEN;
                break;
            case 2:
                a_src_v = gl::BLUE;
                break;
            case 3:
                a_src_v = gl::ALPHA;
                break;
        }
        channels_v = 4;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture to have three chanels packed
     * into 8 bits.
     * 3 bits for Red and Green, and 2 bits for Blue.
     */
    inline  texture_2D::settings&  texture_2D::settings::packed_3channel_8bit()
    { image_format_v = gl::R3_G3_B2; pixel_size_v = 8u; return *this; }
    /**
     * \brief Set the new two dimensional texture to have four chanels packed
     * into 16 bits.
     * Five bits for Red, Green, and Blue, and one bit for Alpha.
     */
    inline  texture_2D::settings&  texture_2D::settings::packed_4channel_16bit()
    { image_format_v = gl::RGB5_A1; pixel_size_v = 16u; return *this; }
    /**
     * \brief Set the new two dimensional texture to have four chanels packed
     * into 32 bits.
     * Ten bits for Red, Green, and Blue, and two for Alpha.
     */
    inline  texture_2D::settings&  texture_2D::settings::packed_4channel_32bit()
    { image_format_v = gl::RGB10_A2; pixel_size_v = 32u; return *this; }
    /**
     * \brief Set the new two dimensional texture to have four chanels packed
     * into 32 bits.
     * Ten bits for Red, Green, and Blue, and two for Alpha. Unsigned.
     */
    inline  texture_2D::settings&  texture_2D::settings::packed_4channel_32bit_unsigned()
    { image_format_v = gl::RGB10_A2UI; pixel_size_v = 32u; return *this; }
    /**
     * \brief Set the new two dimensional texture to have three floating point
     * chanels packed into 32 bits.
     * Eleven bits for Red and Green, and ten for Blue.
     */
    inline  texture_2D::settings&  texture_2D::settings::packed_3channel_32bit_float()
    { image_format_v = gl::R11F_G11F_B10F; pixel_size_v = 32u; return *this; }
    /**
     * \brief Set the new two dimensional texture to have three floating point
     * chanels packed into 32 bits with a shared exponent.
     * Nine bits for Red, Green, Blue mantissa, then five bits for their shared
     * exponent. May not be supported as a renderable format, because WAT!?!
     * There amy be an approrpiate use for this (the OpenGL wiki mentions images
     * whose color channels all have, more or less, the same order of (binary)
     * magnitude when expressed as 9 bit floating point), but it is going to be
     * extremely specific and worse will need to be generated offline.
     */
    inline texture_2D::settings&
    texture_2D::settings::if_you_find_a_use_for_this_image_format_you_get_a_cookie()
    { image_format_v = gl::RGB9_E5; pixel_size_v = 32u; return *this; }
    /**
     * \brief Set the new two dimensional texture to use the sRGB
     * with eight bit chanels.
     * Eight bits for Red, Green, and Blue. Unsigned.
     */
    inline  texture_2D::settings&  texture_2D::settings::sRGB_8bit()
    { image_format_v = gl::SRGB8; pixel_size_v = 24u; return *this; }
    /**
     * \brief Set the new two dimensional texture to use the sRGB
     * with eight bit chanels.
     * Eight bits for Red, Green, and Blue, plus Alpha. Unsigned.
     */
    inline  texture_2D::settings&  texture_2D::settings::sRGBA_8bit()
    { image_format_v = gl::SRGB8_ALPHA8; pixel_size_v = 32u; return *this; }
    /**
     * \brief Set the new two dimensional texture's mipmapping range.
     * \param base The lowest level of mipmap
     * \param max The highest level of mipmap
     */
    inline  texture_2D::settings&
    texture_2D::settings::mipmap_range( size_t const base,
                                        size_t const max )
    {
        base_level_v = base;
        max_level_v = max;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture's sampling range.
     * \param base The lowest level of sampling
     * \param max The highest level of sampling
     */
    inline  texture_2D::settings&
    texture_2D::settings::sample_range( float const base,
                                        float const max )
    {
        base_lod_v = base;
        max_lod_v = max;
        return *this;
    }
     /**
     * \brief Set the new two dimensional texture's sampling bias.
     * The sampling bias is added to the calculated sample depth.
     * \param bias The sampling bias
     */
    inline  texture_2D::settings&
    texture_2D::settings::sample_bias( float const bias )
    {
        lod_bias_v = bias;
        return *this;
    }
    /**
     * \brief Set the new two dimensional texture's sample mimification filter.
     * \param min The minification filter
     */
    inline  texture_2D::settings&
    texture_2D::settings::sample_minification( min_filter_t const& min )
    { min_filter_v = min.val(); return *this; }
    /**
     * \brief Set the new two dimensional texture's sample magnification filter.
     * \param min The maggnification filter
     */
    inline  texture_2D::settings&
    texture_2D::settings::sample_magnification( mag_filter_t const& mag )
    { mag_filter_v = mag.val(); return *this; }
    /**
     * \brief Set the new two dimensional texture's wrap mode along the s-axis.
     * \param mode The wrap mode
     */
    inline  texture_2D::settings&
    texture_2D::settings::wrap_s( wrap_mode_t const& mode )
    { wrap_s_v = mode.val(); return *this; }
    /**
     * \brief Set the new two dimensional texture's wrap mode along the t-axis.
     * \param mode The wrap mode
     */
    inline  texture_2D::settings&
    texture_2D::settings::wrap_t( wrap_mode_t const& mode )
    { wrap_t_v = mode.val(); return *this; }
    /**
     * \brief Set the new two dimensional texture's comparison function for
     * accumulation.
     * \param func The comparison function
     */
    inline  texture_2D::settings&
    texture_2D::settings::comparison_function( comparison_function_t const& func )
    { compare_func_v = func.val(); return *this; }
    /**
     * \brief Set the new two dimensional texture's source file.
     * \param path The file path
     */
    inline texture_2D::settings&    texture_2D::settings::file( std::string const& path )
    { path_v = path; return *this; }    
    

//     class texture_1D {
//     public:
//         
//         class settings {
//         public:
//             settings();
//             settings&       one_dimensional( size_t const dw );
//             settings&       two_dimensional( size_t const dw,
//                                              size_t const dh );
//             settings&       three_dimensional( size_t const dw,
//                                                size_t const dh,
//                                                size_t const dd );
//             settings&       cube_map( size_t const de );
//             settings&       multisampled();
//             settings&       from_buffer();
//             settings&       array( size_t const layers );
//             settings&       unsigned_norm_1( R const& depth );
//             settings&       unsigned_norm_2( RG const& depth );
//             settings&       unsigned_norm_3( RGB const& depth );
//             settings&       unsigned_norm_4( RGBA const& depth );
//             settings&       signed_norm_1( Rsn const& depth );
//             settings&       signed_norm_2( RGsn const& depth );
//             settings&       signed_norm_3( RGBsn const& depth );
//             settings&       signed_norm_4( RGBAsn const& depth );
//             settings&       unsigned_int_1( Rui const& depth );
//             settings&       unsigned_int_2( RGui const& depth );
//             settings&       unsigned_int_3( RGBui const& depth );
//             settings&       unsigned_int_4( RGBAui const& depth );
//             settings&       signed_int_1( Ri const& depth );
//             settings&       signed_int_2( RGi const& depth );
//             settings&       signed_int_3( RGBi const& depth );
//             settings&       signed_int_4( RGBAi const& depth );
//             settings&       floating_point_1( Rf const& depth );
//             settings&       floating_point_2( RGf const& depth );
//             settings&       floating_point_3( RGBf const& depth );
//             settings&       floating_point_4( RGBAf const& depth );
//             settings&       packed_3channel_8bit();
//             settings&       packed_4channel_16bit();
//             settings&       packed_4channel_32bit();
//             settings&       packed_4channel_32bit_unsigned();
//             settings&       packed_3channel_32bit_float();
//             settings&       if_you_find_a_use_for_this_image_format_you_get_a_cookie(); //No, seriously
//             settings&       sRGB_8bit();
//             settings&       sRGBA_8bit();            
//         private:
//             size_t      dw_v;
//             size_t      dh_v;
//             size_t      dd_v;
//             bool        as_cube_v;
//             bool        as_array;
//             size_t      layers_v;
//             bool        from_buffer_v;
//             bool        multisampled_v;
//             GLuint      image_format_v;
//         };
//                             texture( settings const& set );
//         sub_texture         get_sub_texture( size_t const w_start = 0,
//                                              size_t const w_end   = 0,
//                                              size_t const h_start = 0,
//                                              size_t const h_end   = 0,
//                                              size_t const d_start = 0,
//                                              size_t const d_end   = 0  );
//     private:    
//         
//         GLuint              target;
//         uvec3               dim;
//         GLuint              image_format;
//         pixel_array*        pixels;
//     };
// 
// inline texture::settings::settings() :
//                           dw_v ( 1 ),
//                           dh_v ( 0 ),
//                           dd_v ( 0 ),
//                           as_cube_v ( false ),
//                           as_array_v ( false ),
//                           layers_v ( 0 ),
//                           from_buffer_v ( false ) {}
//                     
// 
// 
// inline  texture::settings&  texture::settings::two_dimensional( size_t const dw,
//                                                                 size_t const dh )
// {
//     dw_v = dw;
//     dh_v = dh;
//     return *this;
// }
// 
// inline  texture::settings&  texture::settings::three_dimensional( size_t const dw,
//                                                                   size_t const dh,
//                                                                   size_t const dd )
// {
//     dw_v = dw;
//     dh_v = dh;
//     dd_v = dd;
//     return *this;
// }
//                     
// inline  texture::settings&  texture::settings::cube_map( size_t const de )
// {
//     as_cube_v = true;
//     dw_v = de;
//     dh_v = 0;
//     dd_v = 0;
//     return *this;
// }
// 
// inline  texture::settings&  texture::settings::multisampled()
// {
//     multisampled_v = true;
//     return *this;
// }
// 
// 
// 
// inline  texture::settings&  texture::settings::array( size_t const layers )
// {
//     as_array_v = true;
//     layers_v = layers;
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::unsigned_norm_1( R const& depth )
//     {
//         switch ( depth.n() ) {
//             case 8:
//                 image_format_v = gl::R8;
//             case 16:
//                 image_format_v = gl::R16;
//             default:
//                 std::string msg ( "Bit depth " );
//                 msg += depth.n();
//                 msg += " is illegal for single channel normalized unsigned integer image formats.";
//                 throw std::invalid_argument( msg );
//         }
//         return *this;
//     }
// 
// 
// inline  texture::settings&       texture::settings::unsigned_norm_2( RG const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RG8;
//         case 16:
//             image_format_v = gl::RG16;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for dual channel normalized unsigned integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::unsigned_norm_3( RGB const& depth )
// {
//     switch ( depth.n() ) {
//         case 4:
//             image_format_v = gl::RGB4;
//         case 5:
//             image_format_v = gl::RGB5;
//         case 8:
//             image_format_v = gl::RGB8;
//         case 10:
//             image_format_v = gl::RGB10;
//         case 12:
//             image_format_v = gl::RGB12;
//         case 16:
//             image_format_v = gl::RGB16;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for triple channel normalized unsigned integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::unsigned_norm_4( RGBA const& depth )
// {
//     switch ( depth.n() ) {
//         case 2:
//             image_format_v = gl::RGBA2;
//         case 4:
//             image_format_v = gl::RGBA4;
//         case 5:
//             image_format_v = gl::RGBA5;
//         case 8:
//             image_format_v = gl::RGBA8;
//         case 12:
//             image_format_v = gl::RGBA12;
//         case 16:
//             image_format_v = gl::RGBA16;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for quad channel normalized unsigned integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&   texture::settings::signed_norm_1( Rsn const& depth )
//     {
//         switch ( depth.n() ) {
//             case 8:
//                 image_format_v = gl::R8_SNORM;
//             case 16:
//                 image_format_v = gl::R16_SNORM;
//             default:
//                 std::string msg ( "Bit depth " );
//                 msg += depth.n();
//                 msg += " is illegal for single channel normalized signed integer image formats.";
//                 throw std::invalid_argument( msg );
//         }
//         return *this;
//     }
// 
// inline  texture::settings&       texture::settings::signed_norm_2( RGsn const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RG8_SNORM;
//         case 16:
//             image_format_v = gl::RG16_SNORM;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for dual channel normalized signed integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::signed_norm_3( RGBsn const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RGB8_SNORM;
//         case 16:
//             image_format_v = gl::RGB16_SNORM;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for triple channel normalized signed integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::signed_norm_4( RGBAsn const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RGBA8_SNORM;
//         case 16:
//             image_format_v = gl::RGBA16_SNORM;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for quad channel normalized signed integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&   texture::settings::unsigned_int_1( Ru const& depth )
//     {
//         switch ( depth.n() ) {
//             case 8:
//                 image_format_v = gl::R8UI;
//             case 16:
//                 image_format_v = gl::R16UI;
//             case 32:
//                 image_format_v = gl::R32UI;
//             default:
//                 std::string msg ( "Bit depth " );
//                 msg += depth.n();
//                 msg += " is illegal for single channel unsigned integer image formats.";
//                 throw std::invalid_argument( msg );
//         }
//         return *this;
//     }
// 
// inline  texture::settings&       texture::settings::unsigned_int_2( RGu const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RG8UI;
//         case 16:
//             image_format_v = gl::RG16UI;
//         case 32:
//             image_format_v = gl::RG32UI;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for dual channel unsigned integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::unsigned_int_3( RGBu const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RGB8UI;
//         case 16:
//             image_format_v = gl::RGB16UI;
//         case 32:
//             image_format_v = gl::RGB32UI;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for triple channel unsigned integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::unsigned_int_4( RGBAu const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RGBA8UI;
//         case 16:
//             image_format_v = gl::RGBA16UI;
//         case 32:
//             image_format_v = gl::RGBA32UI;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for quad channel unsigned integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&   texture::settings::signed_int_1( Ri const& depth )
//     {
//         switch ( depth.n() ) {
//             case 8:
//                 image_format_v = gl::R8I;
//             case 16:
//                 image_format_v = gl::R16I;
//             case 32:
//                 image_format_v = gl::R32I;
//             default:
//                 std::string msg ( "Bit depth " );
//                 msg += depth.n();
//                 msg += " is illegal for single channel signed integer image formats.";
//                 throw std::invalid_argument( msg );
//         }
//         return *this;
//     }
// 
// inline  texture::settings&       texture::settings::signed_int_2( RGi const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RG8I;
//         case 16:
//             image_format_v = gl::RG16I;
//         case 32:
//             image_format_v = gl::RG32I;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for dual channel signed integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::signed_int_3( RGBi const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RGB8I;
//         case 16:
//             image_format_v = gl::RGB16I;
//         case 32:
//             image_format_v = gl::RGB32I;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for triple channel signed integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::signed_int_4( RGBAi const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RGBA8I;
//         case 16:
//             image_format_v = gl::RGBA16I;
//         case 32:
//             image_format_v = gl::RGBA32I;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for quad channel signed integer image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&   texture::settings::floating_point_1( Rf const& depth )
//     {
//         switch ( depth.n() ) {
//             case 8:
//                 image_format_v = gl::R8F;
//             case 16:
//                 image_format_v = gl::R16F;
//             case 32:
//                 image_format_v = gl::R32F;
//             default:
//                 std::string msg ( "Bit depth " );
//                 msg += depth.n();
//                 msg += " is illegal for single channel floating point image formats.";
//                 throw std::invalid_argument( msg );
//         }
//         return *this;
//     }
// 
// inline  texture::settings&       texture::settings::floating_point_2( RGf const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RG8F;
//         case 16:
//             image_format_v = gl::RG16F;
//         case 32:
//             image_format_v = gl::RG32F;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for dual channel floating point image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::floating_point_3( RGBf const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RGB8F;
//         case 16:
//             image_format_v = gl::RGB16F;
//         case 32:
//             image_format_v = gl::RGB32F;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for triple channel floating point image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&       texture::settings::floating_point_4( RGBAf const& depth )
// {
//     switch ( depth.n() ) {
//         case 8:
//             image_format_v = gl::RGBA8F;
//         case 16:
//             image_format_v = gl::RGBA16F;
//         case 32:
//             image_format_v = gl::RGBA32F;
//         default:
//             std::string msg ( "Bit depth " );
//             msg += depth.n();
//             msg += " is illegal for quad channel floating point image formats.";
//             throw std::invalid_argument( msg );
//     }
//     return *this;
// }
// 
// inline  texture::settings&  texture::settings::packed_3channel_8bit()
// { image_format_v = gl::R3_G3_B2; return *this; }
// 
// inline  texture::settings&  texture::settings::packed_4channel_16bit()
// { image_format_v = gl::RGB5_A1; return *this; }
// 
// inline  texture::settings&  texture::settings::packed_4channel_32bit()
// { image_format_v = gl::RGB10_A2; return *this; }
// 
// inline  texture::settings&  texture::settings::packed_4channel_32bit_unsigned()
// { image_format_v = gl::RGB10_A2UI; return *this; }
// 
// inline  texture::settings&  texture::settings::packed_4channel_32bit_float()
// { image_format_v = gl::R11F_G11F_B10F; return *this; }
//     
// inline texture::settings&
// texture::settings::if_you_find_a_use_for_this_image_format_you_get_a_cookie()
// { image_format_v = gl::RGB9_E5; return *this; }
// 
// inline  texture::settings&  texture::settings::sRGB_8bit()
// { image_format_v = gl::SRGB8; return *this; }
// 
// inline  texture::settings&  texture::settings::sRGBA_8bit()
// { image_format_v = gl::SRGB8_ALPHA8; return *this; }

}
#endif