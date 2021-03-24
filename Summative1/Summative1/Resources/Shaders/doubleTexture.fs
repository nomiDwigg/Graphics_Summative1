#version 460 core

in vec3 fragColour;
in vec2 fragTexture;


uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float mixValue;

out vec4 finalColour;

void main()
{
    finalColour = mix(texture(tex0, fragTexture), texture(tex1, fragTexture), mixValue);
}