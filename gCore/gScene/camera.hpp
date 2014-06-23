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
            settings&   location( vec3 const& loc );
            settings&   focus( vec3 const& foc );
            settings&   up( vec3 const& up );
            settings&   field_of_view( d_angle const& fov_vert );
            settings&   aspect_ratio( double aspect );
            settings&   near_plane( double near );
            settings&   far_plane( double far );
        private:
            vec3        loc_v;
            vec3        foc_v;
            vec3        up_v;
            d_angle     fov_vert_v;
            double      aspect_v;
            double      near_v;
            double      far_v;
            friend class camera;
        };
        
                        camera( settings const& set = settings() );
        mat4 const&     view_matrix() const;
    protected:
        vec3            loc;
        vec3            focus;
        vec3            up;
        qutn            orient;
        d_angle         fov_vert;
        double          aspect;
        double          near;
        double          far;
        mat4            perspect;
        mat4            view;
    };
    
    inline camera::settings::settings() :
                                loc_v ( 0.0f, 0.0f,  0.0f ),
                                foc_v ( 0.0f, 0.0f, -1.0f ),
                                up_v ( 0.0f, 1.0f, 0.0f ),
                                fov_vert_v ( d_angle::in_degs( 135.0 ) ),
                                aspect_v ( 1.33 ),
                                near_v ( 0.0 ),
                                far_v ( 100.0 ) {}
                                
    inline camera::settings&    camera::settings::location( vec3 const& loc )
    { loc_v = loc; return *this; }
    
    inline camera::settings&    camera::settings::focus( vec3 const& foc )
    { foc_v = foc; return *this; }
    
    inline camera::settings&    camera::settings::up( vec3 const& up )
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