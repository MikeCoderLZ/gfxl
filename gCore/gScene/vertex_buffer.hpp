#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "buffer.hpp"

namespace gfx {

    class vertex_buffer : public buffer {
    public:
        class settings : public buffer::settings {
                        settings( buffer::settings const& set
                                    = buffer::settings() );
            friend      class vertex_buffer;
        };
        
                    vertex_buffer( settings const& set = settings();
                    ~vertex_buffer();
        void        align_vertices();

    };


}
#endif