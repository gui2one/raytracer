#include "editor_gizmo_utils.h"

static void offset_indices(std::vector<unsigned int>& indices, int offset)
{
	for (size_t i = 0; i < indices.size(); i++)
	{
		indices[i] += offset;
	}
	
}

static float lerpf(float a, float b, float ratio)
{
	return (b-a) * ratio + a;
}

static double degToRad(double degrees)
{
	return degrees / 180.0 * PI;
}

namespace EditorGizmoUtils
{

	OGL_DATA_2 makeWireBox()
	{
		OGL_DATA_2 geo_data;
		
		
		
		geo_data.positions.clear();
		geo_data.indices.clear();
		
		geo_data.positions.insert(
			geo_data.positions.end(), {
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

	
	OGL_DATA_2 makeWirePrism()
	{
		OGL_DATA_2 box_data = makeWireBox();
		
		for (size_t i = 0; i < 4; i++)
		{
			box_data.positions[i*3+0] *= 0.5;
			box_data.positions[i*3+1] *= 0.5;
			//~ box_data.vertices[i*3+2] *= 0.5;
		}
		
		return box_data;
		
	}	
		
	OGL_DATA_2 makeSimpleBox()
	{
		OGL_DATA_2 geo_data;
		
		
		
		geo_data.positions.clear();
		geo_data.indices.clear();
		
		geo_data.positions.insert(
			geo_data.positions.end(), {
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
				0,1,2, 0,2,3, // bottom face
				4,5,6, 4,6,7, // top face
				0,1,5, 0,5,4, // y facing 1
				2,3,7, 2,7,6, // y facing 2
				1,2,6, 1,6,5, // x facing 1
				3,0,4, 3,4,7 // x facing 2				
			}
		);
		
		return geo_data;		
	}	

	OGL_DATA_2 makeCone(float radius1, float radius2, float length, int segs_radius, int segs_length)
	{
		OGL_DATA_2 cone_data;
		
		std::vector<float> verts;
		verts.clear();
		
		for (int j = 0; j < segs_length; j++)
		{
			for (int i = 0; i < segs_radius; i++)
			{
				float height_ratio = (float)j / (segs_length-1);
				float radius = lerpf(radius1, radius2, height_ratio);
				verts.push_back(sin( (float)i / (segs_radius-1)*PI*2) * radius);
				verts.push_back(cos( (float)i / (segs_radius-1)*PI*2) * radius);
				verts.push_back(height_ratio * length);
			}
			
		}
		
		
		std::vector<unsigned int> indices;
		indices.clear();
		for (int j = 0; j < segs_length-1; j++)
		{
			for (int i = 0; i < segs_radius -1; i++)
			{
				indices.push_back((i + j * segs_radius) );
				indices.push_back((i + j * segs_radius) + 1 );
				indices.push_back((i + j * segs_radius) + segs_radius + 1);
				
				indices.push_back((i + j * segs_radius) );
				indices.push_back((i + j * segs_radius) + segs_radius + 1);
				indices.push_back((i + j * segs_radius) + segs_radius );
			}
		}
		
		cone_data.positions = verts;
		cone_data.indices = indices;
		return cone_data;
		

	}
		
	OGL_DATA_2 merge(const OGL_DATA_2& geo1, const OGL_DATA_2& geo2)
	{
		OGL_DATA_2 merge_data, temp_data;
		merge_data = geo1;
		temp_data = geo2;
		offset_indices(temp_data.indices, merge_data.positions.size()/3);
		
		merge_data.positions.insert(
			merge_data.positions.end(), temp_data.positions.begin(), temp_data.positions.end()
		);
		
		// merge colors if present in first input data
		if( geo1.colors.size() == geo1.positions.size() )
		{
			if(geo2.colors.size() == geo2.positions.size())
			{
				// there is colors on both, just merge
				merge_data.colors.insert(
					merge_data.colors.end(), temp_data.colors.begin(), temp_data.colors.end()
				);				
			}else{
				printf("adding default color \n");
				// create new default color on second input data
				for (size_t i = 0; i < geo2.positions.size(); i++)
				{
					
					temp_data.colors.push_back(1.0);
				}
				
				// then merge
				merge_data.colors.insert(
					merge_data.colors.end(), temp_data.colors.begin(), temp_data.colors.end()
				);					
			}
		}
		
		merge_data.indices.insert(
			merge_data.indices.end(), temp_data.indices.begin(), temp_data.indices.end()
		);
		
		return merge_data;
		
		
	}
		
		
	OGL_DATA_2 makeLine(glm::vec3 A, glm::vec3 B)
	{
		OGL_DATA_2 geo_data;
		geo_data.positions.clear();
		
		geo_data.positions.insert(
		
			geo_data.positions.begin(),{
				A.x, A.y, A.z, 
				B.x, B.y, B.z
			}
		);
		
		geo_data.indices.insert(
		
			geo_data.indices.begin(),{
				0,1
			}
		);
		
		return geo_data;
	}
	
	void translate(OGL_DATA_2& geo_data, glm::vec3 values)
	{
		for (size_t i = 0; i < geo_data.positions.size(); i+=3)
		{
			geo_data.positions[i+0] += values.x;
			geo_data.positions[i+1] += values.y;
			geo_data.positions[i+2] += values.z;
		}
		
	}

	void rotate(OGL_DATA_2& geo_data, glm::vec3 values, EDITOR_GIZMO_ROTATION_ORDER order)
	{
		switch(order){
			case ROT_ORDER_XYZ:
				for (size_t i = 0; i < geo_data.positions.size() / 3; i++)
				{
					glm::vec3 pos = glm::vec3(
						geo_data.positions[i*3 + 0],
						geo_data.positions[i*3 + 1],
						geo_data.positions[i*3 + 2]);
						
					pos = glm::rotateX( pos, (float)degToRad(values.x));
					pos = glm::rotateY( pos, (float)degToRad(values.y));
					pos = glm::rotateZ( pos, (float)degToRad(values.z));
					geo_data.positions[i*3 + 0] = pos.x;
					geo_data.positions[i*3 + 1] = pos.y;
					geo_data.positions[i*3 + 2] = pos.z;
				}
				
				break;
		}
	}

	void scale(OGL_DATA_2& geo_data, glm::vec3 values)
	{
		for (size_t i = 0; i < geo_data.positions.size()/3; i++)
		{
			geo_data.positions[i*3 + 0] *= values.x;
			geo_data.positions[i*3 + 1] *= values.y;
			geo_data.positions[i*3 + 2] *= values.z;
		}
		
	}	
} // end namespace


