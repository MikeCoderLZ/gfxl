#include <iostream>
#include <stdexcept>
#include <vector>

#include "checkError.hpp"
#include "videoManager.hpp"

int main( int argc, char** argv ) {

    using namespace gfx;
    using namespace std;

    VideoManager testManager;

    Window testWindow = testManager.create_window( WindowSettings()
                                                       .title( "First Window" )
                                                       .x_pos( 256 )
                                                       .use_opengl() );
    Context testContext = testManager.create_context( testWindow,
                                                      ContextSettings()
                                                          .major_version(3)
                                                          .minor_version(3)
                                                          .depth_size(24)
                                                          .double_buffered() );
    testManager.attach_context( testWindow, testContext );
    //testManager.activate_context( testContext );

    GLuint framebuf_ID;
    gl::GenFramebuffers( 1, &framebuf_ID );
    gl::BindFramebuffer( gl::DRAW_FRAMEBUFFER, framebuf_ID);

    GLuint renderbuf_ID;
    gl::GenRenderbuffers( 1, &renderbuf_ID );
    gl::BindRenderbuffer( gl::RENDERBUFFER, renderbuf_ID );
    gl::RenderbufferStorage( gl::RENDERBUFFER, gl::RGBA8, 512, 512 );

    gl::FramebufferRenderbuffer( gl::DRAW_FRAMEBUFFER,
                                 gl::COLOR_ATTACHMENT0,
                                 gl::RENDERBUFFER,
                                 renderbuf_ID );

    GLenum fb_status = gl::CheckFramebufferStatus( gl::DRAW_FRAMEBUFFER );
    gl::BindFramebuffer( gl::DRAW_FRAMEBUFFER, 0 );

    if( fb_status == gl::FRAMEBUFFER_COMPLETE ) {
        cout << "Framebuffer is complete, thank god."  << endl;
    } else {
        cout << "Framebuffer is not complete, god dammit." << endl;
    }

    Program testProgram = testManager.create_program( ProgramSettings()
                                                          .uses_vert( "./shader/testVert.glsl" )
                                                          .uses_frag( "./shader/testFrag.glsl" ) );

    try {
        testProgram.compile();
    } catch (compilation_error e) {
        cout << e.what() << endl;
    }

    checkGLError( "compiled program" );

    //GLenum drawbuffers[] = { gl::BACK_LEFT };
    //gl::DrawBuffers( 1, drawbuffers );

    Buffer testBuffer = testManager.create_buffer( BufferSettings()
                                                   .blocks(3)
                                                   .static_draw()
                                                   .for_array());
    checkGLError( "vertex attribute buffer created" );

    testBuffer.block_format( BlockSpec().attribute( type<vec2>() ) );

    vector< vec2 > position;
    position.push_back( vec2( 1.0f ));
    position.push_back( vec2( 1.0f, -1.0f ));
    position.push_back( vec2( -1.0f ));
    //position.push_back( vec2( -0.5f, 0.5f ));

    testBuffer.fill_attribute( 0, position );

    testBuffer.load_data();
    checkGLError( "loaded vertex data" );
    testBuffer.align_vertices();

    checkGLError( "aligned vertex data" );

    //GLuint testElements[] = { 0, 1, 2 };
    Buffer testElementBuffer = testManager.create_buffer( BufferSettings()
                                                          .blocks(3)
                                                          .for_element_array() );

    testElementBuffer.block_format( BlockSpec()
                                    .attribute( type<uint32>() ) );

    vector< uint32 > indices;
    indices.push_back( 0 );
    indices.push_back( 1 );
    indices.push_back( 2 );

    testElementBuffer.fill_attribute( 0, indices );

    testElementBuffer.load_data();
    checkGLError( "loading element data" );
    //testElementBuffer.align_vertices();

    try {
        testProgram.link();
    } catch ( compilation_error e ) {
        cout << e.what() << endl;
    }

    GLint posLocation = gl::GetAttribLocation( testProgram.getProgID(), "pos" );

    cout << "Location of pos input: " << posLocation << endl;

    cout << testBuffer << endl;
    cout << testElementBuffer << endl;

    testManager.activate_context( testContext );

    gl::BindBuffer( gl::ARRAY_BUFFER, testBuffer.getBuffId() );
    gl::BindBuffer( gl::ELEMENT_ARRAY_BUFFER, testElementBuffer.getBuffId() );

    checkGLError( "bound buffers" );

    gl::Enable( gl::DEPTH_TEST );
    gl::DepthFunc( gl::ALWAYS );

    testProgram.use();
    testContext.clear_color( 0.0f, 1.0f, 1.0f );
    gl::ClearDepth( 1.0f );
    gl::Clear( gl::DEPTH_BUFFER_BIT );
    checkGLError( "cleared color to cyan and depth to 1" );
    testWindow.swap();
    SDL_Delay( 4000 );
    testContext.clear_color( 1.0f, 1.0f, 0.0f );
    gl::ClearDepth( 1.0f );
    gl::Clear( gl::DEPTH_BUFFER_BIT );
    checkGLError( "claered color to yellow and depth to 1" );
    gl::DrawElements( gl::TRIANGLES, 3, gl::UNSIGNED_INT , ( void* ) 0 );
    checkGLError( "drew triangles" );
    testWindow.swap();
    SDL_Delay( 4000 );
    
    return 0;

}
