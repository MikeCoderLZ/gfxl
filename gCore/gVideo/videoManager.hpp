#ifndef SYS_MANAGER_HPP_
#define SYS_MANAGER_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "checkError.hpp"
#include "SDL.h"
#include "gl_core_3_3.hpp"
#include "../gUtility/datatypeinfo.hpp"
#include "../gMath/datatype.hpp"

namespace gfx {

class VideoManager;

/**
 * A named parameter helper class for initializing Window objects. Forward
 * declaration of VideoManager facilitates friending.
 *
 * WindowSettings return a reference to this object, so they are meant to
 * be chained.
 */
class WindowSettings {
public:
	                    WindowSettings();
	WindowSettings&     title( std::string const& title );
	WindowSettings&     x_pos( int x );
	WindowSettings&     y_pos( int y );
	WindowSettings&     width( int w );
	WindowSettings&     height( int h );
	WindowSettings&     x_centered();
	WindowSettings&     y_centered();
	WindowSettings&     maximized();
	WindowSettings&     minimized();
	WindowSettings&     resizable();
	WindowSettings&     use_opengl();
	WindowSettings&     shown();
	WindowSettings&     borderless();
	WindowSettings&     fullscreen();
	WindowSettings&     grab_input();
private:
	friend              class VideoManager;
	std::string         window_title;
	int                 x_position;
	int                 y_position;
	int                 x_size;
	int                 y_size;
	bool                is_x_centered;
	bool                is_y_centered;
	bool                is_minimized;
	bool                is_maximized;
	bool                is_fullscreen;
	bool                is_resizable;
	bool                uses_opengl;
	bool                is_shown;
	bool                no_border;
	bool                input_is_grabbed;
};

inline  WindowSettings::WindowSettings() :
        window_title ("untitled"),
        x_position (-1), y_position (-1),
        // Terrible default!!!!!! FIX ME WITH DYNAMIC SIZE!!!!
        x_size (512), y_size (512),
        is_x_centered (true), is_y_centered (true),
        is_minimized (false), is_maximized (false),
        is_fullscreen (false),
        is_resizable (false),
        uses_opengl (false),
        is_shown (true),
        no_border (false),
        input_is_grabbed (false) {};

inline	WindowSettings&     WindowSettings::title( std::string const& title )
{ window_title = title; return *this; }

inline	WindowSettings&     WindowSettings::x_pos( int x )
{	x_position = x;
	is_x_centered = false;
	return *this; }
inline	WindowSettings&     WindowSettings::y_pos( int y )
{	y_position = y;
	is_y_centered = false;
	return *this; }
inline	WindowSettings&     WindowSettings::width( int w )
{ x_size = w; return *this; }
inline	WindowSettings&     WindowSettings::height( int h )
{ y_size = h; return *this; }

inline  WindowSettings&     WindowSettings::x_centered()
{	is_x_centered = true;
	x_position = -1;
	return *this; }
inline  WindowSettings&     WindowSettings::y_centered()
{	is_y_centered = true;
	y_position = -1;
	return *this; }

inline  WindowSettings&     WindowSettings::maximized()
{	is_maximized = true;
	is_minimized = false;
	is_fullscreen = false;
	return *this; }

inline  WindowSettings&     WindowSettings::minimized()
{	is_minimized = true;
	is_maximized = false;
	is_fullscreen = false;
	return *this; }

inline  WindowSettings&     WindowSettings::fullscreen()
{	is_fullscreen = true;
	is_minimized = false;
	is_maximized = false;
	return *this; }

inline  WindowSettings&     WindowSettings::resizable()
{ is_resizable = true; return *this; }

inline  WindowSettings&     WindowSettings::use_opengl()
{ uses_opengl = true; return *this; }

inline  WindowSettings&     WindowSettings::shown()
{ is_shown = true; return *this; }

inline  WindowSettings&     WindowSettings::borderless()
{ no_border = true; return *this; }
inline  WindowSettings&     WindowSettings::grab_input()
{ input_is_grabbed = true; return *this; }

/**
 * A class that maintains a handle to a system window.  Manipulation of the
 * Window happens via VideoManager; Window itself only has inspection
 * functions.
 * */

class Window {
public:
	void                    swap();
	bool                    uses_opengl() const;
	bool                    operator ==( Window const& rhs ) const;
	friend                  std::ostream& operator <<( std::ostream& out,
	                                                   Window const& rhs );
private:
	friend                  class VideoManager;
	                        Window( std::string const& title,
	                                VideoManager* const manager,
	                                SDL_Window* system_window );
	std::string             title;
	VideoManager* const     manager;
	SDL_Window*             system_window;
};

std::ostream&   operator <<( std::ostream& out, Window const& rhs );

inline  bool    Window::uses_opengl() const
{ return bool( SDL_GetWindowFlags( system_window ) & SDL_WINDOW_OPENGL ); }

// Yes, normally this is a bad idea.  However, two gfx::Window
// objects are closely tied to the SDL system windows they manage,
// so this should actually always work.  Window is NOT getting any
// subclasses; if you do subclass, be forewarned that it is going
// to explode.

inline  bool    Window::operator ==( Window const& rhs ) const
{ return this->system_window == rhs.system_window; }

inline  Window::Window( std::string const& title,
                        VideoManager* const manager,
                        SDL_Window* system_window ) :
                            title ( title ), manager( manager ),
                            system_window( system_window ) {};
/**
 * A Context maintains a handle to a system OpenGL rendering context.
 * Like Window, it is managed by VideoManager and only has inspection
 * functions.
 * */

class Context {
public:
	void                    clear_color( float red, float green,
	                                     float blue, float alpha = 1.0f );
	bool                    is_active() const;
	bool                    operator ==( Context const& rhs ) const;
private:
	friend                  class VideoManager;
	                        Context( VideoManager* const manager,
	                                 Window const* target_window,
	                                 SDL_GLContext system_context);
	VideoManager* const     manager;
	Window const*           target_window;
	SDL_GLContext           system_context;
};

inline  bool    Context::operator ==( Context const& rhs ) const
{ return this->system_context == rhs.system_context; }

inline  Context::Context( VideoManager* const manager,
                          Window const* target_window,
                          SDL_GLContext system_context) :
                              manager( manager ),
                              target_window( target_window ),
                              system_context( system_context ) {};

/**
 * The named parameter helper class for Contexts; analogous to WindowSettings.
 * */

class ContextSettings {
public:
	                    ContextSettings();
	ContextSettings&    major_version( unsigned int maj_ver);
	ContextSettings&    minor_version( unsigned int min_ver);
	ContextSettings&    depth_size( unsigned int bits);
	ContextSettings&    double_buffered();
	ContextSettings&    not_double_buffered();
private:
	friend              class VideoManager;
	unsigned int        maj_ver;
	unsigned int        min_ver;
	unsigned int        depth_bits;
	bool                is_double_buffered;
};

inline  ContextSettings::ContextSettings() :
                maj_ver(1), min_ver(4),
                depth_bits(16), is_double_buffered(true) {};

inline  ContextSettings&    ContextSettings::major_version( unsigned int maj_ver )
{ this->maj_ver = maj_ver; return *this; }

inline  ContextSettings&    ContextSettings::minor_version( unsigned int min_ver )
{ this->min_ver = min_ver; return *this; }

inline  ContextSettings&    ContextSettings::depth_size( unsigned int bits )
{ this->depth_bits = bits; return *this; }

inline  ContextSettings&    ContextSettings::double_buffered()
{ this->is_double_buffered = true; return *this; }

inline  ContextSettings&    ContextSettings::not_double_buffered()
{ this->is_double_buffered = false;	return *this; }

class compilation_error : public std::logic_error {
public:
    explicit compilation_error( std::string const& msg ) : logic_error( msg ) {};
};

class ProgramSettings {
public:
                        ProgramSettings();
    ProgramSettings&    major_version( unsigned int maj_ver);
    ProgramSettings&    minor_version( unsigned int min_ver);
    ProgramSettings&    uses_vert();
    ProgramSettings&    uses_frag();
    ProgramSettings&    uses_geom();
    // ProgramSettings& uses_tess(); /** Needs ARB extension */
    ProgramSettings&    uses_vert( std::string const& path );
    ProgramSettings&    uses_frag( std::string const& path );
    ProgramSettings&    uses_geom( std::string const& path );
    // ProgramSettings& uses_tess( std::string const& path ); /** Needs ARB extension */
    ProgramSettings&    no_vert();
    ProgramSettings&    no_frag();
    ProgramSettings&    no_geom();
    //ProgramSettings& no_tess();/** Needs ARB extension */
private:
    friend              class VideoManager;
    std::string         vert_path;
    std::string         frag_path;
    std::string         geom_path;
    //std::string tess_path;
    unsigned int        maj_ver;
    unsigned int        min_ver;
    bool                has_vert_shader;
    bool                has_frag_shader;
    bool                has_geom_shader;
    bool                has_tess_shader;
};

inline  ProgramSettings::ProgramSettings() :
            vert_path( "" ), frag_path( "" ), geom_path( "" ),
            maj_ver(2), min_ver(0),
            has_vert_shader(true), has_frag_shader(true),
            has_geom_shader(false), has_tess_shader(false) {};

inline  ProgramSettings&    ProgramSettings::major_version( unsigned int maj_ver)
{ this->maj_ver = maj_ver; return *this; }

inline  ProgramSettings&    ProgramSettings::minor_version( unsigned int min_ver)
{ this->min_ver = min_ver; return *this; }

inline  ProgramSettings&    ProgramSettings::uses_vert()
{ this->has_vert_shader = true; return *this; }

inline  ProgramSettings&    ProgramSettings::uses_frag()
{ this->has_frag_shader = true; return *this; }

inline  ProgramSettings&    ProgramSettings::uses_geom()
{ this->has_geom_shader = true; return *this; }

inline  ProgramSettings&    ProgramSettings::uses_vert( std::string const& path )
{ this->has_vert_shader = true; this->vert_path = path; return *this; }

inline  ProgramSettings&    ProgramSettings::uses_frag( std::string const& path )
{ this->has_frag_shader = true; this->frag_path = path; return *this; }

inline  ProgramSettings&    ProgramSettings::uses_geom( std::string const& path )
{ this->has_geom_shader = true; this->geom_path = path; return *this; }

inline  ProgramSettings&    ProgramSettings::no_vert()
{ this->has_vert_shader = false; return *this; }

inline  ProgramSettings&    ProgramSettings::no_frag()
{ this->has_frag_shader = false; return *this; }

inline  ProgramSettings&    ProgramSettings::no_geom()
{ this->has_geom_shader = false; return *this; }

class Program {
public:
    void                    compile();
    void                    link();
    void                    use();
    friend std::ostream&    operator <<( std::ostream& out, Program const& rhs );
    GLuint                  getProgID() const { return prog_ID; }
private:
    friend                  class VideoManager;
                            Program( VideoManager* const manager );
    void                    compile( GLuint stage_ID, std::string const& stage_path );
    VideoManager* const     manager;
    std::string             vert_path;
    std::string             frag_path;
    std::string             geom_path;
    GLuint                  vert_ID;
    GLuint                  frag_ID;
    GLuint                  geom_ID;
    GLuint                  tess_ID;
    GLuint                  prog_ID;
    unsigned int            maj_ver;
    unsigned int            min_ver;
};

std::ostream&   operator <<( std::ostream& out, Program const& rhs );

inline Program::Program( VideoManager* const manager ) :
            manager( manager ),
            vert_path( "" ), frag_path( "" ), geom_path( "" ),
            vert_ID( 0 ), frag_ID( 0 ), geom_ID( 0 ), tess_ID( 0 ), prog_ID( 0 ),
            maj_ver( 2 ), min_ver( 0 ) {};

class BufferSettings {
public:
    friend              class VideoManager;
                        BufferSettings();
    BufferSettings&     blocks( GLsizeiptr new_n_blocks );
    BufferSettings&     static_draw();
    BufferSettings&     static_read();
    BufferSettings&     static_copy();
    BufferSettings&     dynamic_draw();
    BufferSettings&     dynamic_read();
    BufferSettings&     dynamic_copy();
    BufferSettings&     stream_draw();
    BufferSettings&     stream_read();
    BufferSettings&     stream_copy();
    BufferSettings&     for_array();
//    BufferSettings&     for_atomic_counter();
    BufferSettings&     for_copy_read();
    BufferSettings&     for_copy_write();
//    BufferSettings&     for_indirect_draw();
//    BufferSettings&     for_indirect_dispatch();
    BufferSettings&     for_element_array();
    BufferSettings&     for_pixel_packing();
    BufferSettings&     for_pixel_unpacking();
//    BufferSettings&     for_shader_storage();
    BufferSettings&     for_texture();
    BufferSettings&     for_transform_feedback();
    BufferSettings&     for_uniform();
private:
    GLsizeiptr          n_blocks;
    GLenum              usage;
    GLenum              intended_target;
};

inline  BufferSettings::BufferSettings() :
                n_blocks(0), usage( gl::DYNAMIC_DRAW ),
                intended_target( gl::ARRAY_BUFFER ) {}

inline BufferSettings&  BufferSettings::blocks( GLsizeiptr n_blocks )
{ this->n_blocks = n_blocks; return *this; }

inline  BufferSettings&     BufferSettings::static_draw()
{ usage = gl::STATIC_DRAW; return *this; }

inline  BufferSettings&     BufferSettings::static_read()
{ usage = gl::STATIC_READ; return *this; }

inline  BufferSettings&     BufferSettings::static_copy()
{ usage = gl::STATIC_COPY; return *this; }

inline  BufferSettings&     BufferSettings::dynamic_draw()
{ usage = gl::DYNAMIC_DRAW; return *this; }

inline  BufferSettings&     BufferSettings::dynamic_read()
{ usage = gl::DYNAMIC_READ; return *this; }

inline  BufferSettings&     BufferSettings::dynamic_copy()
{ usage = gl::DYNAMIC_COPY; return *this; }

inline  BufferSettings&     BufferSettings::stream_draw()
{ usage = gl::STREAM_DRAW; return *this; }

inline  BufferSettings&     BufferSettings::stream_read()
{ usage = gl::STREAM_READ; return *this; }

inline  BufferSettings&     BufferSettings::stream_copy()
{ usage = gl::STREAM_COPY; return *this; }

inline  BufferSettings&     BufferSettings::for_array()
{ intended_target = gl::ARRAY_BUFFER; return *this; }
//inline  BufferSettings&     BufferSettings::for_atomic_counter()
//{ intended_target = gl::ATOMIC_COUNTER_BUFFER; return *this; }
inline  BufferSettings&     BufferSettings::for_copy_read()
{ intended_target = gl::COPY_READ_BUFFER; return *this; }
inline  BufferSettings&     BufferSettings::for_copy_write()
{ intended_target = gl::COPY_WRITE_BUFFER; return *this; }
//inline  BufferSettings&     BufferSettings::for_indirect_draw()
//{ intended_target = gl::DRAW_INDIRECT_BUFFER; return *this; }
//inline  BufferSettings&     BufferSettings::for_indirect_dispatch()
//{ intended_target = gl::DISPATCH_INDIRECT_BUFFER; return *this; }
inline  BufferSettings&     BufferSettings::for_element_array()
{ intended_target = gl::ELEMENT_ARRAY_BUFFER; return *this; }
inline  BufferSettings&     BufferSettings::for_pixel_packing()
{ intended_target = gl::PIXEL_PACK_BUFFER; return *this; }
inline  BufferSettings&     BufferSettings::for_pixel_unpacking()
{ intended_target = gl::PIXEL_UNPACK_BUFFER; return *this; }
//inline  BufferSettings&     BufferSettings::for_shader_storage()
//{ intended_target = gl::SHADER_STORAGE_BUFFER; return *this; }
inline  BufferSettings&     BufferSettings::for_texture()
{ intended_target = gl::TEXTURE_BUFFER; return *this; }
inline  BufferSettings&     BufferSettings::for_transform_feedback()
{ intended_target = gl::TRANSFORM_FEEDBACK_BUFFER; return *this; }
inline  BufferSettings&     BufferSettings::for_uniform()
{ intended_target = gl::UNIFORM_BUFFER; return *this; }

class BlockSpec {
public:
    friend                          class Buffer;
                                    BlockSpec();
                                    ~BlockSpec();
    template< typename T >
    BlockSpec&                      attribute( type<T> const& proto );
private:
    typedef std::vector< info* >    attrib_vector;
    attrib_vector*                  attributes;
};

inline  BlockSpec::BlockSpec() : attributes( new BlockSpec::attrib_vector() ) {}

template< typename T > inline
BlockSpec&     BlockSpec::attribute( type<T> const& proto )
{   info* new_attrib = (info*) proto.copy();
    attributes->push_back( new_attrib );
    return *this; }

class Buffer {
public:
    friend                      class VideoManager;
    friend std::ostream&        operator <<( std::ostream& out, Buffer const& rhs );
                                ~Buffer();
    void                        block_format( BlockSpec const& spec );
    void                        blocks( GLsizeiptr const blocks );
    void                        add_blocks( GLsizeiptr const more_blocks );
    template< typename DATA >
    void                        fill_attribute( GLuint index,
                                                std::vector< DATA > const& attrib_data );
    void                        load_data();
    void                        align_vertices();
    GLuint                      getBuffId() const { return buff_ID; }
private:
    VideoManager*               manager;
    unsigned char*              data;
    GLsizeiptr                  n_blocks;
    GLsizeiptr                  stride;
    GLuint                      vao_ID;
    GLuint                      buff_ID;
    GLenum                      usage;
    GLenum                      intended_target;
    bool                        data_loaded;
    bool                        verts_specified;
    typedef std::vector<info*>  attrib_vector;
    attrib_vector*              attributes;
                                Buffer( VideoManager* new_manager,
                                        GLsizeiptr new_n_blocks,
                                        GLuint new_vao_ID,
                                        GLuint new_buff_ID,
                                        GLenum new_usage,
                                        GLenum new_target );
    GLsizeiptr                  attribute_offset( GLuint index ) const;
};

inline Buffer::Buffer( VideoManager* new_manager,
                    GLsizeiptr new_n_blocks,
                    GLuint new_vao_ID,
                    GLuint new_buff_ID,
                    GLenum new_usage,
                    GLenum new_target ) :
                        manager( new_manager ),
                        data( 0 ), n_blocks( new_n_blocks ), stride( 0 ),
                        vao_ID( new_vao_ID ), buff_ID( new_buff_ID ),
                        usage( new_usage ), intended_target( new_target ),
                        data_loaded( false ), verts_specified( false )
{ attributes = new attrib_vector(); }

template< typename DATA >
void Buffer::fill_attribute( GLuint index, std::vector< DATA > const& attrib_data )
{
    if ( (*(*attributes)[index]) != type< DATA >() ) {
        std::string msg = "Type stored in std::vector, ";
        msg += type< DATA >().name();
        msg += ", does not match type specified at buffer index ";
        msg += index;
        msg += ", ";
        msg += (*attributes)[index]->name();
        msg += ".";
        throw std::invalid_argument( msg );
    }
    if ( attrib_data.size() > n_blocks ) {
        std::string msg = "Attribute value assignment attempted with ";
        msg += n_blocks;
        msg += " allocated data blocks but ";
        msg += attrib_data.size();
        msg += " attribute values.";
        throw std::invalid_argument( msg);
    }
    if ( not verts_specified ) {
        throw std::logic_error( "Attribute value assignment attempted when vertex format was not specified." );
    }
    if ( data == 0 ) {
        data = new unsigned char[n_blocks * stride];
    }

    GLsizeiptr block;
    unsigned char* cursor = data;
    cursor += attribute_offset( index );
    for( block = 0; block < n_blocks; ++block ) {
        raw_map const mapped_data = attrib_data[block].to_map();
        for( size_t b = 0; b < mapped_data.n_bytes; ++b ) {
            cursor[b] = mapped_data[b];
        }
        cursor += stride;
    }
}

inline  void    Buffer::load_data()
{
    if( intended_target == gl::ELEMENT_ARRAY_BUFFER ){
        gl::BindVertexArray( vao_ID );
        checkGLError( "vao bound for element data load" );
    }
    gl::BindBuffer( intended_target, buff_ID );
    gl::BufferData( intended_target, n_blocks * stride, data, usage );

    data_loaded = true;
}

inline  void    Buffer::align_vertices()
{
    if ( not data_loaded ) {
        std::string msg = "Buffer data has not be uploaded to OpenGL; ";
        msg += "either the buffer is new or the data has changed since ";
        msg += "the last time it was loaded.";
        throw std::logic_error( msg );
    }

    if ( not verts_specified ) {
        std::string msg = "Blocks of buffer data not yet formated.";
        throw std::logic_error( msg );
    }

    std::cout << "Buffer ID: " << buff_ID << std::endl;
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
            std::cout << "VertexAttribPointer called." << std::endl;
            std::cout << "\tindex: " << index << '\n';
            std::cout << "\tsize: " << (*a)->n_components() << '\n';
            std::cout << "\ttype: " << (*a)->component_to_GL() << '\n';
            std::cout << "\tstride: " << stride << '\n';
            std::cout << "\toffset: " << offset << std::endl;
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

inline  std::ostream&   operator <<( std::ostream& out, Buffer const& rhs )
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

    return out; }



/**
 * VideoManager provides an interface for creating and manipulating both
 * Windows and Contexts.  Since these objects work together in a non-trivial
 * way, their interaction is here controlled to make it safe and clear.
 *
 * Creating an instance of either object requires that a ____Settings object is
 * provided for that type.  The reference returned is a live reference to the
 * Window or Context itself in memory.
 */

class VideoManager {
public:
	                                VideoManager();
	                                ~VideoManager();
	Window&                         create_window( WindowSettings const& settings = WindowSettings() );
	Context&                        create_context( Window const& window,
	                                                ContextSettings const& settings = ContextSettings() );
	void                            attach_context( Window const& window,
	                                                Context& context );
	void                            activate_context( Context& context );
	Context&                        get_active_context() const;
	Program&                        create_program( ProgramSettings const& settings = ProgramSettings() );
	Buffer&                         create_buffer( BufferSettings const& settings );
	friend std::ostream&            operator <<( std::ostream& out, VideoManager const& rhs);
private:
	bool                            owned( Context const& context );
	bool                            owned( Window const& window );
	bool                            owned( Program const& program );
	typedef std::vector<Window*>    window_vector;
	typedef std::vector<Context*>   context_vector;
	typedef std::vector<Program*>   program_vector;
	typedef std::vector<Buffer*>    buffer_vector;
	window_vector*                  windows;
	context_vector*                 contexts;
	program_vector*                 programs;
	buffer_vector*                  buffers;
	Context*                        active_context;
};

std::ostream&   operator <<(std::ostream& out, VideoManager const& rhs );

inline  bool    Context::is_active() const
{ return (*this) == manager->get_active_context(); }

inline  bool    VideoManager::owned( Context const& context )
{ return this == context.manager; }

inline  bool    VideoManager::owned( Window const& window )
{ return this == window.manager; }

inline  bool    VideoManager::owned( Program const& program )
{ return this == program.manager; }

}

#endif
