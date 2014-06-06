#version 330

layout( location = 0 ) in vec2 pos;
layout( location = 1 ) in vec3 color_in;
out vec4 color;

mat3 Cxr = mat3( vec3( 0.4124, 0.2126, 0.0193 ),
                 vec3( 0.3576, 0.7152, 0.1192 ),
                 vec3( 0.1805, 0.0722, 0.9505 ) );

mat3 B = mat3( vec3( 1.0479, 0.0296, -0.0092 ),
               vec3( 0.0229, 0.9904, 0.0151 ),
               vec3( -0.0502, -0.0171, 0.7519 ) );

void main()
{
    gl_Position = vec4( pos.xy, 0.0, 1.0 );
    float X = pow((0.055+color_in.r)/1.055, 2.4);
    if( color_in.r <= 0.03928 )
    {
        X = color_in.r / 12.92;
    }
    float Y = pow((0.055+color_in.g)/1.055, 2.4);
    if( color_in.g <= 0.03928 )
    {
        Y = color_in.g / 12.92;
    }
    float Z = pow((0.055+color_in.b)/1.055, 2.4);
    if( color_in.b <= 0.03928 )
    {
        Z = color_in.b / 12.92;
    }
//     float X = pow(color_in.r, 2.2 );
//     float Y = pow(color_in.g, 2.2 );
//     float Z = pow(color_in.b, 2.2 );
    vec3 color_XYZ = vec3( X, Y, Z );
    color_XYZ = Cxr * color_in;
    color_XYZ = color_XYZ / vec3( 0.9643, 1.0000, 0.8251 );
    float X1 = pow( color_XYZ.x, 0.333333333 );
    if ( color_XYZ.x <= 0.008856 ) {
        X1 = 7.787 * color_XYZ.x + 16.0/116.0;
    }
    float Y1 = pow( color_XYZ.y, 0.333333333 );
    if ( color_XYZ.y <= 0.008856 ) {
        Y1 = 7.787 * color_XYZ.y + 16.0/116.0;
    }
    
    float Z1 = pow( color_XYZ.z, 0.333333333 );
    if ( color_XYZ.z <= 0.008856 ) {
        Z1 = 7.787 * color_XYZ.z + 16.0/116.0;
    }
    
    color = vec4( 116.0 * Y1 - 16.0,
                  500.0 * (X1 - Y1),
                  200.0 * (Y1 - Z1),
                  1.0 );
}