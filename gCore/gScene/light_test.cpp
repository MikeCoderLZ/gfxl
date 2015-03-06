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
        
        CHECK_EQUAL( 1.0f, tst_light1.radiance() );
        CHECK_EQUAL( vec3( 0.0f ), tst_light1.position() );
        CHECK_EQUAL( vec3( 1.0f ), tst_light1.color() );
        CHECK_EQUAL( 1.0f, tst_light1.radius() );
    }
    
    TEST( SphereLightCreationSpecified ) {

        sphere_light tst_light2 ( sphere_light::settings()
                            .radiance( 10.0f )
                            .position( vec3( 2.0f ) )
                            .color( vec3( 1.0f, 0.0f, 1.0f ) )
                            .radius( 5.5f )                    );
        
        CHECK_EQUAL( 10.0f, tst_light2.radiance() );
        CHECK_EQUAL( vec3( 2.0f ), tst_light2.position() );
        CHECK_EQUAL( vec3( 1.0f, 0.0f, 1.0f ), tst_light2.color() );
        CHECK_EQUAL( 5.5f, tst_light2.radius() );
    }
    
    TEST( SpotLightCreation ) {
        spot_light tst_light3;
        
        CHECK_EQUAL( 1.0f, tst_light3.radiance() );
        CHECK_EQUAL( vec3( 0.0f ), tst_light3.position() );
        CHECK_EQUAL( vec3( 0.0f, 0.0f, -1.0f ), tst_light3.direction() );
        CHECK_EQUAL( vec3( 1.0f ), tst_light3.color() );
        CHECK_EQUAL( angle::in_degs( 45.0f ).to_rads(), tst_light3.sweep().to_rads() );
        CHECK_EQUAL( 1.0f, tst_light3.radius() );
    }
    
    TEST( SpotLightCreationSpecified ) {
        spot_light tst_light4( spot_light::settings()
                               .radiance( 15.0f )
                               .position( vec3( 2.0f, 1.0f, -4.0f ) )
                               .direction( vec3( -0.5f, 0.5f, -1.0f ) )
                               .color( vec3( 0.0f, 1.0f, 1.0f ) )
                               .sweep( angle::in_degs( 60.0f ) )
                               .radius( 0.2f )                       );
        
        CHECK_EQUAL( 15.0f, tst_light4.radiance() );
        CHECK_EQUAL( vec3( 2.0f, 1.0f, -4.0f ), tst_light4.position() );
        CHECK_EQUAL( vec3( -0.5f, 0.5f, -1.0f ), tst_light4.direction() );
        CHECK_EQUAL( vec3( 0.0f, 1.0f, 1.0f ), tst_light4.color() );
        CHECK_EQUAL( angle::in_degs( 60.0f ).to_rads(), tst_light4.sweep().to_rads() );
        CHECK_EQUAL( 0.2f, tst_light4.radius() );
    }
    
    TEST( SunLightCreation ) {
        sun_light tst_light5;
        
        CHECK_EQUAL( 1.0f, tst_light5.radiance() );
        CHECK_EQUAL( vec3( 0.0f, 0.0f, -1.0f ), tst_light5.direction() );
        CHECK_EQUAL( vec3( 1.0f ), tst_light5.color() );
    }
    
    TEST( SunLightCreationSpecified ) {
        sun_light tst_light6( sun_light::settings()
                                .radiance( 100.0f)
                                .direction( vec3( -0.5f, 0.5f, -0.5f ) )
                                .color( vec3( 1.0f, 1.0f, 0.5f ) )       ); 
        
        CHECK_EQUAL( 100.0f, tst_light6.radiance() );
        CHECK_EQUAL( vec3( -0.5f, 0.5f, -0.5f ), tst_light6.direction() );
        CHECK_EQUAL( vec3( 1.0f, 1.0f, 0.5f ), tst_light6.color() );
    }
}

int main( int argc, char** argv )
{
    return UnitTest::RunAllTests();
}