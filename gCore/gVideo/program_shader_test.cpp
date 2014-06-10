#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "video.hpp"
#include "../gMath/datatype.hpp"
#include "../../UnitTest++_src/UnitTest++.h"
#include "gl_core_3_3.hpp"

using namespace gfx;

SUITE( ProgramTests )
{
    TEST( ProgramContextPrerequisite )
    {
        window test_wndw = video_manager::get().new_window( window::settings()
                                                   .has_3D()        );
        // No OpenGL context has been created;
        // the program will refuse to be created
        std::string excepted = "Exception not caught.";
        try {
            program test_prgm1 = video_manager::get().new_program();
        } catch ( std::logic_error& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception caught.", excepted );
        
        context test_cntx = video_manager::get().new_context( test_wndw );
        CHECK( 2u <= test_cntx.major_version() );
        CHECK( 0u <= test_cntx.minor_version() );
        
        program test_prgm2 = video_manager::get().new_program();
    }
    
    TEST( ProgramSourcePrerequisite )
    {
        window test_wndw = video_manager::get().new_window( window::settings()
                                                   .has_3D()        );
        context test_cntx = video_manager::get().new_context( test_wndw );
        CHECK( 2u <= test_cntx.major_version() );
        CHECK( 0u <= test_cntx.minor_version() );
        
        program test_prgm = video_manager::get().new_program();
        
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
        window test_wndw = video_manager::get().new_window( window::settings()
                                                   .has_3D()        );
        context test_cntx = video_manager::get().new_context( test_wndw );
        program test_prgm = video_manager::get().new_program( program::settings()
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
        window test_wndw = video_manager::get().new_window( window::settings()
                                                   .has_3D()        );
        context test_cntx = video_manager::get().new_context( test_wndw );
        program test_prgm = video_manager::get().new_program( program::settings()
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
        window test_wndw = video_manager::get().new_window( window::settings()
                                                   .has_3D()        );
        std::string excepted = "Exception not caught.";
        try {
            buffer test_buff1 = video_manager::get().new_buffer( buffer::settings().blocks(4) );
        } catch ( std::logic_error& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception caught.", excepted );
        
        context test_cntx = video_manager::get().new_context( test_wndw );
        
        excepted = "Exception not caught.";
        try {
            buffer test_buff2 = video_manager::get().new_buffer( buffer::settings().blocks(4) );
        } catch ( std::logic_error& e ) {
            excepted = "Exception caught.";
        }
        CHECK_EQUAL( "Exception not caught.", excepted );        
    }
    
    TEST( BufferAlignment )
    {
        window test_wndw = video_manager::get().new_window( window::settings()
                                                   .has_3D()        );
        context test_cntx = video_manager::get().new_context( test_wndw );
        buffer test_buff = video_manager::get().new_buffer( buffer::settings().blocks(4) );
        
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
        window test_wndw = video_manager::get().new_window( window::settings()
                                                   .has_3D()        );
        context test_cntx = video_manager::get().new_context( test_wndw );
        buffer test_buff = video_manager::get().new_buffer( buffer::settings().blocks(4) );        
        
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
        window test_wndw = video_manager::get().new_window( window::settings()
                                                   .has_3D()        );
        context test_cntx = video_manager::get().new_context( test_wndw );
        video_manager::get().attach_context( test_wndw, test_cntx );
        program test_prgm = video_manager::get().new_program( program::settings()
                                                    .use_vert( "./shader/testVert.glsl" )
                                                    .use_frag( "./shader/testFrag.glsl" ) );
        test_prgm.compile();
        
        buffer test_buff = video_manager::get().new_buffer( buffer::settings().blocks(4) );
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
    
    TEST( MultipleBufferProgramInteraction )
    {
        window test_wndw = video_manager::get().new_window( window::settings()
                                                   .has_3D()        );
        context test_cntx = video_manager::get().new_context( test_wndw );
        video_manager::get().attach_context( test_wndw, test_cntx );
        program test_prgm = video_manager::get().new_program( program::settings()
                                                    .use_vert( "./shader/testVert_colored.glsl" )
                                                    .use_frag( "./shader/testFrag_colored.glsl" ) );
        test_prgm.compile();
        
        buffer test_buff = video_manager::get().new_buffer( buffer::settings().blocks(4) );
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
        window test_wndw = video_manager::get().new_window( window::settings()
                                                   .has_3D()        );
        context test_cntx = video_manager::get().new_context( test_wndw );
        video_manager::get().attach_context( test_wndw, test_cntx );
        program test_prgm = video_manager::get().new_program( program::settings()
                                                    .use_vert( "./shader/testVert_LAB.glsl" )
                                                    .use_frag( "./shader/testFrag_LAB.glsl" ) );
        test_prgm.compile();
        
        buffer test_buff = video_manager::get().new_buffer( buffer::settings().blocks(4) );
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
        color.push_back( vec3( 0.5f, 0.5f, 0.5f ) );
        
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
    video_manager::get().initialize( video_manager::settings()
                                     .maj_ver( 3 )
                                     .min_ver( 3 )            );

    return UnitTest::RunAllTests();
}