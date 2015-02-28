#include <iostream>
#include <stdexcept>
#include <string>

// #include "../gVideo/video.hpp"
#include "light.hpp"
#include "../gMath/datatype.hpp"
#include "../../UnitTest++_src/UnitTest++.h"

using namespace gfx;

SUITE( LightTests )
{
    
    TEST( SphereLightCreation ) {
        sphere_light tst_light1;
        sphere_light tst_light2 ( sphere_light::settings()
                                    .radiance( 10.0f )
                                    .position( vec3( 1.0f ) )
                                    .color( vec3( 1.0f, 0.0f, 1.0f ) )
                                    .radius( 5.5f )                    );
        CHECK_EQUAL( 1.0f, tst_light1.radiance() );
        CHECK_EQUAL( vec3( 0.0f ), tst_light1.position() );
        CHECK_EQUAL( vec3( 1.0f ), tst_light1.color() );
        CHECK_EQUAL( 1.0f, tst_light1.radius() );
        
        CHECK_EQUAL( 10.0f, tst_light2.radiance() );
        CHECK_EQUAL( vec3( 1.0f ), tst_light2.position() );
        CHECK_EQUAL( vec3( 1.0f, 0.0f, 1.0f ), tst_light2.color() );
        CHECK_EQUAL( 5.5f, tst_light2.radius() );
    }
    
}

int main( int argc, char** argv )
{
    return UnitTest::RunAllTests();
}