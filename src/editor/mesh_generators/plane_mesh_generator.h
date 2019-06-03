#ifndef PLANE_MESH_GENERATOR_H
#define PLANE_MESH_GENERATOR_H

#include "mesh_generator.h"
#include "../utils/editor_mesh_utils.h"
class PlaneMeshGenerator: public MeshGenerator
{
	public:
		PlaneMeshGenerator();
			
		Mesh generate();
	private:
		/* add your private declarations */
};

#endif /* PLANE_MESH_GENERATOR_H */ 
