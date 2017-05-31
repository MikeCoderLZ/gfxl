#ifndef UNIFORM
#define UNIFORM

#include <string>

class program;

namespace gfx {
    
    class uniform {
    public:
        virtual void    upload_uniform( program const& prgm,
                                        std::string const& name ) = 0;
    };
}

#endif