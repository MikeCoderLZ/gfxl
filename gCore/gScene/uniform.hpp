#ifndef UNIFORM
#define UNIFORM

#include <string>
#include <stdexcept>
//#include "../gVideo/gfx_exception.hpp"
#include "program.hpp"

namespace gfx {
    
    class uniformable {
    private:
        virtual void    register_uniform() = 0;
        virtual void    upload_uniform() = 0;
    };
    
    class uniform {
    public:
        virtual void    upload_uniform( program& prgm,
                                        std::string const& name ) = 0;
    protected:
        void        check_program( program const& prgm );
    };
    
    inline void uniform::check_program( program const& prgm )
    {
        if ( not prgm.in_use() ) {
            throw std::logic_error( "Cannot load uniform data into program that is not in use." );
        }
    }
}

#endif