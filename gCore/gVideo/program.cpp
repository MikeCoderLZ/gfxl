namespace gfx {

    program::~program()
    {
        owner->del_program( *this );
        // I do not know if this code is needed.
//         GLint n_shdr;
//         if (     gl::IsProgram( prog_ID )
//              and ( gl::GetProgram( prog_ID, GL_ATTACHED_SHADERS, &n_shdr ), n_shdr > 0 ) )
//         {
//             if ( gl::IsShader( vert_ID ) ) {
//                 gl::DetachShader( prog_ID, vert_ID );
//             }
//             if ( gl::IsShader( frag_ID ) ) {
//                 gl::DetachShader( prog_ID, frag_ID );
//             }
//             if ( gl::IsShader( geom_ID ) ) {
//                 gl::DetachShader( prog_ID, geom_ID );
//             }
//             if ( gl::IsShader( tess_ID ) ) {
//                 gl::DetachShader( prog_ID, tess_ID );
//             }
//         }
        
//         gl::DeleteProgram( prog_ID );
//         gl::DeleteShader( vert_ID );
//         gl::DeleteShader( frag_ID );
//         gl::DeleteShader( geom_ID );
//         gl::DeleteShader( tess_ID );
    }
    
    void    program::compile()
    {
        if ( vert_path == "" ) {
            throw compilation_error( "Vertex shader source path uninitialized.");
        } else {
            compile( this->vert_ID, vert_path );
            gl::AttachShader( prog_ID, vert_ID );
        }
        if ( frag_path == "" ) {
            throw compilation_error( "Fragment shader source path uninitialized.");
        } else {
            compile( this->frag_ID, frag_path );
            gl::AttachShader( prog_ID, frag_ID );
        }
        /** Compile geometry shader only if present */
        if ( this->geom_ID != 0 ) {
            if ( geom_path == "" ) {
                throw compilation_error( "Geometry shader source path uninitialized.");
            } else {
                compile( this->geom_ID, geom_path );
                gl::AttachShader( prog_ID, geom_ID );
            }
        }
    }
    
    void    program::link()
    {
        /**gl::AttachShader( prog_ID, vert_ID );
        gl::AttachShader( prog_ID, frag_ID );
        if ( geom_ID != 0 ) {
            gl::AttachShader( prog_ID, geom_ID );
        }*/

        gl::LinkProgram( prog_ID );

        GLint status = 0;
        gl::GetProgramiv( prog_ID, gl::LINK_STATUS, &status );
        if ( status == gl::FALSE_ ) {
            std::string msg = "Linking of program failed.\n";
            GLint log_length;
            gl::GetProgramiv(prog_ID, gl::INFO_LOG_LENGTH, &log_length );
            char* info_log = new char[log_length];
            GLint returned_length;
            gl::GetProgramInfoLog( prog_ID, log_length, &returned_length, info_log );
            msg += info_log;
            delete[] info_log;
            throw compilation_error( msg );
        }
    }
    
    void program::use()
    { gl::UseProgram( prog_ID ); }
    
    std::ostream& operator <<( std::ostream& out, program const& rhs )
    {
        out << "Program:\n";
        out << "\tversion: " << rhs.maj_ver << "." << rhs.min_ver << "\n";
        out << "\tvertex shader ID: " << rhs.vert_ID << "\n";
        out << "\tvertex path: " << rhs.vert_path << "\n";
        out << "\tfragment shader ID: " << rhs.frag_ID << "\n";
        out << "\tfragment path: " << rhs.frag_path << "\n";
        out << "\tgeometry shader ID: " << rhs.geom_ID << "\n";
        out << "\tgeometry path: " << rhs.geom_path << "\n";
        // out << "\ttessallation shader ID: " << rhs.tess_ID << "\n";
        return out;
    }
    
    program::program( video_manager* const owner,
                      size_t g_id ) :
                      managed( owner, g_id ),
                      vert_path ( "" ),
                      frag_path ( "" ),
                      geom_path ( "" ),
                      vert_ID ( 0 ),
                      frag_ID ( 0 ),
                      geom_ID ( 0 ),
                      tess_ID ( 0 ),
                      prog_ID ( 0 ),
                      maj_ver ( 2 ),
                      min_ver ( 0 )  {}
    
    void    program::compile( GLuint stage_ID, std::string const& stage_path )
    {
        std::fstream shader_in( stage_path.c_str(),
                                std::ios_base::in );
        size_t buffer_size = 128;
        char* buffer = new char[buffer_size];
        std::string shader_file;

        while( shader_in.good() ) {
            // This looks ugly, I know.  Translation:
            // "read a number of bytes equal to the size of the read
            // buffer minus one then assign the character after the end
            // of that read to a null terminating character."
            // The expression can't execute until the index to the array
            // is known, so that expression will always execute first.
            // Still terrifying.
            buffer[ shader_in.read( buffer, buffer_size - 1 ).gcount() ] = '\0';
            shader_file += buffer;
        }

        //std::cout << shader_file << std::endl;

        const char* stage_file_ptr = shader_file.c_str();
        gl::ShaderSource( stage_ID, 1, &stage_file_ptr, 0 );
        gl::CompileShader( stage_ID );

        GLint status = 0;
        gl::GetShaderiv( stage_ID, gl::COMPILE_STATUS, &status );

        if ( status == gl::FALSE_ ) {
            std::string msg = "Compilation of ";
            GLint type;
            gl::GetShaderiv( stage_ID, gl::SHADER_TYPE, &type );
            switch ( type ) {
            case gl::VERTEX_SHADER :
                msg += "vertex";
                break;
            case gl::FRAGMENT_SHADER :
                msg += "fragment";
                break;
            case gl::GEOMETRY_SHADER :
                msg += "geometry";
                break;
            default :
                msg += "unknown or unsupported type of";
            }
            msg += " shader failed:\n";
            GLint log_length;
            gl::GetShaderiv(stage_ID, gl::INFO_LOG_LENGTH, &log_length );
            char* info_log = new char[log_length];
            GLint returned_length;
            gl::GetShaderInfoLog( stage_ID, log_length, &returned_length, info_log );
            msg += info_log;
            delete[] info_log;

            throw compilation_error( msg );
        }
    }
}