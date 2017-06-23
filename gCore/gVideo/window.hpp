#ifndef G_WINDOW_HPP
#define G_WINDOW_HPP

namespace gfx {

    
    /**
     * \class gfx::window window.hpp "gCore/gVideo/window.hpp"
     * \brief Represents a system window.
     * Full control over the window's settings are provided by the usual
     * \ref gfx::window::settings "settings" system. Windows require the
     * \ref gfx::video_system "video system" to be initialized, though
     * all versions of OpenGL are allowed. A working window is needed
     * for a \ref gfx::context "context" to be used for rendering.
     * \see gfx::video_system
     * \see gfx::context
     */
    class window {
    public:
        /**
         * \class gfx::window::settings window.hpp "gCore/gVideo/window.hpp"
         * \brief The settings object for the \ref gfx::window "window" class.
         * Mutators can be chained.
         * \see gfx::window
         * \see gfx::window::settings_3D
         */
        class settings {
            public:
                                    settings();
                settings&           title( std::string const& title );
                settings&           x_pos( int xp );
                settings&           y_pos( int yp );
                settings&           position( int xp,
                                            int yp );
                settings&           center_x();
                settings&           center_y();
                settings&           center();
                settings&           width( int dw );
                settings&           height( int dh );
                settings&           dimensions( int dw,
                                                int dh );
                settings&           corners( int ul_x,
                                            int ul_y,
                                            int lr_x,
                                            int lr_y );
                settings&           corners( ivec2 const& ulc,
                                            ivec2 const& lrc );
                settings&           maximized();
                settings&           minimized();
                settings&           resizable();
                settings&           lock_size();
                settings&           has_3D();
                settings&           visible();
                settings&           no_border();
                settings&           has_border();
                settings&           fullscreen();
                settings&           grab_input();
                settings&           has_focus();
                settings&           no_focus();
            private:
                std::string         title_v;
                ivec2               pos_v;
                ivec2               ulc_v;
                int                 width_v;
                int                 height_v;
                bool                center_on_x;
                bool                center_on_y;
                bool                minimized_v;
                bool                maximized_v;
                bool                fullscreen_v;
                bool                resizable_v;
                bool                uses_opengl;
                bool                visible_v;
                bool                has_border_v;
                bool                has_focus_v;
                bool                grab_input_v;
                friend              class video_system;
                friend              class window;
        };
        
        /**
         * \class gfx::window::setings_3D window.hpp "gCore/gVideo/window.hpp"
         * \brief A settings object for \ref gfx::window "windows" conerned
         * with 3D rendering settings.
         * Distinct from \ref gfx::window::settings "settings", settings_3D
         * keeps the OpenGL relevent settings separate. This may be useful
         * in some use cases, such as parsing high level graphical setting
         * data in an application and not wanting to drag around the regular
         * settings object in the process.
         * \see gfx::window
         * \see gfx::window::settings
         */
        class settings_3D {
            public:
                                    settings_3D();
                settings_3D&        r_bits( unsigned int b );
                settings_3D&        g_bits( unsigned int b );
                settings_3D&        b_bits( unsigned int b );
                settings_3D&        a_bits( unsigned int b );
                settings_3D&        framebuffer_bits( unsigned int b );
                settings_3D&        doublebuffered();
                settings_3D&        not_doublebuffered();
                settings_3D&        depth_bits( unsigned int b );
                settings_3D&        stencil_bits( unsigned int b );
                settings_3D&        r_accumulator_bits( unsigned int b );
                settings_3D&        g_accumulator_bits( unsigned int b );
                settings_3D&        b_accumulator_bits( unsigned int b );
                settings_3D&        a_accumulator_bits( unsigned int b );
                settings_3D&        in_stereo();
                settings_3D&        multisample( unsigned int samples );
                settings_3D&        force_hardware();
                settings_3D&        force_software();
        //         settings_3D&        version( unsigned int maj_ver,
        //                                      unsigned int min_ver );
            private:
                unsigned int        r_bits_v;
                unsigned int        g_bits_v;
                unsigned int        b_bits_v;
                unsigned int        a_bits_v;
                unsigned int        framebuffer_bits_v;
                bool                doublebuffered_v;
                unsigned int        depth_bits_v;
                unsigned int        stencil_bits_v;
                unsigned int        r_accumulator_bits_v;
                unsigned int        g_accumulator_bits_v;
                unsigned int        b_accumulator_bits_v;
                unsigned int        a_accumulator_bits_v;
                bool                in_stereo_v;
                bool                multisample_v;
                unsigned int        samples_v;
                bool                force_hw_v;
                bool                force_sw_v;
        //         unsigned int        maj_ver_v;
        //         unsigned int        min_ver_v;
                friend class        video_system;
                friend              class window;
        };
        
                                window( settings const& set = settings(),
                                        settings_3D const& set_3D = settings_3D() );
                                ~window();
        void                    swap();
        bool                    operator ==( window const& rhs ) const;
        std::string             title() const;
        void                    title( std::string const& ttl );
        int                     x_pos() const;
        void                    x_pos( int xp );
        int                     y_pos() const;
        void                    y_pos( int yp );
        ivec2                   position() const;
        void                    position( int xp, int yp );
        void                    position( ivec2 const& pos );
        bool                    is_x_centered() const;
        void                    center_x();
        bool                    is_y_centered() const;
        void                    center_y();
        int                     width() const;
        void                    width( int dw );
        int                     height() const;
        void                    height( int dh );
        ivec2                   dimensions() const;
        void                    dimensions( int dw,
                                            int dh );
        void                    dimensions( ivec2 const& dim );
        ivec2                   ul_corner() const;
        ivec2                   lr_corner() const;
        void                    corners( int ulx,
                                        int uly,
                                        int lrx,
                                        int lry );
        void                    corners( ivec2 const& ulc,
                                        ivec2 const& lrc );
        bool                    is_maximized() const;
        void                    maximize();
        bool                    is_minimized() const;
        void                    minimize();
        bool                    is_resizable() const;
    //     void                    make_resizable();
    //     void                    lock_size();
        bool                    has_3D() const;
        bool                    is_visible() const;
        void                    make_visible();
        void                    make_hidden();
        bool                    has_border() const;
    //     bool                    is_fullscreen() const;
    // //     void                    make_fullscreen();
    //     bool                    has_focus() const;
    // //     void                    take_focus();
        
        friend                  std::ostream& operator <<( std::ostream& out,
                                                        window const& rhs );
        
    private:
        std::string             title_str;
        SDL_Window*             sys_window;
        friend                  class video_system;
        friend                  class context;
    };

    /**
     * \brief Output \ref gfx::window "window" state information to the given
     * output stream. Intended mostly for debugging and logging use.
     * \param out The output stream
     * \param rhs The window object to output information from
     */
    std::ostream&   operator <<( std::ostream& out, window const& rhs );

    /**
     * \brief Construct a default \ref gfx::window::settings "settings" object.
     * The default values for a \ref gfx::window "window" are essentially
     * useless, consisting of the bare necessary graphical features and
     * zeroed out dimensions.
     */
    inline  window::settings::settings() :
                title_v         ("untitled"),
                pos_v           ( 0, 0 ),
                ulc_v           ( 0, 0 ),
                width_v         (0),          height_v        (0),
                center_on_x     (true),       center_on_y     (true),
                minimized_v     (false),      maximized_v     (false),
                fullscreen_v    (false),
                resizable_v     (false),
                uses_opengl     (false),
                visible_v       (true),
                has_border_v    (true),
                has_focus_v     (false),
                grab_input_v    (false)
    {
        SDL_Rect bounds;
        SDL_GetDisplayBounds( 0, &bounds );
        width_v = bounds.w / 2;
        height_v = bounds.h / 2;
        pos_v[0] = bounds.w / 2;
        pos_v[1] = bounds.h / 2;
        ulc_v[0] = width_v / -2 + pos_v[0];
        ulc_v[1] = height_v / -2 + pos_v[1];
    };
    /**
     * \brief Set the \ref gfx::window "window's" title to the given string.
     * \param title The title of the window
     */
    inline  window::settings&     window::settings::title( std::string const& title )
    { title_v = title; return *this; }
    /**
     * \brief Set the \ref gfx::window "window's" x position to the given value.
     * \param xp The x position of the window, in pixels
     */
    inline  window::settings&     window::settings::x_pos( int xp )
    {   pos_v[0] = xp;
        ulc_v[0] = width_v / -2 + xp;
        center_on_x = false;
        return *this; }
    /**
     * \brief Set the \ref gfx::window "window's" y position to the given value.
     * \param yp The y position of the window, in pixels
     */    
    inline  window::settings&     window::settings::y_pos( int yp )
    {   pos_v[1] = yp;
        ulc_v[1] = height_v / -2 + yp;
        center_on_y = false;
        return *this; }
    /**
     * \brief Set the \ref gfx::window "window's" x and y position to the given
     * values.
     * \param xp The x position of the window, in pixels
     * \param yp The y position of the window, in pixels
     */
    inline  window::settings&     window::settings::position( int xp,
                                                            int yp )
    {   pos_v[0] = xp;
        ulc_v[0] = width_v / -2 + xp;
        pos_v[1] = yp;
        ulc_v[1] = height_v / -2 + yp;
        
        center_on_x = false;
        center_on_y = false;
        return *this; }
    /**
     * \brief Set the \ref gfx::window "window's" width to the given value.
     * \param dw The width of the window, in pixels
     */ 
    inline  window::settings&     window::settings::width( int dw )
    {
        width_v = dw;
        ulc_v[0] = dw / -2 + pos_v[0];
        
        return *this;
    }
    /**
     * \brief Set the \ref gfx::window "window's" height to the given value.
     * \param dh The height of the window, in pixels
     */ 
    inline  window::settings&     window::settings::height( int dh )
    {
        height_v = dh;
        ulc_v[1] = dh / -2 + pos_v[1];
        return *this;    
    }
    /**
     * \brief Set the \ref gfx::window "window's" width and height to the given
     * values.
     * \param dw The width of the window, in pixels
     * \param dh The height of the window, in pixels
     */ 
    inline  window::settings&     window::settings::dimensions( int dw,
                                                                int dh )
    { width_v = dw; height_v = dh; return *this; }
    /**
     * \brief Set the \ref gfx::window "window's" height to the given value.
     * \param dh The height of the window, in pixels
     */
    inline  window::settings&     window::settings::corners( int ul_x,
                                                            int ul_y,
                                                            int lr_x,
                                                            int lr_y )
    {
        ulc_v[0] = ul_x;
        ulc_v[1] = ul_y;
        width_v = lr_x - ul_x;
        height_v = lr_y - ul_y;
        center_on_x = false;
        center_on_y = false;
        return *this;
    }
    /**
     * \brief Set the \ref gfx::window "window's" location and dimensions by
     * specifying the upper left and lower right corners.
     * \param ulc The upper left corner of the window
     * \param lrc The lower right corner of the window
     */
    inline  window::settings&     window::settings::corners( ivec2 const& ulc,
                                                            ivec2 const& lrc )
    {
        ulc_v[0] = ulc[0];
        ulc_v[1] = ulc[1];
        width_v = lrc[0] - ulc[0];
        height_v = lrc[1] - ulc[1];
        center_on_x = false;
        center_on_y = false;
        return *this;
    }
    /**
     * \brief Set the \ref gfx::window "window" to be centered on the x axis.
     * \see gfx::window::settings::center_y()
     * \see gfx::window::settings::center()
     */
    inline  window::settings&     window::settings::center_x()
    {   center_on_x = true;
        return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to be centered on the y axis.
     * \see gfx::window::settings::center_x()
     * \see gfx::window::settings::center()
     */
    inline  window::settings&     window::settings::center_y()
    {   center_on_y = true;
        return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to be centered on both axes.
     * \see gfx::window::settings::center_x()
     * \see gfx::window::settings::center_y()
     */
    inline  window::settings&     window::settings::center()
    {   center_on_x = true;
        center_on_y = true;
        return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to be maximized.
     * \see gfx::window::settings::minimized()
     * \see gfx::window::settings::fullscreen()
     */
    inline  window::settings&     window::settings::maximized()
    {   maximized_v = true;
        minimized_v = false;
        fullscreen_v = false;
        return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to be minimized.
     * \see gfx::window::settings::maximized()
     * \see gfx::window::settings::fullscreen()
     */            
    inline  window::settings&     window::settings::minimized()
    {   minimized_v = true;
        maximized_v = false;
        fullscreen_v = false;
        return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to be fullscreen.
     * That is, the window will take up the whole screen and not have any
     * borders.
     * \see gfx::window::settings::maximized()
     * \see gfx::window::settings::minimized()
     */
    inline  window::settings&     window::settings::fullscreen()
    {   fullscreen_v = true;
        minimized_v = false;
        maximized_v = false;
        return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to be resizable.
     * That is, the user can change the size of the window.
     * \see gfx::window::settings::lock_size()
     */
    inline  window::settings&     window::settings::resizable()
    { resizable_v = true; return *this; }
    /**
     * \brief Set the \ref gfx::window "window's" size to be static.
     * That is, the user can not change the size of the window.
     * \see gfx::window::settings::resizable()
     */
    inline  window::settings&     window::settings::lock_size()
    { resizable_v = false; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to accept an OpenGL context.
     * \see gfx::window:settings_3D
     */
    inline  window::settings&     window::settings::has_3D()
    { uses_opengl = true; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to be visible.
     */
    inline  window::settings&     window::settings::visible()
    { visible_v = true; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to have no border.
     * \see gfx::window::settings::has_border()
     */
    inline  window::settings&     window::settings::no_border()
    { has_border_v = false; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to have a border.
     * \see gfx::window::settings::no_border()
     */
    inline  window::settings&     window::settings::has_border()
    { has_border_v = true; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to be created with focus.
     * \see gfx::window::settings::no_focus()
     */
    inline  window::settings&     window::settings::has_focus()
    { has_focus_v = true; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to be created without focus.
     * \see gfx::window::settings::has_focus()
     */
    inline  window::settings&     window::settings::no_focus()
    { has_focus_v = false; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to grab input from the user.
     */
    inline  window::settings&     window::settings::grab_input()
    { grab_input_v = true; return *this; }
    /**
     * \brief Construct a default \ref gfx::window::settings_3D "3D settings"
     * object.
     * The default 3D settings are the basics: four chanel, 8bit color with
     * doublebuffering.
     */
    inline  window::settings_3D::settings_3D() :
                                    r_bits_v             ( 8 ),
                                    g_bits_v             ( 8 ),
                                    b_bits_v             ( 8 ),
                                    a_bits_v             ( 8 ),
                                    framebuffer_bits_v   ( 0 ),
                                    doublebuffered_v     ( true ),
                                    depth_bits_v         ( 16 ),
                                    stencil_bits_v       ( 0 ),
                                    r_accumulator_bits_v ( 0 ),
                                    g_accumulator_bits_v ( 0 ),
                                    b_accumulator_bits_v ( 0 ),
                                    a_accumulator_bits_v ( 0 ),
                                    in_stereo_v          ( false ),
                                    multisample_v        ( false ),
                                    samples_v            ( 0 ),
                                    force_hw_v           ( false ),
                                    force_sw_v           ( false )/*,
                                    maj_ver_v            ( 1 ),
                                    min_ver_v            ( 4 )*/
                                    {}
    /**
     * \brief Set the number of bits in the red chanel of the \ref gfx::window "window".
     * \see gfx::window::settings3D::g_bits()
     * \see gfx::window::settings3D::b_bits()
     * \see gfx::window::settings3D::a_bits()
     */
    inline window::settings_3D&     window::settings_3D::r_bits( unsigned int b )
    { r_bits_v = b; return *this; }
    /**
     * \brief Set the number of bits in the green chanel of the \ref gfx::window "window".
     * \see gfx::window::settings3D::r_bits()
     * \see gfx::window::settings3D::b_bits()
     * \see gfx::window::settings3D::a_bits()
     */
    inline window::settings_3D&     window::settings_3D::g_bits( unsigned int b )
    { g_bits_v = b; return *this; }
    /**
     * \brief Set the number of bits in the blue chanel of the \ref gfx::window "window".
     * \see gfx::window::settings3D::r_bits()
     * \see gfx::window::settings3D::g_bits()
     * \see gfx::window::settings3D::a_bits()
     */
    inline window::settings_3D&     window::settings_3D::b_bits( unsigned int b )
    { b_bits_v = b; return *this; }
    /**
     * \brief Set the number of bits in the alpha chanel of the \ref gfx::window "window".
     * \see gfx::window::settings3D::r_bits()
     * \see gfx::window::settings3D::g_bits()
     * \see gfx::window::settings3D::b_bits()
     */
    inline window::settings_3D&     window::settings_3D::a_bits( unsigned int b )
    { a_bits_v = b; return *this; }
    /**
     * \brief Set the number of bits in the the \ref gfx::window "window's" framebuffer.
     * \todo Review this function for what it actually does and how that
     * effects contexts.
     */
    inline window::settings_3D&     window::settings_3D::framebuffer_bits( unsigned int b )
    { framebuffer_bits_v = b; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to use doublebuffering.
     * \see gfx::window::settings_3D::not_doublebuffered()
     */
    inline window::settings_3D&     window::settings_3D::doublebuffered()
    { doublebuffered_v = true; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to not use doublebuffering.
     * \see gfx::window::settings_3D::doublebuffered()
     */
    inline window::settings_3D&     window::settings_3D::not_doublebuffered()
    { doublebuffered_v = false; return *this; }
    /**
     * \brief Set the number of bits in the depth chanel of the \ref gfx::window "window".
     * \see gfx::window::settings3D::stencil_bits()
     */
    inline window::settings_3D&     window::settings_3D::depth_bits( unsigned int b )
    { depth_bits_v = b; return *this; }
    /**
     * \brief Set the number of bits in the stencil chanel of the \ref gfx::window "window".
     * \see gfx::window::settings3D::depth_bits()
     */
    inline window::settings_3D&     window::settings_3D::stencil_bits( unsigned int b )
    { stencil_bits_v = b; return *this; }
    /**
     * \brief Set the number of bits in the red accumulator chanel of the
     * \ref gfx::window "window".
     * \see gfx::window::settings3D::g_accumulator_bits()
     * \see gfx::window::settings3D::b_accumulator_bits()
     * \see gfx::window::settings3D::a_accumulator_bits()
     */
    inline window::settings_3D&     window::settings_3D::r_accumulator_bits( unsigned int b )
    { r_accumulator_bits_v = b; return *this; }
    /**
     * \brief Set the number of bits in the green accumulator chanel of the
     * \ref gfx::window "window".
     * \see gfx::window::settings3D::r_accumulator_bits()
     * \see gfx::window::settings3D::b_accumulator_bits()
     * \see gfx::window::settings3D::a_accumulator_bits()
     */
    inline window::settings_3D&     window::settings_3D::g_accumulator_bits( unsigned int b )
    { g_accumulator_bits_v = b; return *this; }
    /**
     * \brief Set the number of bits in the blue accumulator chanel of the
     * \ref gfx::window "window".
     * \see gfx::window::settings3D::r_accumulator_bits()
     * \see gfx::window::settings3D::g_accumulator_bits()
     * \see gfx::window::settings3D::a_accumulator_bits()
     */
    inline window::settings_3D&     window::settings_3D::b_accumulator_bits( unsigned int b )
    { b_accumulator_bits_v = b; return *this; }
    /**
     * \brief Set the number of bits in the alpha accumulator chanel of the
     * \ref gfx::window "window".
     * \see gfx::window::settings3D::r_accumulator_bits()
     * \see gfx::window::settings3D::g_accumulator_bits()
     * \see gfx::window::settings3D::b_accumulator_bits()
     */
    inline window::settings_3D&     window::settings_3D::a_accumulator_bits( unsigned int b )
    { a_accumulator_bits_v = b; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to be a stereo one, for actual
     * 3D viewing.
     */
    inline window::settings_3D&     window::settings_3D::in_stereo()
    { in_stereo_v = false; return *this; }
    /**
     * \brief Set the \ref gfx::window "window" to use multisampling.
     * This is required for multisampling to be active in an associated
     * \ref gfx::context "context".
     */
    inline window::settings_3D&     window::settings_3D::multisample( unsigned int samples )
    {
        multisample_v = true;
        samples_v = samples;
        return *this;
    }
    /**
     * \brief Force the \ref gfx::window "window" to use hardware rendering.
     * \see gfx::window::settings_3D::force_software()
     */
    inline window::settings_3D&     window::settings_3D::force_hardware()
    { force_hw_v = true; return *this; }
    /**
     * \brief Force the \ref gfx::window "window" to use software emulation.
     * \see gfx::window::settings_3D::force_hardware()
     */
    inline window::settings_3D&     window::settings_3D::force_software()
    { force_sw_v = true; return *this; }

    // inline window::settings_3D&     window::settings_3D::version( unsigned int maj_ver,
    //                                                               unsigned int min_ver )
    // {
    //     maj_ver_v = maj_ver;
    //     min_ver_v = min_ver;
    //     return *this;
    // }
    /**
     * \brief Test whether the given \ref gfx::window "window" is the
     * same window as this one.
     */
    inline  bool    window::operator ==( window const& rhs ) const
    { return this->sys_window == rhs.sys_window; }

}
#endif