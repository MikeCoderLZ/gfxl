#pragma once

#include <cstdlib>
#include <string>
#include <iostream>

#ifdef GFX_WARNING_TEST_MODE
    #include <stdexcept>
#endif

#include "util.hpp"

#ifdef GFX_DEBUG
    #define gfx_warning( test, message ) \
                    do { gfx::dynamicWarning( (test), "Warning " __FILENAME__ "::" gfx_xstr(__LINE__) ": " gfx_str(test) " triggered.\n" (message) ); } while(0)
#else
    #define gfx_warning( test, message ) ((void)0)
#endif

#define gfx_static_warning( test, message ) \
                do { gfx::staticWarning<test>( "Warning " __FILENAME__ "::" gfx_xstr(__LINE__) ": " gfx_str(test) " triggered.\n" (message) ); } while(0)

namespace gfx {
    
    /**
     * Runtime warning.
     *
     * If the given test evaulates to true, dynamic warnings write a message to
     * standard error output; that is, they function like assertions but aren't
     * blocking.
     *
     * Dynamic assertions compile out when GFX_DEBUG is not defined.
     *
     * In test mode, warnings throw exceptions that can be caught by the test.
     *
     * Can be used manually, but in general use the macro gfx_dynamic_assertion()
     * for better locality information.
     *
     * @param test A boolean-valued expression which, when true, will trigger logging
     * @param message A message to print to the standard error output.
     */
    inline void dynamicWarning( bool test,
                                const char* message )
    {
        // Note that we have a macro switch on debug here as well,
        // in case anyone uses this function manually. With the
        // macro, it would never even appear in code.
        #ifdef GFX_DEBUG
            #ifdef GFX_WARNING_TEST_MODE
                if ( !test ) {
                    // In test mode we throw assertions instead, so we can test
                    throw std::exception( message );
                }
            #else
                if ( !test ) {
                    std::cerr << message << std::endl;
                }
            #endif
        #endif
        
        return;
    }

    /**
     * Compiletime warning.
     *
     * If the given constant boolean expression evaluates to true, static warnings
     * write a message to standard error output; that is, they function like assertions
     * but aren't blocking.
     *
     * Static assertions compile out if the test expression is false because the
     * test is a constant expression.
     *
     * In test mode, warnings throw exceptions that can be caught by the test.
     *
     * Can be used manually, but in general use the macro gfx_dynamic_assertion()
     * for better locality information.
     *
     * @param test A boolean-valued expression which, when true, will trigger logging
     * @param message A message to print to the standard error output.
     */
    template< constexpr bool TEST>
    inline void staticWarning( const char* message )
    {
        #ifdef GFX_ASSERTION_TEST_MODE
            if ( !TEST ) {
                // In test mode we throw assertions instead, so we can test
                throw std::exception( message );
            }
        #else
            if ( !TEST ) {
                std::cerr << message << std::endl;
            }
        #endif
        
        return;
    }
    
}