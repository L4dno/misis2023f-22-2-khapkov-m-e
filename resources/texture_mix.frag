#version 330

in vec3 vertexPos;
in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec4 colDiffuse;

uniform float divider = 0.5;

out vec4 finalColor;

void main () {
    
    // getting color at point, directed by fragTexCoord
    vec4 texelColor0 = texture(texture0, fragTexCoord);
    vec4 texelColor1 = texture(texture1, fragTexCoord);

    // fractial part of x coord
    float x = fract(fragTexCoord.s);
    // interpolate value (a,b,t)
    float final = smoothstep(divider - 0.1, divider + 0.1, x);
    // interpolate color
    finalColor = mix(texelColor0, texelColor1, final);
}