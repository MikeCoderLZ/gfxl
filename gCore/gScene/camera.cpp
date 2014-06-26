#include <cmath>
#include <iostream>


#include "camera.hpp"
#include "../gMath/op.hpp"
namespace gfx {

    camera::camera( settings const& set ) :
                        pos ( set.pos_v ),
                        look ( set.look_v ),
                        up ( set.up_v ),
                        orient ( 0.0f, 0.0f, 0.0f, 1.0f ),
                        fov_vert ( set.fov_vert_v ),
                        aspect ( set.aspect_v ),
                        near ( set.near_v ),
                        far (set.far_v ),
                        perspect ( mat4::perspective( fov_vert,
                                                      aspect,
                                                      near,
                                                      far      ) ),
                        view ()
    { this->update_view(); }
    
    camera&     camera::look_at( vec3 const& point )
    {
        look = point;
        update_view();
        return *this;
    }
    
    void    camera::update_view()
    {
        qutn rot_to_foc ( 0.0f, 0.0f, 0.0f, 1.0f );
        vec3 look_vec ( (look - pos).norm() );
        vec3 rest_axis ( 0.0f, 0.0f, -1.0f );
        if ( look_vec != rest_axis ) {
            // ugh, this again.
            // Okay, first, get an axis to rotate the camera from
            // 'rest' (looking down into -z) to be aligned with
            // the direction we are supposed to look in
            vec3 look_pivot = rest_axis;
            look_pivot.cross( look_vec );
            look_pivot.norm();
            // Now we construct a rotation that rotates the camera
            // to look in the direction of the look vector
            rot_to_foc = qutn::rotation( look_pivot,
                                         d_angle::in_rads( acos( dot( rest_axis,
                                                                      look_vec ) ) ) );
            rot_to_foc.norm();
            orient = rot_to_foc;
        }
        
        qutn rot_up ( 0.0f, 0.0f, 0.0f, 1.0f );
        vec3 init_up ( 0.0f, 1.0f, 0.0f );
        if ( init_up != up ) {
            // Now we need to rotate the camera around its relative Z axis
            // so that up is correlated with the given up vector.
            // First we make the up vector orthogonal to the look vector
            vec3 relative_up = ortho( up, look_vec ).norm();
            // Then we get the current, relative up vector
            init_up = rot_to_foc.rotate( init_up );
            // Then construct a rotation about the look vector
            // to orient the camera's up with the desired up direction
            qutn rot_up = qutn::rotation( look_vec,
                                          d_angle::in_rads( acos( dot( init_up,
                                                                       relative_up ) ) ) );
            rot_up.norm();
            orient = orient * rot_up;
        }
        view =   mat4::translate( -pos )
               * mat4::rotation( -orient );
        view.norm();
        view = perspect * view;
    }

}