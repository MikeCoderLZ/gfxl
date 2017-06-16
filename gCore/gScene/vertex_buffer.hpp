#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "buffer.hpp"

namespace gfx {

    class vertex_buffer : public buffer {
    public:
        class settings : public buffer::settings {
        public:
                        settings( buffer::settings const& set
                                    = buffer::settings() );
            friend      class vertex_buffer;
        };
        
                        vertex_buffer( settings const& set = settings() );
        virtual         ~vertex_buffer();
        virtual void    upload_data();
        virtual void    align();
    protected:
        GLuint          vao_ID;

    };
    
    inline  vertex_buffer::settings::settings( buffer::settings const& set )
                                                : buffer::settings( set ) {}


}
#endif