#include "./buffer.hpp"

namespace gfx {

    block_spec::~block_spec()
    {
        attrib_vector::iterator i;
        for( i = attributes->begin(); i != attributes->end(); ++i )
            { delete *i; }
        delete attributes;
    }

    buffer::buffer( settings const& set ) :
                        data            ( 0 ),
                        n_blocks        ( set.n_blocks ),
                        stride          ( 0 ),
                        vao_ID          ( 0 ),
                        buff_ID         ( 0 ),
                        usage           ( set.usage ),
                        intended_target ( set.intended_target ),
                        data_loaded     ( false ),
                        verts_specified ( false ),
                        attributes      ( new attrib_vector() )
    {
        if ( video_system::get().get_version() < opengl_1_5 ) {
            throw version_error( "Buffer cannot be created: video system version insufficient (requires 1.5+).");
        }
        if ( not video_system::get().context_present() ) {
            throw initialization_error( "Buffer cannot be created: no context present.");
        }
        
        gl::GenBuffers( 1, &buff_ID );
        gl::GenVertexArrays( 1, &vao_ID );
        // Looks like I decided the video_system doesn't need to know about buffers
        //video_system::get().register_buffer( this );
    }

    buffer::~buffer()
    {
        // Don't need to know about buffers!
        //video_system::get().unregister_buffer( this );
        gl::DeleteBuffers( 1, &buff_ID );
        attrib_vector::iterator i;
        for( i = attributes->begin(); i != attributes->end(); ++i )
            { delete *i; }
        delete attributes;
        delete[] data;
    }

    void buffer::block_format( block_spec const& spec )
    {
        attrib_vector::iterator a;
        GLsizeiptr new_stride = 0;
        for( a = spec.attributes->begin(); a != spec.attributes->end(); ++a ) {
            info* attrib_ptr = (*a)->copy();
            new_stride += attrib_ptr->mapped_size();
            this->attributes->push_back( attrib_ptr );
        }
        verts_specified = true;
        // since the format has changed, we need to flag the buffer as "dirty"
        data_loaded = false;
        stride = new_stride;
        if ( data != 0 ) {
            delete[] data;
        }
        data = new unsigned char[ n_blocks * stride ];
    }
    
    void    buffer::blocks( GLsizeiptr const blocks )
    {
        unsigned char* new_data = new unsigned char[ blocks * stride ];
        GLsizeiptr i;
        for ( i = n_blocks; i < n_blocks; ++i )
            { new_data[i] = data[i]; }
        delete[] data;
        data = new_data;
        this->n_blocks = blocks;
        // The amount of data has changed and the buffer has been extended
        // so it is dirty again
        data_loaded = false;
    }

    void    buffer::add_blocks( GLsizeiptr const more_blocks )
    {
        unsigned char* new_data =
                new unsigned char[ (n_blocks + more_blocks) * stride ];
        GLsizeiptr i;
        // copy over old data to new array
        for ( i = n_blocks; i < n_blocks; ++i )
            { new_data[i] = data[i]; }
        delete[] data;
        data = new_data;
        this->n_blocks += more_blocks;
        // The amount of data has changed and the buffer has been extended
        // so it is dirty again
        data_loaded = false;
    }

    void    buffer::upload_data()
    {
        if( intended_target == gl::ELEMENT_ARRAY_BUFFER ){
            gl::BindVertexArray( vao_ID );
            checkGLError( "vao bound for element data load" );
        }
        gl::BindBuffer( intended_target, buff_ID );
        // TODO Add logic to use gl::BufferSubData() if the number of blocks
        // and the specification hasn't changed
        gl::BufferData( intended_target, n_blocks * stride, data, usage );

        data_loaded = true;
    }

    /*void    buffer::align_vertices()
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
          case DOUBLE :
                gl::VertexAttribLPointer( index,
                                        (*a)->n_components(),
                                        (*a)->component_to_GL(),
                                        stride,
                                        ( void*) offset );
            default :
                break;
            }
            ++index;
        }
    }*/
    
    void buffer::align()
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

    GLsizeiptr buffer::attribute_offset( GLuint index ) const
    {
        if( index == 0 ) { return 0; }

        GLsizeiptr offset = 0;
        GLuint attribute = 0;
        for( attribute = 0; attribute < index; ++attribute )
            { offset += (*attributes)[attribute]->mapped_size(); }
        return offset;
    }
}