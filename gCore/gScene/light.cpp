#include <string>

#include "light.hpp"

namespace gfx {
    
    light::light() : rad ( 0.0f ) {}
                    
    light&      light::radiance( float rad )
    { this->rad = rad; return *this; }
    
    float       light::radiance() const
    { return rad; }
    
    sphere_light::sphere_light( settings const& set ) :
                                    light (),
                                    pos ( set.pos_v ),
                                    col ( set.col_v ),
                                    rd ( set.rd_v ) { rad = set.rad_v; }
    
    sphere_light&   sphere_light::position( vec3 const& pos )
    { this->pos = pos; return *this; }
    
    vec3 const&     sphere_light::position() const
    { return col; }
    
    sphere_light&   sphere_light::color( vec3 const& col )
    { this->col = col; return *this; }
    
    vec3 const&     sphere_light::color() const
    { return col; }
    
    sphere_light&   sphere_light::radius( float rd )
    { this->rd = rd; return *this; }
    
    float     sphere_light::radius() const
    { return rd; }
    
    spot_light::spot_light( settings const& set ) :
                            light(),
                            pos ( set.pos_v ),
                            dir ( set.dir_v ),
                            col ( set.col_v ),
                            swp ( set.swp_v ),
                            rd  ( set.rd_v ) { rad = set.rad_v; }
                            
    spot_light&     spot_light::position( vec3 const& pos )
    { this->pos = pos; return *this; }
    vec3 const&     spot_light::position() const
    { return pos; }
    
    spot_light&     spot_light::direction( vec3 const& dir )
    { this->dir = dir; return *this; }
    vec3 const&     spot_light::direction() const
    { return dir; }
    
    spot_light&     spot_light::color( vec3 const& col )
    { this->col = col; return *this; }
    vec3 const&     spot_light::color() const
    { return col; }
    
    spot_light&     spot_light::sweep( angle const& swp )
    { this->swp = swp; return *this; }
    angle const&     spot_light::sweep() const
    { return swp; }
    
    spot_light&     spot_light::radius( float rd )
    { this->rd = rd; return *this; }
    float     spot_light::radius() const
    { return rd; }
    
    sun_light::sun_light( settings const& set ) :
                            light(),
                            dir ( set.dir_v ),
                            col ( set.col_v ) { rad = set.rad_v; }
    
    sun_light&     sun_light::direction( vec3 const& dir )
    { this->dir = dir; return *this; }
    vec3 const&     sun_light::direction() const
    { return dir; }
    
    sun_light&     sun_light::color( vec3 const& col )
    { this->col = col; return *this; }
    vec3 const&     sun_light::color() const
    { return col; }
}