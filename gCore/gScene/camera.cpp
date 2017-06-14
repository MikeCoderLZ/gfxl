#include <cmath>
#include <iostream>


#include "camera.hpp"
#include "../gMath/op.hpp"
namespace gfx {

    camera::camera() : view_changed (true),
                       view () {};
                       
    camera::~camera() {}
    
    void    camera::upload_uniform( program& prgm,
                                    std::string const& name )
    {
        check_program( prgm );
        std::string mod_name = name;
        mod_name += ".view";
        prgm.upload_uniform( mod_name, view );
    }
    
    mat4 const&     camera::view_matrix()
    {
        if ( view_changed ) {
            this->update_view();
        }
        return view;
    }
    
    proj_cam::proj_cam( settings const& set ) :
                        camera(),
                        pos ( set.pos_v ),
                        look ( set.look_v ),
                        up ( set.up_v ),
                        fov_vert ( set.fov_vert_v ),
                        aspect ( set.aspect_v ),
                        near ( set.near_v ),
                        far ( set.far_v ),
                        perspect ( mat4::perspective( fov_vert,
                                                      aspect,
                                                      near,
                                                      far      ) ),
                        proj_changed ( false ) { update_view(); }
    proj_cam::~proj_cam() {}
    
    proj_cam&     proj_cam::position( vec3 const& point )
    { pos = point; view_changed = true; return *this; }
    
    proj_cam&     proj_cam::look_at( vec3 const& point )
    { look = point; view_changed = true; return *this; }
    
    proj_cam&     proj_cam::upward( vec3 const& dir )
    { up = dir; view_changed = true; return *this; }
    
    proj_cam&     proj_cam::field_of_view( d_angle const& vert )
    {
        fov_vert = vert;
        view_changed = true;
        proj_changed = true;
        return *this;
    }
    
    proj_cam&     proj_cam::aspect_ratio( double ar )
    {
        aspect = ar;
        view_changed = true;
        proj_changed = true;
        return *this;
    }
    
    proj_cam&     proj_cam::near_plane( double np )
    {
        near = np;
        view_changed = true;
        proj_changed = true;
        return *this;
    }
    
    proj_cam&     proj_cam::far_plane( double fp )
    {
        far = fp;
        view_changed = true;
        proj_changed = true;
        return *this;
    }
    
    void    proj_cam::update_view()
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
        if ( proj_changed ) {
            perspect = mat4::perspective( fov_vert,
                                          aspect,
                                          near,
                                          far      );
            proj_changed = false;
        }
        view =   perspect
               * (   test_orient
                   * mat4::translate(-pos) ).ortho();
        view_changed = false;
    }
    
    ortho_cam::ortho_cam( settings const& set ) :
                         camera(),
                         pos ( set.pos_v ),
                         look ( set.look_v ),
                         up ( set.up_v ),
                         aspect ( set.aspect_v ),
                         scale_v ( set.scale_v ),
                         far ( set.far_v ),
                         scale_m ( mat4::identity() ),
                         volume_changed ( true ) {}
                         
    ortho_cam::~ortho_cam() {}
    
    ortho_cam&     ortho_cam::position( vec3 const& point )
    { pos = point; view_changed = true; return *this; }
    
    ortho_cam&     ortho_cam::look_at( vec3 const& point )
    { look = point; view_changed = true; return *this; }
    
    ortho_cam&     ortho_cam::upward( vec3 const& dir )
    { up = dir; view_changed = true; return *this; }
    
    ortho_cam&     ortho_cam::aspect_ratio( double ar )
    {
        aspect = ar;
        view_changed = true;
        volume_changed = true;
        return *this;
    }
    
    ortho_cam&     ortho_cam::scale( double scl )
    { 
        scale_v = scl;
        view_changed = true;
        volume_changed = true;
        return *this;
    }
    
    ortho_cam&     ortho_cam::far_plane( double fp )
    {
        far = fp;
        view_changed = true;
        volume_changed = true;
        return *this;
    }
    
    void    ortho_cam::update_view()
    {
        vec3 look_vec ( (look - pos).norm() ); 
        vec3 new_up = ortho( up, look_vec );
        mat4 orient = homogenize( mat3::column_vectors( cross( look_vec, new_up ),
                                                        new_up,
                                                        -look_vec                  ).norm().invert() );
        if ( volume_changed ) {
            scale_m(0,0) = scale_v / aspect;
            scale_m(1,1) = scale_v;
            scale_m(2,2) = 1.0f / far;
            volume_changed = false;
        }
        
        view =   scale_m
               * (   orient
                   * mat4::translate(-pos) ).ortho();
    }
    
    process_cam::process_cam( settings const& set ) :
                               camera(),
                               mask ( set.mask_v ),
                               screen ( set.screen_v ),
                               clip_m ( mat4::identity() ),
                               clip_changed ( true ){}
                               
    process_cam::~process_cam() {}
    
    process_cam&    process_cam::mask_region( vec2 const& ul_corner,
                                              vec2 const& lr_corner )
    {
        mask[0] = ul_corner[0];
        mask[1] = ul_corner[1];
        mask[2] = lr_corner[0];
        mask[3] = lr_corner[1];
        view_changed = true;
        clip_changed = true;
        return *this;
    }
    
    process_cam&    process_cam::screen_region( vec2 const& ul_corner,
                                              vec2 const& lr_corner )
    {
        screen[0] = ul_corner[0];
        screen[1] = ul_corner[1];
        screen[2] = lr_corner[0];
        screen[3] = lr_corner[1];
        view_changed = true;
        clip_changed = true;
        return *this;
    }
    
    void    process_cam::update_view()
    {
        // Oh, this is totally broken. Masking can't work that way,
        // unless I add some other voodoo.
        if ( clip_changed ) {
            float mx_c = 0.5f * (mask[0] + mask[2]);
            float my_c = 0.5f * (mask[1] + mask[3]);
            float mx_s = 2.0 / abs(mask[2] - mask[0]);
            float my_s = 2.0 / abs(mask[1] - mask[3]);
            
            float sx_c = 0.5f * (screen[0] + screen[2]);
            float sy_c = 0.5f * (screen[1] + screen[3]);
            float sx_s = 0.5f * abs(screen[2] - screen[0]);
            float sy_s = 0.5f * abs(screen[1] - screen[3]);
            
            clip_m.components( mx_s*sx_s, 0.0f,      0.0f, sx_c - mx_c*sx_s,
                               0.0f,      my_s*sy_s, 0.0f, sy_c - my_c*sy_s,
                               0.0f,      0.0f,      1.0f,  0.0f,
                               0.0f,      0.0f,      0.0f,  1.0f                );
            clip_changed = false;
        }
        view = clip_m;
    }

}