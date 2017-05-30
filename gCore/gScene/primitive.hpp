#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <vector>
#include "../gMath/datatype.hpp"
#include "buffer.hpp"

namespace gfx {

    class primitive {
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
                            primitive( settings const& set = settings() );
                            ~primitive();
        primitive&          scale( vec3 const& scl );
        vec3 const&         scale() const;
        primitive&          rotation( qutn const& rot );
        qutn const&         rotation() const;
        primitive&          position( vec3 const& pos );
        vec3 const&         position() const;
        
        mat4 const&         object_matrix() const;
        
        virtual buffer&     geometry() =0;
        
    protected:
        vec3        scale;
        qutn        rot;
        vec3        pos;
        mat4        obj_mat;
        buffer      geom;
    };
    
    inline primitive::settings::settings() : scl_v ( vec3( 1.0f ) ),
                                      rot_v ( qutn() ),
                                      pos_v ( vec3 () ) {}
                                      
    inline primitive::settings& primitive::settings::scale( vec3 const& scl )
    { scl_v = scl; return *this; }
    
    inline primitive::settings& primitive::settings::rotation( qutn const& rot )
    { rot_v = rot; return *this; }
    
    inline primitive::settings& primitive::settings::position( vec3 const& pos )
    { pos_v = pos; return *this; }
    
    class box : public primitive {
    public:
                            box( primitive::settings const& set );
                            ~box();
        virtual buffer&     geometry();
    };
    
    inline box::box( primitive::settings const& set ) : primitive( set )
    {
        geom = buffer( buffer::settings()
                       .blocks( 8 ) );
        geom.block_format( block_spec()
                           .attribute( type<vec3>() )
        std::vector< vec3 > position;
        position.push_back( vec3( 0.5f ) );
        position.push_back( vec3( -0.5f,  0.5f,  0.5f ) );
        position.push_back( vec3( -0.5f,  0.5f, -0.5f ) );
        position.push_back( vec3(  0.5f,  0.5f, -0.5f ) );
        position.push_back( vec3(  0.5f, -0.5f,  0.5f ) );
        position.push_back( vec3( -0.5f, -0.5f,  0.5f ) );
        position.push_back( vec3( -0.5f ) );
        position.push_back( vec3(  0.5f, -0.5f, -0.5f ) );
        
        geom.fill_attribute( 0, position );
    }
    
    class sphere : public primitive {
    public:
                            sphere( primitive::settings const& set );
                            ~sphere();
        virtual buffer&     geometry();    
    };
    
    inline sphere::sphere( primitive::settings const& set ) : primitive( set )
    {
        geom = buffer();
    }
    
    class cone : public primitive {
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
    }

}

#endif