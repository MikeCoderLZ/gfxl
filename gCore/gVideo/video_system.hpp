#ifndef VIDEO_SYSTEM_HPP
#define VIDEO_SYSTEM_HPP

namespace gfx {
    
    /** 
     * \class gfx::video_system video_system.hpp "gCore/gVideo/video_system.hpp"
     * \brief Maintains static information and configuration details of the
     * graphics system.
     * 
     * The video_system class is a singleton class that initializes the
     * underlying (OpenGL and SDL) graphics systems and provides management
     * of rendering contexts. Initialization must be done manually, at which
     * time important program configuration details like OpenGL version are
     * set using the member class \ref gfx::video_system::settings
     * "gfx::video_system::settings".
     * 
     */
    
    class video_system {
    public:
        /**
         * \class gfx::video_system::settings video_system.hpp "gCore/gVideo/video_system.hpp"
         * \brief Configuration class for \ref gfx::video_system "video_system".
         * 
         * The settings member of video_system is a public interface for
         * configuring the video system when it is initialized. It's mutator
         * member functions can be chained; subsequent calls to these functions
         * overwrite changes created by previous calls.
         * 
         */
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
            friend          class video_system;
        };
        video_system&                   initialize( video_system::settings const& set =
                                                    video_system::settings()        );
                                        ~video_system();
        static video_system&            get();
        version const&                  get_version() const;
        bool                            context_present() const;
        void                            check_acceleration_error( std::string const& tag );
        void                            attach_context( window const& window,
                                                        context& context );
        void                            activate_context( context& context );
        context const&                  get_active_context() const;
        context&                        get_active_context();
        friend std::ostream&            operator <<( std::ostream& out,
                                                    video_system const& rhs);
    private:
        static video_system* const      instance;
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


    /**
     * \brief Construct a \ref gfx::video_system::settings "settings" object with
     * default values.
     * 
     * The default settings for the \ref gfx::video_system "gfx::video system" are to
     * use OpenGL 1.4 with the core profile.
     */
    inline  video_system::settings::settings() :
                                        maj_ver_v( 1u ),
                                        min_ver_v( 4u ),
                                        sub_ver_v( 0u ),
                                        profile_v( SDL_GL_CONTEXT_PROFILE_CORE ) {}

    /**
     * \brief Set the OpenGL major version to the given value.
     * 
     * The first number in the version number of OpenGL is the major version.
     * There is no bounds checking at this time, so entering a number that is
     * not 1, 2, 3, or 4 will result in a silent intialization error.
     * @param maj_ver
     * @return This settings object
     * @see gfx::video_system::settings::ver()
     */
    inline video_system::settings&
    video_system::settings::maj_ver( unsigned int maj_ver )
    { maj_ver_v = maj_ver; return *this; }
    /**
     * \brief Set the OpenGL minor version to the given value.
     * 
     * The second number in the version number of OpenGL is the minor version.
     * There is no bounds checking at this time, so entering a number that when
     * combined with the current major version that is not valid will result in
     * a silent intialization error.
     * @param min_ver
     * @return This settings object
     */
    inline video_system::settings&
    video_system::settings::min_ver( unsigned int min_ver )
    { min_ver_v = min_ver; return *this; }
    /**
     * \brief Set the OpenGL subversion to the given value.
     * 
     * The rarely used third number in the version number of OpenGL is the
     * subversion version. There is no bounds checking at this time, so entering
     * a number that when combined with the current major and minor version that
     * is not valid will result in a silent intialization error.
     * @param sub_ver
     * @return This settings object
     */
    inline video_system::settings&
    video_system::settings::sub_ver( unsigned int sub_ver )
    { sub_ver_v = sub_ver; return *this; }
    /**
     * \brief Set the OpenGL version to the given values.
     * 
     * Set all three version numbers at the same time. There is no bounds
     * checking at this time, so entering a fully specified version
     * number that is not valid will result in a silent intialization error.
     * @param maj_ver
     * @param min_ver
     * @param sub_ver
     * @return This settings object
     */
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
    /**
     * \brief Set the OpenGL version to the given values.
     * 
     * Set all three version numbers at the same time using a \ref gfx::version
     * "gfx::version" object; all the valid versions of OpenGL are provided as
     * globals by the gfx::version class, so for readability this member
     * function is recommended.
     * 
     * There is no bounds checking at this time, so constructing a gfx::version
     * object with an invalid version number will result in a silent
     * intialization error.
     * @param ver
     * @return This settings object
     */
    inline video_system::settings&
    video_system::settings::ver( version const& ver )
    { 
        maj_ver_v = ver.maj_ver();
        min_ver_v = ver.min_ver();
        sub_ver_v = ver.sub_ver();
        return *this;
    }
    /**
     * \brief Set the video system to use the core OpenGL profile.
     * 
     * The core OpenGL profile is the profile associated with the core
     * functionality for the given OpenGL version; for versions after 2.0
     * this means that the old drawing functions are depracted and not
     * available for use and instead the \ref gfx::program "shader" pipeline
     * should be used.
     * @return This settings object
     * @see gfx::video_system::settings::compatibility_profile()
     * @see gfx::video_system::settings::es_profile()
     */
    inline video_system::settings&
    video_system::settings::core_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_CORE; return *this; }
    /**
     * \brief Set the video system to use the compatibility OpenGL profile.
     * 
     * The compatibility OpenGL profile is the profile associated with the
     * functionality for the given OpenGL version and any deprecated or
     * removed functionality; versions after 2.0 will provide the
     * \ref gfx::program "shader" pipeline but still have the old drawing
     * functions available for use.
     * @return This settings object
     * @see gfx::video_system::settings::core_profile()
     * @see gfx::video_system::settings::es_profile()
     */
    inline video_system::settings&
    video_system::settings::compatibility_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY; return *this; }
    /**
     * \brief Set the video system to use the ES OpenGL profile.
     * 
     * The ES OpenGL profile is the profile associated with mobile development.
     * Check OpenGL documention for details on what functionality is available.
     * @return This settings object
     * @see gfx::video_system::settings::core_profile()
     * @see gfx::video_system::settings::compatibility_profile()
     */
    inline video_system::settings&
    video_system::settings::es_profile()
    { profile_v = SDL_GL_CONTEXT_PROFILE_ES; return *this; }
    /**
     * \brief Construct a \ref gfx::video_system "video_system" object.
     * 
     * This private constructor is used to build the singleton instance whose
     * settings are then set by a call to \ref gfx::video_system::initialize()
     * "initialize()".
     * @see gfx::video_system::initialize()
     */
    inline video_system::video_system() :
                            vid_ver ( 0, 0 ),
                            contexts ( new context_set() ),
                            active_context( 0 ),
                            zombie ( false ) {}
    /**
     * \brief Add the given \ref gfx::context "context" to the
     * \ref gfx::video_system "video system's" internal collection of managed
     * contexts.
     * 
     * This is a private interface member for use by the context class. It adds
     * the given context to the internal collection of contexts the video system
     * manages.
     * @param cntx
     * @see gfx::sivdeo_system::unregister_context()
     */
    inline void     video_system::register_context( context* cntx )
    { contexts->insert( cntx ); }
    /**
     * \brief Remove the given \ref gfx::context "context" from the
     * \ref gfx::video_system "video system's" internal collection of managed
     * contexts.
     * 
     * This is a private interface member for use by the context class. It
     * removes the given context from the internal collection of contexts
     * the video system manages. It is used when a context destructs, cleaning
     * up after itself should the context be the active one and assigning some
     * other context to the active status. This may cause subtle bugs, and
     * before using a particular context it should be activated first.
     * @param cntx
     * @see gfx::video_system::activate_context()
     * @see gfx::ivdeo_system::register_context()
     */
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
  
  /**
   * \brief Return the single instance of the \ref gfx::video_system
   * "video system".
   * 
   * Since the video_system is a singleton, you must use video_system::get()
   * to access it in order to query it for the current version or a
   * \ref gfx::window "window" or \ref gfx::context "context".
   * @return The single instance of the video system
   */
    inline video_system&  video_system::get()
    { return *video_system::instance; }
    /**
     * \brief Return the current version of the \ref gfx::video_system
     * "video system".
     * 
     * Query the video system for the current OpenGL version, in the form of
     * a \ref gfx::version "version" object. You will need to use
     * \ref gfx::video_system::get() "video_system::get()" to get the video
     * system instance in order to querey it.
     * @return The OpenGL version being used
     * @see gfx::video_system::get()
     */
    inline version const&  video_system::get_version() const
    { return vid_ver; }
    /**
     * \brief Return whether or not there is a \ref gfx::context "context"
     * present and active to use for rendering.
     * 
     * Query the video system to see if there is a currently active context
     * that can be used for OpenGL rendering. You will need to use
     * \ref gfx::video_system::get() "video_system::get()" to get the video
     * system instance in order to querey it.
     * @return Whether or not there is a context ready to use
     * @see gfx::video_system::get_active_context()
     * @see gfx::video_system::get()
     */
    inline bool     video_system::context_present() const
    {
        if ( active_context != 0 ) {
            return true;
        }
        return false;
    }
    /**
     * \brief Return the active \ref gfx::context "context".
     * 
     * Query the video system for the currently active context. You will need
     * to use \ref gfx::video_system::get() "video_system::get()" to get the
     * video system instance in order to querey it.
     * @exception gfx::initialization_error If there is no active context, a
     * gfx::initialization exception will be thrown.
     * @return Whether or not there is a context ready to use
     * @see gfx::video_system::get_context_present()
     * @see gfx::video_system::get()
     */
    inline  context const&    video_system::get_active_context() const
    {
        if ( context_present() ) {
            return *active_context;
        }
        throw initialization_error( "Cannot provide active context: no context present" );
        
    }
    /**
     * \brief Return the active \ref gfx::context "context".
     * 
     * Query the video system for the currently active context. You will need
     * to use \ref gfx::video_system::get() "video_system::get()" to get the
     * video system instance in order to querey it.
     * @exception gfx::initialization_error If there is no active context, a
     * gfx::initialization exception will be thrown.
     * @return Whether or not there is a context ready to use
     * @see gfx::video_system::get_context_present()
     * @see gfx::video_system::get()
     */
    inline  context&    video_system::get_active_context()
    {
        if ( context_present() ) {
            return *active_context;
        }
        throw initialization_error( "Cannot provide active context: no context present" );
    }
}

#endif