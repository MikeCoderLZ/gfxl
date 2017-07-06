#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>

#include "../gVideo/video.hpp"
#include "../gMath/datatype.hpp"
#include "../gMath/constant.hpp"
#include "uniform.hpp"

namespace gfx {

    /*
     * struct camera {
     *      mat4    view;
     * }
     */
    /**
     * \class gfx::camera camera.hpp "gCore/gScene/camera.hpp"
     * \brief A base class for cameras.
     * 
     * Cameras need only implement the why the view matrix is updated.
     */
    class camera: public uniform {
    public:
                        camera();
                        ~camera();
        virtual void    upload_uniform( program& prgm,
                                        std::string const& name );
        mat4 const&     view_matrix();
    protected:
        bool            view_changed;
        mat4            view;
        virtual void    update_view() = 0;
    };
    
    /**
     * \class gfx::proj_cam camera.hpp "gCore/gScene/camera.hpp"
     * \brief A directable projection camera.
     * 
     * Put it somewhere, tell it what to look at, and specify what up is,
     * and it does the rest.
     * 
     * \todo Ummm, chouldn't proj_changed just be view_changed? Review this.
     */
    /* 
     * struct proj_cam {
     *      mat4    view;
     * }
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
    /**
     * \brief Construct a new default projection camera settings object.
     * 
     * The default pjection camera is positioned at the origin, looking
     * down the negative z-axis with the positive y-axis as the up
     * direction. The vertical field of view is 135 degrees, the near
     * plane is 0.01 units in front of the camera and the far plane is
     * at 100 units. Lastly, the aspect ratio is 1.
     */
    inline proj_cam::settings::settings() :
                                pos_v ( 0.0f, 0.0f,  0.0f ),
                                look_v ( 0.0f, 0.0f, -1.0f ),
                                up_v ( 0.0f, 1.0f, 0.0f ),
                                fov_vert_v ( d_angle::in_degs( 135.0 ) ),
                                aspect_v ( 1.0 ),
                                near_v ( 0.01 ),
                                far_v ( 100.0 ) {}
    /**
     * \brief Set the new projection camera's position.
     * \param pos The new projection camera's position.
     * \return This settings object
     */
    inline proj_cam::settings&    proj_cam::settings::position( vec3 const& pos )
    { pos_v = pos; return *this; }
    /**
     * \brief Set the point the new projection camera looks at.
     * \param point The point the new projection camera looks at.
     * \return This settings object
     */
    inline proj_cam::settings&    proj_cam::settings::look_at( vec3 const& point )
    { look_v = point; return *this; }
    /**
     * \brief Set the what new projection camera considers 'up'.
     * \param up The 'up' vector of the camera.
     * \return This settings object
     */
    inline proj_cam::settings&    proj_cam::settings::upward( vec3 const& up )
    { up_v = up; return *this; }
    /**
     * \brief Set the new projection camera's vertical field of view.
     * \param fov_vert The new projection camera's vertical field of view.    
     * \return This settings object
     * \todo Should this use the vertical field of view? I feel like the
     * horizontal fov is more useful.
     */
    inline proj_cam::settings&    proj_cam::settings::field_of_view( d_angle const& fov_vert )
    { fov_vert_v = fov_vert; return *this; }
    /**
     * \brief Set the new projection camera's aspect ratio.
     * \param aspect The new projection camera's aspect ratio.
     * \return This settings object
     */
    inline proj_cam::settings&    proj_cam::settings::aspect_ratio( double aspect )
    { aspect_v = aspect; return *this; }
    /**
     * \brief Set the new projection camera's near clipping plane.
     * \param near The new projection camera's near clipping plane.
     * \return This settings object
     */
    inline proj_cam::settings&    proj_cam::settings::near_plane( double near )
    { near_v = near; return *this; }
    /**
     * \brief Set the new projection camera's far clipping plane.
     * \param pos The new projection camera's far clipping plane.
     * \return This settings object
     */
    inline proj_cam::settings&    proj_cam::settings::far_plane( double far )
    { far_v = far; return *this; }
    
    /**
     * \class gfx::ortho_cam camera.hpp "gCore/gScene/camera/hpp"
     * \brief An orthographic camera.
     * 
     * Functions just like a proj_cam, but with no persepctive, instead
     * using a scaling factor.
     */
    /*
     * struct ortho_cam {
     *      mat4    view;
     * 
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
    /**
     * \brief Construct a default orthogrpahic camera settings object.
     * 
     * The default settins for an orthographic camera are to be
     * positioned at the origin, looking down the negative z-axis
     * with the y-axis designated as 'up'. The aspect ratio is 1,
     * the scale is 1, and the far clipping plane is at 100.
     */
    inline ortho_cam::settings::settings() :
                                 pos_v ( 0.0f, 0.0f,  0.0f ),
                                 look_v ( 0.0f, 0.0f, -1.0f ),
                                 up_v ( 0.0f, 1.0f, 0.0f ),
                                 aspect_v ( 1.0 ),
                                 scale_v ( 1.0 ),
                                 far_v ( 100.0 ) {}
    /**
     * \brief Set the new orthographic camera's position.
     * \param pos The new orthographic camera's position.
     * \return This orthographic camera settings object
     */
    inline ortho_cam::settings&    ortho_cam::settings::position( vec3 const& pos )
    { pos_v = pos; return *this; }
    /**
     * \brief Set the point the new orthographic camera looks at.
     * \param point The point the new orthographic camera looks at.
     * \return This settings object
     */
    inline ortho_cam::settings&    ortho_cam::settings::look_at( vec3 const& point )
    { look_v = point; return *this; }
    /**
     * \brief Set the what new orthographic camera considers 'up'.
     * \param up The 'up' vector of the camera.
     * \return This settings object
     */
    inline ortho_cam::settings&    ortho_cam::settings::upward( vec3 const& up )
    { up_v = up; return *this; }
    /**
     * \brief Set the new orthographic camera's aspect ratio.
     * \param aspect The new orthographic camera's aspect ratio.
     * \return This settings object
     */
    inline ortho_cam::settings&    ortho_cam::settings::aspect_ratio( double ar )
    { aspect_v = ar; return *this; }
    /**
     * \brief Set the new orthographic camera's scale.
     * \param scl The new orthographic camera's scale.
     * \return This settings object
     */
    inline ortho_cam::settings&    ortho_cam::settings::scale( double scl )
    { scale_v = scl; return *this; }
    /**
     * \brief Set the new orthographic camera's far clipping plane.
     * \param pos The new orthographic camera's far clipping plane.
     * \return This settings object
     */
    inline ortho_cam::settings&    ortho_cam::settings::far_plane( double fp )
    { far_v = fp; return *this; }
    
    /**
     * \class gfx::process_cam camera.hpp "gCore/gScene/camera.hpp"
     * \brief A camera for 'process work'.
     * 
     * That is, compositing and rendering mattes and elements to the screen.
     * The mask region is the sub area of the plane [-1,1][-1,1] to project
     * and the screen region is the sub area of the renderbuffer to project to.
     */ 
     /* struct process_cam {
     *      mat4    view;
     * }
     * 
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
    /**
     * \brief Construct a default process camera settings object.
     * 
     * The default settings for a process camera is to mask the entire
     * screen area, which is on ([-1.0,1.0],[-1.0,1.0]).
     */
    inline process_cam::settings::settings() :
                                    mask_v( -1.0f, 1.0f, 1.0f, -1.0f ),
                                    screen_v( -1.0f, 1.0f, 1.0f, -1.0f ) {}
    /**
     * \brief Set the mask region of the new process camera.
     * \param ul_corner The upper left corner
     * \param lr_corner The lower right corner
     * \return This settings object
     */
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
    /**
     * \brief Set the screen region.
     * \param ul_corner The upper left corner
     * \param lr_corner The lower right corner
     * \return This settings object
     */
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