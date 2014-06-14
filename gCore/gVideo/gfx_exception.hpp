#ifndef GFX_EXCEPTION_HPP
#define GFX_EXCEPTION_HPP

#include <stdexcept>

namespace gfx {

    class compilation_error : public std::logic_error {
    public:
        explicit compilation_error( std::string const& msg ) : logic_error( msg ) {};
    };
    
    class binding_error : public std::logic_error {
    public:
        explicit binding_error( std::string const& msg ) : logic_error( msg ) {};
    };

    class unformatted_error : public std::logic_error {
    public:
        explicit unformatted_error( std::string const& msg ) : logic_error( msg ) {};
    };
    
    class initialization_error : public std::logic_error {
    public:
        explicit initialization_error( std::string const& msg ) : logic_error( msg ) {};
    };
    
    class version_error : public std::logic_error {
    public:
        explicit version_error( std::string const& msg ) : logic_error( msg ) {};
    };
}

#endif