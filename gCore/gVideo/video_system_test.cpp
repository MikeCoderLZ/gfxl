#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "../gMath/datatype.hpp"
#include "../../UnitTest++_src/UnitTest++.h"

#include "video.hpp"

using namespace gfx;

SUITE( WindowTests )
{
    TEST( WindowTitle )
    {
        window test_wndw1 ( window::settings()
                            .title("Fiddlesticks") );
        CHECK_EQUAL( "Fiddlesticks", test_wndw1.title() );
        test_wndw1.title( "Brittlebits" );
        CHECK_EQUAL( "Brittlebits", test_wndw1.title() );
    }
    
    TEST( WindowXPosition )
    {
        window test_wndw ( window::settings()
                           .x_pos( 256 )
                           .title("WindowXPosition") );
        CHECK_EQUAL( 256, test_wndw.x_pos() );
        test_wndw.x_pos( 128 );
        CHECK_EQUAL( 128, test_wndw.x_pos() );
    }
    
    TEST( WindowYPosition )
    {
        window test_wndw ( window::settings()
                           .y_pos( 256 )
                           .title("WindowYPosition") );
        CHECK_EQUAL( 256, test_wndw.y_pos() );
        test_wndw.y_pos( 128 );
        CHECK_EQUAL( 128, test_wndw.y_pos() );
    }
    
    TEST( WindowPosition )
    {
        window test_wndw ( window::settings()
                           .position( 256, 256 )
                           .title("WindowPosition") );
        CHECK_EQUAL( ivec2( 256, 256 ), test_wndw.position() );
        test_wndw.position( 128, 128 );
        CHECK_EQUAL( ivec2( 128, 128 ), test_wndw.position() );
        test_wndw.position( ivec2( 384, 384 ) );
        CHECK_EQUAL( ivec2( 384, 384 ), test_wndw.position() );
    }
    
    TEST( WindowXCentering )
    {
        window test_wndw ( window::settings()
                           .center_x()
                           .title("WindowXCentering") );
        CHECK( test_wndw.is_x_centered() );
    }
    
    TEST( WindowYCentering )
    {
        window test_wndw ( window::settings()
                           .center_y()
                           .title("WindowYCentering") );
        CHECK( test_wndw.is_y_centered() );
    }
    
    TEST( WindowWidth )
    {
        window test_wndw ( window::settings()
                           .width( 256 )
                           .title("WindowWidth") );
        CHECK_EQUAL( 256, test_wndw.width() );
        test_wndw.width( 512 );
        CHECK_EQUAL( 512, test_wndw.width() );
    }
    
    TEST( WindowHeight )
    {
        window test_wndw ( window::settings()
                           .height( 256 )
                           .title("WindowHeight") );
        CHECK_EQUAL( 256, test_wndw.height() );
        test_wndw.height( 512 );
        CHECK_EQUAL( 512, test_wndw.height() );
    }
    
    TEST( WindowDimensions )
    {
        window test_wndw ( window::settings()
                           .dimensions( 256, 256 )
                           .title("WindowDimension") );
        CHECK_EQUAL( ivec2( 256, 256 ), test_wndw.dimensions() );
        test_wndw.dimensions( 512, 512 );
        CHECK_EQUAL( ivec2( 512, 512 ), test_wndw.dimensions() );
        test_wndw.dimensions( ivec2( 128, 128 ) );
        CHECK_EQUAL( ivec2( 128, 128 ), test_wndw.dimensions() );
    }
    
    TEST( WindowCorners )
    {
        window test_wndw ( window::settings()
                           .corners( 128, 128,
                                     256, 256 )
                           .title("WindowDimension") );
        CHECK_EQUAL( ivec2( 128, 128 ), test_wndw.ul_corner() );
        CHECK_EQUAL( ivec2( 256, 256 ), test_wndw.lr_corner() );
        CHECK_EQUAL( ivec2( 128, 128 ), test_wndw.dimensions() );
        test_wndw.corners( 200, 200, 300, 300 );
        CHECK_EQUAL( ivec2( 200, 200 ), test_wndw.ul_corner() );
        CHECK_EQUAL( ivec2( 300, 300 ), test_wndw.lr_corner() );
        CHECK_EQUAL( ivec2( 100, 100 ), test_wndw.dimensions() );
        test_wndw.corners( ivec2( 100, 100 ),
                           ivec2( 400, 400 )  );
        CHECK_EQUAL( ivec2( 100, 100 ), test_wndw.ul_corner() );
        CHECK_EQUAL( ivec2( 400, 400 ), test_wndw.lr_corner() );
        CHECK_EQUAL( ivec2( 300, 300 ), test_wndw.dimensions() );
    }
    
    TEST( WindowMaximized )
    {
        window test_wndw ( window::settings()
                           .maximized()
                           .title("WindowMaximized") );
        CHECK( test_wndw.is_maximized() );
        test_wndw.minimize();
        test_wndw.maximize();
        CHECK( test_wndw.is_maximized() );
    }
    
//     TEST( WindowMinimized )
//     {
//         window test_wndw = video_system::get().new_window( window::settings()
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
        window test_wndw ( window::settings()
                           .resizable()
                           .title("WindowResizable") );
        CHECK( test_wndw.is_resizable() );
    }
    
    TEST( WindowOpenGL )
    {
        window test_wndw ( window::settings()
                           .has_3D()
                           .title("WindowOpenGL") );
        CHECK( test_wndw.has_3D() );
    }
    
    TEST( WindowVisibility )
    {
        window test_wndw ( window::settings()
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
        window test_wndw ( window::settings()
                           .has_border()
                           .title("WindowBorders1") );
        CHECK( test_wndw.has_border() );
        
        window test_wndw1 ( window::settings()
                            .no_border()
                            .title("WindowBorders2") );
        CHECK_EQUAL( false, test_wndw1.has_border() );
    }
    
//     TEST( WindowFocus )
//     {
//         window test_wndw = video_system::get().new_window( window::settings()
//                                                  .has_focus()
//                                                  .title("WindowFocus") );
//         CHECK( test_wndw.has_focus() );
//     }
    TEST( WindowDefaultCreation )
    {
        window test_wndw1;
        SDL_Rect bounds;
        SDL_GetDisplayBounds( 0, &bounds );
        CHECK_EQUAL( bounds.w / 2, test_wndw1.width() );
        CHECK_EQUAL( bounds.h / 2, test_wndw1.height() );
        CHECK_EQUAL( bounds.w / 2, test_wndw1.x_pos() );
        CHECK_EQUAL( bounds.h / 2, test_wndw1.y_pos() );
        CHECK_EQUAL( "untitled", test_wndw1.title() );
        CHECK( not test_wndw1.has_3D() );
        CHECK( test_wndw1.has_border() );
    }
}

SUITE( ContextTests )
{
    TEST( ContextCreation )
    {
        window test_wndw1;

        try {
            context fail_cntx ( test_wndw1 );
        } catch (std::logic_error& e ) {
            CHECK_EQUAL( "The creation of a context current in window 'untitled', was attempted, but this window does not support OpenGL.",
                         e.what() );
        }
        window test_wndw2 ( window::settings()
                            .has_3D()       );
        context test_cntx ( test_wndw2 );
        
        CHECK( 1u <= test_cntx.major_version() );
        CHECK( 4u <= test_cntx.minor_version() );
        CHECK( 16 <= test_cntx.depth_bits() );
        CHECK_EQUAL( true, test_cntx.double_buffered() );
    }
    
    TEST( ContextSwap )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        video_system::get().attach_context( test_wndw, test_cntx );
        
        std::cout << "Interactive test; press any key to continue. ";
        
        std::string input;
        std::cin >> input;
        
        std::cout << "First the window will appear yellow.\nConfirm [y/n]: ";
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        test_wndw.swap();
        
        std::cin >> input;        
        CHECK_EQUAL( "y", input );
        
        std::cout << "Now the window will appear magenta.\nConfirm [y/n]: ";
        
        test_cntx.clear_color( 1.0f, 0.0f, 1.0f );
        test_wndw.swap();
        
        std::cin >> input;
        CHECK_EQUAL( "y", input );
    }
}

SUITE( BufferTests )
{
    TEST( BufferCreation )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        
        buffer test_bffr( test_cntx );
        
        CHECK_EQUAL( *(test_bffr.get_target_context()), test_cntx );
        CHECK_EQUAL( test_bffr.get_n_blocks(), 0 );
        CHECK_EQUAL( test_bffr.get_stride(), 0 );
        CHECK_EQUAL( test_bffr.get_vao_ID(), 1 );
        CHECK_EQUAL( test_bffr.get_buff_ID(), 1 );
        CHECK_EQUAL( test_bffr.get_usage(), gl::DYNAMIC_DRAW );
        CHECK_EQUAL( test_bffr.get_intended_target(), gl::ARRAY_BUFFER );
        CHECK_EQUAL( test_bffr.get_data_loaded(), false );
        CHECK_EQUAL( test_bffr.get_verts_specified(), false );
    }
    
    TEST( BufferSpecification )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        
        buffer test_bffr1( test_cntx,
                           buffer::settings()
                            .blocks( 4 )
                            .static_draw()
                            .for_array()     );
        CHECK_EQUAL( test_bffr1.get_n_blocks(), 4 );
        CHECK_EQUAL( test_bffr1.get_usage(), gl::STATIC_DRAW );
        CHECK_EQUAL( test_bffr1.get_intended_target(), gl::ARRAY_BUFFER );
        
        buffer test_bffr2( test_cntx,
                           buffer::settings()
                            .static_read()
                            .for_copy_read()   );
        CHECK_EQUAL( test_bffr2.get_usage(), gl::STATIC_READ );
        CHECK_EQUAL( test_bffr2.get_intended_target(), gl::COPY_READ_BUFFER );
        
        buffer test_bffr3( test_cntx,
                           buffer::settings()
                            .static_copy()
                            .for_copy_write()   );
        CHECK_EQUAL( test_bffr3.get_usage(), gl::STATIC_COPY );
        CHECK_EQUAL( test_bffr3.get_intended_target(), gl::COPY_WRITE_BUFFER );
        
        buffer test_bffr4( test_cntx,
                           buffer::settings()
                            .dynamic_draw()
                            .for_element_array()   );
        CHECK_EQUAL( test_bffr4.get_usage(), gl::DYNAMIC_DRAW );
        CHECK_EQUAL( test_bffr4.get_intended_target(), gl::ELEMENT_ARRAY_BUFFER );
        
        buffer test_bffr5( test_cntx,
                           buffer::settings()
                            .dynamic_read()
                            .for_pixel_packing()   );
        CHECK_EQUAL( test_bffr5.get_usage(), gl::DYNAMIC_READ );
        CHECK_EQUAL( test_bffr5.get_intended_target(), gl::PIXEL_PACK_BUFFER );
        
        buffer test_bffr6( test_cntx,
                           buffer::settings()
                            .dynamic_copy()
                            .for_pixel_unpacking()   );
        CHECK_EQUAL( test_bffr6.get_usage(), gl::DYNAMIC_COPY );
        CHECK_EQUAL( test_bffr6.get_intended_target(), gl::PIXEL_UNPACK_BUFFER );
        
        buffer test_bffr7( test_cntx,
                           buffer::settings()
                            .stream_draw()
                            .for_texture()   );
        CHECK_EQUAL( test_bffr7.get_usage(), gl::STREAM_DRAW );
        CHECK_EQUAL( test_bffr7.get_intended_target(), gl::TEXTURE_BUFFER );
        
        buffer test_bffr8( test_cntx,
                           buffer::settings()
                            .stream_copy()
                            .for_transform_feedback()   );
        CHECK_EQUAL( test_bffr8.get_usage(), gl::STREAM_COPY );
        CHECK_EQUAL( test_bffr8.get_intended_target(), gl::TRANSFORM_FEEDBACK_BUFFER );
        
        buffer test_bffr9( test_cntx,
                           buffer::settings()
                            .for_uniform()   );
        CHECK_EQUAL( test_bffr9.get_usage(), gl::DYNAMIC_DRAW );
        CHECK_EQUAL( test_bffr9.get_intended_target(), gl::UNIFORM_BUFFER );
        
    }
    
    TEST( BufferLoading )
    {
        bool logic_error_thrown__aligned_without_uploading = false;
        bool logic_error_thrown__aligned_without_formatting = false;
        
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw,
                            context::settings() );
        
        buffer test_bffr( test_cntx,
                          buffer::settings()
                          .blocks( 4 )      );
        
        try {
            test_bffr.align_vertices();
        } catch (std::logic_error e) {
            logic_error_thrown__aligned_without_uploading = true;
        }
        
        CHECK( logic_error_thrown__aligned_without_uploading );
        
        test_bffr.upload_data();
        
        try {
            test_bffr.align_vertices();
        } catch (std::logic_error e) {
            logic_error_thrown__aligned_without_formatting = true;
        }
        
        CHECK( logic_error_thrown__aligned_without_formatting );
        
        test_bffr.block_format( block_spec()
                                .attribute( type<vec2>() )
                                .attribute( type<vec3>() ) );
        
        /* vector< vec2 > position;
        position.push_back( vec2( 0.5f ));
        position.push_back( vec2( 0.5f, -0.5f ));
        position.push_back( vec2( -0.5f ));
        position.push_back( vec2( -0.5f, 0.5f ));

        vector< vec3 > color;
        color.push_back( vec3( 1.0f, 0.0f, 0.0f ) );
        color.push_back( vec3( 1.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 0.0f ) );
        color.push_back( vec3( 0.0f, 1.0f, 1.0f ) );
        
        test_bffr1.load_attribute( 0, position );
        test_bffr1.load_attribute( 1, color );
        
        test_bffr.upload_data(); */
        
    }
}

SUITE( ShaderTests )
{
    TEST( ShaderCreationDefaults )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        
        shader test_shdr( test_cntx );
        
        CHECK_EQUAL( 0, test_shdr.vertex_path().compare( "" ) );
        CHECK_EQUAL( 0, test_shdr.fragment_path().compare( "" ) );
        CHECK_EQUAL( 0, test_shdr.tesselation_path().compare( "" ) );
        CHECK_EQUAL( 0, test_shdr.geometry_path().compare( "" ) );
        
    }
    
    TEST( ShaderCreationHandles )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        
        shader* test_shdr = new shader( test_cntx,
                                        shader::settings()
                                        .vertex_path( "vertex" )
                                        .fragment_path( "fragment" )
                                        .tesselation_path( "tesselation" )
                                        .geometry_path( "geometry" ) );
        
        CHECK_EQUAL( 0, test_shdr->vertex_path().compare( "vertex" ) );
        CHECK_EQUAL( 0, test_shdr->fragment_path().compare( "fragment" ) );
        CHECK_EQUAL( 0, test_shdr->tesselation_path().compare( "tesselation" ) );
        CHECK_EQUAL( 0, test_shdr->geometry_path().compare( "geometry" ) );
        
        delete test_shdr;

    }
    
    TEST( ShaderCompilation )
    {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        
        shader test_shdr ( test_cntx,
                            shader::settings()
                            .vertex_path( "./shader/testVert.glsl" )
                            .fragment_path( "./shader/testFrag.glsl" ) );
        test_shdr.compile();
        //bool compilation_success;
        
        
        
    }
    
}

SUITE( IntegratedTests )
{
    TEST( SimpleRendering ) {
        bool logic_error_thrown__aligned_without_uploading = false;
        bool logic_error_thrown__aligned_without_formatting = false;
        
        window test_wndw ( window::settings()
                           .has_3D() );
        context test_cntx ( test_wndw,
                            context::settings()
                            .depth_bits(24)
                            .double_buffered());
        shader test_shdr ( test_cntx,
                           shader::settings()
                           .vertex_path("./shader/testVert_colored.glsl")
                           .fragment_path("./shader/testFrag_colored.glsl") );
        test_shdr.compile();
        
        buffer test_bffr( test_cntx,
                          buffer::settings()
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
        test_bffr.align_vertices();
        
        test_shdr.link();
        test_shdr.use();
        
        GLuint elements[] = { 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4 };
        gl::DrawElements( gl::TRIANGLES, 12, gl::UNSIGNED_INT, elements );
        
        test_wndw.swap();
        
        std::cout << "Do you see a square? [y,n]. ";
        
        std::string input;
        std::cin >> input;
        
        CHECK_EQUAL( 0, input.compare("y") );
    }
}

/* SUITE( ShaderSystemTests )
{
    TEST( ShaderSystemInitialization ) {
        CHECK_EQUAL( 0, shader_system::get().shader_set_size() );
    }
    
    TEST( ShaderSystemBasicInsertion ) {
        window test_wndw ( window::settings()
                           .has_3D()          );
        context test_cntx ( test_wndw );
        CHECK_EQUAL( 0, shader_system::get().shader_set_size() );
        // The insertion happens in the background with magics.
        shader* test_shdr = new shader( test_cntx );
        CHECK_EQUAL( 1, shader_system::get().shader_set_size() );
        delete test_shdr;
    }
    
    
}*/
int main( int argc, char* argv[] )
{
    video_system::get().initialize( video_system::settings() );
    return UnitTest::RunAllTests();
}