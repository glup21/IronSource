#version 440 core

uniform sampler2D colorTexture;

in vec3 fragNormal;
in vec3 fragPos;
in vec2 fragTexCoord;

out vec4 fragColor;

void main()
{
    vec4 texColor = texture(colorTexture, fragTexCoord);
    fragColor = vec4(texColor.rgb, 1.0);
}
