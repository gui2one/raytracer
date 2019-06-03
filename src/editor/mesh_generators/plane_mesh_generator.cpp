#include "plane_mesh_generator.h"


PlaneMeshGenerator::PlaneMeshGenerator()
	: MeshGenerator()
{
	Param<int> * param_int = new Param<int>();
	param_int->setValue(42);
	params.push_back(param_int);
	
	Param<glm::vec3> * param_vec3 = new Param<glm::vec3>();
	param_vec3->setValue(glm::vec3(0.0,1.0,2.0));
	params.push_back(param_vec3);	
}

Mesh PlaneMeshGenerator::generate()
{
	//~ std::cout << "PLANE Generator Generate function" << std::endl;
	
	Mesh mesh = EditorMeshUtils::makeQuad();
	mesh.computeNormals();
	
	return mesh;
}


