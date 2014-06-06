#ifndef VIDEO_MANAGER_HPP
#define VIDEO_MANAGER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include "checkError.hpp"
#include "SDL.h"
#include "gl_core_3_3.hpp"
#include "../gUtility/datatypeinfo.hpp"
#include "../gMath/datatype.hpp"


namespace gfx {

class video_manager;

class managed {
protected:
                          managed( video_manager* owner,
                                   size_t g_id           );
                          ~managed();
    video_manager* const  owner;
    size_t                g_id;
    friend class          video_manager;
};

inline managed::managed( video_manager* owner,
                         size_t g_id           ) :
                            owner( owner ),
                            g_id( g_id )          {}
                            
inline managed::~managed() {}

class window : public managed {
public:
                            ~window();
    void                    swap();
    bool                    operator ==( window const& rhs ) const;
    std::string             title() const;
    void                    title( std::string const& ttl );
    int                     x_pos() const;
    void                    x_pos( int xp );
    int                     y_pos() const;
    void                    y_pos( int yp );
    ivec2                   position() const;
    void                    position( int xp, int yp );
    void                    position( ivec2 const& pos );
    bool                    is_x_centered() const;
    void                    center_x();
    bool                    is_y_centered() const;
    void                    center_y();
    int                     width() const;
    void                    width( int dw );
    int                     height() const;
    void                    height( int dh );
    ivec2                   dimensions() const;
    void                    dimensions( int dw,
                                        int dh );
    void                    dimensions( ivec2 const& dim );
    ivec2                   ul_corner() const;
    ivec2                   lr_corner() const;
    void                    corners( int ulx,
                                     int uly,
                                     int lrx,
                                     int lry );
    void                    corners( ivec2 const& ulc,
                                     ivec2 const& lrc );
    bool                    is_maximized() const;
    void                    maximize();
    bool                    is_minimized() const;
    void                    minimize();
    bool                    is_resizable() const;
//     void                    make_resizable();
//     void                    lock_size();
    bool                    has_3D() const;
    bool                    is_visible() const;
    void                    make_visible();
    void                    make_hidden();
    bool                    has_border() const;
//     bool                    is_fullscreen() const;
// //     void                    make_fullscreen();
//     bool                    has_focus() const;
// //     void                    take_focus();
    
    friend                  std::ostream& operator <<( std::ostream& out,
                                                       window const& rhs );
    
    class settings {
        public:
                                settings();
            settings&           title( std::string const& title );
            settings&           x_pos( int xp );
            settings&           y_pos( int yp );
            settings&           position( int xp,
                                          int yp );
            settings&           center_x();
            settings&           center_y();
            settings&           center();
            settings&           width( int dw );
            settings&           height( int dh );
            settings&           dimensions( int dw,
                                            int dh );
            settings&           corners( int ul_x,
                                         int ul_y,
                                         int lr_x,
                                         int lr_y );
            settings&           corners( ivec2 const& ulc,
                                         ivec2 const& lrc );
            settings&           maximized();
            settings&           minimized();
            settings&           resizable();
            settings&           lock_size();
            settings&           has_3D();
            settings&           visible();
            settings&           no_border();
            settings&           has_border();
            settings&           fullscreen();
            settings&           grab_input();
            settings&           has_focus();
            settings&           no_focus();
        private:
            friend              class video_manager;
            std::string         title_v;
            ivec2               pos_v;
            ivec2               ulc_v;
            int                 width_v;
            int                 height_v;
            bool                center_on_x;
            bool                center_on_y;
            bool                minimized_v;
            bool                maximized_v;
            bool                fullscreen_v;
            bool                resizable_v;
            bool                uses_opengl;
            bool                visible_v;
            bool                has_border_v;
            bool                has_focus_v;
            bool                grab_input_v;
    };
    
    class settings_3D {
    public:
                            settings_3D();
        settings_3D&        r_bits( unsigned int b );
        settings_3D&        g_bits( unsigned int b );
        settings_3D&        b_bits( unsigned int b );
        settings_3D&        a_bits( unsigned int b );
        settings_3D&        framebuffer_bits( unsigned int b );
        settings_3D&        doublebuffered();
        settings_3D&        not_doublebuffered();
        settings_3D&        depth_bits( unsigned int b );
        settings_3D&        stencil_bits( unsigned int b );
        settings_3D&        r_accumulator_bits( unsigned int b );
        settings_3D&        g_accumulator_bits( unsigned int b );
        settings_3D&        b_accumulator_bits( unsigned int b );
        settings_3D&        a_accumulator_bits( unsigned int b );
        settings_3D&        in_stereo();
        settings_3D&        multisample( unsigned int samples );
        settings_3D&        force_hardware();
        settings_3D&        force_software();
//         settings_3D&        version( unsigned int maj_ver,
//                                      unsigned int min_ver );
    private:
        unsigned int        r_bits_v;
        unsigned int        g_bits_v;
        unsigned int        b_bits_v;
        unsigned int        a_bits_v;
        unsigned int        framebuffer_bits_v;
        bool                doublebuffered_v;
        unsigned int        depth_bits_v;
        unsigned int        stencil_bits_v;
        unsigned int        r_accumulator_bits_v;
        unsigned int        g_accumulator_bits_v;
        unsigned int        b_accumulator_bits_v;
        unsigned int        a_accumulator_bits_v;
        bool                in_stereo_v;
        bool                multisample_v;
        unsigned int        samples_v;
        bool                force_hw_v;
        bool                force_sw_v;
//         unsigned int        maj_ver_v;
//         unsigned int        min_ver_v;
        friend class        video_manager;
    };
    
private:
                            window( std::string const& title,
                                    video_manager* const owner,
                                    size_t g_id,
                                    SDL_Window* sys_window );
    std::string             title_str;
    SDL_Window*             sys_window;
    friend                  class video_manager;
};

std::ostream&   operator <<( std::ostream& out, window const& rhs );

inline  window::settings::settings() :
            title_v         ("untitled"),
            pos_v           ( 0, 0 ),
            ulc_v           ( 0, 0 ),
            width_v         (0),          height_v        (0),
            center_on_x     (true),       center_on_y     (true),
            minimized_v     (false),      maximized_v     (false),
            fullscreen_v    (false),
            resizable_v     (false),
            uses_opengl     (false),
            visible_v       (true),
            has_border_v    (true),
            has_focus_v     (false),
            grab_input_v    (false)
{
    SDL_Rect bounds;
    SDL_GetDisplayBounds( 0, &bounds );
    width_v = bounds.w / 2;
    height_v = bounds.h / 2;
    pos_v[0] = bounds.w / 2;
    pos_v[1] = bounds.h / 2;
    ulc_v[0] = width_v / -2 + pos_v[0];
    ulc_v[1] = height_v / -2 + pos_v[1];
};
            
inline  window::settings&     window::settings::title( std::string const& title )
{ title_v = title; return *this; }

inline  window::settings&     window::settings::x_pos( int xp )
{   pos_v[0] = xp;
    ulc_v[0] = width_v / -2 + xp;
    center_on_x = false;
    return *this; }
    
inline  window::settings&     window::settings::y_pos( int yp )
{   pos_v[1] = yp;
    ulc_v[1] = height_v / -2 + yp;
    center_on_y = false;
    return *this; }
    
inline  window::settings&     window::settings::position( int xp,
                                                          int yp )
{   pos_v[0] = xp;
    ulc_v[0] = width_v / -2 + xp;
    pos_v[1] = yp;
    ulc_v[1] = height_v / -2 + yp;
    
    center_on_x = false;
    center_on_y = false;
    return *this; }
    
inline  window::settings&     window::settings::width( int dw )
{
    width_v = dw;
    ulc_v[0] = dw / -2 + pos_v[0];
    
    return *this;
}

inline  window::settings&     window::settings::height( int dh )
{
    height_v = dh;
    ulc_v[1] = dh / -2 + pos_v[1];
    return *this;    
}

inline  window::settings&     window::settings::dimensions( int dw,
                                                            int dh )
{ width_v = dw; height_v = dh; return *this; }
  
inline  window::settings&     window::settings::corners( int ul_x,
                                                         int ul_y,
                                                         int lr_x,
                                                         int lr_y )
{
    ulc_v[0] = ul_x;
    ulc_v[1] = ul_y;
    width_v = lr_x - ul_x;
    height_v = lr_y - ul_y;
    center_on_x = false;
    center_on_y = false;
    return *this;
}

inline  window::settings&     window::settings::corners( ivec2 const& ulc,
                                                         ivec2 const& lrc )
{
    ulc_v[0] = ulc[0];
    ulc_v[1] = ulc[1];
    width_v = lrc[0] - ulc[0];
    height_v = lrc[1] - ulc[1];
    center_on_x = false;
    center_on_y = false;
    return *this;
}

inline  window::settings&     window::settings::center_x()
{   center_on_x = true;
    return *this; }
    
inline  window::settings&     window::settings::center_y()
{   center_on_y = true;
    return *this; }
    
inline  window::settings&     window::settings::center()
{   center_on_x = true;
    center_on_y = true;
    return *this; }

inline  window::settings&     window::settings::maximized()
{   maximized_v = true;
    minimized_v = false;
    fullscreen_v = false;
    return *this; }
            
inline  window::settings&     window::settings::minimized()
{   minimized_v = true;
    maximized_v = false;
    fullscreen_v = false;
    return *this; }

inline  window::settings&     window::settings::fullscreen()
{   fullscreen_v = true;
    minimized_v = false;
    maximized_v = false;
    return *this; }

inline  window::settings&     window::settings::resizable()
{ resizable_v = true; return *this; }

inline  window::settings&     window::settings::lock_size()
{ resizable_v = false; return *this; }

inline  window::settings&     window::settings::has_3D()
{ uses_opengl = true; return *this; }

inline  window::settings&     window::settings::visible()
{ visible_v = true; return *this; }

inline  window::settings&     window::settings::no_border()
{ has_border_v = false; return *this; }

inline  window::settings&     window::settings::has_border()
{ has_border_v = true; return *this; }

inline  window::settings&     window::settings::has_focus()
{ has_focus_v = true; return *this; }

inline  window::settings&     window::settings::no_focus()
{ has_focus_v = false; return *this; }

inline  window::settings&     window::settings::grab_input()
{ grab_input_v = true; return *this; }

inline  window::settings_3D::settings_3D() :
                                r_bits_v             ( 8 ),
                                g_bits_v             ( 8 ),
                                b_bits_v             ( 8 ),
                                a_bits_v             ( 8 ),
                                framebuffer_bits_v   ( 0 ),
                                doublebuffered_v     ( true ),
                                depth_bits_v         ( 16 ),
                                stencil_bits_v       ( 0 ),
                                r_accumulator_bits_v ( 0 ),
                                g_accumulator_bits_v ( 0 ),
                                b_accumulator_bits_v ( 0 ),
                                a_accumulator_bits_v ( 0 ),
                                in_stereo_v          ( false ),
                                multisample_v        ( false ),
                                samples_v            ( 0 ),
                                force_hw_v           ( false ),
                                force_sw_v           ( false )/*,
                                maj_ver_v            ( 1 ),
                                min_ver_v            ( 4 )*/
                                {}
                                              
inline window::settings_3D&     window::settings_3D::r_bits( unsigned int b )
{ r_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::g_bits( unsigned int b )
{ g_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::b_bits( unsigned int b )
{ b_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::a_bits( unsigned int b )
{ a_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::framebuffer_bits( unsigned int b )
{ framebuffer_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::doublebuffered()
{ doublebuffered_v = true; return *this; }

inline window::settings_3D&     window::settings_3D::not_doublebuffered()
{ doublebuffered_v = false; return *this; }

inline window::settings_3D&     window::settings_3D::depth_bits( unsigned int b )
{ depth_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::stencil_bits( unsigned int b )
{ stencil_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::r_accumulator_bits( unsigned int b )
{ r_accumulator_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::g_accumulator_bits( unsigned int b )
{ g_accumulator_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::b_accumulator_bits( unsigned int b )
{ b_accumulator_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::a_accumulator_bits( unsigned int b )
{ a_accumulator_bits_v = b; return *this; }

inline window::settings_3D&     window::settings_3D::in_stereo()
{ in_stereo_v = false; return *this; }

inline window::settings_3D&     window::settings_3D::multisample( unsigned int samples )
{
    multisample_v = true;
    samples_v = samples;
    return *this;
}

inline window::settings_3D&     window::settings_3D::force_hardware()
{ force_hw_v = true; return *this; }

inline window::settings_3D&     window::settings_3D::force_software()
{ force_sw_v = true; return *this; }

// inline window::settings_3D&     window::settings_3D::version( unsigned int maj_ver,
//                                                               unsigned int min_ver )
// {
//     maj_ver_v = maj_ver;
//     min_ver_v = min_ver;
//     return *this;
// }

inline  bool    window::operator ==( window const& rhs ) const
{ return this->sys_window == rhs.sys_window; }

inline  window::window( std::string const& title,
                        video_manager* const owner,
                        size_t g_id,
                        SDL_Window* system_window ) :
                            managed( owner, g_id ),
                            title_str ( title ),
                            sys_window( system_window ) {};

/**
 * The way in which contexts and windows interact is obscure;
 * It is possible that soem OpenGL setting need to be saved in
 * order to make this all work correctly.
 * 
 */
                            
class context : public managed {
public:
    typedef std::vector<GLubyte>  ub_indexer;
    typedef std::vector<GLushort> us_indexer;
    typedef std::vector<GLuint>   ui_indexer;
                            ~context();
    void                    clear_color( float red, float green,
                                         float blue, float alpha = 1.0f );
    bool                    is_active() const;
    unsigned int            major_version() const;
    unsigned int            minor_version() const;
    uvec2                   version() const;
    unsigned int            depth_bits() const;
    bool                    double_buffered() const;
    bool                    operator ==( context const& rhs ) const;
    
    void                    draw_triangles( size_t const tris,
                                            ui_indexer const& indices );
    class settings {
    public:
                            settings();
    private:
        friend              class video_manager;
    };
    
private:
                            context( video_manager* const owner,
                                     size_t g_id,
                                     window const* target_window,
                                     SDL_GLContext sys_context);
    window const*           target_window;
    SDL_GLContext           sys_context;
    friend                  class video_manager;
};

inline context::settings::settings() {};

inline  bool    context::operator ==( context const& rhs ) const
{ return this->sys_context == rhs.sys_context; }

inline void     context::draw_triangles( size_t const tris,
                                         ui_indexer const& indices )
{
    if ( not this->is_active() ) {
        throw std::logic_error( "Request to draw triangles on in-active context." );
    }
    gl::DrawElements( gl::TRIANGLES,
                      tris * 3,
                      gl::UNSIGNED_INT,
                      &indices[0] );
}

inline context::context( video_manager* const owner,
                         size_t g_id,
                         window const* target_window,
                         SDL_GLContext sys_context    ) :
                            managed( owner, g_id ),
                            target_window( target_window ),
                            sys_context( sys_context )      {}

class compilation_error : public std::logic_error {
public:
    explicit compilation_error( std::string const& msg ) : logic_error( msg ) {};
};
                            
class program : public managed {
public:
                            ~program();
    void                    compile();
    void                    link();
    void                    use();
    friend std::ostream&    operator <<( std::ostream& out, program const& rhs );
    GLuint                  get_prog_ID() const { return prog_ID; }
    
    class settings {
    public:
                            settings();
        settings&           maj_ver( unsigned int maj_ver);
        settings&           min_ver( unsigned int min_ver);
        settings&           has_vert();
        settings&           has_frag();
        settings&           has_geom();
        // settings& uses_tess(); /** Needs ARB extension */
        settings&           use_vert( std::string const& path );
        settings&           use_frag( std::string const& path );
        settings&           use_geom( std::string const& path );
        // settings& uses_tess( std::string const& path ); /** Needs ARB extension */
        settings&           no_vert();
        settings&           no_frag();
        settings&           no_geom();
        //settings& no_tess();/** Needs ARB extension */
    private:
        std::string         vert_path;
        std::string         frag_path;
        std::string         geom_path;
        //std::string tess_path;
        unsigned int        maj_ver_v;
        unsigned int        min_ver_v;
        bool                has_vert_v;
        bool                has_frag_v;
        bool                has_geom_v;
        bool                has_tess_v;
        friend              class video_manager;
    };

private:
    friend                  class video_manager;
                            program( video_manager* const manager, size_t g_id );
    void                    compile( GLuint stage_ID, std::string const& stage_path );
    std::string             vert_path;
    std::string             frag_path;
    std::string             geom_path;
    GLuint                  vert_ID;
    GLuint                  frag_ID;
    GLuint                  geom_ID;
    GLuint                  tess_ID;
    GLuint                  prog_ID;
    unsigned int            maj_ver;
    unsigned int            min_ver;
};

inline  program::settings::settings() :
                            vert_path( "" ),
                            frag_path( "" ),
                            geom_path( "" ),
                            maj_ver_v( 2 ),
                            min_ver_v( 0 ),
                            has_vert_v( true ),
                            has_frag_v( true ),
                            has_geom_v( false ),
                            has_tess_v( false )  {}
                            
inline program::settings&   program::settings::maj_ver( unsigned int maj_ver )
{ maj_ver_v = maj_ver; return *this; }

inline program::settings&   program::settings::min_ver( unsigned int min_ver )
{ min_ver_v = min_ver; return *this; }

inline program::settings&   program::settings::has_vert()
{ has_vert_v = true; return *this; }

inline program::settings&   program::settings::has_frag()
{ has_frag_v = true; return *this; }

inline program::settings&   program::settings::has_geom()
{ has_geom_v = true; return *this; }

inline program::settings&   program::settings::use_vert( std::string const& path )
{
    vert_path = path;
    has_vert_v = true;
    return *this;
}

inline program::settings&   program::settings::use_frag( std::string const& path )
{
    frag_path = path;
    has_frag_v = true;
    return *this;
}

inline program::settings&   program::settings::use_geom( std::string const& path )
{
    geom_path = path;
    has_geom_v = true;
    return *this;
}

inline program::settings&   program::settings::no_vert()
{ has_vert_v = false; return *this; }

inline program::settings&   program::settings::no_frag()
{ has_frag_v = false; return *this; }

inline program::settings&   program::settings::no_geom()
{ has_geom_v = false; return *this; }

class block_spec {
public:
                                    block_spec();
                                    ~block_spec();
    template< typename T >
    block_spec&                     attribute( type<T> const& proto );
private:
    typedef std::vector< info* >    attrib_vector;
    attrib_vector*                  attributes;
    friend                          class buffer;
};

inline  block_spec::block_spec() : attributes( new block_spec::attrib_vector() ) {}

inline block_spec::~block_spec()
{
    attrib_vector::iterator i;
    for ( i = attributes->begin(); i < attributes->end(); ++i )
    {
        delete *i;
    }
    delete attributes;
}

template< typename T > inline
block_spec&     block_spec::attribute( type<T> const& proto )
{   info* new_attrib = (info*) proto.copy();
    attributes->push_back( new_attrib );
    return *this; }

class binding_error : public std::logic_error {
public:
    explicit binding_error( std::string const& msg ) : logic_error( msg ) {};
};

class unformatted_error : public std::logic_error {
public:
    explicit unformatted_error( std::string const& msg ) : logic_error( msg ) {};
};
    
class buffer : public managed {
public:
    friend                      class video_manager;
    friend std::ostream&        operator <<( std::ostream& out, buffer const& rhs );
                                ~buffer();
    void                        block_format( block_spec const& spec );
    void                        blocks( GLsizeiptr const blocks );
    void                        add_blocks( GLsizeiptr const more_blocks );
    template< typename DATA >
    void                        fill_attribute( GLuint index,
                                                std::vector< DATA > const& attrib_data );
    void                        load_data();
    void                        align_vertices();
    GLuint                      get_id() const { return buff_ID; }
    
    class settings {
    public:
        friend              class video_manager;
                            settings();
        settings&           blocks( GLsizeiptr new_n_blocks );
        settings&           static_draw();
        settings&           static_read();
        settings&           static_copy();
        settings&           dynamic_draw();
        settings&           dynamic_read();
        settings&           dynamic_copy();
        settings&           stream_draw();
        settings&           stream_read();
        settings&           stream_copy();
        settings&           for_array();
    //    settings&     for_atomic_counter();
        settings&           for_copy_read();
        settings&           for_copy_write();
    //    settings&     for_indirect_draw();
    //    settings&     for_indirect_dispatch();
        settings&           for_element_array();
        settings&           for_pixel_packing();
        settings&           for_pixel_unpacking();
    //    settings&     for_shader_storage();
        settings&           for_texture();
        settings&           for_transform_feedback();
        settings&           for_uniform();
    private:
        GLsizeiptr          blocks_v;
        GLenum              usage_v;
        GLenum              target_v;
    };
    
private:
    unsigned char*              data;
    GLsizeiptr                  n_blocks;
    GLsizeiptr                  stride;
    GLuint                      vao_ID;
    GLuint                      buff_ID;
    GLenum                      usage;
    GLenum                      intended_target;
    bool                        data_loaded;
    bool                        verts_specified;
    typedef std::vector<info*>  attrib_vector;
    attrib_vector*              attributes;
                                buffer( video_manager* owner,
                                        size_t g_ID,
                                        GLsizeiptr n_blocks,
                                        GLuint vao_ID,
                                        GLuint buff_ID,
                                        GLenum usage,
                                        GLenum target );
    GLsizeiptr                  attribute_offset( GLuint index ) const;
};

inline buffer::settings::settings() :
                          blocks_v ( 0 ),
                          usage_v  ( gl::DYNAMIC_DRAW ),
                          target_v ( gl::ARRAY_BUFFER ) {}
                          
inline buffer::settings&    buffer::settings::blocks( GLsizeiptr blocks )
{ blocks_v = blocks; return *this; }

inline buffer::settings&    buffer::settings::static_draw()
{ usage_v = gl::STATIC_DRAW; return *this; }

inline buffer::settings&    buffer::settings::static_read()
{ usage_v = gl::STATIC_READ; return *this; }

inline buffer::settings&    buffer::settings::static_copy()
{ usage_v = gl::STATIC_COPY; return *this; }

inline buffer::settings&    buffer::settings::dynamic_draw()
{ usage_v = gl::DYNAMIC_DRAW; return *this; }

inline buffer::settings&    buffer::settings::dynamic_read()
{ usage_v = gl::DYNAMIC_READ; return *this; }

inline buffer::settings&    buffer::settings::dynamic_copy()
{ usage_v = gl::DYNAMIC_COPY; return *this; }

inline buffer::settings&    buffer::settings::stream_draw()
{ usage_v = gl::STREAM_DRAW; return *this; }

inline buffer::settings&    buffer::settings::stream_read()
{ usage_v = gl::STREAM_READ; return *this; }

inline buffer::settings&    buffer::settings::stream_copy()
{ usage_v = gl::STREAM_COPY; return *this; }

inline buffer::settings&     buffer::settings::for_array()
{ target_v = gl::ARRAY_BUFFER; return *this; }

inline buffer::settings&     buffer::settings::for_copy_read()
{ target_v = gl::COPY_READ_BUFFER; return *this; }

inline buffer::settings&     buffer::settings::for_copy_write()
{ target_v = gl::COPY_WRITE_BUFFER; return *this; }

inline buffer::settings&     buffer::settings::for_element_array()
{ target_v = gl::ELEMENT_ARRAY_BUFFER; return *this; }

inline buffer::settings&     buffer::settings::for_pixel_packing()
{ target_v = gl::PIXEL_PACK_BUFFER; return *this; }

inline buffer::settings&     buffer::settings::for_pixel_unpacking()
{ target_v = gl::PIXEL_UNPACK_BUFFER; return *this; }

inline buffer::settings&     buffer::settings::for_texture()
{ target_v = gl::TEXTURE_BUFFER; return *this; }

inline buffer::settings&     buffer::settings::for_transform_feedback()
{ target_v = gl::TRANSFORM_FEEDBACK_BUFFER; return *this; }

inline buffer::settings&     buffer::settings::for_uniform()
{ target_v = gl::UNIFORM_BUFFER; return *this; }

inline buffer::buffer( video_manager* owner,
                       size_t g_id,
                       GLsizeiptr n_blocks,
                       GLuint vao_ID,
                       GLuint buff_ID,
                       GLenum usage,
                       GLenum target ) :
                        managed         ( owner, g_id ),
                        data            ( 0 ),
                        n_blocks        ( n_blocks ),
                        stride          ( 0 ),
                        vao_ID          ( vao_ID ),
                        buff_ID         ( buff_ID ),
                        usage           ( usage ),
                        intended_target ( target ),
                        data_loaded     ( false ),
                        verts_specified ( false ),
                        attributes      ( new attrib_vector ) {}
                        
template< typename DATA >
void buffer::fill_attribute( GLuint index, std::vector< DATA > const& attrib_data )
{
    if ( not verts_specified ) {
        throw std::logic_error( "Attribute value assignment attempted when vertex format was not specified." );
    }
    if ( (*(*attributes)[index]) != type< DATA >() ) {
        std::string msg = "Type stored in std::vector, ";
        msg += type< DATA >().name();
        msg += ", does not match type specified at buffer index ";
        msg += index;
        msg += ", ";
        msg += (*attributes)[index]->name();
        msg += ".";
        throw std::invalid_argument( msg );
    }
    if ( attrib_data.size() > n_blocks ) {
        std::string msg = "Attribute value assignment attempted with ";
        msg += n_blocks;
        msg += " allocated data blocks but ";
        msg += attrib_data.size();
        msg += " attribute values.";
        throw std::out_of_range( msg );
    }

    if ( data == 0 ) {
        data = new unsigned char[n_blocks * stride];
    }

    GLsizeiptr block;
    unsigned char* cursor = data;
    cursor += attribute_offset( index );
    for( block = 0; block < n_blocks; ++block ) {
        raw_map const mapped_data = attrib_data[block].to_map();
        for( size_t b = 0; b < mapped_data.n_bytes; ++b ) {
            cursor[b] = mapped_data[b];
        }
        cursor += stride;
    }
}

inline  void    buffer::load_data()
{
    if( intended_target == gl::ELEMENT_ARRAY_BUFFER ){
        gl::BindVertexArray( vao_ID );
        checkGLError( "vao bound for element data load" );
    }
    gl::BindBuffer( intended_target, buff_ID );
    gl::BufferData( intended_target, n_blocks * stride, data, usage );

    data_loaded = true;
}

class video_manager {
public:
    
    class settings {
    public:
        settings();
        settings&       maj_ver( unsigned int maj_ver );
        settings&       min_ver( unsigned int min_ver );
        settings&       version( unsigned int maj_ver,
                                 unsigned int min_ver );
        settings&       core_profile();
        settings&       compatibility_profile();
        settings&       es_profile();
    private:
        unsigned int    maj_ver_v;
        unsigned int    min_ver_v;
        int             profile_v;
        friend class video_manager;
    };
                                    video_manager( video_manager::settings const& set =
                                                       video_manager::settings() );
                                    ~video_manager();
    window&                         new_window( window::settings const& set =
                                                    window::settings(),
                                                window::settings_3D const& set_3D =
                                                    window::settings_3D() 
                                              );
    void                            del_window( window const& wndw );
    context&                        new_context( window const& window,
                                                 context::settings const& settings = context::settings() );
    void                            del_context( context const& cntx );
    void                            attach_context( window const& window,
                                                    context& context );
    void                            activate_context( context& context );
    context const&                  get_active_context() const;
    context&                        get_active_context();
    program&                        new_program( program::settings const& settings =
                                                    program::settings() );
    void                            del_program( program const& prgm );
    buffer&                         new_buffer( buffer::settings const& settings );
    void                            del_buffer( buffer const& buff );
    friend std::ostream&            operator <<( std::ostream& out,
                                                 video_manager const& rhs);
private:
    bool                                owns( window const& wndw );
    bool                                owns( context const& cntx );
    bool                                owns( program const& prgm );
    bool                                owns( buffer const& buff );
    
    typedef std::map<size_t, window*>   window_map;
    window_map*                         windows;
    size_t                              nxt_w_id;
    
    typedef std::map<size_t, context*>  context_map;
    context_map*                        contexts;
    size_t                              nxt_c_id;
    context*                            active_context;
    
    typedef std::map<size_t, program*>  program_map;
    program_map*                        programs;
    size_t                              nxt_p_id;
    
    typedef std::map<size_t, buffer*>   buffer_map;
    buffer_map*                         buffers;
    size_t                              nxt_b_id;
    
    bool                                zombie;
};

inline  video_manager::settings::settings() :
                                    maj_ver_v( 1u ),
                                    min_ver_v( 4u ),
                                    profile_v( SDL_GL_CONTEXT_PROFILE_CORE ) {}

inline video_manager::settings&
video_manager::settings::maj_ver( unsigned int maj_ver )
{ maj_ver_v = maj_ver; return *this; }

inline video_manager::settings&
video_manager::settings::min_ver( unsigned int min_ver )
{ min_ver_v = min_ver; return *this; }

inline video_manager::settings&
video_manager::settings::core_profile()
{ profile_v = SDL_GL_CONTEXT_PROFILE_CORE; return *this; }

inline video_manager::settings&
video_manager::settings::compatibility_profile()
{ profile_v = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY; return *this; }

inline video_manager::settings&
video_manager::settings::es_profile()
{ profile_v = SDL_GL_CONTEXT_PROFILE_ES; return *this; }

inline  context const&    video_manager::get_active_context() const
{ return *active_context; }

inline  context&    video_manager::get_active_context()
{ return *active_context; }

inline  bool    context::is_active() const
{ return (*this) == owner->get_active_context(); }

inline  bool    video_manager::owns( window const& wndw )
{ return this == wndw.owner; }

inline  bool    video_manager::owns( context const& cntx )
{ return this == cntx.owner; }

inline  bool    video_manager::owns( program const& prgm )
{ return this == prgm.owner; }

inline  bool    video_manager::owns( buffer const& buff )
{ return this == buff.owner; }

}

#endif