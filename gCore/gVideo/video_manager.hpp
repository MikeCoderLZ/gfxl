#ifndef VIDEO_MANAGER_HPP
#define VIDEO_MANAGER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "checkError.hpp"
#include "SDL.h"
#include "gl_core_3_3.hpp"
#include "../gUtility/datatypeinfo.hpp"
#include "../gMath/datatype.hpp"


namespace gfx {

class video_manager;

// class managed {
// protected:
//     video_manager*  owner;
//     size_t          index;
// };

class window {
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
//     ivec2                   ul_corner() const;
//     void                    ul_corner( int ulx, int uly );
//     void                    ul_corner( ivec2 const& ulc );
//     ivec2                   lr_corner() const;
//     void                    lr_corner( int lrx, int lry );
//     void                    lr_corner( ivec2 const& lrc );
//     void                    corners( int ulx,
//                                      int uly,
//                                      int lrx,
//                                      int lry );
//     void                    corners( ivec2 ulc,
//                                      ivec2 lrc );
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
            settings&           center_x_at( int cx );
            settings&           center_y_at( int cy );
            settings&           center_at( int cx,
                                           int cy );
            settings&           center_x();
            settings&           center_y();
            settings&           center();
            settings&           width( int dw );
            settings&           height( int dh );
            settings&           dimensions( int dw,
                                            int dh );
            settings&           corners( int upper_l_x,
                                         int upper_l_y,
                                         int lower_r_x,
                                         int lower_r_y );
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
            int                 center_x_v;
            int                 center_y_v;
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
    
private:
    friend                  class video_manager;
                            window( std::string const& title,
                                    video_manager* const owner,
                                    SDL_Window* sys_window );
    std::string             title_str;
    video_manager* const    owner;
    SDL_Window*             sys_window;
};

std::ostream&   operator <<( std::ostream& out, window const& rhs );

inline  window::settings::settings() :
            title_v         ("untitled"),
            center_x_v      (-1),         center_y_v      (-1),
            // Terrible default!!!!!! FIX ME WITH DYNAMIC SIZE!!!!
            width_v         (512),        height_v        (512),
            center_on_x     (true),       center_on_y     (true),
            minimized_v     (false),      maximized_v     (false),
            fullscreen_v    (false),
            resizable_v     (false),
            uses_opengl     (false),
            visible_v       (true),
            has_border_v    (true),
            has_focus_v     (false),
            grab_input_v    (false)  {};
            
inline  window::settings&     window::settings::title( std::string const& title )
{ title_v = title; return *this; }

inline  window::settings&     window::settings::center_x_at( int cx )
{   center_x_v = cx;
    center_on_x = false;
    return *this; }
    
inline  window::settings&     window::settings::center_y_at( int cy )
{   center_y_v = cy;
    center_on_y = false;
    return *this; }
    
inline  window::settings&     window::settings::center_at( int cx,
                                                           int cy )
{   center_y_v = cy;
    center_x_v = cx;
    center_on_x = false;
    center_on_y = false;
    return *this; }
    
inline  window::settings&     window::settings::width( int dw )
{ width_v = dw; return *this; }

inline  window::settings&     window::settings::height( int dh )
{ height_v = dh; return *this; }

inline  window::settings&     window::settings::dimensions( int dw,
                                                            int dh )
{ width_v = dw; height_v = dh; return *this; }

inline  window::settings&     window::settings::corners( int upper_l_x,
                                                         int upper_l_y,
                                                         int lower_r_x,
                                                         int lower_r_y )
{
    width_v = lower_r_x - upper_l_x;
    height_v = lower_r_y - upper_l_y;
    center_x_v = upper_l_x + width_v / 2;
    center_y_v = upper_l_y + height_v / 2;
    center_on_x = false;
    center_on_y = false;
    return *this;    
}

inline  window::settings&     window::settings::center_x()
{   center_on_x = true;
    center_x_v = -1;
    return *this; }
    
inline  window::settings&     window::settings::center_y()
{   center_on_y = true;
    center_y_v = -1;
    return *this; }
    
inline  window::settings&     window::settings::center()
{   center_on_x = true;
    center_on_y = true;
    center_x_v = -1;
    center_y_v = -1;
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

inline  window::~window()
{}



inline  bool    window::operator ==( window const& rhs ) const
{ return this->sys_window == rhs.sys_window; }

inline  window::window( std::string const& title,
                        video_manager* const owner,
                        SDL_Window* system_window ) :
                            title_str ( title ), owner( owner ),
                            sys_window( system_window ) {};

// class context {
// public:
//     void                    clear_color( float red, float green,
//                                          float blue, float alpha = 1.0f );
//     bool                    is_active() const;
//     bool                    operator ==( context const& rhs ) const;
//     
//     class settings {
//     public:
//                             settings();
//         settings&           major_version( unsigned int maj_ver);
//         settings&           minor_version( unsigned int min_ver);
//         settings&           depth_size( unsigned int bits);
//         settings&           double_buffered();
//         settings&           not_double_buffered();
//     private:
//         friend              class video_manager;
//         unsigned int        maj_ver;
//         unsigned int        min_ver;
//         unsigned int        depth_bits;
//         bool                is_double_buffered;
//     };
//     
// private:
//     friend                  class video_manager;
//                             context( video_manager* const manager,
//                                      window const* target_window,
//                                      SDL_GLcontext sys_context);
//     video_manager* const     manager;
//     Window const*           target_window;
//     SDL_GLcontext           sys_context;
// };
// 
// class program {
// public:
//     void                    compile();
//     void                    link();
//     void                    use();
//     friend std::ostream&    operator <<( std::ostream& out, program const& rhs );
//     GLuint                  getProgID() const { return prog_ID; }
//     
//     class settings {
//     public:
//                             settings();
//         settings&           major_version( unsigned int maj_ver);
//         settings&           minor_version( unsigned int min_ver);
//         settings&           uses_vert();
//         settings&           uses_frag();
//         settings&           uses_geom();
//         // settings& uses_tess(); /** Needs ARB extension */
//         settings&           uses_vert( std::string const& path );
//         settings&           uses_frag( std::string const& path );
//         settings&           uses_geom( std::string const& path );
//         // settings& uses_tess( std::string const& path ); /** Needs ARB extension */
//         settings&           no_vert();
//         settings&           no_frag();
//         settings&           no_geom();
//         //settings& no_tess();/** Needs ARB extension */
//     private:
//         friend              class video_manager;
//         std::string         vert_path;
//         std::string         frag_path;
//         std::string         geom_path;
//         //std::string tess_path;
//         unsigned int        maj_ver;
//         unsigned int        min_ver;
//         bool                has_vert_shader;
//         bool                has_frag_shader;
//         bool                has_geom_shader;
//         bool                has_tess_shader;
//     };
// 
// private:
//     friend                  class video_manager;
//                             program( video_manager* const manager );
//     void                    compile( GLuint stage_ID, std::string const& stage_path );
//     video_manager* const    manager;
//     std::string             vert_path;
//     std::string             frag_path;
//     std::string             geom_path;
//     GLuint                  vert_ID;
//     GLuint                  frag_ID;
//     GLuint                  geom_ID;
//     GLuint                  tess_ID;
//     GLuint                  prog_ID;
//     unsigned int            maj_ver;
//     unsigned int            min_ver;
// };
// 
// class block_spec {
// public:
//     friend                          class buffer;
//                                     block_spec();
//                                     ~block_spec();
//     template< typename T >
//     block_spec&                     attribute( type<T> const& proto );
// private:
//     typedef std::vector< info* >    attrib_vector;
//     attrib_vector*                  attributes;
// };
// 
// class buffer {
// public:
//     friend                      class video_manager;
//     friend std::ostream&        operator <<( std::ostream& out, buffer const& rhs );
//                                 ~buffer();
//     void                        block_format( block_spec const& spec );
//     void                        blocks( GLsizeiptr const blocks );
//     void                        add_blocks( GLsizeiptr const more_blocks );
//     template< typename DATA >
//     void                        fill_attribute( GLuint index,
//                                                 std::vector< DATA > const& attrib_data );
//     void                        load_data();
//     void                        align_vertices();
//     GLuint                      get_id() const { return buff_id; }
//     
//     class settings {
//     public:
//         friend              class video_manager;
//                             settings();
//         settings&           blocks( GLsizeiptr new_n_blocks );
//         settings&           static_draw();
//         settings&           static_read();
//         settings&           static_copy();
//         settings&           dynamic_draw();
//         settings&           dynamic_read();
//         settings&           dynamic_copy();
//         settings&           stream_draw();
//         settings&           stream_read();
//         settings&           stream_copy();
//         settings&           for_array();
//     //    settings&     for_atomic_counter();
//         settings&           for_copy_read();
//         settings&           for_copy_write();
//     //    settings&     for_indirect_draw();
//     //    settings&     for_indirect_dispatch();
//         settings&           for_element_array();
//         settings&           for_pixel_packing();
//         settings&           for_pixel_unpacking();
//     //    settings&     for_shader_storage();
//         settings&           for_texture();
//         settings&           for_transform_feedback();
//         settings&           for_uniform();
//     private:
//         GLsizeiptr          n_blocks;
//         GLenum              usage;
//         GLenum              intended_target;
//     };
//     
// private:
//     video_manager*              manager;
//     unsigned char*              data;
//     GLsizeiptr                  n_blocks;
//     GLsizeiptr                  stride;
//     GLuint                      vao_id;
//     GLuint                      buff_id;
//     GLenum                      usage;
//     GLenum                      intended_target;
//     bool                        data_loaded;
//     bool                        verts_specified;
//     typedef std::vector<info*>  attrib_vector;
//     attrib_vector*              attributes;
//                                 buffer( video_manager* new_manager,
//                                         GLsizeiptr new_n_blocks,
//                                         GLuint new_vao_id,
//                                         GLuint new_buff_id,
//                                         GLenum new_usage,
//                                         GLenum new_target );
//     GLsizeiptr                  attribute_offset( GLuint index ) const;
// };


class video_manager {
public:
                                    video_manager();
                                    ~video_manager();
    window&                         new_window( window::settings const& settings = window::settings() );
    //void                            del_window( window const& wndw );
//     context&                        new_context( window const& window,
//                                                  context::settings const& settings = context::settings() );
//     void                            attach_context( window const& window,
//                                                     context& context );
//     void                            activate_context( context& context );
//     context&                        get_active_context() const;
//     program&                        new_program( program::settings const& settings = program::settings() );
//     buffer&                         new_buffer( buffer::settings const& settings );
    friend std::ostream&            operator <<( std::ostream& out, video_manager const& rhs);
private:
//     bool                            owns( context const& context );
    bool                            owns( window const& wndw );
//     bool                            owns( program const& program );
    typedef std::vector<window*>    window_vector;
//     typedef std::vector<context*>   context_vector;
//     typedef std::vector<program*>   program_vector;
//     typedef std::vector<buffer*>    buffer_vector;
    window_vector*                  windows;
//     context_vector*                 contexts;
//     program_vector*                 programs;
//     buffer_vector*                  buffers;
//     context*                        active_context;
};

inline  bool    video_manager::owns( window const& wndw )
{ return this == wndw.owner; }

}

#endif