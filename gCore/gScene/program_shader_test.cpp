#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "../gMath/datatype.hpp"
#include "../../UnitTest++_src/UnitTest++.h"

#include "../gVideo/video.hpp"
#include "vertex_buffer.hpp"
#include "program.hpp"

using namespace gfx;

SUITE( BufferTests )
{
    TEST( BufferCreation )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        CHECK( not video_system::get().context_present() );
        bool initialization_error_thrown__no_context_present = false;
        try {
            vertex_buffer test_bffr;
        } catch (initialization_error e) {
            initialization_error_thrown__no_context_present = true;
        }
        
        CHECK( initialization_error_thrown__no_context_present );
        
        context test_cntx ( test_wndw );
        CHECK( video_system::get().context_present() );
        
        vertex_buffer test_bffr;
        
        CHECK_EQUAL( test_bffr.size(), 0 );

    }
    
    TEST( BufferSpecification )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        
        vertex_buffer test_bffr1( vertex_buffer::settings()
                            .blocks( 4 )      );
        CHECK_EQUAL( test_bffr1.size(), 4 );
        
    }
    
    TEST( BufferLoading )
    {
        bool logic_error_thrown__aligned_without_uploading = false;
        bool logic_error_thrown__aligned_without_formatting = false;
        
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw,
                            context::settings() );
        vertex_buffer test_bffr( vertex_buffer::settings()
                          .blocks( 4 )      );
        
        try {
            test_bffr.align();
        } catch (std::logic_error e) {
            logic_error_thrown__aligned_without_uploading = true;
        }
        
        CHECK( logic_error_thrown__aligned_without_uploading );
        
        test_bffr.upload_data();
        
        try {
            test_bffr.align();
        } catch (std::logic_error e) {
            logic_error_thrown__aligned_without_formatting = true;
        }
        
        CHECK( logic_error_thrown__aligned_without_formatting );
        
    }
}

SUITE( ProgramTests )
{
    TEST( ProgramCreationDefaults )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        program test_prgm;
        CHECK_EQUAL( 0, test_prgm.vertex_path().compare( "" ) );
        CHECK_EQUAL( 0, test_prgm.fragment_path().compare( "" ) );
        CHECK_EQUAL( 0, test_prgm.tesselation_path().compare( "" ) );
        CHECK_EQUAL( 0, test_prgm.geometry_path().compare( "" ) );
    }
    
    TEST( ProgramCreationHandles )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        program test_prgm( program::settings()
                           .vertex_path( "vertex" )
                           .fragment_path( "fragment" )
                           .tesselation_path( "tesselation" )
                           .geometry_path( "geometry" ) );
        
        CHECK_EQUAL( 0, test_prgm.vertex_path().compare( "vertex" ) );
        CHECK_EQUAL( 0, test_prgm.fragment_path().compare( "fragment" ) );
        CHECK_EQUAL( 0, test_prgm.tesselation_path().compare( "tesselation" ) );
        CHECK_EQUAL( 0, test_prgm.geometry_path().compare( "geometry" ) );

    }
    
    TEST( ShaderCompilation )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        
        program test_prgm ( program::settings()
                           .vertex_path( "./shader/testVert.glsl" )
                           .fragment_path( "./shader/testFrag.glsl" ) );
        test_prgm.compile();
     
    }
    
}

SUITE( IntegratedTests )
{
    TEST( SimpleRendering ) {
        
        window test_wndw ( window::settings()
                           .has_3D()
                           .dimensions( 512, 512 ) );
        context test_cntx ( test_wndw,
                            context::settings()
                            .depth_bits(24)
                            .double_buffered());
        program test_prgm ( program::settings()
                           .vertex_path("./shader/testVert_colored.glsl")
                           .fragment_path("./shader/testFrag_colored.glsl") );
        test_prgm.compile();
        
        vertex_buffer test_bffr( vertex_buffer::settings()
                          .blocks( 5 )      );
        
        test_bffr.block_format( block_spec()
                                .attribute( type<vec2>() )
                                .attribute( type<vec3>() ) );
        
        std::vector< vec2 > position;
        position.push_back( vec2( 0.5f ));
        position.push_back( vec2( 0.5f, -0.5f ));
        position.push_back( vec2( -0.5f ));
        position.push_back( vec2( -0.5f, 0.5f ));
        position.push_back( vec2( 0.0f ));

        std::vector< vec3 > color;
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 1.0f ) );
        color.push_back( vec3( 0.5f, 0.75f, 0.25f ) );
        
        test_bffr.load_attribute( 0, position );
        test_bffr.load_attribute( 1, color );
        
        test_bffr.upload_data();
        test_bffr.align();
        
        test_prgm.link();
        test_prgm.use();
        
        GLuint elements[] = { 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4 };
        gl::DrawElements( gl::TRIANGLES, 12, gl::UNSIGNED_INT, elements );
        
        test_wndw.swap();
        
        std::cout << "Do you see a multicolored rectangle? [y,n]. ";
        
        std::string input;
        std::cin >> input;
        
        CHECK_EQUAL( 0, input.compare("y") );
    }
}

int main( int argc, char* argv[] )
{
    video_system::get().initialize( video_system::settings().ver(3,3) );
    return UnitTest::RunAllTests();
}