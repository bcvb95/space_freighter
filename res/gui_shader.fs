#version 130 


varying vec2 tex0;

uniform sampler2D tex;

void main()
{     
    gl_FragColor = texture2D(tex, tex0);
}  