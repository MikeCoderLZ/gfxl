#include <stdexcept>
#include <fstream>

#include "./shader.hpp"

//#define GL3_PROTOTYPES 1
//#include "gl3.h"

namespace gfx {

    shader_system* const shader_system::instance = new shader_system();

    shader_system::shader_system()
    {
        next_shdr_ID = 0;
        source_tree = 0;
        paths = 0;
        shaders = new shader_system::shader_set();
    }

    shader_system::~shader_system()
    {
        // HAHAHAHAHAHAHA
        delete source_tree;
        delete paths;
        delete shaders;
    }

    bool    shader_system::add_shader_source( std::string const& src_path )
    {
        return false;
    }

    shader_system::source_node::source_node()
    {
        path = 0;
        source = 0;
        children = 0;
    }

    shader_system::source_node::~source_node()
    {
        delete path;
        delete source;
        delete children;
    }

    bool    shader_system::owned( shader const& shader )
    {
        return false;
    }
    
    unsigned long shader_system::register_shader( shader* shdr)
    {
        shaders->insert( shdr );
        next_shdr_ID += 1;
        return next_shdr_ID - 1;
    }
    
    void shader_system::unregister_shader( shader* shdr)
    {
        shaders->erase( shdr );
    }
    
    /* ------------------- */
    
    shader::shader( context const& context,
                    shader::settings const& set ) : target_context ( &context ),
                                                    v_path( set.v_path ),
                                                    f_path( set.f_path ),
                                                    g_path( set.g_path ),
                                                    t_path( set.t_path ),
                                                    vert_ID( 0 ),
                                                    frag_ID( 0 ),
                                                    geom_ID( 0 ),
                                                    tess_ID( 0 ),
                                                    prog_ID( 0 )
    {
        
        /** Add check for adequate version number of a context */

        if ( set.has_vert ) {
            vert_ID = gl::CreateShader( gl::VERTEX_SHADER );
            v_path = set.v_path;
        }
        if ( set.has_frag ) {
                frag_ID = gl::CreateShader( gl::FRAGMENT_SHADER );
                f_path = set.f_path;
        }
        if ( set.has_geom ) {
                geom_ID = gl::CreateShader( gl::GEOMETRY_SHADER );
                g_path = set.g_path;
        }
        /** if ( settings.has_tess_shader ) {
                    new_program->tess_ID = gl::CreateShader( gl::TESSALLATION_SHADER_ARB );
            }*/

        prog_ID = gl::CreateProgram();

        video_system::get().register_shader( this );
            
    }
    
    shader::~shader()
    { video_system::get().unregister_shader( this ); }
    
    void    shader::compile()
    {
        compile( vert_ID, v_path );
        gl::AttachShader( prog_ID, vert_ID );
        compile( frag_ID, f_path );
        gl::AttachShader( prog_ID, frag_ID );
        /** Compile geometry shader only if present */
        if ( geom_ID != 0 ) {
            compile( geom_ID, g_path );
            gl::AttachShader( prog_ID, geom_ID );
        }
        if ( tess_ID != 0 ) {
            compile( tess_ID, t_path );
            gl::AttachShader( prog_ID, tess_ID );
        }
        
    }

    void    shader::link()
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
            std::cout << "Link failed." << std::endl;
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

    void    shader::use()
    {  gl::UseProgram( prog_ID );  }

    std::ostream& operator<<( std::ostream& out, shader const& rhs )
    {
        return out;
    }
    
    void    shader::compile( GLuint stage_ID, std::string const& stage_path )
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
            buffer[ shader_in.read( buffer, buffer_size - 1 ).gcount() ] = '\0';
            shader_file += buffer;
        }

        // std::cout << shader_file << std::endl;

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
                                 
    /* shader::shader( std::string vertex_path,
                    std::string frag_path )
    {
        vertex_file = new std::string();
        frag_file = new std::string();

        const char* vpth = vertex_path.c_str();

        std::fstream vert_in( vpth, std::ios_base::in );
        //vert_in.open();

        char* read_buffer = new char[80];

        while( vert_in.good() ) {

            vert_in.get( read_buffer, 80 );

            *vertex_file += read_buffer;

        }

        delete[] vpth;

        const char* fpth = frag_path.c_str();

        std::fstream frag_in( fpth, std::ios_base::in );
        //frag_in.open();

        while( frag_in.good() ) {

            frag_in.get( read_buffer, 80 );

            *frag_file += read_buffer;

        }

        delete[] read_buffer;

        delete[] fpth;

        vert_ID = gl::Createshader( gl::VERTEX_SHADER );
        frag_ID = gl::Createshader( gl::FRAGMENT_SHADER );
        prog_ID = gl::CreateProgram();

    }

    shader::~shader()
    {
        delete vertex_file;
        delete frag_file;
    }

    / **
    * The initial test module creates the OpenGL context beforehand;
    * later these two things must be coupled to make it all safe
    * and whatnot.
    * */

    /* bool shader::compile()
    {
        return false;
    }

    bool shader::link()
    {
        return false;
    }

    bool shader::use()
    {
        return false;
    }

    std::ostream& operator<<( std::ostream& out, shader const& rhs )
    {
        out << "vert_ID: " << rhs.vert_ID << "\n";
        out << "frag_ID: " << rhs.frag_ID << "\n";
        out << "prog_ID: " << rhs.prog_ID << "\n\n";

        out << "vertex shader:\n\n" << *(rhs.vertex_file) << "\n";
        out << "fragment shader:\n\n" << *(rhs.frag_file) << std::endl;

        return out;
    } */

}
