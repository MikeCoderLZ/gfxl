#ifndef PROGRAM_HPP
#define PROGRAM_HPP

namespace gfx {

    class compilation_error : public std::logic_error {
    public:
        explicit compilation_error( std::string const& msg ) : logic_error( msg ) {};
    };
                                
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
        void                    compile();
        void                    link();
        void                    use();
        friend std::ostream&    operator <<( std::ostream& out, program const& rhs );
        GLuint                  get_prog_ID() const { return prog_ID; }
    private:
        void                    compile( GLuint stage_ID, std::string const& stage_path );
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
        friend                  class video_manager;
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
}
#endif