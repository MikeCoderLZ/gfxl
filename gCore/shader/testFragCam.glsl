#version 330

uniform mat3 Crx = mat3(  3.240479, -0.9692556, 0.055648,
                         -1.537150,  1.875992, -0.204043,
                         -0.498535,  0.041556,  1.057311);

uniform mat3 B_1 = mat3( vec3( 0.9555, -0.0284, 0.0123 ),
                         vec3( -0.0231, 1.0100, -0.0205 ),
                         vec3( 0.0633, 0.0210, 1.3304 ) );

in vec3 f_col;
layout( location = 0 ) out vec4 color;

void main()
{

    vec3 RGB_color;
    RGB_color.y = (f_col.x + 16.0) * 0.008620689;
    RGB_color.x =  f_col.y * 0.002 + RGB_color.y;
    RGB_color.z = -f_col.z * 0.005 + RGB_color.y;
    
    if ( RGB_color.x > 0.20689655 ) {
        RGB_color.x = pow( RGB_color.x, 3.0 );
    } else {
        RGB_color.x = 0.12841854 * ( RGB_color.x - 0.137931034);
    }

    if ( RGB_color.y > 0.20689655 ) {
        RGB_color.y = pow( RGB_color.y, 3.0 );
    } else {
        RGB_color.y = 0.12841854 * ( RGB_color.y - 0.137931034);
    }
    
    if ( RGB_color.z > 0.20689655 ) {
        RGB_color.z = pow( RGB_color.z, 3.0 );
    } else {
        RGB_color.z = 0.12841854 * ( RGB_color.xz - 0.137931034);
    }
    
    RGB_color = RGB_color * vec3( 0.9643, 1.0, 0.8251 );
    
    RGB_color = Crx * B_1 * RGB_color;
    
    color = vec4( min( pow( max( 0.0, RGB_color.r ), 0.45454545 ), 1.0 ),
                  min( pow( max( 0.0, RGB_color.g ), 0.45454545 ), 1.0 ),
                  min( pow( max( 0.0, RGB_color.b ), 0.45454545 ), 1.0 ),
                  1.0 );

    //color = vec4( f_col, 1.0f);
}