#include <iostream>
#include <string>

#include "../../UnitTest++_src/UnitTest++.h"

#include "camera.hpp"

using namespace gfx;

SUITE( CameraTests )
{
    TEST( CameraCreation )
    {
        proj_cam test_cam;
        mat4 ref_view = mat4::perspective( d_angle::in_degs(135.0),
                                           1.33, 0.0, 100.0);
        CHECK_EQUAL( ref_view,
                     test_cam.view_matrix() );
    }
    
    TEST( CameraChangeLook )
    {
        proj_cam test_cam ( proj_cam::settings()
                          .look_at( vec3(-1.0f, 0.0f, 0.0f) ) );
        mat4 ref_perspective = mat4::perspective( d_angle::in_degs(135.0),
                                                  1.33, 0.0, 100.0);
        mat4 ref_rot1 = mat4::rotation( vec3( 0.0f, 1.0f, 0.0f ),
                                        d_angle::in_degs( -90.0 ) );
        CHECK_EQUAL( ref_perspective * ref_rot1,
                     test_cam.view_matrix() );
        test_cam.look_at( vec3( 1.0f, 0.0f, 0.0f ) );
        mat4 ref_rot2 = mat4::rotation( vec3( 0.0f, 1.0f, 0.0f ),
                                        d_angle::in_degs( 90.0 ) );
        CHECK_EQUAL( ref_perspective * ref_rot2,
                     test_cam.view_matrix() );
    }
}

int main( int argc, char** argv )
{
    return UnitTest::RunAllTests();
}