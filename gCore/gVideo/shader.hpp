#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <iostream>

//#define GL3_PROTOTYPES
//#include "gl3.h"

#include "gl_core_3_3.hpp"
#include "videoManager.hpp"
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
 * The directives block, vert, frag, and geo all define a handle for a block of
 * source code.  The block comprises all the text between the line after the
 * directive and the line before the next blocking directive or EOF.
 *
 * 
 * "block" gives a name to the source, but does not flag that source as a
 * compilable shader stage.  Anything can appear in a block. "vert", "frag", and
 * "geo" define a handle and flag a source block as a compilable shader stage.
 * The shader blocks must meet certain requirements to be "valid" (I have not
 * yet defined these, but they'll be the minimum requirements of the respective
 * shader stage).
 *
 * The "insert" directive substitutes the source associated with the given handle
 * at the location of the directive.
 *
 * The "ref" directive indicates that the file makes use of handles from other
 * source files.  The handle given indicates what handles it will be using;
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
 * handle.  Names are broken into tokens by the period (.) character, and this
 * is used to dynamically match handles. Each token represents the 'order' of
 * the match.  For instance, the string "HandleA" matches both the handles
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
 * Thus creating two handles, "Vertex.LowDef" and "Vertex.HighDef".  Because
 * of the potential ambiguity, the "insert" directive and other mutagenic
 * directives cannot use the "..." syntax (what would it mean, anyway?) and
 * instead must use a name that starts at the root of the handles.
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
 * <block-expression>       ::= <block-tag> "'" <handle-expression> "'"
 * <block-tag>              ::= "begin" | "vert" | "frag" | "geo"
 * <handle-expression>      ::= <handle> | "..." <handle>
 * <handle>                 ::= <handle-tag> | <handle-tag> "." <handle>
 * <handle-tag>             ::= <handle-character> | <handle-character> <handle-tag>
 * <handle-character>       ::= <letter> | <number> | "_"
 * <markup-expression>      ::= <terminator-expression> | <version-expresion> | <version-end-expression> | <insertion-expression>
 * <terminator-espression>  ::= "end"
 * <version-expression>     ::= "ifversion" <version-tag>
 * <end_version-expression> ::= "endversion"
 * <version-tag>            ::= <number> <number> <number>
 * <insertion-expression>   ::= "insert" "'" <handle-tag> "'"
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

class ShaderManager {
    
public:
                ShaderManager();
                ~ShaderManager();
    Shader&     create_shader( ShaderSettings const& settings = ShaderSettings() );
    bool        add_shader_source( std::string const& src_path ):
    
private:
    
    class source_node {
    public:
        source_node();
        ~source_node();
        std::string*        handle;
        std::string*        source;
        typedef std::map<std::string, source_node*>   child_vector;
        child_vector*       children; // null address means leaf node
    };
    
    // annotated source tree structure
    bool                            owned( Shader const& shader );
    source_node*                    source_tree;
    typedef std::map<std::string, source_node*>     handle_map;
    handle_map*                     handles;
    typedef std::vector<Shader*>    shader_vector;
    shader_vector*                  shaders;
};

class ShaderSettings {
public:
    friend              class ShaderManager;
                        ShaderSettings();
    ShaderSettings&     vertex_stage( std::string const& new_v_handle )
    ShaderSettings&     fragment_stage( std::string const& new_f_handle )
    ShaderSettings&     geometry_stage( std::string const& new_g_handle )
    ShaderSettings&     tesselation_stage( std::string const& new_t_handle )
private:
    std::string         v_handle;
    std::string         f_handle;
    std::string         g_handle;
    std::string         t_handle;
};

inline ShaderSettings::ShaderSettings() : v_handle( 0 ),
                                          f_handle( 0 ),
                                          g_handle( 0 ),
                                          t_handle( 0 ) {}

inline ShaderSettings&  ShaderSettings::vertex_stage( std::string const& new_v_handle )
{
    v_handle* = new_v_handle;
    return *this;
}

inline ShaderSettings&  ShaderSettings::fragment_stage( std::string const& new_f_handle )
{
    f_handle* = new_f_handle;
    return *this;
}

inline ShaderSettings&  ShaderSettings::geometry_stage( std::string const& new_g_handle )
{
    g_handle* = new_g_handle;
    return *this;
}

inline ShaderSettings&  ShaderSettings::tesselation_stage( std::string const& new_t_handle )
{
    t_handle* = new_t_handle;
    return *this;
}

class Shader {

public:
    bool            compile();
    bool            link();
    bool            use();
    friend std::ostream& operator<<( std::ostream& out, Shader const& rhs );

private:
    friend          class ShaderManager;
                    Shader( std::string const& new_v_handle,
                            std::string const& new_f_handle,
                            std::string const& new_g_handle,
                            std::string const& new_t_handle );
                    Shader( std::string const& new_v_handle,
                            std::string const& new_f_handle );
    std::string     v_handle;
    std::string     f_handle;
    std::string     g_handle;
    std::string     t_handle;
    GLuint          vert_ID;
    GLuint          frag_ID;
    GLuint          geom_ID;
    GLuint          tess_ID;
    GLuint          prog_ID;

};

std::ostream& operator<<( std::ostream& out, Shader const& rhs );



}

#endif
