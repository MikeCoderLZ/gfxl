namespace gfx {

    video_manager* const video_manager::instance = new video_manager();
    
    video_manager&  video_manager::initialize( video_manager::settings const& set )
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
        // video_manager objects with different settings and create
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
        
        video_manager::instance->vid_ver = version( set.maj_ver_v,
                                                    set.min_ver_v,
                                                    set.sub_ver_v );
        
        return video_manager::instance;
    }

    video_manager::~video_manager()
    {
        zombie = true;
        
        /*buffers->clear();
        programs->clear();
        contexts->clear();
        windows->clear(); */       

        buffer_map::iterator it;
        for( it = buffers->begin(); it != buffers->end(); ++it)
            { delete (*it).second; }
        delete buffers;
        
        program_map::iterator jt;
        for( jt = programs->begin(); jt != programs->end(); ++jt)
            { delete (*jt).second; }
        delete programs;
        
        context_map::iterator kt;
        for( kt = contexts->begin(); kt != contexts->end(); ++kt)
            { delete (*kt).second; }
        delete contexts;
        
        window_map::iterator lt;
        for( lt = windows->begin(); lt != windows->end(); ++lt)
            { delete (*lt).second; }
        delete windows;
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
    
    void video_manager::attach_context( window const& wndw,
                                        context& cntx)
    {
        if ( (not owns( wndw )) or (not owns( cntx )) ) {
            std::string msg = "Illegal attachment of Context to Window '";
            msg += wndw.title();
            msg += "': ";
            if ( not owns( wndw ) ) {
                msg += "Window not owned by manager. ";
            }
            if ( not owns( cntx ) ) {
                msg += "Context not owned by manager. ";
            }
            if ( not wndw.has_3D() ) {
                msg += "Window does not support OpenGL.";
            }
            throw std::logic_error( msg );
        }

        cntx.target_window = &wndw;
        SDL_GL_MakeCurrent( wndw.sys_window, cntx.sys_context );
        active_context = &cntx;
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
    
    program&    video_manager::new_program( program::settings const& set )
    {
        /**
        * This code assumes that this VideoManager is the sole purveyor
        * in the program; no attempt is made to find out if anyone else
        * has created an OpenGL context. It is irrelevant anyway because
        * only this VideoManager can use the program, so we aren't
        * making an incorrect assumption. */
        if ( contexts->size() == 0 ) {
            std::string msg = "No OpenGL context had been created at time of";
            msg += " shading program creation request.";
            throw std::logic_error( msg );
        } /** Add check for adequate version number of a context;
        * OpenGL version should probably be pushed into VideoManager
        * so the whole Manager only uses one version.
        * */
        
        // ^ That guy really knew what he was talking about. ^

        program* new_program = new program( this, nxt_p_id );

        new_program->maj_ver = set.maj_ver_v;
        new_program->min_ver = set.min_ver_v;

        if ( set.has_vert_v ) {
            new_program->vert_ID = gl::CreateShader( gl::VERTEX_SHADER );
            new_program->vert_path = set.vert_path;
        }
        if ( set.has_frag_v ) {
                new_program->frag_ID = gl::CreateShader( gl::FRAGMENT_SHADER );
                new_program->frag_path = set.frag_path;
        }
        if ( set.has_geom_v ) {
                new_program->geom_ID = gl::CreateShader( gl::GEOMETRY_SHADER );
                new_program->geom_path = set.geom_path;
        }
        /** if ( set.has_tess_shader ) {
                    new_program->tess_ID = gl::CreateShader( gl::TESSALLATION_SHADER_ARB );
            }*/

        new_program->prog_ID = gl::CreateProgram();

        (*programs)[nxt_p_id] = new_program;
        ++nxt_p_id;

        return *new_program;
    }
    
    void    video_manager::del_program( program const& prgm )
    {
        if ( this->owns( prgm ) ) {
            if ( gl::IsProgram( prgm.prog_ID ) ) {
                gl::DeleteProgram( prgm.prog_ID );
            }
            if ( gl::IsShader( prgm.vert_ID ) ) {
                gl::DeleteShader( prgm.vert_ID );
            }
            if ( gl::IsShader( prgm.frag_ID ) ) {
                gl::DeleteShader( prgm.frag_ID );
            }
            if ( gl::IsShader( prgm.geom_ID ) ) {
                gl::DeleteShader( prgm.geom_ID );
            }
            if ( gl::IsShader( prgm.tess_ID ) ) {
                gl::DeleteShader( prgm.tess_ID );
            }
            if ( not this->zombie ) {
                // Someone else is calling the deletion
                programs->erase( prgm.g_id );
            }
        }
    }
    
    buffer& video_manager::new_buffer( buffer::settings const& set )
    {
        if ( contexts->size() == 0 ) {
            std::string msg ( "Buffer creation requested in absence of valid " );
            msg += "OpenGL context.";
            throw std::logic_error( msg );
        }
        GLuint new_buff_ID;
        gl::GenBuffers( 1, &new_buff_ID );
        GLuint new_vao_ID;
        gl::GenVertexArrays( 1, &new_vao_ID );

        buffer* new_buffer = new buffer( this, nxt_b_id, set.blocks_v, new_vao_ID, new_buff_ID, set.usage_v, set.target_v );

        (*buffers)[nxt_b_id] = new_buffer;
        ++nxt_b_id;

        return *new_buffer;
    }
    
    void    video_manager::del_buffer( buffer const& buff )
    {
        if ( this->owns( buff ) ) {
            gl::DeleteBuffers( 1, &buff.buff_ID );
            if ( not this->zombie ) {
                // Someone else is calling the deletion
                buffers->erase( buff.g_id );
            }
        }
    }
    
}