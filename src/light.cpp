#include "light.h"


Light::Light():
	position(glm::vec3(0.0,0.0,0.0)),
	intensity(1.0),
	color(Color(1.0,1.0,0.0,1.0))
{
	
}


Light::~Light()
{
	
}

