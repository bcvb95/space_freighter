#version 130 


varying vec2 tex0;

uniform sampler2D texture;
uniform vec4 color;

void main()
{    
    vec4 sampled = vec4(1.0,1.0,1.0, texture2D(texture, tex0).r);
    gl_FragColor = sampled * color;
}  