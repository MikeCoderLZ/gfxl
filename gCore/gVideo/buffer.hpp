#ifndef BUFFER_HPP
#define BUFFER_HPP

namespace gfx {

    class block_spec {
    public:
                                        block_spec();
                                        ~block_spec();
        template< typename T >
        block_spec&                     attribute( type<T> const& proto );
    private:
        typedef std::vector< info* >    attrib_vector;
        attrib_vector*                  attributes;
        friend                          class buffer;
    };

    inline  block_spec::block_spec() : attributes( new block_spec::attrib_vector() ) {}

    inline block_spec::~block_spec()
    {
        attrib_vector::iterator i;
        for ( i = attributes->begin(); i < attributes->end(); ++i )
        {
            delete *i;
        }
        delete attributes;
    }

    template< typename T > inline
    block_spec&     block_spec::attribute( type<T> const& proto )
    {   info* new_attrib = (info*) proto.copy();
        attributes->push_back( new_attrib );
        return *this; }
        
    class buffer {
    public:
        
        class settings {
        public:
                                settings();
            settings&           blocks( GLsizeiptr new_n_blocks );
            settings&           static_draw();
            settings&           static_read();
            settings&           static_copy();
            settings&           dynamic_draw();
            settings&           dynamic_read();
            settings&           dynamic_copy();
            settings&           stream_draw();
            settings&           stream_read();
            settings&           stream_copy();
            settings&           for_array();
        //    settings&     for_atomic_counter();
            settings&           for_copy_read();
            settings&           for_copy_write();
        //    settings&     for_indirect_draw();
        //    settings&     for_indirect_dispatch();
            settings&           for_element_array();
            settings&           for_pixel_packing();
            settings&           for_pixel_unpacking();
        //    settings&     for_shader_storage();
            settings&           for_texture();
            settings&           for_transform_feedback();
            settings&           for_uniform();
        private:
            GLsizeiptr          blocks_v;
            GLenum              usage_v;
            GLenum              target_v;
            friend              class buffer;
        };
                                    buffer( settings const& set = settings() );
        friend std::ostream&        operator <<( std::ostream& out, buffer const& rhs );
                                    ~buffer();
        void                        block_format( block_spec const& spec );
        void                        set_blocks( GLsizeiptr const n_blocks );
        void                        add_blocks( GLsizeiptr const more_blocks );
        template< typename DATA >
        void                        fill_attribute( GLuint index,
                                                    std::vector< DATA > const& attrib_data );
        void                        load_data();
        void                        align_vertices();
        GLuint                      get_id() const { return buff_ID; }
    private:
        unsigned char*              data;
        GLsizeiptr                  blocks;
        GLsizeiptr                  stride;
        GLuint                      vao_ID;
        GLuint                      buff_ID;
        GLenum                      usage;
        GLenum                      target;
        bool                        data_loaded;
        bool                        verts_specified;
        typedef std::vector<info*>  attrib_vector;
        attrib_vector*              attributes;
                                    
        GLsizeiptr                  attribute_offset( GLuint index ) const;
        friend                      class video_system;
    };

    inline buffer::settings::settings() :
                            blocks_v ( 0 ),
                            usage_v  ( gl::DYNAMIC_DRAW ),
                            target_v ( gl::ARRAY_BUFFER ) {}
                            
    inline buffer::settings&    buffer::settings::blocks( GLsizeiptr blocks )
    { blocks_v = blocks; return *this; }

    inline buffer::settings&    buffer::settings::static_draw()
    { usage_v = gl::STATIC_DRAW; return *this; }

    inline buffer::settings&    buffer::settings::static_read()
    { usage_v = gl::STATIC_READ; return *this; }

    inline buffer::settings&    buffer::settings::static_copy()
    { usage_v = gl::STATIC_COPY; return *this; }

    inline buffer::settings&    buffer::settings::dynamic_draw()
    { usage_v = gl::DYNAMIC_DRAW; return *this; }

    inline buffer::settings&    buffer::settings::dynamic_read()
    { usage_v = gl::DYNAMIC_READ; return *this; }

    inline buffer::settings&    buffer::settings::dynamic_copy()
    { usage_v = gl::DYNAMIC_COPY; return *this; }

    inline buffer::settings&    buffer::settings::stream_draw()
    { usage_v = gl::STREAM_DRAW; return *this; }

    inline buffer::settings&    buffer::settings::stream_read()
    { usage_v = gl::STREAM_READ; return *this; }

    inline buffer::settings&    buffer::settings::stream_copy()
    { usage_v = gl::STREAM_COPY; return *this; }

    inline buffer::settings&     buffer::settings::for_array()
    { target_v = gl::ARRAY_BUFFER; return *this; }

    inline buffer::settings&     buffer::settings::for_copy_read()
    { target_v = gl::COPY_READ_BUFFER; return *this; }

    inline buffer::settings&     buffer::settings::for_copy_write()
    { target_v = gl::COPY_WRITE_BUFFER; return *this; }

    inline buffer::settings&     buffer::settings::for_element_array()
    { target_v = gl::ELEMENT_ARRAY_BUFFER; return *this; }

    inline buffer::settings&     buffer::settings::for_pixel_packing()
    { target_v = gl::PIXEL_PACK_BUFFER; return *this; }

    inline buffer::settings&     buffer::settings::for_pixel_unpacking()
    { target_v = gl::PIXEL_UNPACK_BUFFER; return *this; }

    inline buffer::settings&     buffer::settings::for_texture()
    { target_v = gl::TEXTURE_BUFFER; return *this; }

    inline buffer::settings&     buffer::settings::for_transform_feedback()
    { target_v = gl::TRANSFORM_FEEDBACK_BUFFER; return *this; }

    inline buffer::settings&     buffer::settings::for_uniform()
    { target_v = gl::UNIFORM_BUFFER; return *this; }


                            
    template< typename DATA >
    void buffer::fill_attribute( GLuint index, std::vector< DATA > const& attrib_data )
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
        if ( attrib_data.size() > blocks ) {
            std::string msg = "Attribute value assignment attempted with ";
            msg += blocks;
            msg += " allocated data blocks but ";
            msg += attrib_data.size();
            msg += " attribute values.";
            throw std::out_of_range( msg );
        }

        if ( data == 0 ) {
            data = new unsigned char[blocks * stride];
        }

        GLsizeiptr block;
        unsigned char* cursor = data;
        cursor += attribute_offset( index );
        for( block = 0; block < blocks; ++block ) {
            raw_map const mapped_data = attrib_data[block].to_map();
            for( size_t b = 0; b < mapped_data.n_bytes; ++b ) {
                cursor[b] = mapped_data[b];
            }
            cursor += stride;
        }
    }

    inline  void    buffer::load_data()
    {
        if( target == gl::ELEMENT_ARRAY_BUFFER ){
            gl::BindVertexArray( vao_ID );
            checkGLError( "vao bound for element data load" );
        }
        gl::BindBuffer( target, buff_ID );
        gl::BufferData( target, blocks * stride, data, usage );

        data_loaded = true;
    }
}
#endif