#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;

// Output fragment color
out vec4 finalColor;

// Input uniform values
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;

// masks
uniform sampler2D texture6;
uniform sampler2D texture7;
uniform sampler2D texture8;

void main()
{
    // Sample colors from textures and weight maps
    vec4 color1 = texture(texture3, fragTexCoord);
    vec4 color2 = texture(texture4, fragTexCoord);
    vec4 color3 = texture(texture5, fragTexCoord);

    vec4 weight1 = texture(texture6, fragTexCoord);
    vec4 weight2 = texture(texture7, fragTexCoord);
    vec4 weight3 = texture(texture8, fragTexCoord);

    // Normalize weights
    vec4 totalWeight = weight1 + weight2 + weight3;
    weight1 /= totalWeight;
    weight2 /= totalWeight;
    weight3 /= totalWeight;

    // Blend textures based on weight maps
    vec4 outColor = color1 * weight1 + color2 * weight2 + color3 * weight3;

    // Output final color
    finalColor = outColor;
}
