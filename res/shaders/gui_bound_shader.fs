#version 130 

varying vec2 tex0;

uniform sampler2D tex;
uniform float border_width;
uniform vec4 border_color;
uniform float aspect;

uniform vec4 boundRect;

vec2 frag_pos;

void main()
{     
    float minX = border_width;
    float maxX = 1 - border_width;
    float minY = minX * aspect;
    float maxY = 1 - minY;

    frag_pos = gl_FragCoord.xy; 

    if (frag_pos.x > boundRect.x && frag_pos.x < boundRect.y && frag_pos.y > boundRect.z && frag_pos.y < boundRect.w) 
    {
        if (tex0.x < maxX && tex0.x > minX && tex0.y < maxY && tex0.y > minY) {
            gl_FragColor = texture2D(tex, tex0);
        } else {
            gl_FragColor = border_color;
        } 
    } else {
        gl_FragColor = vec4(0,0,0,0);
    }
}  