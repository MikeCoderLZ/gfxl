#include <iostream>
#include <stdexcept>
#include <string>

#include "../gVideo/video.hpp"
#include "texture.hpp"
#include "../gMath/datatype.hpp"
#include "../../UnitTest++_src/UnitTest++.h"

using namespace gfx;

SUITE( Texture1DTests )
{
    TEST( Texture1DCreation )
    {
        texture_1D test_txtr;
    }
    
    TEST( Texture1DDecode )
    {
        texture_1D test_txtr ( texture_1D::settings()
                                .dimension( 256u )
                                .file( "./tex/test_1D.png" ) );
        try {
            test_txtr.decode_file();
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
        
        CHECK_EQUAL( 128u, test_txtr.width() );
        CHECK_EQUAL( 24u, test_txtr.pixel_bits() );
    }
    
    TEST( Texture1DLoad )
    {
        texture_1D test_txtr ( texture_1D::settings()
                                .dimension( 256u )
                                .unsigned_norm_3( eight_bit )
                                .file( "./tex/test_1D.png" ) );        
        
        std::string excepted ( "Exception not caught." );
        try {
            test_txtr.load_data();
        } catch ( std::logic_error& e ) {
            excepted = "Lack of context exception caught.";
        }
        CHECK_EQUAL( "Lack of context exception caught.", excepted );
        
        window test_wndw ( window::settings()
                            .has_3D()         );
        context test_cntx ( test_wndw );
        
        excepted = "Exception not caught.";
        try {
            test_txtr.load_data();
        } catch ( std::logic_error& e ) {
            excepted = "Lack of texture data exception caught.";
        }
        
        CHECK_EQUAL( "Lack of texture data exception caught.", excepted );
        
        test_txtr.decode_file();
        
        excepted = "Exception not caught.";
        try {
            test_txtr.load_data();
        } catch ( std::logic_error& e ) {
            excepted = "Mystery exception caught.";
        }
        
        CHECK_EQUAL( "Exception not caught.", excepted );

    }
}

SUITE( Texture2DTests )
{
    TEST( Texture2DCreation )
    {
        texture_2D test_txtr;
    }
    
    TEST( Texture2DDecode )
    {
        texture_2D test_txtr ( texture_2D::settings()
                                .dimensions( 256u, 256u )
                                .file( "./tex/test_2D.png" ) );
        try {
            test_txtr.decode_file();
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
        
        CHECK_EQUAL( 128u, test_txtr.width() );
        CHECK_EQUAL( 128u, test_txtr.height() );
        CHECK_EQUAL( 24u, test_txtr.pixel_bits() );
    }
    
    TEST( Texture2DLoad )
    {
        texture_2D test_txtr ( texture_2D::settings()
                                .dimensions( 256u, 256u )
                                .unsigned_norm_3( eight_bit )
                                .file( "./tex/test_2D.png" ) );
        
        std::string excepted ( "Exception not caught." );
        try {
            test_txtr.load_data();
        } catch ( std::logic_error& e ) {
            excepted = "Lack of context exception caught.";
        }
        CHECK_EQUAL( "Lack of context exception caught.", excepted );
        
        window test_wndw ( window::settings()
                            .has_3D()         );
        context test_cntx ( test_wndw );
        
        excepted = "Exception not caught.";
        try {
            test_txtr.load_data();
        } catch ( std::logic_error& e ) {
            excepted = "Lack of texture data exception caught.";
        }
        
        CHECK_EQUAL( "Lack of texture data exception caught.", excepted );
        
        test_txtr.decode_file();
        
        excepted = "Exception not caught.";
        try {
            test_txtr.load_data();
        } catch ( std::logic_error& e ) {
            excepted = "Mystery exception caught.";
        }
        
        CHECK_EQUAL( "Exception not caught.", excepted );

    }
}

int main( int argc, char** argv )
{
    video_system::get().initialize( video_system::settings() );
    return UnitTest::RunAllTests();
}