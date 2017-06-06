#version 330

struct camera {
    mat4 view;
};

//struct point_light {
//    float rad;
//    vec3  pos;
//    vec3  col;
//};

uniform mat4 obj_mat;

uniform camera cam;
//uniform point_light light;

layout( location = 0 ) in vec3 pos;
//layout( location = 1 ) in vec3 norm;
layout( location = 1 ) in vec3 col;

//out vec4 norm_out;
//out vec4 light_out;
//out float rad_out;
//out vec3 light_col_out;
out vec3 col_out;


void main()
{
    //mat4 transform = obj_mat;
    mat4 transform = cam.view * obj_mat;
    //norm_out = vec4( norm, 1.0f ) * transform;
    //light_out = vec4( light.pos - pos, 1.0f ) * transform;
    //light_col_out = light.col;
    //rad_out = light.rad;
    //gl_Position = vec4( pos, 1.0f ) * transform;
    
    //norm_out = vec4( norm, 0.0f );
    //light_out = vec4( light.pos, 1.0f );
    //rad_out = light.rad;
    //light_col_out = light.col;
    col_out = col;
    vec4 out_pos = transform * vec4( pos, 1.0f );
    //out_pos.z = -out_pos.z;
    gl_Position = out_pos;
}