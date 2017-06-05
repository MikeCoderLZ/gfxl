#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>

#include "../gMath/constant.hpp"
#include "../gMath/datatype.hpp"
#include "uniform.hpp"

namespace gfx {
    
    /**
     * struct light {
     *      float   rad;
     * }
     * */
    
    class light : public uniform {
    public:
                        light();
        virtual void    upload_uniform( program& prgm,
                                        std::string const& name );
        light&          radiance( float rad );
        float           radiance() const;

    protected:
        float           rad;
    };
    
    /**
     * struct point_light {
     *      float   rad;
     *      vec3    pos;
     *      vec3    col;
     * }
     * */
    
    class point_light : public light {
    public:
        class settings {
        public:
                        settings();
            settings&   radiance( float rad );
            settings&   position( vec3 const& pos );
            settings&   color( vec3 const& col );
            
        protected:
            float           rad_v;
            vec3            pos_v;
            vec3            col_v;
            friend          class point_light;
        };
                        point_light( settings const& set = settings() );
        point_light&    position( vec3 const& pos );
        vec3 const&     position() const;
        point_light&    color( vec3 const& col );
        vec3 const&     color() const;
        virtual void    upload_uniform( program& prgm,
                                        std::string const& name );
    protected:
        vec3            pos;
        vec3            col;
    };
    
    /**
     * struct sphere_light {
     *      float   rad;
     *      vec3    pos;
     *      vec3    col;
     *      float   rd;
     * }
     * */
    
    class sphere_light : public light {
    public:
        class settings {
        public:
                        settings();
            settings&   radiance( float rad );
            settings&   position( vec3 const& pos );
            settings&   color( vec3 const& col );
            settings&   radius( float rd );
            
        protected:
            float           rad_v;
            vec3            pos_v;
            vec3            col_v;
            float           rd_v;
            friend          class sphere_light;
        };
                        sphere_light( settings const& set = settings() );
        sphere_light&   position( vec3 const& pos );
        vec3 const&     position() const;
        sphere_light&   color( vec3 const& col );
        vec3 const&     color() const;
        sphere_light&   radius( float rd );
        float           radius() const;
        virtual void    upload_uniform( program& prgm,
                                        std::string const& name );
    protected:
        vec3            pos;
        vec3            col;
        float           rd;
    };
    
    inline sphere_light::settings::settings() :
                                    rad_v ( 1.0f ),
                                    pos_v ( vec3( 0.0f ) ),
                                    col_v ( vec3( 1.0f) ),
                                    rd_v ( 1.0f ) {}
                                    
    inline sphere_light::settings&
    sphere_light::settings::radiance( float rad )
    { rad_v = rad; return *this; }
    
    inline sphere_light::settings&
    sphere_light::settings::position( vec3 const& pos )
    { pos_v = pos; return *this; }
    
    inline sphere_light::settings&
    sphere_light::settings::color( vec3 const& col )
    { col_v = col; return *this; }
    
    inline sphere_light::settings&
    sphere_light::settings::radius( float rd )
    { rd_v = rd; return *this; }
    
    /**
     * struct spot_light {
     *      float   rad;
     *      vec3    pos;
     *      vec3    dir;
     *      vec3    col;
     *      vec3    swp;
     *      float   rd;
     * }
     * */
    
    class spot_light : public light {
    public:
        class settings {
        public:
                        settings();
            settings&   radiance( float rad );
            settings&   position( vec3 const& pos );
            settings&   direction( vec3 const& dir );
            settings&   color( vec3 const& col );
            settings&   sweep( angle const& swp );
            settings&   radius( float rd );
        protected:
            float           rad_v;
            vec3            pos_v;
            vec3            dir_v;
            vec3            col_v;
            angle           swp_v;
            float           rd_v;
            friend          class spot_light;
        };
                        spot_light( settings const& set = settings() );
        spot_light&     position( vec3 const& pos );
        vec3 const&     position() const;
        spot_light&     direction( vec3 const& dir );
        vec3 const&     direction() const;
        spot_light&     color( vec3 const& col );
        vec3 const&     color() const;
        spot_light&     sweep( angle const& swp );
        angle const&    sweep() const;
        spot_light&     radius( float rd );
        float           radius() const;
        virtual void    upload_uniform( program& prgm,
                                        std::string const& name );
    protected:
        vec3            pos;
        vec3            dir;
        vec3            col;
        angle           swp;
        float           rd;
    };
    
    inline spot_light::settings::settings() :
                                  rad_v ( 1.0f ),
                                  pos_v ( vec3( 0.0f ) ),
                                  dir_v ( vec3( 0.0f, 0.0f, -1.0f ) ),
                                  col_v ( vec3( 1.0f) ),
                                  swp_v ( angle::in_degs( 45.0f ) ),
                                  rd_v  ( 1.0f ) {}
    
    inline spot_light::settings&
    spot_light::settings::radiance( float rad )
    { rad_v = rad; return *this; }
    
    inline spot_light::settings&
    spot_light::settings::position( vec3 const& pos )
    { this->pos_v = pos; return *this; }
    
    inline spot_light::settings&
    spot_light::settings::direction( vec3 const& dir )
    { this->dir_v = dir; return *this; }
    
    inline spot_light::settings&
    spot_light::settings::color( vec3 const& col )
    { this->col_v = col; return *this; }
    
    inline spot_light::settings&
    spot_light::settings::sweep( angle const& swp )
    { this->swp_v = swp; return *this; }
    
    inline spot_light::settings&
    spot_light::settings::radius( float rd )
    { rd_v = rd; return *this; }
    
    /**
     * struct sun_light {
     *      float   rad;
     *      vec3    dir;
     *      vec3    col;
     * }
     * */
    
    class sun_light : public light {
    public:
        class settings {
        public:
                        settings();
            settings&   radiance( float rad );
            settings&   direction( vec3 const& dir );
            settings&   color( vec3 const& col );
        protected:
            float           rad_v;
            vec3            dir_v;
            vec3            col_v;
            friend          class sun_light;
        };
                        sun_light( settings const& set = settings() );
        sun_light&      direction( vec3 const& dir );
        vec3 const&     direction() const;
        sun_light&      color( vec3 const& col );
        vec3 const&     color() const;
        virtual void    upload_uniform( program& prgm,
                                        std::string const& name );
    protected:
        vec3            dir;
        vec3            col;
    };
    
    inline sun_light::settings::settings() :
                                  rad_v ( 1.0f ),
                                  dir_v ( vec3( 0.0f, 0.0f, -1.0f ) ),
                                  col_v ( vec3( 1.0f ) ) {}
    
    inline sun_light::settings&
    sun_light::settings::radiance( float rad )
    { rad_v = rad; return *this; }
    
    inline sun_light::settings&
    sun_light::settings::direction( vec3 const& dir )
    { this->dir_v = dir; return *this; }
    
    inline sun_light::settings&
    sun_light::settings::color( vec3 const& col )
    { this->col_v = col; return *this; }
}

#endif