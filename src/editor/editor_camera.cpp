#include "editor_camera.h"


Camera::Camera() : Entity3D()
{
	//~ printf("initializing Camera\n");
	up_vector = glm::vec3(0.0,1.0,0.0);
	target_position = glm::vec3(0.0,0.0,5.0);
	buildDisplayData();
}

Camera::Camera(const Camera& other): Entity3D()
{
	up_vector = other.up_vector, 
	target_position = other.target_position; 
	fov = other.fov;
	
	printf("CAMERA COPY CONSTRUCTOR\n");
}

Camera::Camera(Camera&& other)// noexcept // move constructor
: fov(other.fov)
{
	printf("MOVE CONSTRUCTOR\n");
}

Camera& Camera::operator=(const Camera& other)
{
	printf("COPY ASSIGNEMENT\n");
	return *this = Camera(other);
	
}

void Camera::setProjection(float angle, float aspect, float near, float far)
{ 
	projection = glm::perspective(angle, aspect, near, far);
	fov = angle;
}

void Camera::buildDisplayData()
{
	main_vertices.clear();
	main_indices.clear();
	
	main_vertices.insert(
		main_vertices.end(), {
			-0.5, -0.5, -0.5,
			 0.5, -0.5, -0.5,
			 0.5,  0.5, -0.5,
			-0.5,  0.5, -0.5, 
			
			-0.5, -0.5,  0.5,
			 0.5, -0.5,  0.5,
			 0.5,  0.5,  0.5,
			-0.5,  0.5,  0.5 			
		}
	);

	main_indices.insert(
		main_indices.end(), {
			0,1,1,2,2,3,3,0, // bottom square
			4,5,5,6,6,7,7,4, // top square
			0,4,
			1,5,
			2,6,
			3,7
		}
	);
		
	if(main_vbo == 0){
		
		GLCall(glGenBuffers(1, &main_vbo));
		//~ printf("m_vbo from Camera --> %d\n", main_vbo);
	}else{
		GLCall(glDeleteBuffers(1, &main_vbo));
		GLCall(glGenBuffers(1, &main_vbo));
	}
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, main_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* main_vertices.size(), main_vertices.data(), GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));	
	
	if(main_ibo == 0)
	{
		GLCall(glGenBuffers(1, &main_ibo));
	}else{		
		GLCall(glDeleteBuffers(1, &main_ibo));
		GLCall(glGenBuffers(1, &main_ibo));
	}

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, main_ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* main_indices.size(), main_indices.data(), GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));		
}

void Camera::draw()
{
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, main_vbo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, main_ibo));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));
	
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glDrawElements(GL_LINES, main_indices.size(), GL_UNSIGNED_INT, nullptr));
	
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));	
	
	
	//~ printf("camera drawing function ...\n");
}


