#version 330

in vec3 f_col;
layout( location = 0 ) out vec4 color;

void main()
{
    color = vec4( f_col, 1.0f);
}