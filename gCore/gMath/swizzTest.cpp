#include "swizzTest.hpp"

float test::output_float()
{
    using namespace gfx;
    fvec3 avec ( 1.8f, 6.2f, 104.8f );
    return avec( x );
}