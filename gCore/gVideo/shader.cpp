#include "./shader.hpp"

#include <fstream>

//#define GL3_PROTOTYPES 1
//#include "gl3.h"

namespace gfx {

    shader_source_tree* const shader_source_tree::instance = new shader_source_tree();
    
    shader_source_tree::shader_source_tree()
    {
        source_tree = 0;
        handles = 0;
        shaders = 0;
    }

    shader_source_tree::~shader_source_tree()
    {
        // HAHAHAHAHAHAHA
        delete source_tree;
        delete handles;
        delete shaders;
    }

    shader&     shader_source_tree::create_shader( shader::settings const& set )
    {
        return *(new shader( set ) );
    }

    bool    shader_source_tree::add_shader_source( std::string const& src_path )
    {
        return false;
    }

    shader_source_tree::source_node::source_node()
    {
        handle = 0;
        source = 0;
        children = 0;
    }

    shader_source_tree::source_node::~source_node()
    {
        delete handle;
        delete source;
        delete children;
    }

    bool    shader_source_tree::owned( shader const& shader )
    {
        return false;
    }

    bool    shader::compile()
    {
        return false;
    }

    bool    shader::link()
    {
        return false;
    }

    bool    shader::use()
    {
        return false;
    }

    std::ostream& operator<<( std::ostream& out, shader const& rhs )
    {
        return out;
    }

    shader::shader( shader::settings const& set ) : v_handle( set.v_handle ),
                                                    f_handle( set.f_handle ),
                                                    g_handle( set.g_handle ),
                                                    t_handle( set.t_handle ),
                                                    vert_ID( 0 ),
                                                    frag_ID( 0 ),
                                                    geom_ID( 0 ),
                                                    tess_ID( 0 ),
                                                    prog_ID( 0 ) {}

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
