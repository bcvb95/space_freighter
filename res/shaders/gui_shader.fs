#version 130 


varying vec2 tex0;

uniform sampler2D tex;
uniform float border_width;
uniform vec4 border_color;
uniform float aspect;

void main()
{     
    float minX = border_width;
    float maxX = 1 - border_width;
    float minY = minX * aspect;
    float maxY = 1 - minY;
    
    if (tex0.x < maxX && tex0.x > minX 
     && tex0.y < maxY && tex0.y > minY) {
        gl_FragColor = texture2D(tex, tex0);
    } else {
        gl_FragColor = border_color;
    } 

}  