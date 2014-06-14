#ifndef G_WINDOW_HPP
#define G_WINDOW_HPP

namespace gfx {

    class window {
    public:
        
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

    std::ostream&   operator <<( std::ostream& out, window const& rhs );

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
                
    inline  window::settings&     window::settings::title( std::string const& title )
    { title_v = title; return *this; }

    inline  window::settings&     window::settings::x_pos( int xp )
    {   pos_v[0] = xp;
        ulc_v[0] = width_v / -2 + xp;
        center_on_x = false;
        return *this; }
        
    inline  window::settings&     window::settings::y_pos( int yp )
    {   pos_v[1] = yp;
        ulc_v[1] = height_v / -2 + yp;
        center_on_y = false;
        return *this; }
        
    inline  window::settings&     window::settings::position( int xp,
                                                            int yp )
    {   pos_v[0] = xp;
        ulc_v[0] = width_v / -2 + xp;
        pos_v[1] = yp;
        ulc_v[1] = height_v / -2 + yp;
        
        center_on_x = false;
        center_on_y = false;
        return *this; }
        
    inline  window::settings&     window::settings::width( int dw )
    {
        width_v = dw;
        ulc_v[0] = dw / -2 + pos_v[0];
        
        return *this;
    }

    inline  window::settings&     window::settings::height( int dh )
    {
        height_v = dh;
        ulc_v[1] = dh / -2 + pos_v[1];
        return *this;    
    }

    inline  window::settings&     window::settings::dimensions( int dw,
                                                                int dh )
    { width_v = dw; height_v = dh; return *this; }
    
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

    inline  window::settings&     window::settings::center_x()
    {   center_on_x = true;
        return *this; }
        
    inline  window::settings&     window::settings::center_y()
    {   center_on_y = true;
        return *this; }
        
    inline  window::settings&     window::settings::center()
    {   center_on_x = true;
        center_on_y = true;
        return *this; }

    inline  window::settings&     window::settings::maximized()
    {   maximized_v = true;
        minimized_v = false;
        fullscreen_v = false;
        return *this; }
                
    inline  window::settings&     window::settings::minimized()
    {   minimized_v = true;
        maximized_v = false;
        fullscreen_v = false;
        return *this; }

    inline  window::settings&     window::settings::fullscreen()
    {   fullscreen_v = true;
        minimized_v = false;
        maximized_v = false;
        return *this; }

    inline  window::settings&     window::settings::resizable()
    { resizable_v = true; return *this; }

    inline  window::settings&     window::settings::lock_size()
    { resizable_v = false; return *this; }

    inline  window::settings&     window::settings::has_3D()
    { uses_opengl = true; return *this; }

    inline  window::settings&     window::settings::visible()
    { visible_v = true; return *this; }

    inline  window::settings&     window::settings::no_border()
    { has_border_v = false; return *this; }

    inline  window::settings&     window::settings::has_border()
    { has_border_v = true; return *this; }

    inline  window::settings&     window::settings::has_focus()
    { has_focus_v = true; return *this; }

    inline  window::settings&     window::settings::no_focus()
    { has_focus_v = false; return *this; }

    inline  window::settings&     window::settings::grab_input()
    { grab_input_v = true; return *this; }

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
                                                
    inline window::settings_3D&     window::settings_3D::r_bits( unsigned int b )
    { r_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::g_bits( unsigned int b )
    { g_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::b_bits( unsigned int b )
    { b_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::a_bits( unsigned int b )
    { a_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::framebuffer_bits( unsigned int b )
    { framebuffer_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::doublebuffered()
    { doublebuffered_v = true; return *this; }

    inline window::settings_3D&     window::settings_3D::not_doublebuffered()
    { doublebuffered_v = false; return *this; }

    inline window::settings_3D&     window::settings_3D::depth_bits( unsigned int b )
    { depth_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::stencil_bits( unsigned int b )
    { stencil_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::r_accumulator_bits( unsigned int b )
    { r_accumulator_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::g_accumulator_bits( unsigned int b )
    { g_accumulator_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::b_accumulator_bits( unsigned int b )
    { b_accumulator_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::a_accumulator_bits( unsigned int b )
    { a_accumulator_bits_v = b; return *this; }

    inline window::settings_3D&     window::settings_3D::in_stereo()
    { in_stereo_v = false; return *this; }

    inline window::settings_3D&     window::settings_3D::multisample( unsigned int samples )
    {
        multisample_v = true;
        samples_v = samples;
        return *this;
    }

    inline window::settings_3D&     window::settings_3D::force_hardware()
    { force_hw_v = true; return *this; }

    inline window::settings_3D&     window::settings_3D::force_software()
    { force_sw_v = true; return *this; }

    // inline window::settings_3D&     window::settings_3D::version( unsigned int maj_ver,
    //                                                               unsigned int min_ver )
    // {
    //     maj_ver_v = maj_ver;
    //     min_ver_v = min_ver;
    //     return *this;
    // }

    inline  bool    window::operator ==( window const& rhs ) const
    { return this->sys_window == rhs.sys_window; }

}
#endif