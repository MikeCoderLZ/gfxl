#include <stdexcept>
#include <fstream>
#include <string>
#include "gl_core_3_3.hpp"
#include "video_manager.hpp"
#include "SDL.h"

namespace gfx {
    
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
        int xp;
        int yp;
        SDL_GetWindowPosition( sys_window, &xp, &yp );
        return xp;
    }
    
    void     window::x_pos( int xp )
    {
        int yp = this->y_pos();
        SDL_SetWindowPosition( sys_window, xp, yp );
    }
    
    int     window::y_pos() const
    {
        int xp;
        int yp;
        SDL_GetWindowPosition( sys_window, &xp, &yp );
        return yp;
    }
    
    void     window::y_pos( int yp )
    {
        int xp = this->x_pos();
        SDL_SetWindowPosition( sys_window, xp, yp );
    }
    
    ivec2   window::position() const
    {
        int xp;
        int yp;
        SDL_GetWindowPosition( sys_window, &xp, &yp );
        return ivec2( xp, yp );
    }
    
    void     window::position( int xp,
                               int yp )
    {
        SDL_SetWindowPosition( sys_window, xp, yp );
    }
    
    void     window::position( ivec2 const& pos )
    {
        SDL_SetWindowPosition( sys_window, pos[0], pos[1] );
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
    
//     ivec2   window::ul_corner() const
//     {
//         int ulx = this->width() / -2 + this->x_pos();
//         int uly = this->height() / -2 + this->y_pos();
//         return ivec2( ulx, uly );
//     }
//     
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
//     
//     ivec2   window::lr_corner() const
//     {
//         int lrx = this->width() / 2 + this->x_pos();
//         int lry = this->height() / 2 + this->y_pos();
//         return ivec2( lrx, lry );
//     }
//     
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
//     
//     void    window::corners( int ulx,
//                              int uly,
//                              int lrx,
//                              int lry )
//     {
//         ivec2 ulc ( ulx, uly );
//         ivec2 lrc ( lrx, lry );
//         ivec2 dim = lrc - ulc;
//         ivec2 pos = ulc + dim / 2;
//         SDL_SetWindowSize( sys_window, dim[0], dim[1] );
//         SDL_SetWindowPosition( sys_window, pos[0], pos[1] );
//     }
//     
//     void    window::corners( ivec2 const& ulc,
//                              ivec2 const& lrc )
//     {
//         ivec2 dim = lrc - ulc;
//         ivec2 pos = ulc + dim / 2;
//         SDL_SetWindowSize( sys_window, dim[0], dim[1] );
//         SDL_SetWindowPosition( sys_window, pos[0], pos[1] );
//     }
    
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
    
    
    video_manager::video_manager()
    {
        this->windows = new window_vector();
        //this->contexts = new context_vector();
    //     this->programs = new program_vector();
    //     this->buffers = new buffer_vector();
    //     active_context = 0;

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
        window_vector::iterator i;
        for( i = windows->begin(); i != windows->end(); ++i)
            { delete *i; }
        delete windows;

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
    
    window& video_manager::new_window( window::settings const& set )
    {

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

        int x_argument = set.center_x_v;

        if ( set.center_on_x ) {
            x_argument = SDL_WINDOWPOS_CENTERED;
        }

        int y_argument = set.center_y_v;

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

        window* new_window = new window( set.title_v, this, new_sys_window );
        windows->push_back( new_window );
        return *new_window;
    }
    
//     void    video_manager::del_window( window const& wndw )
//     {
//         if ( this->owns( wndw ) ) {
//             
//         }
//     }
    
}