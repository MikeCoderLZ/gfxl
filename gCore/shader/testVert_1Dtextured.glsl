#version 330

layout( location = 0 ) in vec2 pos;
layout( location = 1 ) in float uv_in;
out float uv;

void main()
{
    gl_Position = vec4( pos.xy, 0.0, 1.0 );
    uv = uv_in;
}