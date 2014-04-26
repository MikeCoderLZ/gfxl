#include "./shader.hpp"

#include <fstream>

//#define GL3_PROTOTYPES 1
//#include "gl3.h"

namespace gfx {

Shader::Shader( std::string vertex_path,
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

    vert_ID = gl::CreateShader( gl::VERTEX_SHADER );
    frag_ID = gl::CreateShader( gl::FRAGMENT_SHADER );
    prog_ID = gl::CreateProgram();

}

Shader::~Shader()
{
    delete vertex_file;
    delete frag_file;
}

/**
 * The initial test module creates the OpenGL context beforehand;
 * later these two things must be coupled to make it all safe
 * and whatnot.
 * */

bool Shader::compile()
{
    return false;
}

bool Shader::link()
{
    return false;
}

bool Shader::use()
{
    return false;
}

std::ostream& operator<<( std::ostream& out, Shader const& rhs )
{
    out << "vert_ID: " << rhs.vert_ID << "\n";
    out << "frag_ID: " << rhs.frag_ID << "\n";
    out << "prog_ID: " << rhs.prog_ID << "\n\n";

    out << "vertex shader:\n\n" << *(rhs.vertex_file) << "\n";
    out << "fragment shader:\n\n" << *(rhs.frag_file) << std::endl;

    return out;
}

}
