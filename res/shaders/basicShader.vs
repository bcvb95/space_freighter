#version 130 

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec4 position0;
varying vec2 texCoord0;
varying vec4 normal0;

uniform mat4 modelMat;
uniform mat4 projMat;

void main()
{
    gl_Position = projMat * vec4(position, 1.0);

    position0 =  modelMat * vec4(position, 1);
    normal0 =  modelMat * vec4(position, 0);
    texCoord0 = texCoord; 
}