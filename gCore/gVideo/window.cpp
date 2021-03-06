namespace gfx {
    /**
     * \brief Construct a new window object with the given settings.
     * \param set The all-purpose settings
     * \param set_3D The OpenGL-speicfic settings
     * \see gfx::window::settings
     * \see gfx::window::settings_3D
     */
    window::window( settings const& set,
                    settings_3D const& set_3D ) :
                    sys_window ( 0 )
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

        //SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, set_3D.maj_ver_v );
        //SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, set_3D.min_ver_v );
        
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

        sys_window = SDL_CreateWindow( set.title_v.c_str(),
                                           x_argument,
                                           y_argument,
                                           set.width_v,
                                           set.height_v,
                                           SDL_flags );
        if ( !sys_window ) {
            std::string msg( "Unable to create new system window.\n" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        // Can't get it to be created minimized!
        if ( set.minimized_v ) {
            SDL_MinimizeWindow( sys_window );
        }

        title_str = set.title_v;
    }
    /**
     * \brief Destruct the window.
     */
    
    window::~window()
    { SDL_DestroyWindow( sys_window );}
    /**
     * \brief Swap the double buffers.
     * 
     * This will display the latest changes in the window, which will persist
     * until \ref gfx::window::swap() "swap()" is called again.
     * \see gfx::context::clear_color()
     */
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
    /**
     * \brief Return the \ref gfx::window "window's" title.
     * \return The title of the window
     */
    std::string     window::title() const
    { return std::string( SDL_GetWindowTitle( sys_window ) ); }
    /**
     * \brief Set the \ref gfx::window "window's" title to the given string.
     * \param title The title of the window
     */
    void    window::title( std::string const& ttl )
    { SDL_SetWindowTitle( sys_window, ttl.c_str() ); }
    /**
     * \brief Return the \ref gfx::window "window's" x position.
     * \return The x position of the window, in pixels
     */
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
    /**
     * \brief Set the \ref gfx::window "window's" x position to the given value.
     * \param xp The x position of the window, in pixels
     */
    void     window::x_pos( int xp )
    {
        int ul_y = this->ul_corner()[1];
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, dw / -2 + xp, ul_y );
    }
    /**
     * \brief Return the \ref gfx::window "window's" y position.
     * \return The y position of the window, in pixels
     */
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
    /**
     * \brief Set the \ref gfx::window "window's" y position to the given value.
     * \param yp The y position of the window, in pixels
     */
    void     window::y_pos( int yp )
    {
        int ul_x = this->ul_corner()[0];
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, ul_x, dh / -2 + yp );
    }
    /**
     * \brief Return the \ref gfx::window "window's" x and y position.
     * \return The position of the window, in pixels
     */
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
    /**
     * \brief Set the \ref gfx::window "window's" x and y position to the given
     * values.
     * \param xp The x position of the window, in pixels
     * \param yp The y position of the window, in pixels
     */
    void     window::position( int xp,
                               int yp )
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, dw / -2 + xp, dh / -2 + yp );
    }
    /**
     * \brief Set the \ref gfx::window "window's" x and y position to the given
     * values.
     * \param pos The position of the window, in pixels
     */
    void     window::position( ivec2 const& pos )
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, dw / -2 + pos[0], dh / -2 + pos[1] );
    }
    /**
     * \brief Query the \ref gfx::window "window" to see if it set to be
     * centered on the x axis.
     */
    bool    window::is_x_centered() const
    {
        SDL_Rect bounds;
        SDL_GetDisplayBounds( 0, &bounds );
        
        SDL_Rect wndw_bounds;
        SDL_GetDisplayBounds( SDL_GetWindowDisplayIndex( sys_window ), &wndw_bounds );

        return wndw_bounds.x + wndw_bounds.w / 2 == bounds.w / 2;
    }
    /**
     * \brief Set the \ref gfx::window "window" to be centered on the x axis.
     * \see gfx::window::settings::center_y()
     * \see gfx::window::settings::center()
     */
    void    window::center_x()
    {
        int yp = this->y_pos();
        SDL_SetWindowPosition( sys_window, SDL_WINDOWPOS_CENTERED, yp );
    }
    /**
     * \brief Query the \ref gfx::window "window" to see if it set to be
     * centered on the y axis.
     */
    bool    window::is_y_centered() const
    {
        SDL_Rect bounds;
        SDL_GetDisplayBounds( 0, &bounds );
        
        SDL_Rect wndw_bounds;
        SDL_GetDisplayBounds( SDL_GetWindowDisplayIndex( sys_window ), &wndw_bounds );

        return wndw_bounds.y + wndw_bounds.h / 2 == bounds.h / 2;
    }
    /**
     * \brief Set the \ref gfx::window "window" to be centered on the y axis.
     * \see gfx::window::settings::center_x()
     * \see gfx::window::settings::center()
     */
    void    window::center_y()
    {
        int xp = this->x_pos();
        SDL_SetWindowPosition( sys_window, xp, SDL_WINDOWPOS_CENTERED );
    }
    /**
     * \brief Return the \ref gfx::window "window's" width.
     * \return The width of the window, in pixels
     */ 
    int     window::width() const
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        return dw;
    }
    /**
     * \brief Set the \ref gfx::window "window's" width to the given value.
     * \param dw The width of the window, in pixels
     */ 
    void     window::width( int dw )
    {
        int dh = this->height();
        SDL_SetWindowSize( sys_window, dw, dh );
    }
    /**
     * \brief Return the \ref gfx::window "window's" height.
     * \return dh The height of the window, in pixels
     */ 
    int     window::height() const
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        return dh;
    }
    /**
     * \brief Set the \ref gfx::window "window's" height to the given value.
     * \param dh The height of the window, in pixels
     */ 
    void     window::height( int dh )
    {
        int dw = this->width();
        SDL_SetWindowSize( sys_window, dw, dh );
    }
    /**
     * \brief Return the \ref gfx::window "window's" width and height.
     * \return The width and height of the window, in pixels
     */ 
    ivec2   window::dimensions() const
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        return ivec2( dw, dh );
    }
    /**
     * \brief Set the \ref gfx::window "window's" width and height to the given
     * values.
     * \param dw The width of the window, in pixels
     * \param dh The height of the window, in pixels
     */ 
    void    window::dimensions( int dw,
                                int dh )
    {
        SDL_SetWindowSize( sys_window, dw, dh );
    }
    /**
     * \brief Set the \ref gfx::window "window's" width and height to the given
     * values.
     * \param dim The width and height of the window, in pixels
     */ 
    void    window::dimensions( ivec2 const& dim )
    {
        SDL_SetWindowSize( sys_window, dim[0], dim[1] );
    }
    /**
     * \brief Return the \ref gfx::window "window's" upper left corner.
     * \return The upper left corner, in pixels
     * \see gfx::window::lr_corner()
     */
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
    /**
     * \brief Return the \ref gfx::window "window's" lower right corner.
     * \return The lower right corner, in pixels
     * \see gfx::window::ul_corner()
     */
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
    /**
     * \brief Set the \ref gfx::window "window's" corners.
     * \param ulx The upper left x coordinate
     * \param uly The upper left y coordinate
     * \param lrx The lower right x coordinate
     * \param lry The lower right y coordinate
     */
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
    /**
     * \brief Set the \ref gfx::window "window's" corners.
     * \param ulc The upper left corner
     * \param lrc The lower right corner
     */
    void    window::corners( ivec2 const& ulc,
                             ivec2 const& lrc )
    {
        ivec2 dim = lrc - ulc;
        SDL_SetWindowSize( sys_window, dim[0], dim[1] );
        SDL_SetWindowPosition( sys_window, ulc[0], ulc[1] );
    }
    /**
     * \brief Query that \ref gfx::window "window" to see if it is maximized.
     * \return Whether the window is maximized
     * \see gfx::window::maximize()
     */
    bool    window::is_maximized() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_MAXIMIZED ); }
    /**
     * \brief Maximize the \ref gfx::window "window".
     * \see gfx::window::minimize()
     */
    void    window::maximize()
    { SDL_MaximizeWindow( sys_window ); }
    /**
     * \brief Query that \ref gfx::window "window" to see if it is minimized.
     * \return Whether the window is minimized
     * \see gfx::window::minimize()
     */
    bool    window::is_minimized() const
    {
        // This doesn't work.  Sigh.
        return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_MINIMIZED );
    }
    /**
     * \brief Minimize the \ref gfx::window "window".
     * \see gfx::window::maximize()
     */
    void    window::minimize()
    { SDL_MinimizeWindow( sys_window ); }
    /**
     * \brief Query the \ref gfx::window "window" to see if it resizable.
     * \return Whether the window is resizable
     */
    bool    window::is_resizable() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_RESIZABLE ); }
    /**
     * \brief Query the \ref gfx::window "window" to see if is equipped for OpenGL.
     * \return Whether the window can use OpenGL
     */
    bool    window::has_3D() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_OPENGL ); }
    /**
     * \brief Query the \ref gfx::window "window" to see if it is visible.
     * \return Whether the window is visible
     */
    bool    window::is_visible() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_SHOWN ); }
    /**
     * \brief Make the \ref gfx::window "window" visible.
     * \see gfx::window::make_hidden()
     */
    void    window::make_visible()
    { SDL_ShowWindow( sys_window ); }
    /**
     * \brief Make the \ref gfx::window "window" invisible.
     * \see gfx::window::make_visible()
     */
    void    window::make_hidden()
    { SDL_HideWindow( sys_window ); }
    /**
     * \brief Query the \ref gfx::window "window" if it has a border.
     * \return Whether the window has a border
     */
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
}