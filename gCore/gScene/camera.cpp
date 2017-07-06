 #include <cmath>
#include <iostream>


#include "camera.hpp"
#include "../gMath/op.hpp"
namespace gfx {
    /**
     * \brief Construct a new camera.
     */
    camera::camera() : view_changed (true),
                       view () {};
    /**
     * \brief Destruct this camera
     */
    camera::~camera() {}
    /**
     * \brief Upload this camera as a uniform to the program given.
     * 
     * At the moment, this function requires that you have first specified
     * the names of the fields in a camera manually in the program
     * object.
     * \todo Fix this uniform problem
     * \param prgm The program to upload the uniform to
     * \param name The name of the camera variable in the shader source
     */
    void    camera::upload_uniform( program& prgm,
                                    std::string const& name )
    {
        check_program( prgm );
        std::string mod_name = name;
        mod_name += ".view";
        prgm.upload_uniform( mod_name, view );
    }
    /**
     * \brief Return the view matrix of this camera
     * \return The view matrix
     */
    mat4 const&     camera::view_matrix()
    {
        if ( view_changed ) {
            this->update_view();
        }
        return view;
    }
    /**
     * \brief Construct a new projection camera.
     * \param set The settings for the new projection camera
     */
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
    /**
     * \brief Destruct this projection camera.
     */
    proj_cam::~proj_cam() {}
    /**
     * \brief Set the projection camera's position.
     * \param point The position of the projection camera
     * \return This projection camera
     */
    proj_cam&     proj_cam::position( vec3 const& point )
    { pos = point; view_changed = true; return *this; }
    /**
     * \brief Set the point the projection camera looks at.
     * \param point The point the projection camera looks at
     * \return This projection camera
     */
    proj_cam&     proj_cam::look_at( vec3 const& point )
    { look = point; view_changed = true; return *this; }
    /**
     * \brief Set the direction the projection camera considers to be up.
     * \param dir The direction that the projection camera considers to be up
     * \return This projection camera
     */
    proj_cam&     proj_cam::upward( vec3 const& dir )
    { up = dir; view_changed = true; return *this; }
    /**
     * \brief Set the projection camera's vertical field of view.
     * \param vert The vertical field of view
     * \return This projection camera
     */
    proj_cam&     proj_cam::field_of_view( d_angle const& vert )
    {
        fov_vert = vert;
        view_changed = true;
        proj_changed = true;
        return *this;
    }
    /**
     * \brief Set the projection camera's aspect ratio.
     * \param vert The aspect ratio
     * \return This projection camera
     */
    proj_cam&     proj_cam::aspect_ratio( double ar )
    {
        aspect = ar;
        view_changed = true;
        proj_changed = true;
        return *this;
    }
    /**
     * \brief Set the projection camera's near clipping plane.
     * \param np The distance to the near clipping plane
     * \return This projection camera
     */
    proj_cam&     proj_cam::near_plane( double np )
    {
        near = np;
        view_changed = true;
        proj_changed = true;
        return *this;
    }
    /**
     * \brief Set the projection camera's far clipping plane.
     * \param fp The distance to the far clipping plane
     * \return This projection camera
     */
    proj_cam&     proj_cam::far_plane( double fp )
    {
        far = fp;
        view_changed = true;
        proj_changed = true;
        return *this;
    }
    /**
     * \brief Update the view matrix of the projection camera.
     * Used internally.
     */
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
    /**
     * \brief Construct a new orthographic camera.
     * \param set The settings for the new orthographic camera
     */
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
    /**
     * \brief Destruct this orthographic camera.
     */
    ortho_cam::~ortho_cam() {}
    /**
     * \brief Set the orthographic camera's position.
     * \param point The position of the orthographic camera
     * \return This orthographic camera
     */
    ortho_cam&     ortho_cam::position( vec3 const& point )
    { pos = point; view_changed = true; return *this; }
    /**
     * \brief Set the point the orthographic camera looks at.
     * \param point The point the orthographic camera looks at
     * \return This orthographic camera
     */
    ortho_cam&     ortho_cam::look_at( vec3 const& point )
    { look = point; view_changed = true; return *this; }
    /**
     * \brief Set the direction the orthographic camera considers to be up.
     * \param dir The direction that the orthographic camera considers to be up
     * \return This orthographic camera
     */
    ortho_cam&     ortho_cam::upward( vec3 const& dir )
    { up = dir; view_changed = true; return *this; }
    /**
     * \brief Set the orthographic camera's aspect ratio.
     * \param vert The aspect ratio
     * \return This orthographic camera
     */
    ortho_cam&     ortho_cam::aspect_ratio( double ar )
    {
        aspect = ar;
        view_changed = true;
        volume_changed = true;
        return *this;
    }
    /**
     * \brief Set the orthographic camera's scale.
     * \param vert The scale
     * \return This orthographic camera
     */
    ortho_cam&     ortho_cam::scale( double scl )
    { 
        scale_v = scl;
        view_changed = true;
        volume_changed = true;
        return *this;
    }
    /**
     * \brief Set the orthographic camera's far clipping plane.
     * \param fp The distance to the far clipping plane
     * \return This orthographic camera
     */
    ortho_cam&     ortho_cam::far_plane( double fp )
    {
        far = fp;
        view_changed = true;
        volume_changed = true;
        return *this;
    }
    /**
     * \brief Update the view matrix of the orthographic camera.
     * Used internally.
     */
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
    /**
     * \brief Construct a new process camera.
     * \param set The settings for the new process camera
     */
    process_cam::process_cam( settings const& set ) :
                               camera(),
                               mask ( set.mask_v ),
                               screen ( set.screen_v ),
                               clip_m ( mat4::identity() ),
                               clip_changed ( true ){}
    /**
     * \brief Destruct this process camera.
     */
    process_cam::~process_cam() {}
    /**
     * \brief Set the extent of the process camera's masking region.
     * \param ul_corner The upper left corner of the masking region
     * \param lr_corner The lower right corner of the masking region
     * \return This process camera
     */
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
    /**
     * \brief Set the full extent of the process camera's renderable area.
     * \param ul_corner The upper left corner of the renderable area
     * \param lr_corner The lower right corner of the renderable area
     * \return This process camera
     */
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
    /**
     * \brief Update the view matrix of the process camera.
     * Used internally.
     * \todo My internal comments indicate that this is totally broken.
     * So fix it.
     */
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