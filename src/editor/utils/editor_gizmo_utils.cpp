#include "editor_gizmo_utils.h"

static void offset_indices(std::vector<unsigned int>& indices, int offset)
{
	for (size_t i = 0; i < indices.size(); i++)
	{
		indices[i] += offset;
	}
	
}

static double degToRad(double degrees)
{
	return degrees / 180.0 * PI;
}

namespace EditorGizmoUtils
{
	OGL_geometry_data makeWireBox()
	{
		OGL_geometry_data geo_data;
		
		geo_data.vertices.clear();
		geo_data.indices.clear();
		
		geo_data.vertices.insert(
			geo_data.vertices.end(), {
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

		geo_data.indices.insert(
			geo_data.indices.end(), {
				0,1,1,2,2,3,3,0, // bottom square
				4,5,5,6,6,7,7,4, // top square
				0,4,
				1,5,
				2,6,
				3,7
			}
		);
			
		return geo_data;
	}

	OGL_geometry_data makeWirePrism()
	{
		OGL_geometry_data box_data = makeWireBox();
		
		for (size_t i = 0; i < 4; i++)
		{
			box_data.vertices[i*3+0] *= 0.5;
			box_data.vertices[i*3+1] *= 0.5;
			//~ box_data.vertices[i*3+2] *= 0.5;
		}
		
		return box_data;
		
	}
	
	OGL_geometry_data merge(const OGL_geometry_data& geo1, const OGL_geometry_data& geo2)
	{
		OGL_geometry_data merge_data, temp_data;
		merge_data = geo1;
		temp_data = geo2;
		offset_indices(temp_data.indices, merge_data.vertices.size()/3);
		
		merge_data.vertices.insert(
			merge_data.vertices.end(), temp_data.vertices.begin(), temp_data.vertices.end()
		);
		
		merge_data.indices.insert(
			merge_data.indices.end(), temp_data.indices.begin(), temp_data.indices.end()
		);
		
		return merge_data;
		
		
	}
	
	void translate(OGL_geometry_data& geo_data, glm::vec3 values)
	{
		for (size_t i = 0; i < geo_data.vertices.size(); i+=3)
		{
			geo_data.vertices[i+0] += values.x;
			geo_data.vertices[i+1] += values.y;
			geo_data.vertices[i+2] += values.z;
		}
		
	}


	void rotate(OGL_geometry_data& geo_data, glm::vec3 values, EDITOR_GIZMO_ROTATION_ORDER order)
	{
		switch(order){
			case ROT_ORDER_XYZ:
				for (size_t i = 0; i < geo_data.vertices.size() / 3; i++)
				{
					glm::vec3 pos = glm::vec3(
						geo_data.vertices[i*3 + 0],
						geo_data.vertices[i*3 + 1],
						geo_data.vertices[i*3 + 2]);
						
					pos = glm::rotateX( pos, (float)degToRad(values.x));
					pos = glm::rotateY( pos, (float)degToRad(values.y));
					pos = glm::rotateZ( pos, (float)degToRad(values.z));
					geo_data.vertices[i*3 + 0] = pos.x;
					geo_data.vertices[i*3 + 1] = pos.y;
					geo_data.vertices[i*3 + 2] = pos.z;
				}
				
				break;
		}
	}
	
	void scale(OGL_geometry_data& geo_data, glm::vec3 values)
	{
		for (size_t i = 0; i < geo_data.vertices.size()/3; i++)
		{
			geo_data.vertices[i*3 + 0] *= values.x;
			geo_data.vertices[i*3 + 1] *= values.y;
			geo_data.vertices[i*3 + 2] *= values.z;
		}
		
	}
} // end namespace


