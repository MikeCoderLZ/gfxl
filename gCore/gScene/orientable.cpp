#include "orientable.hpp"

namespace gfx {

    orientable::orientable( settings const& set ) : orientation_changed( false ),
                                                    scl ( set.scl_v ),
                                                    rot ( set.rot_v ),
                                                    pos ( set.pos_v ),
                                                    obj_mtrx( mat4::identity() )
    {
        obj_mtrx = update_obj_mtrx();
    }
    
    orientable& orientable::scale( vec3 const& scl ) 
    {
        orientation_changed = true;
        this->scl = scl;
        return *this;
    }
    
    orientable& orientable::stretch( vec3 const& stc ) 
    {
        orientation_changed = true;
        this->scl *= stc;
        return *this;
    }
    
    orientable& orientable::rotation( vec3 const& rot ) 
    {
        orientation_changed = true;
        this->rot = rot;
        return *this;
    }
    
    orientable& orientable::rotate( qutn const& rot ) 
    {
        orientation_changed = true;
        this->rot *= rot;
        return *this;
    }
    
    orientable& orientable::position( vec3 const& pos ) 
    {
        orientation_changed = true;
        this->pos = pos;
    }
    
    orientable& orientable::move( vec3 const& mov ) 
    {
        orientation_changed = true;
        this->pos += mov;
        return *this;
    }
    
    mat4 const& orientable::object_matrix() const
    {
        if ( orientation_changed ) {
            update_obj_mtrx;
        }
        return obj_mtrx;
    }
    
    void    orientable::update_obj_mtrx()
    {
        obj_mtrx = mat4::scale( scl )
                   * mat4::rotation( rot )
                   * mat4::position( pos );
        orientation_changed = false;
    }
    
}