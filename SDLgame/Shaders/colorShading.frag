#version 130
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;
uniform int lightArraySize;
uniform float lightColours[100*3];
uniform float lightPositions[100*2];
uniform float lightRadii[100];
//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

uniform sampler2D mySampler;

void main() {
	vec4 textureColor = texture(mySampler, fragmentUV);
	color = textureColor+fragmentColor;
	vec4 newLightColor = vec4(0.1, 0.1, 0.1, 1);
	float newLightIntensity = 0;
	for(int j = 0; j < lightArraySize; j++)
	{
	float d = distance(vec2(lightPositions[j*2], lightPositions[(j*2) + 1]), fragmentPosition);
	newLightIntensity = 1/(((d/lightRadii[j]))*((d/lightRadii[j])+1));
	newLightColor += (vec4(lightColours[j*3], lightColours[(j*3) + 1], lightColours[(j*3) + 2], 1)*newLightIntensity);
	}
	color = color * newLightColor;
	color.a = textureColor.a;
	//ambient
	color = color*0.5;
	color.a = textureColor.a;



	//-------
}