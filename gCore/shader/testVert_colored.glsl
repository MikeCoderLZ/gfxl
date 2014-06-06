#version 330

layout( location = 0 ) in vec2 pos;
layout( location = 1 ) in vec3 color_in;
out vec4 color;

void main()
{
    gl_Position = vec4( pos.xy, 0.0, 1.0 );
    color = vec4( color_in, 1.0 );
}