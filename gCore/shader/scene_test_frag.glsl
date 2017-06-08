#version 330

in vec4 norm_out;
in vec4 light_pos_out;
in float rad_out;
in vec3 light_col_out;
in vec3 col_out;

layout( location = 0 ) out vec4 color;

void main()
{
    vec3 norm = normalize( norm_out.xyz );
    float dist = length( light_pos_out.xyz );
    float shading = 0.12f + rad_out * max( dot( norm, normalize( light_pos_out.xyz ) ), 0.0 ) * 6.28 / (dist * dist);
    color = vec4( light_col_out * col_out * shading, 1.0 );
    //color = vec4( rad_out, rad_out, rad_out, 1.0f );
    //color = vec4( light_col_out.xyz, 1.0f);
    //color = vec4(col_out, 1.0);
}