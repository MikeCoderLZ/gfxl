#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "../gVideo/video.hpp"
#include "../gMath/datatype.hpp"
#include "texture.hpp"
#include "../../UnitTest++_src/UnitTest++.h"
#include "../gVideo/gl_core_3_3.hpp"
#include "program.hpp"
#include "buffer.hpp"

using namespace gfx;

SUITE( GLSLShadingTests )
{
    TEST( Texture2DProgramInteraction )
    {
        window test_wndw ( window::settings()
                           .has_3D()
                           .width( 256 )
                           .height( 256 ) );
        context test_cntx ( test_wndw );
        video_system::get().attach_context( test_wndw, test_cntx );
        program correction_prgm ( program::settings()
                            .use_vert( "./shader/testVert_2Dtextured.glsl" )
                            .use_frag( "./shader/testNormalRepair_Frag.glsl" ) );
        correction_prgm.compile();
        correction_prgm.uniform( "smilie" );
        
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
        position.push_back( vec2( 1.0f ));
        position.push_back( vec2( 1.0f, -1.0f ));
        position.push_back( vec2( -1.0f ));
        position.push_back( vec2( -1.0f, 1.0f ));
        
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
                               .file( "./tex/caves/cavemossshader01_n.png" )
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
        
        std::cout << "A Normal Map will appear, unfiltered.\nConfirm [y/n]: ";
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        
        gl::DrawElements( gl::TRIANGLES,
                          6,
                          gl::UNSIGNED_INT,
                          elements );
        test_wndw.swap();
        
        std::cin >> input;        
        CHECK_EQUAL( "y", input );
        
        std::cout << "A Normal Map will appear, now filtered.\nConfirm [y/n]: ";
        
        correction_prgm.link();
        correction_prgm.use();
        
        correction_prgm.load_uniform( "smilie", 0 );
        
        test_cntx.clear_color( 1.0f, 1.0f, 0.0f );
        
        gl::DrawElements( gl::TRIANGLES,
                          6,
                          gl::UNSIGNED_INT,
                          elements );
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