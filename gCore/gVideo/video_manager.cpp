#include <stdexcept>
#include <fstream>
#include <string>
#include "gl_core_3_3.hpp"
#include "video_manager.hpp"
#include "SDL.h"

namespace gfx {
    
    window::~window()
    {
        owner->del_window( *this );
    }
    void window::swap()
    {
        if ( this->has_3D() ) {
            /* This makes our buffer swap synchronized with the monitor's vertical refresh */
            // I don't like this here.  Needs to be somewhere else more central.
            SDL_GL_SetSwapInterval(1);
            SDL_GL_SwapWindow( sys_window );
        } else {
            std::string msg = "window::swap() called on window '";
            msg += title_str;
            msg += "', which does not support OpenGL.";
            throw std::logic_error( msg );
        }
    }
    
    std::string     window::title() const
    { return std::string( SDL_GetWindowTitle( sys_window ) ); }
    
    void    window::title( std::string const& ttl )
    { SDL_SetWindowTitle( sys_window, ttl.c_str() ); }
    
    int     window::x_pos() const
    {
        int ul_x;
        int ul_y;
        SDL_GetWindowPosition( sys_window, &ul_x, &ul_y );
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        return ul_x + dw / 2;
    }
    
    void     window::x_pos( int xp )
    {
        int ul_y = this->ul_corner()[1];
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, dw / -2 + xp, ul_y );
    }
    
    int     window::y_pos() const
    {
        int ul_x;
        int ul_y;
        SDL_GetWindowPosition( sys_window, &ul_x, &ul_y );
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        return ul_y + dh / 2;
    }
    
    void     window::y_pos( int yp )
    {
        int ul_x = this->ul_corner()[0];
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, ul_x, dh / -2 + yp );
    }
    
    ivec2   window::position() const
    {
        int ul_x;
        int ul_y;
        SDL_GetWindowPosition( sys_window, &ul_x, &ul_y );
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );

        return ivec2( ul_x + dw / 2, ul_y + dh / 2 );
    }
    
    void     window::position( int xp,
                               int yp )
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, dw / -2 + xp, dh / -2 + yp );
    }
    
    void     window::position( ivec2 const& pos )
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, dw / -2 + pos[0], dh / -2 + pos[1] );
    }
    
    bool    window::is_x_centered() const
    {
        SDL_Rect bounds;
        SDL_GetDisplayBounds( 0, &bounds );
        
        SDL_Rect wndw_bounds;
        SDL_GetDisplayBounds( SDL_GetWindowDisplayIndex( sys_window ), &wndw_bounds );

        return wndw_bounds.x + wndw_bounds.w / 2 == bounds.w / 2;
    }
    
    void    window::center_x()
    {
        int yp = this->y_pos();
        SDL_SetWindowPosition( sys_window, SDL_WINDOWPOS_CENTERED, yp );
    }
    
    bool    window::is_y_centered() const
    {
        SDL_Rect bounds;
        SDL_GetDisplayBounds( 0, &bounds );
        
        SDL_Rect wndw_bounds;
        SDL_GetDisplayBounds( SDL_GetWindowDisplayIndex( sys_window ), &wndw_bounds );

        return wndw_bounds.y + wndw_bounds.h / 2 == bounds.h / 2;
    }
    
    void    window::center_y()
    {
        int xp = this->x_pos();
        SDL_SetWindowPosition( sys_window, xp, SDL_WINDOWPOS_CENTERED );
    }

    int     window::width() const
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        return dw;
    }
    
    void     window::width( int dw )
    {
        int dh = this->height();
        SDL_SetWindowSize( sys_window, dw, dh );
    }
    
    int     window::height() const
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        return dh;
    }
    
    void     window::height( int dh )
    {
        int dw = this->width();
        SDL_SetWindowSize( sys_window, dw, dh );
    }
    
    ivec2   window::dimensions() const
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        return ivec2( dw, dh );
    }
    
    void    window::dimensions( int dw,
                                int dh )
    {
        SDL_SetWindowSize( sys_window, dw, dh );
    }
    
    void    window::dimensions( ivec2 const& dim )
    {
        SDL_SetWindowSize( sys_window, dim[0], dim[1] );
    }
    
    ivec2   window::ul_corner() const
    {
        int ulx;
        int uly;
        SDL_GetWindowPosition( sys_window, &ulx, &uly );
        return ivec2( ulx, uly );
    }
    
//     void    window::ul_corner( int ulx,
//                                int uly )
//     {
//         ivec2 ulc = this->ul_corner();
//         int delta_x = ulc[0] - ulx;
//         int delta_y = ulc[1] - uly;
//         ivec2 dim = this->dimensions();
//         int dw = dim[0] + delta_x;
//         int dh = dim[1] + delta_y;
//         ivec2 pos = this->position();
//         int dx = delta_x / -2 + pos[0];
//         int dy = delta_y / -2 + pos[1];
//         SDL_SetWindowSize( sys_window, dw, dh );
//         SDL_SetWindowPosition( sys_window, dx, dy );
//     }
//     
//     void    window::ul_corner( ivec2 const& ulc )
//     {
//         ivec2 delta = this->ul_corner() - ulc;
//         ivec2 dim = this->dimensions() + delta;
//         ivec2 pos = delta / -2 + this->position();
//         SDL_SetWindowSize( sys_window, dim[0], dim[1] );
//         SDL_SetWindowPosition( sys_window, pos[0], pos[1] );
//     }
    
    ivec2   window::lr_corner() const
    { return this->ul_corner() + this->dimensions(); }
    
//     void    window::lr_corner( int lrx,
//                                int lry )
//     {
//         ivec2 lrc = this->ul_corner();
//         int delta_x = lrc[0] - lrx;
//         int delta_y = lrc[1] - lry;
//         ivec2 dim = this->dimensions();
//         int dw = dim[0] + delta_x;
//         int dh = dim[1] + delta_y;
//         ivec2 pos = this->position();
//         int dx = delta_x / 2 + pos[0];
//         int dy = delta_y / 2 + pos[1];
//         SDL_SetWindowSize( sys_window, dw, dh );
//         SDL_SetWindowPosition( sys_window, dx, dy );
//     }
//     
//     void    window::lr_corner( ivec2 const& lrc )
//     {
//         ivec2 delta = this->lr_corner() - lrc;
//         ivec2 dim = this->dimensions() + delta;
//         ivec2 pos = delta / 2 + this->position();
//         SDL_SetWindowSize( sys_window, dim[0], dim[1] );
//         SDL_SetWindowPosition( sys_window, pos[0], pos[1] );
//     }
    
    void    window::corners( int ulx,
                             int uly,
                             int lrx,
                             int lry )
    {
        ivec2 ulc ( ulx, uly );
        ivec2 lrc ( lrx, lry );
        ivec2 dim = lrc - ulc;
        SDL_SetWindowSize( sys_window, dim[0], dim[1] );
        SDL_SetWindowPosition( sys_window, ulc[0], ulc[1] );
    }
    
    void    window::corners( ivec2 const& ulc,
                             ivec2 const& lrc )
    {
        ivec2 dim = lrc - ulc;
        SDL_SetWindowSize( sys_window, dim[0], dim[1] );
        SDL_SetWindowPosition( sys_window, ulc[0], ulc[1] );
    }
    
    bool    window::is_maximized() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_MAXIMIZED ); }
    
    void    window::maximize()
    { SDL_MaximizeWindow( sys_window ); }
    
    bool    window::is_minimized() const
    {
        // This doesn't work.  Sigh.
        return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_MINIMIZED );
    }
    
    void    window::minimize()
    { SDL_MinimizeWindow( sys_window ); }
    
    bool    window::is_resizable() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_RESIZABLE ); }
    
    bool    window::has_3D() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_OPENGL ); }
    
    bool    window::is_visible() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_SHOWN ); }
    
    void    window::make_visible()
    { SDL_ShowWindow( sys_window ); }
    
    void    window::make_hidden()
    { SDL_HideWindow( sys_window ); }
    
    bool    window::has_border() const
    { return not bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_BORDERLESS ); }
    
//     bool    window::is_fullscreen() const
//     { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_FULLSCREEN ); }
//     
// //     void    window::make_fullscreen()
// //     { SDL_SetWindowFullscreen( sys_window, 0 ); }

//     bool    window::has_focus() const
//     { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_INPUT_FOCUS ); }
//     
//     std::ostream& operator <<( std::ostream& out, window const& rhs)
//     {
//         out << rhs.title_str;
//         return out;
//     }
    
    context::~context()
    {
        owner->del_context( *this );
    }
    
    void context::clear_color( float red, float green, float blue, float alpha )
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Render operation 'clear_color()' called on Context that is not active." );
        }

        gl::ClearColor( red, green, blue, alpha );
        gl::Clear( gl::COLOR_BUFFER_BIT );
    }
    
    unsigned int    context::major_version() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'major_version()' called on Context that is not active." );
        }
        int maj_ver;
        int ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, &maj_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'major_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return (unsigned int)  maj_ver;
    }
    
    unsigned int    context::minor_version() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'minor_version()' called on Context that is not active." );
        }
        int min_ver;
        int ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, &min_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'minor_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return (unsigned int) min_ver ;
    }
    
    uvec2    context::version() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'version()' called on Context that is not active." );
        }
        int maj_ver;
        int ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, &maj_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'major_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        
        int min_ver;
        ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, &min_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'minor_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return uvec2( (unsigned int) maj_ver, (unsigned int) min_ver );
    }
    
    unsigned int    context::depth_bits() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'depth_bits()' called on Context that is not active." );
        }
        int bits;
        int ret = SDL_GL_GetAttribute( SDL_GL_DEPTH_SIZE, &bits );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'depth_bits()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return (unsigned int) bits;
    }
    
    bool    context::double_buffered() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'double_buffered()' called on Context that is not active." );
        }
        int buffed;
        int ret = SDL_GL_GetAttribute( SDL_GL_DOUBLEBUFFER, &buffed );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'double_buffered()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return bool( buffed );
    }
    
    video_manager::video_manager( video_manager::settings const& set ) :
        windows( new window_map() ),
        nxt_w_id( 0 ),
        contexts( new context_map() ),
        nxt_c_id( 0 ),
        active_context( 0 ),
        zombie( false )
    {
        // These three OpenGL attributes must be set before any window
        // which uses OpenGL can be created. If you create two
        // video_manager objects with different settings and create
        // windows with the first before the second, then all the windows
        // created by the second will inherit the first's settings and
        // it's own will have no effect.
        // At least that is what the docs say.
        // So that is why this setting information is discarded:
        // After the first set, it won't matter.
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK,  set.profile_v );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, set.maj_ver_v );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, set.min_ver_v );
        if ( not SDL_WasInit( SDL_INIT_VIDEO ) ) {
            if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
                std::string msg ("Cannot initialize SDL Video subsystem:\n");
                msg += SDL_GetError();
                throw std::runtime_error( msg );
            }
        }
    }

    video_manager::~video_manager()
    {
        /* There is a serious dangling pointer problem; if
        * an object the Manager has constructed goes out of
        * scope then when video_manager either tries to provide
        * that object to someone else or somehow deletes itself
        * before the program finishes then it will try to delete
        * empty memory, and that will be messy.  Constructed
        * objects need to report to the Manager that they are
        * dying. */
        zombie = true;
        contexts->clear();
        windows->clear();
        

//         context_vector::iterator j;
//         for( j = contexts->begin(); j != contexts->end(); ++j)
//             { delete *j; }
//         delete contexts;
// 
//         program_vector::iterator k;
//         for( k = programs->begin(); k != programs->end(); ++k)
//             { delete *k; }
//         delete programs;
// 
//         buffer_vector::iterator u;
//         for( u = buffers->begin(); u != buffers->end(); ++u)
//             { delete *u; }
//         delete buffers;
    }
    
    window& video_manager::new_window( window::settings const& set,
                                       window::settings_3D const& set_3D )
    {
        SDL_GL_SetAttribute( SDL_GL_RED_SIZE, set_3D.r_bits_v );
        SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, set_3D.g_bits_v );
        SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, set_3D.b_bits_v );
        SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, set_3D.a_bits_v );
        
        SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, set_3D.framebuffer_bits_v );
        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, set_3D.depth_bits_v );
        SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, set_3D.stencil_bits_v );
        if ( set_3D.doublebuffered_v ) {
            SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
        } else {
            SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 0 );
        }
        
        SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, set_3D.r_accumulator_bits_v );
        SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, set_3D.g_accumulator_bits_v );
        SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, set_3D.b_accumulator_bits_v );
        SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, set_3D.a_accumulator_bits_v );
        
        if ( set_3D.in_stereo_v ) {
            SDL_GL_SetAttribute( SDL_GL_STEREO, 1 );
        }
        
        if ( set_3D.multisample_v ) {
            SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
            SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, set_3D.samples_v );
        }
        
        if ( set_3D.force_hw_v ) {
            SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
        }
        
        if ( set_3D.force_sw_v ) {
            SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 0 );
        }

        int SDL_flags = 0;

        if ( set.minimized_v ) {
            SDL_flags |= SDL_WINDOW_MINIMIZED;
        } else if ( set.maximized_v ) {
            SDL_flags |= SDL_WINDOW_MAXIMIZED;
        } else if ( set.fullscreen_v ) {
            SDL_flags |= SDL_WINDOW_FULLSCREEN;
        }

        if ( set.resizable_v ) {
            SDL_flags |= SDL_WINDOW_RESIZABLE;
        }

        if ( set.uses_opengl ) {
            SDL_flags |= SDL_WINDOW_OPENGL;
        }

        if ( set.visible_v ) {
            SDL_flags |= SDL_WINDOW_SHOWN;
        }

        if ( not set.has_border_v ) {
            SDL_flags |= SDL_WINDOW_BORDERLESS;
        }
        
        if ( set.has_focus_v ) {
            SDL_flags |= SDL_WINDOW_INPUT_FOCUS;
        }

        if ( set.grab_input_v ) {
            SDL_flags |= SDL_WINDOW_INPUT_GRABBED;
        }

        int x_argument = set.ulc_v[0];

        if ( set.center_on_x ) {
            x_argument = SDL_WINDOWPOS_CENTERED;
        }

        int y_argument = set.ulc_v[1];

        if ( set.center_on_y ) {
            y_argument = SDL_WINDOWPOS_CENTERED;
        }

        SDL_Window* new_sys_window = SDL_CreateWindow( set.title_v.c_str(),
                                                        x_argument,
                                                        y_argument,
                                                        set.width_v,
                                                        set.height_v,
                                                        SDL_flags );
        if ( !new_sys_window ) {
            std::string msg( "Unable to create new system window.\n" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        // Can't get it to be created minimized!
        if ( set.minimized_v ) {
            SDL_MinimizeWindow( new_sys_window );
        }

        window* new_window = new window( set.title_v, this, nxt_w_id, new_sys_window );
        (*windows)[nxt_w_id] = new_window;
        ++nxt_w_id;
        return *new_window;
    }
    
    void    video_manager::del_window( window const& wndw )
    {
        if ( this->owns( wndw ) ) {
            SDL_DestroyWindow( wndw.sys_window );
            if ( not this->zombie ) {
                // Someone else is calling the deletion
                windows->erase( wndw.g_id );
            }
            // If we are not a zombie, we are destructing
            // the video_manager and do not want a looping
            // deletion cascade, where the window is deleted
            // by windows->clear() which calls this function
            // which in turn calls ~window() when
            // windows->erase( ... ) is used.
            // Since ~window() is already being called on the
            // pointer in the map, no memory is
            // leaking.
        }
    }
    
    context& video_manager::new_context( window const& window,
                                         context::settings const& settings )
    {
        if ( not window.has_3D() ) {
            std::string msg = "The creation of a context current in window '";
            msg += window.title();
            msg += "', was attempted, but this window does not support OpenGL.";
            throw std::logic_error( msg );
        }

        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, settings.maj_ver );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, settings.min_ver );

        int doubleBuffered = (settings.is_double_buffered ? 1 : 0 );
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, doubleBuffered );

        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, settings.depth_bits_v );

        SDL_GLContext new_sys_context = SDL_GL_CreateContext( window.sys_window );

        context* new_context = new context( this, nxt_c_id, &window, new_sys_context );

        (*contexts)[nxt_c_id] = new_context;
        ++nxt_c_id;
        
        activate_context( *new_context );        
        
        return *new_context;
    }
    
    void    video_manager::del_context( context const& cntx )
    {
        if ( this->owns( cntx ) ) {
            SDL_GL_DeleteContext( cntx.sys_context );
            if ( not this->zombie ) {
                // Someone else is calling the deletion
                contexts->erase( cntx.g_id );
            }
        }
    }
    
    void video_manager::activate_context( context& cntx )
    {
        if ( (not owns( *cntx.target_window )) or (not owns( cntx )) ) {
            std::string msg = "Illegal activation of Context on Window '";
            msg += cntx.target_window->title();
            msg += "': ";
            if ( not owns( *cntx.target_window ) ) {
                msg += "Window not owned by manager. ";
            }
            if ( not owns( cntx ) ) {
                msg += "Context not owned by manager.";
            }
            throw std::logic_error( msg );
        }

        SDL_GL_MakeCurrent( cntx.target_window->sys_window, cntx.sys_context );
        active_context = &cntx;
    }
    
}