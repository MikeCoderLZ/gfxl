#ifndef VIDEO_MANAGER_HPP
#define VIDEO_MANAGER_HPP

namespace gfx {
    
    class video_system {
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
            friend class video_system;
        };
        video_system&                  initialize( video_system::settings const& set =
                                                        video_system::settings()        );
                                        ~video_system();
        static video_system&            get();
        version const&                  get_version() const;
        bool                            context_present() const;
        void                            attach_context( window const& window,
                                                        context& context );
        void                            activate_context( context& context );
        context const&                  get_active_context() const;
        context&                        get_active_context();
        friend std::ostream&            operator <<( std::ostream& out,
                                                    video_system const& rhs);
    private:
        static video_system* const     instance;
        version                         vid_ver;
        typedef std::set<context*>      context_set;
        context_set*                    contexts;
        context*                        active_context;  
        bool                            zombie;
        
                                        video_system();
        void                            register_context( context* cntx );
        void                            unregister_context( context* cntx );
        friend                          class context;
    };


    
    inline  video_system::settings::settings() :
                                        maj_ver_v( 1u ),
                                        min_ver_v( 4u ),
                                        sub_ver_v( 0u ),
                                        profile_v( SDL_GL_CONTEXT_PROFILE_CORE ) {}

    inline video_system::settings&
    video_system::settings::maj_ver( unsigned int maj_ver )
    { maj_ver_v = maj_ver; return *this; }

    inline video_system::settings&
    video_system::settings::min_ver( unsigned int min_ver )
    { min_ver_v = min_ver; return *this; }
    
    inline video_system::settings&
    video_system::settings::sub_ver( unsigned int sub_ver )
    { sub_ver_v = sub_ver; return *this; }
    
    inline video_system::settings&
    video_system::settings::ver( unsigned int maj_ver,
                                      unsigned int min_ver,
                                      unsigned int sub_ver )
    { 
        maj_ver_v = maj_ver;
        min_ver_v = min_ver;
        sub_ver_v = sub_ver;
        return *this;
    }
    
    inline video_system::settings&
    video_system::settings::ver( version const& ver )
    { 
        maj_ver_v = ver.maj_ver();
        min_ver_v = ver.min_ver();
        sub_ver_v = ver.sub_ver();
        return *this;
    }

    inline video_system::settings&
    video_system::settings::core_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_CORE; return *this; }

    inline video_system::settings&
    video_system::settings::compatibility_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY; return *this; }

    inline video_system::settings&
    video_system::settings::es_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_ES; return *this; }
    
    inline video_system::video_system() :
                            vid_ver ( 0, 0 ),
                            contexts ( new context_set() ),
                            active_context( 0 ),
                            zombie( false ) {}
                            
    inline void     video_system::register_context( context* cntx )
    { contexts->insert( cntx ); }
    inline void     video_system::unregister_context( context* cntx )
    {
        context_set::iterator e = contexts->find( cntx );
        if ( e != contexts->end() ) {
            // The context IS in this set
            if ( cntx == active_context ) {
                // If it is also the active context, we need to reseat
                // the active context
                if ( contexts->size() == 1 ) {
                    // If there is only one context, then the pointer must
                    // be assigned null
                    active_context = 0;
                } else if ( e == --(contexts->end()) ) {
                    // If the context is the last in the set, then we need
                    // need to back track
                    active_context = *(--e);
                    ++e;
                } else {
                    // Otherwise, we can forward track
                    active_context = *(++e);
                    --e;
                }
            }
            // Now we can erase the pointer from the set
            contexts->erase( e );
        }
    }
                            
    inline video_system&  video_system::get()
    { return *video_system::instance; }
    
    inline version const&  video_system::get_version() const
    { return vid_ver; }
    
    inline bool     video_system::context_present() const
    {
        if ( active_context != 0 ) {
            return true;
        }
        return false;
    }
    
    inline  context const&    video_system::get_active_context() const
    {
        if ( context_present() ) {
            return *active_context;
        }
        throw initialization_error( "Cannot provide active context: no context present" );
        
    }

    inline  context&    video_system::get_active_context()
    {
        if ( context_present() ) {
            return *active_context;
        }
        throw initialization_error( "Cannot provide active context: no context present" );
    }

}

#endif