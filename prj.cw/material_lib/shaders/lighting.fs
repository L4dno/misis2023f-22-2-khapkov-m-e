#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec2 fragTexCoord2;
in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D mask0;

uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;


void main()
{
    // Texel color fetching from texture sampler
    vec4 mask = texture(mask0, fragTexCoord2);

    vec4 baseColor = texture(texture0, fragTexCoord);
    vec4 layer1Color = texture(texture1, fragTexCoord);
    vec4 texelColor = mix(layer1Color, baseColor, mask.r);

    vec4 layer2Color = texture(texture2, fragTexCoord);
    texelColor = mix(layer2Color, texelColor, mask.g);

    vec4 layer3Color = texture(texture3, fragTexCoord);
    texelColor = mix(layer3Color, texelColor, mask.b);
   

    finalColor = texelColor;
}
