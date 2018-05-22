#version 130

attribute vec4 position;

varying vec2 tex0;

uniform mat4 projMat;

void main()
{
    gl_Position = projMat * vec4(position.xy, 0.0, 1.0);
    tex0 = position.zw; 
}