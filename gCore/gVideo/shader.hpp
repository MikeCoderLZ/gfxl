#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <iostream>
#include <map>
#include <set>
#include <cstdlib>

//#define GL3_PROTOTYPES
//#include "gl3.h"

#include "gl_core_3_3.hpp"
//#include "videoManager.hpp"
//PFNGLCREATESHADERPROC glCreateShader;
//PFNGLCREATEPROGRAMPROC glCreateProgram;

namespace gfx {

/**
 * Okay, forget GLSW.  We'll come up with our own, The High Level
 * Shading Preprocessor, HLSPrep.
 *
 * Sections of a shader source file are cut up and labeled with the
 * syntax " @<directive> '<name>(.<name>)*' ". This makes any file
 * that uses this system uncompilable on its own, which is a GOOD
 * thing. No one can screw it up, though it does mean you need
 * this system.
 *
 * The directives are:
 *
 * block  - a named block of source code
 * vert   - vertex shader source follows
 * frag   - fragment shader source follows
 * geo    - geometry shader source follows -- There are actually two kinds...
 *
 * end    - end the current block
 *
 * insert - insert the contents of the given block into this block at this point
 * ref    - the file makes reference to another file's contents
 * using  - indicates what version of GLSL the current block uses.
 *
 * The directives block, vert, frag, and geo all define a path for a block of
 * source code.  The block comprises all the text between the line after the
 * directive and the line before the next blocking directive or EOF.
 *
 * 
 * "block" gives a name to the source, but does not flag that source as a
 * compilable shader stage.  Anything can appear in a block. "vert", "frag", and
 * "geo" define a path and flag a source block as a compilable shader stage.
 * The shader blocks must meet certain requirements to be "valid" (I have not
 * yet defined these, but they'll be the minimum requirements of the respective
 * shader stage).
 *
 * The "insert" directive substitutes the source associated with the given path
 * at the location of the directive.
 *
 * The "ref" directive indicates that the file makes use of paths from other
 * source files.  The path given indicates what paths it will be using;
 * the same matching rules apply here as well.
 *
 * Finally, the "using" directive declares what version the current block is using.
 * GLSL's preprocessor does provide it's own directive for this purpose, the
 * "#version" directive, and you are free to use it instead.  However, the GLSL
 * directive has an important syntactical restriction: it must appear in shader
 * source before any other source except whitespace and comments.  gEngines
 * annotations are intended to make adaptive shader code easier, and part of that
 * is providing a way to dynamically pick the shader source that fits the available
 * version of GLSL, assembling a functioning shader from parts written for different
 * versions.
 *
 * Because the blocking system is swapping source around and picking the code
 * that fits the hardware, it must provide it's own facility for the coder to
 * label the version of GLSL they intend to use.  Since gEngine's directives
 * operate on top of the GLSL compiler and preprocessor, having it manipulate
 * the "#version" directive instead would violate the expectations of the coder.
 *
 * So, either only use "#version" and do not use the dynamic code generation
 * of gEngine or only use "@using".  Combining them WILL, I repeat, WILL lead
 * to strange bugs, mostly in the form of compiler errors.
 * 
 * -- 2017 me: I suspect that the thing to do would be to make the @using
 *  directive define a variant of a block specialized for a particular version
 *  of GLSL, letting gEngine decide what the appropriate version to use is
 *  based ont he available hardware/driver support. This also means it requires
 *  it's own terminating directive.
 *
 * -- Handle Matching --
 *
 * Fully qualified names are always unique, so each named block has a unique
 * path.  Names are broken into tokens by the period (.) character, and this
 * is used to dynamically match paths. Each token represents the 'order' of
 * the match.  For instance, the string "HandleA" matches both the paths
 * "HandleA.foo" and "HandleA.bar", but "HandleA.f" does not match "HandleA.foo".
 *
 * 
 * A block ends at an end directive or an EOF. The current block can be extended
 * with a new token by using "..." before it.  For example:
 *
 * @vert "Vertex"
 *
 * @begin "...LowDef"
 * @end
 *
 * @begin "...HighDef"
 * @end
 *
 * @end
 *
 * Thus creating two paths, "Vertex.LowDef" and "Vertex.HighDef".  Because
 * of the potential ambiguity, the "insert" directive and other mutagenic
 * directives cannot use the "..." syntax (what would it mean, anyway?) and
 * instead must use a name that starts at the root of the paths.
 *
 *
 * @begin 'ExtHeader'
 *
 * 	   @begin '...v25'
 * 	   // ...
 * 	   @end
 *
 * 	   @begin '...v31'
 * 	   // ...
 * 	   @end
 *
 * @end
 *
 * @begin 'SphHarmonics'
 * // ...
 * @end
 *
 * @vert 'Vertex'
 *
 *     // Code and stuff
 *     @ifversion 250
 *
 *         @insert 'ExtHeader.v25'
 *         @insert 'SphHarmonics'
 *
 *         // ...
 *     @endversion
 * 
 *     @ifversion 310    
 *
 *         @insert 'ExtHeader.v31'
 *         @insert 'SphHarmonics'
 *
 *         // ...
 *     @endversion
 *
 * @end
 *
 * <code-block>             ::= what's left over, basically
 * <directive>              ::= "@" <directive-expression> <EOL>
 * <directive-expression>   ::= <block-expression> | <markup-expression>
 * <block-expression>       ::= <block-tag> "'" <path-expression> "'"
 * <block-tag>              ::= "begin" | "vert" | "frag" | "geo"
 * <path-expression>      ::= <path> | "..." <path>
 * <path>                 ::= <path-tag> | <path-tag> "." <path>
 * <path-tag>             ::= <path-character> | <path-character> <path-tag>
 * <path-character>       ::= <letter> | <number> | "_"
 * <markup-expression>      ::= <terminator-expression> | <version-expresion> | <version-end-expression> | <insertion-expression>
 * <terminator-espression>  ::= "end"
 * <version-expression>     ::= "ifversion" <version-tag>
 * <end_version-expression> ::= "endversion"
 * <version-tag>            ::= <number> <number> <number>
 * <insertion-expression>   ::= "insert" "'" <path-tag> "'"
 * 
 * 
 * */

/**
 * A Shader object manages a single shader source file.  We adopt
 * the syntax and behavior of the GL Shader Wrangler, which is
 * straight forward to replicate and undoubtedly useful.  Using
 * the GLSW library itself was not done because that library is
 * C-compatible and requires the inclusion of another string library.
 * C++'s native <string> library is sufficient for the task.
 *
 * This implementation must duplicate the interpretive behavior of
 * the GLSW.  However, since GLSW is a centralized service that
 * coordinates loading and accessing shader effect files, we may be
 * at odds.
 *
 * Each Shader object knows the file it manages; it reads this file
 * and stores the individual pieces of the shader according to the
 * Key specified in the file for each piece.  Upon request, the
 * appropriate shader source is assembled from the pieces.
 * */

/**
 * The ShaderManager maintains a source tree of shader files and
 * the associated Shader objects.
 * 
 * */

/*    class shader;

    class shader_system {
        
    public:
                                    shader_system();
                                    ~shader_system();
        static shader_system&  get();
        bool                        add_shader_source( std::string const& src_path );
        
#ifdef DEBUG
        size_t                      shader_set_size() const;
#endif
        
    private:
        
        class source_node {
        public:
            typedef std::map<std::string, source_node*>   child_vector;
            
            source_node();
            ~source_node();
            std::string*        path;
            std::string*        source;
            child_vector*       children; // null address means leaf node
        };
        
        typedef std::map<std::string, shader_system::source_node*>  path_map;
        typedef std::set<shader*>                                   shader_set;
        
        static shader_system* const     instance;
        unsigned long                   next_shdr_ID;
        source_node*                    source_tree;
        path_map*                     paths;
        shader_set*                     shaders;
        
        bool                            owned( shader const& shd );
        unsigned long                   register_shader( shader* shdr );
        void                            unregister_shader( shader* shdr );
        friend                          class shader;
    };

    inline shader_system&  shader_system::get()
    { return *shader_system::instance; }

#ifdef DEBUG
    inline size_t   shader_system::shader_set_size() const
    { return shaders->size(); }
#endif
*/
    class shader {

    public:
        
        class settings {
        public:
                            settings();
            settings&       vertex_path( std::string const& path );
            settings&       fragment_path( std::string const& path );
            settings&       tesselation_path( std::string const& path );
            settings&       geometry_path( std::string const& path );
        private:
            std::string     v_path;
            std::string     f_path;
            std::string     t_path;
            std::string     g_path;
            
            bool            has_vert;
            bool            has_frag;
            bool            has_tess;
            bool            has_geom;
            friend          class shader;
        };
        
                        shader( context const& context,
                                settings const& set = settings() );
                        ~shader();
        void            uniform( std::string const& name );
        std::string     vertex_path() const { return v_path; }
        std::string     fragment_path() const { return f_path; }
        std::string     tesselation_path() const { return t_path; }
        std::string     geometry_path() const { return g_path; }
#ifdef DEBUG
        GLuint          vertex_ID() const { return vert_ID; }
        GLuint          fragment_ID() const { return frag_ID; }
        GLuint          tesselation_ID() const { return tess_ID; }
        GLuint          geometry_ID() const { return geom_ID; }
        GLuint          program_ID() const { return prog_ID; }
#endif
        void            compile();
        void            link();
        emplate< typename T >
        void            load_uniform( std::string const& name,
                                      T const& val             );
        void            use();
        bool            operator ==( shader const& rhs ) const;
        friend          std::ostream& operator<<( std::ostream& out, shader const& rhs );

    private:
        // Probably should remove interdependencies because they are unnecessary
        context const*  target_context;
        typedef
        std::map<std::string, GLint>    key_map;
        key_map*                        uniform_map;
        std::string     v_path;
        std::string     f_path;
        std::string     g_path;
        std::string     t_path;
        bool            has_vert;
        bool            has_frag;
        bool            has_geom;
        bool            has_tess;
        GLuint          vert_ID;
        GLuint          frag_ID;
        GLuint          geom_ID;
        GLuint          tess_ID;
        GLuint          prog_ID;
        void            compile( GLuint stage_ID, std::string const& stage_path );
        friend          class video_system;
        //friend          class shader_system;
    };

    inline bool     shader::operator ==( shader const& rhs ) const
    {   // This is a placeholder; there are cases where this MIGHT cause
        // pronlems.
        return this->prog_ID == rhs.prog_ID; }
    
    std::ostream& operator<<( std::ostream& out, shader const& rhs );
    
    inline shader::settings::settings() : v_path( "" ),
                                          f_path( "" ),
                                          t_path( "" ),
                                          g_path( "" ),
                                          has_vert( false ),
                                          has_frag( false ),
                                          has_tess( false ),
                                          has_geom( false ){}

    inline shader::settings&  shader::settings::vertex_path( std::string const& path )
    {
        v_path = path;
        if ( v_path.compare( "" ) != 0 ) {
            has_vert = true;
        }
        return *this;
    }

    inline shader::settings&  shader::settings::fragment_path( std::string const& path )
    {
        f_path = path;
        if ( f_path.compare( "" ) != 0 ) {
            has_frag = true;
        }
        return *this;
    }

    inline shader::settings&  shader::settings::tesselation_path( std::string const& path )
    {
        t_path = path;
        if ( t_path.compare( "" ) != 0 ) {
            has_tess = true;
        }
        return *this;
    }
    
    inline shader::settings&  shader::settings::geometry_path( std::string const& path )
    {
        g_path = path;
        if ( g_path.compare( "" ) != 0 ) {
            has_geom = true;
        }
        return *this;
    }
    
    template< typename T > inline
    void    shader::load_uniform( std::string const& name,
                                   T const& val     )
    {
        throw std::invalid_argument( "No support for given type of uniform." );
    }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   float32 const& val  )
    { gl::Uniform1f( (*uniform_map)[name], val ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   float const& val  )
    { gl::Uniform1f( (*uniform_map)[name], val ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   vec2 const& val  )
    { gl::Uniform2f( (*uniform_map)[name], val[0], val[1] ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   vec3 const& val  )
    { gl::Uniform3f( (*uniform_map)[name], val[0], val[1], val[2] ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   vec4 const& val  )
    { gl::Uniform4f( (*uniform_map)[name], val[0], val[1], val[2], val[3] ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   int32 const& val  )
    { gl::Uniform1i( (*uniform_map)[name], val ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   int const& val  )
    { gl::Uniform1i( (*uniform_map)[name], val ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   ivec2 const& val  )
    { gl::Uniform2i( (*uniform_map)[name], val[0], val[1] ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   ivec3 const& val  )
    { gl::Uniform3i( (*uniform_map)[name], val[0], val[1], val[2] ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   ivec4 const& val  )
    { gl::Uniform4i( (*uniform_map)[name], val[0], val[1], val[2], val[3] ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   uint32 const& val  )
    { gl::Uniform1ui( (*uniform_map)[name], val ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   uint32_t const& val  )
    { gl::Uniform1ui( (*uniform_map)[name], val ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   uvec2 const& val  )
    { gl::Uniform2ui( (*uniform_map)[name], val[0], val[1] ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   uvec3 const& val  )
    { gl::Uniform3ui( (*uniform_map)[name], val[0], val[1], val[2] ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   uvec4 const& val  )
    { gl::Uniform4ui( (*uniform_map)[name], val[0], val[1], val[2], val[3] ); }
    
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   mat2 const& val         )
    { gl::UniformMatrix2fv( (*uniform_map)[name],
                            1, gl::FALSE_,
                            (GLfloat*) val.to_map().bytes ); }

    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   mat3 const& val         )
    { gl::UniformMatrix3fv( (*uniform_map)[name],
                            1, gl::FALSE_,
                            (GLfloat*) val.to_map().bytes ); }
                            
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   mat4 const& val         )
    { gl::UniformMatrix4fv( (*uniform_map)[name],
                            1, gl::FALSE_,
                            (GLfloat*) val.to_map().bytes ); }
                            
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   mat2x3 const& val         )
    { gl::UniformMatrix2x3fv( (*uniform_map)[name],
                              1, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
                            
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   mat3x2 const& val         )
    { gl::UniformMatrix3x2fv( (*uniform_map)[name],
                              1, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
                              
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   mat2x4 const& val         )
    { gl::UniformMatrix2x4fv( (*uniform_map)[name],
                              1, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
                            
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   mat4x2 const& val         )
    { gl::UniformMatrix4x2fv( (*uniform_map)[name],
                              1, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
                              
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   mat3x4 const& val         )
    { gl::UniformMatrix3x4fv( (*uniform_map)[name],
                              1, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
                            
    template<> inline
    void    shader::load_uniform( std::string const& name,
                                   mat4x3 const& val         )
    { gl::UniformMatrix4x3fv( (*uniform_map)[name],
                              1, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
    
}

#endif
