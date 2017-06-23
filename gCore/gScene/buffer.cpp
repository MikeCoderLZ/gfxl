#include "./buffer.hpp"

namespace gfx {
    /**
     * \brief Destruct the block specificaiton object.
     */
    block_spec::~block_spec()
    {
        attrib_vector::iterator i;
        for( i = attributes->begin(); i != attributes->end(); ++i )
            { delete *i; }
        delete attributes;
    }
    /**
     * \brief Construct a new \ref gfx::buffer "buffer" object.
     * \param set The settings for the new buffer object.
     */
    buffer::buffer( settings const& set ) :
                        data            ( 0 ),
                        n_blocks        ( set.n_blocks ),
                        stride          ( 0 ),
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
        //gl::GenVertexArrays( 1, &vao_ID );
        // Looks like I decided the video_system doesn't need to know about buffers
        //video_system::get().register_buffer( this );
    }
    /**
     * \brief Destruct the buffer.
     */
    buffer::~buffer()
    {
        // Don't need to know about buffers!
        gl::DeleteBuffers( 1, &buff_ID );
        attrib_vector::iterator i;
        for( i = attributes->begin(); i != attributes->end(); ++i )
            { delete *i; }
        delete attributes;
        delete[] data;
    }
    /**
     * \brief Use the given block specification to format the data of the
     * buffer.
     * Each time you call this function, the format is completely overwritten.
     * \param spec The block specification describing the formatting of the
     * buffer.
     */
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
    /**
     * \brief Set the number of data blocks in the \ref gfx::buffer "buffer".
     * This will reallocate the internal memory in order to resize it, copying
     * whatever data has been uploaded via \ref gfx::buffer::load_attribute() 
     * "load_attribute()" into the new memory, as far as it can fit.
     * \todo The copying functionality, as implemented, is wrong. Either
     * fix the loop or remove the copying.
     * \param blocks The number of blocks the buffer now has
     */
    void    buffer::blocks( GLsizeiptr const blocks )
    {
        unsigned char* new_data = new unsigned char[ blocks * stride ];
        GLsizeiptr i;
        // This loop is dead wrong! It is counting BYTES and not BLOCKS.
        // It has been working because I haven't tested it!
        for ( i = n_blocks; i < n_blocks; ++i )
            { new_data[i] = data[i]; }
        delete[] data;
        data = new_data;
        this->n_blocks = blocks;
        // The amount of data has changed and the buffer has been extended
        // so it is dirty again
        data_loaded = false;
    }
    /**
     * \brief Expand the number of data blocks in the \ref gfx::buffer "buffer".
     * This will reallocate the internal memory in order to resize it, copying
     * whatever data has been uploaded via \ref gfx::buffer::load_attribute() 
     * "load_attribute()" into the new memory, as far as it can fit.
     * \todo The copying functionality, as implemented, is wrong. Either
     * fix the loop or remove the copying.
     * \param more_blocks The number of blocks to add to the buffer
     */
    void    buffer::add_blocks( GLsizeiptr const more_blocks )
    {
        unsigned char* new_data =
                new unsigned char[ (n_blocks + more_blocks) * stride ];
        GLsizeiptr i;
        // This loop is dead wrong! It is counting BYTES and not BLOCKS.
        // It has been working because I haven't tested it!
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
    /**
     * \brief Upload the \ref gfx::buffer "buffer's" data to OpenGL.
     * \todo There is no check to see if you have actually specified the data
     * format. This means, internally, the stride member has not been correctly
     * specified and so the upload will send OpenGL an unpredictable number of
     * bytes (usually 0 but in more complex use cases it could be anything
     * depending on the lifetime of the particular buffer). It also doesn't
     * check to see if you have even loaded any data into the buffer client-
     * side or if the buffer is "dirty". Though that is not quite as bad,
     * it certainly isn't very helpful for the user.
     */
    void    buffer::upload_data()
    {
        gl::BindBuffer( intended_target, buff_ID );
        // TODO Add logic to use gl::BufferSubData() if the number of blocks
        // and the specification hasn't changed
        gl::BufferData( intended_target, n_blocks * stride, data, usage );

        data_loaded = true;
    }
    /**
     * \brief Query the \ref gfx::buffer "buffer" for the byte offset
     * of the attribute with the given index.
     * This is probably not going to stick around; it exposes the internals
     * of OpenGL and the buffer class too much. More of a thing to hack
     * functionality that isn't implemented yet, and to be honest I don't
     * know if it even used.
     * \todo Review for deprecation or removal
     * \param index The index of the attribute to get the offset of
     */
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