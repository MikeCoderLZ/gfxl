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
            settings&       sub_ver( unsigned int sub_ver );
            settings&       ver( unsigned int maj_ver,
                                     unsigned int min_ver,
                                     unsigned int sub_ver = 0 );
            settings&       ver( version const& ver );
            settings&       core_profile();
            settings&       compatibility_profile();
            settings&       es_profile();
        private:
            unsigned int    maj_ver_v;
            unsigned int    min_ver_v;
            unsigned int    sub_ver_v;
            int             profile_v;
            friend class video_manager;
        };
        video_manager&                  initialize( video_manager::settings const& set =
                                                        video_manager::settings()        );
                                        ~video_manager();
        static video_manager&           get();
        version const&                  get_version() const;
        void                            attach_context( window const& window,
                                                        context& context );
        void                            activate_context( context& context );
        context const&                  get_active_context() const;
        context&                        get_active_context();
//         program&                        new_program( program::settings const& settings =
//                                                         program::settings() );
//         void                            del_program( program const& prgm );
        buffer&                         new_buffer( buffer::settings const& settings );
        void                            del_buffer( buffer const& buff );
        friend std::ostream&            operator <<( std::ostream& out,
                                                    video_manager const& rhs);
    private:
                                            video_manager();
        static video_manager* const         instance;
        version                             vid_ver;
//         bool                                owns( program const& prgm );
        bool                                owns( buffer const& buff );
        
        context*                            active_context;
        
//         typedef std::map<size_t, program*>  program_map;
//         program_map*                        programs;
//         size_t                              nxt_p_id;
        
        typedef std::map<size_t, buffer*>   buffer_map;
        buffer_map*                         buffers;
        size_t                              nxt_b_id;
        
        bool                                zombie;
    };


    
    inline  video_manager::settings::settings() :
                                        maj_ver_v( 1u ),
                                        min_ver_v( 4u ),
                                        sub_ver_v( 0u ),
                                        profile_v( SDL_GL_CONTEXT_PROFILE_CORE ) {}

    inline video_manager::settings&
    video_manager::settings::maj_ver( unsigned int maj_ver )
    { maj_ver_v = maj_ver; return *this; }

    inline video_manager::settings&
    video_manager::settings::min_ver( unsigned int min_ver )
    { min_ver_v = min_ver; return *this; }
    
    inline video_manager::settings&
    video_manager::settings::sub_ver( unsigned int sub_ver )
    { sub_ver_v = sub_ver; return *this; }
    
    inline video_manager::settings&
    video_manager::settings::ver( unsigned int maj_ver,
                                      unsigned int min_ver,
                                      unsigned int sub_ver )
    { 
        maj_ver_v = maj_ver;
        min_ver_v = min_ver;
        sub_ver_v = sub_ver;
        return *this;
    }
    
    inline video_manager::settings&
    video_manager::settings::ver( version const& ver )
    { 
        maj_ver_v = ver.maj_ver();
        min_ver_v = ver.min_ver();
        sub_ver_v = ver.sub_ver();
        return *this;
    }

    inline video_manager::settings&
    video_manager::settings::core_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_CORE; return *this; }

    inline video_manager::settings&
    video_manager::settings::compatibility_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY; return *this; }

    inline video_manager::settings&
    video_manager::settings::es_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_ES; return *this; }
    
    inline video_manager::video_manager() :
                            vid_ver ( 0, 0 ),
                            active_context( 0 ),
                            buffers( new buffer_map ),
                            nxt_b_id( 0 ),
                            zombie( false ) {}
                            
    inline video_manager&  video_manager::get()
    { return *video_manager::instance; }
    
    inline version const&  video_manager::get_version() const
    { return vid_ver; }
    
    inline  context const&    video_manager::get_active_context() const
    { return *(video_manager::instance->active_context); }

    inline  context&    video_manager::get_active_context()
    { return *(video_manager::instance->active_context); }

//     inline  bool    video_manager::owns( program const& prgm )
//     { return this == prgm.owner; }

    inline  bool    video_manager::owns( buffer const& buff )
    { return this == buff.owner; }

}

#endif