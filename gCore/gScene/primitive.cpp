#include <vector>
#include "../gMath/datatype.hpp"
#include "primitive.hpp"

namespace gfx {
    /**
     * \brief Construct a new box.
     * \param set The settings object ofr this box.
     */
    box::box( box::settings const& set ) : primitive( set )
        {
            geom = new buffer( buffer::settings()
                            .blocks( 8 ) );
            geom->block_format( block_spec()
                            .attribute( type<vec3>() ) );
            std::vector< vec3 > position;
            position.push_back( vec3( 1.0f ) );
            position.push_back( vec3( -1.0f,  1.0f,  1.0f ) );
            position.push_back( vec3( -1.0f,  1.0f, -1.0f ) );
            position.push_back( vec3(  1.0f,  1.0f, -1.0f ) );
            position.push_back( vec3(  1.0f, -1.0f,  1.0f ) );
            position.push_back( vec3( -1.0f, -1.0f,  1.0f ) );
            position.push_back( vec3( -1.0f ) );
            position.push_back( vec3(  1.0f, -1.0f, -1.0f ) );
            
            geom->load_attribute( 0, position );
            
            draw_elements = new GLuint[36];
            draw_elements[0]  = 0;
            draw_elements[1]  = 4;
            draw_elements[2]  = 1;
            draw_elements[3]  = 4;
            draw_elements[4]  = 5;
            draw_elements[5]  = 1;
            draw_elements[6]  = 3;
            draw_elements[7]  = 7;
            draw_elements[8]  = 0;
            draw_elements[9]  = 0;
            draw_elements[10] = 7;
            draw_elements[11] = 4;
            draw_elements[12] = 2;
            draw_elements[13] = 6;
            draw_elements[14] = 3;
            draw_elements[15] = 3;
            draw_elements[16] = 6;
            draw_elements[17] = 7;
            draw_elements[18] = 1;
            draw_elements[19] = 5;
            draw_elements[20] = 2;
            draw_elements[21] = 2;
            draw_elements[22] = 5;
            draw_elements[23] = 6;
            draw_elements[24] = 1;
            draw_elements[25] = 3;
            draw_elements[26] = 0;
            draw_elements[27] = 1;
            draw_elements[28] = 2;
            draw_elements[29] = 3;
            draw_elements[30] = 5;
            draw_elements[31] = 7;
            draw_elements[32] = 6;
            draw_elements[33] = 5;
            draw_elements[34] = 4;
            draw_elements[35] = 7;
            
        }
    /**
     * Destruct this box.
     */
    box::~box() {
        delete geom;
        delete[] draw_elements;
    }
    /**
     * \brief Construct a new sphere.
     * \param set The Settiongs for the sphere.
     */
    sphere::sphere( sphere::settings const& set ) : primitive( set )
        {
            geom = new buffer( buffer::settings()
                            .blocks( 8 ) );
            geom->block_format( block_spec()
                            .attribute( type<vec3>() ) );
            std::vector< vec3 > position;
            position.push_back( vec3( 0.5f ) );
            position.push_back( vec3( -0.5f,  0.5f,  0.5f ) );
            position.push_back( vec3( -0.5f,  0.5f, -0.5f ) );
            position.push_back( vec3(  0.5f,  0.5f, -0.5f ) );
            position.push_back( vec3(  0.5f, -0.5f,  0.5f ) );
            position.push_back( vec3( -0.5f, -0.5f,  0.5f ) );
            position.push_back( vec3( -0.5f ) );
            position.push_back( vec3(  0.5f, -0.5f, -0.5f ) );
            
            geom->load_attribute( 0, position );
        }
    /**
     * \breif Destruc this sphere.
     */
    sphere::~sphere() {
        delete geom;
    }

}