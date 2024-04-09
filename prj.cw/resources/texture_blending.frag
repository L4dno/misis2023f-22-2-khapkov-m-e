#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform sampler2D weight0;
uniform sampler2D weight1;
uniform sampler2D weight2;

// Output fragment color
out vec4 finalColor;

void main()
{
    
    vec4 weightColour0 = texture(weight0, fragTexCoord);
    vec4 weightColour1 = texture(weight1, fragTexCoord);
    vec4 weightColour2 = texture(weight2, fragTexCoord);

    // normalization ???
    //vec4 maskColourSum = maskColour0 + maskColour1 + maskColour2;
    //maskColour0 /=  maskColourSum;
    //maskColour1 /=  maskColourSum;
    //maskColour2 /=  maskColourSum;


    vec4 texelColor0 = texture(texture0, fragTexCoord);
    vec4 texelColor1 = texture(texture1, fragTexCoord);
    vec4 texelColor2 = texture(texture2, fragTexCoord);
    
    finalColor = texelColor0*weightColour0 + texelColor1*weightColour1 + texelColor2*weightColour2;
}
