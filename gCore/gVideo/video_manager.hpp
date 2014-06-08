#ifndef VIDEO_MANAGER_HPP
#define VIDEO_MANAGER_HPP

namespace gfx {

    class video_manager {
    public:
        
        class settings {
        public:
            settings();
            settings&       maj_ver( unsigned int maj_ver );
            settings&       min_ver( unsigned int min_ver );
            settings&       version( unsigned int maj_ver,
                                     unsigned int min_ver );
            settings&       core_profile();
            settings&       compatibility_profile();
            settings&       es_profile();
        private:
            unsigned int    maj_ver_v;
            unsigned int    min_ver_v;
            int             profile_v;
            friend class video_manager;
        };
                                        video_manager( video_manager::settings const& set =
                                                        video_manager::settings() );
                                        ~video_manager();
        window&                         new_window( window::settings const& set =
                                                        window::settings(),
                                                    window::settings_3D const& set_3D =
                                                        window::settings_3D() 
                                                );
        void                            del_window( window const& wndw );
        context&                        new_context( window const& window,
                                                    context::settings const& settings = context::settings() );
        void                            del_context( context const& cntx );
        void                            attach_context( window const& window,
                                                        context& context );
        void                            activate_context( context& context );
        context const&                  get_active_context() const;
        context&                        get_active_context();
        program&                        new_program( program::settings const& settings =
                                                        program::settings() );
        void                            del_program( program const& prgm );
        buffer&                         new_buffer( buffer::settings const& settings );
        void                            del_buffer( buffer const& buff );
        friend std::ostream&            operator <<( std::ostream& out,
                                                    video_manager const& rhs);
    private:
        bool                                owns( window const& wndw );
        bool                                owns( context const& cntx );
        bool                                owns( program const& prgm );
        bool                                owns( buffer const& buff );
        
        typedef std::map<size_t, window*>   window_map;
        window_map*                         windows;
        size_t                              nxt_w_id;
        
        typedef std::map<size_t, context*>  context_map;
        context_map*                        contexts;
        size_t                              nxt_c_id;
        context*                            active_context;
        
        typedef std::map<size_t, program*>  program_map;
        program_map*                        programs;
        size_t                              nxt_p_id;
        
        typedef std::map<size_t, buffer*>   buffer_map;
        buffer_map*                         buffers;
        size_t                              nxt_b_id;
        
        bool                                zombie;
    };


    
    inline  video_manager::settings::settings() :
                                        maj_ver_v( 1u ),
                                        min_ver_v( 4u ),
                                        profile_v( SDL_GL_CONTEXT_PROFILE_CORE ) {}

    inline video_manager::settings&
    video_manager::settings::maj_ver( unsigned int maj_ver )
    { maj_ver_v = maj_ver; return *this; }

    inline video_manager::settings&
    video_manager::settings::min_ver( unsigned int min_ver )
    { min_ver_v = min_ver; return *this; }

    inline video_manager::settings&
    video_manager::settings::core_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_CORE; return *this; }

    inline video_manager::settings&
    video_manager::settings::compatibility_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY; return *this; }

    inline video_manager::settings&
    video_manager::settings::es_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_ES; return *this; }

    inline  context const&    video_manager::get_active_context() const
    { return *active_context; }

    inline  context&    video_manager::get_active_context()
    { return *active_context; }

    inline  bool    context::is_active() const
    { return (*this) == owner->get_active_context(); }

    inline  bool    video_manager::owns( window const& wndw )
    { return this == wndw.owner; }

    inline  bool    video_manager::owns( context const& cntx )
    { return this == cntx.owner; }

    inline  bool    video_manager::owns( program const& prgm )
    { return this == prgm.owner; }

    inline  bool    video_manager::owns( buffer const& buff )
    { return this == buff.owner; }

}

#endif