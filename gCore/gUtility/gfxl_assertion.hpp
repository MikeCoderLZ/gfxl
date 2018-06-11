#pragma once


#include <cstdlib>
#include <string>
#include <iostream>

#ifdef GFX_ASSERTION_TEST_MODE
    #include <stdexcept>
#endif


#include "util.hpp"

#ifdef GFX_DEBUG
    #define gfx_assert( test, message ) \
                    do { gfx::dynamicAssertion( (test), "Assertion " __FILENAME__ "::" gfx_xstr(__LINE__) ": " gfx_str(test) " failed.\n" (message) ); } while(0)
#else
    #define gfx_assert( test, message ) ((void)0)
#endif

#define gfx_static_assert( test, message ) \
                do { gfx::staticAssertion<(test)>( "Assertion " __FILENAME__ "::" gfx_xstr(__LINE__) ": " gfx_str(test) " failed.\n" (message) ); } while(0)

namespace gfx {
    
    /**
     * Runtime assertion.
     *
     * If the given test evaulates to false, dynamic assertions write a message to
     * standard error output and terminate the program. Do not trace stack, do not
     * release resources, go directly to console.
     *
     * Dynamic assertions compile out when GFX_DEBUG is not defined.
     *
     * In test mode, assertions throw exceptions that can be caught by the test.
     *
     * Can be used manually, but in general use the macro gfx_assertion()
     * for better locality information.
     *
     * @param test A boolean-valued expression which, when false, will trigger termination
     * @param message A message to print to the standard error output.
     */
    inline void dynamicAssertion( bool test,
                                  const char* message )
    {
        // Note that we have a macro switch on debug here as well,
        // in case anyone uses this function manually. With the
        // macro, it would never even appear in code.
        #ifdef GFX_DEBUG
            #ifdef GFX_ASSERTION_TEST_MODE
                if ( !test ) {
                    // In test mode we throw assertions instead, so we can test
                    throw std::exception( message );
                }
            #else
                if ( !test ) {
                    std::cerr << message << std::endl;
                    abort();
                }
            #endif
        #endif
        return;
    }

    /**
     * Compiletime assertion.
     *
     * If the given constant boolean expression evaluates to false, static assertions
     * write a message to standard error output and terminate the program. Do not trace
     * stack, do not release resources, go directly to console.
     *
     * Static assertions compile out if the test expression is true because the
     * test is a constant expression.
     *
     * In test mode, assertions throw exceptions that can be caught by the test.
     *
     * Can be used manually, but in general use the macro gfx_dynamic_assertion()
     * for better locality information.
     *
     * @param test A boolean-valued expression which, when false, will trigger termination
     * @param message A message to print to the standard error output.
     */
    template< constexpr bool TEST>
    inline void staticAssertion( const char* message )
    {
        
        #ifdef GFX_ASSERTION_TEST_MODE
            if ( !TEST ) {
                // In test mode we throw assertions instead, so we can test
                throw std::exception( message );
            }
        #else
            if ( !TEST ) {
                std::cerr << message << std::endl;
                abort();
            }
        #endif
        
        return;
    }
    
}