#include "transform_mesh_filter.h"


TransformMeshFilter::TransformMeshFilter()
	: MeshFilter()
{
	
	param_position = new Param<glm::vec3>();
	params.push_back(param_position);
	
	param_rotation = new Param<glm::vec3>();
	params.push_back(param_rotation);
	
	param_scale = new Param<glm::vec3>();
	param_scale->setValue(glm::vec3(1.0, 1.0, 1.0));
	params.push_back(param_scale);
	
	type = TRANSFORM_MESH_FILTER;
	name = "traaansform";
}

void TransformMeshFilter::applyFilter(Mesh& mesh)
{
	//~ printf("applying filter\n");
	//~ printf("num faces : %d\n", mesh.faces.size());
	EditorMeshUtils::translate(mesh, param_position->getValue());
	EditorMeshUtils::rotate(mesh, param_rotation->getValue());
	EditorMeshUtils::scale(mesh, param_scale->getValue());
}


