#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "video.hpp"
#include "../gMath/datatype.hpp"
#include "../../UnitTest++_src/UnitTest++.h"
#include "gl_core_3_3.hpp"

using namespace gfx;

video_manager test_mngr ( video_manager::settings()
                          .maj_ver( 3 )
                          .min_ver( 3 )            );

SUITE( GLSLShadingTests )
{    
    TEST( CIELabProgram )
    {
        window test_wndw = test_mngr.new_window( window::settings()
                                                   .has_3D()        );
        context test_cntx = test_mngr.new_context( test_wndw );
        test_mngr.attach_context( test_wndw, test_cntx );
        program test_prgm = test_mngr.new_program( program::settings()
                                                    .use_vert( "./shader/testVert_LAB.glsl" )
                                                    .use_frag( "./shader/testFrag_LAB.glsl" ) );
        test_prgm.compile();
        
        buffer test_buff = test_mngr.new_buffer( buffer::settings().blocks(4) );
        test_buff.block_format( block_spec()
                                .attribute( type<vec2>() )
                                .attribute( type<vec3>() ) );
        std::vector< vec2 > position;
        position.push_back( vec2( 0.5f ));
        position.push_back( vec2( 0.5f, -0.5f ));
        position.push_back( vec2( -0.5f ));
        position.push_back( vec2( -0.5f, 0.5f ));
        
        std::vector< vec3 > color;
        color.push_back( vec3( 1.0f, 1.0f, 1.0f ) );
        color.push_back( vec3( 1.0f, 1.0f, 1.0f ) );
        color.push_back( vec3( 0.01f, 0.01f, 0.01f ) );
        color.push_back( vec3( 0.01f, 0.01f, 0.01f ) );
        
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
    return UnitTest::RunAllTests();
}