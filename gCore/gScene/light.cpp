#include <string>

#include "../gVideo/gl_core_3_3.hpp"
#include "program.hpp"
#include "light.hpp"
#include "../gVideo/checkError.hpp"

namespace gfx {
    /**
     * \brief Construct a new light.
     */
    light::light() : rad ( 0.0f ) {}
    /**
     * \brief Upload this light as a uniform to the given
     * \ref gfx::program "program".
     * \todo The uniform class and programs aren't smart enough, yet,
     * for this to work properly. Some shenanigans using an updated
     * \ref gfx::info "info" and \ref gfx::type "type" system is needed.
     */
    void        light::upload_uniform( program& prgm,
                                       std::string const& name )
    {
        check_program( prgm );
        prgm.upload_uniform( name + ".rad", rad );
    }
    /**
     * \brief Set the radiance to the given value.
     * \param rad The radiance for the light
     * \return This light object
     */
    light&      light::radiance( float rad )
    { this->rad = rad; return *this; }
    /**
     * \brief Return the light object's radiance.
     * \return The radiance of the light object.
     */
    float       light::radiance() const
    { return rad; }
    /**
     * \brief Construct a new point light object.
     * \param set The settings for the new point light.
     */
    point_light::point_light( settings const& set ) :
                                    light (),
                                    pos ( set.pos_v ),
                                    col ( set.col_v )
    { rad = set.rad_v; }
    /**
     * \brief Set the position to the given value.
     * \param pos The position of the point light
     * \return This point light object
     */
    point_light&   point_light::position( vec3 const& pos )
    { this->pos = pos; return *this; }
    /**
     * \brief Return the point light's position.
     * \return The position of the point light object.
     */
    vec3 const&     point_light::position() const
    { return pos; }
    /**
     * \brief Set the color to the given value.
     * \param col The color of the point light
     * \return This point light object
     */
    point_light&   point_light::color( vec3 const& col )
    { this->col = col; return *this; }
    /**
     * \brief Return the point light's color.
     * \return The color of the point light object.
     */
    vec3 const&     point_light::color() const
    { return col; }
    /**
     * \brief Upload this point light as a uniform to the given
     * \ref gfx::program "program".
     * \todo The uniform class and programs aren't smart enough, yet,
     * for this to work properly. Some shenanigans using an updated
     * \ref gfx::info "info" and \ref gfx::type "type" system is needed.
     */
    void        point_light::upload_uniform( program& prgm,
                                              std::string const& name )
    {
        //std::cout << "Mark2" << std::endl;
        //std::cout << name << std::endl;
        //check_program( prgm );
        //std::string rad_name = name + ".rad";
        prgm.upload_uniform( name + ".rad", rad );
        //checkGLError( "Loaded uniform light.rad" );
        prgm.upload_uniform( name + ".pos", pos );
        prgm.upload_uniform( name + ".col", col );
    }
    /**
     * \brief Construct a new spherical light object.
     * \param set The settings for the new spherical light.
     */
    sphere_light::sphere_light( settings const& set ) :
                                    light (),
                                    pos ( set.pos_v ),
                                    col ( set.col_v ),
                                    rd ( set.rd_v ) { rad = set.rad_v; }
    /**
     * \brief Set the position to the given value.
     * \param pos The position of the spherical light
     * \return This spherical light object
     */
    sphere_light&   sphere_light::position( vec3 const& pos )
    { this->pos = pos; return *this; }
    /**
     * \brief Return the spherical light's position.
     * \return The position of the spherical light object.
     */
    vec3 const&     sphere_light::position() const
    { return pos; }
    /**
     * \brief Set the color to the given value.
     * \param col The color of the spherical light
     * \return This spherical light object
     */
    sphere_light&   sphere_light::color( vec3 const& col )
    { this->col = col; return *this; }
    /**
     * \brief Return the spherical light's color.
     * \return The color of the spherical light object.
     */
    vec3 const&     sphere_light::color() const
    { return col; }
    /**
     * \brief Set the radius to the given value.
     * \param rd The radius of the spherical light
     * \return This spherical light object
     */
    sphere_light&   sphere_light::radius( float rd )
    { this->rd = rd; return *this; }
    /**
     * \brief Return the spherical light's radius.
     * \return The radius of the spherical light object.
     */
    float     sphere_light::radius() const
    { return rd; }
    /**
     * \brief Upload this spherical light as a uniform to the given
     * \ref gfx::program "program".
     * \todo The uniform class and programs aren't smart enough, yet,
     * for this to work properly. Some shenanigans using an updated
     * \ref gfx::info "info" and \ref gfx::type "type" system is needed.
     */
    void        sphere_light::upload_uniform( program& prgm,
                                              std::string const& name )
    {
        check_program( prgm );
        prgm.upload_uniform( name + ".rad", rad );
        prgm.upload_uniform( name + ".pos", pos );
        prgm.upload_uniform( name + ".col", col );
        prgm.upload_uniform( name + ".rd", rd );
    }
    /**
     * \brief Construct a new spot light object.
     * \param set The settings for the new light.
     */
    spot_light::spot_light( settings const& set ) :
                            light(),
                            pos ( set.pos_v ),
                            dir ( set.dir_v ),
                            col ( set.col_v ),
                            swp ( set.swp_v ),
                            rd  ( set.rd_v ) { rad = set.rad_v; }
    /**
     * \brief Set the position to the given value.
     * \param pos The position of the spot light
     * \return This spot light object
     */
    spot_light&     spot_light::position( vec3 const& pos )
    { this->pos = pos; return *this; }
    /**
     * \brief Return the spot light's position.
     * \return The position of the spot light object.
     */
    vec3 const&     spot_light::position() const
    { return pos; }
    /**
     * \brief Set the direction to the given value.
     * \param dir The direction of the spot light
     * \return This spot light object
     */
    spot_light&     spot_light::direction( vec3 const& dir )
    { this->dir = dir; return *this; }
    /**
     * \brief Return the spot light's position.
     * \return The position of the spot light object.
     */
    vec3 const&     spot_light::direction() const
    { return dir; }
    /**
     * \brief Set the color to the given value.
     * \param col The color of the spot light
     * \return This spot light object
     */
    spot_light&     spot_light::color( vec3 const& col )
    { this->col = col; return *this; }
    /**
     * \brief Return the spot light's color.
     * \return The color of the spot light object.
     */
    vec3 const&     spot_light::color() const
    { return col; }
    /**
     * \brief Set the sweep angle to the given value.
     * \param col The sweep angle of the spot light
     * \return This spot light object
     */
    spot_light&     spot_light::sweep( angle const& swp )
    { this->swp = swp; return *this; }
    /**
     * \brief Return the spot light's sweep angle.
     * \return The sweep of the spot light object.
     */
    angle const&     spot_light::sweep() const
    { return swp; }
    /**
     * \brief Set the radius to the given value.
     * \param rd The raotl light object
     */
    spot_light&     spot_light::radius( float rd )
    { this->rd = rd; return *this; }
    /**
     * \brief Return the spot light's radius.
     * \return The radius of the spot light object.
     */
    float     spot_light::radius() const
    { return rd; }
    /**
     * \brief Upload this spot light as a uniform to the given
     * \ref gfx::program "program".
     * \todo The uniform class and programs aren't smart enough, yet,
     * for this to work properly. Some shenanigans using an updated
     * \ref gfx::info "info" and \ref gfx::type "type" system is needed.
     */
    void        spot_light::upload_uniform( program& prgm,
                                            std::string const& name )
    {
        check_program( prgm );
        prgm.upload_uniform( name + ".rad", rad );
        prgm.upload_uniform( name + ".pos", pos );
        prgm.upload_uniform( name + ".dir", dir );
        prgm.upload_uniform( name + ".col", col );
        prgm.upload_uniform( name + ".swp", swp );
        prgm.upload_uniform( name + ".rd", rd );
    }
    /**
     * \brief Construct a new point light object.
     * \param set The settings for the new sun light.
     */
    sun_light::sun_light( settings const& set ) :
                            light(),
                            dir ( set.dir_v ),
                            col ( set.col_v ) { rad = set.rad_v; }
    /**
     * \brief Set the direction to the given value.
     * \param dir The direction of the sun light
     * \return This sun light object
     */
    sun_light&     sun_light::direction( vec3 const& dir )
    { this->dir = dir; return *this; }
    /**
     * \brief Return the sun light's position.
     * \return The position of the sun light object.
     */
    vec3 const&     sun_light::direction() const
    { return dir; }
    /**
     * \brief Set the color to the given value.
     * \param col The color of the sun light
     * \return This sun light object
     */
    sun_light&     sun_light::color( vec3 const& col )
    { this->col = col; return *this; }
    /**
     * \brief Return the sun light's color.
     * \return The color of the sun light object.
     */
    vec3 const&     sun_light::color() const
    { return col; }
    /**
     * \brief Upload this sun light as a uniform to the given
     * \ref gfx::program "program".
     * \todo The uniform class and programs aren't smart enough, yet,
     * for this to work properly. Some shenanigans using an updated
     * \ref gfx::info "info" and \ref gfx::type "type" system is needed.
     */
    void        sun_light::upload_uniform( program& prgm,
                                           std::string const& name )
    {
        check_program( prgm );
        prgm.upload_uniform( name + ".rad", rad );
        prgm.upload_uniform( name + ".dir", dir );
        prgm.upload_uniform( name + ".col", col );
    }
}