#version 330

uniform sampler1D line;
in float uv;

layout( location = 0 ) out vec4 color_out;

void main()
{
    color_out = vec4( texture(line, uv).rgb, 1.0 );
}