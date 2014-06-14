namespace gfx {

    video_system* const video_system::instance = new video_system();
    
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

    video_system::~video_system()
    {
        zombie = true;    
    }
    
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
    
    void video_system::activate_context( context& cntx )
    {
        SDL_GL_MakeCurrent( cntx.target_window->sys_window, cntx.sys_context );
        active_context = &cntx;
    }    
}