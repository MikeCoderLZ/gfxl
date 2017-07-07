#ifndef GFX_EXCEPTION_HPP
#define GFX_EXCEPTION_HPP

#include <stdexcept>

namespace gfx {
    /**
     * \class gfx::compilation_error gfx_exception.hpp "gCore/gVideo/gfx_exception.hpp"
     * \brief A logic error thrown when runtime compilation fails.
     * 
     * Currently, the only runtime compilation is that of GLSL shaders.
     */
    class compilation_error : public std::logic_error {
    public:
        explicit compilation_error( std::string const& msg ) : logic_error( msg ) {};
    };
    /**
     * \class gfx::binding_error gfx_exception.hpp "gCore/gVideo/gfx_exception.hpp"
     * \brief A logic error thrown when OpenGL binding fails...
     * 
     * ...or when it produces an unusable OpenGL server state.
     */
    class binding_error : public std::logic_error {
    public:
        explicit binding_error( std::string const& msg ) : logic_error( msg ) {};
    };
    /**
     * \class gfx::unformatted_error gfx_exception.hpp "gCore/gVideo/gfx_exception.hpp"
     * \brief A logic error thrown when data has not been formatted correctly.
     * 
     * Intended for use with buffers and uniforms.
     * \todo ...Is this thing even ever thrown? Did I forget I wrote this?
     */
    class unformatted_error : public std::logic_error {
    public:
        explicit unformatted_error( std::string const& msg ) : logic_error( msg ) {};
    };
    /**
     * \class gfx::initialization_error gfx_exception.hpp "gCore/gVideo/gfx_exception.hpp"
     * \brief A logic error thrown when a subsystem has not been initialized.
     * 
     * The class gfx::video_system uses this if it is asked to do something
     * it cannot do without having initialized the underlying libraries
     * (OpenGL and SDL).
     */
    class initialization_error : public std::logic_error {
    public:
        explicit initialization_error( std::string const& msg ) : logic_error( msg ) {};
    };
    /**
     * \class gfx::version_error gfx_exception.hpp "gCore/gVideo/gfx_exception.hpp"
     * \brief A logic error thrown when a feature is requested that is not
     * supported by the current version of the associated system.
     * 
     * Usually, gfx::video_system is the system that does not support the
     * feature.
     */
    class version_error : public std::logic_error {
    public:
        explicit version_error( std::string const& msg ) : logic_error( msg ) {};
    };
}

#endif