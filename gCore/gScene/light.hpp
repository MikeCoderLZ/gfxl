#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>

#include "../gMath/constant.hpp"
#include "../gMath/datatype.hpp"
#include "uniform.hpp"

namespace gfx {
    
    /*
     * struct light {
     *      float   rad;
     * }
     * */
    /**
     * \class gfx::light light.hpp "gCore/gVideo/light.hpp"
     * \brief A representation of a simple light.
     * Intended as a base class for other lights as this one is missing
     * important rendering information like position or direction.
     */
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
    
    /*
     * struct point_light {
     *      float   rad;
     *      vec3    pos;
     *      vec3    col;
     * }
     * */
    /**
     * \class gfx::point_light light.hpp "gCore/gVideo/light.hpp"
     * \brief A representation of a point light.
     * This light has color and position as well as radiance.
     */
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
     * \brief Construct a default point light settings object.
     * A default light is position at the origin with a radiance of
     * 1 and is white.
     */
    inline point_light::settings::settings() : rad_v ( 1.0f ),
                                               pos_v ( vec3( 0.0f ) ),
                                               col_v ( vec3( 1.0f ) ) {}
    /**
     * \brief Set the radiance to the given value.
     * \param rad The radiance for the new point light
     * \return This settings object
     */
    inline point_light::settings& point_light::settings::radiance( float rad )
    {
        rad_v = rad;
        return *this;
    }
    /**
     * \brief Set the position to the given value.
     * \param pos The position of the new point light
     * \return This settings object
     */
    inline point_light::settings& point_light::settings::position( vec3 const& pos )
    {
        pos_v = pos;
        return *this;
    }
    /**
     * \brief Set the color to the given value.
     * \param color The color of the new point light
     * \return This settings object
     */
    inline point_light::settings& point_light::settings::color( vec3 const& col )
    {
        col_v = col;
        return *this;
    }
    
    /*
     * struct sphere_light {
     *      float   rad;
     *      vec3    pos;
     *      vec3    col;
     *      float   rd;
     * }
     * */
    /**
     * \class gfx::sphere_light light.hpp "gCore/gVideo/light.hpp"
     * \brief A representation of a spherical light source.
     * This light has color, position, and radius as well as radiance.
     * A sphere light is a type of area light where light is emitted from
     * the entire surface of a sphere of the given radius.
     * \todo Derive or look up the mathematics on how to do this in the shader.
     */
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
    /**
     * \brief Consruct a new default spherical light settings object.
     * The default spherical light is placed a the origin with a color of
     * white, a radiance of 1 and a radius of 1.
     */
    inline sphere_light::settings::settings() :
                                    rad_v ( 1.0f ),
                                    pos_v ( vec3( 0.0f ) ),
                                    col_v ( vec3( 1.0f) ),
                                    rd_v ( 1.0f ) {}
    /**
     * \brief Set the radiance to the given value.
     * \param rad The rad of the new spherical light
     * \return This settings object
     */
    inline sphere_light::settings&
    sphere_light::settings::radiance( float rad )
    { rad_v = rad; return *this; }
    /**
     * \brief Set the position to the given value/
     * \param pos The position of the new spherical light
     * \return This settings object
     */
    inline sphere_light::settings&
    sphere_light::settings::position( vec3 const& pos )
    { pos_v = pos; return *this; }
    /**
     * \brief Set the color to the given value/
     * \param pos The color of the new spherical light
     * \return This settings object
     */
    inline sphere_light::settings&
    sphere_light::settings::color( vec3 const& col )
    { col_v = col; return *this; }
    /**
     * \brief Set the radius to the given value/
     * \param pos The radius of the new spherical light
     * \return This settings object
     */
    inline sphere_light::settings&
    sphere_light::settings::radius( float rd )
    { rd_v = rd; return *this; }
    
    /*
     * struct spot_light {
     *      float   rad;
     *      vec3    pos;
     *      vec3    dir;
     *      vec3    col;
     *      vec3    swp;
     *      float   rd;
     * }
     * */
    /**
     * \class gfx::spot_light light.hpp "gCore/gVideo/light.hpp"
     * \brief A representation of a spot light.
     * This light has color and position as well as radiance. In addition,
     * spot lights have values related to the size of the cone they illumunate.
     * \todo This is even more complex than the sphere light mathematically.
     * Gonna take some work.
     */
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
    /**
     * \brief Construct a new default spot light settings object.
     * The default settings for a spot light are a radiance of 1,
     * placed at the origin, looking down the negative z-axis, with
     * a sweep angle of 45 degrees, a radius of 1, and a color of
     * white.
     */
    inline spot_light::settings::settings() :
                                  rad_v ( 1.0f ),
                                  pos_v ( vec3( 0.0f ) ),
                                  dir_v ( vec3( 0.0f, 0.0f, -1.0f ) ),
                                  col_v ( vec3( 1.0f) ),
                                  swp_v ( angle::in_degs( 45.0f ) ),
                                  rd_v  ( 1.0f ) {}
    /**
     * \brief Set the radiance to the given value.
     * \param rad The radiance of the new spot light.
     * \return This settings object
     */
    inline spot_light::settings&
    spot_light::settings::radiance( float rad )
    { rad_v = rad; return *this; }
    /**
     * \brief Set the position to the given value.
     * \param pos The position of the new spot light.
     * \return This settings object
     */
    inline spot_light::settings&
    spot_light::settings::position( vec3 const& pos )
    { this->pos_v = pos; return *this; }
    /**
     * \brief Set the direction to the given value.
     * \param dir The direction of the new spot light.
     * \return This settings object
     */
    inline spot_light::settings&
    spot_light::settings::direction( vec3 const& dir )
    { this->dir_v = dir; return *this; }
    /**
     * \brief Set the color to the given value.
     * \param col The color of the new spot light.
     * \return This settings object
     */
    inline spot_light::settings&
    spot_light::settings::color( vec3 const& col )
    { this->col_v = col; return *this; }
    /**
     * \brief Set the sweep to the given value.
     * \param swp The sweep of the new spot light.
     * \return This settings object
     */
    inline spot_light::settings&
    spot_light::settings::sweep( angle const& swp )
    { this->swp_v = swp; return *this; }
    /**
     * \brief Set the radius to the given value.
     * \param rd The radius of the new spot light.
     * \return This settings object
     */
    inline spot_light::settings&
    spot_light::settings::radius( float rd )
    { rd_v = rd; return *this; }
    
    /*
     * struct sun_light {
     *      float   rad;
     *      vec3    dir;
     *      vec3    col;
     * }
     * */
    /**
     * \class gfx::sun_light light.hpp "gCore/gVideo/light.hpp"
     * \brief A representation of a sun type light.
     * This light has color and direction as well as radiance. Sunlight
     * effectively shines from the same direction everywhere.
     */
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