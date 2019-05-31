#ifndef CONSTRUCTION_GRID_H
#define CONSTRUCTION_GRID_H


#include "../pch.h"
#include "../shader.h"
class ConstructionGrid
{
	public:
		ConstructionGrid();
		
		void init();
		void draw(Shader& shader);
			
		inline void setMajorSpace(float value)
		{
			major_space = value;
		}
		
		inline float getMajorSpace()
		{
			return major_space;
		}
		
		inline void setMinorDivs(unsigned int divs)
		{
			if( divs > 0 )
			{
				minor_divs = divs;
			}
		}
		
		inline unsigned int getMinorDivs()
		{
			return minor_divs;
		}
	private:

		unsigned int main_vbo  = 0, main_ibo  = 0;
		unsigned int minor_vbo = 0, minor_ibo = 0;
		unsigned int major_vbo = 0, major_ibo = 0;
		float major_space = 1.0;
		unsigned int minor_divs = 4;
		
		glm::vec3 position;
		glm::vec2 size;
		
		
		std::vector<float> minor_vertices, major_vertices, main_vertices;
		std::vector<unsigned int> minor_indices, major_indices, main_indices;
		
};

#endif /* CONSTRUCTION_GRID_H */ 
