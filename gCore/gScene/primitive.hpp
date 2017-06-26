#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../gVideo/gl_core_3_3.hpp"
#include "buffer.hpp"
#include "orientable.hpp"

namespace gfx {
    /**
     * \class gfx::primitive primitive.hpp "gCore/gScene/primitivie.hpp"
     * \brief An interface for basic shapes.
     * Primitives have geometry that is set and can only be manipulated
     * by changing the transformation matrix provided by the base class
     * \ref gfx::orientable "orientable".
     */
    class primitive : public orientable {
    public:
        
        class settings : public orientable::settings {
        public:
                        settings( orientable::settings const& super = orientable::settings() );
        };
                            primitive( settings const& set = settings() );
        virtual             ~primitive();
        
        virtual buffer const&     geometry() const = 0;
    };
    /**
     * \brief Construct a new default primtive settings object.
     * The default settings are the same as for \ref gfx::orientable
     * "orientable" objects.
     */
    inline primitive::settings::settings( orientable::settings const& super )
                                            : orientable::settings( super ) {}
    /**
     * \class gfx::box primitive.hpp "gCore/gScene/primitive.hpp"
     * \brief A six sided volume with all sides perpendicular to adjacent sides.
     */
    class box : public primitive {
    public:
        class settings: public primitive::settings {
        public:
            settings( primitive::settings const& super = primitive::settings() );
        };
                                box( settings const& set = settings() );
                                ~box();
        virtual buffer const&   geometry() const;
        // THIS IS JUST A HACK!!!!!!
        GLuint*                 draw_array();
    private:
        buffer*                 geom;
        GLuint*                 draw_elements;
    };
    /**
     * \brief Construct a new box settings object.
     */
    inline box::settings::settings( primitive::settings const& super )
                                    : primitive::settings( super ) {}
    /**
     * \brief Return the buffer of the box.
     * Using the buffer you can draw the box with OpenGL. I do not like this
     * method of drawing primtives, or any geometry for that matter. The ideal
     * solution is a 'technique' class that synthesizes the drawing settings
     * and tools like programs paired with a 'drawable' interface to define
     * how geometry is provided.
     */
    inline buffer const&  box::geometry() const
    { return *geom; }
    
    /**
     * \brief AHHHHHHHHHHHHHHHHHHHH!!!!!!!!!!!!!!!!!!!
     * The is just a HACK. See comments for \ref gfx::box::geometry geometry().
     */
    inline GLuint*  box::draw_array()
    { return draw_elements; }
    /**
     * \class gfx::sphere primitive.hpp "gCore/gScene/primitive.hpp"
     * \brief A spherical volume.
     */
    class sphere : public primitive {
    public:
        class settings : public primitive::settings {
        public:
                    settings( primitive::settings const& super = primitive::settings() );
        };
                                sphere( settings const& set = settings() );
                                ~sphere();
        virtual buffer const&   geometry() const;
    private:
        buffer*                 geom;
    };
    /**
     * \brief Construct a new sphere settings object.
     */
    inline sphere::settings::settings( primitive::settings const& super )
                                       : primitive::settings( super ) {}
    /**
     * \brief Return the buffer of the sphere.
     * Using the buffer you can draw the sphere with OpenGL. I do not like this
     * method of drawing primtives, or any geometry for that matter. The ideal
     * solution is a 'technique' class that synthesizes the drawing settings
     * and tools like programs paired with a 'drawable' interface to define
     * how geometry is provided.
     */
    inline buffer const&  sphere::geometry() const
    { return *geom; }
    
    /* class cone : public primitive {
    public:
                            cone( primitive::settings const& set );
                            ~cone();
        virtual buffer&     geometry();
    };
    
    inline sphere::sphere( primitive::settings const& set ) : primitive( set )
    {
        geom = buffer();
    }
    
    class cylinder : public primitive {
    public:
                            cylinder( primitive::settings const& set );
                            ~cylinder();
        virtual buffer&     geometry();
    };
    
    inline sphere::sphere( primitive::settings const& set ) : primitive( set )
    {
        geom = buffer();
    }
    
    class torus : public primitive {
    public:
                            torus( primitive::settings const& set );
                            ~torus();
        virtual buffer&     geometry();
    };
    
    inline sphere::sphere( primitive::settings const& set ) : primitive( set )
    {
        geom = buffer();
    }
    
    class plane : public primitive {
    public:
                            plane( primitive::settings const& set );
                            ~plane();
        virtual buffer&     geometry();
    };
    
    inline sphere::sphere( primitive::settings const& set ) : primitive( set )
    {
        geom = buffer();
    } */

}

#endif