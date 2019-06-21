#ifndef CYLINDER_MESH_GENERATOR_H
#define CYLINDER_MESH_GENERATOR_H

#include "mesh_generator.h"
#include "../utils/editor_mesh_utils.h"
class CylinderMeshGenerator: public MeshGenerator
{
	public:
		CylinderMeshGenerator();
			
		Mesh generate();
	private:
	
		Param<float> * param_radius;
		Param<float> * param_height;
		Param<int> * param_segs_radius;
		Param<int> * param_segs_height;
		ParamMenu    * param_menu;
		/* add your private declarations */
};

#endif /* CYLINDER_MESH_GENERATOR_H */ 
