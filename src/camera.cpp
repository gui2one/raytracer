#include "camera.h"


Camera::Camera()
{
	printf("initializing Camera\n");
	up_vector = glm::vec3(0.0,1.0,0.0);
	target_position = glm::vec3(0.0,0.0,5.0);
}


