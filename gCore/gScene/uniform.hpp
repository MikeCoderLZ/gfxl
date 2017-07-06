#ifndef UNIFORM
#define UNIFORM

#include <string>
#include <stdexcept>
//#include "../gVideo/gfx_exception.hpp"
#include "program.hpp"

namespace gfx {
    /**
     * \class gfx::uniformable uniform.hpp "gCore/gScene/uniform.hpp"
     * \brief An interface for data types that can be uploaded as
     * uniforms.
     * 
     * I am still trying to figure out a good way to deal with uniforms.
     * This is one idea, though no code uses it yet and I am unsure if I
     * want to do it this way. As mentioned elsewhere in light.hpp, I may
     * expand the class system in datatype.hpp.
     */
    class uniformable {
    private:
        virtual void    register_uniform() = 0;
        virtual void    upload_uniform() = 0;
    };
    /**
     * \class gfx::uniform uniform.hpp "gCore/gScene/uniform.hpp"
     * \brief An interface for data types that can be uploaded as
     * uniforms.
     * 
     * This code is actually used for now, though it doesn't provide
     * much benefit and could easily be implemented without an interface.
     */
    class uniform {
    public:
        virtual void    upload_uniform( program& prgm,
                                        std::string const& name ) = 0;
    protected:
        void        check_program( program const& prgm );
    };
    /**
     * \brief Check if the given program is currently in use.
     * 
     * This is a pointless function, as I ended up adding the interogative
     * to \ref gfx::program "program" as a public function anyway.
     */
    inline void uniform::check_program( program const& prgm )
    {
        if ( not prgm.in_use() ) {
            throw std::logic_error( "Cannot load uniform data into program that is not in use." );
        }
    }
}

#endif