#version 330

in vec4 norm_out;
in vec4 light_out;
in float rad_out;
in vec3 light_col_out;
in vec3 col_out;

layout( location = 0 ) out vec4 color;

void main()
{
    vec3 norm = normalize( norm_out.xyz );
    float dist = length( light_out.xyz );
    float shading = rad_out * max( dot( norm, normalize( light_out.xyz ) ), 0.0 ) * 6.28 / (dist * dist);
    color = vec4( light_col_out * col_out * shading, 1.0 );
}