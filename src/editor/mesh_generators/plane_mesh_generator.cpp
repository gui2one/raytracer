#include "plane_mesh_generator.h"


PlaneMeshGenerator::PlaneMeshGenerator()
	: MeshGenerator()
{
	
	param_width = new Param<float>();
	param_width->setName("Width");
	param_width->setValue(1.0);
	params.push_back(param_width);
		
	param_length = new Param<float>();
	param_length->setName("Length");
	param_length->setValue(1.0);
	params.push_back(param_length);

}

Mesh PlaneMeshGenerator::generate()
{
	//~ std::cout << "PLANE Generator Generate function" << std::endl;
	
	Mesh mesh = EditorMeshUtils::makeQuad(param_width->getValue(), param_length->getValue());
	mesh.computeNormals();
	
	return mesh;
}


