#version 130 

varying vec4 position0;
varying vec2 texCoord0;
varying vec4 normal0;

uniform sampler2D diffuseSampler;
uniform vec4 camPos;
uniform vec4 lightPos;
uniform vec4 lightColor;

uniform vec4 matEmmissive;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShiny;
uniform vec4 ambient;


void main()
{   
    // compute emmissive term
    vec4 Emmissive = matEmmissive;
    // compute diffuse term
    vec4 N = normalize(normal0);
    vec4 L = normalize(lightPos - position0);
    float NdotL = max(dot(N,L),0);
    vec4 Diffuse = NdotL * lightColor * matDiffuse;
    //compute specular term
    vec4 V = normalize(camPos - position0);
    vec4 H = normalize(L+V);
    vec4 R = reflect(-L, N);
    float RdotV = max(dot(R,V), 0);
    float NdotH = max(dot(N,H), 0);
    vec4 Specular = pow(NdotH, matShiny) * lightColor * matSpecular;
    // sum up the effects
    vec4 effect = (Emmissive + ambient + Diffuse + Specular);
    // set the fragment color
    gl_FragColor = effect * texture2D(diffuseSampler, texCoord0); 

}