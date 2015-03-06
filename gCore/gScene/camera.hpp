#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../gVideo/video.hpp"
#include "../gMath/datatype.hpp"
#include "../gMath/constant.hpp"

namespace gfx {

    class camera {
    public:
                        camera();
                        ~camera();
        mat4 const&     view_matrix();
    protected:
        bool            view_changed;
        mat4            view;
        virtual void    update_view() = 0;
    };
    
    /**
     * An easy to use perspective camera: put it somewhere, tell it
     * what to look at, and specify what up is, and it does the rest.
     * "proj" stand for "projection".
     */
    class proj_cam : public camera {
    public:
        
        class settings {
        public:
                        settings();
            settings&   position( vec3 const& pos );
            settings&   look_at( vec3 const& point );
            settings&   upward( vec3 const& up );
            settings&   field_of_view( d_angle const& fov_vert );
            settings&   aspect_ratio( double aspect );
            settings&   near_plane( double near );
            settings&   far_plane( double far );
        private:
            vec3        pos_v;
            vec3        look_v;
            vec3        up_v;
            d_angle     fov_vert_v;
            double      aspect_v;
            double      near_v;
            double      far_v;
            friend class proj_cam;
        };
        
                        proj_cam( settings const& set = settings() );
                        ~proj_cam();
        proj_cam&       position( vec3 const& point );
        proj_cam&       look_at( vec3 const& point);
        proj_cam&       upward( vec3 const& dir );
        proj_cam&       field_of_view( d_angle const& vert );
        proj_cam&       aspect_ratio( double ar );
        proj_cam&       near_plane( double np );
        proj_cam&       far_plane( double fp );
    protected:
        vec3            pos;
        vec3            look;
        vec3            up;
        d_angle         fov_vert;
        double          aspect;
        double          near;
        double          far;
        mat4            perspect;
        bool            proj_changed;
        virtual void    update_view();
    };
    
    inline proj_cam::settings::settings() :
                                pos_v ( 0.0f, 0.0f,  0.0f ),
                                look_v ( 0.0f, 0.0f, -1.0f ),
                                up_v ( 0.0f, 1.0f, 0.0f ),
                                fov_vert_v ( d_angle::in_degs( 135.0 ) ),
                                aspect_v ( 1.33 ),
                                near_v ( 0.01 ),
                                far_v ( 100.0 ) {}
                                
    inline proj_cam::settings&    proj_cam::settings::position( vec3 const& pos )
    { pos_v = pos; return *this; }
    
    inline proj_cam::settings&    proj_cam::settings::look_at( vec3 const& point )
    { look_v = point; return *this; }
    
    inline proj_cam::settings&    proj_cam::settings::upward( vec3 const& up )
    { up_v = up; return *this; }
    
    inline proj_cam::settings&    proj_cam::settings::field_of_view( d_angle const& fov_vert )
    { fov_vert_v = fov_vert; return *this; }
    
    inline proj_cam::settings&    proj_cam::settings::aspect_ratio( double aspect )
    { aspect_v = aspect; return *this; }
    
    inline proj_cam::settings&    proj_cam::settings::near_plane( double near )
    { near_v = near; return *this; }
    
    inline proj_cam::settings&    proj_cam::settings::far_plane( double far )
    { far_v = far; return *this; }
    
    /**
     * An orthographic camera. Functions just like a proj_cam, but
     * with no persepctive.
     */    
    class ortho_cam : public camera {
    public:
        class settings {
        public:
                        settings();
            settings&   position( vec3 const& pos );
            settings&   look_at( vec3 const& point );
            settings&   upward( vec3 const& up );
            settings&   aspect_ratio( double ar );
            settings&   scale( double scl );
            settings&   far_plane( double fp );
        private:
            vec3        pos_v;
            vec3        look_v;
            vec3        up_v;
            double      aspect_v;
            double      scale_v;
            double      far_v;
            friend      class ortho_cam;
        };
                        ortho_cam( settings const& set = settings() );
                        ~ortho_cam();
        ortho_cam&      position( vec3 const& point );
        ortho_cam&      look_at( vec3 const& point );
        ortho_cam&      upward( vec3 const& dir );
        ortho_cam&      aspect_ratio( double ar );
        ortho_cam&      scale( double scl );
        ortho_cam&      far_plane( double fp );
    protected:
        vec3            pos;
        vec3            look;
        vec3            up;
        double          aspect;
        double          scale_v;
        double          far;
        mat4            scale_m;
        bool            volume_changed;
        virtual void    update_view();
    };
    
    inline ortho_cam::settings::settings() :
                                 pos_v ( 0.0f, 0.0f,  0.0f ),
                                 look_v ( 0.0f, 0.0f, -1.0f ),
                                 up_v ( 0.0f, 1.0f, 0.0f ),
                                 aspect_v ( 1.33 ),
                                 scale_v ( 1.0 ),
                                 far_v ( 100.0 ) {}
    
    inline ortho_cam::settings&    ortho_cam::settings::position( vec3 const& pos )
    { pos_v = pos; return *this; }
    
    inline ortho_cam::settings&    ortho_cam::settings::look_at( vec3 const& point )
    { look_v = point; return *this; }
    
    inline ortho_cam::settings&    ortho_cam::settings::upward( vec3 const& up )
    { up_v = up; return *this; }
    
    inline ortho_cam::settings&    ortho_cam::settings::aspect_ratio( double ar )
    { aspect_v = ar; return *this; }
    
    inline ortho_cam::settings&    ortho_cam::settings::scale( double scl )
    { scale_v = scl; return *this; }
    
    inline ortho_cam::settings&    ortho_cam::settings::far_plane( double fp )
    { far_v = fp; return *this; }
    
    /**
     * A camera specifically for 'process work', or compositing and
     * rendering textures to the screen. The mask region is the sub
     * area of the plane [-1,1][-1,1] to project and the screen
     * region is the sub area of the renderbuffer to project to.
     */
    class process_cam : public camera {
    public:
        class settings {
        public:
                            settings();
            settings&       mask_region( vec2 const& ul_corner,
                                         vec2 const& lr_corner );
            settings&       screen_region( vec2 const& ul_corner,
                                           vec2 const& lr_corner );
        private:
            vec4            mask_v;
            vec4            screen_v;
            friend class    process_cam;
        };
                        process_cam( settings const& set = settings() );
                        ~process_cam();
        process_cam&    mask_region( vec2 const& ul_corner,
                                     vec2 const& lr_corner );
        process_cam&    screen_region( vec2 const& ul_corner,
                                       vec2 const& lr_corner );
    protected:
        vec4            mask;
        vec4            screen;
        mat4            clip_m;
        bool            clip_changed;
        virtual void    update_view();
    };
    
    inline process_cam::settings::settings() :
                                    mask_v( -1.0f, 1.0f, 1.0f, -1.0f ),
                                    screen_v( -1.0f, 1.0f, 1.0f, -1.0f ) {}
                                    
    inline process_cam::settings&
    process_cam::settings::mask_region( vec2 const& ul_corner,
                                        vec2 const& lr_corner )
    {
        mask_v[0] = ul_corner[0];
        mask_v[1] = ul_corner[1];
        mask_v[2] = lr_corner[0];
        mask_v[3] = lr_corner[1];
        return *this;
    }
    
    inline process_cam::settings&
    process_cam::settings::screen_region( vec2 const& ul_corner,
                                          vec2 const& lr_corner )
    {
        screen_v[0] = ul_corner[0];
        screen_v[1] = ul_corner[1];
        screen_v[2] = lr_corner[0];
        screen_v[3] = lr_corner[1];
        return *this;
    }
}

#endif