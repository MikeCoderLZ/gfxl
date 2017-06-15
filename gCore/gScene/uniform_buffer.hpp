#ifndef UNIFORM_BUFFER_HPP
#define UNIFORM_BUFFER_HPP

#include "buffer.hpp"

namespace gfx {

    class uniform_buffer : public buffer {
    public:
        class settings : public buffer::settings {
                        settings( buffer::settings const& set
                                    = buffer::settings() );
            friend      class vertex_buffer;
        };
        
                    uniform_buffer( settings const& set = settings();
                    ~uniform_buffer();
        void        align_uniform_block();

    };


}
#endif