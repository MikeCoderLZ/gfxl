#version 330

layout( location = 0 ) in vec2 pos;

void main()
{
    // Syntax error! Right..              V here!
    gl_Position = vec4( pos.xy, 0.0, 1.0 )
}