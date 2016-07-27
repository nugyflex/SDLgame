#version 130
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;
in float fragTest;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

uniform sampler2D mySampler;
uniform sampler1D test1;
uniform vec2 lightPos;
uniform float lightIntensity;
uniform float renderLighting;

float rand(vec2 n)
{
  return 0.5 + 0.5 * 
     fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}

void main() {
	vec4 textureColor = texture(mySampler, fragmentUV);
	if (texelFetch(test1, 0, 0) == vec4(1,1,1,1) && renderLighting == 1)
	{	
		color = textureColor+fragmentColor;
		vec4 light1color = vec4(0.1, 0.1, 1, 1);
		vec4 light2color = vec4(0, 1, 0, 1);
		//getDistance(fragmentPosition.x, fragmentPosition.y, _distance);
		//cos(x) returns a number between -1 and 1. To convert it into the range 0 to 1
		//you simply do (cos(x) + 1.0) * 0.5

		//Make crazy colors using time and position!
		
		//color = vec4(fragmentColor.r * tintensity/_distance,
		//             fragmentColor.g * tintensity/_distance,
		//             fragmentColor.b * tintensity/_distance/20, fragmentColor.a) * textureColor;
		// compute the current distance from light  
		float d = distance(lightPos, fragmentPosition);
		float d2 = distance(vec2(100,100), fragmentPosition);
		float r = 200;
		float newLightIntensity1 = lightIntensity/(((d/r)+1)*((d/r)+1));
		float newLightIntensity2 = 1/(((d2/r)+1)*((d2/r)+1));
		float newLightIntensity = 0;
		if (fragTest == 1)
		{
			newLightIntensity2 = 0;
		}
		if (fragTest == 0)
		{
			newLightIntensity1 = 0;
		}
		float staticRand = rand(vec2(1,100));
		vec4 newLightColor = (light1color*newLightIntensity1) + (light2color*newLightIntensity2) + 0.1;
		color = color * newLightColor;
		color.a = textureColor.a;
	}
	else
	{
		vec4 textureColor = texture(mySampler, fragmentUV);
		color = textureColor+fragmentColor;

	}
	//ambient
	color = color*0.5;
	color.a = textureColor.a;
	color = texelFetch(test1, 0, 0);
	//-------
}