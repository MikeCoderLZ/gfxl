#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "video.hpp"
#include "../gMath/datatype.hpp"
#include "../gScene/texture.hpp"
#include "../../UnitTest++_src/UnitTest++.h"
#include "gl_core_3_3.hpp"
#include "program.hpp"
#include "buffer.hpp"
#include "../gScene/camera.hpp"

using namespace gfx;

SUITE( ProgramTests )
{
    TEST( ProgramContextPrerequisite )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        // No OpenGL context has been created;
        // the program will refuse to be created
        std::string excepted = "Exception not caught.";
        try {
            program test_prgm1;
        } catch ( std::logic_error& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception caught.", excepted );
        
        context test_cntx ( test_wndw );
        CHECK( 2u <= test_cntx.major_version() );
        CHECK( 0u <= test_cntx.minor_version() );
        
        program test_prgm2;
    }
    
    TEST( ProgramSourcePrerequisite )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        context test_cntx ( test_wndw );
        CHECK( 2u <= test_cntx.major_version() );
        CHECK( 0u <= test_cntx.minor_version() );
        
        program test_prgm;
        
        std::string excepted = "Exception not caught.";
        try {
            test_prgm.compile();
        } catch ( compilation_error& e ) {
            excepted = "Exception caught.";
        }
        
        CHECK_EQUAL( "Exception caught.", excepted );
    }
    
    TEST( ProgramVertexCompilationError )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        context test_cntx ( test_wndw );
        program test_prgm ( program::settings()
                            .use_vert( "./shader/testVert_syntax_error.glsl" )
                            .use_frag( "./shader/testFrag.glsl" ) );
        std::string e_header = "Exception not caught";
        try {
            test_prgm.compile();
        } catch ( compilation_error& e ) {
            e_header = std::string( e.what() ).substr( 0, 21 );
        }
        CHECK_EQUAL( "Compilation of vertex", e_header );
    }
    
    TEST( ProgramFragmentCompilationError )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        context test_cntx ( test_wndw );
        program test_prgm ( program::settings()
                            .use_vert( "./shader/testVert.glsl" )
                            .use_frag( "./shader/testFrag_syntax_error.glsl" ) );
        std::string e_header = "Exception not caught";
        try {
            test_prgm.compile();
        } catch ( compilation_error& e ) {
            e_header = std::string( e.what() ).substr( 0, 23 );
        }
        CHECK_EQUAL( "Compilation of fragment", e_header );
    }    
}

SUITE( BufferTests )
{
    TEST( BufferCreation )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        std::string excepted = "Exception not caught.";
        try {
            buffer test_buff1 ( buffer::settings().blocks(4) );
        } catch ( std::logic_error& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception caught.", excepted );
        
        context test_cntx ( test_wndw );
        
        excepted = "Exception not caught.";
        try {
            buffer test_buff2 ( buffer::settings().blocks(4) );
        } catch ( std::logic_error& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception not caught.", excepted );        
    }
    
    TEST( BufferAlignment )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        context test_cntx ( test_wndw );
        buffer test_buff ( buffer::settings().blocks(4) );
        
        std::string excepted = "Exception not caught.";
        try {
            test_buff.align_vertices();
        } catch ( binding_error& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception caught.", excepted );
        
        test_buff.load_data();
        
        excepted = "Exception not caught.";
        try {
            test_buff.align_vertices();
        } catch ( unformatted_error& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception caught.", excepted );
        
        test_buff.block_format( block_spec()
                                .attribute( type<vec2>() )
                                .attribute( type<vec3>() ) );
        test_buff.load_data();
        
        excepted = "Exception not caught.";
        try {
            test_buff.align_vertices();
        } catch ( std::exception& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception not caught.", excepted );
    }
    
    TEST( BufferFill )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        context test_cntx ( test_wndw );
        buffer test_buff ( buffer::settings().blocks(4) );        
        
        std::vector< vec2 > position;
        position.push_back( vec2( 0.5f ));
        position.push_back( vec2( 0.5f, -0.5f ));
        position.push_back( vec2( -0.5f ));
        position.push_back( vec2( -0.5f, 0.5f ));
        position.push_back( vec2( 10.5f, 11.0f ));
        
        std::vector< vec3 > color;
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 1.0f ) );
        
        std::string excepted = "Exception not caught.";
        try {
            test_buff.fill_attribute( 1, color );
        } catch ( std::logic_error& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception caught.", excepted );
        
        test_buff.block_format( block_spec()
                                .attribute( type<vec2>() )
                                .attribute( type<vec3>() ) );
        test_buff.load_data();
        
        excepted = "Exception not caught.";
        try {
            test_buff.fill_attribute( 0, color );
        } catch ( std::invalid_argument& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception caught.", excepted );
        
        excepted = "Exception not caught.";
        try {
            test_buff.fill_attribute( 0, position );
        } catch ( std::out_of_range& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception caught.", excepted );
        
        excepted = "Exception not caught.";
        try {
            test_buff.fill_attribute( 1, color );
        } catch ( std::exception& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception not caught.", excepted );
    }
}

SUITE( GLSLShadingTests )
{
    TEST( BufferProgramInteraction )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        context test_cntx ( test_wndw );
        video_system::get().attach_context( test_wndw, test_cntx );
        program test_prgm ( program::settings()
                            .use_vert( "./shader/testVert.glsl" )
                            .use_frag( "./shader/testFrag.glsl" ) );
        test_prgm.compile();
        
        buffer test_buff ( buffer::settings().blocks(4) );
        test_buff.block_format( block_spec()
                                .attribute( type<vec2>() ) );
        std::vector< vec2 > position;
        position.push_back( vec2( 0.5f ));
        position.push_back( vec2( 0.5f, -0.5f ));
        position.push_back( vec2( -0.5f ));
        position.push_back( vec2( -0.5f, 0.5f ));
        
        test_buff.fill_attribute( 0, position );
        
        test_buff.load_data();
        test_buff.align_vertices();
        
        test_prgm.link();
        test_prgm.use();
        
        GLuint elements[] = { 0, 1, 2, 0, 2, 3 };
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        test_wndw.swap();
        
        std::cout << "Interactive test; press any key to continue. ";
        
        std::string input;
        std::cin >> input;
        
        std::cout << "A simple magenta square will appear on a yellow background.\nConfirm [y/n]: ";
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        
        gl::DrawElements( gl::TRIANGLES,
                          6,
                          gl::UNSIGNED_INT,
                          elements );
        test_wndw.swap();
        
        
        
        std::cin >> input;        
        CHECK_EQUAL( "y", input );
    }
    
    TEST( CameraProgramInteraction )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        context test_cntx ( test_wndw );
        video_system::get().attach_context( test_wndw, test_cntx );
        program test_prgm ( program::settings()
                            .use_vert( "./shader/testVertCam.glsl" )
                            .use_frag( "./shader/testFragCam.glsl" ) );
        
        test_prgm.compile();
        test_prgm.uniform( "view" );
        
        buffer test_buff ( buffer::settings().blocks(8) );
        test_buff.block_format( block_spec()
                                .attribute( type<vec3>() )
                                .attribute( type<vec3>() ) );
        std::vector< vec3 > position;
        position.push_back( vec3( 0.5f,  0.5f,  0.5f) );
        position.push_back( vec3( 0.5f, -0.5f,  0.5f) );
        position.push_back( vec3(-0.5f, -0.5f,  0.5f) );
        position.push_back( vec3(-0.5f,  0.5f,  0.5f) );
        position.push_back( vec3( 0.5f,  0.5f, -0.5f) );
        position.push_back( vec3( 0.5f, -0.5f, -0.5f) );
        position.push_back( vec3(-0.5f, -0.5f, -0.5f) );
        position.push_back( vec3(-0.5f,  0.5f, -0.5f) );
        test_buff.fill_attribute( 0, position );
        
        std::vector< vec3 > color;
        color.push_back( vec3(1.0f, 1.0f, 1.0f) );
        color.push_back( vec3(1.0f, 0.0f, 0.0f) );
        color.push_back( vec3(1.0f, 1.0f, 0.0f) );
        color.push_back( vec3(0.0f, 1.0f, 0.0f) );
        color.push_back( vec3(0.0f, 0.0f, 1.0f) );
        color.push_back( vec3(1.0f, 0.0f, 1.0f) );
        color.push_back( vec3(0.0f, 0.0f, 0.0f) );
        color.push_back( vec3(0.0f, 1.0f, 1.0f) );
        test_buff.fill_attribute( 1, color );
        
        proj_cam test_cam ( proj_cam::settings()
                            .position( vec3(1.0f, -1.0f, 1.0f) )
                            .look_at( vec3(0.0f, 0.0f, 0.0f) )
                            .upward( vec3(0.0f, 0.0f, 1.0f) )   );
        
        test_buff.load_data();
        test_buff.align_vertices();
        
        test_prgm.link();
        test_prgm.use();
        test_prgm.load_uniform( "view", test_cam.view_matrix() );
        video_system::get().check_acceleration_error( "View matrix uniform" );
        
        GLuint elements[] = { 2, 1, 0,
                              3, 2, 0,
                              5, 4, 0,
                              1, 5, 0,
                              6, 5, 1,
                              2, 6, 1,
                              7, 6, 2,
                              3, 7, 2,
                              4, 7, 3,
                              0, 4, 3,
                              6, 5, 4,
                              7, 6, 4 };
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        test_wndw.swap();
        
        std::cout << "Interactive test; press any key to continue. ";
        
        std::string input;
        std::cin >> input;
        
        std::cout << "A rainbow square will appear on a yellow background in persepctive.\nConfirm [y/n]: ";
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        std::cout << test_cam.view_matrix() << std::endl;
        
        gl::Enable( gl::DEPTH_TEST );
        
        gl::DrawElements( gl::TRIANGLES,
                          36,
                          gl::UNSIGNED_INT,
                          elements );
        test_wndw.swap();
        
        
        
        std::cin >> input;        
        CHECK_EQUAL( "y", input );
    }
    
//     TEST( Texture1DProgramInteraction )
//     {
//         window test_wndw ( window::settings()
//                            .has_3D()        );
//         context test_cntx ( test_wndw );
//         video_system::get().attach_context( test_wndw, test_cntx );
//         program test_prgm ( program::settings()
//                             .use_vert( "./shader/testVert_1Dtextured.glsl" )
//                             .use_frag( "./shader/testFrag_1Dtextured.glsl" ) );
//         test_prgm.uniform( "line" );
//         test_prgm.compile();
//         
//         buffer test_buff ( buffer::settings().blocks(4) );
//         test_buff.block_format( block_spec()
//                                 .attribute( type<vec2>() )
//                                 .attribute( type<float32>() ) );
//         std::vector< vec2 > position;
//         position.push_back( vec2( 0.5f ));
//         position.push_back( vec2( 0.5f, -0.5f ));
//         position.push_back( vec2( -0.5f ));
//         position.push_back( vec2( -0.5f, 0.5f ));
//         
//         std::vector< float32 > uv;
//         uv.push_back( float32( 1.0f ) );
//         uv.push_back( float32( 1.0f ) );
//         uv.push_back( float32( 0.0f ) );
//         uv.push_back( float32( 0.0f ) );
//         
//         test_buff.fill_attribute( 0, position );
//         test_buff.fill_attribute( 1, uv );
//         
//         test_buff.load_data();
//         test_buff.align_vertices();
//         
//         texture_1D test_txtr ( texture_1D::settings()
//                                .file( "./tex/test_1D.png" )
//                                .unsigned_norm_3( eight_bit, b, g, r ) );
//         test_txtr.decode_file();
//         test_txtr.load_data();
//         
//         test_prgm.link();
//         test_prgm.use();
//         test_prgm.load_uniform( "line", 0 );
//         
//         GLuint elements[] = { 0, 1, 2, 0, 2, 3 };
//         
//         test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
//         test_wndw.swap();
//         
//         std::cout << "Interactive test; press any key to continue. ";
//         
//         std::string input;
//         std::cin >> input;
//         
//         std::cout << "A white rectangle with a red edge will appear on a yellow background.\nConfirm [y/n]: ";
//         
//         test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
//         
//         gl::DrawElements( gl::TRIANGLES,
//                           6,
//                           gl::UNSIGNED_INT,
//                           elements );
//         test_wndw.swap();
//         
//         
//         
//         std::cin >> input;        
//         CHECK_EQUAL( "y", input );
//     }
/*    
    TEST( Texture2DProgramInteraction )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        context test_cntx ( test_wndw );
        video_system::get().attach_context( test_wndw, test_cntx );
        program test_prgm ( program::settings()
                            .use_vert( "./shader/testVert_2Dtextured.glsl" )
                            .use_frag( "./shader/testFrag_2Dtextured.glsl" ) );
        test_prgm.compile();
        test_prgm.uniform( "smilie" );
        
        buffer test_buff ( buffer::settings().blocks(4) );
        test_buff.block_format( block_spec()
                                .attribute( type<vec2>() )
                                .attribute( type<vec2>() ) );
        std::vector< vec2 > position;
        position.push_back( vec2( 0.5f ));
        position.push_back( vec2( 0.5f, -0.5f ));
        position.push_back( vec2( -0.5f ));
        position.push_back( vec2( -0.5f, 0.5f ));
        
        std::vector< vec2 > uv;
        uv.push_back( vec2( 1.0f ) );
        uv.push_back( vec2( 1.0f, 0.0f ) );
        uv.push_back( vec2( 0.0f ) );
        uv.push_back( vec2( 0.0f, 1.0f ) );
        
        test_buff.fill_attribute( 0, position );
        test_buff.fill_attribute( 1, uv );
        
        test_buff.load_data();
        test_buff.align_vertices();
        
        texture_2D test_txtr ( texture_2D::settings()
                               .file( "./tex/test_2D.png" )
                               .unsigned_norm_3( eight_bit, b, g, r )
                               .sample_magnification( linear ) );
        test_txtr.decode_file();
        test_txtr.load_data();
        
        test_prgm.link();
        test_prgm.use();
        
        test_prgm.load_uniform( "smilie", 0 );
        
        GLuint elements[] = { 0, 1, 2, 0, 2, 3 };
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        test_wndw.swap();
        
        std::cout << "Interactive test; press any key to continue. ";
        
        std::string input;
        std::cin >> input;
        
        std::cout << "A white rectangle with a black and red smilie will appear on a yellow background.\nConfirm [y/n]: ";
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        
        gl::DrawElements( gl::TRIANGLES,
                          6,
                          gl::UNSIGNED_INT,
                          elements );
        test_wndw.swap();
        
        
        
        std::cin >> input;        
        CHECK_EQUAL( "y", input );
    }*/
    
    TEST( MultipleBufferProgramInteraction )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        context test_cntx ( test_wndw );
        video_system::get().attach_context( test_wndw, test_cntx );
        program test_prgm ( program::settings()
                            .use_vert( "./shader/testVert_colored.glsl" )
                            .use_frag( "./shader/testFrag_colored.glsl" ) );
        test_prgm.compile();
        
        buffer test_buff ( buffer::settings().blocks(4) );
        test_buff.block_format( block_spec()
                                .attribute( type<vec2>() )
                                .attribute( type<vec3>() ) );
        std::vector< vec2 > position;
        position.push_back( vec2( 0.5f ));
        position.push_back( vec2( 0.5f, -0.5f ));
        position.push_back( vec2( -0.5f ));
        position.push_back( vec2( -0.5f, 0.5f ));
        
        std::vector< vec3 > color;
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 1.0f ) );
        
        test_buff.fill_attribute( 0, position );
        test_buff.fill_attribute( 1, color );
        
        test_buff.load_data();
        test_buff.align_vertices();
        
        test_prgm.link();
        test_prgm.use();
        
        GLuint elements[] = { 0u, 1u, 2u, 0u, 2u, 3u };
        
        context::ui_indexer idx ( elements, elements + 6 );
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        test_wndw.swap();
        
        std::cout << "Interactive test; press any key to continue. ";
        
        std::string input;
        std::cin >> input;
        
        std::cout << "A rainbow square will appear on a yellow background.\nConfirm [y/n]: ";
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        
        test_cntx.draw_triangles( 2, idx );
        
        test_wndw.swap();
  
        std::cin >> input;        
        CHECK_EQUAL( "y", input );
    }
    
    TEST( CIELabProgram )
    {
        window test_wndw ( window::settings()
                           .has_3D()        );
        context test_cntx ( test_wndw );
        video_system::get().attach_context( test_wndw, test_cntx );
        program test_prgm ( program::settings()
                            .use_vert( "./shader/testVert_LAB.glsl" )
                            .use_frag( "./shader/testFrag_LAB.glsl" ) );
        test_prgm.compile();
        
        buffer test_buff ( buffer::settings().blocks(4) );
        test_buff.block_format( block_spec()
                                .attribute( type<vec2>() )
                                .attribute( type<vec3>() ) );
        std::vector< vec2 > position;
        position.push_back( vec2( 0.5f ));
        position.push_back( vec2( 0.5f, -0.5f ));
        position.push_back( vec2( -0.5f ));
        position.push_back( vec2( -0.5f, 0.5f ));
        
        std::vector< vec3 > color;
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.5f, 1.0f, 1.0f ) );
        
        test_buff.fill_attribute( 0, position );
        test_buff.fill_attribute( 1, color );
        
        test_buff.load_data();
        test_buff.align_vertices();
        
        test_prgm.link();
        test_prgm.use();
        
        GLuint elements[] = { 0u, 1u, 2u, 0u, 2u, 3u };
        
        context::ui_indexer idx ( elements, elements + 6 );
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        test_wndw.swap();
        
        std::cout << "Interactive test; press any key to continue. ";
        
        std::string input;
        std::cin >> input;
        
        std::cout << "A rainbow square will appear on a yellow background.\nConfirm [y/n]: ";
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        
        test_cntx.draw_triangles( 2, idx );
        
        test_wndw.swap();
        
        
        
        std::cin >> input;        
        CHECK_EQUAL( "y", input );
    }
}

int main( int argc, char* argv[] )
{
    video_system::get().initialize( video_system::settings()
                                     .maj_ver( 3 )
                                     .min_ver( 3 )            );

    return UnitTest::RunAllTests();
}