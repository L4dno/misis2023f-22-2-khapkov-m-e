#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Output fragment color
out vec4 finalColor;

//uniform sampler2D texture0; // Fragment input texture (always required, could be a white pixel)
//uniform vec4 colDiffuse;    // Fragment input color diffuse (multiplied by texture color)

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

// maps
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;



void main()
{


    
    vec4 weightColour0 = texture(texture3, fragTexCoord);
    vec4 weightColour1 = texture(texture4, fragTexCoord);
    vec4 weightColour2 = texture(texture5, fragTexCoord);

    // normalization ???
    vec4 weightColourSum = weightColour0 + weightColour1 + weightColour2;
    weightColour0 /=  weightColourSum;
    weightColour1 /=  weightColourSum;
    weightColour2 /=  weightColourSum;


    vec4 texelColor0 = texture(texture0, fragTexCoord);
    vec4 texelColor1 = texture(texture1, fragTexCoord);
    vec4 texelColor2 = texture(texture2, fragTexCoord);
    
    //finalColor = texelColor0*weightColour0 + texelColor1*weightColour1 + texelColor2*weightColour2;
    finalColor = weightColour0;
}
