#include "editor_camera.h"


Camera::Camera() : 
	Entity3D(),	
	target_position(glm::vec3(0.0,0.0,0.0)),
	up_vector(glm::vec3(0.0,1.0,0.0))
{
	//~ printf("initializing Camera\n");
	
	name = "camera";
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

Camera::~Camera()
{
	//~ printf("Camera DESTRUCTOR\n");
	GLCall(glDeleteBuffers(1, &main_vbo));
	GLCall(glDeleteBuffers(1, &main_ibo));
	
	
}
void Camera::setProjection(float angle, float aspect, float near, float far)
{ 
	projection = glm::perspective(angle, aspect, near, far);
	fov = angle;
}

void Camera::applyTransforms()
{
	//~ printf("camera apply transforms\n");
	glm::mat4 temp = glm::mat4(1.0f);
	
	glm::mat4 view = glm::lookAt(position, target_position, up_vector);

	temp *= glm::inverse(view);
	
	
	temp = glm::scale(temp , scale);
	
	
	
	transforms = temp;		
}




void Camera::buildDisplayData()
{
	
	OGL_DATA_2 main_box_data = EditorGizmoUtils::makeWireBox();
	EditorGizmoUtils::translate(main_box_data, glm::vec3(0.0,0.0,0.5));
	
	OGL_DATA_2 prism = EditorGizmoUtils::makeWirePrism();
	EditorGizmoUtils::rotate(prism, glm::vec3(180.0, 0.0, 0.0));
	EditorGizmoUtils::translate(prism, glm::vec3(0.0, 0.0, -0.5));
	EditorGizmoUtils::scale(prism, glm::vec3(0.6, 0.6, 0.6));
	
	
	OGL_DATA_2 main_geo_data = EditorGizmoUtils::merge(main_box_data, prism);
	
	
	
	main_positions = main_geo_data.positions;
	main_indices = main_geo_data.indices;	

	// COLOR
	main_geo_data.setColor(0.0, 0.0, 1.0);
	
	if(main_vbo == 0){
		
		GLCall(glGenBuffers(1, &main_vbo));
		
	}else{
		GLCall(glDeleteBuffers(1, &main_vbo));
		GLCall(glGenBuffers(1, &main_vbo));
	}
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, main_vbo));
	
	
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* (main_positions.size() + main_geo_data.colors.size()), 0, GL_DYNAMIC_DRAW));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)* main_positions.size(), main_positions.data()));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)* main_positions.size(), sizeof(float)* main_geo_data.colors.size(), main_geo_data.colors.data()));
	
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
	//pos
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));
	//color
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void *)(sizeof(float) * main_positions.size())));

	
	GLCall(glEnableVertexAttribArray(0));// pos
	GLCall(glEnableVertexAttribArray(1));// color

	GLCall(glDrawElements(GL_LINES, main_indices.size(), GL_UNSIGNED_INT, nullptr));
	
	GLCall(glDisableVertexAttribArray(0));// pos
	GLCall(glDisableVertexAttribArray(1));// color

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));	
	
	
	//~ printf("camera drawing function ...\n");
}


