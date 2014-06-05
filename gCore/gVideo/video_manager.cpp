#include <stdexcept>
#include <fstream>
#include <string>
#include "gl_core_3_3.hpp"
#include "video_manager.hpp"
#include "SDL.h"

namespace gfx {
    
    window::~window()
    {
        owner->del_window( *this );
    }
    void window::swap()
    {
        if ( this->has_3D() ) {
            /* This makes our buffer swap synchronized with the monitor's vertical refresh */
            // I don't like this here.  Needs to be somewhere else more central.
            SDL_GL_SetSwapInterval(1);
            SDL_GL_SwapWindow( sys_window );
        } else {
            std::string msg = "window::swap() called on window '";
            msg += title_str;
            msg += "', which does not support OpenGL.";
            throw std::logic_error( msg );
        }
    }
    
    std::string     window::title() const
    { return std::string( SDL_GetWindowTitle( sys_window ) ); }
    
    void    window::title( std::string const& ttl )
    { SDL_SetWindowTitle( sys_window, ttl.c_str() ); }
    
    int     window::x_pos() const
    {
        int ul_x;
        int ul_y;
        SDL_GetWindowPosition( sys_window, &ul_x, &ul_y );
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        return ul_x + dw / 2;
    }
    
    void     window::x_pos( int xp )
    {
        int ul_y = this->ul_corner()[1];
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, dw / -2 + xp, ul_y );
    }
    
    int     window::y_pos() const
    {
        int ul_x;
        int ul_y;
        SDL_GetWindowPosition( sys_window, &ul_x, &ul_y );
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        return ul_y + dh / 2;
    }
    
    void     window::y_pos( int yp )
    {
        int ul_x = this->ul_corner()[0];
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, ul_x, dh / -2 + yp );
    }
    
    ivec2   window::position() const
    {
        int ul_x;
        int ul_y;
        SDL_GetWindowPosition( sys_window, &ul_x, &ul_y );
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );

        return ivec2( ul_x + dw / 2, ul_y + dh / 2 );
    }
    
    void     window::position( int xp,
                               int yp )
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, dw / -2 + xp, dh / -2 + yp );
    }
    
    void     window::position( ivec2 const& pos )
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        
        SDL_SetWindowPosition( sys_window, dw / -2 + pos[0], dh / -2 + pos[1] );
    }
    
    bool    window::is_x_centered() const
    {
        SDL_Rect bounds;
        SDL_GetDisplayBounds( 0, &bounds );
        
        SDL_Rect wndw_bounds;
        SDL_GetDisplayBounds( SDL_GetWindowDisplayIndex( sys_window ), &wndw_bounds );

        return wndw_bounds.x + wndw_bounds.w / 2 == bounds.w / 2;
    }
    
    void    window::center_x()
    {
        int yp = this->y_pos();
        SDL_SetWindowPosition( sys_window, SDL_WINDOWPOS_CENTERED, yp );
    }
    
    bool    window::is_y_centered() const
    {
        SDL_Rect bounds;
        SDL_GetDisplayBounds( 0, &bounds );
        
        SDL_Rect wndw_bounds;
        SDL_GetDisplayBounds( SDL_GetWindowDisplayIndex( sys_window ), &wndw_bounds );

        return wndw_bounds.y + wndw_bounds.h / 2 == bounds.h / 2;
    }
    
    void    window::center_y()
    {
        int xp = this->x_pos();
        SDL_SetWindowPosition( sys_window, xp, SDL_WINDOWPOS_CENTERED );
    }

    int     window::width() const
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        return dw;
    }
    
    void     window::width( int dw )
    {
        int dh = this->height();
        SDL_SetWindowSize( sys_window, dw, dh );
    }
    
    int     window::height() const
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        return dh;
    }
    
    void     window::height( int dh )
    {
        int dw = this->width();
        SDL_SetWindowSize( sys_window, dw, dh );
    }
    
    ivec2   window::dimensions() const
    {
        int dw;
        int dh;
        SDL_GetWindowSize( sys_window, &dw, &dh );
        return ivec2( dw, dh );
    }
    
    void    window::dimensions( int dw,
                                int dh )
    {
        SDL_SetWindowSize( sys_window, dw, dh );
    }
    
    void    window::dimensions( ivec2 const& dim )
    {
        SDL_SetWindowSize( sys_window, dim[0], dim[1] );
    }
    
    ivec2   window::ul_corner() const
    {
        int ulx;
        int uly;
        SDL_GetWindowPosition( sys_window, &ulx, &uly );
        return ivec2( ulx, uly );
    }
    
//     void    window::ul_corner( int ulx,
//                                int uly )
//     {
//         ivec2 ulc = this->ul_corner();
//         int delta_x = ulc[0] - ulx;
//         int delta_y = ulc[1] - uly;
//         ivec2 dim = this->dimensions();
//         int dw = dim[0] + delta_x;
//         int dh = dim[1] + delta_y;
//         ivec2 pos = this->position();
//         int dx = delta_x / -2 + pos[0];
//         int dy = delta_y / -2 + pos[1];
//         SDL_SetWindowSize( sys_window, dw, dh );
//         SDL_SetWindowPosition( sys_window, dx, dy );
//     }
//     
//     void    window::ul_corner( ivec2 const& ulc )
//     {
//         ivec2 delta = this->ul_corner() - ulc;
//         ivec2 dim = this->dimensions() + delta;
//         ivec2 pos = delta / -2 + this->position();
//         SDL_SetWindowSize( sys_window, dim[0], dim[1] );
//         SDL_SetWindowPosition( sys_window, pos[0], pos[1] );
//     }
    
    ivec2   window::lr_corner() const
    { return this->ul_corner() + this->dimensions(); }
    
//     void    window::lr_corner( int lrx,
//                                int lry )
//     {
//         ivec2 lrc = this->ul_corner();
//         int delta_x = lrc[0] - lrx;
//         int delta_y = lrc[1] - lry;
//         ivec2 dim = this->dimensions();
//         int dw = dim[0] + delta_x;
//         int dh = dim[1] + delta_y;
//         ivec2 pos = this->position();
//         int dx = delta_x / 2 + pos[0];
//         int dy = delta_y / 2 + pos[1];
//         SDL_SetWindowSize( sys_window, dw, dh );
//         SDL_SetWindowPosition( sys_window, dx, dy );
//     }
//     
//     void    window::lr_corner( ivec2 const& lrc )
//     {
//         ivec2 delta = this->lr_corner() - lrc;
//         ivec2 dim = this->dimensions() + delta;
//         ivec2 pos = delta / 2 + this->position();
//         SDL_SetWindowSize( sys_window, dim[0], dim[1] );
//         SDL_SetWindowPosition( sys_window, pos[0], pos[1] );
//     }
    
    void    window::corners( int ulx,
                             int uly,
                             int lrx,
                             int lry )
    {
        ivec2 ulc ( ulx, uly );
        ivec2 lrc ( lrx, lry );
        ivec2 dim = lrc - ulc;
        SDL_SetWindowSize( sys_window, dim[0], dim[1] );
        SDL_SetWindowPosition( sys_window, ulc[0], ulc[1] );
    }
    
    void    window::corners( ivec2 const& ulc,
                             ivec2 const& lrc )
    {
        ivec2 dim = lrc - ulc;
        SDL_SetWindowSize( sys_window, dim[0], dim[1] );
        SDL_SetWindowPosition( sys_window, ulc[0], ulc[1] );
    }
    
    bool    window::is_maximized() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_MAXIMIZED ); }
    
    void    window::maximize()
    { SDL_MaximizeWindow( sys_window ); }
    
    bool    window::is_minimized() const
    {
        // This doesn't work.  Sigh.
        return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_MINIMIZED );
    }
    
    void    window::minimize()
    { SDL_MinimizeWindow( sys_window ); }
    
    bool    window::is_resizable() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_RESIZABLE ); }
    
    bool    window::has_3D() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_OPENGL ); }
    
    bool    window::is_visible() const
    { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_SHOWN ); }
    
    void    window::make_visible()
    { SDL_ShowWindow( sys_window ); }
    
    void    window::make_hidden()
    { SDL_HideWindow( sys_window ); }
    
    bool    window::has_border() const
    { return not bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_BORDERLESS ); }
    
//     bool    window::is_fullscreen() const
//     { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_FULLSCREEN ); }
//     
// //     void    window::make_fullscreen()
// //     { SDL_SetWindowFullscreen( sys_window, 0 ); }

//     bool    window::has_focus() const
//     { return bool( SDL_GetWindowFlags( sys_window ) & SDL_WINDOW_INPUT_FOCUS ); }
//     
//     std::ostream& operator <<( std::ostream& out, window const& rhs)
//     {
//         out << rhs.title_str;
//         return out;
//     }
    
    context::~context()
    {
        owner->del_context( *this );
    }
    
    void context::clear_color( float red, float green, float blue, float alpha )
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Render operation 'clear_color()' called on Context that is not active." );
        }

        gl::ClearColor( red, green, blue, alpha );
        gl::Clear( gl::COLOR_BUFFER_BIT );
    }
    
    unsigned int    context::major_version() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'major_version()' called on Context that is not active." );
        }
        int maj_ver;
        int ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, &maj_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'major_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return (unsigned int)  maj_ver;
    }
    
    unsigned int    context::minor_version() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'minor_version()' called on Context that is not active." );
        }
        int min_ver;
        int ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, &min_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'minor_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return (unsigned int) min_ver ;
    }
    
    uvec2    context::version() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'version()' called on Context that is not active." );
        }
        int maj_ver;
        int ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, &maj_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'major_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        
        int min_ver;
        ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, &min_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'minor_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return uvec2( (unsigned int) maj_ver, (unsigned int) min_ver );
    }
    
    unsigned int    context::depth_bits() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'depth_bits()' called on Context that is not active." );
        }
        int bits;
        int ret = SDL_GL_GetAttribute( SDL_GL_DEPTH_SIZE, &bits );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'depth_bits()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return (unsigned int) bits;
    }
    
    bool    context::double_buffered() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'double_buffered()' called on Context that is not active." );
        }
        int buffed;
        int ret = SDL_GL_GetAttribute( SDL_GL_DOUBLEBUFFER, &buffed );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'double_buffered()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return bool( buffed );
    }
    
    program::~program()
    {
        owner->del_program( *this );
        // I do not know if this code is needed.
//         GLint n_shdr;
//         if (     gl::IsProgram( prog_ID )
//              and ( gl::GetProgram( prog_ID, GL_ATTACHED_SHADERS, &n_shdr ), n_shdr > 0 ) )
//         {
//             if ( gl::IsShader( vert_ID ) ) {
//                 gl::DetachShader( prog_ID, vert_ID );
//             }
//             if ( gl::IsShader( frag_ID ) ) {
//                 gl::DetachShader( prog_ID, frag_ID );
//             }
//             if ( gl::IsShader( geom_ID ) ) {
//                 gl::DetachShader( prog_ID, geom_ID );
//             }
//             if ( gl::IsShader( tess_ID ) ) {
//                 gl::DetachShader( prog_ID, tess_ID );
//             }
//         }
        
//         gl::DeleteProgram( prog_ID );
//         gl::DeleteShader( vert_ID );
//         gl::DeleteShader( frag_ID );
//         gl::DeleteShader( geom_ID );
//         gl::DeleteShader( tess_ID );
    }
    
    void    program::compile()
    {
        if ( vert_path == "" ) {
            throw compilation_error( "Vertex shader source path uninitialized.");
        } else {
            compile( this->vert_ID, vert_path );
            gl::AttachShader( prog_ID, vert_ID );
        }
        if ( frag_path == "" ) {
            throw compilation_error( "Fragment shader source path uninitialized.");
        } else {
            compile( this->frag_ID, frag_path );
            gl::AttachShader( prog_ID, frag_ID );
        }
        /** Compile geometry shader only if present */
        if ( this->geom_ID != 0 ) {
            if ( geom_path == "" ) {
                throw compilation_error( "Geometry shader source path uninitialized.");
            } else {
                compile( this->geom_ID, geom_path );
                gl::AttachShader( prog_ID, geom_ID );
            }
        }
    }
    
    void    program::link()
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
    
    void program::use()
    { gl::UseProgram( prog_ID ); }
    
    std::ostream& operator <<( std::ostream& out, program const& rhs )
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
    
    program::program( video_manager* const owner,
                      size_t g_id ) :
                      managed( owner, g_id ),
                      vert_path ( "" ),
                      frag_path ( "" ),
                      geom_path ( "" ),
                      vert_ID ( 0 ),
                      frag_ID ( 0 ),
                      geom_ID ( 0 ),
                      tess_ID ( 0 ),
                      prog_ID ( 0 ),
                      maj_ver ( 2 ),
                      min_ver ( 0 )  {}
    
    void    program::compile( GLuint stage_ID, std::string const& stage_path )
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
            // The expression can't execute until the index to the array
            // is known, so that expression will always execute first.
            // Still terrifying.
            buffer[ shader_in.read( buffer, buffer_size - 1 ).gcount() ] = '\0';
            shader_file += buffer;
        }

        //std::cout << shader_file << std::endl;

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
    
    buffer::~buffer()
    {
        owner->del_buffer( *this );
        attrib_vector::iterator i;
        for ( i = attributes->begin(); i < attributes->end(); ++i ) {
            delete *i;
        }
        delete attributes;
    }
    
    void buffer::block_format( block_spec const& spec )
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
    
    void    buffer::blocks( GLsizeiptr const blocks )
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
    
    void    buffer::add_blocks( GLsizeiptr const more_blocks )
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
    
    GLsizeiptr buffer::attribute_offset( GLuint index ) const
    {
        if( index == 0 ) { return 0; }

        GLsizeiptr offset = 0;
        GLuint attribute = 0;
        for( attribute = 0; attribute < index; ++attribute )
            { offset += (*attributes)[attribute]->mapped_size(); }
        return offset;
    }
    
    
    void    buffer::align_vertices()
    {
        if ( not data_loaded ) {
            std::string msg = "Buffer data has not be uploaded to OpenGL; ";
            msg += "either the buffer is new or the data has changed since ";
            msg += "the last time it was loaded.";
            throw binding_error( msg );
        }

        if ( not verts_specified ) {
            std::string msg = "Blocks of buffer data not yet formated.";
            throw unformatted_error( msg );
        }

        //std::cout << "Buffer ID: " << buff_ID << std::endl;
        gl::BindBuffer( gl::ARRAY_BUFFER, buff_ID );
        checkGLError( "buffer bound to ARRAY_BUFFER" );
        gl::BindVertexArray( vao_ID );
        checkGLError( "vao bound for vertex alignment" );

        attrib_vector::iterator a;
        GLuint index = 0;
        for( a = attributes->begin();
            a != attributes->end();
            ++a ) {
            GLsizeiptr offset = attribute_offset( index );
            switch( (*a)->mapping() ) {
            case FLOAT :
                gl::VertexAttribPointer( index,
                                        (*a)->n_components(),
                                        (*a)->component_to_GL(),
                                        gl::FALSE_,
                                        stride,
                                        ( void* ) offset );
                checkGLError( "VertexAttribPointer called" );
//                 std::cout << "VertexAttribPointer called." << std::endl;
//                 std::cout << "\tindex: " << index << '\n';
//                 std::cout << "\tsize: " << (*a)->n_components() << '\n';
//                 std::cout << "\ttype: " << (*a)->component_to_GL() << '\n';
//                 std::cout << "\tstride: " << stride << '\n';
//                 std::cout << "\toffset: " << offset << std::endl;
                gl::EnableVertexAttribArray( index );
                checkGLError( "Enableed Vertex Attribute Array" );
                break;
            case INTEGER :
                gl::VertexAttribIPointer( index,
                                        (*a)->n_components(),
                                        (*a)->component_to_GL(),
                                        stride,
                                        ( void* ) offset );
                gl::EnableVertexAttribArray( index );
                break;
        /**  case DOUBLE :
                gl::VertexAttribLPointer( index,
                                        (*a)->n_components(),
                                        (*a)->component_to_GL(),
                                        stride,
                                        ( void*) offset );*/
            default :
                break;
            }
            ++index;
        }
    }

    std::ostream&   operator <<( std::ostream& out, buffer const& rhs )
    {   out << "Buffer:\n";
        out << "\tbuffer ID: " << rhs.buff_ID << '\n';
        out << "\tblocks in buffer: " << rhs.n_blocks << std::endl;
        out << "\tblock size: " << rhs.stride << std::endl;
        out << "\ttotal data bytes: " << rhs.n_blocks * rhs.stride << std::endl;
        out << "\tdata loaded: " << rhs.data_loaded << std::endl;
        out << "\tblocks formated: " << rhs.verts_specified << std::endl;

        if ( rhs.data != 0 ) {
            out << "[";
            GLsizeiptr i;
            for ( i = 0; i < rhs.n_blocks * rhs.stride; ++i ) {
                out << (unsigned int) rhs.data[i];
                if ( i % rhs.stride == rhs.stride - 1 ) {
                    if ( i + 1 == rhs.n_blocks * rhs.stride ) {
                        out << "]";
                    } else {
                        out << "]\n[";
                    }
                } else {
                    out << "|";
                }
            }
        }
        return out;
    }
    
    video_manager::video_manager( video_manager::settings const& set ) :
        windows( new window_map() ),
        nxt_w_id( 0 ),
        contexts( new context_map() ),
        nxt_c_id( 0 ),
        active_context( 0 ),
        programs( new program_map ),
        nxt_p_id( 0 ),
        buffers( new buffer_map ),
        nxt_b_id( 0 ),
        zombie( false )
    {
        if ( not SDL_WasInit( SDL_INIT_VIDEO ) ) {
            if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
                std::string msg ("Cannot initialize SDL Video subsystem:\n");
                msg += SDL_GetError();
                throw std::runtime_error( msg );
            }
        }
        // These three OpenGL attributes must be set before any window
        // which uses OpenGL can be created. If you create two
        // video_manager objects with different settings and create
        // windows with the first before the second, then all the windows
        // created by the second will inherit the first's settings and
        // it's own will have no effect.
        // At least that is what the docs say.
        // So that is why this setting information is discarded:
        // After the first set, it won't matter.
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK,  set.profile_v );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, set.maj_ver_v );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, set.min_ver_v );
    }

    video_manager::~video_manager()
    {
        zombie = true;
        
        /*buffers->clear();
        programs->clear();
        contexts->clear();
        windows->clear(); */       

        buffer_map::iterator it;
        for( it = buffers->begin(); it != buffers->end(); ++it)
            { delete (*it).second; }
        delete buffers;
        
        program_map::iterator jt;
        for( jt = programs->begin(); jt != programs->end(); ++jt)
            { delete (*jt).second; }
        delete programs;
        
        context_map::iterator kt;
        for( kt = contexts->begin(); kt != contexts->end(); ++kt)
            { delete (*kt).second; }
        delete contexts;
        
        window_map::iterator lt;
        for( lt = windows->begin(); lt != windows->end(); ++lt)
            { delete (*lt).second; }
        delete windows;
    }
    
    window& video_manager::new_window( window::settings const& set,
                                       window::settings_3D const& set_3D )
    {
        SDL_GL_SetAttribute( SDL_GL_RED_SIZE, set_3D.r_bits_v );
        SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, set_3D.g_bits_v );
        SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, set_3D.b_bits_v );
        SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, set_3D.a_bits_v );
        
        SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, set_3D.framebuffer_bits_v );
        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, set_3D.depth_bits_v );
        SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, set_3D.stencil_bits_v );
        if ( set_3D.doublebuffered_v ) {
            SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
        } else {
            SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 0 );
        }
        
        SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, set_3D.r_accumulator_bits_v );
        SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, set_3D.g_accumulator_bits_v );
        SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, set_3D.b_accumulator_bits_v );
        SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, set_3D.a_accumulator_bits_v );
        
        if ( set_3D.in_stereo_v ) {
            SDL_GL_SetAttribute( SDL_GL_STEREO, 1 );
        }
        
        if ( set_3D.multisample_v ) {
            SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
            SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, set_3D.samples_v );
        }
        
        if ( set_3D.force_hw_v ) {
            SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
        }
        
        if ( set_3D.force_sw_v ) {
            SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 0 );
        }

        //SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, set_3D.maj_ver_v );
        //SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, set_3D.min_ver_v );
        
        int SDL_flags = 0;

        if ( set.minimized_v ) {
            SDL_flags |= SDL_WINDOW_MINIMIZED;
        } else if ( set.maximized_v ) {
            SDL_flags |= SDL_WINDOW_MAXIMIZED;
        } else if ( set.fullscreen_v ) {
            SDL_flags |= SDL_WINDOW_FULLSCREEN;
        }

        if ( set.resizable_v ) {
            SDL_flags |= SDL_WINDOW_RESIZABLE;
        }

        if ( set.uses_opengl ) {
            SDL_flags |= SDL_WINDOW_OPENGL;
        }

        if ( set.visible_v ) {
            SDL_flags |= SDL_WINDOW_SHOWN;
        }

        if ( not set.has_border_v ) {
            SDL_flags |= SDL_WINDOW_BORDERLESS;
        }
        
        if ( set.has_focus_v ) {
            SDL_flags |= SDL_WINDOW_INPUT_FOCUS;
        }

        if ( set.grab_input_v ) {
            SDL_flags |= SDL_WINDOW_INPUT_GRABBED;
        }

        int x_argument = set.ulc_v[0];

        if ( set.center_on_x ) {
            x_argument = SDL_WINDOWPOS_CENTERED;
        }

        int y_argument = set.ulc_v[1];

        if ( set.center_on_y ) {
            y_argument = SDL_WINDOWPOS_CENTERED;
        }

        SDL_Window* new_sys_window = SDL_CreateWindow( set.title_v.c_str(),
                                                        x_argument,
                                                        y_argument,
                                                        set.width_v,
                                                        set.height_v,
                                                        SDL_flags );
        if ( !new_sys_window ) {
            std::string msg( "Unable to create new system window.\n" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        // Can't get it to be created minimized!
        if ( set.minimized_v ) {
            SDL_MinimizeWindow( new_sys_window );
        }

        window* new_window = new window( set.title_v, this, nxt_w_id, new_sys_window );
        (*windows)[nxt_w_id] = new_window;
        ++nxt_w_id;
        return *new_window;
    }
    
    void    video_manager::del_window( window const& wndw )
    {
        if ( this->owns( wndw ) ) {
            SDL_DestroyWindow( wndw.sys_window );
            if ( not this->zombie ) {
                // Someone else is calling the deletion
                windows->erase( wndw.g_id );
            }
            // If we are not a zombie, we are destructing
            // the video_manager and do not want a looping
            // deletion cascade, where the window is deleted
            // by windows->clear() which calls this function
            // which in turn calls ~window() when
            // windows->erase( ... ) is used.
            // Since ~window() is already being called on the
            // pointer in the map, no memory is
            // leaking.
        }
    }
    
    context& video_manager::new_context( window const& window,
                                         context::settings const& settings )
    {
        if ( not window.has_3D() ) {
            std::string msg = "The creation of a context current in window '";
            msg += window.title();
            msg += "', was attempted, but this window does not support OpenGL.";
            throw std::logic_error( msg );
        }

        SDL_GLContext new_sys_context = SDL_GL_CreateContext( window.sys_window );

        context* new_context = new context( this, nxt_c_id, &window, new_sys_context );

        (*contexts)[nxt_c_id] = new_context;
        ++nxt_c_id;
        
        activate_context( *new_context );        
        
        return *new_context;
    }
    
    void    video_manager::del_context( context const& cntx )
    {
        if ( this->owns( cntx ) ) {
            SDL_GL_DeleteContext( cntx.sys_context );
            if ( not this->zombie ) {
                // Someone else is calling the deletion
                contexts->erase( cntx.g_id );
            }
        }
    }
    
    void video_manager::attach_context( window const& wndw,
                                        context& cntx)
    {
        if ( (not owns( wndw )) or (not owns( cntx )) ) {
            std::string msg = "Illegal attachment of Context to Window '";
            msg += wndw.title();
            msg += "': ";
            if ( not owns( wndw ) ) {
                msg += "Window not owned by manager. ";
            }
            if ( not owns( cntx ) ) {
                msg += "Context not owned by manager. ";
            }
            if ( not wndw.has_3D() ) {
                msg += "Window does not support OpenGL.";
            }
            throw std::logic_error( msg );
        }

        cntx.target_window = &wndw;
        SDL_GL_MakeCurrent( wndw.sys_window, cntx.sys_context );
        active_context = &cntx;
    }
    
    void video_manager::activate_context( context& cntx )
    {
        if ( (not owns( *cntx.target_window )) or (not owns( cntx )) ) {
            std::string msg = "Illegal activation of Context on Window '";
            msg += cntx.target_window->title();
            msg += "': ";
            if ( not owns( *cntx.target_window ) ) {
                msg += "Window not owned by manager. ";
            }
            if ( not owns( cntx ) ) {
                msg += "Context not owned by manager.";
            }
            throw std::logic_error( msg );
        }

        SDL_GL_MakeCurrent( cntx.target_window->sys_window, cntx.sys_context );
        active_context = &cntx;
    }
    
    program&    video_manager::new_program( program::settings const& set )
    {
        /**
        * This code assumes that this VideoManager is the sole purveyor
        * in the program; no attempt is made to find out if anyone else
        * has created an OpenGL context. It is irrelevant anyway because
        * only this VideoManager can use the program, so we aren't
        * making an incorrect assumption. */
        if ( contexts->size() == 0 ) {
            std::string msg = "No OpenGL context had been created at time of";
            msg += " shading program creation request.";
            throw std::logic_error( msg );
        } /** Add check for adequate version number of a context;
        * OpenGL version should probably be pushed into VideoManager
        * so the whole Manager only uses one version.
        * */
        
        // ^ That guy really knew what he was talking about. ^

        program* new_program = new program( this, nxt_p_id );

        new_program->maj_ver = set.maj_ver_v;
        new_program->min_ver = set.min_ver_v;

        if ( set.has_vert_v ) {
            new_program->vert_ID = gl::CreateShader( gl::VERTEX_SHADER );
            new_program->vert_path = set.vert_path;
        }
        if ( set.has_frag_v ) {
                new_program->frag_ID = gl::CreateShader( gl::FRAGMENT_SHADER );
                new_program->frag_path = set.frag_path;
        }
        if ( set.has_geom_v ) {
                new_program->geom_ID = gl::CreateShader( gl::GEOMETRY_SHADER );
                new_program->geom_path = set.geom_path;
        }
        /** if ( set.has_tess_shader ) {
                    new_program->tess_ID = gl::CreateShader( gl::TESSALLATION_SHADER_ARB );
            }*/

        new_program->prog_ID = gl::CreateProgram();

        (*programs)[nxt_p_id] = new_program;
        ++nxt_p_id;

        return *new_program;
    }
    
    void    video_manager::del_program( program const& prgm )
    {
        if ( this->owns( prgm ) ) {
            if ( gl::IsProgram( prgm.prog_ID ) ) {
                gl::DeleteProgram( prgm.prog_ID );
            }
            if ( gl::IsShader( prgm.vert_ID ) ) {
                gl::DeleteShader( prgm.vert_ID );
            }
            if ( gl::IsShader( prgm.frag_ID ) ) {
                gl::DeleteShader( prgm.frag_ID );
            }
            if ( gl::IsShader( prgm.geom_ID ) ) {
                gl::DeleteShader( prgm.geom_ID );
            }
            if ( gl::IsShader( prgm.tess_ID ) ) {
                gl::DeleteShader( prgm.tess_ID );
            }
            if ( not this->zombie ) {
                // Someone else is calling the deletion
                programs->erase( prgm.g_id );
            }
        }
    }
    
    buffer& video_manager::new_buffer( buffer::settings const& set )
    {
        if ( contexts->size() == 0 ) {
            std::string msg ( "Buffer creation requested in absence of valid " );
            msg += "OpenGL context.";
            throw std::logic_error( msg );
        }
        GLuint new_buff_ID;
        gl::GenBuffers( 1, &new_buff_ID );
        GLuint new_vao_ID;
        gl::GenVertexArrays( 1, &new_vao_ID );

        buffer* new_buffer = new buffer( this, nxt_b_id, set.blocks_v, new_vao_ID, new_buff_ID, set.usage_v, set.target_v );

        (*buffers)[nxt_b_id] = new_buffer;
        ++nxt_b_id;

        return *new_buffer;
    }
    
    void    video_manager::del_buffer( buffer const& buff )
    {
        if ( this->owns( buff ) ) {
            gl::DeleteBuffers( 1, &buff.buff_ID );
            if ( not this->zombie ) {
                // Someone else is calling the deletion
                buffers->erase( buff.g_id );
            }
        }
    }
    
}