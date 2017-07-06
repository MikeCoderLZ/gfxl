namespace gfx {

    /**
     * \brief Construct a new gfx::context targeting the given
     * window with the given settings.
     * 
     * \param window The target window for the context
     * \param set The settings for the new context
     * @exception std::logic_error If the given window does not support OpenGL,
     * a standard logic error is thrown.
     */
    context::context( window const& window,
                      settings const& set  ) :
                          target_window( &window )
    {
        if ( not window.has_3D() ) {
            std::string msg = "The creation of a context current in window '";
            msg += window.title();
            msg += "', was attempted, but this window does not support OpenGL.";
            throw std::logic_error( msg );
        }
        
        int doubleBuffered = (set.is_double_buffered ? 1 : 0 );
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, doubleBuffered );

        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, (int) set.n_depth_bits );
        
        sys_context = SDL_GL_CreateContext( window.sys_window );
        
        video_system::get().register_context( this );
        video_system::get().activate_context( *this );        
    }
    
    /**
     * \brief Destruct the gfx::context object.
     * \todo Review the 'zombie flag'.
     */
    context::~context()
    {
        // I suspect this implementation of the zombie flag isn't useful,
        // since it would mean that the video_system has been deleted,
        // which can't happen before literally anything else because its
        // creation is hardcoded. A better zombie flag would exist outside
        // the video_system in a pseudo-globally scoped flag because
        // trying to access the video_system's zombie flag would be
        // impossible if had been deleted; if such a situation were to
        // arise then you'd probably get sporatic segmentation faults at
        // the end of execution. I'd have to blame multithreading in that
        // case.
        // 
        // But paranoia usually prevails.
        
        if ( not video_system::get().zombie ) {
            video_system::get().unregister_context( this );
        }
        SDL_GL_DeleteContext( sys_context );
    }
    /**
     * \brief Clear the gfx::context framebuffer to the given
     * color.
     * 
     * \param red The value of the red chanel on [0.0f, 1.0f]
     * \param green The value of the green chanel on [0.0f, 1.0f]
     * \param blue The value of the blue chanelon [0.0f, 1.0f]
     * \param alpha The value of the alpha chanel on [0.0f, 1.0f]
     * @exception std::logic_error If the context is not the active context, a
     * standard logic error is thrown.
     */
    void context::clear_color( float red, float green, float blue, float alpha )
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Render operation 'clear_color()' called on Context that is not active." );
        }

        gl::ClearColor( red, green, blue, alpha );
        gl::Clear( gl::COLOR_BUFFER_BIT );
        
        int isDoubleBuffered = 0;
        SDL_GL_GetAttribute( SDL_GL_DOUBLEBUFFER, &isDoubleBuffered );
        if (isDoubleBuffered ) {
            gl::Clear( gl::DEPTH_BUFFER_BIT );
        }
    }
    /**
     * \brief Query the gfx::context if it is the active context.
     * 
     * @return Whether or not the context is active.
     */
    bool    context::is_active() const
    { return (*this) == video_system::get().get_active_context(); }
    /**
     * \brief Query the gfx::context for the major version of
     * the context.
     * 
     * \todo Why do we even need this? Review for removal.
     * @return The major version number of the context.
     * @exception std::logic_error Calling this function on a context that is not
     * the active one generates a standard logic error.
     * @exception std::runtime_error If, for some reason, the query fails, a
     * standard runtime error will be thrwon.
     */
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
    /**
     * \brief Query the gfx::context for the minor version of
     * the context.
     * 
     * \todo Why do we even need this? Review for removal.
     * @return The minor version number of the context.
     * @exception std::logic_error Calling this function on a context that is not
     * the active one generates a standard logic error.
     * @exception std::runtime_error If, for some reason, the query fails, a
     * standard runtime error will be thrwon.
     */
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
    /**
     * \brief Query the gfx::context for the version of the
     * context.
     * 
     * \todo Why do we even need this? Review for removal. If it is kept,
     * then change the return type to a gfx::version object.
     * @return The version number of the context, represented as a vec2
     * @exception std::logic_error Calling this function on a context that is not
     * the active one generates a standard logic error.
     * @exception std::runtime_error If, for some reason, the query fails, a
     * standard runtime error will be thrwon.
     */
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
    /**
     * \brief Query the gfx::context for the number of depth
     * bits it uses.
     * 
     * @return The number of dpeth bits the context uses
     * @exception std::logic_error Calling this function on a context that is not
     * the active one generates a standard logic error.
     * @exception std::runtime_error If, for some reason, the query fails, a
     * standard runtime error will be thrwon.
    */
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
    /**
     * \brief Query the gfx::context whether or not it uses
     * double buffering.
     * 
     * @return Whether the context uses double buffering
     * @exception std::logic_error Calling this function on a context that is not
     * the active one generates a standard logic error.
     * @exception std::runtime_error If, for some reason, the query fails, a
     * standard runtime error will be thrwon.
     */
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
}