#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../gVideo/video.hpp"
#include "../gMath/datatype.hpp"
#include "../gMath/constant.hpp"

namespace gfx {
 
    class camera {
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
            friend class camera;
        };
        
                        camera( settings const& set = settings() );
        mat4 const&     view_matrix() const;
        camera&         look_at( vec3 const& point);
        camera&         upward( vec3 const& dir );
    protected:
        vec3            pos;
        vec3            look;
        vec3            up;
        qutn            orient;
        d_angle         fov_vert;
        double          aspect;
        double          near;
        double          far;
        mat4            perspect;
        mat4            view;
        void            update_view();
    };
    
    inline camera::settings::settings() :
                                pos_v ( 0.0f, 0.0f,  0.0f ),
                                look_v ( 0.0f, 0.0f, -1.0f ),
                                up_v ( 0.0f, 1.0f, 0.0f ),
                                fov_vert_v ( d_angle::in_degs( 135.0 ) ),
                                aspect_v ( 1.33 ),
                                near_v ( 0.01 ),
                                far_v ( 100.0 ) {}
                                
    inline camera::settings&    camera::settings::position( vec3 const& pos )
    { pos_v = pos; return *this; }
    
    inline camera::settings&    camera::settings::look_at( vec3 const& point )
    { look_v = point; return *this; }
    
    inline camera::settings&    camera::settings::upward( vec3 const& up )
    { up_v = up; return *this; }
    
    inline camera::settings&    camera::settings::field_of_view( d_angle const& fov_vert )
    { fov_vert_v = fov_vert; return *this; }
    
    inline camera::settings&    camera::settings::aspect_ratio( double aspect )
    { aspect_v = aspect; return *this; }
    
    inline camera::settings&    camera::settings::near_plane( double near )
    { near_v = near; return *this; }
    
    inline camera::settings&    camera::settings::far_plane( double far )
    { far_v = far; return *this; }
    
    inline mat4 const&     camera::view_matrix() const
    { return view; }
}

#endif