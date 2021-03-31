#version 460 core

in vec3 fragColour;
in vec2 fragTexture;

out vec4 finalColour;

uniform sampler2D tex;

void main()
{
    finalColour = texture(tex, fragTexture);
}