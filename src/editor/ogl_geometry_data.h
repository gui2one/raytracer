#ifndef OGL_GEOMETRY_DATA_H
#define OGL_GEOMETRY_DATA_H

struct OGL_DATA_2
{
	std::vector<float> positions;
	std::vector<float> colors;
	std::vector<float> uvs;
	
	std::vector<unsigned int> indices;
	
	
	void setColor(float r, float g, float b){
		if( colors.size() > 0) 
			colors.clear();
			
		for (size_t i = 0; i < positions.size(); i+=3)
		{
			colors.insert(
				colors.begin(), { r, g, b}
			);
		}
		
		
	}
};

struct OGL_geometry_data
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
	glm::vec3 translate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 rotate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
	

	
};

#endif /* OGL_GEOMETRY_DATA_H */
