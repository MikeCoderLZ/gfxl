#ifndef BUFFER
#define BUFFER

#include "../gVideo/video.hpp"
#include "block_spec.hpp"

/**
 * What must happen here is to separate out the vertex related elements of
 * the class, leaving only the buffer object elements. Then, create derived
 * classes for each of the various things that use buffers:
 * 
 * vertex_buffer
 * uniform_buffer
 * texture_buffer
 * feedback_buffer
 * pixel_buffer
 * 
 * and so on. Each drived class will implement the appropriate special
 * things that make them work. _Probably_ leave block_spec outside the
 * buffer class because it is going to be useful for all sorts of things.
 * Also, improve the attribute/name alignment stuff, probably via buffer
 * mapping.
 * 
 */

namespace gfx {
    
    class block_spec {
    public:
                                        block_spec();
                                        ~block_spec();
        template< typename T >
        block_spec&                     attribute( type<T> const& proto );
    private:
        friend                          class buffer;
        typedef std::vector< info* >    attrib_vector;
        attrib_vector*                  attributes;
    };

    inline  block_spec::block_spec() : attributes( new block_spec::attrib_vector() ) {}

    template< typename T > inline
    block_spec&     block_spec::attribute( type<T> const& proto )
    {   
        // pointers to the type class can be safely
        // cast to pointers to the info ABC
        info* new_attrib = (info*) proto.copy();
        attributes->push_back( new_attrib );
        return *this; }

    class buffer {
    public:
        
        class settings {
        public:
                        settings();
            settings&   blocks( GLsizeiptr new_n_blocks );
            settings&   static_draw();
            settings&   static_read();
            settings&   static_copy();
            settings&   dynamic_draw();
            settings&   dynamic_read();
            settings&   dynamic_copy();
            settings&   stream_draw();
            settings&   stream_read();
            settings&   stream_copy();
            settings&   for_array();
    //    settings&   for_atomic_counter();
            settings&   for_copy_read();
            settings&   for_copy_write();
    //    settings&   for_indirect_draw();
    //    settings&   for_indirect_dispatch();
            settings&   for_element_array();
            settings&   for_pixel_packing();
            settings&   for_pixel_unpacking();
    //    settings&   for_shader_storage();
            settings&   for_texture();
            settings&   for_transform_feedback();
            settings&   for_uniform();
        private:
            friend              class buffer;
            GLsizeiptr          n_blocks;
            GLenum              usage;
            GLenum              intended_target;
        };
                                    buffer( settings const& set = settings() );
        virtual                     ~buffer();
        void                        block_format( block_spec const& spec );
        GLsizeiptr                  size() const;
        void                        blocks( GLsizeiptr const blocks );
        void                        add_blocks( GLsizeiptr const more_blocks );
        template< typename DATA >
        void                        load_attribute( GLuint index,
                                                    std::vector< DATA > const& attrib_data );
        /*template< typename DATA >
        void                        load_attribute( char const* name,
                                                    std::vector< DATA > const& attrib_data );*/
        /*template< typename DATA >
        void                        load_attribute( std::string const& name,
                                                    std::vector< DATA > const& attrib_data );*/
        void                        upload_data();
        void                        align_vertices();
        virtual void                align();
        // Unsure if everyone should be allowed to use this code...
#ifdef DEBUG
//        context const*              get_target_context() const { return target_context; }
        GLsizeiptr                  get_n_blocks() const { return n_blocks; }
        GLsizeiptr                  get_stride() const { return stride; }
        GLuint                      get_vao_ID() const { return vao_ID; }
        GLuint                      get_buff_ID() const { return buff_ID; }
        GLenum                      get_usage() const { return usage; }
        GLenum                      get_intended_target() const { return intended_target; }
        bool                        get_data_loaded() const { return data_loaded; }
        bool                        get_verts_specified() const { return verts_specified; }
#endif
        friend std::ostream&        operator <<( std::ostream& out, buffer const& rhs );
    protected:
//        context const*              target_context;
        unsigned char*              data;
        GLsizeiptr                  n_blocks;
        GLsizeiptr                  stride;
        GLuint                      vao_ID;
        GLuint                      buff_ID;
        GLenum                      usage;
        GLenum                      intended_target;
        bool                        data_loaded;
        bool                        verts_specified;
        typedef std::vector<info*>  attrib_vector;
        attrib_vector*              attributes;
        GLsizeiptr                  attribute_offset( GLuint index ) const;
    };

    inline  buffer::settings::settings() :
                    n_blocks(0),
                    usage( gl::DYNAMIC_DRAW ),
                    intended_target( gl::ARRAY_BUFFER ) {}

    inline buffer::settings&  buffer::settings::blocks( GLsizeiptr n_blocks )
    { this->n_blocks = n_blocks; return *this; }

    inline  buffer::settings&     buffer::settings::static_draw()
    { usage = gl::STATIC_DRAW; return *this; }

    inline  buffer::settings&     buffer::settings::static_read()
    { usage = gl::STATIC_READ; return *this; }

    inline  buffer::settings&     buffer::settings::static_copy()
    { usage = gl::STATIC_COPY; return *this; }

    inline  buffer::settings&     buffer::settings::dynamic_draw()
    { usage = gl::DYNAMIC_DRAW; return *this; }

    inline  buffer::settings&     buffer::settings::dynamic_read()
    { usage = gl::DYNAMIC_READ; return *this; }

    inline  buffer::settings&     buffer::settings::dynamic_copy()
    { usage = gl::DYNAMIC_COPY; return *this; }

    inline  buffer::settings&     buffer::settings::stream_draw()
    { usage = gl::STREAM_DRAW; return *this; }

    inline  buffer::settings&     buffer::settings::stream_read()
    { usage = gl::STREAM_READ; return *this; }

    inline  buffer::settings&     buffer::settings::stream_copy()
    { usage = gl::STREAM_COPY; return *this; }

    inline  buffer::settings&     buffer::settings::for_array()
    { intended_target = gl::ARRAY_BUFFER; return *this; }
    //inline  buffer::settings&     buffer::settings::for_atomic_counter()
    //{ intended_target = gl::ATOMIC_COUNTER_BUFFER; return *this; }
    inline  buffer::settings&     buffer::settings::for_copy_read()
    { intended_target = gl::COPY_READ_BUFFER; return *this; }
    inline  buffer::settings&     buffer::settings::for_copy_write()
    { intended_target = gl::COPY_WRITE_BUFFER; return *this; }
    //inline  buffer::settings&     buffer::settings::for_indirect_draw()
    //{ intended_target = gl::DRAW_INDIRECT_BUFFER; return *this; }
    //inline  buffer::settings&     buffer::settings::for_indirect_dispatch()
    //{ intended_target = gl::DISPATCH_INDIRECT_BUFFER; return *this; }
    inline  buffer::settings&     buffer::settings::for_element_array()
    { intended_target = gl::ELEMENT_ARRAY_BUFFER; return *this; }
    inline  buffer::settings&     buffer::settings::for_pixel_packing()
    { intended_target = gl::PIXEL_PACK_BUFFER; return *this; }
    inline  buffer::settings&     buffer::settings::for_pixel_unpacking()
    { intended_target = gl::PIXEL_UNPACK_BUFFER; return *this; }
    //inline  buffer::settings&     buffer::settings::for_shader_storage()
    //{ intended_target = gl::SHADER_STORAGE_BUFFER; return *this; }
    //inline  buffer::settings&     buffer::settings::for_texture()
    //{ intended_target = gl::TEXTURE_BUFFER; return *this; }
    inline  buffer::settings&     buffer::settings::for_transform_feedback()
    { intended_target = gl::TRANSFORM_FEEDBACK_BUFFER; return *this; }
    //inline  buffer::settings&     buffer::settings::for_uniform()
    //{ intended_target = gl::UNIFORM_BUFFER; return *this; }

    inline GLsizeiptr  buffer::size() const
    { return n_blocks; }
    
    template< typename DATA >
    void buffer::load_attribute( GLuint index, std::vector< DATA > const& attrib_data )
    {
        if ( not verts_specified ) {
            throw std::logic_error( "Attribute value assignment attempted when vertex format was not specified." );
        }
        if ( (*(*attributes)[index]) != type< DATA >() ) {
            std::string msg = "Type stored in std::vector, ";
            msg += type< DATA >().name();
            msg += ", does not match type specified at buffer index ";
            msg += index;
            msg += ", ";
            msg += (*attributes)[index]->name();
            msg += ".";
            throw std::invalid_argument( msg );
        }
        if ( attrib_data.size() > n_blocks ) {
            std::string msg = "Attribute value assignment attempted with ";
            msg += n_blocks;
            msg += " allocated data blocks but ";
            msg += attrib_data.size();
            msg += " attribute values.";
            throw std::invalid_argument( msg);
        }
        
        if ( data == 0 ) {
            data = new unsigned char[n_blocks * stride];
        }

        GLsizeiptr block;
        unsigned char* cursor = data;
        cursor += attribute_offset( index );
        for( block = 0; block < n_blocks; ++block ) {
            raw_map const mapped_data = attrib_data[block].to_map();
            for( size_t b = 0; b < mapped_data.n_bytes; ++b ) {
                cursor[b] = mapped_data[b];
            }
            cursor += stride;
        }
    }
}
#endif