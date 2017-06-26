#include "orientable.hpp"

namespace gfx {
    /**
     * \brief Construct a new orientable object.
     */
    orientable::orientable( settings const& set ) : orientation_changed( false ),
                                                    scl ( set.scl_v ),
                                                    rot ( set.rot_v ),
                                                    pos ( set.pos_v ),
                                                    obj_mtrx( mat4::identity() )
    {
        obj_mtrx = update_obj_mtrx();
    }
    /**
     * \brief Return the scale of the orientable object.
     * \return The scale of the orientable object.
     */
    vec3 const& orientable::scale() 
    { return scl; }
    /**
     * \brief Set the scale of the orientable object.
     * \param stc The scale of the orientable object.
     * \return This orientable object
     */
    orientable& orientable::stretch( vec3 const& stc ) 
    {
        orientation_changed = true;
        this->scl *= stc;
        return *this;
    }
    /**
     * \brief Return the rotiation of the orientable object.
     * \return The rotation of the orientable object.
     */
    vec3 const& orientable::rotation() 
    { return rot; }
    /**
     * \brief Set the rotation of the orientable object.
     * \param stc The rotation of the orientable object.
     * \return This orientable object
     */
    orientable& orientable::rotate( qutn const& rot ) 
    {
        orientation_changed = true;
        this->rot *= rot;
        return *this;
    }
    /**
     * \brief Return the position of the orientable object.
     * \return The position of the orientable object.
     */
    orientable& orientable::position( vec3 const& pos ) 
    {
        orientation_changed = true;
        this->pos = pos;
    }
    /**
     * \brief Set the position of the orientable object.
     * \param stc The position of the orientable object.
     * \return This orientable object
     */
    orientable& orientable::move( vec3 const& mov ) 
    {
        orientation_changed = true;
        this->pos += mov;
        return *this;
    }
    /**
     * \brief Return the transformation matrix of this orientable object.
     * \return The transformaton of the orientable object.
     */
    mat4 const& orientable::object_matrix() const
    {
        if ( orientation_changed ) {
            this->update_obj_mtrx();
        }
        return obj_mtrx;
    }
    /**
     * \brief Generate the trnasformation matrix from current settings.
     */
    void    orientable::update_obj_mtrx()
    {
        obj_mtrx = mat4::scale( scl )
                   * mat4::rotation( rot )
                   * mat4::position( pos );
        orientation_changed = false;
    }
    
}