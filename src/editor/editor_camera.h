#ifndef CAMERA_H
#define CAMERA_H

#include "../pch.h"
#include "entity3d.h"
#include "utils/editor_gizmo_utils.h"

class Camera : public Entity3D
{
	public:
		Camera();
		Camera(const Camera& other);// copy constructor
		Camera(Camera&& other); // move constructor
		Camera& operator=(const Camera& other);
		~Camera();
		void setProjection(float angle, float aspect, float near, float far);
		
		void applyTransforms() ; //override;
		void buildDisplayData();
		void draw(); // override;
		float fov = 20.0;
		glm::mat4 projection;
		
		//~ glm::vec3 position;
		//~ glm::vec3 rotation;
		//~ glm::vec3 scale;
		//~ 
		glm::vec3 target_position;
		glm::vec3 up_vector;
		
		
		unsigned int 
			main_vbo = 0, 
			main_ibo = 0;
			
		double    orbit_u = PI;
		double    orbit_v = PI / 3.0;
		double    orbit_radius = 5.0;
		glm::vec3 orbit_center = glm::vec3(0.0, 0.0, 0.0);
			
		
		
	private:
	
		std::vector<float> main_vertices;
		std::vector<unsigned int> main_indices;
		/* add your private declarations */
};

#endif /* CAMERA_H */ 
