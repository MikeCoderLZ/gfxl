#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "../gVideo/video.hpp"
#include "../gMath/datatype.hpp"
#include "../gMath/constant.hpp"
#include "../../UnitTest++_src/UnitTest++.h"

#include "buffer.hpp"
#include "program.hpp"
#include "light.hpp"
#include "camera.hpp"

using namespace gfx;

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
                           .vertex_path("./shader/scene_test_vert.glsl")
                           .fragment_path("./shader/scene_test_frag.glsl") );
        try {
            test_prgm.compile();
        } catch ( std::exception& e ) {
            std::cout << e.what() << std::endl;
        }
        
        std::cout<< "Mark1!" << std::endl;
        test_prgm.uniform( "obj_mat" );
        std::cout<< "Mark2!" << std::endl;
       
       
        test_prgm.uniform( "cam" );
         try {
        test_prgm.uniform( "light" );
        } catch ( std::exception& e ) {
                 std::cout << e.what() << std::endl;
        }
        
        buffer test_bffr( buffer::settings()
                          .blocks( 36 )      );
        
        test_bffr.block_format( block_spec()
                                .attribute( type<vec3>() )  // position
                                .attribute( type<vec3>() )  // normal
                                .attribute( type<vec3>() ) ); // color
        
        std::vector< vec3 > position;

        // Front
        position.push_back( vec3(  0.5f,  0.5f, -0.5f ));
        position.push_back( vec3( -0.5f,  0.5f, -0.5f ));
        position.push_back( vec3( -0.5f, -0.5f, -0.5f ));
        
        position.push_back( vec3(  0.5f,  0.5f, -0.5f ));
        position.push_back( vec3( -0.5f, -0.5f, -0.5f ));
        position.push_back( vec3(  0.5f, -0.5f, -0.5f ));
        
        // Right
        position.push_back( vec3(  0.5f,  0.5f,  0.5f ));
        position.push_back( vec3( -0.5f, -0.5f,  0.5f ));
        position.push_back( vec3(  0.5f, -0.5f, -0.5f ));
        
        position.push_back( vec3(  0.5f,  0.5f,  0.5f ));
        position.push_back( vec3(  0.5f, -0.5f, -0.5f ));
        position.push_back( vec3(  0.5f, -0.5f,  0.5f ));
        
        // Left
        position.push_back( vec3( -0.5f,  0.5f, -0.5f ));
        position.push_back( vec3( -0.5f,  0.5f,  0.5f ));
        position.push_back( vec3( -0.5f, -0.5f,  0.5f ));
        
        position.push_back( vec3( -0.5f,  0.5f, -0.5f ));
        position.push_back( vec3( -0.5f, -0.5f,  0.5f ));
        position.push_back( vec3( -0.5f, -0.5f, -0.5f ));
        
        // Back
        position.push_back( vec3( -0.5f,  0.5f,  0.5f ));
        position.push_back( vec3(  0.5f,  0.5f,  0.5f ));
        position.push_back( vec3(  0.5f, -0.5f,  0.5f ));
        
        position.push_back( vec3( -0.5f,  0.5f,  0.5f ));
        position.push_back( vec3(  0.5f, -0.5f,  0.5f ));
        position.push_back( vec3( -0.5f, -0.5f,  0.5f ));
        
        // Top
        position.push_back( vec3(  0.5f,  0.5f,  0.5f ));
        position.push_back( vec3( -0.5f,  0.5f,  0.5f ));
        position.push_back( vec3( -0.5f,  0.5f, -0.5f ));
        
        position.push_back( vec3(  0.5f,  0.5f,  0.5f ));
        position.push_back( vec3( -0.5f,  0.5f, -0.5f ));
        position.push_back( vec3(  0.5f,  0.5f, -0.5f ));
        
        // Bottom
        position.push_back( vec3( -0.5f, -0.5f,  0.5f ));
        position.push_back( vec3(  0.5f, -0.5f,  0.5f ));
        position.push_back( vec3(  0.5f, -0.5f, -0.5f ));
        
        position.push_back( vec3( -0.5f, -0.5f,  0.5f ));
        position.push_back( vec3(  0.5f, -0.5f, -0.5f ));
        position.push_back( vec3( -0.5f, -0.5f, -0.5f ));

        std::vector< vec3 > normal;
        // Front
        normal.push_back( vec3( 0.0f, 0.0f, -1.0f ) );
        normal.push_back( vec3( 0.0f, 0.0f, -1.0f ) );
        normal.push_back( vec3( 0.0f, 0.0f, -1.0f ) );
        
        normal.push_back( vec3( 0.0f, 0.0f, -1.0f ) );
        normal.push_back( vec3( 0.0f, 0.0f, -1.0f ) );
        normal.push_back( vec3( 0.0f, 0.0f, -1.0f ) );
        
        // Right
        normal.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        normal.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        normal.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
       
        normal.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        normal.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        normal.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        
        // Left
        normal.push_back( vec3( -1.0f, 0.0f, 0.0f ) );
        normal.push_back( vec3( -1.0f, 0.0f, 0.0f ) );
        normal.push_back( vec3( -1.0f, 0.0f, 0.0f ) );
       
        normal.push_back( vec3( -1.0f, 0.0f, 0.0f ) );
        normal.push_back( vec3( -1.0f, 0.0f, 0.0f ) );
        normal.push_back( vec3( -1.0f, 0.0f, 0.0f ) );
        
        // Back
        normal.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        normal.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        normal.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        
        normal.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        normal.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        normal.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        
        // Top
        normal.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        normal.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        normal.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        
        normal.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        normal.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        normal.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        
        // Bottom
        normal.push_back( vec3( 0.0f, -1.0f, 0.0f ) );
        normal.push_back( vec3( 0.0f, -1.0f, 0.0f ) );
        normal.push_back( vec3( 0.0f, -1.0f, 0.0f ) );
        
        normal.push_back( vec3( 0.0f, -1.0f, 0.0f ) );
        normal.push_back( vec3( 0.0f, -1.0f, 0.0f ) );
        normal.push_back( vec3( 0.0f, -1.0f, 0.0f ) );
        
        
        std::vector< vec3 > color;
        // Front
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        
        // Right
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        
        // Left
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        
        // Back
        color.push_back( vec3( 0.0f, 1.0f, 1.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 1.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 1.0f ) );
        
        color.push_back( vec3( 0.0f, 1.0f, 1.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 1.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 1.0f ) );
        
        // Top
        color.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        color.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        color.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        
        color.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        color.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        color.push_back( vec3( 0.0f, 0.0f, 1.0f ) );
        
        // Bottom
        color.push_back( vec3( 1.0f, 0.0f, 1.0f ) );
        color.push_back( vec3( 1.0f, 0.0f, 1.0f ) );
        color.push_back( vec3( 1.0f, 0.0f, 1.0f ) );
        
        color.push_back( vec3( 1.0f, 0.0f, 1.0f ) );
        color.push_back( vec3( 1.0f, 0.0f, 1.0f ) );
        color.push_back( vec3( 1.0f, 0.0f, 1.0f ) );
        
        mat4 test_obj_mtrx = mat4::rotation( vec3( 0.0f, 1.0f, 0.0f),
                                        d_angle::in_degs( 0.0f) );

        point_light test_lght ( point_light::settings()
                                .radiance( 0.8f )
                                .position( vec3( 1.0f, 1.0f, -1.0f ) )
                                .color( vec3( 1.0f, 1.0f, 1.0f ) )     );
        
        proj_cam test_cmra( proj_cam::settings()
                            .position( vec3( 0.0f, 0.0f, 5.0f ) )
                            .look_at( vec3() )
                            .upward( vec3( 0.0f, 1.0f, 0.0f ) )
                            .field_of_view( d_angle::in_degs( 135.0 ) )
                            .aspect_ratio( 1.0 )
                            .near_plane( 0.01 )
                            .far_plane( 100.0 )                         );

        try {
        test_bffr.load_attribute( 0, position );
        } catch (std::exception& e ) {
            std::cout << e.what() << std::endl;
        }
        test_bffr.load_attribute( 1, normal );
        
        
        test_bffr.load_attribute( 2, color );
        
        
        
        test_bffr.upload_data();
        
        test_bffr.align_vertices();
        
        try {
            test_prgm.link();
            
        } catch (compilation_error& e ) {
            std::cout<< e.what() << std::endl;
        }
        try {
        test_prgm.use();
        } catch (std::exception& e ) {
            std::cout << e.what() << std::endl;
        }
        try {
        test_prgm.load_uniform( "obj_mtrx", test_obj_mtrx );
        test_lght.upload_uniform( test_prgm, std::string( "light" ) );
        test_cmra.upload_uniform( test_prgm, std::string( "camera" ) );
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        GLuint elements[] = { 0, 1, 2, 3, 4, 5,
                              6, 7, 8, 9, 10, 11,
                              12, 13, 14, 15, 16, 17,
                              18, 19, 20, 21, 22, 23,
                              24, 25, 26, 27, 28, 29,
                              30, 31, 32, 33, 34, 35 };
               
        unsigned int frames = 0;
        while( frames < 150 ) {
            SDL_Delay( 33 );
            ++frames;
            gl::DrawElements( gl::TRIANGLES, 36, gl::UNSIGNED_INT, elements );
            test_wndw.swap();
            test_obj_mtrx = test_obj_mtrx
                            * mat4::rotation( vec3( 0.0f, 1.0f, 0.0f ),
                                              d_angle::in_degs( 360.0 / 30.0 ) );
            test_obj_mtrx.norm();
            test_prgm.load_uniform( std::string( "obj_mtrx" ), test_obj_mtrx );

        }
    }
}

int main( int argc, char* argv[] )
{
    video_system::get().initialize( video_system::settings().ver( 3, 3 ) );
    return UnitTest::RunAllTests();
}