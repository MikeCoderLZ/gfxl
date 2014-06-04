#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "video_manager.hpp"
#include "../gMath/datatype.hpp"
#include "../../UnitTest++_src/UnitTest++.h"

using namespace gfx;

video_manager test_mngr;

SUITE( WindowTests )
{
    TEST( WindowTitle )
    {
        window test_wndw1 = test_mngr.new_window( window::settings()
                                                  .title("Fiddlesticks") );
        CHECK_EQUAL( "Fiddlesticks", test_wndw1.title() );
        test_wndw1.title( "Brittlebits" );
        CHECK_EQUAL( "Brittlebits", test_wndw1.title() );
    }
    
    TEST( WindowXPosition )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .center_x_at( 256 )
                                                 .title("WindowXPosition") );
        CHECK_EQUAL( 256, test_wndw.x_pos() );
        test_wndw.x_pos( 128 );
        CHECK_EQUAL( 128, test_wndw.x_pos() );
    }
    
    TEST( WindowYPosition )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .center_y_at( 256 )
                                                 .title("WindowYPosition") );
        CHECK_EQUAL( 256, test_wndw.y_pos() );
        test_wndw.y_pos( 128 );
        CHECK_EQUAL( 128, test_wndw.y_pos() );
    }
    
    TEST( WindowPosition )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .center_at( 256, 256 )
                                                 .title("WindowPosition") );
        CHECK_EQUAL( ivec2( 256, 256 ), test_wndw.position() );
        test_wndw.position( 128, 128 );
        CHECK_EQUAL( ivec2( 128, 128 ), test_wndw.position() );
        test_wndw.position( ivec2( 384, 384 ) );
        CHECK_EQUAL( ivec2( 384, 384 ), test_wndw.position() );
    }
    
    TEST( WindowXCentering )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .center_x()
                                                 .title("WindowXCentering") );
        CHECK( test_wndw.is_x_centered() );
    }
    
    TEST( WindowYCentering )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .center_y()
                                                 .title("WindowYCentering") );
        CHECK( test_wndw.is_y_centered() );
    }
    
    TEST( WindowWidth )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .width( 256 )
                                                 .title("WindowWidth") );
        CHECK_EQUAL( 256, test_wndw.width() );
        test_wndw.width( 512 );
        CHECK_EQUAL( 512, test_wndw.width() );
    }
    
    TEST( WindowHeight )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .height( 256 )
                                                 .title("WindowHeight") );
        CHECK_EQUAL( 256, test_wndw.height() );
        test_wndw.height( 512 );
        CHECK_EQUAL( 512, test_wndw.height() );
    }
    
    TEST( WindowDimensions )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .dimensions( 256, 256 )
                                                 .title("WindowDimension") );
        CHECK_EQUAL( ivec2( 256, 256 ), test_wndw.dimensions() );
        test_wndw.dimensions( 512, 512 );
        CHECK_EQUAL( ivec2( 512, 512 ), test_wndw.dimensions() );
        test_wndw.dimensions( ivec2( 128, 128 ) );
        CHECK_EQUAL( ivec2( 128, 128 ), test_wndw.dimensions() );
    }
    
    TEST( WindowMaximized )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .maximized()
                                                 .title("WindowMaximized") );
        CHECK( test_wndw.is_maximized() );
        test_wndw.minimize();
        test_wndw.maximize();
        CHECK( test_wndw.is_maximized() );
    }
    
//     TEST( WindowMinimized )
//     {
//         window test_wndw = test_mngr.new_window( window::settings()
//                                                  .minimized()
//                                                  .title("WindowMinimized") );
//         std::cout << "Is Minimized? " << test_wndw.is_minimized() << std::endl;
//         //test_wndw.minimize();
//         std::cout << "Is Minimized? " << test_wndw.is_minimized() << std::endl;
//         bool mini = test_wndw.is_maximized();
//         CHECK_EQUAL( true, mini );
//         test_wndw.maximize();
//         std::cout << "Confirm [y/n]: ";
//         std::string confirmation;
//         std::cin >> confirmation;
//         CHECK_EQUAL( "y", confirmation );
//         test_wndw.minimize();
//         CHECK( test_wndw.is_minimized() );
//     }

    TEST( WindowResizable )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .resizable()
                                                 .title("WindowResizable") );
        CHECK( test_wndw.is_resizable() );
    }
    
    TEST( WindowOpenGL )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .has_3D()
                                                 .title("WindowOpenGL") );
        CHECK( test_wndw.has_3D() );
    }
    
    TEST( WindowVisibility )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .visible()
                                                 .title("WindowVisiblity") );
        CHECK( test_wndw.is_visible() );
        test_wndw.make_hidden();
        CHECK_EQUAL( false, test_wndw.is_visible() );
        test_wndw.make_visible();
        CHECK( test_wndw.is_visible() );
        
    }
    
    TEST( WindowBorders )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                 .has_border()
                                                 .title("WindowBorders1") );
        CHECK( test_wndw.has_border() );
        
        window test_wndw1 = test_mngr.new_window( window::settings()
                                                  .no_border()
                                                  .title("WindowBorders2") );
        CHECK_EQUAL( false, test_wndw1.has_border() );
    }
    
//     TEST( WindowFocus )
//     {
//         window test_wndw = test_mngr.new_window( window::settings()
//                                                  .has_focus()
//                                                  .title("WindowFocus") );
//         CHECK( test_wndw.has_focus() );
//     }
//     TEST( WindowDefaultCreation )
//     {
//         window test_wndw1 = test_mngr.new_window();
//         std::cout << "Created default window, centered on screen and 512×512." << std::endl;
//         std::cout << "Confirm [y/n]: ";
//         std::string confirmation;
//         std::cin >> confirmation;
//         CHECK_EQUAL( "y", confirmation );
//     }
}

int main( int argc, char* argv[] )
{
    return UnitTest::RunAllTests();
}