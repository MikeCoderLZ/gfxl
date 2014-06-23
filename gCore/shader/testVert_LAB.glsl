#version 330

layout( location = 0 ) in vec2 pos;
layout( location = 1 ) in vec3 color_in;
out vec4 color;

mat3 Cxr = mat3( 0.412453, 0.212671, 0.019334,
                 0.357580, 0.715160, 0.119193,
                 0.180423, 0.072169, 0.950227 );

mat3 B = mat3( vec3( 1.0479, 0.0296, -0.0092 ),
               vec3( 0.0229, 0.9904, 0.0151 ),
               vec3( -0.0502, -0.0171, 0.7519 ) );

void main()
{
    gl_Position = vec4( pos.xy, 0.0, 1.0 );
    vec3 XYZ_color = vec3 ( pow( color_in.r, 2.2 ),
                            pow( color_in.g, 2.2 ),
                            pow( color_in.b, 2.2 ) );
                     
    XYZ_color = B * Cxr * XYZ_color;
    XYZ_color = XYZ_color * vec3( 1.037021, 1.0, 1.211974 );
    
    float X_1;
    if ( XYZ_color.x > 0.008856 ) {
        X_1 = pow( XYZ_color.x, 0.33333333 );
    } else {
        X_1 = 7.787037 * XYZ_color.x + 0.137931034;
    }
    
    float Y_1;
    if ( XYZ_color.y > 0.008856 ) {
        Y_1 = pow( XYZ_color.y, 0.33333333 );
    } else {
        Y_1 = 7.787037 * XYZ_color.y + 0.137931034;
    }
    
    float Z_1;
    if ( XYZ_color.z > 0.008856 ) {
        Z_1 = pow( XYZ_color.z, 0.33333333 );
    } else {
        Z_1 = 7.787037 * XYZ_color.z + 0.137931034;
    }
    
    
    color = vec4( min( max( 0.0,    116.0 * Y_1 - 16.0  ), 100.0 ),
                  min( max( -128.0, 500.0 * (X_1 - Y_1) ), 128.0 ),
                  min( max( -128.0, 200.0 * (Y_1 - Z_1) ), 128.0 ),
                  1.0 );
}