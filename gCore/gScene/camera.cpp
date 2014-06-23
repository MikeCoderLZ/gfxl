#include <cmath>

#include "camera.hpp"
#include "../gMath/op.hpp"
namespace gfx {

    camera::camera( settings const& set ) :
                        loc ( set.loc_v ),
                        focus ( set.foc_v ),
                        up ( set.up_v ),
                        orient (),
                        fov_vert ( set.fov_vert_v ),
                        aspect ( set.aspect_v ),
                        near ( set.near_v ),
                        far (set.far_v ),
                        perspect (),
                        view ()
    {
        // ugh, this again.
        // Okay, first, get an axis to rotate the camera from
        // 'rest' (looking down into -z) to be aligned with
        // the direction we are supposed to look in
        vec3 look_vec ( (focus - loc).norm() );
        vec3 rest_axis ( 0.0f, 0.0f, -1.0f );
        vec3 look_pivot = rest_axis;
        look_pivot.cross( look_vec ).norm();
        // Now we construct a rotation that rotates the camera
        // to look in the direction of the look vector
        qutn rot_to_foc = qutn::rotation( look_pivot,
                                          d_angle::in_rads( acos( dot( rest_axis,
                                                                       look_vec ) ) ) );
        // Now we need to rotate the camera around its relative Z axis
        // so that up is correlated with the given up vector.
        // First we make the up vector orthogonal to the look vector
        vec3 relative_up = ortho( up, look_vec ).norm();
        // Then we get the current, relative up vector
        vec3 current_up = rot_to_foc.rotate( vec3(0.0f, 1.0f, 0.0f) );
        // Then construct a rotation about the look vector
        // to orient the camera's up with the desired up direction
        qutn rot_up = qutn::rotation( look_vec,
                                      d_angle::in_rads( acos( dot( current_up,
                                                              relative_up ) ) ) );
        orient = rot_to_foc * rot_up;
        
        perspect = mat4::perspective( fov_vert.to_rads(),
                                      aspect,
                                      near,
                                      far );
        view =   perspect
               * mat4::translate( -loc )
               * mat4::rotation( -orient );
    }

}