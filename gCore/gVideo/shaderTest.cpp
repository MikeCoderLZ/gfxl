#include "./shader.hpp"
#include "./videoManager.hpp"
#include <iostream>

int main( int argc, char** argv )
{
    using namespace gfx;
    using std::cout;
    using std::endl;

    VideoManager testManager;

    Window testWindow1 = testManager.create_window( WindowSettings()
                                                    .title( "Test Window" )
                                                    .x_pos( 256 )
                                                    .use_opengl());

    Context testContext1 = testManager.create_context( testWindow1,
                                                           ContextSettings()
                                                           .major_version(3)
                                                           .minor_version(3)
                                                           .depth_size(24)
                                                           .double_buffered() );
    testManager.attach_context( testWindow1, testContext1 );
    testManager.activate_context( testContext1 );

    Shader testShader1("../asset/testVert.gshd",
                       "../asset/testFrag.gshd" );

    cout << testShader1 << endl;

    return 0;
}
