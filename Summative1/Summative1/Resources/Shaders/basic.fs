#version 460 core

in vec3 fragColour;
in vec2 fragTexture;

uniform sampler2D tex;

out vec4 finalColour;

void main()
{
    finalColour = texture(tex, fragTexture);
}