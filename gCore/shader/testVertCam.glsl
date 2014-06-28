#version 330

uniform mat4 view;

layout( location = 0 ) in vec3 pos;
layout( location = 1 ) in vec3 col;

out vec3 f_col;

void main()
{
    gl_Position = view * vec4( pos, 1.0 );
    f_col = col;
}