#version 330

in vec4 norm_out;
in vec4 light_out;
in float rad_out;
in vec3 light_col_out;
in vec3 col_out;

layout( location = 0 ) out vec4 color;

void main()
{
    norm_out = normalize( norm_out );
    float dist = mag( light_out.xyz );
    shading = rad_out * max( dot( norm_out, normalize( light_out ) ), 0.0 ) * 6.28 / (dist * dist);
    color = light_col_out * col_out * shading;
}