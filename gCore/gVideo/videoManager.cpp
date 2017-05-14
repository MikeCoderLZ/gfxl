#include <stdexcept>
#include <fstream>
#include "gl_core_3_3.hpp"
#include "videoManager.hpp"
#include "SDL.h"

namespace gfx {

void Window::swap()
{
	if ( this->uses_opengl() ) {
		/* This makes our buffer swap synchronized with the monitor's vertical refresh */
		// I don't like this here.  Needs to be somewhere else more central.
		SDL_GL_SetSwapInterval(1);
		SDL_GL_SwapWindow( system_window );
	} else {
		std::string msg = "Window::swap() called on window '";
		msg += title;
		msg += "', which does not support OpenGL.";
		throw std::logic_error( msg );
	}
}

std::ostream& operator <<( std::ostream& out, Window const& rhs)
{
	out << rhs.title;
	/**out << "Window: " << rhs.settings.title << "\n";
	out << "\t< ";
	if ( rhs.settings.is_x_centered ) {
		out << "center";
	} else {
		out << rhs.settings.x_position;
	}
	out << ", ";
	if ( rhs.settings.is_y_centered ) {
		out << "center";
	} else {
		out << rhs.settings.y_position;
	}
	out << " >\n";

	out << "\t< " << rhs.settings.x_size << ", " << rhs.settings.y_size << " >";

	if ( rhs.settings.is_maximized ) {
		out << "\n\tcreate maximized";
	} else if ( rhs.settings.is_minimized ) {
		out << "\n\tcreate minimized";
	} else if ( rhs.settings.is_fullscreen ) {
		out << "\n\tcreate fullscreen";
	}
	if ( rhs.settings.is_resizable ) {
		out << "\n\tresizable";
	} else {
		out << "\n\tnot resizable";
	}
	if ( rhs.settings.no_border ) {
		out << "\n\tborderless";
	} else {
		out << "\n\tbordered";
	}
	if ( rhs.settings.uses_opengl ) {
		out << "\n\tuses OpenGL";
	}
	if ( rhs.settings.is_shown ) {
		out << "\n\tshown";
	} else {
		out << "\n\tnot shown";
	}
	if ( rhs.settings.input_is_grabbed ) {
		out << "\n\tgrabs input";
	} else {
		out << "\n\tdoes not grab input";
	}*/

	return out;
}

void Context::clear_color(float red, float green, float blue, float alpha )
{
	if ( not this->is_active() ) {
		throw std::logic_error( "Render operation 'run_clear_test()' called on Context that is not active." );
	}

	gl::ClearColor( red, green, blue, alpha );
	gl::Clear( gl::COLOR_BUFFER_BIT );
}

void    Program::compile( GLuint stage_ID, std::string const& stage_path )
{
    std::fstream shader_in( stage_path.c_str(),
                            std::ios_base::in );
    size_t buffer_size = 128;
    char* buffer = new char[buffer_size];
    std::string shader_file;

    while( shader_in.good() ) {
        // This looks ugly, I know.  Translation:
        // "read a number of bytes equal to the size of the read
        // buffer minus one then assign the character after the end
        // of that read to a null terminating character."
        buffer[ shader_in.read( buffer, buffer_size - 1 ).gcount() ] = '\0';
        shader_file += buffer;
    }

    std::cout << shader_file << std::endl;

    const char* stage_file_ptr = shader_file.c_str();
    gl::ShaderSource( stage_ID, 1, &stage_file_ptr, 0 );
    gl::CompileShader( stage_ID );

    GLint status = 0;
    gl::GetShaderiv( stage_ID, gl::COMPILE_STATUS, &status );

    if ( status == gl::FALSE_ ) {
        std::string msg = "Compilation of ";
        GLint type;
        gl::GetShaderiv( stage_ID, gl::SHADER_TYPE, &type );
        switch ( type ) {
        case gl::VERTEX_SHADER :
            msg += "vertex";
            break;
        case gl::FRAGMENT_SHADER :
            msg += "fragment";
            break;
        case gl::GEOMETRY_SHADER :
            msg += "geometry";
            break;
        default :
            msg += "unknown or unsupported type of";
        }
        msg += " shader failed:\n";
        GLint log_length;
        gl::GetShaderiv(stage_ID, gl::INFO_LOG_LENGTH, &log_length );
        char* info_log = new char[log_length];
        GLint returned_length;
        gl::GetShaderInfoLog( stage_ID, log_length, &returned_length, info_log );
        msg += info_log;
        delete[] info_log;

        throw compilation_error( msg );
    }
}

void    Program::compile()
{
    compile( this->vert_ID, vert_path );
    gl::AttachShader( prog_ID, vert_ID );
    compile( this->frag_ID, frag_path );
    gl::AttachShader( prog_ID, frag_ID );
    /** Compile geometry shader only if present */
    if ( this->geom_ID != 0 ) {
        compile( this->geom_ID, geom_path );
        gl::AttachShader( prog_ID, geom_ID );
    }
}

void    Program::link()
{
    /**gl::AttachShader( prog_ID, vert_ID );
    gl::AttachShader( prog_ID, frag_ID );
    if ( geom_ID != 0 ) {
        gl::AttachShader( prog_ID, geom_ID );
    }*/

    gl::LinkProgram( prog_ID );

    GLint status = 0;
    gl::GetProgramiv( prog_ID, gl::LINK_STATUS, &status );
    if ( status == gl::FALSE_ ) {
        std::cout << "Link failed." << std::endl;
        std::string msg = "Linking of program failed.\n";
        GLint log_length;
        gl::GetProgramiv(prog_ID, gl::INFO_LOG_LENGTH, &log_length );
        char* info_log = new char[log_length];
        GLint returned_length;
        gl::GetProgramInfoLog( prog_ID, log_length, &returned_length, info_log );
        msg += info_log;
        delete[] info_log;
        throw compilation_error( msg );
    }
}

void Program::use()
{
    gl::UseProgram( prog_ID );
}

std::ostream& operator <<( std::ostream& out, Program const& rhs )
{
    out << "Program:\n";
    out << "\tversion: " << rhs.maj_ver << "." << rhs.min_ver << "\n";
    out << "\tvertex shader ID: " << rhs.vert_ID << "\n";
    out << "\tvertex path: " << rhs.vert_path << "\n";
    out << "\tfragment shader ID: " << rhs.frag_ID << "\n";
    out << "\tfragment path: " << rhs.frag_path << "\n";
    out << "\tgeometry shader ID: " << rhs.geom_ID << "\n";
    out << "\tgeometry path: " << rhs.geom_path << "\n";
    // out << "\ttessallation shader ID: " << rhs.tess_ID << "\n";
    return out;
}

BlockSpec::~BlockSpec()
{
    attrib_vector::iterator i;
    for( i = attributes->begin(); i != attributes->end(); ++i )
        { delete *i; }
    delete attributes;
}

void Buffer::block_format( BlockSpec const& spec )
{
    attrib_vector::iterator a;
    GLsizeiptr new_stride = 0;
    for( a = spec.attributes->begin(); a != spec.attributes->end(); ++a ) {
        info* attrib_ptr = (*a)->copy();
        new_stride += attrib_ptr->mapped_size();
        this->attributes->push_back( attrib_ptr );
    }
    verts_specified = true;
    // since the format has changed, we need to flag the buffer as "dirty"
    data_loaded = false;
    stride = new_stride;
    if ( data != 0 ) {
        delete[] data;
    }
    data = new unsigned char[ n_blocks * stride ];
}

void    Buffer::blocks( GLsizeiptr const blocks )
{
    unsigned char* new_data = new unsigned char[ blocks * stride ];
    GLsizeiptr i;
    for ( i = n_blocks; i < n_blocks; ++i )
        { new_data[i] = data[i]; }
    delete[] data;
    data = new_data;
    this->n_blocks = blocks;
    // The amount of data has changed and the buffer has been extended
    // so it is dirty again
    data_loaded = false;
}

void    Buffer::add_blocks( GLsizeiptr const more_blocks )
{
    unsigned char* new_data =
            new unsigned char[ (n_blocks + more_blocks) * stride ];
    GLsizeiptr i;
    for ( i = n_blocks; i < n_blocks; ++i )
        { new_data[i] = data[i]; }
    delete[] data;
    data = new_data;
    this->n_blocks += more_blocks;
    // The amount of data has changed and the buffer has been extended
    // so it is dirty again
    data_loaded = false;
}

GLsizeiptr Buffer::attribute_offset( GLuint index ) const
{
    if( index == 0 ) { return 0; }

    GLsizeiptr offset = 0;
    GLuint attribute = 0;
    for( attribute = 0; attribute < index; ++attribute )
        { offset += (*attributes)[attribute]->mapped_size(); }
    return offset;
}

Buffer::~Buffer()
{
    gl::DeleteBuffers( 1, &buff_ID );
    attrib_vector::iterator i;
    std::cout << "Mark 1" << std::endl;
    for( i = attributes->begin(); i != attributes->end(); ++i )
        { delete *i; }
    delete attributes;
    delete[] data;
    std::cout << "Mark 2" << std::endl;
}

VideoManager::VideoManager()
{
	this->windows = new window_vector();
	this->contexts = new context_vector();
	this->programs = new program_vector();
	this->buffers = new buffer_vector();
	active_context = 0;

	if ( not SDL_WasInit( SDL_INIT_VIDEO ) ) {
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
			std::string msg ("Cannot initialize SDL Video subsystem:\n");
			msg += SDL_GetError();
			throw std::runtime_error( msg );
		}
	}
}
VideoManager::~VideoManager()
{
    /* There is a serious dangling pointer problem; if
     * an object the Manager has constructed goes out of
     * scope then when VideoManager either tries to provide
     * that object to someone else or somehow deletes itself
     * before the program finishes then it will try to delete
     * empty memory, and that will be messy.  Constructed
     * objects need to report to the Manager that they are
     * dying. */
	window_vector::iterator i;
	for( i = windows->begin(); i != windows->end(); ++i)
	    { delete *i; }
	delete windows;

	context_vector::iterator j;
	for( j = contexts->begin(); j != contexts->end(); ++j)
	    { delete *j; }
	delete contexts;

	program_vector::iterator k;
	for( k = programs->begin(); k != programs->end(); ++k)
	    { delete *k; }
	delete programs;

    std::cout << "Deleting Buffers; num buffers: " << buffers->size() << std::endl;
    
    buffer_vector::iterator u;
    for( u = buffers->begin(); u != buffers->end(); ++u)
        { std::cout << "deleting buffer" << std::endl;
            delete *u; }
    delete buffers;
}

Window& VideoManager::create_window( WindowSettings const& settings )
{

	int SDL_flags = 0;

	if ( settings.is_minimized ) {
		SDL_flags |= SDL_WINDOW_MINIMIZED;
	} else if ( settings.is_maximized ) {
		SDL_flags |= SDL_WINDOW_MAXIMIZED;
	} else if ( settings.is_fullscreen ) {
		SDL_flags |= SDL_WINDOW_FULLSCREEN;
	}

	if ( settings.is_resizable ) {
		SDL_flags |= SDL_WINDOW_RESIZABLE;
	}

	if ( settings.uses_opengl ) {
		SDL_flags |= SDL_WINDOW_OPENGL;
	}

	if ( settings.is_shown ) {
		SDL_flags |= SDL_WINDOW_SHOWN;
	}

	if ( settings.no_border ) {
		SDL_flags |= SDL_WINDOW_BORDERLESS;
	}

	if ( settings.input_is_grabbed ) {
		SDL_flags |= SDL_WINDOW_INPUT_GRABBED;
	}

	int x_argument = settings.x_position;

	if ( settings.is_x_centered ) {
		x_argument = SDL_WINDOWPOS_CENTERED;
	}

	int y_argument = settings.y_position;

	if ( settings.is_y_centered ) {
		y_argument = SDL_WINDOWPOS_CENTERED;
	}

	SDL_Window* newSystemWindow = SDL_CreateWindow( settings.window_title.c_str(),
													x_argument,
											        y_argument,
											        settings.x_size,
											        settings.y_size,
											        SDL_flags );
	if ( !newSystemWindow ) {
		std::string msg( "Unable to create new system window.\n" );
		msg += SDL_GetError();
		throw std::runtime_error( msg );
	}


	Window* newWindow = new Window( settings.window_title, this, newSystemWindow );
	windows->push_back( newWindow );
	return *newWindow;
}

Context& VideoManager::create_context( Window const& window,
									   ContextSettings const& settings )
{
	if ( not window.uses_opengl() ) {
		std::string msg = "The creation of a Context current in Window '";
		msg += window.title;
		msg += "', was attempted, but this window does not support OpenGL.";
		throw std::logic_error( msg );
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, settings.maj_ver );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, settings.min_ver );

	int doubleBuffered = (settings.is_double_buffered ? 1 : 0 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, doubleBuffered );

	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, settings.depth_bits );

	SDL_GLContext newSystemContext = SDL_GL_CreateContext( window.system_window );

	Context* newContext = new Context( this, &window, newSystemContext );

	active_context = newContext;

	contexts->push_back( newContext );
	return *newContext;

}

void VideoManager::attach_context( Window const& window,
								   Context& context)
{
	if ( (not owned( window )) or (not owned( context )) ) {
		std::string msg = "Illegal attachment of Context to Window '";
		msg += window.title;
		msg += "': ";
		if ( not owned( window ) ) {
			msg += "Window not owned by manager. ";
		}
		if ( not owned( context ) ) {
			msg += "Context not owned by manager. ";
		}
		if ( not window.uses_opengl() ) {
		    msg += "Window does not support OpenGL.";
		}
		throw std::logic_error( msg );
	}

	context.target_window = &window;
	SDL_GL_MakeCurrent( window.system_window, context.system_context );
	active_context = &context;
}

void VideoManager::activate_context( Context& context )
{
	if ( (not owned( *context.target_window )) or (not owned( context )) ) {
		std::string msg = "Illegal activation of Context on Window '";
		msg += context.target_window->title;
		msg += "': ";
		if ( not owned( *context.target_window ) ) {
			msg += "Window not owned by manager. ";
		}
		if ( not owned( context ) ) {
			msg += "Context not owned by manager.";
		}
		throw std::logic_error( msg );
	}

	SDL_GL_MakeCurrent( context.target_window->system_window, context.system_context );
	active_context = &context;
}

Context& VideoManager::get_active_context() const
{
	return *active_context;
}

Program& VideoManager::create_program( ProgramSettings const& settings )
{
    /**
     * This code assumes that this VideoManager is the sole purveyor
     * in the program; no attempt is made to find out if anyone else
     * has created an OpenGL context. It is irrelevant anyway because
     * only this VideoManager can use the Program, so we aren't
     * making an incorrect assumption. */
    if ( contexts->size() == 0 ) {
        std::string msg = "No OpenGL context had been created at time of";
        msg += " shading program creation request.";
        throw std::logic_error( msg );
    } /** Add check for adequate version number of a context;
       * OpenGL version should probably be pushed into VideoManager
       * so the whole Manager only uses one version.
       * */

    Program* new_program = new Program( this );

    new_program->maj_ver = settings.maj_ver;
    new_program->min_ver = settings.min_ver;

    if ( settings.has_vert_shader ) {
        new_program->vert_ID = gl::CreateShader( gl::VERTEX_SHADER );
        new_program->vert_path = settings.vert_path;
    }
    if ( settings.has_frag_shader ) {
            new_program->frag_ID = gl::CreateShader( gl::FRAGMENT_SHADER );
            new_program->frag_path = settings.frag_path;
    }
    if ( settings.has_geom_shader ) {
            new_program->geom_ID = gl::CreateShader( gl::GEOMETRY_SHADER );
            new_program->geom_path = settings.geom_path;
    }
    /** if ( settings.has_tess_shader ) {
                new_program->tess_ID = gl::CreateShader( gl::TESSALLATION_SHADER_ARB );
        }*/

    new_program->prog_ID = gl::CreateProgram();

    this->programs->push_back( new_program );

    return *new_program;

}

Buffer& VideoManager::create_buffer( BufferSettings const& settings )
{
    std::cout << "Created Buffer; num buffers: " << buffers->size() << std::endl;
    GLuint new_buff_ID;
    gl::GenBuffers( 1, &new_buff_ID );
    GLuint new_vao_ID;
    gl::GenVertexArrays( 1, &new_vao_ID );

    Buffer* new_buffer = new Buffer( this, settings.n_blocks, new_vao_ID, new_buff_ID, settings.usage, settings.intended_target );

    buffers->push_back( new_buffer );

    return *new_buffer;
}

std::ostream& operator <<( std::ostream& out, VideoManager const& rhs )
{
	out << "VideoManager:\n" << "\tnumber of windows: " << rhs.windows->size();
	return out;
}

}
