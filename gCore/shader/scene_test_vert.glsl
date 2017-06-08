#version 330

struct camera {
    mat4 view;
};

struct point_light {
    float rad;
    vec3  pos;
    vec3  col;
};

uniform mat4 obj_mat;
uniform point_light light;
uniform camera cam;


layout( location = 0 ) in vec3 pos;
layout( location = 1 ) in vec3 norm;
layout( location = 2 ) in vec3 col;

out vec4 norm_out;
out vec4 light_pos_out;
out float rad_out;
out vec3 light_col_out;
out vec3 col_out;


void main()
{
    //mat4 transform = obj_mat;
    //mat4 transform = cam.view * obj_mat;
    vec4 out_pos = obj_mat * vec4( pos, 1.0f );
    light_pos_out = vec4( light.pos - out_pos.xyz, 1.0f );
    light_col_out = light.col;
    rad_out = light.rad;
    col_out = col;
    out_pos = cam.view * out_pos;
    norm_out = obj_mat * vec4( norm, 0.0f );
    gl_Position = out_pos;
}