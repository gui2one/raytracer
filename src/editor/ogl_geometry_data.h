#ifndef OGL_GEOMETRY_DATA_H
#define OGL_GEOMETRY_DATA_H

struct OGL_geometry_data
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
	glm::vec3 translate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 rotate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
	

	
};

#endif /* OGL_GEOMETRY_DATA_H */
