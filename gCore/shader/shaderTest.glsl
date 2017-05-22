
@vert 'Vertex'
@using 330

layout( location = 0 ) in vec2 pos;

void main()
{
    gl_Position = vec4( pos.xy, 0.0, 1.0 );
}

@frag 'Fragment'
@using 330

layout( location = 0 ) out vec4 color;

void main()
{
    color = vec4( 1.0f, 0.0f, 1.0f, 1.0f);
}