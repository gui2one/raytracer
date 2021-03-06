#ifndef GRID_MESH_GENERATOR_H
#define GRID_MESH_GENERATOR_H

#include "mesh_generator.h"
#include "../utils/editor_mesh_utils.h"
class GridMeshGenerator: public MeshGenerator
{
	public:
		GridMeshGenerator();
			
		Mesh generate();
	private:
	
		Param<float> * param_width;
		Param<float> * param_length;
		Param<int> * param_segs_width;
		Param<int> * param_segs_length;
		ParamMenu    * param_menu;
		/* add your private declarations */
};

#endif /* GRID_MESH_GENERATOR_H */ 
