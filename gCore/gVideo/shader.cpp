#include <stdexcept>
#include <fstream>

#include "./shader.hpp"

//#define GL3_PROTOTYPES 1
//#include "gl3.h"

namespace gfx {

    /* shader_system* const shader_system::instance = new shader_system();

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
    } */
    
    /* ------------------- */
    
    shader::shader( context const& context,
                    shader::settings const& set ) : target_context ( &context ),
                                                    v_path( set.v_path ),
                                                    f_path( set.f_path ),
                                                    g_path( set.g_path ),
                                                    t_path( set.t_path ),
                                                    has_vert( set.has_vert),
                                                    has_frag( set.has_frag),
                                                    has_geom( set.has_geom),
                                                    has_tess( set.has_tess),
                                                    vert_ID( 0 ),
                                                    frag_ID( 0 ),
                                                    geom_ID( 0 ),
                                                    tess_ID( 0 ),
                                                    prog_ID( 0 )
    {

        if ( video_system::get().get_version() < opengl_2_0 ) {
            throw version_error( "Program cannot be created: video system version insufficient (requires 2.0+).");
        }
        
        if ( not video_system::get().context_present() ) {
            throw initialization_error( "Program cannot be created: no context present.");
        }
        
        if ( has_vert ) {
            vert_ID = gl::CreateShader( gl::VERTEX_SHADER );
            v_path = set.v_path;
        }
        if ( has_frag ) {
                frag_ID = gl::CreateShader( gl::FRAGMENT_SHADER );
                f_path = set.f_path;
        }
        if ( has_geom ) {
                geom_ID = gl::CreateShader( gl::GEOMETRY_SHADER );
                g_path = set.g_path;
        }
        /** if ( settings.has_tess_shader ) {
                    new_program->tess_ID = gl::CreateShader( gl::TESSALLATION_SHADER_ARB );
            }*/

        prog_ID = gl::CreateProgram();
        // Probably remove dependencies
        video_system::get().register_shader( this );
            
    }
    
    shader::~shader()
    { // Probably remove dependencies
        video_system::get().unregister_shader( this ); 
        
        if ( gl::IsShader( vert_ID ) ) {
            gl::DeleteShader( vert_ID );
        }
        if ( gl::IsShader( frag_ID ) ) {
            gl::DeleteShader( frag_ID );
        }
        if ( gl::IsShader( geom_ID ) ) {
            gl::DeleteShader( geom_ID );
        }
        if ( gl::IsShader( tess_ID ) ) {
            gl::DeleteShader( tess_ID );
        }
        if ( gl::IsProgram( prog_ID ) ) {
                gl::DeleteProgram( prog_ID );
        }
        
        uniform_map->clear();
    }
    
    void    shader::uniform( std::string const& name )
    { (*uniform_map)[ name ] = -1; }
    
    void    shader::compile()
    {
        if ( has_vert ) {
            if ( vert_path == "" ) {
                throw compilation_error( "Vertex shader source path uninitialized.");
            } else {
                compile( this->vert_ID, vert_path );
                gl::AttachShader( prog_ID, vert_ID );
            }
        }
        if ( has_frag ) {
            if ( frag_path == "" ) {
                throw compilation_error( "Fragment shader source path uninitialized.");
            } else {
                compile( this->frag_ID, frag_path );
                gl::AttachShader( prog_ID, frag_ID );
            }
        }
        if ( has_geom ) {
            if ( geom_path == "" ) {
                throw compilation_error( "Geometry shader source path uninitialized.");
            } else {
                compile( this->geom_ID, geom_path );
                gl::AttachShader( prog_ID, geom_ID );
            }
        }
        if ( has_tess ) {
            if ( tess_path == "" ) {
                throw compilation_error( "Tesselation shader source path uninitialized.");
            } else {
                compile( this->tess_ID, tess_path );
                gl::AttachShader( prog_ID, tess_ID );
            }
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
        
        key_map::iterator unfm;
        
        for ( unfm = uniform_map->begin();
              unfm != uniform_map->end();
              ++unfm                       ) {
            (*uniform_map)[unfm->first] = gl::GetUniformLocation( prog_ID,
                                                                  unfm->first.c_str() );
        }
    }

    void    shader::use()
    {  gl::UseProgram( prog_ID );  }

    std::ostream& operator<<( std::ostream& out, shader const& rhs )
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
            // The expression can't execute until the index to the array
            // is known, so that expression will always execute first.
            // Still terrifying.
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

}
