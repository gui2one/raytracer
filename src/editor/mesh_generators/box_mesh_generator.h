#ifndef BOX_MESH_GENERATOR_H
#define BOX_MESH_GENERATOR_H

#include "mesh_generator.h"
#include "../utils/editor_mesh_utils.h"
class BoxMeshGenerator: public MeshGenerator
{
	public:
		BoxMeshGenerator();
			
		Mesh generate();
	private:
	
		Param<float> * param_width;
		Param<float> * param_length;
		Param<float> * param_height;
		Param<int>   * param_segs_width;
		Param<int>   * param_segs_length;
		Param<int>   * param_segs_height;
		
		/* add your private declarations */
};

#endif /* BOX_MESH_GENERATOR_H */ 
