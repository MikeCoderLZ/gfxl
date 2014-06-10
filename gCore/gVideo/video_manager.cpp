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
        
        return *video_manager::instance;
    }

    video_manager::~video_manager()
    {
        zombie = true;    

        buffer_map::iterator it;
        for( it = buffers->begin(); it != buffers->end(); ++it)
            { delete (*it).second; }
        delete buffers;
        
//         program_map::iterator jt;
//         for( jt = programs->begin(); jt != programs->end(); ++jt)
//             { delete (*jt).second; }
//         delete programs;
    }
    
    void video_manager::attach_context( window const& wndw,
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
    
    void video_manager::activate_context( context& cntx )
    {
        SDL_GL_MakeCurrent( cntx.target_window->sys_window, cntx.sys_context );
        active_context = &cntx;
    }
    
//     program&    video_manager::new_program( program::settings const& set )
//     {
//         /**
//         * This code assumes that this VideoManager is the sole purveyor
//         * in the program; no attempt is made to find out if anyone else
//         * has created an OpenGL context. It is irrelevant anyway because
//         * only this VideoManager can use the program, so we aren't
//         * making an incorrect assumption. */
//         /** Add check for adequate version number of a context;
//         * OpenGL version should probably be pushed into VideoManager
//         * so the whole Manager only uses one version.
//         * */
//         
//         // ^ That guy really knew what he was talking about. ^
// 
//         program* new_program = new program( this, nxt_p_id );
// 
//         new_program->maj_ver = set.maj_ver_v;
//         new_program->min_ver = set.min_ver_v;
// 
//         if ( set.has_vert_v ) {
//             new_program->vert_ID = gl::CreateShader( gl::VERTEX_SHADER );
//             new_program->vert_path = set.vert_path;
//         }
//         if ( set.has_frag_v ) {
//                 new_program->frag_ID = gl::CreateShader( gl::FRAGMENT_SHADER );
//                 new_program->frag_path = set.frag_path;
//         }
//         if ( set.has_geom_v ) {
//                 new_program->geom_ID = gl::CreateShader( gl::GEOMETRY_SHADER );
//                 new_program->geom_path = set.geom_path;
//         }
//         /** if ( set.has_tess_shader ) {
//                     new_program->tess_ID = gl::CreateShader( gl::TESSALLATION_SHADER_ARB );
//             }*/
// 
//         new_program->prog_ID = gl::CreateProgram();
// 
//         (*programs)[nxt_p_id] = new_program;
//         ++nxt_p_id;
// 
//         return *new_program;
//     }
//     
//     void    video_manager::del_program( program const& prgm )
//     {
//         if ( this->owns( prgm ) ) {
//             if ( gl::IsProgram( prgm.prog_ID ) ) {
//                 gl::DeleteProgram( prgm.prog_ID );
//             }
//             if ( gl::IsShader( prgm.vert_ID ) ) {
//                 gl::DeleteShader( prgm.vert_ID );
//             }
//             if ( gl::IsShader( prgm.frag_ID ) ) {
//                 gl::DeleteShader( prgm.frag_ID );
//             }
//             if ( gl::IsShader( prgm.geom_ID ) ) {
//                 gl::DeleteShader( prgm.geom_ID );
//             }
//             if ( gl::IsShader( prgm.tess_ID ) ) {
//                 gl::DeleteShader( prgm.tess_ID );
//             }
//             if ( not this->zombie ) {
//                 // Someone else is calling the deletion
//                 programs->erase( prgm.g_id );
//             }
//         }
//     }
    
    buffer& video_manager::new_buffer( buffer::settings const& set )
    {
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