#include <stdexcept>
#include <fstream>
#include <iostream>
#include "./program.hpp"

//#define GL3_PROTOTYPES 1
//#include "gl3.h"

namespace gfx {
    
    program*    program::current_prgm = 0;
    
    program::program( program::settings const& set ) : uniform_map( new program::key_map() ),
                                                      vert_path( set.vert_path ),
                                                      frag_path( set.frag_path ),
                                                      geom_path( set.geom_path ),
                                                      tess_path( set.tess_path ),
                                                      has_vert( set.has_vert),
                                                      has_frag( set.has_frag),
                                                      has_geom( set.has_geom),
                                                      has_tess( set.has_tess),
                                                      vert_ID( 0 ),
                                                      frag_ID( 0 ),
                                                      geom_ID( 0 ),
                                                      tess_ID( 0 ),
                                                      prog_ID( 0 ),
                                                      in_use_v ( false )
    {

        if ( video_system::get().get_version() < opengl_2_0 ) {
            throw version_error( "Program cannot be created: video system version insufficient (requires 2.0+).");
        }
        
        if ( not video_system::get().context_present() ) {
            throw initialization_error( "Program cannot be created: no context present.");
        }
        
        if ( has_vert ) {
            vert_ID = gl::CreateShader( gl::VERTEX_SHADER );
            vert_path = set.vert_path;
        }
        if ( has_frag ) {
                frag_ID = gl::CreateShader( gl::FRAGMENT_SHADER );
                frag_path = set.frag_path;
        }
        if ( has_geom ) {
                geom_ID = gl::CreateShader( gl::GEOMETRY_SHADER );
                geom_path = set.geom_path;
        }
        /** if ( settings.has_tess_shader ) {
                    new_program->tess_ID = gl::CreateShader( gl::TESSALLATION_SHADER_ARB );
            }*/

        prog_ID = gl::CreateProgram();
        // Probably remove dependencies
        //video_system::get().register_shader( this );
            
    }
    
    program::~program()
    { // Probably remove dependencies
        //video_system::get().unregister_shader( this ); 
        if ( program::current_prgm != 0 and *(program::current_prgm) == *this ) {
            program::current_prgm->in_use_v = false;
            program::current_prgm = 0;
        }
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
    
    void    program::uniform_name( std::string const& name )
    { (*uniform_map)[name] = -1;}
    
    void    program::compile()
    {
        if ( has_vert ) {
            if ( vert_path == "" ) {
                throw compilation_error( "Vertex program source path uninitialized.");
            } else {
                compile( this->vert_ID, vert_path );
                gl::AttachShader( prog_ID, vert_ID );
            }
        }
        if ( has_frag ) {
            if ( frag_path == "" ) {
                throw compilation_error( "Fragment program source path uninitialized.");
            } else {
                compile( this->frag_ID, frag_path );
                gl::AttachShader( prog_ID, frag_ID );
            }
        }
        if ( has_geom ) {
            if ( geom_path == "" ) {
                throw compilation_error( "Geometry program source path uninitialized.");
            } else {
                compile( this->geom_ID, geom_path );
                gl::AttachShader( prog_ID, geom_ID );
            }
        }
        if ( has_tess ) {
            if ( tess_path == "" ) {
                throw compilation_error( "Tesselation program source path uninitialized.");
            } else {
                compile( this->tess_ID, tess_path );
                gl::AttachShader( prog_ID, tess_ID );
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

    void    program::use()
    {  
        if ( program::current_prgm == 0 ) {
            program::current_prgm = this;
        } else if ( *(program::current_prgm) != *this ) {
            program::current_prgm->in_use_v = false;
            program::current_prgm = this;
        }
        gl::UseProgram( prog_ID );
        in_use_v = true;
    }

    std::ostream& operator<<( std::ostream& out, program const& rhs )
    {
        out << "Program:\n";
        out << "\tvertex program ID: " << rhs.vert_ID << "\n";
        out << "\tvertex path: " << rhs.vert_path << "\n";
        out << "\tfragment program ID: " << rhs.frag_ID << "\n";
        out << "\tfragment path: " << rhs.frag_path << "\n";
        out << "\tgeometry program ID: " << rhs.geom_ID << "\n";
        out << "\tgeometry path: " << rhs.geom_path << "\n";
        // out << "\ttessallation program ID: " << rhs.tess_ID << "\n";
        return out;
    }
    
    void    program::compile( GLuint stage_ID, std::string const& stage_path )
    {
        std::fstream program_in( stage_path.c_str(),
                                std::ios_base::in );
        size_t buffer_size = 128;
        char* buffer = new char[buffer_size];
        std::string program_file;

        while( program_in.good() ) {
            // This looks ugly, I know.  Translation:
            // "read a number of bytes equal to the size of the read
            // buffer minus one then assign the character after the end
            // of that read to a null terminating character."
            // The expression can't execute until the index to the array
            // is known, so that expression will always execute first.
            // Still terrifying.
            buffer[ program_in.read( buffer, buffer_size - 1 ).gcount() ] = '\0';
            program_file += buffer;
        }
        // std::cout << program_file << std::endl;

        const char* stage_file_ptr = program_file.c_str();
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
            msg += " program failed:\n";
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
