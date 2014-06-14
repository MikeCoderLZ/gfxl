#version 330

uniform sampler2D smilie;
in vec2 uv;

layout( location = 0 ) out vec4 color_out;

void main()
{
    color_out = vec4( texture(smilie, uv).rgb, 1.0 );
}