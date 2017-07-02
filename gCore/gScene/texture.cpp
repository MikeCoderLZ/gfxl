#include <FreeImage.h>
#include "texture.hpp"


namespace gfx {
    
//     struct pixel_RGBA2 {
//         uint8_t red : 2;
//         uint8_t green : 2;
//         uint8_t blue : 2;
//         uint8_t alpha : 2;
//     };
    
//     struct pixel_RGBA4 {
//         uint16_t red : 4;
//         uint16_t green : 4;
//         uint16_t blue : 4;
//         uint16_t alpha : 4;
//     };
//     
//     struct pixel_RGB4 {
//         uint16_t red : 4;
//         uint16_t green : 4;
//         uint16_t blue : 4;
//     };
//     
//     struct pixel_RGB5 {
//         uint16_t red : 5;
//         uint16_t green : 5;
//         uint16_t blue : 5;
//     };
//     
//     struct pixel_RGBA5 {
//         uint32_t red : 5;
//         uint32_t green : 5;
//         uint32_t blue : 5;
//         uint32_t alpha : 5;
//     };
// 
//     struct pixel_R8 {
//         uint8_t red;
//     };
//     
//     struct pixel_RG8 {
//         uint8_t red;
//         uint8_t green;
//     };
//     
//     struct pixel_RGB8 {
//         uint8_t red;
//         uint8_t green;
//         uint8_t blue;
//     };
//     
//     struct pixel_RGBA8 {
//         uint8_t red;
//         uint8_t green;
//         uint8_t blue;
//         uint8_t alpha;
//     };
//     
//     struct pixel_R8s {
//         int8_t red;
//     };
//     
//     struct pixel_RG8s {
//         int8_t red;
//         int8_t green;
//     };
//     
//     struct pixel_RGB8s {
//         int8_t red;
//         int8_t green;
//         int8_t blue;
//     };
//     
//     struct pixel_RGBA8s {
//         int8_t red;
//         int8_t green;
//         int8_t blue;
//         int8_t alpha;
//     };
// 
//     struct pixel_RGB10 {
//         uint32_t red : 10;
//         uint32_t green : 10;
//         uint32_t blue : 10;
//     };
//     
//     struct pixel_RGB12 {
//         unsigned int red : 12;
//         unsigned int green : 12;
//         unsigned int blue : 12;
//     };
//     
//     struct pixel_RGBA12 {
//         unsigned int red : 12;
//         unsigned int green : 12;
//         unsigned int blue : 12;
//         unsigned int alpha : 12;
//     };
//     
//     struct pixel_R16 {
//         uint16_t red;
//     };
//     
//     struct pixel_RG16 {
//         uint16_t red;
//         uint16_t green;
//     };
//     
//     struct pixel_RGB16 {
//         uint16_t red;
//         uint16_t green;
//         uint16_t blue;
//     };
//     
//     struct pixel_RGBA16 {
//         uint16_t red;
//         uint16_t green;
//         uint16_t blue;
//         uint16_t alpha;
//     };
//     
//     struct pixel_R16s {
//         int16_t red;
//     };
//     
//     struct pixel_RG16s {
//         int16_t red;
//         int16_t green;
//     };
//     
//     struct pixel_RGB16s {
//         int16_t red;
//         int16_t green;
//         int16_t blue;
//     };
//     
//     struct pixel_RGBA16s {
//         int16_t red;
//         int16_t green;
//         int16_t blue;
//         int16_t alpha;
//     };
//     
//     struct pixel_R32 {
//         uint32_t red;
//     };
//     
//     struct pixel_RG32 {
//         uint32_t red;
//         uint32_t green;
//     };
//     
//     struct pixel_RGB32 {
//         uint32_t red;
//         uint32_t green;
//         uint32_t blue;
//     };
//     
//     struct pixel_RGBA32 {
//         uint32_t red;
//         uint32_t green;
//         uint32_t blue;
//         uint32_t alpha;
//     };
//     
//     struct pixel_R32s {
//         int32_t red;
//     };
//     
//     struct pixel_RG32s {
//         int32_t red;
//         int32_t green;
//     };
//     
//     struct pixel_RGB32s {
//         int32_t red;
//         int32_t green;
//         int32_t blue;
//     };
//     
//     struct pixel_RGBA32s {
//         int32_t red;
//         int32_t green;
//         int32_t blue;
//         int32_t alpha;
//     };
//     
//     struct pixel_R32f {
//         float red;
//     };
//     
//     struct pixel_RG32f {
//         float red;
//         float green;
//     };
//     
//     struct pixel_RGB32f {
//         float red;
//         float green;
//         float blue;
//     };
//     
//     struct pixel_RGBA32f {
//         float red;
//         float green;
//         float blue;
//         float alpha;
//     };
//     
//     struct pixel_R16f {
//         union {
//             struct {
//                 uint16_t sign : 1;
//                 uint16_t mantissa : 10;
//                 uint16_t exponent : 5;
//             };
//             uint16_t chunk;
//         } red;
//     };
//     
//     struct pixel_RG16f {
//         union {
//             struct {
//                 uint16_t sign : 1;
//                 uint16_t mantissa : 10;
//                 uint16_t exponent : 5;
//             };
//             uint16_t chunk;
//         } red;
//         union {
//             struct {
//                 uint16_t sign : 1;
//                 uint16_t mantissa : 10;
//                 uint16_t exponent : 5;
//             };
//             uint16_t chunk;
//         } green;
//     };
//     
//     struct pixel_RGB16f {
//         union {
//             struct {
//                 uint16_t sign : 1;
//                 uint16_t mantissa : 10;
//                 uint16_t exponent : 5;
//             };
//             uint16_t chunk;
//         } red;
//         union {
//             struct {
//                 uint16_t sign : 1;
//                 uint16_t mantissa : 10;
//                 uint16_t exponent : 5;
//             };
//             uint16_t chunk;
//         } green;
//         union {
//             struct {
//                 uint16_t sign : 1;
//                 uint16_t mantissa : 10;
//                 uint16_t exponent : 5;
//             };
//             uint16_t chunk;
//         } blue;
//     };
//     
//     struct pixel_RGBA16f {
//         union {
//             struct {
//                 uint16_t sign : 1;
//                 uint16_t mantissa : 10;
//                 uint16_t exponent : 5;
//             };
//             uint16_t chunk;
//         } red;
//         union {
//             struct {
//                 uint16_t sign : 1;
//                 uint16_t mantissa : 10;
//                 uint16_t exponent : 5;
//             };
//             uint16_t chunk;
//         } green;
//         union {
//             struct {
//                 uint16_t sign : 1;
//                 uint16_t mantissa : 10;
//                 uint16_t exponent : 5;
//             };
//             uint16_t chunk;
//         } blue;
//         union {
//             struct {
//                 uint16_t sign : 1;
//                 uint16_t mantissa : 10;
//                 uint16_t exponent : 5;
//             };
//             uint16_t chunk;
//         } alpha;
//     };
    
//     class pixel_array {
//     public:
//         virtual unsigned char*      data() = 0;
//         virtual void                assign( size_t index,
//                                             uint8_t red,
//                                             uint8_t green = 0,
//                                             uint8_t blue  = 0,
//                                             uint8_t alpha = 0  ) = 0;
//         virtual void                assign( size_t index,
//                                             int8_t red,
//                                             int8_t green = 0,
//                                             int8_t blue  = 0,
//                                             int8_t alpha = 0  ) = 0;
//         virtual void                assign( size_t index,
//                                             uint16_t red,
//                                             uint16_t green = 0,
//                                             uint16_t blue  = 0,
//                                             uint16_t alpha = 0  ) = 0;
//         virtual void                assign( size_t index,
//                                             int16_t red,
//                                             int16_t green = 0,
//                                             int16_t blue  = 0,
//                                             int16_t alpha = 0  ) = 0;
//         virtual void                assign( size_t index,
//                                             uint32_t red,
//                                             uint32_t green = 0,
//                                             uint32_t blue  = 0,
//                                             uint32_t alpha = 0  ) = 0;
//         virtual void                assign( size_t index,
//                                             int32_t red,
//                                             int32_t green = 0,
//                                             int32_t blue  = 0,
//                                             int32_t alpha = 0  ) = 0;
//         virtual void                assign( size_t index,
//                                             float red,
//                                             float green = 0,
//                                             float blue  = 0,
//                                             float alpha = 0  ) = 0;                                    
//     };
//     
//     class pixel_sheet {
//     public:
//         virtual unsigned char*      data() = 0;
//         virtual void                assign( size_t index );
//     };
//     
//     class pixel_volume {
//     public:
//         virtual unsigned char*      data() = 0;
//         virtual void                assign( size_t index );
//     };
//     
//     class RGBA8_array : public pixel_array {
//     public:
//         virtual unsigned char*  data();
//         virtual void            assign( size_t index,
//                                         uint8_t red,
//                                         uint8_t green,
//                                         uint8_t blue,
//                                         uint8_t alpha );
//     private:
//         union pixel {
//             struct {
//                 uint8_t red;
//                 uint8_t green;
//                 uint8_t blue;
//                 uint8_t alpha;
//             } channel;
//             uint32_t color;
//         };
//     }; 
    /**
     * \brief Construct a new one dimensional texture.
     * \param set The settings for the new texture.
     */
    texture_1D::texture_1D( settings const& set ) :
                            tex_ID ( 0 ),
                            target ( 0 ),
                            width_v ( set.dw_v ),
                            pixels_v ( set.pixels_v ),
                            pixel_bits_v ( set.pixel_size_v ),
                            image_format ( set.image_format_v ),
                            path ( set.path_v ),
                            data ( 0 )
    {
        gl::GenTextures( 1, &tex_ID );
        if ( set.as_array_v ) {
            target = gl::TEXTURE_1D_ARRAY;
        } else {
            target = gl::TEXTURE_1D;
        }
        gl::ActiveTexture( gl::TEXTURE0 );
        gl::BindTexture( target, tex_ID );
        
        gl::TexParameteri( target, gl::TEXTURE_BASE_LEVEL, set.base_level_v );
        gl::TexParameteri( target, gl::TEXTURE_MAX_LEVEL, set.max_level_v );
        gl::TexParameteri( target, gl::TEXTURE_SWIZZLE_R, set.r_src_v );
        if ( set.channels_v > 1 ) {
            gl::TexParameteri( target, gl::TEXTURE_SWIZZLE_G, set.g_src_v );
            if ( set.channels_v > 2 ) {
                gl::TexParameteri( target, gl::TEXTURE_SWIZZLE_B, set.b_src_v );
                if ( set.channels_v > 3 ) {
                    gl::TexParameteri( target, gl::TEXTURE_SWIZZLE_A, set.a_src_v );
                }
            }
        }
        gl::TexParameterf( target, gl::TEXTURE_MIN_LOD, set.base_lod_v );
        gl::TexParameterf( target, gl::TEXTURE_MAX_LOD, set.max_lod_v );
        gl::TexParameterf( target, gl::TEXTURE_LOD_BIAS, set.lod_bias_v );
        
        gl::TexParameteri( target, gl::TEXTURE_MIN_FILTER, set.min_filter_v );
        gl::TexParameteri( target, gl::TEXTURE_MAG_FILTER, set.mag_filter_v );
        
        gl::TexParameteri( target, gl::TEXTURE_WRAP_S, set.wrap_s_v );
        gl::TexParameteri( target, gl::TEXTURE_WRAP_T, set.wrap_t_v );
        
        if ( set.compare_func_v == 0 ) {
            gl::TexParameteri( target, gl::TEXTURE_COMPARE_MODE, gl::NONE );
        } else {
            gl::TexParameteri( target,
                               gl::TEXTURE_COMPARE_MODE,
                               gl::COMPARE_REF_TO_TEXTURE );
            gl::TexParameteri( target,
                               gl::TEXTURE_COMPARE_FUNC,
                               set.compare_func_v );
        }
        gl::BindTexture( target, 0 );
    }
    /**
     * \brief Destruct this one dimensional texture.
     * \todo It doesn't free OpenGL resources, foo'!
     */
    texture_1D::~texture_1D()
    {
        delete[] data;
    }
    /**
     * \brief Return the one dimensional texture's width.
     * \return The one dimensional texutre's width
     */
    size_t  texture_1D::width() const
    { return width_v; }
    /**
     * \brief Return the number of pixels in the one dimensional texture.
     * \return The number of pixels in the one dimensional texture
     * \todo Review this name. Not sold on it.
     */
    size_t  texture_1D::pixels() const
    { return pixels_v; }
    /**
     * \brief Return the number of bits in a pixel.
     * \return The number of bits in a pixel
     */
    size_t  texture_1D::pixel_bits() const
    { return pixel_bits_v; }
    /**
     * \brief Set the file path to the texture's source file.
     * \return The file path to the texture's source file
     */
    void    texture_1D::file( std::string const& path )
    { this->path = path; }
    /**
     * \brief Access the texture's source file and load it.
     * Note that this does not hand the data over to OpenGL, it just
     * opens the file and turns it into pixel data on the client side.
     */
    void    texture_1D::decode_file()
    {
        FIBITMAP* src = FreeImage_Load( FIF_PNG, path.c_str(), PNG_DEFAULT );
        
        if ( src ) {
            if ( FreeImage_GetHeight( src ) > 1 ) {
                throw std::logic_error( "Source data for 1D texture is not one dimensional." );
            }
            width_v = FreeImage_GetWidth( src );
            pixels_v = width_v;
            pixel_bits_v = FreeImage_GetBPP( src );
            size_t pixel_bytes = pixel_bits_v / 8;
            
            BYTE* bits = FreeImage_GetBits( src );

            size_t bytes = pixel_bytes * pixels_v;
            
            data = new unsigned char[bytes];
            
            while( bytes ) {
                --bytes;
                data[bytes] = bits[bytes];
            }
            
            FreeImage_Unload( src );
        }
        
    }
    /**
     * \brief Upload the texture's data to OpenGL.
     * This function requires that \ref gfx::texture_1D::decode_file "decode_file()"
     * has been called on this one dimensional texture.
     * \todo Does this take into account the pxiel formatting options are all?
     */
    void    texture_1D::load_data()
    {
        if ( not video_system::get().context_present() ) {
            throw std::logic_error( "No OpenGL context available to load texture to." );
        }
        if ( data == 0 ) {
            throw std::logic_error( "Texture data not initialized." );
        }
        gl::ActiveTexture( gl::TEXTURE0 );
        gl::BindTexture( target, tex_ID );
        gl::TexImage1D( target,
                        0,
                        image_format,
                        width_v,
                        0,
                        gl::RGB,
                        gl::UNSIGNED_BYTE,
                        data              );
        //video_system::get().check_acceleration_error("Texture_1D load_data");
        
    }
    /**
     * \brief Activate use of this texture in the current state of OpenGL.
     * \todo This function is not very "intelligent", it assumes things about
     * what texture bindings the texture should use (specifically it assigns
     * this texture to binding 0). This is a relative of the uniform problem
     * over in lights and cameras. These issues must be resolved.
     */
    void    texture_1D::use()
    {
        if ( not video_system::get().context_present() ) {
            throw std::logic_error( "No OpenGL context available to bind texture to." );
        }
        gl::ActiveTexture( gl::TEXTURE0 );
        gl::BindTexture( target, tex_ID );
    }
    /**
     * \brief Return the number of bytes in the texture.
     * \return The number of bytes in the texture.
     */
    size_t  texture_1D::bytes()
    { return pixel_bits_v * pixels_v; }
    
    
    
    
    
    
    
    /**
     * \brief Construct a new two dimensional texture.
     * \param set The settings for the new texture.
     */
    texture_2D::texture_2D( settings const& set ) :
                            tex_ID ( 0 ),
                            target ( 0 ),
                            width_v ( set.dw_v ),
                            height_v ( set.dh_v ),
                            pixels_v ( set.pixels_v ),
                            pixel_bits_v ( set.pixel_size_v ),
                            image_format ( set.image_format_v ),
                            path ( set.path_v ),
                            data ( 0 )
    {
        gl::GenTextures( 1, &tex_ID );
        if ( set.as_array_v ) {
            target = gl::TEXTURE_2D_ARRAY;
        } else {
            target = gl::TEXTURE_2D;
        }
        gl::ActiveTexture( gl::TEXTURE0 );
        gl::BindTexture( target, tex_ID );
        
        gl::TexParameteri( target, gl::TEXTURE_BASE_LEVEL, set.base_level_v );
        gl::TexParameteri( target, gl::TEXTURE_MAX_LEVEL, set.max_level_v );
        gl::TexParameteri( target, gl::TEXTURE_SWIZZLE_R, set.r_src_v );
        if ( set.channels_v > 1 ) {
            gl::TexParameteri( target, gl::TEXTURE_SWIZZLE_G, set.g_src_v );
            if ( set.channels_v > 2 ) {
                gl::TexParameteri( target, gl::TEXTURE_SWIZZLE_B, set.b_src_v );
                if ( set.channels_v > 3 ) {
                    gl::TexParameteri( target, gl::TEXTURE_SWIZZLE_A, set.a_src_v );
                }
            }
        }
        gl::TexParameterf( target, gl::TEXTURE_MIN_LOD, set.base_lod_v );
        gl::TexParameterf( target, gl::TEXTURE_MAX_LOD, set.max_lod_v );
        gl::TexParameterf( target, gl::TEXTURE_LOD_BIAS, set.lod_bias_v );
        
        gl::TexParameteri( target, gl::TEXTURE_MIN_FILTER, set.min_filter_v );
        gl::TexParameteri( target, gl::TEXTURE_MAG_FILTER, set.mag_filter_v );
        
        gl::TexParameteri( target, gl::TEXTURE_WRAP_S, set.wrap_s_v );
        gl::TexParameteri( target, gl::TEXTURE_WRAP_T, set.wrap_t_v );
        
        if ( set.compare_func_v == 0 ) {
            gl::TexParameteri( target, gl::TEXTURE_COMPARE_MODE, gl::NONE );
        } else {
            gl::TexParameteri( target,
                               gl::TEXTURE_COMPARE_MODE,
                               gl::COMPARE_REF_TO_TEXTURE );
            gl::TexParameteri( target,
                               gl::TEXTURE_COMPARE_FUNC,
                               set.compare_func_v );
        }
        gl::BindTexture( target, 0 );
    }
    /**
     * \brief Destruct this one dimensional texture.
     * \todo It doesn't free OpenGL resources, foo'!
     */
    texture_2D::~texture_2D()
    {
        delete[] data;
    }
    /**
     * \brief Return the two dimensional texture's width.
     * \return The two dimensional texutre's width
     */
    size_t  texture_2D::width() const
    { return width_v; }
    /**
     * \brief Return the two dimensional texture's height.
     * \return The two dimensional texutre's height
     */
    size_t  texture_2D::height() const
    { return height_v; }
    /**
     * \brief Return the number of pixels in the two dimensional texture.
     * \return The number of pixels in the two dimensional texture
     * \todo Review this name. Not sold on it.
     */
    size_t  texture_2D::pixels() const
    { return pixels_v; }
    /**
     * \brief Return the number of bits in a pixel.
     * \return The number of bits in a pixel
     */
    size_t  texture_2D::pixel_bits() const
    { return pixel_bits_v; }
    /**
     * \brief Set the file path to the texture's source file.
     * \return The file path to the texture's source file
     */
    void    texture_2D::file( std::string const& path )
    { this->path = path; }
    /**
     * \brief Access the texture's source file and load it.
     * Note that this does not hand the data over to OpenGL, it just
     * opens the file and turns it into pixel data on the client side.
     */
    void    texture_2D::decode_file()
    {
        FIBITMAP* src = FreeImage_Load( FIF_PNG, path.c_str(), PNG_DEFAULT );
        
        if ( src ) {
            width_v = FreeImage_GetWidth( src );
            height_v = FreeImage_GetHeight( src );
            pixels_v = width_v * height_v;
            pixel_bits_v = FreeImage_GetBPP( src );
            size_t pixel_bytes = pixel_bits_v / 8;
            
            BYTE* bits = FreeImage_GetBits( src );

            size_t bytes = pixel_bytes * pixels_v;
            
            data = new unsigned char[bytes];
            
            while( bytes ) {
                --bytes;
                data[bytes] = bits[bytes];
            }
            
            FreeImage_Unload( src );
        }
        
    }
    /**
     * \brief Upload the texture's data to OpenGL.
     * This function requires that \ref gfx::texture_1D::decode_file "decode_file()"
     * has been called on this two dimensional texture.
     * \todo Does this take into account the pxiel formatting options are all?
     */
    void    texture_2D::load_data()
    {
        if ( not video_system::get().context_present() ) {
            throw std::logic_error( "No OpenGL context available to load texture to." );
        }
        if ( data == 0 ) {
            throw std::logic_error( "Texture data not initialized." );
        }
        gl::ActiveTexture( gl::TEXTURE0 );
        gl::BindTexture( target, tex_ID );
        gl::TexImage2D( target,
                        0,
                        image_format,
                        width_v,
                        height_v,
                        0,
                        gl::RGB,
                        gl::UNSIGNED_BYTE,
                        data              );
        //video_system::get().check_acceleration_error("Texture_2D load_data");
    }
    /**
     * \brief Activate use of this texture in the current state of OpenGL.
     * \todo This function is not very "intelligent", it assumes things about
     * what texture bindings the texture should use (specifically it assigns
     * this texture to binding 0). This is a relative of the uniform problem
     * over in lights and cameras. These issues must be resolved.
     */
    void    texture_2D::use()
    {
        if ( not video_system::get().context_present() ) {
            throw std::logic_error( "No OpenGL context available to bind texture to." );
        }
        gl::ActiveTexture( gl::TEXTURE0 );
        gl::BindTexture( target, tex_ID );
    }
    /**
     * \brief Return the number of bytes in the texture.
     * \return The number of bytes in the texture.
     */
    size_t  texture_2D::bytes()
    { return pixel_bits_v * pixels_v; }
    
    
}