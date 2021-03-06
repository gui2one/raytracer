#ifndef MESH_GENERATOR_H
#define MESH_GENERATOR_H

#include "../../pch.h"
#include "../../mesh.h"
#include "../param.h"


enum MESH_GENERATOR_TYPE
{
	GRID_MESH_GENERATOR,
	BOX_MESH_GENERATOR,
	CYLINDER_MESH_GENERATOR
};

class MeshGenerator
{
	public:
		MeshGenerator();
		
		virtual Mesh generate(); 
		
		virtual ~MeshGenerator();
		
		
		std::vector<BaseParam*> params;
	private:
		/* add your private declarations */
};

#endif /* MESH_GENERATOR_H */ 
