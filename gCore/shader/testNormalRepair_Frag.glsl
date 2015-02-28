#version 330

uniform sampler2D smilie;
in vec2 uv;

layout( location = 0 ) out vec4 color_out;

void main()
{
    float uv_x = 0;
    float uv_x_rmd = modf( uv.x * 512.0f, uv_x );
    
    float uv_y = 0;
    float uv_y_rmd = modf( uv.y * 512.0f, uv_y );
    
    uv_x = mod( int(uv_x), 4 );
    uv_y = mod( int(uv_y), 4 );
    
    float radius = 0.1f;
    
    if( uv_x == 0 || uv_x == 3) {
        radius = 0.45f;
    }
    if( uv_y == 0 || uv_y == 3 ) {
        radius += 0.45f;
    }
    
    float delta = 1.0f / 512.0f * radius;
    float h_delta = delta * 0.5f;
    
    float xl1_uv = uv.x - h_delta;
    float xr1_uv = uv.x + h_delta;
    
    float xl2_uv = uv.x - delta - h_delta;
    float xr2_uv = uv.x + delta + h_delta;
    
    float yu1_uv = uv.y - h_delta;
    float yd1_uv = uv.y + h_delta;
    
    float yu2_uv = uv.y - delta - h_delta;
    float yd2_uv = uv.y + delta + h_delta;
    
    vec3 xl1 = texture(smilie, vec2(xl1_uv, yu1_uv) ).rgb;
    vec3 xr1 = texture(smilie, vec2(xr1_uv, yd1_uv) ).rgb;
    
    vec3 xl2 = texture(smilie, vec2(xl2_uv, yu2_uv) ).rgb;
    vec3 xr2 = texture(smilie, vec2(xr2_uv, yd2_uv) ).rgb;
    
    vec3 yu1 = texture(smilie, vec2(xr1_uv, yu1_uv) ).rgb;
    vec3 yd1 = texture(smilie, vec2(xl1_uv, yd1_uv) ).rgb;
    
    vec3 yu2 = texture(smilie, vec2(xr2_uv, yu2_uv) ).rgb;
    vec3 yd2 = texture(smilie, vec2(xl2_uv, yd2_uv) ).rgb;
    
    xl1.rg = xl1.rg * 2.0f - 1.0f;
    xr1.rg = xr1.rg * 2.0f - 1.0f;
    
    xl2.rg = xl2.rg * 2.0f - 1.0f;
    xr2.rg = xr2.rg * 2.0f - 1.0f;
    
    yu1.rg = yu1.rg * 2.0f - 1.0f;
    yd1.rg = yd1.rg * 2.0f - 1.0f;
    
    yu2.rg = yu2.rg * 2.0f - 1.0f;
    yd2.rg = yd2.rg * 2.0f - 1.0f;
    
    xl1 = normalize( xl1 );
    xr1 = normalize( xr1 );
    
    xl2 = normalize( xl2 );
    xr2 = normalize( xr2 );
    
    yu1 = normalize( yu1 );
    yd1 = normalize( yd1 );
    
    yu2 = normalize( yu2 );
    yd2 = normalize( yd2 );    
    
    // That'd be the mean of two quadratic Bezier curves aligned on the x,y axes
    
    vec3 dif = mix( mix( mix( xl2, xl1, 0.5f ),
                            mix( xl1, xr1, 0.5f ), 0.5f ),
                       mix( mix( xl1, xr1, 0.5f ),
                            mix( xr1, xr2, 0.5f ), 0.5f ), 0.5f );
    dif += mix( mix( mix( yu2, yu1, 0.5f ),
                        mix( yu1, yd1, 0.5f ), 0.5f ),
                   mix( mix( yu1, yd1, 0.5f ),
                        mix( yd1, yd2, 0.5f ), 0.5f ), 0.5f );
    
    vec3 normal = texture(smilie, uv).rgb;
    
    normal.g = normal.g * 2.0f - 1.0f;
    normal.r = normal.r * 2.0f - 1.0f;
    
    normal = normalize( normal );
    
    dif = normalize( dif + vec3( dif.xy, 0.0f ) * 0.05f );
    
    normal.rg = normal.rg * 0.5f + 0.5f;
    dif.rg = dif.rg * 0.5f + 0.5f;  
    
    color_out = vec4( dif, 1.0f );
}