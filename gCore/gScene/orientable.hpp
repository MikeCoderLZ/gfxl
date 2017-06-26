#ifndef ORIENTABLE_HPP
#define ORIENTABLE_HPP

#include "../gMath/datatype.hpp"

namespace gfx {
 
    /**
     * \class gfx::orientable orientable.hpp "gCore/gscne/orientable.hpp"
     * \brief A base class for any object that can be oriented in 3-space.
     * The rule with multiple inheritance is usually that you should keep
     * as much implementation out of the base classes in the multiply
     * inherited class tree. This class would ignore that rule is it is
     * used as a base class. I'm leaning towards using the composition
     * pattern from the mobile game, as it worked pretty well there.
     * In that case, orientable would just be another component and not
     * much would have to change (other than inheriting the base component
     * class).
     * 
     * Orientable implicitly means that the object exists within simulation
     * space; orientable objects are NOT used for any sort of GUI elements
     * or effects objects which have non-euclidean properties (such as a sky
     * box). Orientable does NOT imply that the object is collidable, though.
     * That would be the job of the (as yet unwritten) collidable class.
     */
    class orientable {
    public:
        class settings {
        public:
                        settings();
            settings&   scale( vec3 const& scl );
            settings&   rotation( qutn const& rot );
            settings&   position( vec3 const& pos );
        protected:
            vec3        scl_v;
            qutn        rot_v;
            vec3        pos_v;
    };
                        orientable( settings const& set = settings() );
        orientable&     scale( vec3 const& scl );
        orientable&     stretch( vec3 const& scl );
        vec3 const&     scale() const;
        orientable&     rotation( qutn const& rot );
        orientable&     rotate( qutn const& rot );
        qutn const&     rotation() const;
        orientable&     position( vec3 const& pos );
        orientable&     move( vec3 const& mov );
        vec3 const&     position() const;
        mat4 const&     object_matrix() const;
    protected:
        bool        orientation_changed;
        void        update_obj_mtrx();
    private:
        vec3        scl;
        qutn        rot;
        vec3        pos;
        mat4        obj_mtrx;
    };
    /**
     * \brief Construct a new orientable settings object with default settings.
     * The default settings for an orientable object are to have a scale of
     * 1 on all axes, a zeroed out rotation, and to be placed at the origin.
     */
    inline orientable::settings::settings() : scl_v ( vec3( 1.0f, 1.0f, 1.0f ) ),
                                              rot_v ( qutn() ),
                                              pos_v ( vec3() ) {}
    /**
     * \brief Set the scale of the new orientable object.
     * \param scl The scale of the new orientable object.
     * \return This settings object
     */
    inline orientable::settings& orientable::settings::scale( vec3 const& scl )
    {
        scl_v = scl;
        return *this;
    }
    /**
     * \brief Set the rotation of the new orientable object.
     * \param scl The rotation of the new orientable object.
     * \return This settings object
     */
    inline orientable::settings& orientable::settings::rotation( qutn const& rot )
    {
        rot_v = rot;
        return *this;
    }
    /**
     * \brief Set the position of the new orientable object.
     * \param scl The position of the new orientable object.
     * \return This settings object
     */
    inline orientable::settings& orientable::settings::position( vec3 const& pos )
    {
        pos_v = pos;
        return *this;
    }
    /**
     * \brief Return the scale of the orientable object.
     * \return The scale of the orientable object.
     */
    inline vec3 const& orientable::scale() const
    { return scl; }
    /**
     * \brief Return the rotation of the orientable object.
     * \return The rotation of the orientable object.
     */
    inline qutn const& orientable::rotation() const
    { return rot; }
    /**
     * \brief Return the position of the orientable object.
     * \return The position of the orientable object.
     */
    inline vec3 const& orientable::position() const
    { return pos; }

}

#endif