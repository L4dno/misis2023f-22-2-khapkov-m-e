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

uniform sampler2D weight0;
uniform sampler2D weight1;
uniform sampler2D weight2;



void main()
{

 // Output debug message
    TraceLog(LOG_INFO, "Shader execution started");


    

    
    vec4 weightColour0 = texture(weight0, fragTexCoord);
    vec4 weightColour1 = texture(weight1, fragTexCoord);
    vec4 weightColour2 = texture(weight2, fragTexCoord);

    // Output debug message with texture sample values
    TraceLog(LOG_INFO, "weight1: %f, %f, %f, %f", weight0.r, weight0.g, weight0.b, weight0.a);
    //TraceLog(LOG_INFO, "Color2: %f, %f, %f, %f", color2.r, color2.g, color2.b, color2.a);
    //TraceLog(LOG_INFO, "Color3: %f, %f, %f, %f", color3.r, color3.g, color3.b, color3.a);

    // normalization ???
    vec4 weightColourSum = weightColour0 + weightColour1 + weightColour2;
    weightColour0 /=  weightColourSum;
    weightColour1 /=  weightColourSum;
    weightColour2 /=  weightColourSum;


    vec4 texelColor0 = texture(texture0, fragTexCoord);
    vec4 texelColor1 = texture(texture1, fragTexCoord);
    vec4 texelColor2 = texture(texture2, fragTexCoord);
    
    finalColor = texelColor0*weightColour0 + texelColor1*weightColour1 + texelColor2*weightColour2;
}
