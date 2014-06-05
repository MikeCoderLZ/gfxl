#version 330

layout( location = 0 ) out vec4 color;

void main()
{
    // Syntax error! Right...            V here!
    color = vec4( 1.0f, 0.0f, 1.0f, 0.5f)
}