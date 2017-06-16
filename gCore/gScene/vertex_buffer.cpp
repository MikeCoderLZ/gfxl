#include "vertex_buffer.hpp"

namespace gfx {

    vertex_buffer::vertex_buffer( settings const& set ) :
                                    buffer::buffer( set ) 
    { gl::GenVertexArrays( 1, &vao_ID ); }
    
    vertex_buffer::~vertex_buffer()
    { gl::DeleteVertexArrays( 1, &vao_ID ); }
    
    void    vertex_buffer::upload_data()
    {
        if( intended_target == gl::ELEMENT_ARRAY_BUFFER ){
            gl::BindVertexArray( vao_ID );
            checkGLError( "vao bound for element data load" );
        }
        buffer::upload_data();
    }
    
    void  vertex_buffer::align()
    {
        if ( not data_loaded ) {
            std::string msg = "Buffer data has not been uploaded to OpenGL; ";
            msg += "either the buffer is new or the data has changed since ";
            msg += "the last time it was loaded.";
            throw std::logic_error( msg );
        }

        if ( not verts_specified ) {
            std::string msg = "Blocks of buffer data not yet formated.";
            throw std::logic_error( msg );
        }

        std::cout << "Buffer ID: " << buff_ID << std::endl;
        gl::BindBuffer( gl::ARRAY_BUFFER, buff_ID );
        checkGLError( "buffer bound to ARRAY_BUFFER" );
        gl::BindVertexArray( vao_ID );
        checkGLError( "vao bound for vertex alignment" );

        attrib_vector::iterator a;
        GLuint index = 0;
        for( a = attributes->begin();
            a != attributes->end();
            ++a ) {
            GLsizeiptr offset = attribute_offset( index );
            switch( (*a)->mapping() ) {
            case FLOAT :
                gl::VertexAttribPointer( index,
                                        (*a)->n_components(),
                                        (*a)->component_to_GL(),
                                        gl::FALSE_,
                                        stride,
                                        ( void* ) offset );
                checkGLError( "VertexAttribPointer called" );
                std::cout << "VertexAttribPointer called." << std::endl;
                std::cout << "\tindex: " << index << '\n';
                std::cout << "\tsize: " << (*a)->n_components() << '\n';
                std::cout << "\ttype: " << (*a)->component_to_GL() << '\n';
                std::cout << "\tstride: " << stride << '\n';
                std::cout << "\toffset: " << offset << std::endl;
                gl::EnableVertexAttribArray( index );
                checkGLError( "Enabled Vertex Attribute Array" );
                break;
            case INTEGER :
                gl::VertexAttribIPointer( index,
                                        (*a)->n_components(),
                                        (*a)->component_to_GL(),
                                        stride,
                                        ( void* ) offset );
                gl::EnableVertexAttribArray( index );
                break;
        /**  case DOUBLE :
                gl::VertexAttribLPointer( index,
                                        (*a)->n_components(),
                                        (*a)->component_to_GL(),
                                        stride,
                                        ( void*) offset );*/
            default :
                break;
            }
            ++index;
        }
    }

}