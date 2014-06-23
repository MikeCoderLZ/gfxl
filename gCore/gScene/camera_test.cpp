#include <iostream>
#include <string>

#include "../../UnitTest++_src/UnitTest++.h"

#include "camera.hpp"

using namespace gfx;

SUITE( CameraTests )
{
    TEST( CameraCreation )
    {
        camera test_cam;
        CHECK_EQUAL( mat4::perspective( 135.0, 1.33, 0.0, 100.0),
                     test_cam.view_matrix() );
    }
}

int main( int argc, char** argv )
{
    return UnitTest::RunAllTests();
}