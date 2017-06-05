#ifndef ORIENTABLE_HPP
#define ORIENTABLE_HPP

#include "../gMath/datatype.hpp"

namespace gfx {
 
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
    
    inline orientable::settings::settings() : scl_v ( vec3( 1.0f, 1.0f, 1.0f ) ),
                                              rot_v ( qutn() ),
                                              pos_v ( vec3() ) {}
                                    
    inline orientable::settings& orientable::settings::scale( vec3 const& scl )
    {
        scl_v = scl;
        return *this;
    }
    
    inline orientable::settings& orientable::settings::rotation( qutn const& rot )
    {
        rot_v = rot;
        return *this;
    }
    
    inline orientable::settings& orientable::settings::position( vec3 const& pos )
    {
        pos_v = pos;
        return *this;
    }
    
    inline vec3 const& orientable::scale() const
    { return scl; }
    
    inline qutn const& orientable::rotation() const
    { return rot; }
    
    inline vec3 const& orientable::position() const
    { return pos; }

}

#endif