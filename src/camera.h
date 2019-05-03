#ifndef CAMERA_H
#define CAMERA_H

#include "pch.h"

class Camera
{
	public:
		Camera();
		inline void setProjection(float angle, float aspect, float near, float far)
		{ 
			projection = glm::perspective(angle, aspect, near, far);
			fov = angle;
		}
		
		float fov;
		glm::mat4 projection;
		glm::vec3 position;
		glm::vec3 target_position;
		glm::vec3 up_vector;
		
		
		
			
	private:
		/* add your private declarations */
};

#endif /* CAMERA_H */ 
