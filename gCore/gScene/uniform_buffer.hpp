#ifndef UNIFORM_BUFFER_HPP
#define UNIFORM_BUFFER_HPP

#include "buffer.hpp"

namespace gfx {

    class uniform_buffer : public buffer {
    public:
        class settings : public buffer::settings {
        public:
                        settings( buffer::settings const& set
                                    = buffer::settings() );
            settings&   use_std140();
            friend      class uniform_buffer;
        protected:
            bool        use_std140_v;
        };
        
                        uniform_buffer( settings const& set = settings();
        virtual         ~uniform_buffer();
        virtual void    align();
    protected:
        

    };

    uniform_buffer::settings::settings( buffer::settings const& set ) :
                                            buffer::settings( set ),
                                            use_std140_v ( false ) {}

    uniform_buffer::settings&   uniform_buffer::settings::use_std140()
    { use_std140_v = true; }

}
#endif