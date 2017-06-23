namespace gfx {

    /**
     * \internal This statement creates the \ref gfx::video_system "video system" instance.
     * \see gfx::video_system::video_system()
     * \see gfx::video_system::initialize()
     */
    video_system* const video_system::instance = new video_system();
    /**
     * \brief Initialize the \ref gfx::video_system "video system" with the
     * given settings.
     * 
     * The video_system must be manually initialized in order to set up SDL
     * and OpenGL with the desired settings. The
     * \ref gfx::video_system:settings "settings" object default construtor is
     * called if no argument is given, and so the default settings are version
     * 1.4 of OpenGl using the core profile.
     * @param set The video system settings; defaults to version 1.4 using core profile
     */
    video_system&  video_system::initialize( video_system::settings const& set )
    {
        if ( not SDL_WasInit( SDL_INIT_VIDEO ) ) {
            if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
                std::string msg ("Cannot initialize SDL Video subsystem:\n");
                msg += SDL_GetError();
                throw std::runtime_error( msg );
            }
        }
        // These three OpenGL attributes must be set before any window
        // which uses OpenGL can be created. If you create two
        // video_system objects with different settings and create
        // windows with the first before the second, then all the windows
        // created by the second will inherit the first's settings and
        // it's own will have no effect.
        // At least that is what the docs say.
        // So that is why this setting information is discarded:
        // After the first set, it won't matter.
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK,  set.profile_v );
        unsigned int min_ver = set.min_ver_v;
        
        if ( min_ver < 10u and set.sub_ver_v > 0u ) {
            min_ver *= 10u;
            min_ver += set.sub_ver_v;
        }
        
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, set.maj_ver_v );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, min_ver );
        
        video_system::instance->vid_ver = version( set.maj_ver_v,
                                                    set.min_ver_v,
                                                    set.sub_ver_v );
        
        return *video_system::instance;
    }

    /**
     * \brief Destruct the \ref gfx::video_system "video system".
     * 
     * Since the video_system is a singleton, this is only ever called after
     * all application code has ended.
     */
    video_system::~video_system()
    {
        zombie = true;    
        delete contexts;
    }
    /**
     * \brief Output useful debuging information to standard error.
     * 
     * @param tag A code tag that is appended to the error message.
     */
    void    video_system::check_acceleration_error( std::string const& tag )
    {
        if ( context_present() ) {
            std::string msg ("");
            GLint error = gl::GetError();
            switch ( error ) {
                case gl::INVALID_ENUM:
                    msg += "Invalid enum at ";
                    break;
                case gl::INVALID_VALUE:
                    msg += "Invalid value at ";
                    break;
                case gl::INVALID_OPERATION:
                    msg +=  "Invalid operation at ";
                    break;
                case gl::INVALID_FRAMEBUFFER_OPERATION:
                    msg += "Invalid framebuffer operation at ";
                    break;
                case gl::OUT_OF_MEMORY:
                    msg += "Out of memory at ";
                    break;
                default:
                    msg += "No error on load at ";
                    break;
            }
            msg += tag;
            std::cerr << msg << std::endl;
        }
    }
    /**
     * \brief Attach the given \ref gfx::context "context" to the given
     * \ref gfx::window "window".
     * 
     * Using this function will cause the given context to become the current
     * and active one and set it to be used in the given window. An error is
     * thrown if the window does not support OpenGL.
     * 
     * \todo Review this function and it's relation to \ref gfx::context::context()
     * "gfx::context's constructor" as they seem to do the same thing; this
     * functionality should most likely be merged into that function instead.
     * 
     * @param wndw The window to use the context with
     * @param cntx The context to use for rendering
     * @exception std::logic_error A standard logic error is thrown if the specified
     * window was created without support for OpenGL rendering contexts.
     */
    void video_system::attach_context( window const& wndw,
                                        context& cntx)
    {
        if ( not wndw.has_3D() ) {
            std::string msg = "Illegal attachment of Context to Window '";
            msg += wndw.title();
            msg += "': Window does not support OpenGL.";
            throw std::logic_error( msg );
        }

        cntx.target_window = &wndw;
        SDL_GL_MakeCurrent( wndw.sys_window, cntx.sys_context );
        active_context = &cntx;
    }
    /**
     * \brief Make the given \ref gfx::context "context" the active one.
     * 
     * Activating a context will cause all subsquent rendering calls and
     * OpenGL state modifications to be enacted on that context. The target
     * window of the given context will be made the current one.
     * @param cntx The context to activate
     * @see gfx::program::use()
     */
    void video_system::activate_context( context& cntx )
    {
        SDL_GL_MakeCurrent( cntx.target_window->sys_window, cntx.sys_context );
        active_context = &cntx;
    }    
}