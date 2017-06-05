#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../gVideo/gl_core_3_3.hpp"
#include "buffer.hpp"
#include "orientable.hpp"

namespace gfx {

    class primitive : public orientable {
    public:
        
        class settings : public orientable::settings {
        public:
                        settings( orientable::settings const& super = orientable::settings() );
        };
                            primitive( settings const& set = settings() );
                            ~primitive();
        
        virtual buffer const&     geometry() const = 0;
    };
    
    inline primitive::settings::settings( orientable::settings const& super )
                                            : orientable::settings( super ) {}
    
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
    
    inline box::settings::settings( primitive::settings const& super )
                                    : primitive::settings( super ) {}
                                    
    inline buffer const&  box::geometry() const
    { return *geom; }
    
    /**
     * AHHHHHHHHHHHHHHHHHHHH!!!!!!!!!!!!!!!!!!!
     */
    inline GLuint*  box::draw_array()
    { return draw_elements; }
    
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
    
    inline sphere::settings::settings( primitive::settings const& super )
                                       : primitive::settings( super ) {}
    
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