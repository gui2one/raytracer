#ifndef TRANSFORM_MESH_FILTER_H
#define TRANSFORM_MESH_FILTER_H

#include "mesh_filter.h"
#include "../utils/editor_mesh_utils.h"

class TransformMeshFilter: public MeshFilter
{
	public:
		TransformMeshFilter();
			
		void applyFilter(Mesh& mesh) override;	
		Param<glm::vec3> * param_position;
		Param<glm::vec3> * param_rotation;
		Param<glm::vec3> * param_scale;
	private:
		/* add your private declarations */
};

#endif /* TRANSFORM_MESH_FILTER_H */ 
