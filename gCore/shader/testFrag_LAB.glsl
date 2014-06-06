#version 330

in vec4 color;
layout( location = 0 ) out vec4 color_out;

mat3 Crx = mat3( vec3( 3.2410, -0.9692, 0.0556 ),
                 vec3( -1.5374, 1.8760, -0.2040 ),
                 vec3( -0.4986, 0.0416, 1.0570 ) );

mat3 B_1 = mat3( vec3( 0.9555, -0.0284, 0.0123 ),
                 vec3( -0.0231, 1.0100, -0.0205 ),
                 vec3( 0.0633, 0.0210, 1.3304 ) );

void main()
{
    vec3 color_XYZ;
    color_XYZ.y = (color.x + 16.0) / 116.0;
    color_XYZ.x = color.y / 500.0 + color_XYZ.y;
    color_XYZ.z = color_XYZ.y - color.z / 200.0;
    
    float X1 = pow( color_XYZ.x, 3.0 );
    if ( color_XYZ.x <= 0.206893 ) {
        X1 = (X1 - 16.0/116.0)/7.787;
    }
    float Y1 = pow( color_XYZ.y, 3.0 );
    if ( color_XYZ.y <= 0.206893 ) {
        Y1 = (Y1 - 16.0/116.0)/7.787;
    }
    float Z1 = pow( color_XYZ.z, 3.0 );
    if ( color_XYZ.z <= 0.206893 ) {
        Z1 = (Z1 - 16.0/116.0)/7.787;
    }
    
    vec3 color_RGB = Crx * ( vec3( X1, Y1, Z1 ) * vec3( 0.9643, 1.0000, 0.8251 ) );
    float R = 1.055 * pow(color_RGB.r, 1.0/2.4) - 0.055;
    if ( color_RGB.r <= 0.00304 )
    {
        R = 12.92 * color_RGB.r;
    }
    float G = 1.055 * pow(color_RGB.g, 1.0/2.4) - 0.055;
    if ( color_RGB.g <= 0.00304 )
    {
        G = 12.92 * color_RGB.g;
    }
    float B = 1.055 * pow(color_RGB.b, 1.0/2.4) - 0.055;
    if ( color_RGB.b <= 0.00304 )
    {
        B = 12.92 * color_RGB.b;
    }
//     float R = pow( color_RGB.r, 1.0/2.2 );
//     float G = pow( color_RGB.g, 1.0/2.2 );
//     float B = pow( color_RGB.b, 1.0/2.2 );
    
    color_out = vec4( R, G, B,
                      color.a );
//        color_out = vec4( color.r * 0.01, 0.0, 0.0, 1.0);
}