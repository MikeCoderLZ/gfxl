#include <iostream>
#include <stdexcept>
#include <vector>

#include "videoManager.hpp"

unsigned int delay = 1000;

using namespace gfx;

int main( int argc, char* argv[] )
{
    using namespace std;

	cout << "VideoManager tests." << endl;

	VideoManager testManager;

	cout << "Empty VideoManager:\n" << testManager << endl;

	Window testWindow1 = testManager.create_window();
	Window testWindow2 = testManager.create_window( WindowSettings()
													.title( "Second Window!" )
													.x_pos( 256 )
													.use_opengl());
	Window testWindow3 = testManager.create_window( WindowSettings()
														.title( "Third Window..." )
														.x_pos( 768 )
														.y_pos( 64 )
														.use_opengl());

	cout << "Attempt illegal Program creation without an OpenGL Context:\n";

	try {
	    Program testProgram1 = testManager.create_program();
	} catch ( std::logic_error e ) {
	    cout << e.what() << endl;
	}

	cout << "Attempt illegal Context creation on non-OpenGL Window:\n";

	try {
	Context testContext1 = testManager.create_context( testWindow1 );
	} catch ( std::logic_error e ) {
		cout << e.what() << endl;
	}
	Context testContext2 = testManager.create_context( testWindow2,
													   ContextSettings()
			  	  	  	  	  	  	  	  	  	  	   .major_version(3)
			  	  	  	  	  	  	  	  	  	  	   .minor_version(3)
			  	  	  	  	  	  	  	  	  	  	   .depth_size(24)
			  	  	  	  	  	  	  	  	  	  	   .double_buffered() );
	testManager.attach_context( testWindow3, testContext2 );

	cout << "Create Program creation with an OpenGL context ready:\n";

	Program testProgram2 = testManager.create_program( ProgramSettings()
	                                                   .uses_vert( "./shader/testVert.glsl" )
	                                                   .uses_frag( "./shader/testFrag.glsl" ) );

	cout << "Compile Program; there is no source so it should error:\n";

	try {
	    testProgram2.compile();
	} catch ( compilation_error e ) {
	    cout << e.what() << endl;
	}

	cout << testProgram2 << endl;

	cout << "Create a Buffer." << endl;

	Buffer testBuffer1 = testManager.create_buffer( BufferSettings().blocks(4) );
	cout << "Created.  Now catch the exception when we try to align the data without having loaded it first." << endl;

	try {
	    testBuffer1.align_vertices();
	} catch (std::logic_error e) {
	    cout << e.what() << endl;
	}

	testBuffer1.load_data();

	cout << "Now it is loaded, but we will still throw an exception because the formatting has not been specified." << endl;

	try {
        testBuffer1.align_vertices();
    } catch (std::logic_error e) {
        cout << e.what() << endl;
    }

	testBuffer1.block_format( BlockSpec()
	                           .attribute( type<fvec2>() )
	                           .attribute( type<fvec3>() ) );
	cout << testBuffer1 << endl;

	if( gl::GetError() != gl::NO_ERROR_ ) {
	    cout << "GL error detected." << endl;
	}

	vector< fvec2 > position;
	position.push_back( fvec2( 0.5f ));
	position.push_back( fvec2( 0.5f, -0.5f ));
	position.push_back( fvec2( -0.5f ));
	position.push_back( fvec2( -0.5f, 0.5f ));

	vector< fvec3 > color;
	color.push_back( fvec3( 1.0f, 0.0f, 0.0f ) );
	color.push_back( fvec3( 1.0f, 1.0f, 0.0f ) );
	color.push_back( fvec3( 0.0f, 1.0f, 0.0f ) );
	color.push_back( fvec3( 0.0f, 1.0f, 1.0f ) );

	cout << "Now will fill in the first attribute's data." << endl;

	try {
	    testBuffer1.fill_attribute( 0, position );
	} catch (std::logic_error e) {
	    cout << "Exception!" << endl;
	    cout << e.what() << endl;
	}

	cout << "Now the second." << endl;
	try {
	    testBuffer1.fill_attribute( 1, color );
    } catch (std::logic_error e) {
        cout << "Exception!" << endl;
        cout << e.what() << endl;
    }
    cout << "Now we need to load the buffer data again because it has changed." << endl;
    testBuffer1.load_data();
    cout << testBuffer1 << endl;

    cout << "And now we can align the verticies." << endl;
    try {
        testBuffer1.align_vertices();
    } catch (std::logic_error e) {
        cout << "Exception!" << endl;
        cout << e.what() << endl;
    }

	cout << testBuffer1 << endl;

	cout << "Now we can link and use the program." << endl;

	testProgram2.link();
	testProgram2.use();

	cout << "Now we set the element buffer." << endl;

	GLuint elements[] = { 0, 1, 2, 0, 2, 3 };

	SDL_Delay( delay );

	cout << "Attempt illegal call of swap() on non-OpenGL Window:\n";

	try {
		testWindow1.swap();
	} catch (std::logic_error& e) {
		cout << e.what() << endl;
	}

	cout << "Clearing the first context to red and calling swap() on second window should do nothing interesting." << endl;
	testManager.activate_context( testContext2 );
	testContext2.clear_color( 1.0, 0.0, 0.0 );
	testWindow2.swap();
	SDL_Delay(delay);

	cout << "Calling swap() on the third window should reveal a red." << endl;
	testWindow3.swap();
	gl::DrawElements( gl::TRIANGLES, 6, gl::UNSIGNED_INT, elements );
	SDL_Delay(delay);
	cout << "Calling swap() on the third window should reveal a square." << endl;
	testWindow3.swap();
	SDL_Delay(delay*4);
	cout << "And now should reveal yellow." << endl;
	testManager.activate_context( testContext2 );
	testContext2.clear_color( 1.0, 1.0, 0.0 );
	testWindow3.swap();
	SDL_Delay(delay);

	cout << "Now we create a second context with the third window then make it current to the second and the second context current to the third, and try swap() on the second window then the third window." << endl;

	Context testContext3 = testManager.create_context( testWindow3,
															   ContextSettings()
					  	  	  	  	  	  	  	  	  	  	   .major_version(3)
					  	  	  	  	  	  	  	  	  	  	   .minor_version(3)
					  	  	  	  	  	  	  	  	  	  	   .depth_size(24)
					  	  	  	  	  	  	  	  	  	  	   .double_buffered() );
	testManager.attach_context( testWindow3, testContext2 );
	testManager.attach_context( testWindow2, testContext3 );

	cout << "Swap second to green..." << endl;
	testManager.activate_context( testContext3 );
	testContext3.clear_color( 0.0, 1.0, 0.0 );
	testWindow2.swap();
	SDL_Delay(delay);
	cout << "swap third to cyan." << endl;
	testManager.activate_context( testContext2 );
	testContext2.clear_color( 0.0, 1.0, 1.0 );
	testWindow3.swap();
	SDL_Delay(delay);

	cout << "Now with 3 windows:\n" << testManager << endl;

	cout << "First window:\n" << testWindow1 << endl;
	cout << "Second window:\n" << testWindow2 << endl;
	cout << "Third window:\n" << testWindow3 << endl;

	cout << "Done." << endl;
	return 0;
}
