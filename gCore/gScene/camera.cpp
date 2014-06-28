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
    
    camera&     camera::upward( vec3 const& dir )
    {
        up = dir;
        update_view();
        return *this;
    }
    
    void    camera::update_view()
    {
        // We could leave this to the norm() call later,
        // but if the vector is of any significant size
        // it will introduce serious errors into the generated
        // basis.
        vec3 look_vec ( (look - pos).norm() ); 
        vec3 new_up = ortho( up, look_vec );
        mat4 test_orient = homogenize( mat3::column_vectors( cross( look_vec, new_up ),
                                                             new_up,
                                                            -look_vec                  ).norm().invert() );
        view =   perspect
               * (   test_orient
                   * mat4::translate(-pos) ).ortho();
    }

}