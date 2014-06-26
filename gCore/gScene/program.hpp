#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <cstring>
#include <cstdint>
#include <map>
#include "../gVideo/gl_core_3_3.hpp"
#include "../gVideo/video.hpp"

namespace gfx {
                                
    class program {
    public:
        
        class settings {
        public:
                                settings();
            settings&           maj_ver( unsigned int maj_ver);
            settings&           min_ver( unsigned int min_ver);
            settings&           has_vert();
            settings&           has_frag();
            settings&           has_geom();
            // settings& uses_tess(); /** Needs ARB extension */
            settings&           use_vert( std::string const& path );
            settings&           use_frag( std::string const& path );
            settings&           use_geom( std::string const& path );
            // settings& uses_tess( std::string const& path ); /** Needs ARB extension */
            settings&           no_vert();
            settings&           no_frag();
            settings&           no_geom();
            //settings& no_tess();/** Needs ARB extension */
        private:
            std::string         vert_path;
            std::string         frag_path;
            std::string         geom_path;
            //std::string tess_path;
            unsigned int        maj_ver_v;
            unsigned int        min_ver_v;
            bool                has_vert_v;
            bool                has_frag_v;
            bool                has_geom_v;
            bool                has_tess_v;
            friend              class program;
        };
        
                                program( settings const& set = settings() );
                                ~program();
        void                    uniform( std::string const& name );
        void                    compile();
        void                    link();
        template< typename T >
        void                    load_uniform( std::string const& name,
                                              T const& val             );
        void                    use();
        friend std::ostream&    operator <<( std::ostream& out, program const& rhs );
        GLuint                  get_prog_ID() const { return prog_ID; }
    private:
        
        typedef
        std::map<std::string, GLint>    key_map;
        key_map*                        uniform_map;
        void                            compile( GLuint stage_ID,
                                                 std::string const& stage_path );
        std::string                     vert_path;
        std::string                     frag_path;
        std::string                     geom_path;
        GLuint                          vert_ID;
        GLuint                          frag_ID;
        GLuint                          geom_ID;
        GLuint                          tess_ID;
        GLuint                          prog_ID;
        unsigned int                    maj_ver;
        unsigned int                    min_ver;
        friend                          class video_system;
    };

    inline  program::settings::settings() :
                                vert_path( "" ),
                                frag_path( "" ),
                                geom_path( "" ),
                                maj_ver_v( 2 ),
                                min_ver_v( 0 ),
                                has_vert_v( true ),
                                has_frag_v( true ),
                                has_geom_v( false ),
                                has_tess_v( false )  {}
                                
    inline program::settings&   program::settings::maj_ver( unsigned int maj_ver )
    { maj_ver_v = maj_ver; return *this; }

    inline program::settings&   program::settings::min_ver( unsigned int min_ver )
    { min_ver_v = min_ver; return *this; }

    inline program::settings&   program::settings::has_vert()
    { has_vert_v = true; return *this; }

    inline program::settings&   program::settings::has_frag()
    { has_frag_v = true; return *this; }

    inline program::settings&   program::settings::has_geom()
    { has_geom_v = true; return *this; }

    inline program::settings&   program::settings::use_vert( std::string const& path )
    {
        vert_path = path;
        has_vert_v = true;
        return *this;
    }

    inline program::settings&   program::settings::use_frag( std::string const& path )
    {
        frag_path = path;
        has_frag_v = true;
        return *this;
    }

    inline program::settings&   program::settings::use_geom( std::string const& path )
    {
        geom_path = path;
        has_geom_v = true;
        return *this;
    }

    inline program::settings&   program::settings::no_vert()
    { has_vert_v = false; return *this; }

    inline program::settings&   program::settings::no_frag()
    { has_frag_v = false; return *this; }

    inline program::settings&   program::settings::no_geom()
    { has_geom_v = false; return *this; }
    
    template< typename T > inline
    void    program::load_uniform( std::string const& name,
                                   T const& val     )
    {
        throw std::invalid_argument( "No support for given type of uniform." );
    }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   float32 const& val  )
    { gl::Uniform1f( (*uniform_map)[name], val ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   float const& val  )
    { gl::Uniform1f( (*uniform_map)[name], val ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   vec2 const& val  )
    { gl::Uniform2f( (*uniform_map)[name], val[0], val[1] ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   vec3 const& val  )
    { gl::Uniform3f( (*uniform_map)[name], val[0], val[1], val[2] ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   vec4 const& val  )
    { gl::Uniform4f( (*uniform_map)[name], val[0], val[1], val[2], val[3] ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   int32 const& val  )
    { gl::Uniform1i( (*uniform_map)[name], val ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   int const& val  )
    { gl::Uniform1i( (*uniform_map)[name], val ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   ivec2 const& val  )
    { gl::Uniform2i( (*uniform_map)[name], val[0], val[1] ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   ivec3 const& val  )
    { gl::Uniform3i( (*uniform_map)[name], val[0], val[1], val[2] ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   ivec4 const& val  )
    { gl::Uniform4i( (*uniform_map)[name], val[0], val[1], val[2], val[3] ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   uint32 const& val  )
    { gl::Uniform1ui( (*uniform_map)[name], val ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   uint32_t const& val  )
    { gl::Uniform1ui( (*uniform_map)[name], val ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   uvec2 const& val  )
    { gl::Uniform2ui( (*uniform_map)[name], val[0], val[1] ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   uvec3 const& val  )
    { gl::Uniform3ui( (*uniform_map)[name], val[0], val[1], val[2] ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   uvec4 const& val  )
    { gl::Uniform4ui( (*uniform_map)[name], val[0], val[1], val[2], val[3] ); }
    
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   mat2 const& val         )
    { gl::UniformMatrix2fv( (*uniform_map)[name],
                            4, gl::FALSE_,
                            (GLfloat*) val.to_map().bytes ); }

    template<> inline
    void    program::load_uniform( std::string const& name,
                                   mat3 const& val         )
    { gl::UniformMatrix3fv( (*uniform_map)[name],
                            9, gl::FALSE_,
                            (GLfloat*) val.to_map().bytes ); }
                            
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   mat4 const& val         )
    { gl::UniformMatrix4fv( (*uniform_map)[name],
                            16, gl::FALSE_,
                            (GLfloat*) val.to_map().bytes ); }
                            
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   mat2x3 const& val         )
    { gl::UniformMatrix2x3fv( (*uniform_map)[name],
                              6, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
                            
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   mat3x2 const& val         )
    { gl::UniformMatrix3x2fv( (*uniform_map)[name],
                              6, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
                              
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   mat2x4 const& val         )
    { gl::UniformMatrix2x4fv( (*uniform_map)[name],
                              8, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
                            
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   mat4x2 const& val         )
    { gl::UniformMatrix4x2fv( (*uniform_map)[name],
                              8, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
                              
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   mat3x4 const& val         )
    { gl::UniformMatrix3x4fv( (*uniform_map)[name],
                              12, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
                            
    template<> inline
    void    program::load_uniform( std::string const& name,
                                   mat4x3 const& val         )
    { gl::UniformMatrix4x3fv( (*uniform_map)[name],
                              12, gl::FALSE_,
                              (GLfloat*) val.to_map().bytes ); }
    
    
}
#endif